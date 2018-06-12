<?php

class Score
{
    private $utilisateur, $partie;

    private $reponses_correctes, $questions_total, $temps_partie, $score_final, $date_score;

    public function __construct($reponses_correctes = 0, $questions_total = 0, $temps_partie = 0, $score_final = 0)
    {
        $this->utilisateur = null;
        $this->partie = null;

        $this->reponses_correctes = $reponses_correctes;
        $this->questions_total = $questions_total;
        $this->temps_partie = $temps_partie;
        $this->score_final = $score_final;
    }

    public function addInDatabase(User $utilisateur, Partie $partie)
    {
        $prepFetchDup = Database::getInstance()
        ->prepare("SELECT * FROM possede_scores WHERE id_utilisateur = ? AND id_partie = ?");

        if(!$prepFetchDup->execute(array($utilisateur->getId(), $partie->getId())))
        {
            throw new ScoreException("Database error : failed to fetch score");
        }

        // Decide if we update or not
        $dupResult = $prepFetchDup->fetch();

        if(!empty($dupResult))
        {
            // Update ONLY if current score > old score
            if($this->score_final > $dupResult['score_final'])
            {
                $prepUpdate = Database::getInstance()
                ->prepare("UPDATE possede_scores SET score_final = ?, date_score = NOW()
                WHERE id_utilisateur = ? AND id_partie = ?");
    
                if(!$prepUpdate->execute(array(
                    $this->score_final,
                    $utilisateur->getId(),
                    $partie->getId()
                )))
                {
                    throw new ScoreException("Database error : failed to update score");
                }
            }
        }
        else
        {
            $prepAdd = Database::getInstance()
            ->prepare("INSERT INTO possede_scores (id_utilisateur, id_partie, reponses_correctes, questions_total, temps_partie, score_final, date_score)
            VALUES (:id_user, :id_partie, :reponses_correctes, :questions_total, :temps_partie, :score_final, NOW())");
    
            if($prepAdd->execute(array(
                'id_user' => $utilisateur->getId(),
                'id_partie' => $partie->getId(),
                'reponses_correctes' => $this->reponses_correctes,
                'questions_total' => $this->questions_total,
                'temps_partie' => $this->temps_partie,
                'score_final' => $this->score_final
            )))
            {
                $this->utilisateur = $utilisateur;
                $this->partie = $partie;
            }
            else
            {
                throw new ScoreException("Database error : failed to add new score");
            }
        }
    }
}