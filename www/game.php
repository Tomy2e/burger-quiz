<?php

require_once('php/autoload.php');

if ( !isConnected($user) )
{
    header('Location: index.php');
    exit;
}
?>
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
        <link rel="stylesheet" type="text/css" href="css/notify.css">

        <script src="js/main.js"></script>
        <script src="js/ajax.js"></script>
        <script src="js/notify.js"></script>
		<script src="js/game.js"></script>
	</head>
	<body>
		<?php require_once("templates/header.php"); ?>

		<!-- Page content -->
		<div id="page-quiz" class="main-content centered">

            <div id="notify-container"></div>

            <div class="fullscreen selected" id="game-ui">
                
                <div class="vbox" id="question-zone">
                    <ul class="steps-indicator">
                        <li id="step1"></li>
                        <li id="step2"></li>
                        <li id="step3"></li>
                    </ul>
                    
                    <h2 id="question">...</h2>
                    <h1 id="affirmation">Préparation de la sauce...</h1>
                </div>
                
                <div class="progress-bar">
                    <div id="remaining-time" class="progress-bar-indicator"></div>
                </div>

                <div id="choices" class="hbox">
                    <button id="choice1" class="choice squared flat">Loading...</button>
                    <button id="choice2" class="choice squared flat">Loading...</button>
                    <button id="both" class="roundel">Les deux</button>
                </div>
            </div>

            <div class="fullscreen" id="answer-true">
                <h1>Bien joué !</h1>
                <img src="resources/img/burger-content.png" alt="Là c'est une image de burger content mais vous pouvez pas la voir pour une raison quelconque">

                <div class="score-box">
                    <div id="score">
                        <h2>666</h2>
                        <span>points</span>
                    </div>
                    <h3>(+42)</h3>
                </div>

                <button class="next-question">Question suivante</button>
            </div>

            <div class="fullscreen" id="answer-false">
                <h1>Perdu !</h1>
                <span id="correct-answer">La réponse était : </span>

                <img src="resources/img/burger-triste.png" alt="Là c'est une image de burger triste mais vous pouvez pas la voir pour une raison quelconque">

                <div class="score-box">
                    <div id="score">
                        <h2>666</h2>
                        <span>points</span>
                    </div>
                    <h3>(+0)</h3>
                </div>

                <button class="next-question">Question suivante</button>

            </div>

            <div class="fullscreen" id="results">
                <h1>Là normalement c'est un écran de résultats</h1>
                <h2>Mais vous ne pouvez pas le voir parce qu'il n'est pas encore fait</h2>
                <img src="resources/img/imagedequalité.jpg" alt="image de qualité.jpeg">
                <h3>En attendant je vous propose cette image d'un homme respirant la joie de vivre afin de vous réconforter</h3>
            </div>
		</div>

		<?php require_once("templates/footer.php"); ?>
	</body>
</html>