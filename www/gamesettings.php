<!DOCTYPE html>

<?php
require_once('php/autoload.php');

if ( !isConnected($user) )
{
	header('Location: connect.php');
	exit;
}
?>
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

		<script src="js/main.js"></script>
		<script src="js/slider-button.js"></script>
		<script src="js/game-settings.js"></script>
	</head>
	<body>
		<?php require_once("templates/header.php"); ?>

		<!-- Page content -->
		<div id="page-quiz" class="main-content centered">

			<h1>Thème</h1>
			<ul class="hbox hnav-list" id="theme-list">

				<?php
					require_once('php/config.php');
					require_once('php/Database.class.php');
					require_once('php/Theme.class.php');

					$db = Database::getInstance();
					
					$themes = Theme::fetchAllThemes();

					foreach ($themes as $theme) {
						echo '<li id="'.$theme->getId().'" class="theme-list-item">';
							echo '<img class="theme-cover" src="'.( ($theme->getPhoto() == "") ? '/resources/img/imagedequalité.jpg"' : $theme->getPhoto() ).' alt="image de qualité.jpeg">';
							echo '<h3>'.$theme->getLibelle().'</h3>';
						echo '</li>';
					}

				?>
				
				<!--li id="0" class="theme-list-item">
					<img class="theme-cover" src="/resources/img/imagedequalité.jpg" alt="image de qualité.jpeg">
					<h3>ISEN</h3>
				</li>
				<li id="1" class="theme-list-item">
					<img class="theme-cover" src="/resources/img/imagedequalité.jpg" alt="image de qualité.jpeg">
					<h3>People</h3>
				</li>
				<li id="2" class="theme-list-item">
					<img class="theme-cover" src="/resources/img/imagedequalité.jpg" alt="image de qualité.jpeg">
					<h3>Science</h3>
				</li>
				<li id="3" class="theme-list-item">
					<img class="theme-cover" src="/resources/img/imagedequalité.jpg" alt="image de qualité.jpeg">
					<h3>Histoire</h3>
				</li-->
			</ul>

			<h1>Difficulté</h1>
			<div class="slider-button" id="difficulty">
				<ul class="hnav-list">
					<li id="1" class="selected">Facile</li>
					<li id="2">Moyen</li>
					<li id="3">Difficile</li>
				</ul>

				<div id="slider-button-marker"></div>
			</div>
			
			<a id="play" class="button squared highlighted disabled" href="game.php">Jouer !</a>
			<a id="replay" href="game.php">Rejouer une partie</a>
		</div>

		<?php require_once("templates/footer.php"); ?>
	</body>
</html>