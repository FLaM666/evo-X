--Here are the callbacks funcs ... this is actually what MaNGOSScript.dll exports , exported to lua

printf("Loading Callbacks by Derex...\n")

--return  -1 if func is not handled (false) (RETURN_NOK)
--               0 on success (true) (RETURN_OK)
--               everything else is also counted for true

--Yes , Here is big mess :)

--bool GossipHello ( Player * player, Creature *_Creature )
function GossipHello(player,_Creature)     
        current_scriptname = _Creature:GetScriptName()
        current_script = m_scripts[current_scriptname]

        if current_script ~= nil then
                   current_func = current_script["GossipHello"]
        
                   if current_func ~= nil then
                         return current_func(player,_Creature)
                   else
                          printf("Script : %s %s" , current_scriptname , " does not have a GossipHello function!\n" )
                   end
        else
                   printf("Script : %s %s", current_scriptname, " is not handled by LuaScript!\n")
        end
        return RETURN_NOK
end

-- bool GossipSelect( Player *player, Creature *_Creature,uint32 sender, uint32 action )
function GossipSelect( player, _Creature, sender, action )        
        current_scriptname = _Creature:GetScriptName()
        current_script = m_scripts[current_scriptname]

        if current_script ~= nil then
                   current_func = current_script["GossipSelect"]
        
                   if current_func ~= nil then
                         return current_func(player, _Creature, sender, action)
                   else
                          printf("LuaScript : %s %s" , current_scriptname , " does not have a GossipSelect function!\n" )
                   end
        else
                   printf("LuaScript : %s %s", current_scriptname, " is not handled by LuaScript!\n")
        end        
        return RETURN_NOK
end

-- bool GossipSelectWithCode( Player *player, Creature *_Creature, uint32 sender, uint32 action, char* sCode )
function GossipSelectWithCode( player, _Creature, sender, action, sCode )        
        current_scriptname = _Creature:GetScriptName()
        current_script = m_scripts[current_scriptname]

        if current_script ~= nil then
                   current_func = current_script["GossipSelectWithCode"]
        
                   if current_func ~= nil then
                         return current_func(player, _Creature, sender, action, sCode)
                   else
                          printf("Script : %s %s " , current_scriptname , " does not have a GossipSelectWithCode function!\n" )
                   end
        else
                   printf("Script : %s %s", current_scriptname, " is not handled by LuaScript!\n")
        end   
        return RETURN_NOK
end

-- bool QuestAccept( Player *player, Creature *_Creature, Quest *_Quest )
function QuestAccept( player, _Creature, _Quest )        
        current_scriptname = _Creature:GetScriptName()
        current_script = m_scripts[current_scriptname]

        if current_script ~= nil then
                   current_func = current_script["QuestAccept"]
        
                   if current_func ~= nil then
                         return current_func(player, _Creature, _Quest )
                   else
                          printf("Script : %s %s" , current_scriptname , " does not have a QuestAccept function!\n" )
                   end
        else
                   printf("Script : %s %s", current_scriptname, " is not handled by LuaScript!\n")
        end   
        return RETURN_NOK
end

-- bool QuestSelect( Player *player, Creature *_Creature, Quest *_Quest )
function QuestSelect( player,_Creature,_Quest )        
        current_scriptname = _Creature:GetScriptName()
        current_script = m_scripts[current_scriptname]

        if current_script ~= nil then
                   current_func = current_script["QuestSelect"]
        
                   if current_func ~= nil then
                         return current_func(player,_Creature,_Quest)
                   else
                          printf("Script : %s %s", current_scriptname, " does not have a QuestSelect function!\n" )
                   end
        else
                   printf("Script : %s %s", current_scriptname, " is not handled by LuaScript!\n")
        end   
        return RETURN_NOK
end

-- bool QuestComplete( Player *player, Creature *_Creature, Quest *_Quest )
function QuestComplete( player, _Creature, _Quest )        
        current_scriptname = _Creature:GetScriptName()
        current_script = m_scripts[current_scriptname]

        if current_script ~= nil then
                   current_func = current_script["QuestComplete"]
        
                   if current_func ~= nil then
                         return current_func( player, _Creature, _Quest)
                   else
                          printf("Script : %s %s" , current_scriptname, " does not have a QuestComplete function!\n" )
                   end
        else
                   printf("Script : %s %s", current_scriptname, " is not handled by LuaScript!\n")
        end   
        return RETURN_NOK
end

-- bool ChooseReward( Player *player, Creature *_Creature, Quest *_Quest, uint32 opt )
function ChooseReward( player, _Creature, _Quest, opt )        
        current_scriptname = _Creature:GetScriptName()
        current_script = m_scripts[current_scriptname]

        if current_script ~= nil then
                   current_func = current_script["ChooseReward"]
        
                   if current_func ~= nil then
                         return current_func(player,_Creature)
                   else
                          printf("Script : %s %s" ,current_scriptname, " does not have a ChooseReward function!\n" )
                   end
        else
                   printf("Script : %s %s", current_scriptname, " is not handled by LuaScript!\n")
        end   
        return RETURN_NOK
end

-- uint32 NPCDialogStatus( Player *player, Creature *_Creature )
function NPCDialogStatus( player, _Creature )        
        current_scriptname = _Creature:GetScriptName()
        current_script = m_scripts[current_scriptname]

        if current_script ~= nil then
                   current_func = current_script["NPCDialogStatus"]
        
                   if current_func ~= nil then
                         return current_func(player,_Creature)
                   else
                          printf("Script : %s %s" , current_scriptname , " does not have a NPCDialogStatus function!\n" )
                   end
        else
                   printf("Script : %s %s", current_scriptname, " is not handled by LuaScript!\n")
        end   
        return 100
end

-- bool ItemHello( Player *player, Item *_Item, Quest *_Quest )
function ItemHello( player, _Item, _Quest )        
        current_scriptname = _Creature:GetScriptName()
        current_script = m_scripts[current_scriptname]

        if current_script ~= nil then
                   current_func = current_script["ItemHello"]
        
                   if current_func ~= nil then
                         return current_func(player, _Item, _Quest)
                   else
                          printf("Script : %s %s" , current_scriptname, " does not have a ItemHello function!\n" )
                   end
        else
                   printf("Script : %s %s", current_scriptname, " is not handled by LuaScript!\n")
        end   
        return RETURN_NOK
end

-- bool ItemQuestAccept( Player *player, Item *_Item, Quest *_Quest )
function ItemQuestAccept( player, _Item, _Quest )        
        current_scriptname = _Creature:GetScriptName()
        current_script = m_scripts[current_scriptname]

        if current_script ~= nil then
                   current_func = current_script["ItemQuestAccept"]
        
                   if current_func ~= nil then
                         return current_func(player, _Item, _Quest)
                   else
                          printf("Script : %s %s" , current_scriptname, " does not have a ItemQuestAccept function!\n" )
                   end
        else
                   printf("Script : %s %s", current_scriptname, " is not handled by LuaScript!\n")
        end   
        return RETURN_NOK
end

-- bool GOHello( Player *player, GameObject *_GO )
function GOHello( player,_GO )        
        current_scriptname = _Creature:GetScriptName()
        current_script = m_scripts[current_scriptname]

        if current_script ~= nil then
                   current_func = current_script["GOHello"]
        
                   if current_func ~= nil then
                         return current_func(player,_GO)
                   else
                          printf("Script : %s %s" , current_scriptname, " does not have a GOHello function!\n" )
                   end
        else
                   printf("Script : %s %s", current_scriptname, " is not handled by LuaScript!\n")
        end   
        return RETURN_NOK
end

-- bool GOQuestAccept( Player *player, GameObject *_GO, Quest *_Quest )
function GOQuestAccept( player, _GO, _Quest )      
        current_scriptname = _Creature:GetScriptName()
        current_script = m_scripts[current_scriptname]

        if current_script ~= nil then
                   current_func = current_script["GOQuestAccept"]
        
                   if current_func ~= nil then
                         return current_func(player, _GO, _Quest)
                   else
                          printf("Script : %s %s" , current_scriptname, " does not have a GOQuestAccept function!\n" )
                   end
        else
                   printf("Script : %s %s", current_scriptname, " is not handled by LuaScript!\n")
        end   
        return RETURN_NOK
end

-- bool GOChooseReward( Player *player, GameObject *_GO, Quest *_Quest, uint32 opt )
function GOChooseReward( player, _GO, _Quest, opt )
        current_scriptname = _Creature:GetScriptName()
        current_script = m_scripts[current_scriptname]

        if current_script ~= nil then
                   current_func = current_script["GOChooseReward"]
        
                   if current_func ~= nil then
                         return current_func( player, _GO, _Quest, opt)
                   else
                          printf("Script : %s %s" , current_scriptname, " does not have GOChooseReward function!\n" )
                   end
        else
                   printf("Script : %s %s", current_scriptname, " is not handled by LuaScript!\n")
        end   
        return RETURN_NOK
end

-- bool AreaTrigger( Player *player, Quest *_Quest, uint32 triggerID )
function AreaTrigger( player, _Quest, triggerID )
        current_area_trigger = triggerID
        current_at_script = m_Area_triggers[current_area_trigger]

        if current_script ~= nil then
                         return current_script( player, _Quest )
                   else
                   printf("Areatrigger : %d %s", current_area_trigger, " is not handled by LuaScript!\n")
        end   
        return RETURN_NOK
end

-- void ScriptsFree()
function ScriptsFree()

end

printf("CallBacks loaded!\n")
