-- Scripts for Mangos-Lua scripting library

-- guards
UPDATE `creature_template` SET `ScriptName` = 'guard_stormwind' WHERE `entry` = 1423;
-- misc

-- Bom'bay
UPDATE `creature_template` SET `ScriptName` = 'misc_bombay' WHERE `entry` = 10578;
UPDATE `creature_template` SET `npcflag` = '65' WHERE `entry` =10578;
INSERT INTO `npc_text` VALUES (150000, 'Ya mon, I be Gadrin''s assistant. Dis here volunteer work be my way of gettin through Witch Doctor School. Since you help him, I help ya for free. Whatcha need fixin?', 'Ya mon, I be Gadrin''s assistant. Dis here volunteer work be my way of gettin through Witch Doctor School. Since you help him, I help ya for free. Whatcha need fixin?', 0, 1, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0, '', '', 0, 0, 0, 0, 0, 0, 0, 0);

