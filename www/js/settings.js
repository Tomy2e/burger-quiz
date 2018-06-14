

window.addEventListener('windowmanagerready', () => {

    var username = document.getElementsByName('username')[0];
    var email = document.getElementsByName('mail')[0];
    //var passwd = document.getElementsByName('password')[0]; //way too easy

    //lets try something more... tasteful
    var passwd = ((document.getElementsByName('password').length > 0) ? document.getElementsByName('password') : [null])[0];


    var btnChangePic = document.getElementById('btn-changepic');
    var btnChangePasswd = document.getElementById('btn-changepasswd');

    if ( btnChangePic && WindowManager.wndPic )
    {

        WindowManager.wndPic.onvalidate = (ev) => {
            var profilePic = document.getElementById('profile-pic-large');
            var inputPhoto = document.getElementById('photo');
            var url = document.getElementById('url-photo').value;

            ajaxRequest('POST', 'ajax.php?action=set_user_info', {
                'photo': url
            },
            (res) => {
                let json = JSON.parse(res);

                if (json.status === 'ok') {
                    profilePic.src = url;
                    new NotifyNotification('Sauvegardé !', 'Votre photo de profil a bien été mise à jour', 'ok');
                }
                else {
                    new NotifyNotification("Erreur", json.message, 'error', 5000);
                }
            });
        }

        btnChangePic.addEventListener('click', (ev) => {
            ev.preventDefault();
            WindowManager.wndPic.show();
        });
    }

    if (btnChangePasswd && WindowManager.wndPasswd)
    {
        WindowManager.wndPasswd.onvalidate = (ev) => {
            var username = document.getElementById('username').value;
            var currentPassword = document.getElementById('current-password').value;
            var newPassword = document.getElementById('new-password').value;
            var confPassword = document.getElementById('conf-password').value;

            if ( currentPassword )
            {
                ajaxRequest('POST', 'ajax.php?action=check_auth', {
                    'username': username,
                    'password': currentPassword
                },
                (res) => {
                    let json = JSON.parse(res);
                    
                    if (json.status === 'ok') {
                        
                        new NotifyNotification('Lorem', 'ca marche peut être', 'ok');
                    }
                    else {
                        new NotifyNotification("Erreur", json.message, 'error', 5000);
                    }
                });
            }
        };

        btnChangePasswd.addEventListener('click', (ev) => {
            ev.preventDefault();
            WindowManager.wndPasswd.show();
        });
    }
});