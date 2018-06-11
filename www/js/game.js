class Game
{
    constructor()
    {
        var _GET = new URL(location.href).searchParams;

        this.screens = document.querySelectorAll("fullscreen");
        this.selected = undefined;

        this.theme = _GET.get('id_theme');
        this.difficulty = _GET.get('d');

        for (let screen of this.screens)
        {
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

        for (let screen of this.screens)
        {
            if ( screen.id == screenId)
            {
                screen.classList.add('selected');
                return true;
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
            this.nextQuestion();
        });
    }

    nextQuestion()
    {
        ajaxRequest('GET', 'ajax.php?action=next_question', {}, (res) => {
            console.log(JSON.parse(res));
        });
    }

    answer()
    {

    }

    static answers() { return {'first':1, 'second':2, 'both':3, 'none':4}; }
}

window.addEventListener('load', () => {
    var quiz = new Game();

    quiz.begin();
});