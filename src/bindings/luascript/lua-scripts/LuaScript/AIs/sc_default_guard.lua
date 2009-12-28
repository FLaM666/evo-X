guard_default_ai = { }

-- distances are in square
guard_default_ai_talk_distance_sq = 5

function guard_default_ai_Gossip_Hello(player,_Creature)


local LuaAI = _Creature:GetLuaAI() -- get AI class of creature , note not all creatures have such but only this with Lua AI`s
if LuaAI == nil then return end
if isNULL(LuaAI) then return end -- DONT FORGET this please ,of you will get your problems :)

local data = LuaAI:Data()

if data["Talk"][player:GetGUIDLow()] == 2 then

local randn = rand_range(1,100)
if randn < 33 then
LuaAI:DoSay("Welcome back",0)
elseif randn > 33 and randn < 66 then
LuaAI:DoSay("I am glad to see you again",0)
else 
LuaAI:DoSay("Hello again",0)
end

end

data["Talk"][player:GetGUIDLow()] = 1

LuaAI:SetData(data)

end

-- this will check if player in going away from Guard and will tell goodbye to the player :)
guard_default_ai_CheckTalk = function(LuaAI,unit)
local data = LuaAI:Data()

if  data["Talk"][ unit:GetGUIDLow() ] == nil then return end

    if LuaAI:GetCreature():GetDistanceSq(unit) > guard_default_ai_talk_distance_sq then
    
            if  data["Talk"][ unit:GetGUIDLow() ] == 1 then
			
			LuaAI:GetCreature():LookAt(unit)
			
			num = rand_range(1,100)
				if num < 20 then
				LuaAI:DoSay("See ya next time !",0)
				elseif num >= 20 and num < 50 then
				LuaAI:DoSay("Good Bye Stranger !",0)
				elseif num >= 50 and num < 70 then
				LuaAI:DoSay("Good luck , hope to see you soon !",0)
				else
				LuaAI:DoSay("Bye Bye !",0)
				end

			LuaAI:GetCreature():HandleEmoteCommand(EMOTE_ONESHOT_WAVE)
			data["Talk"][ unit:GetGUIDLow() ] = 2
			LuaAI:SetData(data)
			end

	end

end


guard_default_ai["Init"] = function(LuaAI)
-- log("guard_default_ai Init")
-- LuaAI:SetUpdateInterval(10000)
local data = LuaAI:Data()
data = { }
data["Talk"] = { }

LuaAI:SetData(data)

return true
end

-- Called when state is changed to that
guard_default_ai["Enter"] = function(LuaAI)
-- log("guard_default_ai Enter")

end

-- Called when this state is going to be changed to other
guard_default_ai["Exit"] = function(LuaAI)
-- log("guard_default_ai Exit")
end

guard_default_ai["Update"] = function(LuaAI)
end

guard_default_ai["DeInit"] = function(LuaAI)
-- log("guard_default_ai DeInit")
end

guard_default_ai["MoveInLineOfSight"] = function(LuaAI,unit)
-- log("guard_default_ai MoveInLineOfSight distance : %d" , LuaAI:GetCreature():GetDistanceSq(unit))
guard_default_ai_CheckTalk(LuaAI,unit)
LuaAI:MoveInLineOfSight_agr(unit)
end

-- Called at each attack of creature by any victim
guard_default_ai["AttackStart"] = function(LuaAI,unit)
log("guard_default_ai AttackStart")
-- 10151 fireball 11
-- 10161 ConeOfCold

--TODO Seeems that dont work for now ... dont have time to test
local spellid = 10151 -- fireball is default
local randn = rand_range(1,100)

if randn > 70 then  spellid = 10161
end

LuaAI:GetCreature():StopMoving()
LuaAI:DoCast(unit,spellid)
LuaAI:DoStartAttack(unit)
end

-- Called at stoping attack by any attacker
guard_default_ai["AttackStop"] = function(LuaAI,unit)
-- log("guard_default_ai AttackStop")
-- TODO  Iam not sure that this is correct
LuaAI:DoStopAttack()
end

-- Called at any Damage from any attacker
guard_default_ai["DamageInflict"] = function(LuaAI,unit,amount_damage)
log("guard_default_ai DamageInflict")
end

-- Is unit visibale for MoveInLineOfSight , have to return bool
guard_default_ai["IsVisible"] = function(LuaAI,unit)
-- log("guard_default_ai IsVisible")
return LuaAI:IsVisible_agr(unit)
end

--Check condition for attack stop , have to return bool
guard_default_ai["needToStop"] = function(LuaAI)
--log("guard_default_ai needToStop")

return LuaAI:needToStop_agr()
end

-- Dont forget this , or the script wont be loaded
-- hiho , we can use same ai for more than one scriptname :) 
m_AI["guard_stormwind"] = guard_default_ai
m_AI["guard_ironforge"] = guard_default_ai
m_AI["guard_mulgore"] = guard_default_ai
m_AI["guard_teldrassil"] = guard_default_ai
m_AI["guard_tirisfal"] = guard_default_ai
m_AI["guard_orgrimmar"] = guard_default_ai
m_AI["guard_undercity"] = guard_default_ai
m_AI["guard_bluffwatcher"] = guard_default_ai
m_AI["guard_darnassus"] = guard_default_ai
m_AI["guard_dunmorogh"] = guard_default_ai
m_AI["guard_durotar"] = guard_default_ai
m_AI["guard_elwynnforest"] = guard_default_ai

