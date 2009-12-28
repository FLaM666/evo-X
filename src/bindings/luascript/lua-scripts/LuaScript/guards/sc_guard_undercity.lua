scriptname = "guard_undercity"
DisableCppScript( scriptname )

--Taken from ScriptsDev, converted - SABROG

m_scripts[scriptname] = {}

m_scripts[scriptname]["GossipHello"] = function(player,_Creature)

-- TODO this is used by  guard_default_ai , if script is not part of it anymore pls remove this
guard_default_ai_Gossip_Hello(player,_Creature)

	    player:ADD_GOSSIP_ITEM( 0, "The Bank"				, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1)
	    player:ADD_GOSSIP_ITEM( 0, "Bat Handler"			, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2)
	    player:ADD_GOSSIP_ITEM( 0, "Guild Master"			, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3)
	    player:ADD_GOSSIP_ITEM( 0, "The Inn"				, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4)
	    player:ADD_GOSSIP_ITEM( 0, "The Mailbox"			, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5)
	    player:ADD_GOSSIP_ITEM( 0, "Auction House"			, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6)
	    player:ADD_GOSSIP_ITEM( 0, "Zeppelin Master"		, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7)
	    player:ADD_GOSSIP_ITEM( 0, "Weapon Master"		, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8)
	    player:ADD_GOSSIP_ITEM( 0, "Stable Master"			, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9)
	    player:ADD_GOSSIP_ITEM( 0, "Battlemaster"			, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10)
	    player:ADD_GOSSIP_ITEM( 0, "Class Trainer"			, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11)
	    player:ADD_GOSSIP_ITEM( 0, "Profession Trainer"		, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12)
	    player:SEND_GOSSIP_MENU(3543,_Creature:GetGUID())

	return RETURN_OK
end

function SendDefaultMenu_guard_undercity(player, _Creature, action)

    if action == GOSSIP_ACTION_INFO_DEF + 1 then

        player:SEND_POI(1595.64001464844, 232.455993652344, 99, 6, 0, "Undercity Bank")
        player:SEND_GOSSIP_MENU(3514,_Creature:GetGUID())

    elseif action == GOSSIP_ACTION_INFO_DEF + 2 then

        player:SEND_POI(1565.90002441406, 271.434997558594, 99, 6, 0, "Undercity Bat Handler")
        player:SEND_GOSSIP_MENU(3515,_Creature:GetGUID())

    elseif action == GOSSIP_ACTION_INFO_DEF + 3 then

        player:SEND_POI(1594.17004394531, 205.572006225586, 99, 6, 0, "Undercity Guild Master")
        player:SEND_GOSSIP_MENU(3516,_Creature:GetGUID())

    elseif action == GOSSIP_ACTION_INFO_DEF + 4 then

        player:SEND_POI(1639.43005371094, 220.998001098633, 99, 6, 0, "Undercity Inn")
        player:SEND_GOSSIP_MENU(3517,_Creature:GetGUID())
    
    elseif action == GOSSIP_ACTION_INFO_DEF + 5 then

        player:SEND_POI(1632.68994140625, 219.40299987793, 99, 6, 0, "Undercity Mailbox")
        player:SEND_GOSSIP_MENU(3518,_Creature:GetGUID())
    
    elseif action == GOSSIP_ACTION_INFO_DEF + 6 then

        player:SEND_POI(2059.0400390625, 274.868988037109, 99, 6, 0, "Undercity Zeppelin")
        player:SEND_GOSSIP_MENU(3519,_Creature:GetGUID())
    
    elseif action == GOSSIP_ACTION_INFO_DEF + 7 then

        player:SEND_GOSSIP_MENU(3520,_Creature:GetGUID())
    
    elseif action == GOSSIP_ACTION_INFO_DEF + 8 then

        player:SEND_POI(1670.31005859375, 324.665985107422, 99, 6, 0, "Archibald")
        player:SEND_GOSSIP_MENU(4521,_Creature:GetGUID())
    
    elseif action == GOSSIP_ACTION_INFO_DEF + 9 then

        player:SEND_POI(1634.18005371094, 226.768005371094, 99, 6, 0, "Anya Maulray")
        player:SEND_GOSSIP_MENU(5979,_Creature:GetGUID())
    
    elseif action == GOSSIP_ACTION_INFO_DEF + 10 then

        player:ADD_GOSSIP_ITEM( 0, "Alterac Valley"		, GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 1)
        player:ADD_GOSSIP_ITEM( 0, "Arathi Basin"			, GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 2)
        player:ADD_GOSSIP_ITEM( 0, "Warsong Gulch"		, GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 3)
        player:SEND_GOSSIP_MENU(7527,_Creature:GetGUID())
    
    elseif action == GOSSIP_ACTION_INFO_DEF + 11 then

        player:ADD_GOSSIP_ITEM( 0, "Mage"				, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 1)
        player:ADD_GOSSIP_ITEM( 0, "Priest"				, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 2)
        player:ADD_GOSSIP_ITEM( 0, "Rogue"				, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 3)
        player:ADD_GOSSIP_ITEM( 0, "Warlock"			, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 4)
        player:ADD_GOSSIP_ITEM( 0, "Warrior"				, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 5)
        player:SEND_GOSSIP_MENU(3542,_Creature:GetGUID())

    elseif action == GOSSIP_ACTION_INFO_DEF + 12 then

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
        player:SEND_GOSSIP_MENU(3541,_Creature:GetGUID())

    end
end

function SendBattleMasterMenu_guard_undercity(player, _Creature, action)

    if action == GOSSIP_ACTION_INFO_DEF + 1 then

        player:SEND_POI(1329.05004882812, 333.920013427734, 99, 6, 0, "Grizzle Halfmane")
        player:SEND_GOSSIP_MENU(7525,_Creature:GetGUID())

    elseif action == GOSSIP_ACTION_INFO_DEF + 2 then

        player:SEND_POI(1283.30004882812, 287.160003662109, 99, 6, 0, "Sir Malory Wheeler")
        player:SEND_GOSSIP_MENU(7646,_Creature:GetGUID())

    elseif action == GOSSIP_ACTION_INFO_DEF + 3 then

        player:SEND_POI(1265.09997558594, 351.182006835937, 99, 6, 0, "Kurden Bloodclaw")
        player:SEND_GOSSIP_MENU(7526,_Creature:GetGUID())

    end
end

function SendClassTrainerMenu_guard_undercity(player, _Creature, action)

    if action == GOSSIP_ACTION_INFO_DEF + 1 then

        player:SEND_POI(1781.08996582031, 53.0096015930176, 99, 6, 0, "Undercity Mage Trainers")
        player:SEND_GOSSIP_MENU(3513,_Creature:GetGUID())

    elseif action == GOSSIP_ACTION_INFO_DEF + 2 then

        player:SEND_POI(1758.33996582031, 401.506988525391, 99, 6, 0, "Undercity Priest Trainers")
        player:SEND_GOSSIP_MENU(3521,_Creature:GetGUID())

    elseif action == GOSSIP_ACTION_INFO_DEF + 3 then

        player:SEND_POI(1418.56005859375, 65.024299621582, 99, 6, 0, "Undercity Rogue Trainers")
        player:SEND_GOSSIP_MENU(3526,_Creature:GetGUID())

    elseif action == GOSSIP_ACTION_INFO_DEF + 4 then

        player:SEND_POI(1780.92004394531, 53.1697006225586, 99, 6, 0, "Undercity Warlock Trainers")
        player:SEND_GOSSIP_MENU(3526,_Creature:GetGUID())

    elseif action == GOSSIP_ACTION_INFO_DEF + 5 then

        player:SEND_POI(1775.59997558594, 418.192993164063, 99, 6, 0, "Undercity Warrior Trainers")
        player:SEND_GOSSIP_MENU(3527,_Creature:GetGUID())

    end
end

function SendProfTrainerMenu_guard_undercity(player, _Creature, action)

    if action == GOSSIP_ACTION_INFO_DEF + 1 then

        player:SEND_POI(1419.82995605469, 417.196990966797, 99, 6, 0, "The Apothecarium")
        player:SEND_GOSSIP_MENU(3528,_Creature:GetGUID())
 
    elseif action == GOSSIP_ACTION_INFO_DEF + 2 then

        player:SEND_POI(1696, 285.0419921875, 99, 6, 0, "Undercity Blacksmithing Trainer")
        player:SEND_GOSSIP_MENU(3529,_Creature:GetGUID())

    elseif action == GOSSIP_ACTION_INFO_DEF + 3 then

        player:SEND_POI(1596.34997558594, 274.683990478516, 99, 6, 0, "Undercity Cooking Trainer")
        player:SEND_GOSSIP_MENU(3530,_Creature:GetGUID())

    elseif action == GOSSIP_ACTION_INFO_DEF + 4 then

        player:SEND_POI(1488.5400390625, 280.194000244141, 99, 6, 0, "Undercity Enchanting Trainer")
        player:SEND_GOSSIP_MENU(3531,_Creature:GetGUID())

    elseif action == GOSSIP_ACTION_INFO_DEF + 5 then

        player:SEND_POI(1408.58996582031, 143.430999755859, 99, 6, 0, "Undercity Engineering Trainer")
        player:SEND_GOSSIP_MENU(3532,_Creature:GetGUID())

    elseif action == GOSSIP_ACTION_INFO_DEF + 6 then

        player:SEND_POI(1519.65002441406, 167.199005126953, 99, 6, 0, "Undercity First Aid Trainer")
        player:SEND_GOSSIP_MENU(3533,_Creature:GetGUID())

    elseif action == GOSSIP_ACTION_INFO_DEF + 7 then

        player:SEND_POI(1679.90002441406, 89.0226974487305, 99, 6, 0, "Undercity Fishing Trainer")
        player:SEND_GOSSIP_MENU(3534,_Creature:GetGUID())

    elseif action == GOSSIP_ACTION_INFO_DEF + 8 then

        player:SEND_POI(1558.08996582031, 349.369995117188, 99, 6, 0, "Undercity Herbalism Trainer")
        player:SEND_GOSSIP_MENU(3535,_Creature:GetGUID())

    elseif action == GOSSIP_ACTION_INFO_DEF + 9 then

        player:SEND_POI(1498.76000976562, 196.432998657227, 99, 6, 0, "Undercity Leatherworking Trainer")
        player:SEND_GOSSIP_MENU(3536,_Creature:GetGUID())

    elseif action == GOSSIP_ACTION_INFO_DEF + 10 then

        player:SEND_POI(1642.88000488281, 335.588012695313, 99, 6, 0, "Undercity Mining Trainer")
        player:SEND_GOSSIP_MENU(3537,_Creature:GetGUID())

    elseif action == GOSSIP_ACTION_INFO_DEF + 11 then

        player:SEND_POI(1498.60998535156, 196.466003417969, 99, 6, 0, "Undercity Skinning Trainer")
        player:SEND_GOSSIP_MENU(3538,_Creature:GetGUID())

    elseif action == GOSSIP_ACTION_INFO_DEF + 12 then

        player:SEND_POI(1689.55004882813, 193.022994995117, 99, 6, 0, "Undercity Tailoring Trainer")
        player:SEND_GOSSIP_MENU(3539,_Creature:GetGUID())

    end
end

m_scripts[scriptname]["GossipSelect"] = function(player, _Creature, sender, action)
    -- Serving guard_undercity/main menu
    if sender == GOSSIP_SENDER_MAIN then
        SendDefaultMenu_guard_undercity(player, _Creature, action)

    elseif sender == GOSSIP_SENDER_SEC_CLASSTRAIN then
        SendClassTrainerMenu_guard_undercity(player, _Creature, action)

    elseif sender == GOSSIP_SENDER_SEC_PROFTRAIN then
        SendProfTrainerMenu_guard_undercity(player, _Creature, action)

    elseif sender == GOSSIP_SENDER_SEC_BATTLEINFO then
        SendBattleMasterMenu_guard_undercity(player, _Creature, action)

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
