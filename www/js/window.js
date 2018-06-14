class Window
{
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

});