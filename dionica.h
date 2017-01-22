#ifndef DIONICA_H_INCLUDED
#define DIONICA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

typedef struct dionica
{
    char ulaz[21], izlaz[21];
    double duzina;
    int sat,minut;
} DIONICA;

void ucitaj_dionicu(DIONICA *d)
{
    printf("  Ulaz: ");
    scanf("%s", d->ulaz);
    printf("  Izlaz: ");
    scanf("%s", d->izlaz);
    printf("  Duzina: ");
    scanf("%lf", &d->duzina);
    printf("  Minimalno vrijeme prolaska: \n");
    printf("  Sati: ");
    scanf("%d", &d->sat);
    printf("  Minuta: ");
    scanf("%d", &d->minut);
}

void upisivanjeDionice()        //unosenje dionica u sistem
{
    DIONICA d;
    FILE *dat;

    printf("Podaci o dionici:\n");
    ucitaj_dionicu(&d);         //unosenje podataka o dionica
    system("cls");

    if ((dat = fopen("Dionice.txt", "a"))!=NULL)
    {

        fseek(dat,0,SEEK_END);
        fprintf(dat, "%-7s %-7s %-3.2lf    %3d:%02d\n", d.ulaz, d.izlaz, d.duzina, d.sat, d.minut);
    }
    fclose(dat);
}

int citanjeDatoteke_dionica(DIONICA *niz, char *ime_dat)    //citanje dionica iz datoteke i smjestanje u niz
{
    FILE *dat;
    int i=0;
    if((dat=fopen(ime_dat, "r"))!=NULL)
    {
        while(fscanf(dat, "%s %s %lf %d:%d", niz[i].ulaz, niz[i].izlaz, &niz[i].duzina, &niz[i].sat, &niz[i].minut)!=EOF)
            i++;

        fclose(dat);
        return i;       //vraca broj dionica
    }
    return 0;
}

int seq_search_dionice(DIONICA *niz,int n,char *kljuc1, char *kljuc2)   //pretrazivanje dionica u nizu
{
    int i = 0;
    for (i = 0; i < n; i++)
        if ((strcmp(niz[i].ulaz, kljuc1)==0) && (strcmp(niz[i].izlaz, kljuc2)==0)) return i; //indeks trazene dionice
    return -1;  //nije pronadjena dionica
}



void izmjena_dionice()
{
    int n,i,c=100,j;
    DIONICA *niz,d;
    niz = (DIONICA *)malloc(c * sizeof(DIONICA));
    n=citanjeDatoteke_dionica(niz,"Dionice.txt"); //citanje dionica iz datoteke i smjestanje u niz

    printf("Unesite ulaz dionice za izmjenu: ");
    scanf("%s", d.ulaz);
    printf("Unesite izlaz dionice za izmjenu: ");
    scanf("%s", d.izlaz);
    system("cls");
    printf("Rezultat pretrage:\n");
    i = seq_search_dionice(niz, n, d.ulaz, d.izlaz);    //pretrazivanje niza dionica i-indeks trazene dionice
    if(i==-1) printf("Dionica ne postoji!");
    else
    {


        printf("ULAZ    IZLAZ   DUZINA   VRIJEME\n");
        printf("================================\n");
        printf("%-7s %-7s %-3.2lf    %3d:%02d\n" ,niz[i].ulaz, niz[i].izlaz, niz[i].duzina, niz[i].sat, niz[i].minut);
        printf("================================\n");


        FILE *dat;

        if((dat=fopen("Dionice.txt", "w"))!=NULL)
        {
            for(j=0; j<n; j++)
                if(i!=j)//i je indeks dionice za editovanje
                {
                    fprintf(dat, "%-7s %-7s %-3.2lf    %3d:%02d\n" ,niz[j].ulaz, niz[j].izlaz, niz[j].duzina, niz[j].sat, niz[j].minut);    //upis dionica koje se ne mijenjaju
                }
                else
                {
                    ucitaj_dionicu(niz+j); //unosenje izmjena na dionici
                    fprintf(dat, "%-7s %-7s %-3.2lf    %3d:%02d\n" ,niz[j].ulaz, niz[j].izlaz, niz[j].duzina, niz[j].sat, niz[j].minut);
                }
            fclose(dat);
            free(niz);
        }
        system("cls");

    }
}

void brisanje_dionice()
{
    int n,i,c=100,k;
    DIONICA *niz,d;
    niz = (DIONICA *)malloc(c * sizeof(DIONICA));
    n=citanjeDatoteke_dionica(niz, "Dionice.txt");  //citanje dionica iz datoteke i smjestanje u niz

    printf("Unesite ulaz dionice za brisanje: ");
    scanf("%s", d.ulaz);
    printf("Unesite izlaz dionice za brisanje: ");
    scanf("%s", d.izlaz);
    system("cls");
    printf("Rezultat pretrage:\n");
    i = seq_search_dionice(niz, n, d.ulaz, d.izlaz);    //pretrazivanje niza dionica
    if(i==-1) printf("Dionica ne postoji!");
    else
    {


        printf("ULAZ    IZLAZ   DUZINA   VRIJEME\n");
        printf("================================\n");
        printf("%-7s %-7s %-3.2lf    %3d:%02d\n" ,niz[i].ulaz, niz[i].izlaz, niz[i].duzina, niz[i].sat, niz[i].minut);
        printf("================================\n");
        printf("Dionica obrisana!\n");

        FILE *dat;


        if ((dat = fopen("Dionice.txt", "w"))!=NULL)
        {
            for(k=0; k<n; k++)
                if(i!=k)        //i je indeks dionice koja se brise, ostale se upisuju u datoteku
                    fprintf(dat, "%-7s %-7s %-3.2lf    %3d:%02d\n" ,niz[k].ulaz, niz[k].izlaz, niz[k].duzina, niz[k].sat, niz[k].minut);
            fclose(dat);


        }
        free(niz);
    }
}


void prikaz_dionica()
{
    int n,i,c=100;
    DIONICA *niz;

    niz = (DIONICA *)malloc(c * sizeof(DIONICA));
    n=citanjeDatoteke_dionica(niz,"Dionice.txt"); //citanje dionica iz datoteke
    printf("ULAZ    IZLAZ   DUZINA   VRIJEME\n");
    printf("================================\n");
    for(i=0; i<n; i++)          //prikaz dionica
        printf("%-7s %-7s %-3.2lf    %3d:%02d\n" ,niz[i].ulaz, niz[i].izlaz, niz[i].duzina, niz[i].sat, niz[i].minut);
    printf("================================\n");
    free(niz);
}

#endif // DIONICA_H_INCLUDED
