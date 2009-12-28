scriptname = "guard_dunmorogh"
DisableCppScript( scriptname )

-- Taken from ScriptsDev, converted - Greatestevil

m_scripts[scriptname] = {}
m_scripts[scriptname]["GossipHello"] = function(player,_Creature)

-- TODO this is used by  guard_default_ai , if script is not part of it anymore pls remove this
guard_default_ai_Gossip_Hello(player,_Creature)

	player:ADD_GOSSIP_ITEM( 6, "Bank"					, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1)
	player:ADD_GOSSIP_ITEM( 2, "Gryphon Master"			, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2)
	player:ADD_GOSSIP_ITEM( 2, "Guild Master"			, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3)
	player:ADD_GOSSIP_ITEM( 1, "The Inn"					, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4)
	player:ADD_GOSSIP_ITEM( 5, "Stable Master"			, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5)
	player:ADD_GOSSIP_ITEM( 3, "Class Trainer"				, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6)
	player:ADD_GOSSIP_ITEM( 3, "Profession Trainer"		, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7)
	player:SEND_GOSSIP_MENU(2593,_Creature:GetGUID())

return RETURN_OK
end

function SendDefaultMenu_guard_dunmorogh(player, _Creature, action)
	if action == GOSSIP_ACTION_INFO_DEF + 1 then

		player:SEND_GOSSIP_MENU(4288,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 2 then

		player:SEND_GOSSIP_MENU(4289,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 3 then

		player:SEND_GOSSIP_MENU(4290,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 4 then

		player:SEND_POI(-5582.66, -525.89, 6, 6, 0, "Thunderbrew Distillery")
		player:SEND_GOSSIP_MENU(4291,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 5 then

		player:SEND_POI(-5604, -509.58, 6, 6, 0, "Shelby Stoneflint")
		player:SEND_GOSSIP_MENU(5985,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 6 then

		player:ADD_GOSSIP_ITEM( 3, "Hunter"				, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 1)
		player:ADD_GOSSIP_ITEM( 3, "Mage"				, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 2)
		player:ADD_GOSSIP_ITEM( 3, "Paladin"				, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 3)
		player:ADD_GOSSIP_ITEM( 3, "Priest"				, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 4)
		player:ADD_GOSSIP_ITEM( 3, "Rogue"				, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 5)
		player:ADD_GOSSIP_ITEM( 3, "Warlock"				, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 6)
		player:ADD_GOSSIP_ITEM( 3, "Warrior"				, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 7)
		player:SEND_GOSSIP_MENU(4292,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 7 then

		player:ADD_GOSSIP_ITEM( 3, "Alchemy"			, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 1)
		player:ADD_GOSSIP_ITEM( 3, "Blacksmithing"		, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 2)
		player:ADD_GOSSIP_ITEM( 3, "Cooking"				, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 3)
		player:ADD_GOSSIP_ITEM( 3, "Enchanting"			, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 4)
		player:ADD_GOSSIP_ITEM( 3, "Engineering"			, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 5)
		player:ADD_GOSSIP_ITEM( 3, "First Aid"				, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 6)
		player:ADD_GOSSIP_ITEM( 3, "Fishing"				, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 7)
		player:ADD_GOSSIP_ITEM( 3, "Herbalism"			, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 8)
		player:ADD_GOSSIP_ITEM( 3, "Leatherworking"		, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 9)
		player:ADD_GOSSIP_ITEM( 3, "Mining"				, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 10)
		player:ADD_GOSSIP_ITEM( 3, "Skinning"				, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 11)
		player:ADD_GOSSIP_ITEM( 3, "Tailoring"			, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 12)
		player:SEND_GOSSIP_MENU(4300,_Creature:GetGUID())
	end
end

function SendClassTrainerMenu_guard_dunmorogh(player, _Creature, action)
	if action == GOSSIP_ACTION_INFO_DEF + 1 then

		player:SEND_POI(-5618.29, -454.25, 6, 6, 0, "Grif Wildheart")
		player:SEND_GOSSIP_MENU(4293,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 2 then

		player:SEND_POI(-5585.6, -539.99, 6, 6, 0, "Magis Sparkmantle")
		player:SEND_GOSSIP_MENU(4294,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 3 then

		player:SEND_POI(-5585.6, -539.99, 6, 6, 0, "Azar Stronghammer")
		player:SEND_GOSSIP_MENU(4295,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 4 then

		player:SEND_POI(-5591.74, -525.61, 6, 6, 0, "Maxan Anvol")
		player:SEND_GOSSIP_MENU(4296,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 5 then

		player:SEND_POI(-5602.75, -542.4, 6, 6, 0, "Hogral Bakkan")
		player:SEND_GOSSIP_MENU(4297,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 6 then

		player:SEND_POI(-5641.97, -523.76, 6, 6, 0, "Gimrizz Shadowcog")
		player:SEND_GOSSIP_MENU(4298,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 7 then

		player:SEND_POI(-5604.79, -529.38, 6, 6, 0, "Granis Swiftaxe")
		player:SEND_GOSSIP_MENU(4299,_Creature:GetGUID())
	end
end

function SendProfTrainerMenu_guard_dunmorogh(player, _Creature, action)
	if action == GOSSIP_ACTION_INFO_DEF + 1 then

		player:SEND_GOSSIP_MENU(4301,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 2 then

		player:SEND_POI(-5584.72, -428.41, 6, 6, 0, "Tognus Flintfire")
		player:SEND_GOSSIP_MENU(4302,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 3 then
		
		player:SEND_POI(-5596.85, -541.43, 6, 6, 0, "Gremlock Pilsnor")
		player:SEND_GOSSIP_MENU(4303,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 4 then

		player:SEND_GOSSIP_MENU(4304,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 5 then

		player:SEND_POI(-5531, -666.53, 6, 6, 0, "Bronk Guzzlegear")
		player:SEND_GOSSIP_MENU(4305,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 6 then

		player:SEND_POI(-5603.67, -523.57, 6, 6, 0, "Thamner Pol")
		player:SEND_GOSSIP_MENU(4306,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 7 then

		player:SEND_POI(-5202.39, -51.36, 6, 6, 0, "Paxton Ganter")
		player:SEND_GOSSIP_MENU(4307,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 8 then

		player:SEND_GOSSIP_MENU(4308,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 9 then

		player:SEND_GOSSIP_MENU(4310,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 10 then

		player:SEND_POI(-5531, -666.53, 6, 6, 0, "Yarr Hamerstone")
		player:SEND_GOSSIP_MENU(4311,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 11 then

		player:SEND_GOSSIP_MENU(4312,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 12 then

		player:SEND_GOSSIP_MENU(4313,_Creature:GetGUID())
	end
end

m_scripts[scriptname]["GossipSelect"] = function(player, _Creature, sender, action)
	-- Serving guard_dunmorogh/main menu
	if sender == GOSSIP_SENDER_MAIN then
		SendDefaultMenu_guard_dunmorogh(player, _Creature, action)

	-- Came from the second menu already
	elseif sender == GOSSIP_SENDER_SEC_CLASSTRAIN then
		SendClassTrainerMenu_guard_dunmorogh(player, _Creature, action)

	elseif sender == GOSSIP_SENDER_SEC_PROFTRAIN then
		SendProfTrainerMenu_guard_dunmorogh(player, _Creature, action)
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
