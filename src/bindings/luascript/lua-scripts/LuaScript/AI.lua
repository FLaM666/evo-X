

-- luabind::adl::object GetAI(Creature* creature)
function GetAI(_Creature)
        current_scriptname = _Creature:GetScriptName()
        current_state = m_AI[current_scriptname]

        if current_state ~= nil then
                          return current_state
                   else
                          return m_AI["default_ai"]
        end   
       
return(nil) 
end

--int HasAI(Creature* creature)
function HasAI(_Creature)
        current_scriptname = _Creature:GetScriptName()
        current_state = m_AI[current_scriptname]

        if current_state ~= nil then
                          return 1
                   else
                          return 0
        end   
       
return 0
end