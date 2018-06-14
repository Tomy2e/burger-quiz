<?php

/*!
 *  \brief Indique que l'utilisateur est connecté
 *  \param id_user : L'ID de l'utilisateur dans la base de données
 */
function doConnection($id_user)
{
    $_SESSION['id_user'] = $id_user;
}

/*!
 *  \brief Vérifie que l'utilisateur est connecté
 *  \param userObj : une variable passée par référence qui contiendra l'objet User
 *  \return true ou false si l'utilisateur est connecté ou pas
 */
function isConnected(&$userObj = null)
{
    if(!empty($_SESSION['id_user']))
    {
        $userMgr = new UserManager;
        $userFound = $userMgr->fetchUserById($_SESSION['id_user']); 

        if(empty($userFound))
        {
            return false;
        }
        else
        {
            $userObj = $userFound[0];
            return true;
        }
    }
    else
    {
        return false;
    }
}

/*!
 *  \brief Déconnecte l'utilisateur actuel
 */
function disconnect()
{
    $_SESSION['id_user'] = 0;
    unset($_SESSION['id_user']);
}

/**
 * \brief Vérifie si les identifiants (pseudo et mot de passe) fournis sont corrects
 */
function checkAuth($username, $password)
{

        $userMgr = new UserManager;
        $userFound = $userMgr->fetchUserByUsername($username);

        if(empty($userFound)) {
            throw new Exception("Nom d'utilisateur inconnu");
        }

        if(password_verify($password, $userFound[0]->getPassword()))
        {
            return true;
        }
        else
        {
            throw new Exception("Mot de passe incorrect");
        }

}