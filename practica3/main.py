"""
Buscador de expresión regular que conforma un correo electrónico y links presentes en una página web.

Entrada:
Este programa recibe 3 URL del usuario, de paginas web donde se sabe que puede haber correos electrónicos o links.

Salida:
El programa genera 2 archivos de salida.
Correos.txt: Almacena todos los correos presentes en cada uno de los URL
Links.txt: Almacena los link presentes en los 3 URL.

"""


import urllib.request
import re

#Solicitamos al usuario los 3 URL

url1 = input("Ingresa la URL de la página web: ")
url2 = input("Ingresa la URL de la página web: ")
url3 = input("Ingresa la URL de la página web: ")

#Definimos la expresión regular de un correo electrónico.



"""
Para evitar bloqueos al hacer la solicitud HTTP, agregamos un "User-Agent" en los headers.
Algunas páginas web bloquean solicitudes sin un User-Agent válido porque parecen ser de bots.
Aquí estamos simulando el User-Agent de un navegador Chrome.
"""
headers = {
    "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/110.0.0.0 Safari/537.36"
}

# Creamos la solicitud HTTP con los headers
req = urllib.request.Request(url, headers=headers)

try:
    """ 
    Enviamos la solicitud HTTP y leemos la respuesta.
    La página web se obtiene en bytes, por lo que la decodificamos a UTF-8 para manejar texto.
    """
    with urllib.request.urlopen(req) as response:
        html = response.read().decode("utf-8")

    """ 
    #Expresión regular para buscar la palabra exacta en el HTML.
    
    Patrón explicado:
    - (?:^|[\s.,!?;:"'()<>-]) → Asegura que la palabra no esté dentro de otra.
      - `^` → Puede estar al inicio del texto.
      - `[\s.,!?;:"'()<>-]` → También puede estar precedida por un espacio o un signo de puntuación.

    - (" + re.escape(palabra) + ") → La palabra exacta que buscamos.
      - `re.escape(palabra)` → Escapa caracteres especiales en la palabra (por seguridad).
      - `()` → Captura la coincidencia para extraer la posición de inicio y fin.

    - (?:[\s.,!?;:"'()<>-]|$) → Asegura que la palabra termine correctamente.
      - `[\s.,!?;:"'()<>-]` → Debe estar seguida de un espacio o un signo de puntuación.
      - `$` → También puede estar al final del texto.

    - `re.IGNORECASE` → Permite coincidencias sin distinguir mayúsculas o minúsculas.
    """
    pattern = re.compile(r"(?:^|[\s.,!?;:\"'()<>-])(" + re.escape(palabra) + r")(?:[\s.,!?;:\"'()<>-]|$)", re.IGNORECASE)

    """
    `finditer()` busca todas las coincidencias en el texto y devuelve objetos Match.
    Extraemos las posiciones de inicio y fin de cada coincidencia.
    """
    matches = [(m.start(1), m.end(1)) for m in pattern.finditer(html)]

    """ 
    Si encontramos coincidencias, mostramos cuántas hay y hasta 10 fragmentos de contexto.
    Extraemos un poco de texto antes y después para dar mejor visualización.
    """
    if matches:
        print(f"\n🔍 Se encontraron {len(matches)} coincidencias exactas de '{palabra}':\n")
        for i, (start, end) in enumerate(matches, 1):  # Muestra hasta 10 fragmentos
            fragmento = html[max(0, start - 30): min(len(html), end + 30)]
            print(f"{i}. ...{fragmento.strip()}...")
    else:
        print(f"\n❌ No se encontró la palabra exacta '{palabra}' en la página.")

except urllib.error.HTTPError as e:
    """ 
    Captura errores HTTP (como 403 Forbidden, 404 Not Found, etc.).
    """
    print(f"Error HTTP: {e}")
except urllib.error.URLError as e:
    """ 
    Captura errores de conexión o direcciones inválidas.
    """
    print(f"Error de URL: {e}")
except Exception as e:
    """ 
    Captura cualquier otro error inesperado para evitar que el programa se detenga bruscamente.
    """
    print(f"Error inesperado: {e}")
