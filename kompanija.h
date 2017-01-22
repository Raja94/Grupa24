#ifndef KOMPANIJA_H_INCLUDED
#define KOMPANIJA_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct kompanija
{
    char naziv[31];
} KOMPANIJA;

void ucitaj_kompaniju(KOMPANIJA *k)
{
    printf("  Naziv: ");
    scanf("%s", k->naziv);
}

void upisivanjeKompanije()      //registrovanje kompanija u sistem
{
    KOMPANIJA k;
    FILE *dat;

    printf("Podaci o kompaniji:\n");
    ucitaj_kompaniju(&k);   //unos podataka
    system("cls");

    if ((dat = fopen("Kompanije.txt", "a"))!=NULL)
    {

        fseek(dat,0,SEEK_END);
        fprintf(dat, "%-30s\n", k.naziv);
    }
    fclose(dat);
}

int citanjeDatoteke_kompanija(KOMPANIJA *niz, char *ime_dat)  //citanje kompanija iz datoteke i smjestanje u niz
{                                                             //vraca broj registrovanih kompanija
    FILE *dat;
    int i=0;
    if((dat=fopen(ime_dat, "r"))!=NULL)
    {
        while(fscanf(dat, "%s", &niz[i].naziv)!=EOF) //citanje kompanija i brojanje
               i++;

        fclose(dat);
        return i;       //vraca broj kompanija
    }
    return 0;
}

int seq_search_kompanije(KOMPANIJA *niz,int n,char *kljuc)
{
    int i = 0;
    for (i = 0; i < n; i++)
        if (strcmp(niz[i].naziv, kljuc)==0 ) return i; //indeks trazene kompanije
    return -1;
}

void brisanje_kompanije()
{
    int n,i,c=100,j;
    KOMPANIJA *niz,k;
    niz = (KOMPANIJA *)malloc(c * sizeof(KOMPANIJA));
    n=citanjeDatoteke_kompanija(niz, "Kompanije.txt");  //citanje kompanija iz datoteke i smjestanje u niz

    printf("Unesite naziv kompanije za brisanje: ");
    scanf("%s", k.naziv);
    system("cls");

    printf("Rezultat pretrage:\n");
    i = seq_search_kompanije(niz, n, k.naziv);      //pretrazivanje niza
    if(i==-1) printf("Kompanija ne postoji!");
    else
    {


        printf("NAZIV                         \n");
        printf("==============================\n");
        printf("%-30s\n" ,niz[i].naziv);
        printf("==============================\n");
        printf("Kompanija obrisana!\n");

        FILE *dat;


        if ((dat = fopen("Kompanije.txt", "w"))!=NULL)
        {
            for(j=0; j<n; j++)
                if(j!=i) //i je indeks kompanije koja se brise
                    fprintf(dat, "%-30s\n" ,niz[j].naziv); //upisivanje ostalih kompanija u datoteku
            fclose(dat);


        }
        free(niz);
    }
}

void prikaz_kompanije()
{
    int n,i,c=100;
    KOMPANIJA *niz;

    niz = (KOMPANIJA *)malloc(c * sizeof(KOMPANIJA));
    n=citanjeDatoteke_kompanija(niz,"Kompanije.txt");
    printf("NAZIV                         \n");
    printf("==============================\n");
    for(i=0; i<n; i++)
        printf("%-30s\n" ,niz[i].naziv);
    printf("==============================\n");
    free(niz);
}

#endif // KOMPANIJA_H_INCLUDED
