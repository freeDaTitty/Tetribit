# Tetribit
The game of Tetris on bytes

Pentru ca programul sa functioneze corespunzator, am folosit
urmatoarele variabile si metode, dupa cum sunt scrise in program astfel:
- am inclus biblioteca <math.h> pentru a efectua anumite operatii matematice
- harta este o variabila ce memoreaza harta
- numar_mutari retine numarul de mutari
- i este un contor de numarare prin care accesez fiecare piesa
- j este tot un contor de numarare, dar prin care accesez fiecare transformare
- transformare retine transformarea introdusa de la tastatura
- numar_Linii_Complete retine numarul liniilor complete

Pentru inceput, citesc harta si o generez. Apoi, pentru a putea muta
piesele fara ca ele sa iasa din harta, am initilizat 2 masti,
masca_dreapta, respectiv masca_stanga ce vor primi valorile unei
coloane pline de 1, ultima, respectiv prima coloana.

Citesc numarul de mutari, le parcurg, citesc si fiecare piesa, in cazul
in care exista, iar apoi, pentru a nu pierde valoarea hartii si nici a piesei
voi initializa un fel de copii ale acestora, care isi pot schimba valorile,
intocmai pentru a nu se pierde cele initiale.

In cazul in care are loc o coliziune, piesa nu mai poate fi mutata si, 
totusi, mai avem transformari de citit, am initializat o variabila
rest_transformari cu -1.

Citesc fiecare transformare, daca suntem pe prima linie, afisam partea
de jos a unei piese(in cazul in care e pe 2 randuri), in cazul in care suntem
pe a 2 a linia, o afisam complet, altfel doar o coboram.

Citim transformarea, iar daca piesa nu poate fi coborata, o urcam la locul
ei de drept, citim si restul transformarilor si trecem la urmatoarea piesa.
Altfel, mutam piesa cu cate o pozitie in directia indicata (- la stanga,
 + la dreapta), pana nu se mai poate. Pentru a verifica daca am mutat piesa cat
s a putut, am luat o variabila numita contor. Daca piesa ar fi atins marginea
hartii sau ar fi facut coliziune cu alta piesa sau cu harta insasi, incetam.

Desigur, pentru a retine harta, o uneam cu piesa aflata in pozitia finala
a sa, iar apoi o afisam. Penrtu a verifica daca avem linii complete, parcurgeam
harta finala, iar, daca gaseam 8 puncte pe linie, le eliminam. Am declarat 2
variabile de numarare a liniilor complete pentru:
	-a afisa harta fara liniile complete
	-a folosi in calcularea scorului
	-a nu se pierde valoarea, astfel incat harta sa nu fie afisata corect

In cazul in care sunt la ultima mutare, iar alte transformari "nu si mai
au rostul", afisez harta o singura data, pentru a nu afisa acelasi lucru
de mai multe ori. Ar fi degeaba.
	
Cazul Special al jocului era atins in momentul in care o piesa aflata
pe 2 linii nu cobora complet. Daca acest lucru se intampla la a 2 a mutare,
generam harta propriu zisa si incheiam jocul.
	
Am calculat apoi numarul de 0 uri intr o variabila nr_Zero.

Pentru a nu incarca functia principala main mai mult decat este, am
declarat 3 functii cheie.
	-Verificare_Linie_Complete pentru a verifica daca avem linie completa.
Pentru aceasta verificare, am impartit harta in 2. Harta de deasupra
liniei complete, pe care am coborat o si urcat o la loc pentru a se pierde
valorile de sub, cu tot cu linia completa, si harta de sub linia completa,
pe care am urcat o si coborat o la loc pentru a se pierde valorile de deasupra,
cu tot cu linia completa. Le am unit apoi, pentru a face o harta in care
liniile complete sunt complet eliminate.

-Generare_Hara pentru a genera harta.
Fiind o harta de 64 de biti, am parcurs o de la coada la cap pentru a o 
afisa corespunzator, semanand cu o harta initiala de tetris.

-Parcurgere_Harta pentru a parcurge harta si a calcula numarul
de zerouri, folosit in ecuatia de calcul a scorului.
