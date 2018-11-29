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
-- ===================== [ INCLUDE  ] ================================
require("dcm")
require("as")
require("s19")
require("math")
require("os")
-- ===================== [ MACRO    ] ================================

-- ===================== [ LOCAL    ] ================================
local can_bus = 0
local dcm_chl = 0

local FLASH_WRITE_SIZE = 512
local FLASH_READ_SIZE  = 512

local l_flsdrv = nil
local l_app = nil
local l_flsdrv_s = nil
local l_app_s = nil
-- ===================== [ DATA     ] ================================
-- ===================== [ FUNCTION ] ================================
function is_all_zero(data,size)
  bAllZero = true
  for i=1,size,1 do
    if data[i] ~= 0 then
      bAllZero = false
      break
    end
  end
  return bAllZero
end

function enter_extend_session()
  ercd,res = dcm.transmit(dcm_chl,{0x10,0x03})
  
  if (false == ercd) then
    print("  >> enter extend session failed!")
  else
    print("  >> enter extend session ok!")
  end
  
  return ercd
  
end

function enter_program_session()
  ercd,res = dcm.transmit(dcm_chl,{0x10,0x02})
  
  if (false == ercd) then
    print("  >> enter program session failed!")
  else
    print("  >> enter program session ok!")
  end
  
  return ercd
  
end

function security_extds_access()
  -- level 1 
  ercd,res = dcm.transmit(dcm_chl,{0x27,0x01})
  
  if (false == ercd) then
    print("  >> security access request seed failed!")
  else
    print("  >> security access request seed ok!")
    seed = (res[3]<<24) + (res[4]<<16) + (res[5]<<8) +(res[6]<<0)
    key = seed ~ 0x78934673

    ercd,res = dcm.transmit(dcm_chl,{0x27,0x02,(key>>24)&0xFF,(key>>16)&0xFF,(key>>8)&0xFF,(key>>0)&0xFF})
    if (false == ercd) then
      print("  >> security access send key failed!")
    else
      print("  >> security access send key ok!")
    end
  end
  
  return ercd
  
end

function security_prgs_access()
  -- level 2
  ercd,res = dcm.transmit(dcm_chl,{0x27,0x03})
  
  if (false == ercd) then
    print("  >> security access request seed failed!")
  else
    print("  >> security access request seed ok!")
    seed = (res[3]<<24) + (res[4]<<16) + (res[5]<<8) +(res[6]<<0)
    key = seed ~ 0x94586792
    ercd,res = dcm.transmit(dcm_chl,{0x27,0x04,(key>>24)&0xFF,(key>>16)&0xFF,(key>>8)&0xFF,(key>>0)&0xFF})
    if (false == ercd) then
      print("  >> security access send key failed!")
    else
      print("  >> security access send key ok!")
    end
  end
  
  return ercd
  
end


function routine_erase_flash()

  srecord = l_app_s
  
  if( nil == srecord ) then
    print("  >> invalid application srecord file!")
    return false
  end
  
  secnbr = rawlen(srecord)
  for i=1,secnbr,1 do
    ss = srecord[i]
    if false == is_all_zero(ss["data"],ss["size"]) then
      eaddr = ss["addr"]+ss["size"]
    end
  end

  addr =  srecord[1]["addr"]
  size = eaddr - addr;

  data = {}
  data[1] = 0x31
  data[2] = 0x01 -- routine start
  data[3] = 0xFF -- address and length format
  data[4] = 0x01 -- address and length format

  data[5] = (addr>>24)&0xFF
  data[6] = (addr>>16)&0xFF
  data[7] = (addr>>8)&0xFF
  data[8] = (addr>>0)&0xFF

  sz = math.floor((size+FLASH_READ_SIZE-1)/FLASH_READ_SIZE)*FLASH_READ_SIZE

  data[9]  = (sz>>24)&0xFF
  data[10] = (sz>>16)&0xFF
  data[11] = (sz>>8)&0xFF
  data[12] = (sz>>0)&0xFF
  data[13] = 0xFF -- memory identifier

  ercd,res = dcm.transmit(dcm_chl,data)

  if (false == ercd) then
    print("  >> routine erase flash failed!")
  else
    print("  >> routine erase flash ok!")
  end
  
  return ercd
  
end

function request_upload(addr,size,mem)
  data = {}
  data[1] = 0x35
  data[2] = 0x00 -- data format identifier
  data[3] = 0x44 -- address and length format
  data[4] = (addr>>24)&0xFF
  data[5] = (addr>>16)&0xFF
  data[6] = (addr>>8)&0xFF
  data[7] = (addr>>0)&0xFF

  sz = math.floor((size+FLASH_READ_SIZE-1)/FLASH_READ_SIZE)*FLASH_READ_SIZE

  data[8] = (sz>>24)&0xFF
  data[9] = (sz>>16)&0xFF
  data[10] = (sz>>8)&0xFF
  data[11] = (sz>>0)&0xFF
  data[12] = mem -- memory identifier
 
  ercd,res = dcm.transmit(dcm_chl,data)
  
  if (false == ercd) then
    print("  >> request upload failed!")
  else
    print("  >> request upload ok!")
  end
  
  return ercd
end

function request_transfer_exit()
  ercd,res = dcm.transmit(dcm_chl,{0x37})
  
  if (false == ercd) then
    print("  >> request_transfer_exit failed!")
  else
    print("  >> request_transfer_exit ok!")
  end
  
  return ercd
end

function request_download(addr,size,mem)
  data = {}
  data[1] = 0x34
  data[2] = 0x00 -- data format identifier
  data[3] = 0x44 -- address and length format
  data[4] = (addr>>24)&0xFF
  data[5] = (addr>>16)&0xFF
  data[6] = (addr>>8)&0xFF
  data[7] = (addr>>0)&0xFF

  sz = math.floor((size+FLASH_WRITE_SIZE-1)/FLASH_WRITE_SIZE)*FLASH_WRITE_SIZE

  data[8] = (sz>>24)&0xFF
  data[9] = (sz>>16)&0xFF
  data[10] = (sz>>8)&0xFF
  data[11] = (sz>>0)&0xFF
  data[12] = mem -- memory identifier
 
  ercd,res = dcm.transmit(dcm_chl,data)
  
  if (false == ercd) then
    print("  >> request download failed!")
  else
    print("  >> request download ok!")
  end
  
  return ercd
end

function request_transfer_exit()
  ercd,res = dcm.transmit(dcm_chl,{0x37})
  
  if (false == ercd) then
    print("  >> request_transfer_exit failed!")
  else
    print("  >> request_transfer_exit ok!")
  end
  
  return ercd
end

function download_one_record(addr,size,data,mem)
  ercd = request_download(addr,size,mem)
  
  -- download application
  blockSequenceCounter = 1
  left_size = size
  pos = 0

  ability = math.floor((4096-4)/FLASH_WRITE_SIZE) * FLASH_WRITE_SIZE

  while (left_size > 0) and (true== ercd) do
    req ={}
    req[1] = 0x36
    req[2] = blockSequenceCounter
    req[3] = 0
    req[4] = mem
    
    sz = ability
    if (left_size > ability) then      
      left_size = left_size - ability
    else
      sz = math.floor((left_size+FLASH_WRITE_SIZE-1)/FLASH_WRITE_SIZE)*FLASH_WRITE_SIZE
	  left_size = 0
    end

    --print(string.format("next pos=%X,sz=%X,ability=%X",pos,sz,ability))

    for i=1,sz,1 do
      if(pos+i <= size) then
        req[4+i] = data[pos+i]
      else
        req[4+i] = 0xFF
      end
    end

    ercd,res = dcm.transmit(dcm_chl,req)
    
    -- TODO: I don't know why sz becomes sz+4
    --if(sz > ability) then
    --  print("somehow bug here")
    --  sz = ability
    --end
    -- pos = pos + sz
    pos = pos + ability

    blockSequenceCounter = (blockSequenceCounter + 1)&0xFF
 
  end
  
  if (true == ercd) then
    ercd = request_transfer_exit()
  end
  
  return ercd
end

function upload_one_record(addr,size,mem)
  ercd = request_upload(addr,size,mem)
  record = {}
  
  -- request upload application
  blockSequenceCounter = 1
  left_size = size
  pos = 0
  ability = math.floor((4096-4)/FLASH_READ_SIZE) * FLASH_READ_SIZE

  while (left_size > 0) and (true== ercd) do
    req ={}
    req[1] = 0x36
    req[2] = blockSequenceCounter
    req[3] = 0
    req[4] = mem

    ercd,res = dcm.transmit(dcm_chl,req)
    
    sz = rawlen(res) - 2
    
    if (left_size > sz) then
      left_size = left_size - sz
    else
      sz = left_size
      left_size = 0
    end
    
    for i=1,sz,1 do
      record[pos+i] = res[2+i]
    end
    
    pos = pos + sz

    blockSequenceCounter = (blockSequenceCounter + 1)&0xFF
 
  end
  
  if (true == ercd) then
    ercd = request_transfer_exit()
  end
  
  return ercd,record
end

function download_flash_driver()
  srecord = l_flsdrv_s
  
  if( nil == srecord ) then
    print("  >> invalid flash driver srecord file!")
    return false
  end
  -- flash driver mapped to address 0
  secnbr = rawlen(srecord)
  for i=1,secnbr,1 do
    ss = srecord[i]
    addr =  ss["addr"]-srecord[1]["addr"]
    ercd =  download_one_record(addr,ss["size"],ss["data"],0xFD)
    if (false == ercd) then
      break
    end
  end
 
  if (false == ercd) then
    print("  >> download flash driver failed!")
  else
    print("  >> download flash driver ok!")
  end
  
  return ercd
end

function fl_compare(s1,s2)

  ercd = true
  length = rawlen(s1)
  for i=1,length,1 do
    if s1[i] ~= s2[i] then
      print(string.format("fl_compare: not equal @ %X %02X != %02X",i,s1[i],s2[i]))
      ercd = false
      break
    end
  end
  
  return ercd
end

function check_flash_driver()
  srecord = s19.open(l_flsdrv)
  
  if( nil == srecord ) then
    print("  >> invalid flash driver srecord file!")
    return false
  end
  -- flash driver mapped to address 0
  flsdrv = s19.new()
  secnbr = rawlen(srecord)
  for i=1,secnbr,1 do
    ss = srecord[i]
    addr =  ss["addr"]-srecord[1]["addr"]
    ercd,record =  upload_one_record(addr,ss["size"],0xFD)
    if (false == ercd) then
      break
    else
      s19.append(flsdrv,srecord[1]["addr"],record)
      ercd = fl_compare(srecord[i]["data"],record)
      if (false == ercd) then
        s19.dump(flsdrv,"flsdrv_dump.s19")
        break
      end
    end
  end
 
  s19.dump(flsdrv,"flsdrv_dump.s19")
  if (false == ercd) then
    print("  >> check flash driver failed!")
  else
    print("  >> check flash driver ok!")
  end
  
  return ercd
end

function download_application()

  srecord = l_app_s
  
  if( nil == srecord ) then
    print("  >> invalid application srecord file!")
    return false
  end
  
  secnbr = rawlen(srecord)
  for i=1,secnbr,1 do
    ss = srecord[i]
    addr =  ss["addr"]
    if false == is_all_zero(ss["data"],ss["size"]) then
    ercd =  download_one_record(addr,ss["size"],ss["data"],0xFF)
    if (false == ercd) then
      break
    end
    end
  end
 
  if (false == ercd) then
    print("  >> download application failed!")
  else
    print("  >> download application ok!")
  end
  
  return ercd
end

function check_application()
  srecord = l_app_s
  
  if( nil == srecord ) then
    print("  >> invalid application srecord file!")
    return false
  end
  app = s19.new()
  secnbr = rawlen(srecord)
  for i=1,secnbr,1 do
    ss = srecord[i]
    addr =  ss["addr"]
    if false == is_all_zero(ss["data"],ss["size"]) then
    ercd,record =  upload_one_record(addr,ss["size"],0xFF)
    if (false == ercd) then
      break
    else
      s19.append(app,srecord[i]["addr"],record)
      ercd = fl_compare(srecord[i]["data"],record)
      if (false == ercd) then
        s19.dump(app,"application_dump.s19")
        break
      end
    end
    end
  end
  s19.dump(app,"application_dump.s19")
  if (false == ercd) then
    print("  >> check application failed!")
  else
    print("  >> check application ok!")
  end
  
  return ercd
end

function routine_test_jump_to_application()
  ercd,res = dcm.transmit(dcm_chl,{0x31,0x01,0xFF,0x03})
  
  if (false == ercd) then
    print("  >> routine test jump to application failed!")
  else
    print("  >> routine test jump to application ok!")
  end
  os.usleep(5000000)
  return ercd
  
end

operation_list = {enter_extend_session, security_extds_access,
                  enter_program_session,security_prgs_access,
                  download_flash_driver, -- check_flash_driver,
                  routine_erase_flash, download_application, -- check_application,
				          routine_test_jump_to_application
}

function main(argc,argv)
  data = {}
  if argc == 0 then
  	 print("Usage: flashloader.lua flsdrv app device port baudrate")
	 return
  else
    l_flsdrv = argv[1]
    l_app = argv[2]
	device = argv[3] -- serial socket peak vxl tcp	
	port = argv[4]
	baudrate = argv[5]
	if device == "socket" then
      if os.name() == "posix" then
        os.execute("sudo modprobe vcan")
	    os.execute("sudo ip link add dev can0 type vcan")
	    os.execute("sudo ip link set up can0")
	  end
	end
	if device == "tcp" then
      device = "serial" -- special treatment for QEMU serial tcp:127.0.0.1:1103 
      port = 0x746370
      baudrate = 1000000
	end
	as.can_open(can_bus,device,port,baudrate)
  end
  os.execute("mkdir laslog")
  as.can_log("laslog/flash-loader.asc")
  dcm.init(dcm_chl,can_bus,0x732,0x731)
  
  os.usleep(1000000)
  
  l_flsdrv_s = s19.open(l_flsdrv)
  l_app_s = s19.open(l_app)

  for i=1,rawlen(operation_list),1 do
    ercd = operation_list[i]()
    if false == ercd then
      break
    end
  end
  as.can_log() -- no paramter close the file
  os.execute("pgrep .exe|xargs -i kill -9 {}")
  os.execute("cat laslog/flash-loader.asc")
end

main(rawlen(arg),arg)
