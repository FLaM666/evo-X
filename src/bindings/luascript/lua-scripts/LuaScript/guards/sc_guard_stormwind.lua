scriptname = "guard_stormwind"
DisableCppScript( scriptname )

--Taken from ScriptsDev

m_scripts[scriptname] = {}
m_scripts[scriptname]["GossipHello"] = function(player,_Creature)

-- TODO this is used by  guard_default_ai , if script is not part of it anymore pls remove this
guard_default_ai_Gossip_Hello(player,_Creature)

	player:ADD_GOSSIP_ITEM( 0, "Auction House"			, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1)
	player:ADD_GOSSIP_ITEM( 0, "Bank of Stormwind"		, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2)
	player:ADD_GOSSIP_ITEM( 0, "Deeprun Tram"			, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3)
	player:ADD_GOSSIP_ITEM( 0, "The Inn"					, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4)
	player:ADD_GOSSIP_ITEM( 0, "Gryphon Master"			, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5)
	player:ADD_GOSSIP_ITEM( 0, "Guild Master"			, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6)
	player:ADD_GOSSIP_ITEM( 0, "Mailbox"					, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7)
	player:ADD_GOSSIP_ITEM( 0, "Stable Master"			, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8)
	player:ADD_GOSSIP_ITEM( 0, "Weapon Master"			, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9)
	player:ADD_GOSSIP_ITEM( 0, "Officer's Lounge"			, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10)
	player:ADD_GOSSIP_ITEM( 8, "Battlemaster"			, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11)
	player:ADD_GOSSIP_ITEM( 3, "Class Trainer"			, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12)
	player:ADD_GOSSIP_ITEM( 3, "Profession Trainer"		, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 13)
	player:SEND_GOSSIP_MENU(2593,_Creature:GetGUID());

return RETURN_OK
end

--Some functions
function SendDefaultMenu_guard_stormwind(player, _Creature,  action)
	if action == GOSSIP_ACTION_INFO_DEF + 1 then

		player:SEND_POI(-8811.46, 667.46, 6, 6, 0, "Stormwind Auction House")
		player:SEND_GOSSIP_MENU(3834,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 2 then

		player:SEND_POI(-8916.87, 622.87, 6, 6, 0, "Stormwind Bank")
		player:SEND_GOSSIP_MENU(764,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 3 then

		player:SEND_POI(-8378.88, 554.23, 6, 6, 0, "The Deeprun Tram")
		player:SEND_GOSSIP_MENU(3813,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 4 then

		player:SEND_POI(-8869.0, 675.4, 6, 6, 0, "The Gilded Rose")
		player:SEND_GOSSIP_MENU(3860,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 5 then

		player:SEND_POI(-8837.0, 493.5, 6, 6, 0, "Stormwind Gryphon Master")
		player:SEND_GOSSIP_MENU(879,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 6 then

		player:SEND_POI(-8894.0, 611.2, 6, 6, 0, "Stormwind Vistor`s Center")
		player:SEND_GOSSIP_MENU(882,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 7 then

		player:SEND_POI(-8876.48, 649.18, 6, 6, 0, "Stormwind Mailbox")
		player:SEND_GOSSIP_MENU(3618,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 8 then

		player:SEND_POI(-8433.0, 554.7, 6, 6, 0, "Jenova Stoneshield")
		player:SEND_GOSSIP_MENU(5984,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 9 then

		player:SEND_POI(-8797.0, 612.8, 6, 6, 0, "Woo Ping")
		player:SEND_GOSSIP_MENU(4516,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 10 then

		player:SEND_POI(-8759.92, 399.69, 6, 6, 0, "Champions` Hall")
		player:SEND_GOSSIP_MENU(7047,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 11 then

		player:ADD_GOSSIP_ITEM( 8, "Alterac Valley"		, GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 1);
		player:ADD_GOSSIP_ITEM( 8, "Arathi Basin"			, GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 2);
		player:ADD_GOSSIP_ITEM( 8, "Warsong Gulch"		, GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 3);
		player:SEND_GOSSIP_MENU(7499,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 12 then

		player:ADD_GOSSIP_ITEM( 0, "Mage"				, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 1)
		player:ADD_GOSSIP_ITEM( 0, "Rogue"				, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 2)
		player:ADD_GOSSIP_ITEM( 0, "Warrior"				, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 3)
		player:ADD_GOSSIP_ITEM( 0, "Druid"				, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 4)
		player:ADD_GOSSIP_ITEM( 0, "Priest"				, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 5)
		player:ADD_GOSSIP_ITEM( 0, "Paladin"				, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 6)
		player:ADD_GOSSIP_ITEM( 0, "Hunter"				, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 7)
		player:ADD_GOSSIP_ITEM( 0, "Warlock"			, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 8)
		player:SEND_GOSSIP_MENU(4264,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 13 then

		player:ADD_GOSSIP_ITEM( 0, "Alchemy"			, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 1)
		player:ADD_GOSSIP_ITEM( 0, "Blacksmithing"		, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 2)
		player:ADD_GOSSIP_ITEM( 0, "Cooking"				, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 3)
		player:ADD_GOSSIP_ITEM( 0, "Enchanting"			, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 4)
		player:ADD_GOSSIP_ITEM( 0, "Engineering"			, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 5)
		player:ADD_GOSSIP_ITEM( 0, "First Aid"			, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 6)
		player:ADD_GOSSIP_ITEM( 0, "Fishing"				, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 7)
		player:ADD_GOSSIP_ITEM( 0, "Herbalism"			, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 8)
		player:ADD_GOSSIP_ITEM( 0, "Leatherworking"		, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 9)
		player:ADD_GOSSIP_ITEM( 0, "Mining"				, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 10)
		player:ADD_GOSSIP_ITEM( 0, "Skinning"			, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 11)
		player:ADD_GOSSIP_ITEM( 0, "Tailoring"			, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 12)
		player:SEND_GOSSIP_MENU(4273,_Creature:GetGUID())
	end
end

function SendBattleMasterMenu_guard_stormwind(player, _Creature, action)
	if action == GOSSIP_ACTION_INFO_DEF + 1 then

		player:SEND_POI(-8443.88, 335.99, 6, 6, 0, "Thelman Slatefist")
		player:SEND_GOSSIP_MENU(7500,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 2 then

		player:SEND_POI(-8443.88, 335.99, 6, 6, 0, "Lady Hoteshem")
		player:SEND_GOSSIP_MENU(7650,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 3 then

		player:SEND_POI(-8443.88, 335.99, 6, 6, 0, "Elfarran")
		player:SEND_GOSSIP_MENU(7501,_Creature:GetGUID())
	end
end

function SendClassTrainerMenu_guard_stormwind(player, _Creature, action)
	if action == GOSSIP_ACTION_INFO_DEF + 1 then

		player:SEND_POI(-9012.0, 867.6, 6, 6, 0, "Wizard`s Sanctum")
		player:SEND_GOSSIP_MENU(899,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 2 then

		player:SEND_POI(-8753.0, 367.8, 6, 6, 0, "Stormwind - Rogue House")
		player:SEND_GOSSIP_MENU(900,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 3 then

		player:SEND_POI(-8624.54, 402.61, 6, 6, 0, "Stormwind Barracks")
		player:SEND_GOSSIP_MENU(901,_Creature:GetGUID())

	elseif (action == GOSSIP_ACTION_INFO_DEF + 4) then

		player:SEND_POI(-8751.0, 1124.5, 6, 6, 0, "The Park")
		player:SEND_GOSSIP_MENU(902,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 5 then

		player:SEND_POI(-8512.0, 862.4, 6, 6, 0, "Catedral Of Light")
		player:SEND_GOSSIP_MENU(903,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 6 then

		player:SEND_POI(-8577.0, 881.7, 6, 6, 0, "Catedral Of Light")
		player:SEND_GOSSIP_MENU(904,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 7 then

		player:SEND_POI(-8413.0, 541.5, 6, 6, 0, "Hunter Lodge")
		player:SEND_GOSSIP_MENU(905,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 8 then

		player:SEND_POI(-8948.91, 998.35, 6, 6, 0, "The Slaughtered Lamb")
		player:SEND_GOSSIP_MENU(906,_Creature:GetGUID())
	end
end

function SendProfTrainerMenu_guard_stormwind(player, _Creature, action)
	if action == GOSSIP_ACTION_INFO_DEF + 1 then

		player:SEND_POI(-8988.0, 759.60, 6, 6, 0, "Alchemy Needs")
		player:SEND_GOSSIP_MENU(919,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 2 then

		player:SEND_POI(-8424.0, 616.9, 6, 6, 0, "Therum Deepforge")
		player:SEND_GOSSIP_MENU(920,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 3 then

		player:SEND_POI(-8611.0, 364.6, 6, 6, 0, "Pig and Whistle Tavern")
		player:SEND_GOSSIP_MENU(921,_Creature:GetGUID())


	elseif action == GOSSIP_ACTION_INFO_DEF + 4 then

		player:SEND_POI(-8858.0, 803.7, 6, 6, 0, "Lucan Cordell")
		player:SEND_GOSSIP_MENU(941,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 5 then

		player:SEND_POI(-8347.0, 644.1, 6, 6, 0, "Lilliam Sparkspindle")
		player:SEND_GOSSIP_MENU(922,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 6 then

		player:SEND_POI(-8513.0, 801.8, 6, 6, 0, "Shaina Fuller")
		player:SEND_GOSSIP_MENU(923,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 7 then

		player:SEND_POI(-8803.0, 767.5, 6, 6, 0, "Arnold Leland")
		player:SEND_GOSSIP_MENU(940,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 8 then

		player:SEND_POI(-8967.0, 779.5, 6, 6, 0, "Alchemy Needs")
		player:SEND_GOSSIP_MENU(924,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 9 then

		player:SEND_POI(-8726.0, 477.4, 6, 6, 0, "The Protective Hide")
		player:SEND_GOSSIP_MENU(925,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 10 then

		player:SEND_POI(-8434.0, 692.8, 6, 6, 0, "Gelman Stonehand")
		player:SEND_GOSSIP_MENU(927,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 11 then

		player:SEND_POI(-8716.0, 469.4, 6, 6, 0, "The Protective Hide")
		player:SEND_GOSSIP_MENU(928,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 12 then

		player:SEND_POI(-8938.0, 800.7, 6, 6, 0, "Duncan`s Textiles")
		player:SEND_GOSSIP_MENU(929,_Creature:GetGUID())
	end
end

m_scripts[scriptname]["GossipSelect"] = function(player, _Creature, sender, action)
	--Serving guard_stormwind/main menu
	if sender == GOSSIP_SENDER_MAIN then
		SendDefaultMenu_guard_stormwind(player, _Creature, action)

	--Came from the second menu already
	elseif sender == GOSSIP_SENDER_SEC_CLASSTRAIN then
		SendClassTrainerMenu_guard_stormwind(player, _Creature, action)

	elseif sender == GOSSIP_SENDER_SEC_PROFTRAIN then
		SendProfTrainerMenu_guard_stormwind(player, _Creature, action)

	elseif sender == GOSSIP_SENDER_SEC_BATTLEINFO then
		SendProfTrainerMenu_guard_stormwind(player, _Creature, action)
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
