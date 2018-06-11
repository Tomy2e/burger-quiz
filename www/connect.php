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
        ->setPhoto('')
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
        <title>Connexion</title>
    </head>

    <body>
        <h1>Connexion</h1>
        <?php if(!empty($error_login)) { echo $error_login; } ?>
        <form action="" method="post">
            Username : <input type="text" name="login_username"/><br />
            Password : <input type="password" name="login_password"/><br />
            <input type="submit" value="Connexion"/>
        </form>

        <h1>Inscription</h1>
        <?php if(!empty($error_register)) { echo $error_register; } ?>
        <form action="" method="post">
            Username : <input type="text" name="register_username"/><br />
            Age : <input type="number" name="register_age"/><br />
            Email : <input type="email" name="register_email"/><br />
            Password : <input type="password" name="register_password"/><br />
            Confirm password : <input type="password" name="register_password2"/><br />
            <input type="submit" value="Inscription"/>
        </form>
    </body>
</html>