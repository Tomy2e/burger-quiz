<?php

/**
* \author Tomy Guichard & Gwenolé Leroy-Ferrec
* \brief Classe permettant de gérer les Scores
*/
class ScoresManager 
{
    private $db; //!< Instance PDO

    /*!
     *  \brief Constructeur de la classe ScoresManager
     * 
     * Récupère l'instance PDO
     */
    public function __construct()
    {
        $this->db = Database::getInstance();
    }

    /*!
     *  \brief Récupère le classement général
     * 
     * Pour chaque utilisateur, récupère le score total, le top score et le top temps
     * 
     *  \param orderby : Critère de tri = total, top_score ou temps_min
     */
    public function getClassementGeneral($orderby = "total")
    {
        switch($orderby)
        {
            case 'total':
                $sqlOrderBy = 'total_points DESC';
            break;

            case 'top_score':
                $sqlOrderBy = 'top_score DESC';
            break;

            case 'temps_min':
                $sqlOrderBy = 'temps_min ASC';
            break;

            default:
                $sqlOrderBy = 'total_points DESC';
            break;
        }

        $prepFetch = $this->db->prepare("SELECT utilisateurs.nom_utilisateur, SUM(score_final) AS total_points,
        (SELECT MAX(score_final) FROM possede_scores AS e1 WHERE e1.id_utilisateur = possede_scores.id_utilisateur) AS top_score,
        (SELECT MIN(temps_partie) FROM possede_scores AS e1 WHERE e1.id_utilisateur = possede_scores.id_utilisateur) AS temps_min
        FROM possede_scores, utilisateurs
        WHERE possede_scores.id_utilisateur = utilisateurs.id_utilisateur
        GROUP BY possede_scores.id_utilisateur
        ORDER BY $sqlOrderBy");

        if($prepFetch->execute())
        {
            return $prepFetch->fetchAll();
        }
        else
        {
            throw new ScoresManagerException("Database error : failed to fetch 'classement général'");
        }
    }
}