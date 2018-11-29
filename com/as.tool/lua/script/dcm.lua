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
require("cantp")
-- ===================== [ MACRO    ] ================================

-- ===================== [ LOCAL    ] ================================
local M = {}
local runtime = {}
local l_service = { [0x10]="diagnostic session control",[0x11]="ecu reset",[0x14]="clear diagnostic information",
                [0x19]="read dtc information",[0x22]="read data by identifier",[0x23]="read memory by address",
                [0x24]="read scaling data by identifier",[0x27]="security access",[0x28]="communication control",
                [0x2A]="read data by periodic identifier",[0x2C]="dynamically define data identifier",[0x2E]="write data by identifier",
                [0x2F]="input output control by identifier",[0x31]="routine control",[0x34]="request download",
                [0x35]="request upload",[0x36]="transfer data",[0x37]="request transfer exit",
                [0x3D]="write memory by address",[0x3E]="tester present",[0x7F]="negative response",
                [0x85]="control dtc setting",[0x01]="request current powertrain diagnostic data",[0x02]="request powertrain freeze frame data",
                [0x04]="clear emission related diagnostic information",[0x03]="request emission related diagnostic trouble codes",[0x07]="request emission related diagnostic trouble codes detected during current or last completed driving cycle",
                [0x09]="request vehicle information"}
                
local l_nrc = { [0x10]="general reject",[0x21]="busy repeat request",[0x22]="conditions not correct",
                [0x24]="request sequence error",[0x31]="request out of range",[0x33]="secutity access denied",
                [0x35]="invalid key",[0x72]="general programming failure",[0x73]="wrong block sequence counter",
                [0x7E]="sub function not supported in active session",[0x81]="rpm too high",[0x82]="rpm to low",
                [0x83]="engine is running",[0x84]="engine is not running",[0x85]="engine run time too low",
                [0x86]="temperature too high",[0x87]="temperature too low",[0x88]="vehicle speed too high",
                [0x89]="vehicle speed too low",[0x8A]="throttle pedal too high",[0x8B]="throttle pedal too low",
                [0x8C]="transmission range not in neutral",[0x8D]="transmission range not in gear",[0x8F]="brake switch not closed",
                [0x90]="shifter lever not in park",[0x91]="torque converter clutch locked",[0x92]="voltage too high",
                [0x93]="voltage too low",[0x00]="positive response",[0x11]="service not supported",
                [0x12]="sub function not supported",[0x13]="incorrect message length or invalid format",[0x78]="response pending",
                [0x7F]="service not supported in active session"}
                
-- ===================== [ DATA     ] ================================
dcm = M 

-- ===================== [ FUNCTION ] ================================
function M.init(channel,bus,rxid,txid)
  cantp.init(channel,bus,rxid,txid)
end

function get_service_name(serviceid)
    service = l_service[serviceid]
    if nil == service then
      service = string.format("unknown(%X)",serviceid)
    end
    
    return service
end

function get_nrc_name(nrc)
    name = l_nrc[nrc]
    if nil == name then
      name = string.format("unknown(%X)",nrc)
    end
  
  return name
end

local function show_negative_response(res)
  if (res[1] == 0x7f) and (rawlen(res) == 3) then
    service = get_service_name(res[2])
    nrc = get_nrc_name(res[3])
    print(string.format("  >> service '%s' negative response '%s' ",service,nrc))
  else
    print("unknown response")
  end
  
end

local function show_request(req)
  ss = string.format("  >> dcm request %s = [",get_service_name(req[1]))
  len = rawlen(req)
  if len > 16 then
    len = 16
  end
  for i=1,len,1 do
    ss = string.format("%s%02X,",ss,req[i])
  end
  ss = string.format("%s],",ss)
  print(ss)
end

local function show_response(res)
  ss = "  >> dcm response = ["
  len = rawlen(res)
  if len > 16 then
    len = 16
  end
  for i=1,len,1 do
    ss = string.format("%s%02X,",ss,res[i])
  end
  ss = string.format("%s],",ss)
  print(ss)
end

function M.transmit(channel,req)
  ercd = true
  response  = nil
  show_request(req)
  cantp.transmit(channel,req)
  while ercd == true do
    ercd,res = cantp.receive(channel)
    if ercd == true then
      show_response(res)
      if (req[1]|0x40 == res[1]) then
        -- positive response
        response  = res
        break
      elseif (rawlen(res) == 3) and (res[1] == 0x7f) and (res[2] == req[1]) and (res[3] == 0x78) then
        -- response is pending as server is busy
        -- continue
      else
        show_negative_response(res)
        ercd = false 
      end
    else
      ercd = false
    end
  end

  return ercd,response
end
-- ===================== [ INSTANCE ] ================================
return dcm