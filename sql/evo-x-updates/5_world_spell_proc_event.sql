ALTER TABLE db_version CHANGE COLUMN required_004_01_evo_X_world required_005_01_evo_X_world bit;

DELETE FROM spell_proc_event WHERE entry = 58375;
INSERT INTO spell_proc_event (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`) VALUES ('58375', '0', '4', '0', '512', '0', '16', '0', '0', '100', '0');
DELETE FROM spell_proc_event WHERE entry = 58388;
INSERT INTO spell_proc_event (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`) VALUES ('58388', '0', '4', '0', '64', '0', '16', '0', '0', '100', '0');