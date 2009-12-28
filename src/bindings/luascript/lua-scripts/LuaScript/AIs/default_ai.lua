default_ai = { }

-- AI`s are in deep test ... i mean realy deep test
-- Things are getting little tought , better wait for manual before starting codding AI`s

--EVERY script should have the first 3 functions
--If you dont have them , then simply your script wont be loaded ;)
local LuaAI = _Creature:GetLuaAI() -- get AI class of creature , note not all creatures have such but only this with Lua AI`s
if isNULL(LuaAI) then return end -- DONT FORGET this please ,of you will get your problems :)

--Called on every new object initialization
default_ai["Init"] = function(LuaAI)
log("default_ai Init")
return true
end

-- Called when state is changed to that
default_ai["Enter"] = function(LuaAI)
log("default_ai Enter")

end

-- Called when this state is going to be changed to other
default_ai["Exit"] = function(LuaAI)
log("default_ai Exit")

end


--These down are callbacks from mangos ,you may skip some of them if you dont need them

-- Update function , called at each update cycle ,you can set the update interval using LuaAI:SetUpdateInterval(time) , time is in miliseconds ( 1000ms = 1sec )
--  if time is zero then Update wont be called at all , default is zero 
default_ai["Update"] = function(LuaAI)

end

--Called on destroying of the LuaAI class ( eg this is your destructor ) , It is opcional and can be scipped
--This is also called if you return false ,in Init Function , so be extremely carefull
default_ai["DeInit"] = function(LuaAI)
log("default_ai DeInit")
end

-- Called if IsVisible(Unit *who) is true at each *who move
-- This means that is somebody is visible around and this is called
default_ai["MoveInLineOfSight"] = function(LuaAI,unit)
log("default_ai MoveInLineOfSight")
end

-- Called at each attack of creature by any victim
default_ai["AttackStart"] = function(LuaAI,unit)
log("default_ai AttackStart")
end

-- Called at stoping attack by any attacker
default_ai["AttackStop"] = function(LuaAI,unit)
log("default_ai AttackStop")
end

-- Called at any Damage from any attacker
default_ai["DamageInflict"] = function(LuaAI,unit,amount_damage)
log("default_ai DamageInflict")
end

-- Is unit visibale for MoveInLineOfSight , have to return bool
default_ai["IsVisible"] = function(LuaAI,unit)
log("default_ai IsVisible")
return true
end

--Check condition for attack stop , have to return bool
default_ai["needToStop"] = function(LuaAI)
log("default_ai needToStop")

return true
end

-- Dont forget this , or the script wont be loaded
m_AI["default_ai"] = default_ai