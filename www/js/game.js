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

    begin()
    {
        ajaxRequest('POST', 'ajax.php?action=new_game', 
        {
            'id_theme':this.theme,
            'difficulty':this.difficulty,
        }, 
        (res) => {
            res = JSON.parse(res);

            if (res.status === 'ok')
            {
                this.nextQuestion();
            }
            else
            {
                new NotifyNotification("Erreur", res.message, 'error', 5000);
            }
        });
    }

    nextQuestion()
    {
        ajaxRequest('GET', 'ajax.php?action=next_question', {}, (res) => {

            res = JSON.parse(res);

            if ( res.status === 'ok' )
            {
                var question = document.getElementById('question');
                var proposition = document.getElementById('affirmation');
                var choice1 = document.getElementById('choice1');
                var choice2 = document.getElementById('choice2');

                question.innerText = res.current_question;
                proposition.innerText = res.current_proposition;
                choice1.innerText = res.libelle1;
                choice2.innerText = res.libelle2;

            }
            else
            {
                new NotifyNotification("Erreur", res.message, 'error', 5000);
            }

            this.show('game-ui');
            console.log(res);
        });
    }

    answer(choice)
    {
        ajaxRequest('POST', 'ajax.php?action=answer_question', {'answer':choice}, (res) => {
            res = JSON.parse(res);

            if ( res.status === 'ok' )
            {
                let screen;

                if ( res.answer_correct ) screen = 'answer-true';
                else screen = 'answer-false';

                let score = document.querySelector('#' + screen + ' #score h2');
                let scoreDelta = document.querySelector('#' + screen + ' .score-box h3');

                score.innerText = res.new_score;
                scoreDelta.innerText = res.diff_score;

                this.show(screen);
            }
            else
            {
                new NotifyNotification("Erreur", res.message, 'error', 5000);
            }

        });
    }
}

Game.answers = { 'first': 1, 'second': 2, 'both': 3, 'none': 4 };

window.addEventListener('load', () => {
    var quiz = new Game();


    /**
     * test
     */
    /*setTimeout(() => {
        quiz.show('answer-true');

        setTimeout(() => {
            quiz.show('answer-false');

            setTimeout(() => {
                quiz.show('game-ui');
            }, 1000);
        }, 1000);
    }, 1000);*/

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
        
        btn.addEventListener('click', (ev) => {
            quiz.nextQuestion();
        });
    }

    quiz.begin();
});