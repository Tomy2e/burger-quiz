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
		<link rel="stylesheet" type="text/css" href="css/menu.css">

		<script src="/js/main.js"></script>
	</head>
	<body>
		<?php require_once("templates/header.html"); ?>

		<!-- Page content -->
		<div class="main-content">
			<div class="hbox">
				<a class="button squared menu-item" id="settings" href="settings.php">
					<img src="/resources/img/settings.png" alt="">
					<h2>Options</h2>
				</a>

				<a class="button squared menu-item" id="play" href="launch.php.php">
					<img src="/resources/img/burger-content.png" alt="">
					<h2>Jouer</h2>
				</a>

				<a class="button squared menu-item" id="ranking" href="ranking.php">
					<img src="/resources/img/coupe.png" alt="">
					<h2>Classement</h2>
				</a>
			</div>
		</div>

		<?php require_once("templates/footer.html"); ?>
	</body>
</html>