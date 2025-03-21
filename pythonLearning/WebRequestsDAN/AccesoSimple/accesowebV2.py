"""

accesoweb.py
VERSION 2.0 

El programa anterior tenía problemas con otros tipos de páginas web.

El error ocurre porque el contenido devuelto por https://www.python.org está comprimido (gzip),
y el programa intenta decodificarlo como si fuera texto sin procesarlo primero.

"""


import urllib.request
import gzip

# URL de la página web
url = "https://www.python.org"

try:
    # Enviar la solicitud HTTP y obtener la respuesta
    with urllib.request.urlopen(url) as response:
        # Verificar si la respuesta está comprimida
        if response.info().get('Content-Encoding') == 'gzip':
            with gzip.GzipFile(fileobj=response) as decompressed:
                html = decompressed.read().decode("utf-8")
        else:
            html = response.read().decode("utf-8")
        
        print(html)  # Imprimir el contenido HTML

except urllib.error.HTTPError as e:
    print(f"Error: {e}")
except urllib.error.URLError as e:
    print(f"Error: {e}")
except Exception as e:
    print(f"Error: {e}")


"""
¿Qué cambia aquí?

Detecta si la respuesta está comprimida (Content-Encoding: gzip).
La descomprime antes de decodificarla en texto UTF-8.

"""