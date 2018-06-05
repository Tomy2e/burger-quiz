class Window
{
    constructor(element)
    {
        this.element = element;
        //this.visible = element.classList.contains('hidden');
    }

    show()
    {
        this.element.style.display = "flex";

        setTimeout( () => {
            this.element.classList.remove('hidden');
        }, 20);
    }

    hide()
    {
        this.element.classList.add('hidden');
        this.element.fireOnce('transitionend', (ev) => {
            this.element.style.display = "none";
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
