<?php

require_once('php/autoload.php');

if(!isConnected($user) || empty($_GET['action']))
{
    header("Location: index.php");
    exit;
}

if($_GET['action'] == 'new_game')
{
    try {
        // ID game défini ?
        if(!empty($_POST['id_game']))
        {
            $partiesMgr = new PartiesManager;

            $findPartie = $partiesMgr->fetchPartieById($_POST['id_game']);

            if(empty($findPartie))
            {
                throw new Exception("The game was not found");
            }

            $currentPartie = $findPartie[0];
            $currentPartie->getQuestions();
        }
        else
        {
            $currentPartie = new Partie;

            $themeChoisi = new Theme;
            if(!$themeChoisi->fetchFromId($_POST['id_theme']))
            {
                throw new Exception("The theme was not found");
            }

            $currentPartie->setDifficulte($_POST['difficulty']);

            $currentPartie->pickRandomQuestionsByTheme($themeChoisi);

            $currentPartie->createInDatabase();
        }

        $_SESSION['current_partie'] = serialize($currentPartie);
        $_SESSION['current_question_index'] = 0;
        $_SESSION['current_propositions'] = null;
        $_SESSION['current_proposition_index'] = 0;
        $_SESSION['current_proposition_answered'] = true;
        $_SESSION['current_proposition_timesent'] = 0;
        $_SESSION['current_score'] = 0;

        // OK!!
        echo json_encode(array(
            'status' => 'ok'
        ));

    } catch (Exception $e)
    {
        echo $e->getMessage();
        echo json_encode(array(
            'status' => 'error',
            'message' => $e->getMessage()
        ));
    }

}
else if($_GET['action'] == 'next_question')
{
    $currentPartie = unserialize($_SESSION['current_partie']);

    try {
        if(!empty($_SESSION['current_partie']) && $_SESSION['current_proposition_answered'] == true)
        {
            // It is the first time the user calls "next_question"
            if(is_null($_SESSION['current_propositions']))
            {
                $_SESSION['current_propositions'] = serialize($currentPartie->getQuestions()[0]->fetchRandomPropositions());
            }
            else
            {
                if($_SESSION['current_proposition_index'] == count(unserialize($_SESSION['current_propositions'])) - 1)
                {
                    // Go to the next question
                    if($_SESSION['current_question_index'] == count($currentPartie->getQuestions()) - 1)
                    {
                        throw new Exception("No more questions available");
                    }
                    
                    $_SESSION['current_question_index']++;
                    $_SESSION['current_proposition_index'] = 0;
                    $_SESSION['current_propositions'] = serialize($currentPartie->getQuestions()[$_SESSION['current_question_index']]->fetchRandomPropositions());
                }
                else
                {
                    // Go to the next proposition
                    $_SESSION['current_proposition_index']++;
                }
            }

            $_SESSION['current_proposition_answered'] = false;
            $_SESSION['current_proposition_timesent'] = time();

            $currentPropositions = unserialize($_SESSION['current_propositions']);

            $currentProposition = $currentPropositions[$_SESSION['current_proposition_index']];
            
            //print_r($currentPartie->getQuestions()[$_SESSION['current_question_index']]);   
            //print_r($currentProposition);

            $currentQuestion = $currentPartie->getQuestions()[$_SESSION['current_question_index']];

            echo json_encode(array(
                'status' => 'ok',
                'current_question' => $currentQuestion->getLibelle1() . ", " . $currentQuestion->getLibelle2() . " ou les deux ?",
                'current_proposition' => $currentProposition->getLibelle(),
                'libelle1' => $currentQuestion->getLibelle1(),
                'libelle2' => $currentQuestion->getLibelle2(),
                'current_question_progress' => $_SESSION['current_question_index'] + 1,
                'current_proposition_progress' => $_SESSION['current_proposition_index'] + 1
            ));

        }
        else
        {
            throw new Exception("Game was not started or last proposition was not answered");
        }        
    } catch(Exception $e)
    {
        echo json_encode(array(
           'status' => 'error',
           'message' => $e->getMessage() 
        ));
    }    
}
else if($_GET['action'] == 'answer_question')
{
    
}