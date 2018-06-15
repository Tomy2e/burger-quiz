-- phpMyAdmin SQL Dump
-- version 4.6.6deb4
-- https://www.phpmyadmin.net/
--
-- Host: localhost:3306
-- Generation Time: Jun 15, 2018 at 02:34 PM
-- Server version: 10.1.26-MariaDB-0+deb9u1
-- PHP Version: 7.0.27-0+deb9u1

SET FOREIGN_KEY_CHECKS=0;
SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `burgerquiz_prod`
--

--
-- Dumping data for table `appartient_parties`
--

INSERT INTO `appartient_parties` (`id_partie`, `id_question`) VALUES
(1, 1),
(1, 3),
(1, 4),
(2, 3),
(2, 4),
(2, 5),
(3, 2),
(3, 6),
(3, 7),
(4, 2),
(4, 6),
(4, 7),
(5, 1),
(5, 3),
(5, 5),
(6, 1),
(6, 4),
(6, 5),
(7, 4),
(7, 8),
(7, 9),
(8, 1),
(8, 3),
(8, 9),
(9, 4),
(9, 8),
(9, 9),
(10, 4),
(10, 8),
(10, 9),
(11, 4),
(11, 8),
(11, 9),
(12, 2),
(12, 6),
(12, 7),
(13, 1),
(13, 4),
(13, 5),
(14, 4),
(14, 8),
(14, 9),
(15, 1),
(15, 4),
(15, 5),
(16, 6),
(16, 7),
(16, 10),
(17, 1),
(17, 4),
(17, 5),
(18, 6),
(18, 7),
(18, 10);

--
-- Dumping data for table `appartient_themes`
--

INSERT INTO `appartient_themes` (`id_theme`, `id_question`) VALUES
(1, 2),
(1, 6),
(1, 7),
(1, 10),
(1, 11),
(2, 1),
(2, 3),
(2, 4),
(2, 5),
(2, 12),
(3, 4),
(3, 8),
(3, 9),
(4, 1),
(4, 3),
(4, 4),
(4, 5),
(4, 9),
(4, 12);

--
-- Dumping data for table `parties`
--

INSERT INTO `parties` (`id_partie`, `date_partie`, `difficulte_partie`) VALUES
(1, '2018-06-15 09:38:23', 1),
(2, '2018-06-15 09:41:02', 1),
(3, '2018-06-15 10:32:51', 1),
(4, '2018-06-15 10:40:49', 1),
(5, '2018-06-15 10:40:52', 1),
(6, '2018-06-15 10:53:31', 1),
(7, '2018-06-15 11:12:30', 1),
(8, '2018-06-15 11:12:33', 1),
(9, '2018-06-15 11:12:36', 1),
(10, '2018-06-15 11:12:38', 1),
(11, '2018-06-15 11:12:40', 1),
(12, '2018-06-15 13:54:23', 2),
(13, '2018-06-15 14:00:57', 1),
(14, '2018-06-15 14:01:01', 1),
(15, '2018-06-15 14:01:03', 1),
(16, '2018-06-15 14:03:59', 1),
(17, '2018-06-15 14:17:51', 1),
(18, '2018-06-15 14:27:39', 2);

--
-- Dumping data for table `possede_scores`
--

INSERT INTO `possede_scores` (`id_utilisateur`, `id_partie`, `reponses_correctes`, `questions_total`, `temps_partie`, `score_final`, `date_score`) VALUES
(3, 1, 7, 9, 9, 1773, '2018-06-15 09:43:03'),
(3, 6, 9, 9, 26, 1716, '2018-06-15 10:54:04'),
(3, 11, 9, 9, 19, 1741, '2018-06-15 11:13:08'),
(4, 12, 5, 9, 22, 1440, '2018-06-15 13:55:08'),
(5, 17, 8, 9, 34, 1495, '2018-06-15 14:18:31');

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
(17, 'Il a une tête plate', 2, 1, 3),
(18, 'Il vaut mieux éviter de marcher dessus', 3, 1, 3),
(19, 'Il a le bout pointu', 2, 1, 3),
(20, 'Il en existe sans tête', 2, 1, 3),
(21, 'Il est très utile', 2, 1, 3),
(22, 'Se mange', 2, 1, 4),
(23, 'Dirige la Russie', 1, 1, 4),
(24, 'Vient d\'un pays nordique', 3, 1, 4),
(25, 'a un corps de louttre', 2, 1, 5),
(26, 'originaire de St Denis de la Réunion', 1, 1, 5),
(27, 'il creuse les terriers', 2, 1, 5),
(28, 'titre de Meilleur économiste de France', 1, 1, 5),
(29, 'il pèse entre 2 et 100 kilos', 3, 1, 5),
(30, 'il pond 2 à 3 oeufs', 2, 1, 5),
(31, 's\'accouple au printemps', 3, 1, 5),
(32, 'Paradoxus fut son premier nom', 2, 1, 5),
(33, 'Pratique la chasse à l\'ours', 1, 1, 4),
(34, 'on a d\'abord cru à une supercherie', 3, 1, 5),
(35, 'A bon goût', 2, 1, 4),
(36, 'Les meilleurs', 1, 1, 6),
(37, 'Ils savent faire des classes en PHP', 2, 1, 6),
(38, 'Ils auront leur année', 1, 1, 6),
(39, 'Ce sont de vrais Bretons', 2, 1, 6),
(40, 'Ils sont alcooliques', 3, 1, 6),
(41, 'Ils se disent les meilleurs', 3, 1, 6),
(42, 'Peut se faire cuisiner', 3, 1, 4),
(43, 'Pratique la chasse aux tchétchènes ', 1, 1, 4),
(44, 'On peut faire des classes', 3, 1, 7),
(45, 'C\'est un langage interprété', 3, 1, 7),
(46, 'Il s\'exécute généralement côté serveur', 1, 1, 7),
(47, 'Il faut se serrer la main avant', 2, 1, 8),
(48, 'On peut regretter amèrement de l\'avoir fait', 3, 1, 8),
(49, 'Ça peut soulager une nation entière', 3, 1, 8),
(50, 'Ca peut engendrer des conflits', 3, 1, 8),
(51, 'Il est très actif sur Twitter', 2, 1, 9),
(52, 'Il a fait exécuter son oncle', 1, 1, 9),
(53, 'Il a l\'arme nucléaire', 3, 1, 9),
(54, 'Ca peut tourner en conflit', 3, 1, 8),
(55, 'Le meilleur', 2, 1, 10),
(56, 'Il a reçu l\'ISEN d\'Or du meilleur club', 1, 1, 10),
(57, 'C\'est pratique pour manger', 1, 1, 10),
(58, 'Les délais y sont trés longs', 3, 1, 10),
(59, 'Ils se sont fait piquer du matos', 1, 1, 10),
(60, 'Ils ont piqué du matos', 2, 1, 10),
(61, 'Ils en bavent des maths', 3, 1, 11),
(62, 'Les meilleurs', 1, 1, 11),
(63, 'Ils sont alcooliques', 2, 1, 11),
(64, 'Ils maitrisent des compétences utiles à leur épanouissement futur dans le monde professionnel', 1, 1, 11),
(65, 'Sur une bougie, ça brûle mieux', 1, 1, 11),
(66, 'Il aime le rouge', 1, 1, 9),
(67, 'Il divise l\'opinion dans son pays', 2, 1, 9),
(68, 'Il détruit l\'opposition dans son pays', 1, 1, 9),
(69, 'Un avion', 3, 1, 12),
(70, 'Un hydravion', 1, 1, 12),
(71, 'Un oiseau', 1, 1, 12),
(72, 'Un oiseau mais bourré', 2, 1, 12),
(73, 'Un voleur', 1, 1, 12),
(74, 'Une voiture', 2, 1, 12),
(75, 'Un voleur de voitures', 3, 1, 12),
(76, 'Un tank', 2, 1, 12),
(77, 'Un voleur russe en tank', 3, 1, 12),
(78, 'Une fusée', 1, 1, 12),
(79, 'Un chauffard bourré sur un pont', 3, 1, 12);

--
-- Dumping data for table `questions`
--

INSERT INTO `questions` (`id_question`, `libelle1`, `libelle2`, `active_question`) VALUES
(1, 'Bernard Tapie', 'un tapis', 1),
(2, 'Ilyes', 'Bonal', 0),
(3, 'Nicolas Sarkozy', 'un clou', 1),
(4, 'Vladimir Poutine', 'une poutine', 1),
(5, 'Raymond Barre', 'un Ornithorynque', 1),
(6, 'CIR Rennes', 'CIR Brest', 1),
(7, 'PHP', 'JavaScript', 1),
(8, 'Un pet', 'la paix', 1),
(9, 'Kim Jong Un', 'Donal Trump', 1),
(10, 'Club Foyer', 'Club Elec', 1),
(11, 'CIR', 'CSI', 1),
(12, 'Ca vole', 'ca roule', 1);

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
(3, 'tomy', '$2y$10$m86x1nOxfQTXpstV6TFdxOcNeRIF/.KdAYw6T5TZM9B6phW5gTIFe', 19, 'tomy2e@live.fr', 'resources/img/users/default.png'),
(4, 'RaskarkapaK', '$2y$10$QjVKYnPCPYGK9MKRt3S74ecZPGMDwXUnFjRGEAVLTlGYkkSgnGJe2', 42, 'raskarkapak@crou.fr', 'resources/img/users/default.png'),
(5, 'user', '$2y$10$kkAvBbewSG.FWdUwIddeLej1DGybc59F50fwTELNIVZVtKSsuaUqG', 20, 'user@user.com', 'resources/img/users/default.png');
SET FOREIGN_KEY_CHECKS=1;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
