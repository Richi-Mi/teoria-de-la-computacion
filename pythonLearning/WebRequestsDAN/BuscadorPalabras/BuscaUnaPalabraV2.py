"""

Este programa soluciona el bloqueo que pueden tener algunos servidores.

-  Explicación del cambio
Se usa urllib.request.Request(url, headers=headers) → Esto le dice al servidor que el programa es un navegador (en este caso, Chrome en Windows).
Se usa headers["User-Agent"] → Sin esto, el servidor puede rechazar la solicitud.
Se mantiene la lógica de búsqueda → Pero ahora la solicitud tiene más probabilidades de éxito.

"""


import urllib.request
import re

# Pedir URL y palabra a buscar
url = input("Ingresa la URL de la página web: ")
palabra = input("Ingresa la palabra que quieres buscar: ")

# Definir headers para simular un navegador
headers = {
    "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/110.0.0.0 Safari/537.36"
}

# Crear solicitud con headers
req = urllib.request.Request(url, headers=headers)

try:
    # Enviar solicitud y obtener respuesta
    with urllib.request.urlopen(req) as response:
        html = response.read().decode("utf-8")

    # Buscar todas las coincidencias con contexto
    pattern = re.compile(r"(.{0,30}" + re.escape(palabra) + r".{0,30})", re.IGNORECASE)
    matches = pattern.findall(html)

    # Mostrar resultados
    if matches:
        print(f"\n🔍 Se encontraron {len(matches)} coincidencias de '{palabra}':\n")
        for i, fragmento in enumerate(matches, 1):  # Muestra hasta 10 fragmentos
            print(f"{i}. ...{fragmento.strip()}...")
    else:
        print(f"\n❌ No se encontró la palabra '{palabra}' en la página.")

except urllib.error.HTTPError as e:
    print(f"Error HTTP: {e}")
except urllib.error.URLError as e:
    print(f"Error de URL: {e}")
except Exception as e:
    print(f"Error inesperado: {e}")
