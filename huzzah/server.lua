local defaultSpeed = 9600
local programSpeed = 57600
--local programSpeed = 115200
local rstPin = 4 -- GPIO 2
local counter = 0
gpio.mode(rstPin, gpio.OUTPUT)
gpio.write(rstPin, gpio.HIGH)
uart.setup(0, defaultSpeed, 8, 0, 1, 1)

function connect (conn, data)
    
    conn:on ("receive", function (conn, data)
        if (string.sub(data, 1, 3) == "GET") then
            handle_http(conn, data)
            return
        end
        if (data == "q\r\n") then
            conn:close()
            return
        end
        if (counter == 0) then
            uart.setup(0, programSpeed, 8, 0, 1, 0)
            gpio.write(rstPin, gpio.LOW)
        end
        if (counter == 1) then
            gpio.write(rstPin, gpio.HIGH)
        end
        uart.write(0, data)
        counter = counter+1
    end)
     
	uart.on("data", 0, function(data)
	    conn:send(data)
	end, 0)
	
	conn:on("disconnection",function(c) 
	    uart.on("data")
	    uart.setup(0, defaultSpeed, 8, 0, 1, 1)
	    counter = 0
	end)
end

function handle_http(cn, req_data)
    local id = 0
    local address = 0x30

	params = get_http_req (req_data)
	cn:send("HTTP/1.1 200/OK\r\nServer: NodeLuau\r\nContent-Type: text/html\r\n\r\n")
	cn:send ("<h1>ESP8266 Command Server</h1>\r\n")
	if (params["command"] ~= nil) then
		cn:send("</br>Received command = " .. params["command"])
		print ("Command received: " .. params["command"])
		i2c.start(id)
		i2c.address(id, address, i2c.TRANSMITTER)
		i2c.write(id, params["command"])
		i2c.stop(id)
        uart.write(0, params["command"])
	end

	-- Close the connection for the request
	cn:close ( )
end

-- Build and return a table of the http request data
function get_http_req (instr)
	local t = {}
	local str = string.sub(instr, 0, 200)
	local v = string.gsub(split(str, ' ')[2], '+', ' ')
	parts = split(v, '?')
	local params = {}
	if (table.maxn(parts) > 1) then
		for idx,part in ipairs(split(parts[2], '&'))  do
			parmPart = split(part, '=')
			params[parmPart[1]] = parmPart[2]
		end
	end
	return params
end

-- Source: http://lua-users.org/wiki/MakingLuaLikePhp
-- Credit: http://richard.warburton.it/
function split(str, splitOn)
    if (splitOn=='') then return false end
    local pos,arr = 0,{}
    for st,sp in function() return string.find(str,splitOn,pos,true) end do
        table.insert(arr,string.sub(str,pos,st-1))
        pos = sp + 1
    end
    table.insert(arr,string.sub(str,pos))
    return arr
end

-- Hang out until we get a wifi connection before the httpd server is started.
--tmr.alarm (1, 800, 1, function ( )
--  if wifi.sta.getip ( ) == nil then
--     print ("Waiting for Wifi connection")
--  else
--     tmr.stop (1)
--     print ("Config done, IP is " .. wifi.sta.getip ( ))
--  end
--end)

if srv~=nil then
  srv:close()
end
srv = net.createServer (net.TCP)
-- Server listening on port 80, call connect function if a request is received
srv:listen (80, connect)
