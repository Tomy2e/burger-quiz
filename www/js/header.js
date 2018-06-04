function updateMarkerPosition()
{
    var selectedItem = document.querySelector('.hnav-list li a.selected');
    var marker = document.getElementById('marker');

    console.log(selectedItem);
    
    if (selectedItem && marker)
    {
        let selectedItemRect = selectedItem.getBoundingClientRect();
        let markerRect = marker.getBoundingClientRect();

        console.log(selectedItemRect.left);

        marker.style.left = (selectedItemRect.left + (selectedItemRect.right - selectedItemRect.left)/2 - (markerRect.right - markerRect.left)/2 ).toString() + "px";        
    }
}

function initNav()
{
    var links = document.querySelectorAll('.hnav-list li a');

    for (const i in links)
    {
        if (links.hasOwnProperty(i))
        {
            links[i].addEventListener('click', (event) => {
                let selected = document.querySelector('.hnav-list li a.selected');

                if (selected) selected.classList.remove('selected');

                event.target.classList.add('selected');
                
                updateMarkerPosition();
            });
        }
    }
}