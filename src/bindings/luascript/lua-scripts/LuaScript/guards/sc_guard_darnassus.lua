scriptname = "guard_darnassus"
DisableCppScript( scriptname )

--Taken from ScriptsDev

m_scripts[scriptname] = {}
m_scripts[scriptname]["GossipHello"] = function(player,_Creature)

-- TODO this is used by  guard_default_ai , if script is not part of it anymore pls remove this
guard_default_ai_Gossip_Hello(player,_Creature)

	player:ADD_GOSSIP_ITEM( 1, "Auction House"			, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1)
	player:ADD_GOSSIP_ITEM( 6, "Bank"					, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2)
	player:ADD_GOSSIP_ITEM( 2, "Hippogryph Master"		, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3)
	player:ADD_GOSSIP_ITEM( 0, "Guild Master"			, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4)
	player:ADD_GOSSIP_ITEM( 1, "The Inn"					, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5)
	player:ADD_GOSSIP_ITEM( 4, "Mailbox"					, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6)
	player:ADD_GOSSIP_ITEM( 5, "Stable Master"			, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8)
	player:ADD_GOSSIP_ITEM( 0, "Weapon Master"			, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9)
	player:ADD_GOSSIP_ITEM( 8, "Battlemaster"			, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11)
	player:ADD_GOSSIP_ITEM( 3, "Class Trainer"				, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12)
	player:ADD_GOSSIP_ITEM( 3, "Profession Trainer"		, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 13)
	player:SEND_GOSSIP_MENU(3016,_Creature:GetGUID());

return RETURN_OK
end

--Some functions
function SendDefaultMenu_guard_darnassus(player, _Creature,  action)
	if action == GOSSIP_ACTION_INFO_DEF + 1 then

		player:SEND_POI(9861.23, 2334.55, 6, 6, 0, "Darnassus Auction House")
		player:SEND_GOSSIP_MENU(3833,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 2 then

		player:SEND_POI(9938.45, 2512.35, 6, 6, 0, "Darnassus Bank")
		player:SEND_GOSSIP_MENU(3017,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 3 then

		player:SEND_POI(9945.65, 2618.94, 6, 6, 0, "Rut'theran Village")
		player:SEND_GOSSIP_MENU(3018,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 4 then

		player:SEND_POI(10076.40, 2199.59, 6, 6, 0, "Darnassus Guild Master")
		player:SEND_GOSSIP_MENU(3019,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 5 then

		player:SEND_POI(10133.29, 2222.52, 6, 6, 0, "Darnassus Inn")
		player:SEND_GOSSIP_MENU(3020,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 6 then

		player:SEND_POI(9942.17, 2495.48, 6, 6, 0, "Darnassus Mailbox")
		player:SEND_GOSSIP_MENU(3021,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 7 then

		player:SEND_POI(10167.20, 2522.66, 6, 6, 0, "Alassin")
		player:SEND_GOSSIP_MENU(5980,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 8 then

		player:SEND_POI(9907.11, 2329.70, 6, 6, 0, "Ilyenia Moonfire")
		player:SEND_GOSSIP_MENU(4517,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 9 then

		player:ADD_GOSSIP_ITEM( 8, "Alterac Valley"		, GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 1);
		player:ADD_GOSSIP_ITEM( 8, "Arathi Basin"			, GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 2);
		player:ADD_GOSSIP_ITEM( 8, "Warsong Gulch"		, GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 3);
		player:SEND_GOSSIP_MENU(7519,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 10 then

		player:ADD_GOSSIP_ITEM( 3, "Druid"				, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 1)
		player:ADD_GOSSIP_ITEM( 3, "Hunter"				, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 2)
		player:ADD_GOSSIP_ITEM( 3, "Priest"				, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 3)
		player:ADD_GOSSIP_ITEM( 3, "Rogue"				, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 4)
		player:ADD_GOSSIP_ITEM( 3, "Warrior"				, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 5)
		player:SEND_GOSSIP_MENU(4264,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 11 then

		player:ADD_GOSSIP_ITEM( 3, "Alchemy"			, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 1)
		player:ADD_GOSSIP_ITEM( 3, "Cooking"				, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 2)
		player:ADD_GOSSIP_ITEM( 3, "Enchanting"			, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 3)
		player:ADD_GOSSIP_ITEM( 3, "First Aid"				, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 4)
		player:ADD_GOSSIP_ITEM( 3, "Fishing"				, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 5)
		player:ADD_GOSSIP_ITEM( 3, "Herbalism"			, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 6)
		player:ADD_GOSSIP_ITEM( 3, "Leatherworking"		, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 7)
		player:ADD_GOSSIP_ITEM( 3, "Skinning"				, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 8)
		player:ADD_GOSSIP_ITEM( 3, "Tailoring"			, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 9)
		player:SEND_GOSSIP_MENU(4273,_Creature:GetGUID())
	end
end

function SendBattleMasterMenu_guard_stormwind(player, _Creature, action)
	if action == GOSSIP_ACTION_INFO_DEF + 1 then

		player:SEND_POI(9923.61, 2327.43, 6, 6, 0, "Brogun Stoneshield")
		player:SEND_GOSSIP_MENU(7518,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 2 then

		player:SEND_POI(9977.37, 2324.39, 6, 6, 0, "Keras Wolfheart")
		player:SEND_GOSSIP_MENU(7651,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 3 then

		player:SEND_POI(9979.84, 2315.79, 6, 6, 0, "Aethalas")
		player:SEND_GOSSIP_MENU(7482,_Creature:GetGUID())
	end
end

function SendClassTrainerMenu_guard_darnassus(player, _Creature, action)
	if action == GOSSIP_ACTION_INFO_DEF + 1 then

		player:SEND_POI(10186, 2570.46, 6, 6, 0, "Darnassus Druid Trainer")
		player:SEND_GOSSIP_MENU(3024,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 2 then

		player:SEND_POI(10177.29, 2511.10, 6, 6, 0, "Darnassus Hunter Trainer")
		player:SEND_GOSSIP_MENU(3023,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 3 then

		player:SEND_POI(9659.12, 2524.88, 6, 6, 0, "Temple of the Moon")
		player:SEND_GOSSIP_MENU(3025,_Creature:GetGUID())

	elseif (action == GOSSIP_ACTION_INFO_DEF + 4) then

		player:SEND_POI(10122, 2599.12, 6, 6, 0, "Darnassus Rogue Trainer")
		player:SEND_GOSSIP_MENU(3026,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 5 then

		player:SEND_POI(9951.91, 2280.38, 6, 6, 0, "Warrior's Terrace")
		player:SEND_GOSSIP_MENU(3033,_Creature:GetGUID())
	end
end

function SendProfTrainerMenu_guard_darnassus(player, _Creature, action)
	if action == GOSSIP_ACTION_INFO_DEF + 1 then

		player:SEND_POI(10075.90, 2356.76, 6, 6, 0, "Darnassus Alchemy Trainer")
		player:SEND_GOSSIP_MENU(3035,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 2 then

		player:SEND_POI(10088.59, 2419.21, 6, 6, 0, "Darnassus Cooking Trainer")
		player:SEND_GOSSIP_MENU(3036,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 3 then

		player:SEND_POI(10146.09, 2313.42, 6, 6, 0, "Darnassus Enchanting Trainer")
		player:SEND_GOSSIP_MENU(3337,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 4 then

		player:SEND_POI(10150.09, 2390.43, 6, 6, 0, "Darnassus First Aid Trainer")
		player:SEND_GOSSIP_MENU(3037,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 5 then

		player:SEND_POI(9836.20, 2432.17, 6, 6, 0, "Darnassus Fishing Trainer")
		player:SEND_GOSSIP_MENU(3038,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 6 then

		player:SEND_POI(9757.17, 2430.16, 6, 6, 0, "Darnassus Herbalism Trainer")
		player:SEND_GOSSIP_MENU(3039,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 7 then

		player:SEND_POI(10086.59, 2255.77, 6, 6, 0, "Darnassus Leatherworking Trainer")
		player:SEND_GOSSIP_MENU(3040,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 8 then

		player:SEND_POI(10081.40, 2257.18, 6, 6, 0, "Darnassus Skinning Trainer")
		player:SEND_GOSSIP_MENU(3042,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 9 then

		player:SEND_POI(10079.70, 2268.19, 6, 6, 0, "Darnassus Tailor")
		player:SEND_GOSSIP_MENU(3044,_Creature:GetGUID())
	end
end

m_scripts[scriptname]["GossipSelect"] = function(player, _Creature, sender, action)
	--Serving guard_darnassus/main menu
	if sender == GOSSIP_SENDER_MAIN then
		SendDefaultMenu_guard_darnassus(player, _Creature, action)

	--Came from the second menu already
	elseif sender == GOSSIP_SENDER_SEC_CLASSTRAIN then
		SendClassTrainerMenu_guard_darnassus(player, _Creature, action)

	elseif sender == GOSSIP_SENDER_SEC_PROFTRAIN then
		SendProfTrainerMenu_guard_darnassus(player, _Creature, action)

	elseif sender == GOSSIP_SENDER_SEC_BATTLEINFO then
		SendProfTrainerMenu_guard_darnassus(player, _Creature, action)
	end
return RETURN_OK
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

return(128)
end
