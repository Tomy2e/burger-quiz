window.addEventListener('load', () => {
    var selectors = document.querySelector('.hbox-selector');

    if (selectors)
    {
        var btn = new SliderButton(selectors);
    }
}); 

class SliderButton
{
    constructor(element)
    {
        this.element = element;

        var children = this.element.children
        for (let i=0 ; i < children.length ; i++)
        {
            if ( children[i].tagName == "DIV" && children[i].id == "slider-button-marker")
            {
                this.marker = children[i];
                break;
            }
        }

        this.element.addEventListener('click', (ev) => {
            console.log('yuo clockd my btn');
            console.log(ev.target);

            this.select(ev.target);
        });

    }

    select(target)
    {
        var targetRect = target.getBoundingClientRect();
        var elementRect = this.element.getBoundingClientRect();

        this.marker.style.marginLeft = 
    }
}
