scriptname = "guard_orgrimmar"
DisableCppScript( scriptname )

-- Taken from ScriptsDev, converted - SABROG

m_scripts[scriptname] = {}
m_scripts[scriptname]["GossipHello"] = function(player,_Creature)

-- TODO this is used by  guard_default_ai , if script is not part of it anymore pls remove this
guard_default_ai_Gossip_Hello(player,_Creature)

	player:ADD_GOSSIP_ITEM( 0, "Bank"				, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1)
	player:ADD_GOSSIP_ITEM( 0, "Wind Rider Master"	, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2)
	player:ADD_GOSSIP_ITEM( 0, "Guild Master"		, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3)
	player:ADD_GOSSIP_ITEM( 0, "The Inn"				, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4)
	player:ADD_GOSSIP_ITEM( 0, "Mailbox"				, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5)
	player:ADD_GOSSIP_ITEM( 0, "Auction House"		, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6)
	player:ADD_GOSSIP_ITEM( 0, "Zeppelin Master"		, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7)
	player:ADD_GOSSIP_ITEM( 0, "Weapon Master"		, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8)
	player:ADD_GOSSIP_ITEM( 0, "Stable Master"		, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9)
	player:ADD_GOSSIP_ITEM( 0, "Officer's Lounge"		, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10)
	player:ADD_GOSSIP_ITEM( 0, "Battlemaster"		, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11)
	player:ADD_GOSSIP_ITEM( 0, "Class Trainer"		, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12)
	player:ADD_GOSSIP_ITEM( 0, "Profession Trainer"	, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 13)
	player:SEND_GOSSIP_MENU(2593,_Creature:GetGUID())

    return RETURN_OK
end

function SendDefaultMenu_guard_orgrimmar(player, _Creature, action)
	if action == GOSSIP_ACTION_INFO_DEF + 1 then

		player:SEND_POI(1631.51000976562, -4375.330078125, 99, 6, 0, "Bank of Orgrimmar")
		player:SEND_GOSSIP_MENU(2554,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 2 then

		player:SEND_POI(1676.60998535156, -4332.72021484375, 99, 6, 0, "The Sky Tower")
		player:SEND_GOSSIP_MENU(2555,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 3 then

		player:SEND_POI(1576.93005371094, -4294.75, 99, 6, 0, "Horde Embassy")
		player:SEND_GOSSIP_MENU(2556,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 4 then

		player:SEND_POI(1644.51000976562, -4447.27978515625, 99, 6, 0, "Orgrimmar Inn")
		player:SEND_GOSSIP_MENU(2557,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 5 then

		player:SEND_POI(1622.53002929687, -4388.7998046875, 99, 6, 0, "Orgrimmar Mailbox")
		player:SEND_GOSSIP_MENU(2558,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 6 then

		player:SEND_POI(1679.21997070313, -4450.10986328125, 99, 6, 0, "Orgrimmar Auction House")
		player:SEND_GOSSIP_MENU(3075,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 7 then

		player:SEND_POI(1337.36999511719, -4632.7001953125, 99, 6, 0, "Orgrimmar Zeppelin Tower")
		player:SEND_GOSSIP_MENU(3173,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 8 then

		player:SEND_POI(2092.56005859375, -4823.9501953125, 99, 6, 0, "Sayoc & Hanashi")
		player:SEND_GOSSIP_MENU(4519,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 9 then

		player:SEND_POI(2133.1201171875, -4663.93017578125, 99, 6, 0, "Xon'cha")
		player:SEND_GOSSIP_MENU(5974,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 10 then

		player:SEND_POI(1633.56005859375, -4249.3701171875, 99, 6, 0, "Hall of Legends")
		player:SEND_GOSSIP_MENU(7046,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 11 then

		player:ADD_GOSSIP_ITEM( 0, "Alterac Valley"		, GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 1)
		player:ADD_GOSSIP_ITEM( 0, "Arathi Basin"			, GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 2)
		player:ADD_GOSSIP_ITEM( 0, "Warsong Gulch"		, GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 3)
		player:SEND_GOSSIP_MENU(7521,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 12 then

		player:ADD_GOSSIP_ITEM( 0, "Hunter"				, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 1)
		player:ADD_GOSSIP_ITEM( 0, "Mage"				, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 2)
		player:ADD_GOSSIP_ITEM( 0, "Priest"				, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 3)
		player:ADD_GOSSIP_ITEM( 0, "Shaman"				, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 4)
		player:ADD_GOSSIP_ITEM( 0, "Rogue"				, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 5)
		player:ADD_GOSSIP_ITEM( 0, "Warlock"			, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 6)
		player:ADD_GOSSIP_ITEM( 0, "Warrior"				, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 7)
		player:SEND_GOSSIP_MENU(2599,_Creature:GetGUID())

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
		player:SEND_GOSSIP_MENU(2594,_Creature:GetGUID())
	end
end

function SendBattleMasterMenu_guard_orgrimmar(player, _Creature, action)
	if action == GOSSIP_ACTION_INFO_DEF + 1 then

		player:SEND_POI(1983.92004394531, -4794.2099609375, 99, 6, 0, "Hall of the Brave")
		player:SEND_GOSSIP_MENU(7484,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 2 then

		player:SEND_POI(1983.92004394531, -4794.2099609375, 99, 6, 0, "Hall of the Brave")
		player:SEND_GOSSIP_MENU(7644,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 3 then

		player:SEND_POI(1983.92004394531, -4794.2099609375, 99, 6, 0, "Hall of the Brave")
		player:SEND_GOSSIP_MENU(7520,_Creature:GetGUID())
	end
end

function SendClassTrainerMenu_guard_orgrimmar(player, _Creature, action)
	if action == GOSSIP_ACTION_INFO_DEF + 1 then

		player:SEND_POI(2114.84008789062, -4625.31982421875, 99, 6, 0, "Orgrimmar Hunter's Hall")
		player:SEND_GOSSIP_MENU(2559,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 2 then

		player:SEND_POI(1451.26000976562, -4223.330078125, 99, 6, 0, "Darkbriar Lodge")
		player:SEND_GOSSIP_MENU(2560,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 3 then

		player:SEND_POI(1442.21997070313, -4183.240234375, 99, 6, 0, "Spirit Lodge")
		player:SEND_GOSSIP_MENU(2561,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 4 then

		player:SEND_POI(1925.34997558594, -4181.89013671875, 99, 6, 0, "Thrall's Fortress")
		player:SEND_GOSSIP_MENU(2562,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 5 then

		player:SEND_POI(1773.39001464844, -4278.97021484375, 99, 6, 0, "Shadowswift Brotherhood")
		player:SEND_GOSSIP_MENU(2563,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 6 then

		player:SEND_POI(1849.57995605469, -4359.68994140625, 99, 6, 0, "Darkfire Enclave")
		player:SEND_GOSSIP_MENU(2564,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 7 then

		player:SEND_POI(1983.92004394531, -4794.2099609375, 99, 6, 0, "Hall of the Brave")
		player:SEND_GOSSIP_MENU(2565,_Creature:GetGUID())
	end
end

function SendProfTrainerMenu_guard_orgrimmar(player, _Creature, action)
	if action == GOSSIP_ACTION_INFO_DEF + 1 then

		player:SEND_POI(1955.17004394531, -4475.7998046875, 99, 6, 0, "Yelmak's Alchemy and Potions")
		player:SEND_GOSSIP_MENU(2497,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 2 then

		player:SEND_POI(2054.34008789062, -4831.85009765625, 99, 6, 0, "The Burning Anvil")
		player:SEND_GOSSIP_MENU(2499,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 3 then

		player:SEND_POI(1780.96997070313, -4481.31005859375, 99, 6, 0, "Borstan's Firepit")
		player:SEND_GOSSIP_MENU(2500,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 4 then

		player:SEND_POI(1917.5, -4434.9501953125, 99, 6, 0, "Godan's Runeworks")
		player:SEND_GOSSIP_MENU(2501,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 5 then

		player:SEND_POI(2038.4599609375, -4744.759765625, 99, 6, 0, "Nogg's Machine Shop")
		player:SEND_GOSSIP_MENU(2653,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 6 then

		player:SEND_POI(1485.21997070313, -4160.91015625, 99, 6, 0, "Survival of the Fittest")
		player:SEND_GOSSIP_MENU(2502,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 7 then

		player:SEND_POI(1994.15002441406, -4655.7001953125, 99, 6, 0, "Lumak's Fishing")
		player:SEND_GOSSIP_MENU(2503,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 8 then

		player:SEND_POI(1898.61999511719, -4454.93994140625, 99, 6, 0, "Jandi's Arboretum")
		player:SEND_GOSSIP_MENU(2504,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 9 then

		player:SEND_POI(1852.82995605469, -4562.31982421875, 99, 6, 0, "Kodohide Leatherworkers")
		player:SEND_GOSSIP_MENU(2513,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 10 then

		player:SEND_POI(2029.7900390625, -4704.080078125, 99, 6, 0, "Red Canyon Mining")
		player:SEND_GOSSIP_MENU(2515,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 11 then

		player:SEND_POI(1852.82995605469, -4562.31982421875, 99, 6, 0, "Kodohide Leatherworkers")
		player:SEND_GOSSIP_MENU(2516,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 12 then

		player:SEND_POI(1802.66003417969, -4560.66015625, 99, 6, 0, "Magar's Cloth Goods")
		player:SEND_GOSSIP_MENU(2518,_Creature:GetGUID())
	end
end

m_scripts[scriptname]["GossipSelect"] = function(player, _Creature, sender, action)
	-- Serving guard_orgrimmar/main menu
	if sender == GOSSIP_SENDER_MAIN then
		SendDefaultMenu_guard_orgrimmar(player, _Creature, action)

	-- Came from the second menu already
	elseif sender == GOSSIP_SENDER_SEC_CLASSTRAIN then
		SendClassTrainerMenu_guard_orgrimmar(player, _Creature, action)

	elseif sender == GOSSIP_SENDER_SEC_PROFTRAIN then
		SendProfTrainerMenu_guard_orgrimmar(player, _Creature, action)

	elseif sender == GOSSIP_SENDER_SEC_BATTLEINFO then
		SendBattleMasterMenu_guard_orgrimmar(player, _Creature, action)
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
