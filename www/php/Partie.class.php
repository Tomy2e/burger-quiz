<?php

class Partie
{
    private $id, $date, $difficulte;

    private $questions;

    private $db;

    public function __construct($id = null, $date = null, $difficulte = null)
    {

        $this->db = Database::getInstance();

        $this->id = $id;
        $this->date = $date;
        $this->difficulte = $difficulte;

        $this->questions = array();
    }

    public function pickRandomQuestionsByTheme(Theme $theme, $number = 3)
    {
        // the $number variable is not used in the SQL query yet

        $prepFetch = $this->db->prepare("SELECT * FROM questions, appartient_themes WHERE questions.id_question = appartient_themes.id_question AND appartient_themes.id_theme = ? AND questions.active_question = 1 ORDER BY RAND() LIMIT 3");
        if($prepFetch->execute(array(
            $theme->getId()
        )))
        {
            $fetchQuestions = $prepFetch->fetchAll();

            $pickedQuestions = array();

            if(count($fetchQuestions) < $number)
            {
                throw new PartieException("Not enough questions available in this theme");
            }

            // Transform arrays of arrays to arrays of Question objects
            foreach($fetchQuestions as $question)
            {
                array_push($pickedQuestions, new Question($question['id_question'], $question['libelle1'], $question['libelle2'], $question['active_question']));
            }

            if(!is_null($this->id))
            {
                // If the game is already in the database, we replace the old questions with the new ones

                $prepRemoveOldQuestions = $this->db->prepare("DELETE FROM appartient_parties WHERE id_partie = ?");
                if(!$prepRemoveOldQuestions->execute(array(
                    $this->id
                )))
                {
                    throw new PartieException("Database error : failed to remove old questions");
                }

                foreach($pickedQuestions as $question)
                {
                    $prepAddNewQuestion = $this->db->prepare("INSERT INTO appartient_parties (id_partie, id_question) VALUES (?,?)");
                    if(!$prepAddNewQuestion->execute(array(
                        $this->id,
                        $question->getId()
                    )))
                    {
                        throw new PartieException("Database error : could not add a new question to this game");
                    }
                }
            }

            $this->questions = $pickedQuestions;
        }
        else
        {
            throw new PartieException("Database error : failed to pick random questions by theme");
        }
    }

    public function createInDatabase()
    {
        if(is_null($this->id))
        {
            $prepAdd = $this->db->prepare("INSERT INTO parties (date_partie, difficulte_partie) VALUES (?,?)");
            if($prepAdd->execute(array(
                $this->date,
                $this->difficulte
            )))
            {
                $this->id = $this->db->lastInsertId();

                // Add existing questions to the database

                foreach($this->questions as $question)
                {
                    $prepAddNewQuestion = $this->db->prepare("INSERT INTO appartient_parties (id_partie, id_question) VALUES (?,?)");
                    if(!$prepAddNewQuestion->execute(array(
                        $this->id,
                        $question->getId()
                    )))
                    {
                        throw new PartieException("Database error : could not add a new question to this game");
                    }
                }

                return true;
            }
            else
            {
                throw new PartieException("Database error : failed to create the game");
            }
        }
        else
        {
            throw new PartieException("The game was already added in the database");
        }
    }
}