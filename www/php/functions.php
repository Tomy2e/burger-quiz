<?php

function doConnection($id_user)
{
    $_SESSION['id_user'] = $id_user;
}

function isConnected(&$userObj = null)
{
    if(!empty($_SESSION['id_user']))
    {
        $userMgr = new UserManager;
        $userFound = $userMgr->fetchUserById($_SESSION['id_user']); 

        if(empty($userFound))
        {
            return false;
        }
        else
        {
            $userObj = $userFound[0];
            return true;
        }
    }
    else
    {
        return false;
    }
}

function disconnect()
{
    $_SESSION['id_user'] = 0;
    unset($_SESSION['id_user']);
}