import urllib.request
import re

# Pedir URL y palabras a buscar
url = input("Ingresa la URL de la página web: ")
palabra1 = input("Ingresa la primera palabra que quieres buscar: ")
palabra2 = input("Ingresa la segunda palabra que quieres buscar: ")

# Definir headers para simular un navegador
headers = {
    "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/110.0.0.0 Safari/537.36"
}

# Crear solicitud con headers
req = urllib.request.Request(url, headers=headers)

try:
    with urllib.request.urlopen(req) as response:
        html = response.read().decode("utf-8")

    # Expresión regular para buscar "palabra1" seguida de "palabra2" con separadores
    pattern = re.compile(
        r"(?:^|[\s.,!?;:\"'()<>-])(.{0,30}" + re.escape(palabra1) + r"[\s]+"
        + re.escape(palabra2) + r".{0,30})(?:[\s.,!?;:\"'()<>-]|$)", re.IGNORECASE
    )

    matches = pattern.findall(html)

    # Mostrar resultados
    if matches:
        print(f"\n🔍 Se encontraron {len(matches)} coincidencias exactas de '{palabra1} {palabra2}':\n")
        for i, fragmento in enumerate(matches, 1):
            print(f"{i}. ...{fragmento.strip()}...")
    else:
        print(f"\n❌ No se encontró la combinación '{palabra1} {palabra2}' en la página.")

except urllib.error.HTTPError as e:
    print(f"Error HTTP: {e}")
except urllib.error.URLError as e:
    print(f"Error de URL: {e}")
except Exception as e:
    print(f"Error inesperado: {e}")
