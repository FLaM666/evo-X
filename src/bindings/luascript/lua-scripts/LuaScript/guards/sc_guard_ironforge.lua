scriptname = "guard_ironforge"
DisableCppScript( scriptname )

-- Taken from ScriptsDev, converted - Greatestevil

m_scripts[scriptname] = {}
m_scripts[scriptname]["GossipHello"] = function(player,_Creature)

-- TODO this is used by  guard_default_ai , if script is not part of it anymore pls remove this
guard_default_ai_Gossip_Hello(player,_Creature)

	player:ADD_GOSSIP_ITEM( 1, "Auction House"			, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1)
	player:ADD_GOSSIP_ITEM( 6, "Bank of Ironforge"		, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2)
	player:ADD_GOSSIP_ITEM( 4, "Deeprun Tram"			, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3)
	player:ADD_GOSSIP_ITEM( 2, "Gryphon Master"			, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4)
	player:ADD_GOSSIP_ITEM( 0, "Guild Master"			, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5)
	player:ADD_GOSSIP_ITEM( 1, "The Inn"					, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6)
	player:ADD_GOSSIP_ITEM( 4, "Mailbox"					, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7)
	player:ADD_GOSSIP_ITEM( 5, "Stable Master"			, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8)
	player:ADD_GOSSIP_ITEM( 0, "Weapon Master"			, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9)
	player:ADD_GOSSIP_ITEM( 8, "Battlemaster"			, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10)
	player:ADD_GOSSIP_ITEM( 3, "Class Trainer"				, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11)
	player:ADD_GOSSIP_ITEM( 3, "Profession Trainer"		, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12)
	player:SEND_GOSSIP_MENU(2760,_Creature:GetGUID())

	return RETURN_OK
end

function SendDefaultMenu_guard_ironforge(player, _Creature, action)
	if action == GOSSIP_ACTION_INFO_DEF + 1 then

		player:SEND_POI(-4957.39, -911.6, 6, 6, 0, "Ironforge Auction House")
		player:SEND_GOSSIP_MENU(3014,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 2 then

		player:SEND_POI(-4891.91, -991.47, 6, 6, 0, "The Vault")
		player:SEND_GOSSIP_MENU(2761,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 3 then

		player:SEND_POI(-4835.27, -1294.69, 6, 6, 0, "Deeprun Tram")
		player:SEND_GOSSIP_MENU(3814,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 4 then

		player:SEND_POI(-4821.52, -1152.3, 6, 6, 0, "Ironforge Gryphon Master")
		player:SEND_GOSSIP_MENU(2762,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 5 then

		player:SEND_POI(-5021, -996.45, 6, 6, 0, "Ironforge Visitor's Center")
		player:SEND_GOSSIP_MENU(2764,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 6 then

		player:SEND_POI(-4850.47, -872.57, 6, 6, 0, "Stonefire Tavern")
		player:SEND_GOSSIP_MENU(2768,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 7 then

		player:SEND_POI(-4845.7, -880.55, 6, 6, 0, "Ironforge Mailbox")
		player:SEND_GOSSIP_MENU(2769,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 8 then

		player:SEND_POI(-5010.2, -1262, 6, 6, 0, "Ulbrek Firehand")
		player:SEND_GOSSIP_MENU(5986,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 9 then

		player:SEND_POI(-5040, -1201.88, 6, 6, 0, "Bixi and Buliwyf")
		player:SEND_GOSSIP_MENU(4518,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 10 then

		player:ADD_GOSSIP_ITEM( 8, "Alterac Valley"		, GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 1)
		player:ADD_GOSSIP_ITEM( 8, "Arathi Basin"			, GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 2)
		player:ADD_GOSSIP_ITEM( 8, "Warsong Gulch"		, GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 3)
		player:SEND_GOSSIP_MENU(7529,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 11 then

		player:ADD_GOSSIP_ITEM( 3, "Hunter"				, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 1)
		player:ADD_GOSSIP_ITEM( 3, "Mage"				, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 2)
		player:ADD_GOSSIP_ITEM( 3, "Paladin"				, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 3)
		player:ADD_GOSSIP_ITEM( 3, "Priest"				, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 4)
		player:ADD_GOSSIP_ITEM( 3, "Rogue"				, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 5)
		player:ADD_GOSSIP_ITEM( 3, "Warlock"				, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 6)
		player:ADD_GOSSIP_ITEM( 3, "Warrior"				, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 7)
		player:SEND_GOSSIP_MENU(2766,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 12 then

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
		player:SEND_GOSSIP_MENU(2793,_Creature:GetGUID())
	end
end

function SendBattleMasterMenu_guard_ironforge(player, _Creature, action)
	if action == GOSSIP_ACTION_INFO_DEF + 1 then

		player:SEND_POI(-5047.87, -1263.77, 6, 6, 0, "Glordrum Steelbeard")
		player:SEND_GOSSIP_MENU(7483,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 2 then

		player:SEND_POI(-5038.37, -1266.39, 6, 6, 0, "Donal Osgood")
		player:SEND_GOSSIP_MENU(7649,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 3 then

		player:SEND_POI(-5037.24, -1274.82, 6, 6, 0, "Lylandris")
		player:SEND_GOSSIP_MENU(7528,_Creature:GetGUID())
	end
end

function SendClassTrainerMenu_guard_ironforge(player, _Creature, action)
	if action == GOSSIP_ACTION_INFO_DEF + 1 then

		player:SEND_POI(-5023, -1253.68, 6, 6, 0, "Hall of Arms")
		player:SEND_GOSSIP_MENU(2770,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 2 then

		player:SEND_POI(-4627, -926.45, 6, 6, 0, "Hall of Mysteries")
		player:SEND_GOSSIP_MENU(2771,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 3 then

		player:SEND_POI(-4627.02, -926.45, 6, 6, 0, "Hall of Mysteries")
		player:SEND_GOSSIP_MENU(2773,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 4 then

		player:SEND_POI(-4627, -926.45, 6, 6, 0, "Hall of Mysteries")
		player:SEND_GOSSIP_MENU(2772,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 5 then

		player:SEND_POI(-4647.83, -1124, 6, 6, 0, "Ironforge Rogue Trainer")
		player:SEND_GOSSIP_MENU(2774,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 6 then

		player:SEND_POI(-4605, -1110.45, 6, 6, 0, "Ironforge Warlock Trainer")
		player:SEND_GOSSIP_MENU(2775,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 7 then

		player:SEND_POI(-5023.08, -1253.68, 6, 6, 0, "Hall of Arms")
		player:SEND_GOSSIP_MENU(2776,_Creature:GetGUID())
	end
end

function SendProfTrainerMenu_guard_ironforge(player, _Creature, action)
	if action == GOSSIP_ACTION_INFO_DEF + 1 then

		player:SEND_POI(-4858.5, -1241.83, 6, 6, 0, "Berryfizz's Potions and Mixed Drinks")
		player:SEND_GOSSIP_MENU(2794,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 2 then

		player:SEND_POI(-4796.97, -1110.17, 6, 6, 0, "The Great Forge")
		player:SEND_GOSSIP_MENU(2795,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 3 then

		player:SEND_POI(-4767.83, -1184.59, 6, 6, 0, "The Bronze Kettle")
		player:SEND_GOSSIP_MENU(2796,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 4 then

		player:SEND_POI(-4803.72, -1196.53, 6, 6, 0, "Thistlefuzz Arcanery")
		player:SEND_GOSSIP_MENU(2797,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 5 then

		player:SEND_POI(-4799.56, -1250.23, 6, 6, 0, "Springspindle's Gadgets")
		player:SEND_GOSSIP_MENU(2798,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 6 then

		player:SEND_POI(-4881.6, -1153.13, 6, 6, 0, "Ironforge Physician")
		player:SEND_GOSSIP_MENU(2799,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 7 then

		player:SEND_POI(-4597.91, -1091.93, 6, 6, 0, "Traveling Fisherman")
		player:SEND_GOSSIP_MENU(2800,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 8 then

		player:SEND_POI(-4876.9, -1151.92, 6, 6, 0, "Ironforge Physician")
		player:SEND_GOSSIP_MENU(2801,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 9 then

		player:SEND_POI(-4745, -1027.57, 6, 6, 0, "Finespindle's Leather Goods")
		player:SEND_GOSSIP_MENU(2802,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 10 then

		player:SEND_POI(-4705.06, -1116.43, 6, 6, 0, "Deepmountain Mining Guild")
		player:SEND_GOSSIP_MENU(2804,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 11 then

		player:SEND_POI(-4745, -1027.57, 6, 6, 0, "Finespindle's Leather Goods")
		player:SEND_GOSSIP_MENU(2805,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 12 then

		player:SEND_POI(-4719.60, -1056.96, 6, 6, 0, "Stonebrow's Clothier")
		player:SEND_GOSSIP_MENU(2807,_Creature:GetGUID())
	end
end

m_scripts[scriptname]["GossipSelect"] = function(player, _Creature, sender, action)
	-- Serving guard_ironforge/main menu
	if sender == GOSSIP_SENDER_MAIN then
		SendDefaultMenu_guard_ironforge(player, _Creature, action)

	-- Came from the second menu already
	elseif sender == GOSSIP_SENDER_SEC_CLASSTRAIN then
		SendClassTrainerMenu_guard_ironforge(player, _Creature, action)

	elseif sender == GOSSIP_SENDER_SEC_PROFTRAIN then
		SendProfTrainerMenu_guard_ironforge(player, _Creature, action)

	elseif sender == GOSSIP_SENDER_SEC_BATTLEINFO then
		SendBattleMasterMenu_guard_ironforge(player, _Creature, action)
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
