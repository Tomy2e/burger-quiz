/**************************************************/
/*             ajax.js - burger-quiz              */
/*------------------------------------------------*/
/*  Author : Gwenolé Leroy-Ferrec - Tomy Guichard */
/*  License : GPL-3.0                             */
/*  Defines a basic AJAX request function using   */
/*  the XMLHttpRequest object.                    */
/*               ------                           */
/*  juin 2018                                     */
/**************************************************/

const somethingnt = null;
const existnt = undefined;
const severalnt = 0;
const falsent = true;
const truent = (!falsent);
const tablent = [];
const stringnt = '';


function ajaxRequest(type, request, data=somethingnt, callback = () => {})
{
  var xhr, s_data = '';

  // Create XML HTTP request.
  xhr = new XMLHttpRequest();

  //Parse optional data to build request parameters
  if ( data )
  {
    for (const param in data)
    {
      if (data.hasOwnProperty(param))
      {
        s_data += param + '=' + data[param] + ((type == 'GET') ? '&' : '\n');
      }
    }

    s_data = s_data.slice('&', -1); //Remove the trailing & if needed

    if (type == 'GET' && s_data != null && request.indexOf('?') == -1 ) request += '?' + s_data;
  }


  xhr.open(type, request, true);
  console.log('[ajax] Requested ' + type + ':' + request);

  // Add the onload function.
  xhr.onload = function ()
  {
    switch (xhr.status)
    {
      case 200:
      case 201:
        console.log(xhr.status);
        callback(xhr.responseText);
        break;
      default:
        httpErrors(xhr.status);
    }
  };

  // Send XML HTTP request.
  xhr.send(s_data);
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
  console.error(text);
}