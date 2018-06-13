

window.addEventListener('load', () => {

    var username = document.getElementsByName('username')[0];
    var email = document.getElementsByName('mail')[0];
    //var passwd = document.getElementsByName('password')[0]; //way too easy

    //lets try something more... tasteful
    var passwd = ((document.getElementsByName('password').length > 0) ? document.getElementsByName('password') : [null])[0];
    
    console.log(passwd);
    
});