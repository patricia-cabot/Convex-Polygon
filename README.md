# Pràctica de AP2: Polígons convexos
## Documentació general

**Instalació**

Per utilitzar el programa només cal descarregar-se els arxius i tenir un compilador de c++. Per visualitzar els documents, serveix qualsevol editor de text.

Per utilitzar la comanda draw, s'ha de tenir descarregada la llibreria draw. Per fer-ho, s'ha d'escriure la comanda següent a la terminal:

`git clone https://github.com/pngwriter/pngwriter.git`

Després hem de compilar la lliberira:

`cd pngwriter`

`cmake -DPNGwriter_USE_FREETYPE=OFF -DCMAKE_INSTALL_PREFIX=$HOME/libs .`

`make`

`make install`


**Compilació**

En el fitxer `Makefile` tenim un recull de les comandes necessàries per fer servir el treball. Hem d'escriure la comanda `make` a la terminal per compilar i `./main.exe` per executar.


**Convex Polygon calculator**

Tenim una àmplia col·lecció de operacions que es poden utilitzar. Aquí es troba la informació necessària per fer un bon ús del programa:

* **_Definir poligons_** : amb la comanda `polygon`. Primer introduim el nom del polígon i després els punts que volem que el formin. Al acabar escriurà "ok"
* **_Donar els punts d'un polygon_**: amb la comanda `print`. Hem de introduir el nom del polígon. En cas que el polígon estigui buit, escriurà " the polygon is empty"
* **_Intersecció de polígons_**: amb la comanda `intersection`. Podem introduir o dos (p1, p2) o tres polígons (p1, p2, p3). En el primer cas, farem la intersecció dels polígons p1 i p2 i es guardarà en el polígon p1. En el segon cas, farem la intersecció dels poligons p2 i p3 i guardarem la intersecció en el polígon p1. Al acabar escriurà "ok".
* **_Unió de polígons_**: amb la comanda `union`. Podem introduir o dos (p1, p2) o tres polígons (p1, p2, p3). En el primer cas, farem la unió dels polígons p1 i p2 i es guardarà en el polígon p1. En el segon cas, farem la unió dels poligons p2 i p3 i guardarem la unió en el polígon p1. Al acabar escriurà "ok".
* **_Bounding box_**: amb la comanda `bbox`. Primer introduirem el nom de la boundin box i després tot els polígons que volem que contingui. Al acabar escriurà "ok".
* **_Saber si un polígon està dins d'un altre polígon_**: amb la comanda `inside`. Primer introduim el nom del polígon que volem que volem saber si conté el segon. En cas que el primer estigui buit, escriurà " is empty, so it cannot contain another polygon"; en cas que el segon estigui buit, escriurà " is empty, so it cannot be contained". Si no es dona cap dels dos casos, el programa escriurà "yes" en cas que el primer polígon contingui el segon i "no", altrament,
* **_Saber si un punt està dins d'un polígon_**: amb la comanda `point_inside`. Primer introduim el nom del polígon i després donem les coordenades (x,y) del punt que volem saber si es contingut. En cas que el primer estigui buit, escriurà " is empty, so it cannot contain a point". Si no es dona el cas, escriurà "yes" si el polígon conté el punt i "no", altrament.
* **_Nombre de vèrtex_**: amb la comanda `vertices`. Introduim el nom del polígon que retorna el nombre de vèrtex del polígon.
* **_Nombre d'arestes_**: amb la comanda `edges`. Introduim el nom del polígon que retorna el nombre d'arestes del polígon.
* **_Perímetre_**: amb la comanda `perimeter`. Introduim el nom del polígon que retorna la llargada del perímetre del polígon.
* **_Àrea_**: amb la comanda `area`. Introduim el nom del polígon que retorna l'area del polígon.
* **_Saber si un polígon és regular_**: amb la comanda `regular`. Introduim el nom del polígon que retorna "yes" si el polígon és regular i "no", altrament.
* **_Punt centroid del polígon_**: amb la comanda `centroid`. Introduim el nom del polígon que retorna les coordenades (x,y) del punt centroid del polígon.
* **_Saber si un polígon està buit_**: amb la comanda `empty`. Introduim el nom del polígon que retorna "yes" si el polígon està buit i "no", altrament.
* **_Saber si un polígon és monògon_**: amb la comanda `monogon`. Introduim el nom del polígon que retorna "yes" si el polígon és monògon i "no", altrament.
* **_Saber si un polígon és dígon_**: amb la comanda `digon`. Introduim el nom del polígon que retorna "yes" si el polígon és dígon i "no", altrament.
* **_Saber els colors actuals d'un polígon_**: amb la comanda `give_colors`. Introduim el nom del polígon que retorna els colors del polígon amb el color que representen (red, green, blue).
* **_Guardar polígons en un arxiu .txt_**: amb la comanda `save`. Introduim el nom del fitxer i després els polígons que volem guardar*hi. En cas de introduir un polígon que no existeix, el programa retornarà l'error(4) i seguirà guardant polígons, ignorant el que no existia. Al acabar escriurà "ok".
* **_Carregar polígons guardats en un arxiu .txt_**: amb la comanda `load`. Introduim el nom del fitxer que volem carregar. Al acabar escriurà "ok".
* **_Donar una llista amb els polígons actuals_**: amb la comanda `list`. Si la llista està buida, escriurà "There are no polygons". Altrament, escriurà una llista amb els polígons actuals.
* **_Canviar el color del polígon_**: amb la comanda `setcol`. Introduim el nom del polígon que volem canviar el color i després introduim els números que indiquen la quantitat de cada dolor, vermell, verd i blau respectivament. Si els números introduits son més petits que 0 o més gran que 1, donarà error(3). Si no hi ha cap problema, al acabar escriurà "ok".
* **_Dibuixar polígons en un arxiu png_**: amb la comanda `draw`. Primer introduim el nom de l'arxiu png i després els polígons que volem dibuixar*hi. Al acabar escriurà "ok".

* **_Errors_**: llista d'errors possibles:
 1. _error(1)_: "error: unrecognized command" : si la comanda no coincideix amb les existents.
 2. _error(2)_: "error: polygon not defined yet" : si estem intentant cridar un polígon que no existeix.
 3. _error(3)_: "error: wrong format" : si utilitzem comandes que no encaixen amb els demanats.
 4. _error(4)_: "error: command with wrong number or type of arguments" : si utilitzem paràmetres erronis o el nombre de paràmetres és incorrecte.

* **_Comanda `#`_**: serveix per fer comentaris. Retorna "#".
