function updateMarkerPosition()
{
    var selectedItem = document.querySelector('.hnav-list li a.selected');
    var marker = document.getElementById('marker');
    
    if (selectedItem && marker)
    {
        let selectedItemRect = selectedItem.getBoundingClientRect();
        let markerRect = marker.getBoundingClientRect();

        marker.style.left = (selectedItemRect.left + (selectedItemRect.right - selectedItemRect.left)/2 - (markerRect.right - markerRect.left)/2 ).toString() + "px";        
    } else {
        
    }
}

function initNav()
{
    var links = document.querySelectorAll('.hnav-list li a');

    var pageContent = document.querySelector('.main-content');

    if ( pageContent )
    {
        var navItem = document.getElementById('nav-' + pageContent.id.replace('page-', ''));
        
        if ( navItem )
        {
            selectNavItem(navItem);
            updateMarkerPosition();
        }
    }

    for (const i in links)
    {
        if (links.hasOwnProperty(i))
        {
            links[i].addEventListener('click', (event) => {
                selectNavItem(event.target);
                
                updateMarkerPosition();
            });
        }
    }
}

function selectNavItem(element)
{
    let selected = document.querySelector('.hnav-list li a.selected');

    if (selected) selected.classList.remove('selected');

    element.classList.add('selected');
}