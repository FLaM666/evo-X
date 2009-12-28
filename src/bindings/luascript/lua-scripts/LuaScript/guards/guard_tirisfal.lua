-- Mango Style guard_tirisfal script
-- Converted by SinnerG

-- Create the Mango Script Base object
Guard_Tirisfal = Mango.Scripts.Create('guard_tirisfal');
Guard_Tirisfal:ForceLUA(); -- Don't use the CPP version if valid

-- Function prototypes (to keep it clean)
local Guard_Tirisfal_GossipHello
local Guard_Tirisfal_GossipSelect
local Guard_Tirisfal_SendDefaultMenu
local Guard_Tirisfal_SendClassTrainerMenu
local Guard_Tirisfal_SendProfTrainerMenu
          
-- The actual functions
-- Send the first menu (with the selections)
function Guard_Tirisfal_GossipHello(player,_Creature)
    -- TODO this is used by  guard_default_ai , if script is not part of it anymore pls remove this
	guard_default_ai_Gossip_Hello(player,_Creature)
	
	player:ADD_GOSSIP_ITEM( 6, "Bank"				, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1)
	player:ADD_GOSSIP_ITEM( 2, "Bat Handler"		, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2)
	player:ADD_GOSSIP_ITEM( 1, "The Inn"			, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3)
	player:ADD_GOSSIP_ITEM( 5, "Stable Master"		, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4)
	player:ADD_GOSSIP_ITEM( 3, "Class Trainer"		, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5)
	player:ADD_GOSSIP_ITEM( 3, "Profession Trainer"	, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6)
	player:SEND_GOSSIP_MENU(2593,_Creature:GetGUID())

return RETURN_OK
end
          
function Guard_Tirisfal_GossipSelect(player, _Creature, sender, action)
	if sender == GOSSIP_SENDER_MAIN then
		Guard_Tirisfal_SendDefaultMenu(player, _Creature, action)

	elseif sender == GOSSIP_SENDER_SEC_CLASSTRAIN then
		Guard_Tirisfal_SendClassTrainerMenu(player, _Creature, action)

	elseif sender == GOSSIP_SENDER_SEC_PROFTRAIN then
		Guard_Tirisfal_SendProfTrainerMenu_(player, _Creature, action)

	end
return RETURN_OK
end

function Guard_Tirisfal_SendDefaultMenu(player, _Creature, action)
	if action == GOSSIP_ACTION_INFO_DEF + 1 then --Bank

		player:SEND_GOSSIP_MENU(4074,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 2 then --bat handler

		player:SEND_GOSSIP_MENU(4075,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 3 then --Inn

		player:SEND_POI(2246.68, 241.89, 6, 6, 0, "Gallows` End Tavern")
		player:SEND_GOSSIP_MENU(4076,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 4 then --Stable Master

		player:SEND_POI(2267.66, 319.32, 6, 6, 0, "Morganus")
		player:SEND_GOSSIP_MENU(5978,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 5 then --Class trainer

		player:ADD_GOSSIP_ITEM( 3, "Mage"				, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 1)
		player:ADD_GOSSIP_ITEM( 3, "Priest"				, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 2)
		player:ADD_GOSSIP_ITEM( 3, "Rogue"				, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 3)
		player:ADD_GOSSIP_ITEM( 3, "Warlock"			, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 4)
		player:ADD_GOSSIP_ITEM( 3, "Warrior"			, GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 5)
		player:SEND_GOSSIP_MENU(4292,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 6 then --Profession trainer

		player:ADD_GOSSIP_ITEM( 3, "Alchemy"			, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 1)
		player:ADD_GOSSIP_ITEM( 3, "Blacksmithing"		, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 2)
		player:ADD_GOSSIP_ITEM( 3, "Cooking"			, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 3)
		player:ADD_GOSSIP_ITEM( 3, "Enchanting"			, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 4)
		player:ADD_GOSSIP_ITEM( 3, "Engineering"		, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 5)
		player:ADD_GOSSIP_ITEM( 3, "First Aid"			, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 6)
		player:ADD_GOSSIP_ITEM( 3, "Fishing"			, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 7)
		player:ADD_GOSSIP_ITEM( 3, "Herbalism"			, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 8)
		player:ADD_GOSSIP_ITEM( 3, "Leatherworking"		, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 9)
		player:ADD_GOSSIP_ITEM( 3, "Mining"				, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 10)
		player:ADD_GOSSIP_ITEM( 3, "Skinning"			, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 11)
		player:ADD_GOSSIP_ITEM( 3, "Tailoring"			, GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 12)
		player:SEND_GOSSIP_MENU(4300,_Creature:GetGUID())
	end
end

function Guard_Tirisfal_SendClassTrainerMenu(player, _Creature, action)
	if action == GOSSIP_ACTION_INFO_DEF + 1 then --Mage

		player:SEND_POI(2259.18, 240.93, 6, 6, 0, "Cain Firesong")
		player:SEND_GOSSIP_MENU(4077,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 2 then --Priest

		player:SEND_POI(2259.18, 240.93, 6, 6, 0, "Dark Cleric Beryl")
		player:SEND_GOSSIP_MENU(4078,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 3 then --Rogue

		player:SEND_POI(2259.18, 240.93, 6, 6, 0, "Marion Call")
		player:SEND_GOSSIP_MENU(4079,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 4 then --Warlock

		player:SEND_POI(2259.18, 240.93, 6, 6, 0, "Rupert Boch")
		player:SEND_GOSSIP_MENU(4080,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 5 then --Warrior

		player:SEND_POI(2256.48, 240.32, 6, 6, 0, "Austil de Mon")
		player:SEND_GOSSIP_MENU(4081,_Creature:GetGUID())
	end
end

function Guard_Tirisfal_SendProfTrainerMenu(player, _Creature, action)
	if action == GOSSIP_ACTION_INFO_DEF + 1 then --Alchemy

		player:SEND_POI(2263.25, 344.23, 6, 6, 0, "Carolai Anise")
		player:SEND_GOSSIP_MENU(4082,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 2 then --Blacksmithing

		player:SEND_GOSSIP_MENU(4083,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 3 then --Cooking

		player:SEND_GOSSIP_MENU(4084,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 4 then --Enchanting

		player:SEND_POI(2250.35, 249.12, 6, 6, 0, "Vance Undergloom")
		player:SEND_GOSSIP_MENU(4085,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 5 then --Engineering

		player:SEND_GOSSIP_MENU(4086,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 6 then --First Aid

		player:SEND_POI(2246.68, 241.89, 6, 6, 0, "Nurse Neela")
		player:SEND_GOSSIP_MENU(4087,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 7 then --Fishing

		player:SEND_POI(2292.37, -10.72, 6, 6, 0, "Clyde Kellen")
		player:SEND_GOSSIP_MENU(4088,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 8 then --Herbalism

		player:SEND_POI(2268.21, 331.69, 6, 6, 0, "Faruza")
		player:SEND_GOSSIP_MENU(4089,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 9 then --Leatherworking

		player:SEND_POI(2027, 78.72, 6, 6, 0, "Shelene Rhobart")
		player:SEND_GOSSIP_MENU(4090,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 10 then --Mining

		player:SEND_GOSSIP_MENU(4091,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 11 then --Skinning

		player:SEND_POI(2027, 78.72, 6, 6, 0, "Rand Rhobart")
		player:SEND_GOSSIP_MENU(4092,_Creature:GetGUID())

	elseif action == GOSSIP_ACTION_INFO_DEF + 12 then --Tailoring

		player:SEND_POI(2160.45, 659.93, 6, 6, 0, "Bowen Brisboise")
		player:SEND_GOSSIP_MENU(4093,_Creature:GetGUID())
	end
end

-- Assign the functions
Guard_Tirisfal.GossipHello = Guard_Tirisfal_GossipHello;
Guard_Tirisfal.GossipSelect= Guard_Tirisfal_GossipSelect;

-- Activate (run) the script
Guard_Tirisfal:Activate();
