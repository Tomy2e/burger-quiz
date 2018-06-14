<?php

/**
* \author Tomy Guichard & Gwenolé Leroy-Ferrec
* \brief Classe permettant de représenter une Partie
*/
class Partie
{
    private $id; //!< ID de la partie

    private $date; //!< Date de la partie

    private $difficulte; //!< Difficulté de la partie

    private $nb_joueurs; //!< Nombre de joueurs ayant joué à la partie

    private $questions; //!< Tableau contenant les questions de la partie

    /*!
     *  \brief Constructeur de la classe Partie
     * 
     * Initialise les propriétés de la classe en fonction des paramètres
     *
     *  \param id : ID de la partie
     *  \param date : date de la partie
     *  \param difficulte : difficulté de la partie (1, 2 ou 3)
     *  \param nb_joueurs : le nombre de joueurs ayant joué à la partie
     */
    public function __construct($id = null, $date = null, $difficulte = null, $nb_joueurs = 0)
    {
        $this->id = $id;
        $this->date = $date;
        $this->difficulte = $difficulte;
        $this->nb_joueurs = $nb_joueurs;

        $this->questions = array();
    }

    /*!
     *  \brief Retourne l'ID de la partie
     *
     *  \return L'ID de la partie
     */
    public function getId()
    {
        return $this->id;
    }

    /*!
     *  \brief Retourne le nombre de joueurs ayant joué à la partie
     *
     *  \return Le nombre de joueurs ayant joué à la partie
     */
    public function getNbJoueurs()
    {
        return $this->nb_joueurs;
    }

    /*!
     *  \brief Défini la difficulté de la partie
     * 
     *  \param diff : un nombre appartenant à l'intervalle [1;3]
     */
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

    /*!
     *  \brief Retourne la difficulté de la partie
     * 
     *  \return un nombre appartenant à l'intervalle [1;3]
     */
    public function getDifficulte()
    {
        return $this->difficulte;
    }

    /*!
     *  \brief Récupère les questions
     * 
     * Si l'ID est non nul et qu'il n'y a pas de questions dans la classe
     * on récupère les questions associées à l'ID dans la base de données
     * Sinon on retourne simplement les questions existantes
     *
     *  \return Un tableau d'objets Question
     */
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

    /*!
     *  \brief Rempli la classe de questions aléatoires en fonction d'un thème
     * 
     * S'il n'y a pas assez de questions dans un thème, retourne une exception
     * 
     *  \param theme : une instance de la classe Theme
     *  \param number : le nombre de questions à piocher (n'a aucun effect pour l'instant)
     */
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

    /*!
     *  \brief Crée la partie dans la base de données
     * 
     * Ne fonctionne que si la partie n'a pas déjà été ajoutée dans la base de données
     *
     *  \return true en cas de réussite
     */
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

    /*!
     *  \brief Récupère les scores liés à la partie dans la base de données
     * 
     *  \return Un tableau avec la liste de scores et l'utilisateur qui a joué
     */
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

    /*!
     *  \brief Liste les thèmes associés aux questions de la partie
     * 
     *  \return Un tableau avec les thèmes
     */
    public function fetchThemes()
    {
        if(!is_null($this->id))
        {
            $prepFetch = Database::getInstance()->prepare("SELECT DISTINCT(themes.id_theme),themes.libelle_theme, themes.photo_theme
            FROM parties, themes, appartient_parties, appartient_themes
            WHERE parties.id_partie = 1 AND appartient_parties.id_partie = parties.id_partie
                AND appartient_themes.id_question = appartient_parties.id_question
                AND appartient_themes.id_theme = themes.id_theme");

            if($prepFetch->execute(array($this->id)))
            {
                $arrayOfThemes = array();

                foreach($prepFetch->fetchAll() as $theme_raw)
                {
                    array_push($arrayOfThemes, new Theme($theme_raw['id_theme'], $theme_raw['libelle_theme'], $theme_raw['photo_theme']));
                }

                return $arrayOfThemes;
            }
            else
            {
                throw new PartieException("Database error : faield to fetch themes");
            }
        }
        else
        {
            throw new PartieException("The game is not in the database yet!");
        }
    }
}
