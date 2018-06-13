/****************************************************/
/*				main.js - burger-quiz				*/
/*--------------------------------------------------*/
/*	Author : Gwenolé Leroy-Ferrec - Tomy Guichard	*/
/*	License : GPL-3.0								*/
/*	juin 2018										*/
/****************************************************/

/* Attaches an event listener that will be only fired once */
Element.prototype.fireOnce = function (event, callback)
{
	this.addEventListener(event, function (e) {
		//Remove the event listener
		e.target.removeEventListener(e.type, arguments.callee);
		//Call the callback
		return callback(e);
	});
}

var _GET = new URL(location.href).searchParams;

window.addEventListener('load', function ()
{
	initNav();
	updateMarkerPosition();

	window.onresize = updateMarkerPosition();

	var profileWindow = new Window(this.document.getElementById('profile-modal'));

	var profileWindowToggler = document.getElementById('profile-selector');

	if ( profileWindow && profileWindowToggler )
	{
		profileWindowToggler.addEventListener('click', (event) => {
			profileWindow.toggle();
		});

		var buttons = this.document.querySelectorAll('#profile-modal .button');

		for (const button of buttons) {
			button.addEventListener('click', (ev) => {
				profileWindow.hide();
			});
		}
	}

	var mainContent = document.querySelector('body > div.main-content');

	if ( mainContent )
	{
		mainContent.style.opacity = "1";

		window.onbeforeunload = () => {
			mainContent.style.opacity = "0";
		}
	}
});

