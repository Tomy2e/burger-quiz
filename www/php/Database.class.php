<?php

/**
 * Database class
 * 
 * This class manages the PDO instance
 * 
 * @author Tomy Guichard <tomy.guichard@isen-ouest.yncrea.fr>
 * @author Gwenolé Leroy-Ferrec <gwenole.le-roy-ferrec@isen-ouest.yncrea.fr>
 */
class Database
{

    /**
     * The PDO Instance
     *
     * @var PDO
     */
    public static $instance;

    /**
     * Returns the current PDO Instance
     * 
     * If it doesn't exist, creates a new PDO instance.
     *
     * @return PDO
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