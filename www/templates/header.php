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
		<img src="resources/img/users/vlad.png" alt="vlad" id="profile-pic">
	</div>

	<div class="window vbox hidden" id="profile-modal">
		<div class="triangle" id="modal-toparrow"></div>

		<h2>Vlad</h2>

		<div class="roundel centered" id="window-profile-pic">
			<img src="resources/img/users/vlad.png" alt="vlad" id="profile-pic-big">
		</div>

		<button id="btn-param">Paramétres</button>
		<button class="highlighted" id="btn-disconnect">Déconnexion</button>
	</div>

	<?php
	} else {
	?>
	
	<a id="btn-connect" class="button highlighted squared" href="connect.php">Connexion</a>

	<?php
	}
	?>
</header>