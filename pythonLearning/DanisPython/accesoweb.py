"""
To access to a Web Page using python, we can use the library urllib.request
to send a HTTP request and obtain the page's content.

The following code is a basic example of the use of this library"""

import urllib.request

# URL de la página web a la que deseas acceder
url = "https://www.example.com"

try:
    # Enviar la solicitud HTTP y obtener la respuesta
    with urllib.request.urlopen(url) as response:
        # Leer el contenido de la respuesta
        html = response.read().decode("utf-8")
        print(html) # Imprimir el contenido HTML

except urllib.error.HTTPError as e:
    print(f"Error: {e}")
except urllib.error.URLError as e:
    print(f"Error: {e}")
except Exception as e:
    print(f"Error: {e}")

