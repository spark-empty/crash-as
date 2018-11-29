-- /**
-- * AS - the open source Automotive Software on https://github.com/parai
-- *
-- * Copyright (C) 2015  AS <parai@foxmail.com>
-- *
-- * This source code is free software; you can redistribute it and/or modify it
-- * under the terms of the GNU General Public License version 2 as published by the
-- * Free Software Foundation; See <http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt>.
-- *
-- * This program is distributed in the hope that it will be useful, but
-- * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
-- * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
-- * for more details.
-- */

-- place this file under LAU_PATH=/path/to/this/script/?.lua

-- ===================== [ INCLUDE  ] ================================
require("as")
require("os")
-- ===================== [ MACRO    ] ================================
local ISO15765_TPCI_MASK =  0x30
local ISO15765_TPCI_SF = 0x00         --/* Single Frame */
local ISO15765_TPCI_FF = 0x10         --/* First Frame */
local ISO15765_TPCI_CF = 0x20         --/* Consecutive Frame */
local ISO15765_TPCI_FC = 0x30         --/* Flow Control */
local ISO15765_TPCI_DL = 0x7          --/* Single frame data length mask */
local ISO15765_TPCI_FS_MASK = 0x0F    --/* Flow control status mask */


local ISO15765_FLOW_CONTROL_STATUS_CTS    =    0
local ISO15765_FLOW_CONTROL_STATUS_WAIT   =    1
local ISO15765_FLOW_CONTROL_STATUS_OVFLW  =    2

local CANTP_ST_IDLE = 0
local CANTP_ST_START_TO_SEND = 1
local CANTP_ST_SENDING = 2
local CANTP_ST_WAIT_FC = 3
local CANTP_ST_WAIT_CF = 4
local CANTP_ST_SEND_CF = 5
local CANTP_ST_SEND_FC = 6

local cfgSTmin = 10
local cfgBS    = 8
local cfgPadding = 0x55
-- ===================== [ LOCAL    ] ================================
local M = {}
local runtime = {}
-- ===================== [ DATA     ] ================================
cantp = M 
-- ===================== [ FUNCTION ] ================================
function M.init(channel,bus,rxid,txid)
  runtime[channel] = {}
  runtime[channel]["bus"]  = bus
  runtime[channel]["rxid"] = rxid
  runtime[channel]["txid"] = txid
  
  runtime[channel]["t_size"] = 0 -- already transmit size or receive response data size 

  -- get on FC
  runtime[channel]["cfgSTmin"] = 0
  
  runtime[channel]["SN"] = 0
  runtime[channel]["BS"] = 0
  runtime[channel]["STmin"] = 0
  runtime[channel]["state"] = CANTP_ST_IDLE
end

local function sendSF(channel,data)
  length = rawlen(data)
  bus = runtime[channel]["bus"]
  txid = runtime[channel]["txid"]
  pdu = {}
  pdu[1] = ISO15765_TPCI_SF | length
  for i=2,length+1,1 do
    pdu[i] = data[i-1]
  end
  for i=length+2,8,1 do
    pdu[i] = cfgPadding
  end

  return as.can_write(bus,txid,pdu)
end

local function sendFF(channel,data)
  length = rawlen(data)
  bus = runtime[channel]["bus"]
  txid = runtime[channel]["txid"]
  pdu = {}
  pdu[1] = ISO15765_TPCI_FF | ((length>>8)&0x0F)
  pdu[2] = length&0xFF
  
  for i=3,8,1 do
    pdu[i] = data[i-2]
  end
  
  runtime[channel]["SN"] = 0
  runtime[channel]["t_size"] = 6
  runtime[channel]["state"] = CANTP_ST_WAIT_FC
  
  return as.can_write(bus,txid,pdu)
end

local function elapsed(pre)

  gap = as.time() -pre

  return gap
end

-- wait a response frame
local function waitRF(channel)
  ercd = false
  data=nil
  rxid = runtime[channel]["rxid"]
  pre = as.time()
  while (elapsed(pre) < 5.0) and (ercd == false) do   -- 1s timeout
    result,canid,data = as.can_read(channel,rxid)
    if result and (canid == rxid) then
      ercd = true
      break
    else
      os.usleep(10) -- sleep a while 
    end
  end
  
  if false == ercd then
    print("cantp timeout when receiving a frame! elapsed time = ",elapsed(pre)," s!")
  end
  
  return ercd,data
end

local function sendCF(channel,request) 
  sz = rawlen(request)
  bus = runtime[channel]["bus"]
  txid = runtime[channel]["txid"]
  t_size = runtime[channel]["t_size"]
  pdu = {}
  
  runtime[channel]["SN"] = runtime[channel]["SN"] + 1
  if runtime[channel]["SN"] > 15 then
    runtime[channel]["SN"] = 0
  end
  l_size = sz - t_size  --  left size 
  if l_size > 7 then
    l_size = 7
  end
  
  pdu[1] = ISO15765_TPCI_CF | runtime[channel]["SN"]
  
  for i=1,l_size,1 do
    pdu[1+i] = request[t_size+i]
  end
  
   for i=l_size+2,8,1 do
    pdu[i] = cfgPadding
  end
  
  runtime[channel]["t_size"] = runtime[channel]["t_size"] + l_size
  
  if runtime[channel]["t_size"] == sz then
    runtime[channel]["state"] = CANTP_ST_IDLE
  else
    if runtime[channel]["BS"] > 0 then
      runtime[channel]["BS"] = runtime[channel]["BS"] - 1
      if 0 == runtime[channel]["BS"] then
        runtime[channel]["state"] = CANTP_ST_WAIT_FC
      else
        runtime[channel]["state"] = CANTP_ST_SEND_CF
      end
    else
      runtime[channel]["state"] = CANTP_ST_SEND_CF
    end
  end
  
  runtime[channel]["STmin"] = runtime[channel]["cfgSTmin"]
  
  return as.can_write(bus,txid,pdu)
end

local function handleFC(channel,request)
  ercd,data = waitRF(channel)
  if true == ercd then
    if (data[1]&ISO15765_TPCI_MASK) == ISO15765_TPCI_FC then
      if (data[1]&ISO15765_TPCI_FS_MASK) == ISO15765_FLOW_CONTROL_STATUS_CTS then
        runtime[channel]["cfgSTmin"] = data[3]
        runtime[channel]["BS"] = data[2]
        runtime[channel]["STmin"] = 0   -- send the first CF immediately
        runtime[channel]["state"] = CANTP_ST_SEND_CF
      elseif (data[1]&ISO15765_TPCI_FS_MASK) == ISO15765_FLOW_CONTROL_STATUS_WAIT then
        runtime[channel]["state"] = CANTP_ST_WAIT_FC
      elseif (data[1]&ISO15765_TPCI_FS_MASK) == ISO15765_FLOW_CONTROL_STATUS_OVFLW then
        print("cantp buffer over-flow, cancel...")
        ercd = false
      else
        print(string.format("FC error as reason %X,invalid flow status",data[1]))
        ercd = false
      end
    else
      print(string.format("FC error as reason %X,invalid PCI",data[1]))
      ercd = false 
    end
  end
  return ercd
end

local function waitms(timeout)
	pre = os.clock()
	while (os.clock()-pre)<(timeout/1000) do
	end
end

local function ScheduleTx(channel,request)

  length = rawlen(request)

  ercd = sendFF(channel,request)  -- FF sends 6 bytes
  
  if true == ercd then
    while(runtime[channel]["t_size"] < length) do
      if runtime[channel]["state"] == CANTP_ST_WAIT_FC then
        ercd = handleFC(channel,request);
      elseif runtime[channel]["state"] == CANTP_ST_SEND_CF then
        if runtime[channel]["STmin"] > 0 then
		  waitms(runtime[channel]["STmin"]);
		  runtime[channel]["STmin"] = 0
        end
        if runtime[channel]["STmin"] == 0 then
          ercd = sendCF(channel,request);
        end
      else
        print("cantp: transmit unknown state ",runtime[channel]["state"])
        ercd = false
      end
      if ercd == false then
        break
      end
    end
  end
  
  return ercd
end

function M.transmit(channel,data)
  -- print("request: ",channel,table.concat(data, ":"))
  if rawlen(data) < 7 then
    ercd = sendSF(channel,data)
  else
    ercd = ScheduleTx(channel,data)
  end
  return ercd
end

local function waitSForFF(channel,response)
  ercd,data = waitRF(channel)
  finished = false
  if true == ercd then
    if (data[1]&ISO15765_TPCI_MASK) == ISO15765_TPCI_SF then
      lsize = data[1]&ISO15765_TPCI_DL
      for i=1,lsize,1 do
        response[i] = data[1+i]
      end
      ercd = true
      finished = true
    elseif (data[1]&ISO15765_TPCI_MASK) == ISO15765_TPCI_FF then
      runtime[channel]["t_size"] = ((data[1]&0x0F)<<8) + data[2]
      for i=1,6,1 do
        response[i] = data[2+i]
      end
      runtime[channel]["state"] = CANTP_ST_SEND_FC
      runtime[channel]["SN"] = 0
      ercd = true
      finished = false
    else
      ercd = false
      finished = true
    end
  end

  return ercd,finished
end

local function waitCF(channel,response) 
  sz = rawlen(response)
  t_size = runtime[channel]["t_size"]
  
  ercd,data = waitRF(channel)
  
  if true == ercd then
    if (data[1]&ISO15765_TPCI_MASK) == ISO15765_TPCI_CF then
      runtime[channel]["SN"] = runtime[channel]["SN"] + 1
      if runtime[channel]["SN"] > 15 then
        runtime[channel]["SN"] = 0
      end
      
      SN = data[1]&0x0F
      if SN == runtime[channel]["SN"] then
        l_size = t_size -sz  --  left size 
        if l_size > 7 then
          l_size = 7
        end
        for i=1,l_size,1 do
          response[sz+i] = data[1+i]
        end
        
        if (sz+l_size) == t_size then
          finished = true
        else
          if runtime[channel]["BS"] > 0 then
            runtime[channel]["BS"] = runtime[channel]["BS"] - 1
            if 0 == runtime[channel]["BS"] then
              runtime[channel]["state"] = CANTP_ST_SEND_FC
            else
              runtime[channel]["state"] = CANTP_ST_WAIT_CF
            end
          else
            runtime[channel]["state"] = CANTP_ST_WAIT_CF
          end
        end
      else
        ercd = false
        finished = true
        print("cantp: wrong sequence number!",SN,runtime[channel]["SN"])
      end
    else
      ercd = false
      finished = true
    end
  end
  
  return ercd,finished
end

local function sendFC(channel)
  
  bus = runtime[channel]["bus"]
  txid = runtime[channel]["txid"]
  pdu = {}
  pdu[1] = ISO15765_TPCI_FC | ISO15765_FLOW_CONTROL_STATUS_CTS
  pdu[2] = cfgBS
  pdu[3] = cfgSTmin
  
  for i=4,8,1 do
    pdu[i] = cfgPadding
  end
  
  runtime[channel]["BS"] = cfgBS
  runtime[channel]["state"] = CANTP_ST_WAIT_CF
  
  return as.can_write(bus,txid,pdu)
end

function M.receive(channel)
  ercd = true
  response = {}
  
  finished = false
  
  ercd,finished = waitSForFF(channel,response)

  while (true == ercd) and (false == finished) do
    if runtime[channel]["state"] == CANTP_ST_SEND_FC then
      ercd = sendFC(channel)
    elseif runtime[channel]["state"] == CANTP_ST_WAIT_CF then
      ercd,finished = waitCF(channel,response)
    else
      print("cantp: receive unknown state ",runtime[channel]["state"])
      ercd = false
    end
  end
  
  -- print("response:",channel,table.concat(response, ":"))
  return ercd,response
end
-- ===================== [ INSTANCE ] ================================
return cantp
