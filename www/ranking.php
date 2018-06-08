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

		<script src="/js/main.js"></script>
	</head>
	<body>
		<?php require_once("templates/header.html"); ?>

		<!-- Page content -->
		<div id="page-ranking" class="main-content">
			<h1>Classements</h1>
			<section id="top3">
				<h1>Meilleurs joueurs</h1>
				<div class="podium hbox">
					<div id="second">
						<div class="user roundel">
							<img src="resources/img/users/vlad.png" alt="Vlad">
							<h2>Vlad</h2>
							<span class="topscore">15252<span>
						</div>

						<div class="step">
							<h2>2</h2>
						</div>
					</div>

					<div id="first">
						<div class="user roundel">
							<img src="resources/img/users/vlad.png" alt="Vlad">
							<h2>Vlad</h2>
							<span class="topscore">7.8×10⁹<span>
						</div>

						<div class="step">
							<h2>1</h2>
						</div>
					</div>

					<div id="third">
						<div class="user roundel">
							<img src="resources/img/users/vlad.png" alt="Vlad">
							<h2>Vlad</h2>
							<span class="topscore">-15252<span>
						</div>

						<div class="step">
							<h2>3</h2>
						</div>
					</div>
				</div>
			</section>

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
						<tr>
							<td>1</td>
							<td>Vlad</td>
							<td>1897</td>
							<td>51s</td>
							<td>452085</td>
						</tr>
					</tbody>
				</table>
			</section>
		</div>

		<?php require_once("templates/footer.html"); ?>
	</body>
</html>