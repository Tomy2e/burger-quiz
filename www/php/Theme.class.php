<?php

/**
* \author Tomy Guichard & Gwenolé Leroy-Ferrec
* \brief Classe permettant de représenter un Theme
*/
class Theme 
{
    private $id; //!< ID du thème

    private $libelle; //!< Libellé du thème

    private $photo; //!< Lien vers la photo du thème

    private $db; //!< Contient l'instance PDO

    /*!
     *  \brief Constructeur de la classe Theme
     * 
     * Rempli automatiquement la classe à partir des paramètres
     * 
     *  \param id : l'ID du thème
     *  \param libelle : le libellé du thème
     *  \param photo : le lien vers la photo du thème
     */
    public function __construct($id = null, $libelle = null, $photo = null)
    {
        $this->db = Database::getInstance();
        $this->id = $id;
        $this->libelle = $libelle;
        $this->photo = $photo;
    }

    /*!
     *  \brief Cherche un thème à partir du libellé
     * 
     *  \param libelle : le libellé EXACT du thème
     *  \return true si le thème a été trouvé ou false sinon
     */
    public function fetchFromLibelle($libelle)
    {
        $prepFetch = $this->db->prepare("SELECT * FROM themes WHERE libelle_theme = ?");
        if($prepFetch->execute(array(
            $libelle
        )))
        {
            $theme = $prepFetch->fetch();

            if(empty($theme))
            {
                return false;
            }
            else
            {
                $this->id = $theme['id_theme'];
                $this->libelle = $theme['libelle_theme'];
                $this->photo = $theme['photo_theme'];
                
                return true;
            }
        }
        else
        {
            throw new ThemeException("Database error : failed to fetch themes from libelle");
        }
    }

    /*!
     *  \brief Cherche un thème à partir de son ID
     * 
     *  \param id : l'ID du thème
     *  \return true si le thème a été trouvé ou false sinon
     */
    public function fetchFromId($id)
    {
        $prepFetch = $this->db->prepare("SELECT * FROM themes WHERE id_theme = ?");
        if($prepFetch->execute(array(
            $id
        )))
        {
            $theme = $prepFetch->fetch();

            if(empty($theme))
            {
                return false;
            }
            else
            {
                $this->id = $theme['id_theme'];
                $this->libelle = $theme['libelle_theme'];
                $this->photo = $theme['photo_theme'];
                
                return true;
            }
        }
        else
        {
            throw new ThemeException("Database error : failed to fetch themes from id");
        }
    }

    /*!
     *  \brief Retourne l'ID du thème
     * 
     *  \return l'ID du thème
     */
    public function getId()
    {
        return $this->id;
    }

    /*!
     *  \brief Retourne le libellé du thème
     * 
     *  \return le libellé du thème
     */
    public function getLibelle()
    {
        return $this->libelle;
    }

    /*!
     *  \brief Retourne le lien vers la photo du thème
     * 
     *  \return le lien vers la photo du thème
     */
    public function getPhoto()
    {
        return $this->photo;
    }

    /*!
     *  \brief Récupère tous les thèmes de la base de données
     * 
     *  \return un tableau d'objets Theme
     */
    public static function fetchAllThemes()
    {
        $prepFetch = Database::getInstance()->prepare("SELECT * FROM themes");

        if($prepFetch->execute())
        {
            $fetchedThemes = array();

            foreach($prepFetch->fetchAll() as $theme)
            {
                array_push($fetchedThemes, new Theme($theme['id_theme'], $theme['libelle_theme'], $theme['photo_theme']));
            }

            return $fetchedThemes;
        }
        else
        {
            throw new ThemeException("Database error : failed to fetch themes");
        }
    }
}