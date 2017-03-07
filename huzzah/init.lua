local id = 0
local sda = 1 -- GPIO 5
local scl = 2 -- GPIO 4
i2c.setup(id, sda, scl, i2c.SLOW)

local serialPin = 8
gpio.mode(serialPin, gpio.OUTPUT)
gpio.write(serialPin, gpio.LOW)
tmr.delay(3000000)
gpio.write(serialPin, gpio.HIGH)

local s,err
if file.open("server.lua") then
    s,err = pcall(function() dofile("server.lua") end)
end
if not s then print(err) end
