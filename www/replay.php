<?php

require_once('php/autoload.php');

if ( !isConnected($user) )
{
    header('Location: index.php');
    exit;
}

$partiesMgr = new PartiesManager;

$popular = $partiesMgr->fetchLatestParties();
?>
<!DOCTYPE html>
<html>
	<head>
		<meta charset="utf-8">
		<meta author="Gwenolé Leroy-Ferrec - Tomy Guichard">

		<title>Rejouer une partie - The Ultimate Burger Quiz</title>

		<link rel="stylesheet" type="text/css" href="css/main.css">
		<link rel="stylesheet" type="text/css" href="css/generic-theme.css">
		<link rel="stylesheet" type="text/css" href="css/fonts.css">
		<link rel="stylesheet" type="text/css" href="css/header.css">
		<link rel="stylesheet" type="text/css" href="css/footer.css">
		<link rel="stylesheet" type="text/css" href="css/podium.css">

		<script src="js/main.js"></script>
	</head>
	<body>
		<?php require_once("templates/header.php"); ?>

		<!-- Page content -->
		<div id="page-quiz" class="main-content">
			<h1>Rejouer une partie</h1>


			<section id="general-ranking">
				<div class="hbox">
					<h2>Parties les plus populaires</h2>
				</div>

				<table class="flat-table">
					<thead>
						<tr>
							<td>#</td>
							<td>Thèmes</td>
							<td>Difficulté</td>
							<td>Nombre de joueurs</td>
                            <td>Meilleur score</td>
                            <td>Action</td>
						</tr>
					</thead>
					<tbody>
						<?php foreach($popular as $entree) : ?>
						<tr>
							<td><?= $entree->getId(); ?></td>
							<td>
                                <?php
                                $themes = $entree->fetchThemes();
                                foreach($themes as $key=>$theme) : ?>
                                <?php echo $theme->getLibelle(); if($key != count($themes) - 1) { echo ", "; } ?>
                                <?php endforeach; ?>
                            </td>
                            <td>
                                <?php
                                switch($entree->getDifficulte()) {
                                    case 1: echo "facile"; break;
                                    case 2 : echo "moyen"; break;
                                    case 3 : echo "difficile"; break;
                                } ?>
                            </td>
							<td><?= $entree->getNbJoueurs(); ?></td>
                            <td><?php $best = $entree->fetchScores()[0]; ?>
                            <?= $best['nom_utilisateur']; ?>: <?= $best['score_final'] ;?></td>
                            <td><a href="game.php?id_partie=<?= $entree->getId(); ?>">Rejouer</a></td>
						</tr>
						<?php endforeach; ?>
					</tbody>
				</table>
			</section>
		</div>

		<?php require_once("templates/footer.php"); ?>
	</body>
</html>
