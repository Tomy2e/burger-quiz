/****************************************/
/*              window.js               */
/*  A simple tool to display and use    */
/* customizable modal windows.          */
/*             -------                  */
/* Gwenolé Leroy-Ferrec    -   mai 2018 */
/****************************************/


/**
 * LICENSE : GNU GPL-3.0
 * You can use, distribute and modify this file and all the associated files
 * as permitted by the LICENSE. Only the aforementionned LICENSE applies to
 * the present files and all it's associated files (window.js, window.css)
 */


 class Window
{
    /**
     * Window : A simple way to create modal windows in the current page, and manage them. Very early WIP.
     * @param {HTMLElement} element The underlying HTML DOM Element that is actually the graphical part of the window. Ususally, a div with the "window" class is used.
     */
    constructor(element)
    {
        this.element = element;
        //this.visible = element.classList.contains('hidden');

        this.onhide = function () {};
        this.onshow = function () {};
        this.onclose = function () {};
        this.oncancel = function () {};
        this.onvalidate = function () {};
    }

    show()
    {
        this.element.style.display = "inherit";

        setTimeout( () => {
            this.element.classList.remove('hidden');
            this.onshow();
        }, 20);
    }

    hide()
    {
        this.element.classList.add('hidden');
        this.element.fireOnce('transitionend', (ev) => {
            this.element.style.display = "none";
            this.onhide();
        });
    }

    toggle()
    {
        if ( this.visible() )
        {
            this.hide();
        } else {
            this.show();
        }
    }

    visible()
    {
        return !this.element.classList.contains('hidden');
    }
};


/**
 * WindowManager
 * The WindowManager object is an interface used to access the Windows created and control them.
 */

/* Event to be dispatched when the WindowManager is ready (ie, it have finished loading all the windows into its list) */
var ev_WindowManagerReady = new Event('windowmanagerready');

/* FIXME: upgrade to ES6 class */
var WindowManager = {
    'windowList': [],
    add: function (_window)
    {
        this.windowList.push(_window);
        this[prettify(_window.element.id)] = _window;
    }
};


/* TODO: use the main class to add windows */
window.addEventListener('load', (ev) => {

    var windows_not_microsoft = document.querySelectorAll('.main-content .window');

    for (const item of windows_not_microsoft) {
        let _window = new Window(item);

        let btnClose = document.querySelector('.window#' + _window.element.id + ' #close-btn');
        let btnOk = document.querySelector('.window#' + _window.element.id + ' #btn-ok');
        let btnCancel = document.querySelector('.window#' + _window.element.id + ' #btn-cancel');

        if (btnClose) btnClose.addEventListener('click', (ev) => {
            ev.preventDefault();

            _window.onclose(ev);
            _window.hide();
        });

        if (btnCancel) btnCancel.addEventListener('click', (ev) => {
            ev.preventDefault();

            _window.oncancel(ev);
            _window.hide();
        });

        if (btnOk) btnOk.addEventListener('click', (ev) => {
            ev.preventDefault();
            console.log(_window.onvalidate);
            
            _window.onvalidate(ev);
            _window.hide();
        });

        WindowManager.add(_window);
    }

    
    window.dispatchEvent(ev_WindowManagerReady);
});