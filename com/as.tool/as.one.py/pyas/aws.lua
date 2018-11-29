-- /**
-- * AS - the open source Automotive Software on https://github.com/parai
-- *
-- * Copyright (C) 2017  AS <parai@foxmail.com>
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
require("as")
require("as")
json = require("json")
-- ===================== [ MACRO    ] ================================

-- ===================== [ LOCAL    ] ================================
local M = {}
local index = 0
-- ===================== [ DATA     ] ================================
aws = M
-- ===================== [ FUNCTION ] ================================
function M.server(uri,port)
  local s = as.open(string.format("websock%d",index),string.format("%s\0%d\0%d",uri,port,1))
  index = index + 1  
  return s
end

-- return the handle of the server accept clients
function M.srvlst(s)
  local ps = nil
  local rv,data = as.ioctl(s,0,"nil",-1);
  if rv > 0 then
    ps = json.decode(data)
  end
  return ps
end

function M.client(uri,port)
  local s = as.open(string.format("websock%d",index),string.format("%s\0%d\0%d",uri,port,0))
  index = index + 1
  return s
end

function M.call(s,api,verb,obj)
   local ds = string.format("c%s\0%s\0%s",api,verb,json.encode(obj))
  return as.write(s,ds,-1)
end

function M.pend_msg(s)
  while true do
    local len,data = as.read(s)
    if len > 0 then
      msg=json.decode(data)
      break
    end
	os.usleep(1000)
  end
  return msg
end

function M.reply_okay(s,msg,robj)
  local ds = string.format("r%s\0%s\0%s\0%s","okay",json.encode(robj),msg.param,msg.msg)
  as.write(s,ds,-1)
end

function M.reply_fail(s,msg,robj)
  local ds = string.format("r%s\0%s\0%s\0%s","fail",json.encode(robj),msg.param,msg.msg)
  as.write(s,ds,-1)
end

return aws
