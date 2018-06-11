<?php

class PartiesManager 
{
    private $db;

    function __construct()
    {
        $this->db = Database::getInstance();
    }

    private function partieArrayToObject($arrayOfArray)
    {
        $arrayOfParties = array();

        foreach($arrayOfArray as $partieArray)
        {
            array_push($arrayOfParties, new Partie(
                $partieArray['id_partie'],
                $partieArray['date_partie'],
                $partieArray['difficulte_partie']
            ));
        }

        return $arrayOfParties;
    }

    public function fetchPartieById($id_partie)
    {
        $prepareFetch = $this->db->prepare("SELECT * FROM parties WHERE id_partie = ?");
        if($prepareFetch->execute(array(
            $id_partie
        )))
        {
            return $this->partieArrayToObject($prepareFetch->fetchAll());
        }
        else
        {
            throw new PartiesManagerException("An error has occured during database access");
        }
    }
}