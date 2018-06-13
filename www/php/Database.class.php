<?php

/**
* \author Tomy Guichard & Gwenolé Leroy-Ferrec
* \brief Classe permettant de gérer l'instance PDO
*/
class Database
{

    public static $instance; //!< Contient l'instance PDO

    /*!
     *  \brief Retourne l'instance actuelle de PDO
     * 
     * Si elle n'existe pas, on en crée une nouvelle
     *
     *  \return L'instance PDO
     */
    static function getInstance()
    {
        if(empty(self::$instance))
        {
            try {
                self::$instance = new PDO('mysql:host='.MYSQL_HOST.';dbname='.MYSQL_DBNAME, MYSQL_USERNAME, MYSQL_PASSWORD, array(PDO::MYSQL_ATTR_INIT_COMMAND => 'SET NAMES utf8'));

                if(ENVIRONMENT == 'DEV')
                {
                    // set ERRMODE to EXCEPTION if ENVIRONMENT is set to DEV
                    self::$instance->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
                }
                
            } catch (PDOException $e) {
                print "Erreur !: " . $e->getMessage() . "<br/>";
                die();
            }
        }
        return self::$instance;
    }
}