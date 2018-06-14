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
		<link rel="stylesheet" type="text/css" href="css/settings.css">

		<script src="js/main.js"></script>
		<script src="js/settings.js"></script>
	</head>
	<body>
		<?php require_once("templates/header.php"); ?>

		<!-- Page content -->
		<div id="page-settings" class="main-content">
			<h1>Paramétres</h1>
			
			<div id="settings" class="hbox">
				<form class="vbox" action="#">
					<label for="username">Nom d'utilisateur</label>
					<input type="text" value="<?php echo $user->getUsername(); ?>" name="username">

					<label for="mail">Adresse mail</label>
					<input type="text" value="<?php echo $user->getEmail(); ?>" name="mail">

					<div id="lbl-age" class="hbox">
						<label for="age">Age</label>
						<input type="number" value="<?php echo $user->getAge(); ?>" min="0" max="150" step="1" name="age">
					</div>

					<div id="lbl-changepasswd" class="inline-option hbox">
						<label for="password">Mot de passe</label>
						<a id="btn-changepasswd" href="#">Modifier le mot de passe</a>
					</div>

					<input id="password" type="hidden" name="password" value="">
					<input id="photo" type="hidden" name="photo" value="<?php echo $user->getPhoto(); ?>">

					<button class="highlighted" type="submit">Enregistrer les modifications</button>
				</form>

				<div class="vbox">
					<img id="profile-pic-large" class="roundel" src="resources/img/users/vlad.png" alt="Avatar">
					<a id="btn-changepic" href="#">Modifier</a>
				</div>
			</div>

			<div id="wnd-profile-pic" class="window screen-centered fixed hidden">
				<button id="close-btn">×</button>
				<h3>Modifier la photo de profil</h3>

				<form class="vbox" action="#">
					<label for="photo">URL de l'image</label>
					<input id="url-photo" type="text" value="<?php echo $user->getPhoto(); ?>" name="photo">

					<div class="hbox inline-option button-bar">
						<button id="btn-cancel" type="submit">Annuler</button>
						<button id="btn-ok" class="highlighted" type="submit">Ok</button>
					</div>
				</form>
			</div>

			<div id="wnd-passwd" class="window screen-centered fixed hidden">
				<button id="close-btn">×</button>
				<h3>Modifier le mot de passe</h3>

				<form class="vbox" action="#">
					<label for="current_passwd">Mot de passe actuel</label>
					<input type="password" value="" name="current_passwd">

					<label for="passwd">Nouveau mot de passe</label>
					<input type="password" value="" name="passwd">

					<label for="confirm_passwd">Confirmer le mot de passe</label>
					<input type="password" value="" name="confirm_passwd">

					<div class="hbox inline-option button-bar">
						<button id="btn-cancel" type="submit">Annuler</button>
						<button id="btn-ok" class="highlighted" type="submit">Ok</button>
					</div>
				</form>
			</div>
		</div>

		<?php require_once("templates/footer.php"); ?>
	</body>
</html>