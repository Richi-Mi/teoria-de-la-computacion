import urllib.request
import re

emailPattern = r"[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}"
urlPattern = r"https?://[a-zA-Z0-9.-]+(?:\.[a-zA-Z]{2,})+(?:/[^\s]*)?"

def doRequest( url ):
    with urllib.request.urlopen( url ) as response:
        html = response.read()

        emails = re.findall( emailPattern, str( html ) )
        urls  = re.findall( urlPattern, str( html ) )

        print(f"Correos de { url }: \n")
        print( emails )
        print(f"URL's de { url }: \n")
        print( urls )

url1 = input()
url2 = input()
url3 = input()

doRequest( url1 )
doRequest( url2 )
doRequest( url3 )