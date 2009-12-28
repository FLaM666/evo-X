scriptname = "guard_mulgore"
DisableCppScript( scriptname )

-- Taken from ScriptsDev, converted - Greatestevil

m_scripts[scriptname] = {}

m_scripts[scriptname]["GossipHello"] = function(player,_Creature)

-- TODO this is used by  guard_default_ai , if script is not part of it anymore pls remove this
guard_default_ai_Gossip_Hello(player,_Creature)

	player:ADD_GOSSIP_ITEM( 6, "Bank"						, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1)
	player:ADD_GOSSIP_ITEM( 2, "Wind Rider Master"			, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2)
	player:ADD_GOSSIP_ITEM( 1, "The Inn"						, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3)
	player:ADD_GOSSIP_ITEM( 5, "Stable Master"				, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4)
	player:ADD_GOSSIP_ITEM( 3, "Class Trainer"					, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5)
	player:ADD_GOSSIP_ITEM( 3, "Profession Trainer"			, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6)
	player:SEND_GOSSIP_MENU(3543,_Creature:GetGUID())

	return RETURN_OK
end

function SendDefaultMenu_guard_mulgore(player, _Creature, action)
	if action == GOSSIP_ACTION_INFO_DEF + 1 then

		player:SEND_GOSSIP_MENU(4051,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 2 then

		player:SEND_GOSSIP_MENU(4052,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 3 then

		player:SEND_POI(-2361.38, -349.19, 6, 6, 0, "Bloodhoof Village Inn")
		player:SEND_GOSSIP_MENU(4053,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 4 then

		player:SEND_POI(-2338.86, -357.56, 6, 6, 0, "Seikwa")
		player:SEND_GOSSIP_MENU(5976,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 5 then

		player:ADD_GOSSIP_ITEM( 3, "Druid"				, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 1)
		player:ADD_GOSSIP_ITEM( 3, "Hunter"				, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 2)
		player:ADD_GOSSIP_ITEM( 3, "Shaman"				, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 3)
		player:ADD_GOSSIP_ITEM( 3, "Warrior"				, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 4)
		player:SEND_GOSSIP_MENU(4069,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 6 then

		player:ADD_GOSSIP_ITEM( 3, "Alchemy"			, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 1)
		player:ADD_GOSSIP_ITEM( 3, "Blacksmithing"		, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 2)
		player:ADD_GOSSIP_ITEM( 3, "Cooking"				, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 3)
		player:ADD_GOSSIP_ITEM( 3, "Enchanting"			, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 4)
		player:ADD_GOSSIP_ITEM( 3, "First Aid"				, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 5)
		player:ADD_GOSSIP_ITEM( 3, "Fishing"				, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 6)
		player:ADD_GOSSIP_ITEM( 3, "Herbalism"			, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 7)
		player:ADD_GOSSIP_ITEM( 3, "Leatherworking"		, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 8)
		player:ADD_GOSSIP_ITEM( 3, "Mining"				, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 9)
		player:ADD_GOSSIP_ITEM( 3, "Skinning"				, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 10)
		player:ADD_GOSSIP_ITEM( 3, "Tailoring"			, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 11)
		player:SEND_GOSSIP_MENU(3541,_Creature:GetGUID())
	end
end

function SendClassTrainerMenu_guard_mulgore(player, _Creature, action)
	if action == GOSSIP_ACTION_INFO_DEF + 1 then

		player:SEND_POI(-2312.15, -443.69, 6, 6, 0, "Gennia Runetotem")
		player:SEND_GOSSIP_MENU(4054,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 2 then

		player:SEND_POI(-2178.14, -406.14, 6, 6, 0, "Yaw Sharpmane")
		player:SEND_GOSSIP_MENU(4055,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 3 then

		player:SEND_POI(-2301.5, -439.87, 6, 6, 0, "Narm Skychaser")
		player:SEND_GOSSIP_MENU(4056,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 4 then

		player:SEND_POI(-2345.43, -494.11, 6, 6, 0, "Krang Stonehoof")
		player:SEND_GOSSIP_MENU(4057,_Creature:GetGUID())
	end
end

function SendProfTrainerMenu_guard_mulgore(player, _Creature, action)
	if action == GOSSIP_ACTION_INFO_DEF + 1 then

		player:SEND_GOSSIP_MENU(4058,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 2 then

		player:SEND_GOSSIP_MENU(4059,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 3 then

		player:SEND_POI(-2263.34, -287.91, 6, 6, 0, "Pyall Silentstride")
		player:SEND_GOSSIP_MENU(4060,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 4 then

		player:SEND_GOSSIP_MENU(4061,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 5 then

		player:SEND_POI(-2353.52, -355.82, 6, 6, 0, "Vira Younghoof")
		player:SEND_GOSSIP_MENU(4062,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 6 then

		player:SEND_POI(-2349.21, -241.37, 6, 6, 0, "Uthan Stillwater")
		player:SEND_GOSSIP_MENU(4063,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 7 then

		player:SEND_GOSSIP_MENU(4064,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 8 then

		player:SEND_POI(-2257.12, -288.63, 6, 6, 0, "Chaw Stronghide")
		player:SEND_GOSSIP_MENU(4065,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 9 then

		player:SEND_GOSSIP_MENU(4066,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 10 then

		player:SEND_POI(-2252.94, -291.32, 6, 6, 0, "Yonn Deepcut")
		player:SEND_GOSSIP_MENU(4067,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 11 then

		player:SEND_GOSSIP_MENU(4068,_Creature:GetGUID())
	end
end

m_scripts[scriptname]["GossipSelect"] = function(player, _Creature, sender, action)
	-- Serving guard_mulgore/main menu
	if sender == GOSSIP_SENDER_MAIN then
		SendDefaultMenu_guard_mulgore(player, _Creature, action)

	-- Came from the second menu already
	elseif sender == GOSSIP_SENDER_SEC_CLASSTRAIN then
		SendClassTrainerMenu_guard_mulgore(player, _Creature, action)

	elseif sender == GOSSIP_SENDER_SEC_PROFTRAIN then
		SendProfTrainerMenu_guard_mulgore(player, _Creature, action)
	end
return RETURN_OK
end

m_scripts[scriptname]["GossipSelectWithCode"] = function(player, _Creature, sender, action, sCode)

return RETURN_NOK
end

m_scripts[scriptname]["QuestAccept"] = function( player, _Creature, _Quest )

return RETURN_NOK
end

m_scripts[scriptname]["QuestSelect"] = function(player, _Creature, _Quest)

return RETURN_NOK
end

m_scripts[scriptname]["QuestComplete"] = function(player, _Creature, _Quest)

return RETURN_NOK
end

m_scripts[scriptname]["ChooseReward"] = function(player, _Creature, _Quest, opt)

return RETURN_NOK
end

m_scripts[scriptname]["NPCDialogStatus"] = function(player, _Creature)

return(128)
end
