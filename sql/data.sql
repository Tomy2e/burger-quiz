-- phpMyAdmin SQL Dump
-- version 4.5.4.1deb2ubuntu2
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Jun 07, 2018 at 08:39 AM
-- Server version: 5.7.22-0ubuntu0.16.04.1
-- PHP Version: 7.0.30-0ubuntu0.16.04.1

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";

SET FOREIGN_KEY_CHECKS=0;

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `burgerquiz`
--

--
-- Dumping data for table `appartient_themes`
--

INSERT INTO `appartient_themes` (`id_theme`, `id_question`) VALUES
(2, 1),
(1, 2),
(2, 2),
(2, 3);

--
-- Dumping data for table `propositions`
--

INSERT INTO `propositions` (`id_proposition`, `libelle_proposition`, `reponse_proposition`, `active_proposition`, `id_question`) VALUES
(1, 'On peut le rouler', 3, 1, 1),
(2, 'On peut l\'aspirer', 2, 1, 1),
(3, 'A été ministre de la ville', 1, 1, 1),
(4, 'Ses ancêtres remontent à moins 500 avant J.C', 2, 1, 1),
(5, 'Il y a beaucoup de contrefaçons', 2, 1, 1),
(6, 'S\'entretient de façon journalière avec un aspirateur', 2, 1, 1),
(7, 'Matricule 265-449G', 1, 1, 1),
(8, 'A une époque, j\'ai vomi dessus', 2, 1, 1),
(9, 'A une bonne vision des choses', 2, 1, 2),
(10, 'A perdu le contrôle de son PC', 1, 1, 2),
(11, 'A perdu le contrôle de son année', 3, 1, 2),
(12, 'A eu le Voltaire à 5 points près', 1, 1, 2),
(13, 'S\'est baigné dans le lac', 2, 1, 2),
(14, 'Imbattable au beer pong', 2, 1, 2),
(15, 'On peut taper dessus', 3, 1, 3),
(16, 'Maire de Neuilly', 1, 1, 3),
(17, 'Il a une tête plate', 2, 1, 3),
(18, 'Il vaut mieux éviter de marcher dessus', 3, 1, 3),
(19, 'Il a le bout pointu', 2, 1, 3),
(20, 'Il en existe sans tête', 2, 1, 3),
(21, 'Il est très utile', 2, 1, 3);

--
-- Dumping data for table `questions`
--

INSERT INTO `questions` (`id_question`, `libelle1`, `libelle2`, `active_question`) VALUES
(1, 'Bernard Tapie', 'un tapis', 1),
(2, 'Ilyes', 'Bonal', 1),
(3, 'Nicolas Sarkozy', 'un clou', 1);

--
-- Dumping data for table `themes`
--

INSERT INTO `themes` (`id_theme`, `libelle_theme`, `photo_theme`) VALUES
(1, 'ISEN', ''),
(2, 'People', ''),
(3, 'Géopolitique', ''),
(4, 'Histoire', '');

--
-- Dumping data for table `utilisateurs`
--

INSERT INTO `utilisateurs` (`id_utilisateur`, `nom_utilisateur`, `password_utilisateur`, `age_utilisateur`, `email_utilisateur`, `photo_utilisateur`) VALUES
(2, 'tomy2e', '$2y$10$cXQAyx1YAItnwOLvE1f0weENivhhhJScBuW0ZUa4Gnpi/reblbz4q', 19, 'tomy2e@live.fr', 'images/photo.png');

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;

SET FOREIGN_KEY_CHECKS=1;
