

window.addEventListener('windowmanagerready', () => {

    var btnChangePic = document.getElementById('btn-changepic');
    var btnChangePasswd = document.getElementById('btn-changepasswd');
    var userSettingsForm = document.getElementById('user-settings');
    
    var initialUsername = document.getElementById('username').value;
    var initialMail = document.getElementById('mail').value;
    var initialAge = document.getElementById('age').value;


    if ( btnChangePic && WindowManager.wndPic )
    {

        WindowManager.wndPic.onvalidate = (ev) => {
            var profilePic = document.getElementById('profile-pic-large');
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

    if ( btnChangePasswd && WindowManager.wndPasswd )
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
                    
                    if (json.status === 'ok')
                    {
                        if ( newPassword === confPassword )
                        {
                            ajaxRequest('POST', 'ajax.php?action=set_user_info', {
                                'password': newPassword
                            },
                            (res) => {
                                let json = JSON.parse(res);

                                if (json.status === 'ok')
                                {
                                    new NotifyNotification('Sauvegardé !', 'Votre mot de passe a bien été mise à jour', 'ok');
                                }
                                else
                                {
                                    new NotifyNotification("Erreur", json.message, 'error', 5000);
                                }
                            });
                        }
                        else 
                        {
                            new NotifyNotification("Erreur", "Les mots de passe ne correspondent pas", 'error', 5000);
                        }
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

        userSettingsForm.onsubmit = (ev) => {
            ev.preventDefault();

            var newUsername = document.getElementById('username').value;
            var newMail = document.getElementById('mail').value;
            var newAge = document.getElementById('age').value;

            var updatedInfo = {};

            if ( newUsername !== initialUsername ) updatedInfo.username = newUsername;
            if ( newAge !== initialAge ) updatedInfo.age = newAge;
            if ( newMail !== initialMail ) updatedInfo.mail = newMail;

            ajaxRequest('POST', 'ajax.php?action=set_user_info', updatedInfo, (res) => {
                let json = JSON.parse(res);

                if (json.status === 'ok') {
                    new NotifyNotification('Sauvegardé !', 'Vos modifications ont été enregistrées', 'ok');
                }
                else {
                    new NotifyNotification("Erreur", json.message, 'error', 5000);
                }
            });
        }
    }
});