/*
*Dinu Daniel, 314CB
*/

/*
* Pentru a efectua anumite calcule matematice,
* introduc, in plus, biblioteca <math.h> .
*/

#include <stdio.h>
#include <math.h>

/*
* Pentru a verifica daca exista o linie completa si pentru a o elimina din 
* harta, am conceput un subprogram in care despart harta in 2, in functie
* de liniile complete, deasupra si sub ele, mai apoi unindu le.
*/


unsigned long long Verificare_Linie_Completa(unsigned long long harta, int indice_harta)
{
    unsigned long long harta_deasupra_liniei = harta , harta_sub_linie = harta;

    harta_deasupra_liniei >>= ((unsigned long long)indice_harta + 8ULL);

    harta_deasupra_liniei <<= ((unsigned long long)indice_harta + 8ULL);

    harta_deasupra_liniei >>= 8;

    harta_sub_linie <<= (63 - (unsigned long long)indice_harta);
    harta_sub_linie <<= 1;



    harta_sub_linie >>= (63 - (unsigned long long)indice_harta);
    harta_sub_linie >>= 1;

    harta = (harta_deasupra_liniei | harta_sub_linie);

    return harta;
}

/*
* Pentru a genera harta corespunzator, am parcurs o de la coada la
* cap, astfel incat aceasta sa semene cu o tabla de tetris, de 8x8.
*/

void Generare_Harta(unsigned long long harta)
{
    int indice_harta;

    for(indice_harta = 63; indice_harta >= 0; indice_harta--)
    {

        if((harta >> (unsigned long long)indice_harta) & 1)
        {
            printf("#");
        }

        else
        {
            printf(".");
        }

        if(indice_harta % 8 == 0)
        {
            printf("\n");
        }
    }
    printf("\n");
}

/*
* Pentru a determina numarul de zerouri ce ne va ajuta la 
* calculul scorului, parcurg harta si scad fiecare bit ce
* are valoarea 1 din 64. (puncte pe tabla de 8x8)
*/

int Parcurgere_Harta(unsigned long long harta, int nr_Zero)
{
    int indice_harta;

    for(indice_harta = 63; indice_harta >= 0; indice_harta--)
    {

        if((harta >> (unsigned long long)indice_harta) & 1)
        {
            nr_Zero--;
        }
    }

    return nr_Zero;
}


int main()
{
	/*
	* i si j sunt folosite pentru a parcurge fiecare piesa, respectiv 
	* transformare.	
	*/

    unsigned long long harta;
    int indice;
    int numar_mutari, i, j, transformare;
    int numar_Linii_Complete= 0;

    scanf("%llu", &harta);
    Generare_Harta(harta);

	/*
	* Pentru a nu depasi marginea tablei, am compus 2 masti care sa
	* ia valorile primei si ultimei coloane.
	*/

    unsigned long long masca_stanga = 0, masca_dreapta = 0;

    for(indice = 0; indice < 57; indice += 8)
    {
        masca_dreapta += pow(2, indice);
    }

    for(indice = 7; indice < 64; indice += 8)
    {
        masca_stanga += pow(2, indice);
    }

    scanf("%d", &numar_mutari);
    for(i = 0; i < numar_mutari; i++)
    {
        unsigned long long piesa;

        scanf("%llu", &piesa);

		/*
		* Nu mi doresc sa pierd valorile initiale ale hartii si
		* piesei, asa ca le copiez in alte 2 variabile, pozitie_noua
		* fiind piesa asezata pe pozitia curenta, dupa fiecare
		* transformare.
		*/

        unsigned long long harta_noua, pozitie_noua;

		/*
		* Daca mai sunt transformari de citit, dar nu isi mai au rostul
		* declar o variabila cu ajutorul careia sa le citesc si atat.
		*/

        int rest_transformari = -1;

        for(j = 0; j < 8; j++)
        {
            harta_noua = harta;

            rest_transformari++;

			/*
			* Afisez partea de jos a piesei daca sunt pe primul rand.
			*/

            if(j == 0)
            {
                pozitie_noua = piesa << 56;
            }

			/*
			* Afisez piesa intreaga daca sunt pe al doilea rand, iar
			* piesa e pe 2 linii.
			*/

            else if (j == 1)
            {
                pozitie_noua = piesa << 48;
            }

			/*
			* Cobor piesa cu cate un nivel.
			*/

            else if (j != 0)
            {
                pozitie_noua >>= 8;
            }

            scanf("%d", &transformare);

			/*
			* In cazul in care piesa nu mai poate cobori si mai sunt
			* trasnformari de citit, le citesc si trec la urmatoarea
			* piesa.
			*/

            if((harta_noua & pozitie_noua) != 0)
            {
                harta_noua |= (pozitie_noua <<= 8);
                while(rest_transformari < 7)
                {
                    rest_transformari++;
                    scanf("%d", &transformare);
                }
                break;
            }

			/*
			* Mut piesa fie in stanga (semn negativ), fie in dreapta
			* (semn pozitiv) cu cate o pozitie pana cand fie fac coliziune
			* cu harta, fie cu peretii hartii.
			*/

            if(transformare < 0)
            {
                int contor = 0;
                while(((pozitie_noua & masca_stanga) == 0))
                {
                    pozitie_noua <<= 1;
                    piesa <<= 1;
                    if((harta_noua & pozitie_noua) != 0)
                    {
                        piesa >>= 1;
                        pozitie_noua >>= 1;
                        break;
                    }
                    contor++;
                    if(contor == (0 - transformare))
                        break;
                }
            }

            else if(transformare > 0)
            {
                int contor = 0;
                while(((pozitie_noua & masca_dreapta) == 0))
                {
                    piesa >>= 1;
                    pozitie_noua >>= 1;
                    if((harta_noua & pozitie_noua) != 0)
                    {
                        piesa <<= 1;
                        pozitie_noua <<= 1;
                        break;
                    }
                    contor++;
                    if(contor == transformare)
                        break;
                }
            }

			/*
			* Memorez harta noua si o afisez.
			*/

            harta_noua |= pozitie_noua;

            Generare_Harta(harta_noua);
        }

		/*
		* Verific daca exista linii pline.
		*/

        int puncte_pe_linie = 0, copie_numar_Linii_Complete= 0;
	int indice_harta;

        for(indice_harta = 63; indice_harta >= 0; indice_harta--)
        {
            if((harta_noua >> indice_harta) & 1)
            {
                puncte_pe_linie++;
            }
            if(indice_harta % 8 == 0)
            {
                if(puncte_pe_linie == 8)
                {
					/*
					* Daca exista, le numar pentru calculul scorului, le scot 
					* si creez o copie pentru a afisa harta fara ele.
					*/

                    copie_numar_Linii_Complete++;
                    numar_Linii_Complete++;
                    harta_noua = Verificare_Linie_Completa(harta_noua, indice_harta);
                }

                puncte_pe_linie = 0;
            }
        }
        if(copie_numar_Linii_Complete> 0)
        {
            Generare_Harta(harta_noua);
            copie_numar_Linii_Complete= 0;
        }

		/*
		* Afisez harta o singura data in cazul in care nu mai pot avea 
		* alte mutari.
		*/

        if(i == numar_mutari - 1)
        {
            if((harta_noua | (pozitie_noua << 8)) == harta_noua)
                Generare_Harta(harta_noua);
            harta = harta_noua;
            break;
        }

		/*
		* Caz Special
		* Daca introduc o piesa aflata pe 2 linii si nu se introduce
		* complet pentru ca nu mai are loc, inchei jocul.
		*/

        if(j == 1)
        {
            if((((harta_noua) - harta) >> 8) != (piesa << 48))
            {
                Generare_Harta(harta_noua);
                harta = harta_noua;
                break;
            }
        }

        harta = harta_noua;
    }

	/*
	* Calculez numarul de zerouri.
	*/

    int nr_Zero = 64;
    nr_Zero = Parcurgere_Harta(harta, nr_Zero);

	/*
	* Calculez scorul.
	*/	

    float scor = (sqrt(nr_Zero) + pow(1.25, numar_Linii_Complete));

    printf("GAME OVER!\nScore:%.2f", scor);

    return 0;
}
