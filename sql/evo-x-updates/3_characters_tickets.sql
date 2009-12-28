ALTER TABLE character_db_version CHANGE COLUMN required_001_01_evo_X_characters required_002_01_evo_X_characters bit;

DROP TABLE IF EXISTS `character_ticket`;
CREATE TABLE `tickets` (
  `guid` int(10) NOT NULL auto_increment,
  `playerGuid` int(11) unsigned NOT NULL default '0',
  `name` varchar(15) NOT NULL,
  `message` text NOT NULL,
  `createtime` int(10) NOT NULL default '0',
  `map` int NOT NULL DEFAULT '0',
  `posX` float NOT NULL DEFAULT '0',
  `posY` float NOT NULL DEFAULT '0',
  `posZ` float NOT NULL DEFAULT '0',
  `timestamp` int(10) NOT NULL default '0',
  `closed` int(10) NOT NULL default '0',
  `assignedto` int(10) NOT NULL default '0',
  `comment` text NOT NULL,
  PRIMARY KEY  (`guid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT='Ticket System';

--
-- Dumping data for table `tickets`
--

LOCK TABLES `tickets` WRITE;
/*!40000 ALTER TABLE `tickets` DISABLE KEYS */;
/*!40000 ALTER TABLE `tickets` ENABLE KEYS */;
UNLOCK TABLES;