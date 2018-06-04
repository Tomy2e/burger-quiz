function updateMarkerPosition()
{
    var selectedItem = document.querySelector('.hnav-list li a.selected');
    var marker = document.querySelector('.marker');

    console.log(selectedItem);
    
    if (selectedItem && marker)
    {
        let selectedItemRect = selectedItem.getBoundingClientRect();
        let markerRect = marker.getBoundingClientRect();

        console.log(selectedItemRect.left);

        marker.style.left = (selectedItemRect.left + (selectedItemRect.right - selectedItemRect.left)/2 - (markerRect.right - markerRect.left)/2 ).toString() + "px";        
    }
}