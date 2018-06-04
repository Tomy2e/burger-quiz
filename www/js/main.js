/****************************************************/
/*				main.js - burger-quiz				*/
/*--------------------------------------------------*/
/*	Author : Gwenolé Leroy-Ferrec - Tomy Guichard	*/
/*	License : GPL-3.0								*/
/*	juin 2018										*/
/****************************************************/


window.onload = function ()
{
	initNav();
	updateMarkerPosition();

	var profileWindow = new Window(this.document.getElementById('profile-modal'));

	var profileWindowToggler = document.getElementById('profile-selector');

	profileWindowToggler.addEventListener('click', (event) => {
		profileWindow.toggle();
	})
}