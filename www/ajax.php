<?php

require_once('php/autoload.php');

header("Cache-control: no-store, no-cache, must-revalidate");
header("Pragma: no-cache");
header("Content-Type: application/json; charset=utf-8");

if(!isConnected($user) || empty($_GET['action']))
{
    echo json_encode(array(
        'status' => 'error',
        'message' => 'Accès non autorisé'
    ));
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

            $currentPartie->setDifficulte(intval($_POST['difficulty']));

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
        $_SESSION['current_propositions_correct'] = 0;
        $_SESSION['current_partietime'] = 0;

        // OK!!
        echo json_encode(array(
            'status' => 'ok'
        ));

    } catch (Exception $e)
    {
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

            switch($currentPartie->getDifficulte())
            {
                case 1 : 
                    $timeToAnswer = 30;
                break;

                case 2 : 
                    $timeToAnswer = 20;
                break;

                case 3 :
                    $timeToAnswer = 10;
                break;

                default :
                throw new Exception("Invalid difficulty");
                break;
            }

            echo json_encode(array(
                'status' => 'ok',
                'current_question' => $currentQuestion->getLibelle1() . ", " . $currentQuestion->getLibelle2() . " ou les deux ?",
                'current_proposition' => $currentProposition->getLibelle(),
                'libelle1' => $currentQuestion->getLibelle1(),
                'libelle2' => $currentQuestion->getLibelle2(),
                'current_question_progress' => $_SESSION['current_question_index'] + 1,
                'current_proposition_progress' => $_SESSION['current_proposition_index'] + 1,
                'time_to_answer' => $timeToAnswer
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
else if ($_GET['action'] == 'answer_question')
{
    try {
        $currentPartie = unserialize($_SESSION['current_partie']);
        $currentPropositions = unserialize($_SESSION['current_propositions']);
        $currentProposition = $currentPropositions[$_SESSION['current_proposition_index']];

        if(!empty($_SESSION['current_partie']) && $_SESSION['current_proposition_answered'] == false)
        {
            // Check if answer is correct
            if(intval($_POST['answer']) == $currentProposition->getReponse())
            {
               $answerCorrect = true; 

               $_SESSION['current_propositions_correct']++;

                // Check how much time taken to answer
                $timeToAnswer = time() - $_SESSION['current_proposition_timesent'];

                if($currentPartie->getDifficulte() == 1)
                {
                    // Time to answer in this difficulty : 30 seconds
                    if($timeToAnswer > 35)
                    {
                        $answerPoints = 0;
                    }
                    else
                    {
                        $answerPoints = ceil(100 + ((30 - abs($timeToAnswer))* 100)/30);
                    }
                }
                else if($currentPartie->getDifficulte() == 2)
                {
                    // Time to answer in this difficulty : 20 seconds
                    if($timeToAnswer > 25)
                    {
                        $answerPoints = 0;
                    }
                    else
                    {
                        $answerPoints = ceil(200 + ((20 - abs($timeToAnswer))* 100)/20);;
                    }
                }
                else if($currentPartie->getDifficulte() == 3)
                {
                    // Time to answer in this difficulty : 10 seconds
                    if($timeToAnswer > 15)
                    {
                        $answerPoints = 0;
                    }
                    else
                    {
                        $answerPoints = ceil(300 + ((10 - abs($timeToAnswer))* 100)/10);;
                    }
                }
                else
                {
                    throw new Exception("Invalid difficulty");
                }
            }
            else
            {
                $answerCorrect = false;
                $answerPoints = 0;
            }


            $_SESSION['current_score'] += $answerPoints;
            $_SESSION['current_partietime'] += $timeToAnswer;
            $_SESSION['current_proposition_answered'] = true;

            // Check if the game is finished
            if($_SESSION['current_question_index'] == count($currentPartie->getQuestions()) -  1
            && $_SESSION['current_proposition_index'] == count($currentPropositions) - 1)
            {
                $partieFinished = true;

                // Add score to database
                $newScore = new Score($_SESSION['current_propositions_correct'], 9,
                $_SESSION['current_partietime'], $_SESSION['current_score']);
                $newScore->addInDatabase($user, $currentPartie);
            }
            else
            {
                $partieFinished = false;
            }

            // Get answer of this question
            switch($currentProposition->getReponse())
            {
                case 1:
                    $currentReponse = $currentPartie->getQuestions()[$_SESSION['current_question_index']]->getLibelle1();
                break;

                case 2:
                    $currentReponse = $currentPartie->getQuestions()[$_SESSION['current_question_index']]->getLibelle2();
                break;

                default:
                    $currentReponse = "Les deux";
                break;
            }

            echo json_encode(array(
                'status' => 'ok',
                'answer_correct' => $answerCorrect,
                'answer' => $currentReponse,
                'new_score' => $_SESSION['current_score'],
                'diff_score' => $answerPoints,
                'partie_terminee' => $partieFinished
            ));
        }
        else
        {
            throw new Exception("Game was not started or last proposition was already answered");
        }
    } catch (Exception $e)
    {
        echo json_encode(array(
            'status' => 'error',
            'message' => $e->getMessage()
        ));
    }
}
else if($_GET['action'] == 'get_results')
{
    try {
        $currentPartie = unserialize($_SESSION['current_partie']);
        $currentPropositions = unserialize($_SESSION['current_propositions']);
        $currentProposition = $currentPropositions[$_SESSION['current_proposition_index']];

        // Check if the game is finished
        if($_SESSION['current_question_index'] == count($currentPartie->getQuestions()) -  1
        && $_SESSION['current_proposition_index'] == count($currentPropositions) - 1)
        {
            echo json_encode(array(
                'status' => 'ok',
                'id_game' => $currentPartie->getId(),
                'scoreboard' => $currentPartie->fetchScores()
            ));
            print_r();
        }
        else
        {
            throw new Exception("Game is not finished!");
        }
    } catch (Exception $e)
    {
        echo json_encode(array(
            'status' => 'error',
            'message' => $e->getMessage()
        ));
    }
} 
else if($_GET['action'] == 'set_user_info')
{
    try
    {
        if ( isset($_POST['username']) ) $user->setUsername($_POST['username']);
        if ( isset($_POST['password']) ) $user->setPassword($_POST['password']);
        if ( isset($_POST['email']) ) $user->setEmail($_POST['email']);
        if ( isset($_POST['photo']) ) $user->setPhoto($_POST['photo']);

        echo json_encode(array(
            'status' => 'ok'
        ));
    }
    catch (Exception $e)
    {
        echo json_encode( array(
            'status' => 'error',
            'message' => $e->getMessage()
        ));
    }
}