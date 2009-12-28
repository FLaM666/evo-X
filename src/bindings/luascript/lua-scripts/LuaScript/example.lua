--This is simple script file that contains example script
--Note , If you dont need some function you can remove them, probably if you make script for NPC you wont need Go funcs ... etc
--by Derex

--                  How to Script:
----------------------------------------------------
--1.Make new file and copy the conents of this file
--2.Change scriptname according to how your scrip will be named
--3.Do some coding :)  , you need to find documentation on what functions you can use
--4.Open MasterScript.lua and add your file at the end with fallowing command :
--                 include ('LuaScript/example.lua')
--5.Then you can execute some SQL`s and add to some npc`s/mobs your scriptname 
--6.UPDATE `creature_template` SET `ScriptName` = 'example' WHERE `entry` = 1423;

scriptname = "example"

m_scripts[scriptname] = {}


m_scripts[scriptname]["GossipHello"] = function(player,_Creature)

return RETURN_NOK
end

m_scripts[scriptname]["GossipSelect"] = function(player, _Creature, sender, action)

return RETURN_NOK
end

m_scripts[scriptname]["GossipSelectWithCode"] = function(player, _Creature, sender, action, sCode)

return RETURN_NOK
end

m_scripts[scriptname]["QuestAccept"] = function( player, _Creature, _Quest )

return RETURN_NOK
end

m_scripts[scriptname]["QuestSelect"] = function(player,_Creature,_Quest)

return RETURN_NOK
end

m_scripts[scriptname]["ChooseReward"] = function(player, _Creature, _Quest, opt)

return RETURN_NOK
end

m_scripts[scriptname]["NPCDialogStatus"] = function(player,_Creature)

return(100)
end

m_scripts[scriptname]["ItemHello"] = function(player, _Item, _Quest)

return RETURN_NOK
end

m_scripts[scriptname]["ItemQuestAccept"] = function(player, _Item, _Quest)

return RETURN_NOK
end

m_scripts[scriptname]["GOHello"] = function(player,_GO )

return RETURN_NOK
end

m_scripts[scriptname]["GOQuestAccept"] = function(player, _GO, _Quest )

return RETURN_NOK
end

m_scripts[scriptname]["GOChooseReward"] = function(player, _GO, _Quest, opt)

return RETURN_NOK
end
