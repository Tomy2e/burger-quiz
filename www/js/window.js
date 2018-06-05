class Window
{
    constructor(element)
    {
        this.element = element;
        //this.visible = element.classList.contains('hidden');
        this.element.addEventListener('transitionend', () => {
            console.log('transitionend');
            
            if ( !this.visible() )
            {
                //this.element.style.zIndex = "-1";
                this.element.style.zIndex = "-100";
            } else {
                this.element.style.display = "flex";
            }
            
        });
    }

    show()
    {
        this.element.classList.remove('hidden');
    }

    hide()
    {
        this.element.classList.add('hidden');
    }

    toggle()
    {
        if (!this.visible()) this.element.style.zIndex = "100";
        this.element.classList.toggle('hidden');
    }

    visible()
    {
        return !this.element.classList.contains('hidden');
    }
};
