

window.addEventListener('load', () => {
    initThemeSelector();

    var btnPlay = document.getElementById('play');

    if ( btnPlay )
    {
        btnPlay.addEventListener('click', (ev) => {
            ev.preventDefault();

            if ( btnPlay.classList.contains('disabled') ) return false;
            
            var id_theme = document.querySelector('.theme-list-item.selected');
            var difficulty = document.querySelector('#difficulty .selected');

            if ( id_theme && difficulty )
            {
                id_theme = id_theme.id;
                difficulty = difficulty.id;
            } else {
                console.error('Error : no theme or difficulty level selected. Please select both.');
                return false;
            }
            
            location.href = "game.php?action=play&id_theme=" + id_theme + "&d=" + difficulty;
        });
    }
});



function initThemeSelector()
{
    var btnThemes = document.querySelectorAll('.theme-list-item');
    var btnPlay = document.getElementById('play');
    
    for (const i in btnThemes) {
        if (btnThemes.hasOwnProperty(i)) {
            btnThemes[i].addEventListener('click', (ev) => {
                var selectedTheme = document.querySelector('.theme-list-item.selected');

                if (selectedTheme) {
                    selectedTheme.classList.remove('selected');
                }
                btnThemes[i].classList.add('selected');
                btnPlay.classList.remove('disabled');
            });
        }
    }
}
