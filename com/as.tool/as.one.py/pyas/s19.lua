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

-- reference: https://en.wikipedia.org/wiki/S19
-- ===================== [ INCLUDE  ] ================================
require("io")
-- ===================== [ MACRO    ] ================================

-- ===================== [ LOCAL    ] ================================
local M = {}
local l_s19 = nil
local l_error = false
local l_lineno = nil
local l_file = nil
-- ===================== [ DATA     ] ================================
s19 = M
-- ===================== [ FUNCTION ] ================================
local function hexs(data)
  ss = "["
  len = rawlen(data)
  for i=1,len,1 do
    ss = string.format("%s%02X,",ss,data[i])
  end
  ss = string.format("%s],",ss)
  return ss
end
local function b2h(b)
  v = 0
  if(string.byte(b)>=string.byte("0") and string.byte(b)<=string.byte("9")) then
    v = string.byte(b) - string.byte("0")
  elseif(string.byte(b)>=string.byte("a") and string.byte(b)<=string.byte("f")) then
    v = string.byte(b) - string.byte("a") + 10
  elseif(string.byte(b)>=string.byte("A") and string.byte(b)<=string.byte("F")) then
    v = string.byte(b) - string.byte("A") + 10
  else
    print(string.format("%s::encounter invalid character @ line %d "%s"",l_file,l_lineno,b))
    l_error = true
  end
  
  return v
end

local function s19byte(line,pos)
  b = (b2h(string.sub(line,pos,pos))<<4) + (b2h(string.sub(line,pos+1,pos+1)))
  return b
end

local function s19word(line,pos)
  b0 = (b2h(string.sub(line,pos,pos))<<4) + (b2h(string.sub(line,pos+1,pos+1)))
  b1 = (b2h(string.sub(line,pos+2,pos+2))<<4) + (b2h(string.sub(line,pos+3,pos+3)))
  
  return (b0<<8)+b1
end

local function s19long(line,pos)
  b0 = (b2h(string.sub(line,pos,pos))<<4) + (b2h(string.sub(line,pos+1,pos+1)))
  b1 = (b2h(string.sub(line,pos+2,pos+2))<<4) + (b2h(string.sub(line,pos+3,pos+3)))
  b2 = (b2h(string.sub(line,pos+4,pos+4))<<4) + (b2h(string.sub(line,pos+5,pos+5)))
  b3 = (b2h(string.sub(line,pos+6,pos+6))<<4) + (b2h(string.sub(line,pos+7,pos+7)))
  return (b0<<24)+(b1<<16)+(b2<<8)+b3
end
local function s19s0(line)
  l_s19 = {}  -- initialize section codes
end

function M.new()
	return {}
end

function M.append(record,address,data)
  sz = rawlen(record)
  bytes = rawlen(data)
  if sz > 0 then
    ss = record[sz]
  else
    sz = 1
    record[sz] = {}
    ss = record[sz]
    ss["addr"] = address
    ss["size"] = 0
    ss["data"] = {}
  end

  if address == ss["addr"]+ss["size"] then
    -- same section
  else
    -- new section
    sz = sz + 1
    record[sz] = {}
    ss = record[sz]
    ss["addr"] = address
    ss["size"] = 0
    ss["data"] = {}
  end

  dl = rawlen(ss["data"])
  for i=1,bytes,1 do
    ss["data"][dl+i] = data[i]
  end
  ss["size"] = ss["size"] + bytes
end

local function s19s3(line)
  
  bytes  = s19byte(line,3) - 5
  address= s19long(line,5)  
  data = {}
  for i=1,bytes,1 do
    data[i] = s19byte(line,11+2*i)
  end
  ck = s19byte(line,13+2*bytes)
  checksum = bytes+5
  checksum = checksum + ((address>>24)&0xFF) + ((address>>16)&0xFF) + ((address>>8)&0xFF) +((address>>0)&0xFF)
  for i=1,bytes,1 do
    checksum = checksum + data[i]
  end
  if( (checksum&0xFF)+ck == 0xFF ) then
    -- checksum is OK
  else
    print(string.format("%s::checksum error @ line %d %s",l_file,l_lineno,line))
    l_error = true
    return
  end
  M.append(l_s19,address,data)
end

function M.dump(srecord,f)
  fp = io.open(f,"w")
  sz = rawlen(srecord)
  for i=1,sz,1 do
	  ss = srecord[i]
	  address = ss["addr"]
    size = ss["size"]
	  data = ss["data"]
    cstr = ""
    last_j = 0
    checksum = 0
	  for j=1,size,1 do
	    checksum = checksum + data[j]
	    cstr = string.format("%s%02X",cstr,data[j])
	    if( ((j%32) == 0) or (j == size)) then
		    sz = j - last_j
        addr = address + last_j
        checksum = checksum + sz + 5
        checksum = checksum + ((addr>>24)&0xFF) + ((addr>>16)&0xFF) + ((addr>>8)&0xFF) +((addr>>0)&0xFF)
        fp:write(string.format("S3%02X%08X%s%02X\n",sz+5,addr,cstr,0xFF-(checksum&0xFF)))
        last_j = j
        cstr = ""
        checksum = 0
	    end
	  end
  end
  io.close(fp)
end

function M.open(f)
  l_s19 = nil
  l_lineno = 0
  l_error = false
  l_file = f
  for line in io.lines(f) do
    if 0 == l_lineno then
      if( string.sub(line,1,2) == "S0") then
        s19s0(line)
      else
        print(string.format("%s::invalid s19 record @ line %d %s",l_file,l_lineno,line))
        l_error = true
      end
    else
      if( string.sub(line,1,2) == "S3") then
        s19s3(line)
      end
    end
    if(l_error==true) then
      break
    end
    l_lineno = l_lineno + 1
  end
  if(l_error==true) then
    l_s19 = nil
  end
  return l_s19
end

-- ===================== [ INSTANCE ] ================================
return s19
