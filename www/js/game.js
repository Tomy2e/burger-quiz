class Game
{
    constructor()
    {
        var _GET = new URL(location.href).searchParams;

        this.screens = document.querySelectorAll(".fullscreen");
        this.selected = undefined;

        this.theme = _GET.get('id_theme');
        this.difficulty = _GET.get('d');

        for (let screen of this.screens)
        {
            console.log(screen);
            
            if ( screen.classList.contains('selected') )
            {
                this.selected = screen;
                break;
            }
        }
    }

    show(screenId)
    {        
        if ( this.selected ) this.selected.classList.remove('selected');

        var target = this.getScreen(screenId);

        if ( target )
        {
            target.classList.add('selected');
            this.selected = target;

            return true;
        }
        else
        {
            return false;
        }
    }

    getScreen(screenId)
    {
        for (let screen of this.screens) {
            if (screen.id == screenId)
            {
                return screen;
            }
        }

        console.warn('[Game] Screen #' + screenId + ' not found in the current set of screens.');
        return false;
    }

    request(action, param = null, callback = () => {}, type = null)
    {
        if ( !type )
        {
            switch (action) {
                case 'new_game':
                case 'answer_question':
                    type = 'POST';
                    break;
                
                case 'next_question':
                case 'get_results':
                default:
                    type = 'GET';
                    break;
            }
        }

        ajaxRequest(type, 'ajax.php?action=' + action, param, (res) => {            
            let json = JSON.parse(res);

            if (json.status === 'ok')
            {
                callback(json, res);
            }
            else {
                new NotifyNotification("Erreur", json.message, 'error', 5000);
            }
        });
    }

    begin()
    {
        this.request('new_game', 
        {
            'id_theme':this.theme,
            'difficulty':this.difficulty,
        }, 
        (res) => {
                this.nextQuestion();
        });
    }

    nextQuestion()
    {
        this.request('next_question', {}, (res) => {

            var question = document.getElementById('question');
            var proposition = document.getElementById('affirmation');
            var choice1 = document.getElementById('choice1');
            var choice2 = document.getElementById('choice2');

            question.innerText = res.current_question;
            proposition.innerText = res.current_proposition;
            choice1.innerText = res.libelle1;
            choice2.innerText = res.libelle2;
            
            this.show('game-ui');
        });
    }

    answer(choice)
    {
        this.request('answer_question', {'answer':choice}, (res) => {

            let screen;

            if ( res.answer_correct ) screen = 'answer-true';
            else 
            {
                screen = 'answer-false';

                document.querySelector('#answer-false #correct-answer').innerText = "La bonne réponse était : " + res.answer;
            }

            let score = document.querySelector('#' + screen + ' #score h2');
            let scoreDelta = document.querySelector('#' + screen + ' .score-box h3');

            score.innerText = res.new_score;
            scoreDelta.innerText = '(+' + res.diff_score + ')';


            if (res.partie_terminee)
            {
                console.log('##### PARTIE TERMINEE #####');
                
                let btnNext = document.querySelector('#' + screen + ' .next-question');

                btnNext.onclick = (ev) => {
                    
                    this.request('get_results', null, (res) => {
                        
                    });
                    this.show('results');
                }
            }

            this.show(screen);
        });
    }
}

Game.answers = { 'first': 1, 'second': 2, 'both': 3, 'none': 4 };

window.addEventListener('load', () => {
    var quiz = new Game();

    if ( !quiz.show(_GET.get('page')) ) quiz.show('game-ui');

    var btnChoice1 = document.getElementById('choice1');
    var btnChoice2 = document.getElementById('choice2');
    var btnBoth = document.getElementById('both');

    btnChoice1.addEventListener('click', (ev) => {
        console.log(ev.target);
        quiz.answer(Game.answers.first);
    });

    btnChoice2.addEventListener('click', (ev) => {
        console.log(ev.target);
        quiz.answer(Game.answers.second);
    });

    btnBoth.addEventListener('click', (ev) => {
        console.log(ev.target);
        quiz.answer(Game.answers.both);
    });

    var btnNext = document.querySelectorAll('.next-question');

    for ( const btn of btnNext )
    {
        console.log(btn);
        
        btn.onclick = (ev) => {
            quiz.nextQuestion();
        };
    }

    quiz.begin();
});