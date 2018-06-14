<head>
	<!--link rel="stylesheet" href="css/header.css"-->
	<link rel="shortcut icon" href="resources/img/favicon.png">

	<script src="js/header.js"></script>
	<script src="js/window.js"></script>
</head>

<header class="hnav hbox">

	<img id="site-logo" src="resources/img/burger-content.png" alt="">
	<h1>The Ultimate Burger Quiz</h1>

	<div class="spacer"></div>

	<?php

	require_once('php/autoload.php');

	if ( isConnected($user) )
	{
	?>
	<span id="hnav-right">
		<ul class="hnav-list">
			<li><a id="nav-menu" href="index.php">Menu</a></li>
			<li><a id="nav-quiz" href="gamesettings.php">Quiz</a></li>
			<li><a id="nav-ranking" href="ranking.php">Classements</a></li>
		</ul>

		<div class="triangle" id="marker"></div>
	</span>

	<div class="roundel" id="profile-selector">
		<img src="<?= $user->getPhoto(); ?>" alt="Photo de profil" id="profile-pic">
	</div>

	<div class="window vbox hidden" id="profile-modal">
		<div class="triangle" id="modal-toparrow"></div>

		<h2><?php echo $user->getUsername(); ?></h2>

		<div class="roundel centered" id="window-profile-pic">
			<img src="<?= $user->getPhoto(); ?>" alt="Photo de profil" id="profile-pic-big">
		</div>

		<a href="settings.php" class="button highlighted" id="btn-param">Paramétres</a>
		<a href="disconnect.php" class="button highlighted" id="btn-disconnect">Déconnexion</a>
	</div>

	<?php
	} else {
	?>
	
	<a id="btn-connect" class="button highlighted squared" href="connect.php">Connexion</a>

	<?php
	}
	?>
</header>