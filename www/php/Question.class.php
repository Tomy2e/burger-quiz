<?php

class Question
{
    private $id, $libelle1, $libelle2, $active;

    private $db;

    public function __construct($id = null, $libelle1 = null, $libelle2 = null, $active = null)
    {
        $this->db = Database::getInstance();
        $this->id = $id;
        $this->libelle1 = $libelle1;
        $this->libelle2 = $libelle2;
        $this->active = $active;
    }

    public function getId()
    {
        return $this->id;
    }

    public function fetchRandomPropositions($number = 3)
    {
        $prepFetch = $this->db->prepare("SELECT * FROM propositions WHERE id_question = ? AND active_proposition = 1 ORDER BY RAND() LIMIT 3");
        if($prepFetch->execute(array(
            $this->id
        )))
        {
            $fetchedPropositions = $prepFetch->fetchAll();

            if(count($fetchedPropositions) < $number)
            {
                throw new QuestionException("Not enough propositions in the database were found");
            }

            $finalPropositions = array();

            foreach($fetchedPropositions as $proposition)
            {
                array_push($finalPropositions, new Proposition($proposition['id_proposition'], $proposition['libelle_proposition'], $proposition['reponse_proposition'], $proposition['active_proposition']));
            }

            return $finalPropositions;
        }
        else
        {
            throw new QuestionException("Database error : failed to fetch propositions");
        }
    }
}