-- MySQL dump 10.13  Distrib 5.5.41, for debian-linux-gnu (x86_64)
--
-- Host: 0.0.0.0    Database: pset7
-- ------------------------------------------------------
-- Server version	5.5.41-0ubuntu0.14.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `history`
--

DROP TABLE IF EXISTS `history`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `history` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `user_id` int(10) unsigned NOT NULL,
  `transaction` varchar(10) NOT NULL,
  `symbol` varchar(10) NOT NULL,
  `shares` int(10) unsigned NOT NULL,
  `price` int(10) unsigned NOT NULL,
  `time` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=24 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `history`
--

LOCK TABLES `history` WRITE;
/*!40000 ALTER TABLE `history` DISABLE KEYS */;
INSERT INTO `history` VALUES (1,0,'BUY','AAPL',2,121,'2015-11-03 00:01:08'),(2,0,'SELL','CAKE',10,49,'2015-11-03 00:01:17'),(3,0,'BUY','NFLX',5,108,'2015-11-03 00:01:22'),(4,0,'BUY','CAKE',10,49,'2015-11-03 00:01:28'),(5,16,'SELL','GOOGL',12,748,'2015-11-03 00:04:09'),(6,16,'BUY','GOOGL',5,748,'2015-11-03 00:06:43'),(7,16,'BUY','GOOGL',5,748,'2015-11-03 00:07:17'),(8,16,'BUY','AAPL',1,121,'2015-11-03 00:07:33'),(9,16,'SELL','NFLX',5,108,'2015-11-03 00:07:57'),(10,16,'BUY','CS',20,25,'2015-11-03 01:31:25'),(11,16,'BUY','GS',2,190,'2015-11-03 01:31:35'),(12,16,'BUY','FB',20,103,'2015-11-03 01:31:44'),(13,16,'SELL','CS',20,25,'2015-11-03 01:32:36'),(14,16,'BUY','TWTR',10,29,'2015-11-03 01:33:17'),(15,16,'BUY','SBUX',2,62,'2015-11-03 01:50:32'),(16,16,'SELL','FB',20,103,'2015-11-03 02:03:14'),(17,16,'SELL','AAPL',4,121,'2015-11-03 02:56:00'),(18,16,'SELL','GS',2,190,'2015-11-03 02:56:09'),(19,16,'BUY','MS',2,33,'2015-11-03 02:57:05'),(20,16,'BUY','GM',2,36,'2015-11-03 02:57:24'),(21,16,'BUY','FB',2,103,'2015-11-03 02:58:11'),(22,16,'BUY','MAR',10,77,'2015-11-03 04:22:03'),(23,16,'SELL','FB',2,103,'2015-11-03 04:22:23');
/*!40000 ALTER TABLE `history` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `portfolios`
--

DROP TABLE IF EXISTS `portfolios`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `portfolios` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `user_id` int(255) unsigned NOT NULL,
  `symbol` varchar(7) NOT NULL,
  `shares` int(255) unsigned NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `user_id` (`user_id`,`symbol`)
) ENGINE=InnoDB AUTO_INCREMENT=51 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `portfolios`
--

LOCK TABLES `portfolios` WRITE;
/*!40000 ALTER TABLE `portfolios` DISABLE KEYS */;
INSERT INTO `portfolios` VALUES (4,14,'CMB',15),(15,14,'SHAK',15),(18,14,'AAPL',3),(20,14,'GOOGL',2),(23,14,'BK',20),(25,14,'BAC',100),(26,14,'',10),(27,14,'APPL',2),(29,14,'SPB',50),(37,16,'CAKE',10),(38,16,'GOOGL',10),(44,16,'TWTR',10),(45,16,'SBUX',2),(46,16,'MS',2),(47,16,'GM',2),(49,16,'MAR',10),(50,16,'F',0);
/*!40000 ALTER TABLE `portfolios` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `users`
--

DROP TABLE IF EXISTS `users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `users` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `cash` decimal(65,4) unsigned DEFAULT '0.0000',
  `username` varchar(255) NOT NULL,
  `hash` varchar(255) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `username` (`username`)
) ENGINE=InnoDB AUTO_INCREMENT=17 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `users`
--

LOCK TABLES `users` WRITE;
/*!40000 ALTER TABLE `users` DISABLE KEYS */;
INSERT INTO `users` VALUES (1,20691.0000,'andi','$2y$10$c.e4DK7pVyLT.stmHxgAleWq4yViMmkwKz3x8XCo4b/u3r8g5OTnS'),(2,20691.0000,'caesar','$2y$10$0p2dlmu6HnhzEMf9UaUIfuaQP7tFVDMxgFcVs0irhGqhOxt6hJFaa'),(3,20691.0000,'eli','$2y$10$COO6EnTVrCPCEddZyWeEJeH9qPCwPkCS0jJpusNiru.XpRN6Jf7HW'),(4,20691.0000,'hdan','$2y$10$o9a4ZoHqVkVHSno6j.k34.wC.qzgeQTBHiwa3rpnLq7j2PlPJHo1G'),(5,20691.0000,'jason','$2y$10$ci2zwcWLJmSSqyhCnHKUF.AjoysFMvlIb1w4zfmCS7/WaOrmBnLNe'),(6,20691.0000,'john','$2y$10$dy.LVhWgoxIQHAgfCStWietGdJCPjnNrxKNRs5twGcMrQvAPPIxSy'),(7,20691.0000,'levatich','$2y$10$fBfk7L/QFiplffZdo6etM.096pt4Oyz2imLSp5s8HUAykdLXaz6MK'),(8,20691.0000,'rob','$2y$10$3pRWcBbGdAdzdDiVVybKSeFq6C50g80zyPRAxcsh2t5UnwAkG.I.2'),(9,20691.0000,'skroob','$2y$10$395b7wODm.o2N7W5UZSXXuXwrC0OtFB17w4VjPnCIn/nvv9e4XUQK'),(10,20691.0000,'zamyla','$2y$10$UOaRF0LGOaeHG4oaEkfO4O7vfI34B1W23WqHr9zCpXL68hfQsS3/e'),(14,12198.9400,'dionhagan','$2y$10$z1Y3EVCOXn9sikW1DfafY.QdJco2bAbVgYzETIwEiPzXlD/.e.3gW'),(15,20691.0000,'nicasia','$2y$10$yaMxVlWlio1n72y7Zc6CFOjdzGemxuYEoFrJdTt2o7PHhkkM.Egku'),(16,13545.7200,'marina','$2y$10$cuona1lsiL4QSzvgwAy2Xe8sDKE8Kjdy5h3E1G3X1yGEohqYyoZYi');
/*!40000 ALTER TABLE `users` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2015-11-06 16:21:44
