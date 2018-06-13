<?php

/**
* \author Tomy Guichard & Gwenolé Leroy-Ferrec
* \brief Classe permettant de gérer les parties
*/
class PartiesManager 
{
    private $db; //!< Instance PDO

    /*!
     *  \brief Constructeur de la classe PartiesManager
     * 
     * Récupère l'instance PDO
     */
    function __construct()
    {
        $this->db = Database::getInstance();
    }

    /*!
     *  \brief Transforme un tableau de tableau en tableau d'objets Partie
     * 
     *  \param arrayOfArray : le tableau de tableau
     *  \return un tableau d'objets Partie
     */
    private function partieArrayToObject($arrayOfArray)
    {
        $arrayOfParties = array();

        foreach($arrayOfArray as $partieArray)
        {
            array_push($arrayOfParties, new Partie(
                $partieArray['id_partie'],
                $partieArray['date_partie'],
                $partieArray['difficulte_partie'],
                (isset($partieArray['nb_joueurs'])) ? $partieArray['nb_joueurs'] : 0
            ));
        }

        return $arrayOfParties;
    }

    /*!
     *  \brief Récupère une partie à partir de son ID
     * 
     *  \param id_partie : l'ID de la partie recherchée
     *  \return un tableau d'objets Partie
     */
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

    /*!
     *  \brief Récupère les parties les plus populaires
     * 
     * Les parties les plus jouées sont classées en premier
     * 
     *  \return un tableau d'objets Partie
     */
    public function fetchLatestParties()
    {
        $prepareFetch = $this->db->prepare("SELECT *,
        (SELECT COUNT(possede_scores.score_final) FROM possede_scores WHERE parties.id_partie = possede_scores.id_partie) AS nb_joueurs
        FROM parties
        WHERE (SELECT COUNT(possede_scores.score_final) FROM possede_scores WHERE parties.id_partie = possede_scores.id_partie) > 0
        ORDER BY nb_joueurs DESC, id_partie DESC");

        if($prepareFetch->execute())
        {
            return $this->partieArrayToObject($prepareFetch->fetchAll());
        }
        else
        {
            throw new PartiesManagerException("An error has occured during database access");
        }
    }
}