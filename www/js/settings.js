

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

            profilePic.src = inputPhoto.value = url;
        }

        btnChangePic.addEventListener('click', (ev) => {
            ev.preventDefault();
            WindowManager.wndPic.show();
        });
    }

    if (btnChangePasswd && WindowManager.wndPasswd)
    {
        WindowManager.wndPasswd.onvalidate = (ev) => {
            //TODO : manage password changes here
        };

        btnChangePasswd.addEventListener('click', (ev) => {
            ev.preventDefault();
            WindowManager.wndPasswd.show();
        });
    }
});