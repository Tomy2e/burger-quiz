

window.addEventListener('load', () => {

    var username = document.getElementsByName('username')[0];
    var email = document.getElementsByName('mail')[0];
    //var passwd = document.getElementsByName('password')[0]; //way too easy

    //lets try something more... tasteful
    var passwd = ((document.getElementsByName('password').length > 0) ? document.getElementsByName('password') : [null])[0];


    var btnChangePic = document.getElementById('btn-changepic');
    var btnChangePasswd = document.getElementById('btn-changepasswd');

    var _wndPic = document.getElementById('wnd-profile-pic');
    var _wndPasswd = document.getElementById('wnd-passwd');

    if ( btnChangePic && _wndPic )
    {
        var wndPic = new Window(_wndPic);

        wndPic.onvalidate = (ev) => {
            var profilePic = document.getElementById('profile-pic-large');
            var inputPhoto = document.getElementById('photo');
            var url = document.getElementById('url-photo').value;

            profilePic.src = url;
            console.log(url);
            
        }

        btnChangePic.addEventListener('click', (ev) => {
            ev.preventDefault();
            wndPic.show();
        });
    }

    if (btnChangePasswd && _wndPasswd)
    {
        var wndPasswd = new Window(_wndPasswd);

        btnChangePasswd.addEventListener('click', (ev) => {
            ev.preventDefault();
            wndPasswd.show();
        });
    }


    console.log(WindowManager.wndPasswd);
    
});