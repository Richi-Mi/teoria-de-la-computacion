# Libreria URLIB de PYTHON


Información extraída de: https://docs.python.org/es/3/howto/urllib2.html

## Intro

urllib.request es un módulo Python para acceder y utilizar recursos de internet identificados por URLs (Uniform Resource Locators). Ofrece una interfaz muy simple, a través de la función urlopen. Esta función es capaz de acceder a URLs usando una variedad de protocolos diferentes. También ofrece una interfaz un poco más compleja para manejar situaciones comunes - como la autenticación básica, cookies y proxies, entre otros. Estos son proporcionados por los llamados objetos de apertura y gestores.

urllib.request soporta la obtención de recursos identificados por URLs para muchos «esquemas de URL» (identificados por la cadena de texto ubicada antes del ":" en el URL - por ejemplo "ftp" es el esquema de URL de "ftp://python.org/") usando sus protocolos de red asociados (por ejemplo FTP, HTTP). Este tutorial se centra en el caso más común, HTTP.

## Gestión de excepciones

urlopen raises URLError when it cannot handle a response (though as usual with Python APIs, built-in exceptions such as ValueError, TypeError etc. may also be raised).

HTTPError is the subclass of URLError raised in the specific case of HTTP URLs.

Las clases de excepción se exportan desde el módulo urllib.error.

## Manejo de errores

- HTTPError

Every HTTP response from the server contains a numeric «status code». Sometimes the status code indicates that the server is unable to fulfil the request. The default handlers will handle some of these responses for you (for example, if the response is a «redirection» that requests the client fetch the document from a different URL, urllib will handle that for you). For those it can’t handle, urlopen will raise an HTTPError. Typical errors include “404” (page not found), “403” (request forbidden), and “401” (authentication required).