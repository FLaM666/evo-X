ALTER TABLE db_version CHANGE COLUMN required_001_01_evo_X_world required_002_01_evo_X_world bit;

CREATE TABLE `db_version_evo_x` (
  `version` varchar(120) NOT NULL,
  `evo_X_Full_Database_001` bit(1) DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED COMMENT='Used evo_x version notes';




