/*
 Navicat Premium Data Transfer

 Source Server         : 192.168.12.91
 Source Server Type    : MySQL
 Source Server Version : 50726
 Source Host           : 192.168.12.91:3306
 Source Schema         : game_db

 Target Server Type    : MySQL
 Target Server Version : 50726
 File Encoding         : 65001

 Date: 16/07/2019 10:02:08
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for player
-- ----------------------------
DROP TABLE IF EXISTS `player`;
CREATE TABLE `player`  (
  `id` int(11) NOT NULL AUTO_INCREMENT COMMENT '自增主键',
  `player_id` bigint(20) NOT NULL COMMENT '角色id',
  `name` varchar(64) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL COMMENT '名称',
  `picture` varchar(255) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL COMMENT '头像',
  `faction` int(11) NOT NULL COMMENT '势力',
  `sex` int(11) NOT NULL COMMENT '性别',
  `prof` int(11) NOT NULL COMMENT '职业',
  `level` int(11) NOT NULL COMMENT '等级',
  `exp` int(11) NOT NULL COMMENT '经验',
  `vip_level` int(11) NOT NULL COMMENT 'vip',
  `offical_pos` int(11) NOT NULL COMMENT '官职',
  `power` int(11) NOT NULL COMMENT '战力',
  `cash` int(11) NOT NULL COMMENT '现金',
  `gold` int(11) NOT NULL COMMENT '元宝',
  `copper` int(11) NOT NULL COMMENT '铜币',
  `cp_zone_id` int(11) NOT NULL COMMENT '亲密空间id',
  `online_time` int(11) NOT NULL COMMENT '累计在线',
  `login_ts` bigint(20) NOT NULL COMMENT '最近登录时间戳',
  `logout_ts` bigint(20) NOT NULL COMMENT '最近登出时间戳',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 1 CHARACTER SET = latin1 COLLATE = latin1_swedish_ci ROW_FORMAT = Dynamic;

SET FOREIGN_KEY_CHECKS = 1;
