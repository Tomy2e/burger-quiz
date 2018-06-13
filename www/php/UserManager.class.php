<?php

/**
* \author Tomy Guichard & Gwenolé Leroy-Ferrec
* \brief Classe permettant de gérer les Users
*/
class UserManager
{
    private $db; //!< Instance PDO

    /*!
     *  \brief Constructeur de la classe UserManager
     * 
     * Récupère l'instance PDO
     */
    public function __construct()
    {
        $this->db = Database::getInstance();
    }

    /*!
     *  \brief Transforme un tableau de tableau en tableau d'objets User
     * 
     *  \param arrayOfArray : un tableau de tableau
     *  \return un tableau d'objets User
     */
    private function userArrayToObject($arrayOfArray)
    {
        $arrayOfUsers = array();

        foreach($arrayOfArray as $userArray)
        {
            array_push($arrayOfUsers, new User(
                $userArray['id_utilisateur'],
                $userArray['nom_utilisateur'],
                $userArray['password_utilisateur'],
                $userArray['age_utilisateur'],
                $userArray['email_utilisateur'],
                $userArray['photo_utilisateur']
            ));
        }

        return $arrayOfUsers;
    }

    /*!
     *  \brief Récupère un utilisateur par son nom d'utilisateur
     * 
     *  \param username : le nom d'utilisateur exact
     *  \return un tableau contenant un objet User
     */
    public function fetchUserByUsername($username)
    {
        $prepareFetch = $this->db->prepare("SELECT * FROM utilisateurs WHERE nom_utilisateur = ?");
        if($prepareFetch->execute(array(
            $username
        )))
        {
            return $this->userArrayToObject($prepareFetch->fetchAll());
        }
        else
        {
            throw new UserManagerException("An error has occured during database access");
        }
    }

    /*!
     *  \brief Récupère un utilisateur par son ID
     * 
     *  \param id : l'ID de l'utilisateur
     *  \return un tableau contenant un objet User
     */
    public function fetchUserById($id)
    {
        $prepareFetch = $this->db->prepare("SELECT * FROM utilisateurs WHERE id_utilisateur = ?");
        if($prepareFetch->execute(array(
            $id
        )))
        {
            return $this->userArrayToObject($prepareFetch->fetchAll());
        }
        else
        {
            throw new UserManagerException("An error has occured during database access");
        }
    }
    
}