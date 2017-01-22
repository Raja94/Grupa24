#include "korisnik.h"
#include "dionica.h"
#include "kompanija.h"
#include <stdio.h>
#include <stdlib.h>
int main()
{
    STATISTIKA s;
    s.racun=0;s.stanjeA=0;s.stanjeB=0;s.stanjeC=0;s.stanjeD=0;s.suma=0;
    char v,h,c,k;
    char ime_cvora[21];
    int b;
    do
    {
        printf("Unesite komandu:\n P-Prijava\n X-Izlaz\n");
        scanf("\n%c",&v);
        system("cls");

        if(v=='P')
        {
            b=login();
            system("cls");
            printf("Ulogovali ste se kao %s\n", ((b == 1) ? "Admin" :  "Operater"));
            printf("Unesite naziv cvora na kom radite: ");
            scanf("%s", ime_cvora);
            system("cls");

            if(b==1)
            {
                do
                {
                    printf("\nUnesite komandu:\n Z-Rad sa zaposlenim\n D-Rad sa dionicama\n K-Rad sa kompanijama\n S-Statistika\n X-Odjava\n");
                    scanf("\n%c",&c);
                    system("cls");

                    if (c=='S') statistika(&s);
                    else
                        if(c=='Z')
                    {
                        do
                        {
                            printf("\nUnesite komandu:\n D-Dodavanje radnika\n B-Brisanje radnika\n P-Prikaz radnika\n I-Izmjena radnika\n X-Izlaz\n");
                            scanf("\n%c", &k);
                            system("cls");

                            if(k=='D') b=dodavanje_radnika();
                            else if (k=='B') brisanje_radnika();
                            else if (k=='P') prikaz_radnika();
                            else if (k=='I') edit_radnika();
                            else if (k!='X') printf("Pogresna komanda!\n");
                        }while(k!='X');
                    }
                    else if(c=='D')
                    {
                        do
                        {
                            printf("\nUnesite komandu:\n D-Dodavanje dionice\n B-Brisanje dionice\n P-Prikaz dionica\n I-Izmjena dionice\n X-Izlaz\n");
                            scanf("\n%c", &k);
                            system("cls");

                            if(k=='D') upisivanjeDionice();
                            else if (k=='B') brisanje_dionice();
                            else if (k=='P') prikaz_dionica();
                            else if (k=='I') izmjena_dionice();
                            else if (k!='X') printf("Pogresna komanda!\n");
                        }while(k!='X');
                    }
                    else if(c=='K')
                    {
                        do
                        {
                            printf("\nUnesite komandu:\n D-Dodavanje kompanije\n B-Brisanje kompanije\n P-Prikaz kompanija\n X-Izlaz\n");
                            scanf("\n%c", &k);
                            system("cls");

                            if(k=='D') upisivanjeKompanije();
                            else if (k=='B') brisanje_kompanije();
                            else if (k=='P') prikaz_kompanije();
                            else if (k!='X') printf("Pogresna komanda!\n");
                        }while(k!='X');
                    }
                    else  if (c!='X') printf("Pogresna komanda!\n");
                }
                while(c!='X');

            }
            else if(b==2)
            {
                do
                {
                    printf("\nUnesite komandu:\n P-Putarina\n S-Statistika\n X-Odjava\n");
                    scanf("\n%c",&h);
                    system("cls");

                    if(h=='P') putarina(ime_cvora,&s);
                    else if (h=='S') statistika(&s);
                    else if (h!='X') printf("Pogresna komanda!\n");
                }
                while(h!='X');

            }

        }
        else  if (v!='X') printf("Pogresna komanda!\n");
    }
    while(v!='X');


    return 0;
}




