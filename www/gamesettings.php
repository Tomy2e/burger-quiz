<!DOCTYPE html>
<html>
	<head>
		<meta charset="utf-8">
		<meta author="Gwenolé Leroy-Ferrec - Tomy Guichard">

		<title>The Ultimate Burger Quiz</title>

		<link rel="stylesheet" type="text/css" href="css/main.css">
		<link rel="stylesheet" type="text/css" href="css/generic-theme.css">
		<link rel="stylesheet" type="text/css" href="css/fonts.css">
		<link rel="stylesheet" type="text/css" href="css/header.css">
		<link rel="stylesheet" type="text/css" href="css/footer.css">
		<link rel="stylesheet" type="text/css" href="css/gamesettings.css">

		<script src="/js/main.js"></script>
		<script src="js/slider-button.js"></script>
	</head>
	<body>
		<?php require_once("templates/header.html"); ?>

		<!-- Page content -->
		<div id="page-quiz" class="main-content centered">

			<h1>Thème</h1>
			<ul class="hbox hnav-list" id="theme-list">
				<li id="isen" class="theme-list-item">
					<img class="theme-cover" src="/resources/img/imagedequalité.jpg" alt="image de qualité.jpeg">
					<h3>ISEN</h3>
				</li>
				<li id="people" class="theme-list-item">
					<img class="theme-cover" src="/resources/img/imagedequalité.jpg" alt="image de qualité.jpeg">
					<h3>People</h3>
				</li>
				<li class="theme-list-item">
					<img class="theme-cover" src="/resources/img/imagedequalité.jpg" alt="image de qualité.jpeg">
					<h3>Science</h3>
				</li>
				<li class="theme-list-item">
					<img class="theme-cover" src="/resources/img/imagedequalité.jpg" alt="image de qualité.jpeg">
					<h3>Histoire</h3>
				</li>
			</ul>

			<h1>Difficulté</h1>
			<div class="slider-button" id="difficulty">
				<ul class="hnav-list">
					<li class="selected">Facile</li>
					<li>Moyen</li>
					<li>Difficile</li>
				</ul>

				<div id="slider-button-marker"></div>
			</div>
			
			<a id="play" class="button flat highlighted" href="game.php">Jouer !</a>
			<a id="replay" href="game.php">Rejouer une partie</a>

		</div>

		<?php require_once("templates/footer.html"); ?>
	</body>
</html>