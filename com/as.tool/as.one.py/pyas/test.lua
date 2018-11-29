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
require("cantp")
require("as")
require("s19")
require("os")
require("aws")
json = require("json")

local function hext(data) -- this is for table
  ss = "["
  len = rawlen(data)
  for i=1,len,1 do
    ss = string.format("%s%02X,",ss,data[i])
  end
  ss = string.format("%s],",ss)
  return ss
end

local function hexs(data) -- this is for string
  ss = "["
  len = rawlen(data)
  for i=1,len,1 do
    ss = string.format("%s%02X,",ss,string.byte(data,i))
  end
  ss = string.format("%s],",ss)
  return ss
end

function test_can_peak()
  data = {}
  as.can_open(0,"peak",0,1000000)
  cantp.init(0,0,0x732,0x731)
  for i=1,256,1 do
    data[i] = i;
  end
  cantp.transmit(0,data)
  response = cantp.receive(0)
end

function test_s19()
  srecord = s19.open("D:/repository/as/release/ascore/out/stm32f107vc.s19")
  secnbr = rawlen(srecord)
  for i=1,secnbr,1 do
    ss = srecord[i]
    print(string.format("addr=%X,size=%X,data=%s",ss['addr'],ss['size'],hexs(ss['data'])))
  end
end

function test_can_serail()
  data = {}
  as.can_open(0,"serial",3,115200)
  while true do
	as.can_read(0,0x732)
  end
end

function test_can_tcp()
  data = {}
  as.can_open(0,"serial",0x746370,115200)
  while true do
	ercd,canid,data = as.can_read(0,-1)
	if ercd == true then
	  print(string.format("canid=%03X, data=[%02X,%02X,%02X,%02X,%02X,%02X,%02X,%02X]",canid,
		data[1],data[2],data[3],data[4],data[5],data[6],data[7],data[8]))
      as.can_write(0,canid,data)
	end
  end
end

function test_can_vcan()
  data = {}
  as.can_open(0,"socket",32,115200)
  while true do
	ercd,canid,data = as.can_read(0,-1)
	if ercd == true then
	  print(string.format("canid=%03X, data=[%02X,%02X,%02X,%02X,%02X,%02X,%02X,%02X]",canid,
		data[1],data[2],data[3],data[4],data[5],data[6],data[7],data[8]))
	end
  end
end

function test_can_amb()
  data = {}
  as.can_open(0,"socket",0,1000000)
  while true do
	ercd = as.can_write(0,0x100,{0x00,0x01,0x00,0x02,0x00,0x03,0x00,0x04})
  os.usleep(100)
  end
end

function test_asdev()

  as.ioctl(12,7,{1,2,3},3)
  as.ioctl(12,6,"Hello World",3)
  as.write(12,"Hello World",3)
  as.write(12,{1,2,3},3)
  fd = as.open("COM14",string.format("%d\0%s",115200,"8N1"))
  len,data = as.read(fd)
  if len > 0 then
    print("rx string is: ",rawlen(data),data)
    print("rx raw data is: ",hexs(data))
  end
end

function test_ascomtcp()
  fd = as.open("COMTCP",string.format("%d\0%s",115200,"8N1"))
  ss = ""
  while true do
    len,data = as.read(fd)
    if len > 0 then
      for i=1,len,1 do
		-- is '\n' or '\r' end of string:
        if string.byte(data,i) == 10 or string.byte(data,i) == 13 then
		  print(ss)
		  -- as.write(fd,"SCAN000401080104000000000000\n",-1);
		  ss = ""
		else        
		  ss = string.format("%s%c",ss,string.byte(data,i))
      	end
      end
    end
    
  end
end

function test_aswebsock()
  port = 8080
  ss = as.open("websock01",string.format("%s\0%d\0%d","127.0.0.1",port,1))
  cs0 = as.open("websock02",string.format("%s\0%d\0%d","127.0.0.1",port,0))
  cs1 = as.open("websock03",string.format("%s\0%d\0%d","127.0.0.1",port,0))
  os.usleep(1000)
  rv,data = as.ioctl(ss,0,"nil",-1);
  print("accept param:",data)
  ps = json.decode(data)
  print(ps.params[0],ps.params[1],ps.params[2])
  ds = string.format("c%s\0%s\0%s","hello","ping","null")
  as.write(cs0,ds,-1)
  while true do
    len,data = as.read(ss)
    if len > 0 then
      print("CALL",data)
      msg=json.decode(data)
      robj = { hi="this is an example" }
      ds = string.format("r%s\0%s\0%s\0%s","okay",json.encode(robj),msg.param,msg.msg)
      as.write(ss,ds,-1)
      break
    end
  end
  
  
  ds = string.format("c%s\0%s\0%s","gui","refresh","null")
  as.write(cs1,ds,-1)
  while true do
    len,data = as.read(ss)
    if len > 0 then
      print("CALL",data)
      msg=json.decode(data)
      robj = { hi="this is an example2" }
      ds = string.format("r%s\0%s\0%s\0%s","okay",json.encode(robj),msg.param,msg.msg)
      as.write(ss,ds,-1)
      break
    end
  end
  os.usleep(1000000)
end

function test_aws_pkg()
  port = 8080
  s = aws.server("127.0.0.1",port)
  c = aws.client("127.0.0.1",port)
  obj = { hi="this is an example call" }  
  aws.call(c,"hello","ping",obj)
  msg = aws.pend_msg(s)
  print(json.encode(msg))
  obj = { hi="this is an example reply" }  
  aws.reply_okay(s,msg,obj)
  msg = aws.pend_msg(c)
  print(json.encode(msg))
  lst = aws.srvlst(s)
  print(json.encode(lst))
end

test_aws_pkg()

print("Test END")
