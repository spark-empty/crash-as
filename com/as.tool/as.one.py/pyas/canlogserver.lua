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

-- ===================== [ LOCAL    ] ================================
local can_bus = 0
-- ===================== [ DATA     ] ================================
-- ===================== [ FUNCTION ] ================================
local function logmsg(canid,data)
  ss = string.format("canid=%03X dlc=%s data=[",canid,rawlen(data))
  for i=1,rawlen(data),1 do
    ss = string.format("%s%02X,",ss,data[i])
  end
  ss = string.format("%s] @ %f s",ss,as.time())
  print(ss)
end

function main(argc,argv)
  data = {}
  if argc == 0 then
	print("Usage: canlogserver.lua socket")
	return
  else
	as.can_open(can_bus,"socket",0,1000000)
  end
  print(" >> canlog server on-line!")
  while true do   
    result,canid,data = as.can_read(can_bus,-1)
    -- if result and (canid&0x770)==0x550 then
    if result then
      logmsg(canid,data)
    else
      os.usleep(10) -- sleep a while 
    end
  end
end

main(rawlen(arg),arg)
