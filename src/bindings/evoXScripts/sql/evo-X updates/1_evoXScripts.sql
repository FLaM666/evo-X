DELETE FROM script_texts WHERE entry BETWEEN -1603017 AND -1603000;
INSERT INTO script_texts VALUES
(-1603000, "New toys? For me? I promise I won't break them this time!", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 15724, 1, 0, 0, "XT-002 Aggro"),
(-1603001, "NO! NO! NO! NO! NO!", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 15727, 1, 0, 0, "XT-002 Tympanic Tantrum"),
(-1603002, "I... I think I broke it.", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 15728, 1, 0, 0, "XT-002 Slay 1"),
(-1603003, "I guess it doesn't bend that way.", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 15729, 1, 0, 0, "XT-002 Slay 2"),
(-1603004, "So tired. I will rest for just a moment!", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 15725, 1, 0, 0, "XT-002 Heart Opened"),
(-1603005, "I'm ready to play!", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 15726, 1, 0, 0, "XT-002 Heart Closed"),
(-1603006, "Time for a new game! My old toys will fight my new toys!", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 15732, 1, 0, 0, "XT-002 Adds"),
(-1603007, "I'm tired of these toys. I don't want to play anymore!", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 15730, 1, 0, 0, "XT-002 Berserk"),
(-1603008, "You are bad... Toys... Very... Baaaaad!", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 15731, 1, 0, 0, "XT-002 Death"),
(-1603009, "Hostile entities detected. Threat assessment protocol active. Primary target engaged. Time minus thirty seconds to re-evaluation.", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 15506, 1, 0, 0, "Flame Leviathan Aggro"),
(-1603010, "Total systems failure. Defense protocols breached. Leviathan Unit shutting down.", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 15520, 1, 0, 0, "Flame Leviathan Death"),
(-1603011, "Threat assessment routine modified. Current target threat level: zero. Acquiring new target.", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 15521, 1, 0, 0, "Flame Leviathan Slay"),
(-1603012, "You will suffer for this trespass!", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 15552, 1, 0, 0, "Hodir Aggro"),
(-1603013, "I... I am released from his grasp... at last.", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 15557, 1, 0, 0, "Hodir Death"),
(-1603014, "Tragic. To come so far, only to fail.", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 15553, 1, 0, 0, "Hodir Slay 1"),
(-1603015, "Welcome to the endless winter.", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 15554, 1, 0, 0, "Hodir Slay 2"),
(-1603016, "Winds of the north consume you!", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 15555, 1, 0, 0, "Hodir Flash Freeze"),
(-1603017, "<Furious Roar>", NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 15556, 1, 0, 0, "Hodir Frozen Blows");

/*
Navicat MySQL Data Transfer

Source Server         : Salja
Source Server Version : 50137
Source Host           : localhost:3306
Source Database       : scriptdev2

Target Server Type    : MYSQL
Target Server Version : 50137
File Encoding         : 65001

Date: 2009-12-28 22:25:42
*/

SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for `evoXScripts_db_version`
-- ----------------------------
DROP TABLE IF EXISTS `sd2_db_version`;
CREATE TABLE `evoXScripts_version` (
  `version` varchar(255) NOT NULL DEFAULT '' COMMENT 'Database version string'
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of evoXScripts_version
-- ----------------------------
INSERT INTO `evoXScripts_version` VALUES ('evoXScripts (for evo-X Emu 060) ');