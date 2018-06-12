<?php
require_once('php/autoload.php');

if ( isConnected( $user ) )
{
    disconnect();
    
    //doThings('great stuff, no bugs, please');
}
?>