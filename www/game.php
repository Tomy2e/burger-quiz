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
		<link rel="stylesheet" type="text/css" href="css/game.css">

        <script src="js/main.js"></script>
        <script src="js/ajax.js"></script>
		<script src="js/game.js"></script>
	</head>
	<body>
		<?php require_once("templates/header.html"); ?>

		<!-- Page content -->
		<div id="page-quiz" class="main-content centered">
            <div class="fullscreen selected" id="game-ui">
                <div class="vbox" id="question-zone">
                    <ul class="steps-indicator">
                        <li id="step1"></li>
                        <li id="step2"></li>
                        <li id="step3"></li>
                    </ul>

                    <h2 id="question">Bernard Tapie, un tapis ou les deux ?</h2>
                    <h1 id="affirmation">Il peut voler</h1>
                </div>

                <div id="choices" class="hbox">
                    <button id="choice1" class="choice squared flat">Bernard Tapie</button>
                    <button id="choice2" class="choice squared flat">Un tapis</button>
                    <button id="both" class="roundel">Les deux</button>
                </div>

                <div class="progress-bar" id"timer-bar">
                    <div id="progress"></div>
                </div>
            </div>

            <div class="fullscreen" id="answer-true">
                <h1>Bien joué !</h1>
            </div>

            <div class="fullscreen" id="answer-false">
                <h1>Perdu !</h1>
            </div>
		</div>

		<?php require_once("templates/footer.html"); ?>
	</body>
</html>