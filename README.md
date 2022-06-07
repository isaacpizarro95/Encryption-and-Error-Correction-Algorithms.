Aquest programa conté un algorisme corrector d'errors. És útil quan vols descodificar un missatge que s'ha codificat mitjançant l'algorisme
de Reed-Solomon ja que, en absència d'errors et tornarà el missatge original i si existeixen e < ((p-1)-k/2 errors es corregiran mitjançant
l'algorisme de Berlekamp-Welch. El missatge ha de consistir en elements d'un cos finit (Fp), es a dir, els seus elements, per assegurar el bon
funcionament del programa, han de ser <= p.

Explicació programa PizarroIsaac:
- Llegeix un missatge d'un fitxer del tipus .dat, .bin o .txt. Un altre format tornarà un missatge d'error i aturarà el programa.
- Depenent del paràmetre seleccionat codificarà o descodificarà el missatge llegit. Si el missatge s'ha de descodificar i aquest té errors
s'aplicarà un algorisme de correcció d'errors que podrà corregir fins a ((p-1)-k)/2 errors. Si en té més no podrà corregir-los.
- Després de codificar/descodificar el missatge, escriura el missatge codificat/descodificat en un nou arxiu del mateix tipus que el de lectura,
a excepció de si el de lectura era .txt que llavors serà .txt.bin. En el cas de codificar s'afegirà un .RS i en descodificar un .BW al fitxer.

Us del programa:
- Després de compilar amb gcc -o 'nom_executable' PizarroIsaac.c hi han les següents opcions de paràmetres:
- ./PizarroIsaac configura -p=x -k=y on x,y son nombres naturals. Aquesta opció genera un arxiu de configuració RS-BW.cfg per donar valors
predeterminats a p i k cada cop que es compila el programa. Per exemple: ./PizarroIsaac configura p=31 k=22
- ./PizarroIsaac codifica 'nom_fitxer' -p=x -k=y on p,k són paràmetres opcionals. Si no s'especifica p i k s'assignarà el valor de l'arxiu de
l'arxiu de configuració o, si aquest no existeix, el valors predeterminats al main p=257 i k=200.
- ./PizarroIsaac descodifica 'nom_fitxer' -p=x -k=y. Mateix funcionament que abans.
