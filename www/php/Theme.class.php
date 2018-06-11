<?php

class Theme 
{
    private $id, $libelle, $photo;

    private $db;

    public function __construct($id = null, $libelle = null, $photo = null)
    {
        $this->db = Database::getInstance();
        $this->id = $id;
        $this->libelle = $libelle;
        $this->photo = $photo;
    }

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

    public function getId()
    {
        return $this->id;
    }

    public function getLibelle()
    {
        return $this->libelle;
    }

    public function getPhoto()
    {
        return $this->photo;
    }

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