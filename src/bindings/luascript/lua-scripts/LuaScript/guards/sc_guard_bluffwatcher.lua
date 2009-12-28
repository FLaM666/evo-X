scriptname = "guard_bluffwatcher"
DisableCppScript( scriptname )

-- Taken from ScriptsDev, converted - Greatestevil

m_scripts[scriptname] = {}
m_scripts[scriptname]["GossipHello"] = function(player,_Creature)

-- TODO this is used by  guard_default_ai , if script is not part of it anymore pls remove this
guard_default_ai_Gossip_Hello(player,_Creature)

	player:ADD_GOSSIP_ITEM( 0, "Bank"					, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1)
	player:ADD_GOSSIP_ITEM( 0, "Wind Rider Master"		, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2)
	player:ADD_GOSSIP_ITEM( 0, "Guild Master"			, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3)
	player:ADD_GOSSIP_ITEM( 0, "The Inn"					, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4)
	player:ADD_GOSSIP_ITEM( 0, "Mailbox"					, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5)
	player:ADD_GOSSIP_ITEM( 0, "Auction House"			, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6)
	player:ADD_GOSSIP_ITEM( 0, "Weapon Master"			, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7)
	player:ADD_GOSSIP_ITEM( 0, "Stable Master"			, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8)
	player:ADD_GOSSIP_ITEM( 0, "Battlemaster"			, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9)
	player:ADD_GOSSIP_ITEM( 0, "Class Trainer"			, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10)
	player:ADD_GOSSIP_ITEM( 0, "Profession Trainer"		, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11)
	player:SEND_GOSSIP_MENU(3543,_Creature:GetGUID())

return RETURN_OK
end

function SendDefaultMenu_guard_bluffwatcher(player, _Creature, action)
	if action == GOSSIP_ACTION_INFO_DEF + 1 then

		player:SEND_POI(-1257.8, 24.14, 6, 6, 0, "Thunder Bluff Bank")
		player:SEND_GOSSIP_MENU(1292,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 2 then

		player:SEND_POI(-1196.43, 28.26, 6, 6, 0, "Wind Rider Roost")
		player:SEND_GOSSIP_MENU(1293,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 3 then

		player:SEND_POI(-1296.5, 127.57, 6, 6, 0, "Thunder Bluff Civic Information")
		player:SEND_GOSSIP_MENU(1291,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 4 then

		player:SEND_POI(-1296, 39.7, 6, 6, 0, "Thunder Bluff Inn")
		player:SEND_GOSSIP_MENU(3153,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 5 then

		player:SEND_POI(-1263.59, 44.36, 6, 6, 0, "Thunder Bluff Mailbox")
		player:SEND_GOSSIP_MENU(3154,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 6 then

		player:SEND_POI(1381.77, -4371.16, 6, 6, 0, "Auction House")
		player:SEND_GOSSIP_MENU(3155,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 7 then

		player:SEND_POI(-1282.31, 89.56, 6, 6, 0, "Ansekhwa")
		player:SEND_GOSSIP_MENU(4520,_Creature:GetGUID())
	elseif action == GOSSIP_ACTION_INFO_DEF + 8 then

		player:SEND_POI(-1270.19, 48.84, 6, 6, 0, "Bulrug")
		player:SEND_GOSSIP_MENU(5977,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 9 then

		player:ADD_GOSSIP_ITEM( 8, "Alterac Valley"		, GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 1)
		player:ADD_GOSSIP_ITEM( 8, "Arathi Basin"			, GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 2)
		player:ADD_GOSSIP_ITEM( 8, "Warsong Gulch"		, GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 3)
		player:SEND_GOSSIP_MENU(7527,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 10 then

		player:ADD_GOSSIP_ITEM( 3, "Druid"				, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 1)
		player:ADD_GOSSIP_ITEM( 3, "Hunter"				, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 2)
		player:ADD_GOSSIP_ITEM( 3, "Mage"				, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 3)
		player:ADD_GOSSIP_ITEM( 3, "Priest"				, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 4)
		player:ADD_GOSSIP_ITEM( 3, "Shaman"				, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 5)
		player:ADD_GOSSIP_ITEM( 3, "Warrior"				, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 6)
		player:SEND_GOSSIP_MENU(3542,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 11 then

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

function SendBattleMasterMenu_guard_bluffwatcher(player, _Creature, action)
	if action == GOSSIP_ACTION_INFO_DEF + 1 then

		player:SEND_POI(-1387.82, -97.55, 6, 6, 0, "Taim Ragetotem")
		player:SEND_GOSSIP_MENU(7522,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 2 then

		player:SEND_POI(-997, 214.12, 6, 6, 0, "Martin Lindsey")
		player:SEND_GOSSIP_MENU(7648,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 3 then

		player:SEND_POI(-1384.94, -75.91, 6, 6, 0, "Kergul Bloodaxe")
		player:SEND_GOSSIP_MENU(7523,_Creature:GetGUID())
	end
end

function SendClassTrainerMenu_guard_bluffwatcher(player, _Creature, action)
	if action == GOSSIP_ACTION_INFO_DEF + 1 then

		player:SEND_POI(-1054.47, -285, 6, 6, 0, "Hall of Elders")
		player:SEND_GOSSIP_MENU(1294,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 2 then

		player:SEND_POI(-1416.32, -114.28, 6, 6, 0, "Hunter's Hall")
		player:SEND_GOSSIP_MENU(1295,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 3 then

		player:SEND_POI(-1061.2, 195.5, 6, 6, 0, "Pools of Vision")
		player:SEND_GOSSIP_MENU(1296,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 4 then

		player:SEND_POI(-1061.2, 195.5, 6, 6, 0, "Pools of Vision")
		player:SEND_GOSSIP_MENU(1297,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 5 then

		player:SEND_POI(-989.54, 278.25, 6, 6, 0, "Hall of Spirits")
		player:SEND_GOSSIP_MENU(1298,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 6 then

		player:SEND_POI(-1416.32, -114.28, 6, 6, 0, "Hunter's Hall")
		player:SEND_GOSSIP_MENU(1299,_Creature:GetGUID())
	end
end

function SendProfTrainerMenu_guard_bluffwatcher(player, _Creature, action)
	if action == GOSSIP_ACTION_INFO_DEF + 1 then

		player:SEND_POI(-1085.56, 27.29, 6, 6, 0, "Bena's Alchemy")
		player:SEND_GOSSIP_MENU(1332,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 2 then

		player:SEND_POI(-1239.75, 104.88, 6, 6, 0, "Karn's Smithy")
		player:SEND_GOSSIP_MENU(1333,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 3 then

		player:SEND_POI(-1214.5, -21.23, 6, 6, 0, "Aska's Kitchen")
		player:SEND_GOSSIP_MENU(1334,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 4 then

		player:SEND_POI(-1112.65, 48.26, 6, 6, 0, "Dawnstrider Enchanters")
		player:SEND_GOSSIP_MENU(1335,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 5 then

		player:SEND_POI(-996.58, 200.5, 6, 6, 0, "Spiritual Healing")
		player:SEND_GOSSIP_MENU(1336,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 6 then

		player:SEND_POI(-1169.35, -68.87, 6, 6, 0, "Mountaintop Bait & Tackle")
		player:SEND_GOSSIP_MENU(1337,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 7 then

		player:SEND_POI(-1137.7, -1.51, 6, 6, 0, "Holistic Herbalism")
		player:SEND_GOSSIP_MENU(1338,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 8 then

		player:SEND_POI(-1156.22, 66.86, 6, 6, 0, "Thunder Bluff Armorers")
		player:SEND_GOSSIP_MENU(1339,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 9 then

		player:SEND_POI(-1249.17, 155, 6, 6, 0, "Stonehoof Geology")
		player:SEND_GOSSIP_MENU(1340,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 10 then

		player:SEND_POI(-1148.56, 51.18, 6, 6, 0, "Mooranta")
		player:SEND_GOSSIP_MENU(1343,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 11 then

		player:SEND_POI(-1156.22, 66.86, 6, 6, 0, "Thunder Bluff Armorers")
		player:SEND_GOSSIP_MENU(1341,_Creature:GetGUID())
	end
end

m_scripts[scriptname]["GossipSelect"] = function(player, _Creature, sender, action)
	-- Serving guard_bluffwatcher/main menu
	if sender == GOSSIP_SENDER_MAIN then
		SendDefaultMenu_guard_bluffwatcher(player, _Creature, action)

	-- Came from the second menu already
	elseif sender == GOSSIP_SENDER_SEC_CLASSTRAIN then
		SendClassTrainerMenu_guard_bluffwatcher(player, _Creature, action)

	elseif sender == GOSSIP_SENDER_SEC_PROFTRAIN then
		SendProfTrainerMenu_guard_bluffwatcher(player, _Creature, action)

	elseif sender == GOSSIP_SENDER_SEC_BATTLEINFO then
		SendBattleMasterMenu_guard_bluffwatcher(player, _Creature, action)
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
