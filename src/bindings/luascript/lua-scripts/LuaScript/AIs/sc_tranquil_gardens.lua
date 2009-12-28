-----------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------
-- Tranquil Gardens Cemetery ( south of Darkshire-Duskwood )
-----------------------------------------------------------------------------------------------------------------
-- This is script in early development
-- And is for testing only

-- The idea is to split up the creatures in 2 groups casters and warriors 

-- Here is SQL
-- UPDATE `creature_template` SET`ScriptName` = 'tranquil_caster' WHERE `entry` = 203;
-- UPDATE `creature_template` SET`ScriptName` = 'tranquil_warrior' WHERE `entry` = 48;
-- UPDATE `creature_template` SET`ScriptName` = 'tranquil_cheff' WHERE `entry` = 511;

tranquil_warriors_group = { }

function register_tranquil_warrior(LuaAI)
tranquil_warriors_group[ LuaAI:GetCreature():GetGUIDLow() ] = LuaAI
end

function unregister_tranquil_warrior(LuaAI)
table.remove( tranquil_warriors_group , LuaAI:GetCreature():GetGUIDLow() )
end

tranquil_casters_group = { }

function register_tranquil_caster(LuaAI)
log("register_tranquil_caster")
tranquil_casters_group[ LuaAI:GetCreature():GetGUIDLow() ] = LuaAI
end

function unregister_tranquil_caster(LuaAI)
table.remove( tranquil_casters_group , LuaAI:GetCreature():GetGUIDLow() )
end

-----------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------
tranquil_warrior_ai = { }

tranquil_warrior_ai["Init"] = function(LuaAI)
-- TODO need to add check if the the unit is in tranquil gardens ,if no ,dont add him ,probbably assign other AI
-- register_tranquil_warrior(LuaAI)
-- LuaAI:SetUpdateInterval(2000)
log("tranquil_warrior Init")
return true
end

tranquil_warrior_ai["Enter"] = function(LuaAI)
register_tranquil_caster(LuaAI)
log("tranquil_warrior Enter")
end

tranquil_warrior_ai["Exit"] = function(LuaAI)
log("tranquil_warrior Exit")
unregister_tranquil_warrior(LuaAI)
end

tranquil_warrior_ai["Update"] = function(LuaAI)
log("tranquil_warrior Update %d" , LuaAI:GetCreature():GetGUIDLow() )
end

tranquil_warrior_ai["MoveInLineOfSight"] = function(LuaAI,unit)
log("tranquil_warrior MoveInLineOfSight")
end

tranquil_warrior_ai["DeInit"] = function(LuaAI,unit)
log("tranquil_warrior_ai DeInit")
unregister_tranquil_warrior(LuaAI)
end

m_AI["tranquil_warrior"] = tranquil_warrior_ai

-----------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------

tranquil_caster_ai = { }

tranquil_caster_ai["Init"] = function(LuaAI)
-- TODO need to add check if the the unit is in tranquil gardens ,if no ,dont add him ,probbably assign other AI
register_tranquil_caster(LuaAI)
log("tranquil_caster Init " )
return true
end

tranquil_caster_ai["Enter"] = function(LuaAI)
register_tranquil_caster(LuaAI)
log("tranquil_caster Enter")
end

tranquil_caster_ai["Exit"] = function(LuaAI)
log("tranquil_caster Exit")
unregister_tranquil_caster(LuaAI)
end

tranquil_caster_ai["Update"] = function(LuaAI)
end

tranquil_caster_ai["MoveInLineOfSight"] = function(LuaAI,unit)
log("tranquil_caster MoveInLineOfSight")
end

tranquil_caster_ai["DeInit"] = function(LuaAI,unit)
log("tranquil_caster DeInit")
unregister_tranquil_caster(LuaAI)
end

m_AI["tranquil_caster"] = tranquil_caster_ai

-----------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------
