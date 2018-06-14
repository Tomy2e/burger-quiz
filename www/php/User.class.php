<?php

/**
* \author Tomy Guichard & Gwenolé Leroy-Ferrec
* \brief Classe permettant de représenter un User
*/
class User
{
    private $id; //!< ID de l'utilisateur

    private $username; //!< Nom d'utilisateur

    private $password; //!< Mot de passe hashé de l'utilisateur

    private $age; //!< Âge de l'utilisateur

    private $email; //!< Adresse email de l'utilisateur

    private $photo; //!< Lien vers la photo de l'utilisateur

    private $db; //!< Instance PDO

    /*!
     *  \brief Constructeur de la classe User
     * 
     * Rempli automatiquement la classe à partir des paramètres
     * 
     *  \param id : l'ID de l'utilisateur
     *  \param username : le nom d'utilisateur
     *  \param password : le mot de passe hashé
     *  \param age : l'âge de l'utilisateur
     *  \param email : l'adresse email de l'utilisateur
     *  \param photo : le lien vers la photo de l'utilisateur
     */
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

    /*!
     *  \brief Retourne l'ID de l'utilisateur
     * 
     *  \return l'ID de l'utilisateur
     */
    public function getId()
    {
        return $this->id;
    }

    /*!
     *  \brief Retourne le nom d'utilisateur
     * 
     *  \return le nom d'utilisateur
     */
    public function getUsername()
    {
        return $this->username;
    }

    /*!
     *  \brief Retourne le mot de passe hashé
     * 
     * S'il n'est pas hashé (modifié depuis l'interface Qt),
     * on le hash et on met à jour la base de données
     * 
     *  \return le mot de passe hashé
     */
    public function getPassword()
    {
        // If password is not hashed, let's hash it
        if(substr($this->password, 0, 10) == "nothashed:")
        {
            $explPw = explode(":", $this->password);

            $this->setPassword($explPw[1]);
        }

        return $this->password;
    }

    /*!
     *  \brief Retourne l'âge de l'utilisateur
     * 
     *  \return l'âge de l'utilisateur
     */
    public function getAge()
    {
        return $this->age;
    }

    /*!
     *  \brief Retourne l'adresse email
     * 
     *  \return l'adresse email
     */
    public function getEmail()
    {
        return $this->email;
    }

    /*!
     *  \brief Retourne le lien vers la photo de l'utilisateur
     * 
     *  \return le lien vers la photo de l'utilisateur
     */
    public function getPhoto()
    {
        return $this->photo;
    }

    /*!
     *  \brief Change le nom d'utilisateur
     * 
     *  \param username : Le nouveau nom d'utilisateur
     */
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

        if(strlen($username) < 4)
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

    /*!
     *  \brief Change le mot de passe
     * 
     *  \param password : Le nouveau mot de passe
     */
    public function setPassword($password)
    {

        $this->password = password_hash($password, PASSWORD_DEFAULT);

        // If ID is defined, update the database
        if(!is_null($this->id)) 
        {
            $prepUpdatePassword = $this->db->prepare("UPDATE utilisateurs SET password_utilisateur = ? WHERE id_utilisateur = ?");
            if(!$prepUpdatePassword->execute(array(
                $this->password,
                $this->id
            )))
            {
                throw new UserException("Database error : Failed to update the password");
            }
        }
        
        return $this;
    }

    /*!
     *  \brief Change l'âge de l'utilisateur
     * 
     *  \param age : Le nouvel âge de l'utilisateur
     */
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


    /*!
     *  \brief Change l'email de l'utilisateur
     * 
     *  \param email : Le nouvel email de l'utilisateur
     */
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

    /*!
     *  \brief Change la photo de l'utilisateur
     * 
     *  \param photo : La nouvelle photo de l'utilisateur
     */
    public function setPhoto($photo)
    {
        $photo = filter_var($photo, FILTER_SANITIZE_URL);
        if(!filter_var($photo, FILTER_VALIDATE_URL))
        {
            throw new UserException("URL is not valid. Details: \nURL : ".$photo);
        }

        // If ID is defined, update the database
        if(!is_null($this->id)) 
        {
            $prepUpdatePhoto = $this->db->prepare("UPDATE utilisateurs SET photo_utilisateur = ? WHERE id_utilisateur = ?");
            if(!$prepUpdatePhoto->execute(array(
                $photo,
                $this->id
            )))
            {
                throw new UserException("Database error : Failed to update the user profile picture");
            }
        }

        $this->photo = $photo;

        return $this;
    }

    /*!
     *  \brief Supprime l'utilisateur
     *  \return true en cas de réussite
     */
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

    /*!
     *  \brief Crée l'utilisateur dans la base de données
     * 
     *  \return true en cas de réussite
     */
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