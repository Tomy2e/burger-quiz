<?php

class Partie
{
    private $id, $date, $difficulte;

    private $questions;


    public function __construct($id = null, $date = null, $difficulte = null)
    {
        $this->id = $id;
        $this->date = $date;
        $this->difficulte = $difficulte;

        $this->questions = array();
    }

    public function getId()
    {
        return $this->id;
    }

    public function setDifficulte($diff)
    {
        if(is_numeric($diff) && $diff > 0 && $diff < 4)
        {
            $this->difficulte = $diff;
        }
        else
        {
            $this->difficulte = 1;
        }
    }

    public function getDifficulte()
    {
        return $this->difficulte;
    }

    public function getQuestions()
    {
        if(!is_null($this->id) && empty($this->questions))
        {
            // Fetch questions in database
            $prepFetch = Database::getInstance()->prepare("SELECT * FROM questions, appartient_parties WHERE appartient_parties.id_question = questions.id_question AND appartient_parties.id_partie = ?");
            if($prepFetch->execute(array(
                $this->id
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

                $this->questions = $pickedQuestions;
            }
            else
            {
                throw new PartieException("Database error : failed to fetch questions");
            }
        }

        return $this->questions;
    }

    public function pickRandomQuestionsByTheme(Theme $theme, $number = 3)
    {
        // the $number variable is not used in the SQL query yet

        $prepFetch = Database::getInstance()->prepare("SELECT * FROM questions, appartient_themes WHERE questions.id_question = appartient_themes.id_question AND appartient_themes.id_theme = ? AND questions.active_question = 1 ORDER BY RAND() LIMIT 3");
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

                $prepRemoveOldQuestions = Database::getInstance()->prepare("DELETE FROM appartient_parties WHERE id_partie = ?");
                if(!$prepRemoveOldQuestions->execute(array(
                    $this->id
                )))
                {
                    throw new PartieException("Database error : failed to remove old questions");
                }

                foreach($pickedQuestions as $question)
                {
                    $prepAddNewQuestion = Database::getInstance()->prepare("INSERT INTO appartient_parties (id_partie, id_question) VALUES (?,?)");
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
            $prepAdd = Database::getInstance()->prepare("INSERT INTO parties (date_partie, difficulte_partie) VALUES (NOW(),?)");
            if($prepAdd->execute(array(
                $this->difficulte
            )))
            {
                $this->id = Database::getInstance()->lastInsertId();

                // Add existing questions to the database

                foreach($this->questions as $question)
                {
                    $prepAddNewQuestion = Database::getInstance()->prepare("INSERT INTO appartient_parties (id_partie, id_question) VALUES (?,?)");
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

    public function fetchScores()
    {
        if(!is_null($this->id))
        {
            $prepFetch = Database::getInstance()->prepare("SELECT nom_utilisateur, photo_utilisateur, score_final, date_score 
            FROM possede_scores, utilisateurs
            WHERE possede_scores.id_utilisateur = utilisateurs.id_utilisateur
                AND possede_scores.id_partie = ?
            ORDER BY possede_scores.score_final DESC");

            if($prepFetch->execute(array($this->id)))
            {
                return $prepFetch->fetchAll(PDO::FETCH_ASSOC);
            }
            else
            {
                throw new PartieException("Database error : faield to fetch scores");
            }
        }
        else
        {
            throw new PartieException("The game is not in the database yet!");
        }
    }
}