<?php
require_once('php/autoload.php');

$scoresMgr = new ScoresManager;

$classementGeneral = $scoresMgr->getClassementGeneral();

?>
<!DOCTYPE html>
<html>
	<head>
		<meta charset="utf-8">
		<meta author="Gwenolé Leroy-Ferrec - Tomy Guichard">

		<title>Classements - The Ultimate Burger Quiz</title>

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
		<div id="page-ranking" class="main-content">
			<h1>Classements</h1>

			<?php
			if (count($classementGeneral) >= 3)
			{
			?>
			<section id="top3">
				<h1>Meilleurs joueurs</h1>
				<div class="podium hbox">
					<div id="second">
						<div class="user roundel">
							<?php

							echo '<img src="'.$classementGeneral[1]['photo_utilisateur'].'" alt="Vlad">';
							echo '<h2>'.$classementGeneral[1]['nom_utilisateur'].'</h2>';
							echo '<span class="topscore">'.$classementGeneral[1]['total_points'].'<span>';
							?>
						</div>

						<div class="step">
							<h2>2</h2>
						</div>
					</div>

					<div id="first">
						<div class="user roundel">
							<?php

							echo '<img src="'.$classementGeneral[0]['photo_utilisateur'].'" alt="Vlad">';
							echo '<h2>'.$classementGeneral[0]['nom_utilisateur'].'</h2>';
							echo '<span class="topscore">'.$classementGeneral[0]['total_points'].'<span>';
							?>
						</div>

						<div class="step">
							<h2>1</h2>
						</div>
					</div>

					<div id="third">
						<div class="user roundel">
							<?php

							echo '<img src="'.$classementGeneral[2]['photo_utilisateur'].'" alt="Vlad">';
							echo '<h2>'.$classementGeneral[2]['nom_utilisateur'].'</h2>';
							echo '<span class="topscore">'.$classementGeneral[2]['total_points'].'<span>';
							?>
						</div>

						<div class="step">
							<h2>3</h2>
						</div>
					</div>
				</div>
			</section>
			<?php } ?>

			<section id="general-ranking">
				<div class="hbox">
					<h2>Classement général</h2>
					<div id="rank-sort">
						<span>Classer par </span>
						<select name="sort-mode" id="sort-selector">
							<option value="score" default>score</option>
							<option value="topscore">top score</option>
							<option value="toptime">top temps</option>
						</select>
					</div>
				</div>

				<table class="flat-table">
					<thead>
						<tr>
							<td>#</td>
							<td>Joueur</td>
							<td>Top score</td>
							<td>Top temps</td>
							<td>Total</td>
						</tr>
					</thead>
					<tbody>
						<?php foreach($classementGeneral as $key => $entree) : ?>
						<tr>
							<td><?= $key + 1; ?></td>
							<td><?= $entree['nom_utilisateur']; ?></td>
							<td><?= $entree['top_score']; ?></td>
							<td><?= $entree['temps_min']; ?>s</td>
							<td><?= $entree['total_points']; ?></td>
						</tr>
						<?php endforeach; ?>
					</tbody>
				</table>
			</section>
		</div>

		<?php require_once("templates/footer.php"); ?>
	</body>
</html>
