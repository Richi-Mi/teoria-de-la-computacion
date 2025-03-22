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

# Solicitamos las 3 URLs al usuario MEJOR MANEJO EN UNA LISTA
urls = [input(f"Ingrese la URL {i+1}: ") for i in range(3)]


#Definimos la expresión regular de un correo electrónico.

# Expresión regular para correos electrónicos
regex_correo = re.compile(r"[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}")

# Expresión regular para links
regex_link = re.compile(r'href=["\'](https?://[^"\']+)["\']')

#Creamos los dos archivos de salida para correos y LINKS

# Creamos los archivos de salida e iteramos por cada URL buscando las coincidencias.
with open("correos.txt", "w") as file1, open("links.txt", "w") as file2:
    for url in urls:
        print(f"\n🔍 Analizando: {url}")

        # Definir headers para simular un navegador
        headers = {
            "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/110.0.0.0 Safari/537.36"
        }

        # Hacer la solicitud HTTP
        try:
            req = urllib.request.Request(url, headers=headers)
            with urllib.request.urlopen(req) as response:
                html = response.read().decode("utf-8")

            # Buscar correos
            correos = regex_correo.findall(html)
            if correos:
                file1.write(f"\nCorreos encontrados en {url}:\n" + "\n".join(set(correos)) + "\n")
                print(f"📩 {len(correos)} correos encontrados.")
            else:
                print("❌ No se encontraron correos.")

            # Buscar links
            links = regex_link.findall(html)
            if links:
                file2.write(f"\nLinks encontrados en {url}:\n" + "\n".join(set(links)) + "\n")
                print(f"🌐 {len(links)} links encontrados.")
            else:
                print("❌ No se encontraron links.")

        except urllib.error.HTTPError as e:
            print(f"⚠️ Error HTTP: {e}")
        except urllib.error.URLError as e:
            print(f"⚠️ Error de URL: {e}")
        except Exception as e:
            print(f"⚠️ Error inesperado: {e}")
