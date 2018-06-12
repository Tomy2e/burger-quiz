

class SliderButton
{
    constructor(element)
    {
        this.element = element;

        /* Parse this element's children to find the marker and, eventually, a default selected item */
        var children = this.element.children;

        for (let i=0 ; i < children.length ; i++)
        {
            if ( children[i].tagName == "UL" )
            {
                //Parse all items
                for (let j = 0; j < children[i].children.length; j++)
                {
                    const item = children[i].children[j];
                    if ( item.classList.contains('selected') )  //This item is selected by default
                    {
                        this.selectedItem = item;
                    }
                }
            }
            //Find the marker
            if ( children[i].tagName == "DIV" && children[i].id == "slider-button-marker")
            {
                this.marker = children[i];
            }
        }

        this.element.addEventListener('click', (ev) => {
            console.log(ev.target);

            this.select(ev.target);
        });

        if ( this.selectedItem ) this.select(this.selectedItem);
    }

    select(target)
    {
        //Bounding rects of our elements
        var targetRect = target.getBoundingClientRect();
        var elementRect = this.element.getBoundingClientRect();

        //Translate the marker to it's target position
        this.marker.style.marginLeft = (((targetRect.left - elementRect.left) / elementRect.width) * 100) + '%';
        this.marker.style.width = (targetRect.width / elementRect.width) * 100 + '%';

        //Select the targeted item, and unselect the previously selected item
        this.selectedItem.classList.remove('selected');
        target.classList.add('selected');
        this.selectedItem = target;

        console.log(this.marker);
        
    }

    getSelectedItem()
    {
        return this.selectedItem;
    }
}

window.addEventListener('load', () => {
    var selectors = document.querySelector('.slider-button');

    if (selectors) {
        var btn = new SliderButton(selectors);
    }
});