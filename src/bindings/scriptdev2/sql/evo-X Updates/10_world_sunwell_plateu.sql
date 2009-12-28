-- Muru Event
-- Muru and Entropius
UPDATE `creature_template` SET `lootid` = '25840', `mingold` = '2250000', `maxgold` = '2750000', `minhealth` = '5200000', `maxhealth` = '5200000', `mechanic_immune_mask` = '1073463287', `ScriptName` = 'boss_muru' WHERE `entry` IN (25741);

-- Dark Fiend
UPDATE `creature_template` SET `faction_A` = '14', `faction_H` = '14', `speed` = '0.6', `ScriptName` = 'dark_fiend' WHERE `entry` IN (25744); 

-- Void Sentinel
UPDATE `creature_template` SET `mechanic_immune_mask` = '1073463287', `AIName` = '', `ScriptName` = 'mob_voidsentinel' WHERE `entry` IN (25772); 
UPDATE `creature_template` SET `minmana` = '10000', `maxmana` = '10000' WHERE `entry` IN (25798, 25772);

-- Singularity
UPDATE creature_template SET `faction_A` = '14', `faction_H` = '14', `speed` = '1', `rank` = '1', `AIName` = '', `ScriptName` = 'mob_singularity' WHERE `entry` IN (25855); 