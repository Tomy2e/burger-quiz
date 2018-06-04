<?php

class User
{
    private $id, $username, $password, $age, $email, $photo;
    private $db;

    public function __construct($id = null, $username = null, $password = null, $age = null, $email = null, $photo = null)
    {
        $this->db = Database::getInstance();
        $this->id = $id;
        $this->username = $username;
        $this->password = $password;
        $this->age = $age;
        $this->email = $email;
        $this->photo = $photo;
    }

    public function getId()
    {
        return $this->id;
    }

    public function getUsername()
    {
        return $this->username;
    }

    public function getPassword()
    {
        return $this->password;
    }

    public function getAge()
    {
        return $this->age;
    }

    public function getEmail()
    {
        return $this->email;
    }

    public function getPhoto()
    {
        return $this->photo;
    }

    public function setUsername($username)
    {
        if(!ctype_alnum($username))
        {
            throw new UserException("Username must be alphanumeric");
        }

        if(strlen($username) > 64)
        {
            throw new UserException("Username exceeds 64 characters");
        }

        if(strlen($username) <= 4)
        {
            throw new UserException("Username must contain at least 4 characters");
        }

        $prepValidationUsername = $this->db->prepare("SELECT * FROM utilisateurs WHERE nom_utilisateur = ?");
        $prepValidationUsername->execute(array(
            $username
        ));

        if(!empty($prepValidationUsername->fetch()))
        {
            throw new UserException("Username is already in use");
        }

        // If ID is defined, update the database
        if(!is_null($this->id)) 
        {
            $prepUpdateUsername = $this->db->prepare("UPDATE utilisateurs SET nom_utilisateur = ? WHERE id_utilisateur = ?");
            if(!$prepUpdateUsername->execute(array(
                $username,
                $this->id
            )))
            {
                throw new UserException("Database error : Failed to update the username");
            }
        }

        $this->username = $username;

        return $this;
    }

    public function setPassword($password)
    {

        // If ID is defined, update the database
        if(!is_null($this->id)) 
        {
            $prepUpdatePassword = $this->db->prepare("UPDATE utilisateurs SET password_utilisateur = ? WHERE id_utilisateur = ?");
            if(!$prepUpdatePassword->execute(array(
                $password,
                $this->id
            )))
            {
                throw new UserException("Database error : Failed to update the password");
            }
        }

        $this->password = password_hash($password, PASSWORD_DEFAULT);

        return $this;
    }

    public function setAge($age)
    {
        if(!is_numeric($age))
        {
            throw new UserException("Age must be a numeric value");
        }

        $age = (int)$age;

        if($age < 13)
        {
            throw new UserException("You must be at least 13 to use this website");
        }

        // If ID is defined, update the database
        if(!is_null($this->id)) 
        {
            $prepUpdateAge = $this->db->prepare("UPDATE utilisateurs SET age_utilisateur = ? WHERE id_utilisateur = ?");
            if(!$prepUpdateAge->execute(array(
                $age,
                $this->id
            )))
            {
                throw new UserException("Database error : Failed to update the age");
            }
        }

        $this->age = $age;

        return $this;
    }

    public function setEmail($email)
    {
        if(!filter_var($email, FILTER_VALIDATE_EMAIL))
        {
            throw new UserException("Email is not valid");
        }

        $prepValidationEmail = $this->db->prepare("SELECT * FROM utilisateurs WHERE email_utilisateur = ?");
        $prepValidationEmail->execute(array(
            $email
        ));

        if(!empty($prepValidationEmail->fetch()))
        {
            throw new UserException("Email is already in use");
        }

        // If ID is defined, update the database
        if(!is_null($this->id)) 
        {
            $prepUpdateEmail = $this->db->prepare("UPDATE utilisateurs SET email_utilisateur = ? WHERE id_utilisateur = ?");
            if(!$prepUpdateEmail->execute(array(
                $email,
                $this->id
            )))
            {
                throw new UserException("Database error : Failed to update the email");
            }
        }

        $this->email = $email;

        return $this;
    }

    public function setPhoto($photo)
    {
        $this->photo = $photo;

        return $this;
    }

    public function remove()
    {
        if(!is_null($this->id))
        {
            $prepDeleteUser = $this->db->prepare("DELETE FROM utilisateurs WHERE id_utilisateur = ?");
            if(!$prepDeleteUser->execute(array(
                $this->id
            )))
            {
                throw new UserException("Database error : Failed to delete the user");
            }
            else
            {
                $this->id = null;
                return true;
            }
        }
        else
        {
            throw new UserException("This user is not in the database");
        }
    }

    public function createInDatabase()
    {
        if(is_null($this->id))
        {
            $prepAdd = $this->db->prepare("INSERT INTO utilisateurs (nom_utilisateur, password_utilisateur, age_utilisateur, email_utilisateur, photo_utilisateur) VALUES (?,?,?,?,?)");
            if($prepAdd->execute(array(
                $this->username,
                $this->password,
                $this->age,
                $this->email,
                $this->photo
            )))
            {
                $this->id = $this->db->lastInsertId();
                return true;
            }
            else
            {
                throw new UserException("Database error : Failed to add the user");
            }
        }
        else
        {
            throw new UserException("This user already exist in the database");
        }
    }
}