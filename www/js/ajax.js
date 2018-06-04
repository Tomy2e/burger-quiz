/****************************************/
/*    ajax.js - burger-quiz          */
/*--------------------------------------*/
/*  Author : Gwenolé Leroy-Ferrec - Tomy Guichard                  */
/*  License : GPL-3.0                */
/*  Defines a basic AJAX request        */
/*  function using the XMLHttpRequest   */
/*  object.                             */
/*               ------                 */
/*  juin 2018                      */
/****************************************/



function ajaxRequest(type, request, callback, data = null)
{
  var xhr;

  // Create XML HTTP request.
  xhr = new XMLHttpRequest();
  if (type == 'GET' && data != null)
    request += '?' + data;
  xhr.open(type, request, true);

  // Add the onload function.
  xhr.onload = function ()
  {
    switch (xhr.status)
    {
      case 200:
      case 201:
        console.log(xhr.responseText);
        callback(xhr.responseText);
        break;
      default:
        httpErrors(xhr.status);
    }
  };

  // Send XML HTTP request.
  xhr.send(data);
}

//------------------------------------------------------------------------------
//--- httpErrors ---------------------------------------------------------------
//------------------------------------------------------------------------------
// Display a message corresponding to an Http error code.
// \param errorNumber the error code.
function httpErrors(errorNumber)
{
  var text;

  text = '[ajax.js] Request error : ';

  switch (errorNumber)
  {
    case 400:
      // Bad request.
      text += '400 Bad Request';
      break;
    case 401:
      // Unauthorized.
      text += '401 Unauthorized';
      break;
    case 403:
      // Forbidden.
      text += '403 Forbidden';
      break;
    case 404:
      // Ressource not found.
      text += '404 Not Found';
      break;
    case 500:
      // Internal server error.
      text += '500 Internal Server Error';
      break;
    case 503:
      // Service unavailable.
      text += '503 Service Unavailable';
      break;
    default:
      text += ' HTTP Error Code : ' + errorNumber;
      break;
  }
  console.log(text);
}