<?php

require_once('php/autoload.php');

// Connexion
if(!empty($_POST['login_username']) && !empty($_POST['login_password']))
{
    try {
        $userMgr = new UserManager;
        $userFound = $userMgr->fetchUserByUsername($_POST['login_username']);

        if(empty($userFound)) {
            throw new Exception("L'utilisateur n'a pas été trouvé");
        }

        if(password_verify($_POST['login_password'], $userFound[0]->getPassword()))
        {
            doConnection($userFound[0]->getId());
            header("Location: index.php");
            exit;
        }
        else
        {
            throw new Exception("Mot de passe incorrect");
        }
    } catch (Exception $e)
    {
        $error_login = $e->getMessage();
    }
}
// Inscription
else if(!empty($_POST['register_username']))
{
    try {
        $newUser = new User;

        if(strcmp($_POST['register_password'], $_POST['register_password2']) != 0)
        {
            throw new Exception("Les mots de passe ne correspondent pas");
        }

        $newUser->setUsername($_POST['register_username'])
        ->setPassword($_POST['register_password'])
        ->setAge($_POST['register_age'])
        ->setEmail($_POST['register_email'])
        ->createInDatabase();

        doConnection($newUser->getId());

        header("Location: index.php");
        exit;
    } catch (Exception $e)
    {
        $error_register = $e->getMessage();
    }
}
?>
<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8">
		<meta author="Gwenolé Leroy-Ferrec - Tomy Guichard">

		<title>Connexion - The Ultimate Burger Quiz</title>

		<link rel="stylesheet" type="text/css" href="css/main.css">
		<link rel="stylesheet" type="text/css" href="css/generic-theme.css">
		<link rel="stylesheet" type="text/css" href="css/fonts.css">
		<link rel="stylesheet" type="text/css" href="css/header.css">
		<link rel="stylesheet" type="text/css" href="css/footer.css">
		<link rel="stylesheet" type="text/css" href="css/login.css">

        <script src="js/main.js"></script>
    </head>

    <body>
        <?php require_once("templates/header.php"); ?>

		<!-- Page content -->
		<div id="page-quiz" class="main-content centered">
            <h1>Connexion</h1>

            <?php if(!empty($error_login)) { echo $error_login; } ?>

            <form id="login" class="vbox" action="" method="post">
                <label>Username : </label><input type="text" name="login_username"/>
                <label>Password : </label><input type="password" name="login_password"/>
                <button class="highlighted" type="submit" value="Connexion">Connection</button>
            </form>

            <h1>Inscription</h1>

            <?php if(!empty($error_register)) { echo $error_register; } ?>

            <form id="register" class="vbox" action="" method="post">
                <div class="hbox">
                    <div id="username" class="expand">
                        <label>Username : </label><input type="text" name="register_username"/>
                    </div>
                    <div id="age" class="expand">
                        <label>Age : </label><input type="number" name="register_age"/>
                    </div>
                </div>

                <label>Email : </label><input type="email" name="register_email"/>
                <label>Password : </label><input type="password" name="register_password"/>
                <label>Confirm password : </label><input type="password" name="register_password2"/>
                <button class="highlighted" type="submit" value="Inscription">Inscription</button>
            </form>
        </div>
    </body>
</html>