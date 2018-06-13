<?php
require_once('php/autoload.php');

if ( isConnected( $user ) )
{
    disconnect();
    header('Location: connect.php');
    //doThings('great stuff, no bugs, please');
}
?>