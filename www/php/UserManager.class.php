<?php

class UserManager
{
    private $db;

    public function __construct()
    {
        $this->db = Database::getInstance();
    }

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