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

					<div id="lbl-changepasswd" class="hbox">
						<label for="password">Mot de passe</label>
						<a id="btn-changepasswd" href="#">Modifier le mot de passe</a>
					</div>
					<input type="password" disabled value="<?php echo $user->getPassword(); ?>" name="password">

					<button class="highlighted" type="submit">Enregistrer les modifications</button>
				</form>
			</div>
		</div>

		<?php require_once("templates/footer.php"); ?>
	</body>
</html>