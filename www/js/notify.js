/****************************************/
/*              notify.js               */
/*  A simple way to display customisable*/
/* notifications using Javascript.      */
/*             -------                  */
/* Gwenolé Leroy-Ferrec    -   mai 2018 */
/****************************************/


/**
 * LICENSE : GNU GPL-3.0
 * You can use, distribute and modify this file and all the associated files
 * as permitted by the LICENSE. Only the aforementionned LICENSE applies to
 * the present files and all it's associated files (notify.js, notify.css)
 */



class NotifyNotification
{

    /**
     * constructor : Creates and displays a new NotifyNotification. An element with id "notify-container" must exist in the DOM for the new notification to be displayed in.
     * @param {String} title The title to display of the notification
     * @param {String} content The text to display in the notofication's body. HTML can be used.
     * @param {String} type The type of notification to display. Valid types are : info, ok, warning, error
     * @param {Number} showtime How long should the notification be displayed. Use -1 to display it forever (ie, until the DOM is reloaded). You can use hide() to hide it at any time.
     * @param {Function} onShow A callback function that will be called each time the notification will be shown
     * @param {Function} onHide A callback function that will be called each time the notification will be hidden
     */
    constructor( title, content, type='info', showtime=10000, onShow = () => {}, onHide = () => {} )
    {
        this.title = title;
        this.content = content;

        this.type = type;
        this.showtime = showtime;

        this.onshow = onShow;
        this.onhide = onHide;

        this.DOMElement = document.createElement('div');
        
        this.DOMElement.classList.add('notification');
        this.DOMElement.classList.add('notif-hidden');
        this.DOMElement.classList.add(this.type);
                                 /*.add('notif-hidden')
                                 .add(this.type);*/

        this.DOMElement.innerHTML = '<h3>'+this.title+'</h3>';
        this.DOMElement.innerHTML += '<p>'+this.content+'</p>';
        this.DOMElement.innerHTML += '<button>×</button>';

        var parent = document.getElementById('notify-container');
        if ( parent )
        {
            parent.appendChild(this.DOMElement);
        }
        
        setTimeout( () => {
            this.display();
        }, 50);

        if ( this.showtime != -1 ) setTimeout( () => {
            this.hide();
        }, this.showtime);        
    }


    /** */
    display()
    {
        this.DOMElement.classList.remove('notif-hidden');
        this.onshow();
    }

    hide()
    {
        this.DOMElement.classList.add('notif-hidden');
        this.onhide();

        this.DOMElement.ontransitionend = () => {
            this.DOMElement.remove();
        }
    }
}