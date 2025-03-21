import urllib.request
import gzip
import re

# Solicitar URL y palabra clave al usuario
url = input("Ingresa la URL de la página web: ")
word = input("Ingresa la palabra que quieres buscar: ")

try:
    # Enviar la solicitud HTTP y obtener la respuesta
    with urllib.request.urlopen(url) as response:
        # Verificar si la respuesta está comprimida
        if response.info().get('Content-Encoding') == 'gzip':
            with gzip.GzipFile(fileobj=response) as decompressed:
                html = decompressed.read().decode("utf-8", errors="ignore")
        else:
            html = response.read().decode("utf-8", errors="ignore")

    # Buscar la palabra en el HTML usando expresiones regulares
    matches = [(m.start(), m.end()) for m in re.finditer(re.escape(word), html, re.IGNORECASE)]

    # Mostrar los resultados
    if matches:
        print(f"\nLa palabra '{word}' se encontró {len(matches)} veces en la página.\n")
        # Muestra hasta 10 coincidencias
        # for i, (start, end) in enumerate(matches[:10], 1):  

        #Muestra TODAS las coincidencias
        for i, (start, end) in enumerate(matches, 1):  
            print(f"{i}. Posición: {start}-{end} | Fragmento: ...{html[max(0, start-30):min(len(html), end+30)]}...")
    else:
        print(f"\nLa palabra '{word}' no se encontró en la página.")

except urllib.error.HTTPError as e:
    print(f"Error HTTP: {e}")
except urllib.error.URLError as e:
    print(f"Error de conexión: {e}")
except Exception as e:
    print(f"Error inesperado: {e}")
