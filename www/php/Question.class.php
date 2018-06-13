<?php

/**
* \author Tomy Guichard & Gwenolé Leroy-Ferrec
* \brief Classe permettant de représenter une Question
*/
class Question
{
    private $id; //!< ID de la question

    private $libelle1; //!< Libellé 1 de la question

    private $libelle2; //!< Libellé 2 de la question

    private $active; //!< Indique si la question active ou non (1 ou 0)

    /*!
     *  \brief Constructeur de la classe Question
     * 
     * Rempli automatiquement la classe à partir des paramètres
     * 
     *  \param id : l'ID de la question
     *  \param libelle1 : le libellé 1 de la question
     *  \param libelle2 : le libellé 2 de la question
     *  \param active : l'état de la question (1 ou 0)
     */
    public function __construct($id = null, $libelle1 = null, $libelle2 = null, $active = null)
    {
        $this->id = $id;
        $this->libelle1 = $libelle1;
        $this->libelle2 = $libelle2;
        $this->active = $active;
    }

    /*!
     *  \brief Retourne l'ID de la question
     * 
     *  \return l'ID de la question
     */
    public function getId()
    {
        return $this->id;
    }

    /*!
     *  \brief Retourne le libellé 1 de la question
     * 
     *  \return le libellé 1 de la question
     */
    public function getLibelle1()
    {
        return $this->libelle1;
    }

    /*!
     *  \brief Retourne le libellé 2 de la question
     * 
     *  \return le libellé 2 de la question
     */
    public function getlibelle2()
    {
        return $this->libelle2;
    }

    /*!
     *  \brief Récupère 3 propositions aléatoires liées à la Question
     *  \param number : le nombre de propositions à chercher (non pris en compte actuellement)
     *  \return Un tableau d'objets Proposition
     */
    public function fetchRandomPropositions($number = 3)
    {
        $prepFetch = Database::getInstance()->prepare("SELECT * FROM propositions WHERE id_question = ? AND active_proposition = 1 ORDER BY RAND() LIMIT 3");
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