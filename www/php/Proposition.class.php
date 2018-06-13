<?php

/**
* \author Tomy Guichard & Gwenolé Leroy-Ferrec
* \brief Classe permettant de représenter une Proposition
*/
class Proposition
{
    private $id; //!< ID de la Proposition

    private $libelle; //!< Libellé de la proposition (Ex: on peut le rouler)

    private $reponse; //!< Réponse à la proposition (1, 2 ou 3)

    private $active; //!< Proposition active ou non (1 ou 0)

    /*!
     *  \brief Constructeur de la classe Proposition
     * 
     * Rempli automatiquement la classe à partir des paramètres
     * 
     *  \param id : l'ID de la proposition
     *  \param libelle : le libellé de la proposition
     *  \param reponse : la réponse à la proposition (1, 2 ou 3)
     *  \param active : l'état de la proposition (1 ou 0)
     */
    public function __construct($id, $libelle, $reponse, $active)
    {
        $this->id = $id;
        $this->libelle = $libelle;
        $this->reponse = $reponse;
        $this->active = $active;
    }

    /*!
     *  \brief Retourne le libellé de la proposition
     * 
     *  \return libelle : le libellé de la proposition
     */
    public function getLibelle()
    {
        return $this->libelle;
    }

    /*!
     *  \brief Retourne la réponse à la proposition
     * 
     *  \return la réponse (1, 2 ou 3)
     */
    public function getReponse()
    {
        return $this->reponse;
    }
}