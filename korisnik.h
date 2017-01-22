#ifndef KORISNIK_H_INCLUDED
#define KORISNIK_H_INCLUDED
#include <windows.h>
#include "dionica.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct statistika
{
 int stanjeA,stanjeB,stanjeC,stanjeD,suma;
 double racun;
}
 STATISTIKA;

typedef struct korisnik
{
    char ime[21], prezime[21], user[21], sifra[21];
    int status;
} KORISNIK;

int login();
int login_find(char *user, char *sifra);
void unos(KORISNIK *k);
void unos_izmjena(KORISNIK *k);
int dodavanje_radnika();
void ispis_u_fajl(KORISNIK *k, FILE *dat);
int find(char *user, int status);
void brisanje_radnika();
int citanjeDatoteke_user(KORISNIK *niz, char *ime_dat);
int seq_search_user(KORISNIK *niz,int n,char *kljuc);
void edit_radnika();
void prikaz_radnika();
void statistika(STATISTIKA *);
void putarina(char *,STATISTIKA *);

void statistika(STATISTIKA *s)  //funkcija za prikazivanje statistike, koliko je proslo vozila...
{
    FILE *dat;
    if((dat = fopen("Statistika.txt","w"))!=NULL)
    {
        fprintf(dat, "A: %d B: %d C: %d D: %d UKUPNO VOZILA: %d UKUPNO NOVCA: %7.2lf\n ",s->stanjeA,s->stanjeB,s->stanjeC,s->stanjeD,s->suma,s->racun);
        fprintf(dat, "------------------------------------");
        printf("Stanje:\n\tA: %d\n\tB: %d\n\tC: %d\n\tD: %d\n\tUKUPNO VOZILA: %d\n\tUKUPNO NOVCA:%7.2lf\n\t",s->stanjeA,s->stanjeB,s->stanjeC,s->stanjeD,s->suma,s->racun);
        fclose(dat);
    }


}

int login() //funkcija za logovanje u sistem
{
    char ID[21], sifra[21];
    int greska = 0;
    int status = 0;
    do
    {
        system("cls");
        if(greska == 0)  //prilikom prvog logovanja
        {
            printf("Korisnicko ime: ");
            scanf("%s", ID);
            printf("Sifra: ");
            scanf("%s", sifra);
            greska++;
        }
        else            //ukoliko korisnik unese pogresnu sifru ili username ispisuje se greska
        {
            printf("Pogresna sifra ili korisnicko ime!\n");
            printf("Korisnicko ime: ");
            scanf("%s", ID);
            printf("Sifra: ");
            scanf("%s", sifra);
        }
    }
    while ((status=login_find(ID,sifra))==0);   //provjera da li username postoji u bazi registrovanih korisnika
    return status;      //vraca status logovanog korisnika, Admin[1], Operater[2]
}

int login_find(char *user, char *sifra)     //trazi u bazi registrovanih korisnika username i sifru koju
{                                           //korisnik unosi prilikom logovanja na sistem
    FILE *dat;
    if((dat = fopen("Administratori.txt", "r"))!=NULL)
    {
        char pom[21], pom1[21];
        int status;
        while(fscanf(dat,"%s %s %d", pom, pom1, &status)!=EOF)  //cita postojece korisnike iz datoteke
        {
            if(strcmp(user,pom)==0 && strcmp(sifra,pom1)==0)    //poredi unesenu sifru i username sa postojecim
            {
                fclose(dat);
                return status; //vraca status korisnika(Admin[1], Operater[2]
            }
            char pom2[21];
            fscanf(dat,"%s", pom2);         //preskakanje imena
            fscanf(dat,"%s", pom2);         //preskakanje prezimena
        }
        fclose(dat);
    }
    if((dat = fopen("Operateri.txt", "r"))!=NULL)
    {
        char pom[21], pom1[21];
        int status;
        while(fscanf(dat,"%s %s %d", pom, pom1, &status)!=EOF)    //cita postojece korisnike iz datoteke
        {
            if(strcmp(user,pom)==0 && strcmp(sifra,pom1)==0)     //poredi unesenu sifru i username sa postojecim
            {
                fclose(dat);
                return status; //vraca status korisnika(Admin[1], Operater[2]
            }
            char pom2[21];
            fscanf(dat,"%s", pom2);
            fscanf(dat,"%s", pom2);
        }
        fclose(dat);
    }
    return 0;   //ukoliko nije pronasao poklapanje unesenog username i sifre vraca 0
}

void unos(KORISNIK *k)   //funkcija za unos podataka o korisniku
{
    printf("Ime: ");
    scanf("%s", k->ime);
    printf("Prezime: ");
    scanf("%s", k->prezime);
    printf("Korisnicko ime: ");
    scanf("%s", k->user);
    do
    {
        printf("Sifra: ");
        scanf("%s", k->sifra);
    }
    while (strlen(k->sifra)<8 || strlen(k->sifra)>20);  //sifra mora biti duza od 8 karaktera i kraca od 20
    int pom;
    do
    {
        printf("Status: Admin[1] Operater[2]: "); //izbor statusa korisnika pri registraciji
        scanf("%d", &pom);
    }
    while(pom < 1 || pom > 2);
    k->status = pom;
}


int dodavanje_radnika()    //registrovanje radnika
{
    FILE *dat;
    KORISNIK k;
    do
    {
        unos(&k);       //unos podataka o korisniku
    }
    while (find(k.user,k.status)!=0);   //provjera da li uneseni username vec postoji u bazi korisnika

    if(k.status == 1)      //ukoliko je korisnik Admin
    {
        if((dat=fopen("Administratori.txt", "a"))!=NULL)
        {
            ispis_u_fajl(&k,dat);       //upis korisnika u bazu podataka za Admine
            fclose(dat);
        }
    }
    else
    {
        if((dat=fopen("Operateri.txt", "a"))!=NULL)     //ukoliko je korisnik operater
        {
            ispis_u_fajl(&k,dat);       //upis korisnika u bazu podataka za operatere
            fclose(dat);
        }
    }
    return 0;
}

void ispis_u_fajl(KORISNIK *k, FILE *dat)   //upisivanje korisnika u datoteku
{
    fprintf(dat, "%-20s %-20s %d %-20s %-20s\n", k->user, k->sifra, k->status, k->ime, k->prezime);
}

int find(char *user, int status)  //pronalazi korisnika i vraca njegovu poziciju u datoteci
{
    FILE *dat;
    int broj_reda=0;
    if(status == 1)     //ukoliko je korisnik admin pretrazuje se datoteka Administratori.txt
    {
        if((dat = fopen("Administratori.txt", "r"))!=NULL)
        {
            char pom[21];
            while(fscanf(dat,"%s", pom)!=EOF)  //citanje username iz datoteke
            {
                broj_reda++;
                if(strcmp(user,pom)==0)         //ukoliko je to trazeni username
                {
                    fclose(dat);
                    return broj_reda;           //vraca broj reda usera
                }
                char pom2[21];
                fscanf(dat,"%s", pom2);        //preskakanje sifre
                fscanf(dat,"%s", pom2);        //preskakanje statusa
                fscanf(dat,"%s", pom2);        //preskakanje imena
                fscanf(dat,"%s", pom2);        //preskakanje prezimena
            }
            fclose(dat);
            return 0;
        }
        else
            return 0;       //vraca 0 ukoliko nije pronasao usera
    }
    else if(status == 2)        //ukoliko je korisnik operater pretrazuje se datoteka Operateri.txt
    {
        if((dat = fopen("Operateri.txt", "r"))!=NULL)
        {
            char pom[21];
            while(fscanf(dat,"%s", pom)!=EOF)      //citanje username iz datoteke
            {
                broj_reda++;
                if(strcmp(user,pom)==0)             //ukoliko je to trazeni username
                {
                    fclose(dat);
                    return broj_reda;               //vraca broja reda usera
                }
                char pom2[21];
                fscanf(dat,"%s", pom2);            //preskakanje sifre
                fscanf(dat,"%s", pom2);            //preskakanje statusa
                fscanf(dat,"%s", pom2);            //preskakanje imena
                fscanf(dat,"%s", pom2);            //preskakanje prezimena
            }
            fclose(dat);
            return 0;
        }
        else
            return 0;       //vraca 0 ukoliko nije pronasao usera
    }
    return 0;
}

void brisanje_radnika()            //brisanje usera iz baze
{
    char ime_dat[21];
    int pom;
    do
    {
        printf("Koga brisete: Admin[1], Operater[2]: ");
        scanf("%d", &pom);
    }
    while(pom < 1 || pom > 3);
    if(pom==1)      //brisanje admina - kopiranje imena datoteke u ime_dat
        strcpy(ime_dat,"Administratori.txt");
    else if(pom==2) //brisanje operatera - kopiranje imena datoteke u ime_dat
        strcpy(ime_dat,"Operateri.txt");
    int n,i,c=100,j;
    KORISNIK *niz,k;
    niz = (KORISNIK *)malloc(c * sizeof(KORISNIK));
    n=citanjeDatoteke_user(niz,ime_dat);    //ucitavanje korisnika iz odgovarajuce datoteke i brojanje korisnika

    printf("Unesite username korisnika koga brisete: ");
    scanf("%s", k.user);
    printf("Rezultat pretrage:\n");
    i =  seq_search_user(niz, n, k.user);    //pretraga korisnika i trazenje njegovog indeksa u nizu korisnika
    if(i==-1) printf("Korisnik ne postoji!");
    else                                     //korisnik pronadjen
    {


        printf("USER                 IME                  PREZIME              STATUS\n");
        printf("=====================================================================\n");
        printf("%-20s %-20s %-20s %-7s\n" ,niz[i].user, niz[i].ime, niz[i].prezime,
               ((niz[i].status == 1) ? "Admin" : "Operater"));
        printf("=====================================================================\n");
        printf("Korisnik obrisan!\n");


        FILE *dat;

        if((dat=fopen(ime_dat, "w"))!=NULL)
        {
            for(j=0; j<n; j++)
                if(i!=j)            //i je indeks korisnika za brisanje
                {
                    ispis_u_fajl(niz+j,dat);    //upis svih korisnika sem korisnika sa indeksom i
                }
            fclose(dat);
        }
        free(niz);      //brisanje niza

    }
}

int citanjeDatoteke_user(KORISNIK *niz, char *ime_dat)    //citanje korisnika iz datoteke i vracanje broja korisnika
{
    FILE *dat;
    int i=0;
    if((dat=fopen(ime_dat, "r"))!=NULL)
    {
        while(fscanf(dat, "%s %s %d %s %s", niz[i].user, niz[i].sifra, &niz[i].status, niz[i].ime, niz[i].prezime)!=EOF)
            i++;

        fclose(dat);
        return i;  //vracanje broja korisnika
    }
    return 0;
}

int seq_search_user(KORISNIK *niz,int n,char *kljuc)   //pretrazivanje korisnika iz niza
{
    int i = 0;
    for (i = 0; i < n; i++)
        if (strcmp(niz[i].user, kljuc)==0) return i;    //vracanje indeksa pronadjenog korisnika
    return -1;          //nije pronadjen trazeni korisnik
}

void edit_radnika()          //izmjena korisnika
{
    char ime_dat[21];
    int pom;
    do
    {
        printf("Koga editujete: Admin[1], Operater[2]: ");
        scanf("%d", &pom);
    }
    while(pom < 1 || pom > 3);
    if(pom==1)          //izmjena podataka admina, ime_dat=Administratori.txt
        strcpy(ime_dat,"Administratori.txt");
    else if(pom==2)     //izmjena podataka operatera, ime_dat=Operateri.txt
        strcpy(ime_dat,"Operateri.txt");
    int n,i,c=100,j;
    KORISNIK *niz,k;
    niz = (KORISNIK *)malloc(c * sizeof(KORISNIK));
    n=citanjeDatoteke_user(niz,ime_dat);    //ocitavanje korisnika i smjestanje u niz

    printf("Unesite username korisnika koga mijenjate: ");
    scanf("%s", k.user);        //username korisnika kojeg mijenjamo
    printf("Rezultat pretrage:\n");
    i = seq_search_user(niz, n, k.user); //pretraga korisnika i vracanje njegovog indeksa u nizu
    if(i==-1) printf("Korisnik ne postoji!");
    else                //korisnik pronadjen
    {


        printf("USER                 IME                  PREZIME              STATUS\n");  //ispis podataka korisnika
        printf("=====================================================================\n");
        printf("%-20s %-20s %-20s %-7s\n" ,niz[i].user, niz[i].ime, niz[i].prezime,
               ((niz[i].status == 1) ? "Admin" : "Operater"));
        printf("=====================================================================\n");


        FILE *dat,*dat2;

        if((dat=fopen(ime_dat, "w"))!=NULL)
        {
            for(j=0; j<n; j++){
                if(i!=j)      //i je indeks korisnika za editovanje
                {
                    ispis_u_fajl(niz+j,dat);    //upis korisnika koji se ne mijenjaju
                }
                else
                {
                    unos(niz+i);        //ucitavanje izmjena pronadjenog korisnika
                    if(niz[i].status==1)
                    {
                        if(strcmp("Administratori.txt", ime_dat)==0)
                            ispis_u_fajl(niz+i,dat);
                        else if((dat2=fopen("Administratori.txt", "a"))!=NULL)
                        {
                            ispis_u_fajl(niz+i,dat2);    //upisivanje izmjenjenih podataka o korisniku u datoteku
                            fclose(dat2);
                        }

                    }
                    else if(niz[i].status==2)
                    {
                        if(strcmp("Operateri.txt", ime_dat)==0)
                            ispis_u_fajl(niz+i,dat);
                        else if((dat2=fopen("Operateri.txt", "a"))!=NULL)
                        {
                            ispis_u_fajl(niz+i,dat2);    //upisivanje izmjenjenih podataka o korisniku u datoteku
                            fclose(dat2);
                        }

                    }
                }
            }
            fclose(dat);
            free(niz);
        }

    }
}

void prikaz_radnika()
{
    int n,i,c=100;
    KORISNIK *niz;
    char ime_dat[20];

    strcpy(ime_dat,"Administratori.txt");
    niz = (KORISNIK *)malloc(c * sizeof(KORISNIK));
    n=citanjeDatoteke_user(niz,ime_dat);
    printf("Administratori:\n");
    printf("USER                 IME                  PREZIME              STATUS\n");
    printf("=====================================================================\n");
    for(i=0; i<n; i++)
        printf("%-20s %-20s %-20s %-7s\n" ,niz[i].user, niz[i].ime, niz[i].prezime,
               ((niz[i].status == 1) ? "Admin" : "Operater"));
    printf("=====================================================================\n\n");
    free(niz);

    strcpy(ime_dat,"Operateri.txt");
    niz = (KORISNIK *)malloc(c * sizeof(KORISNIK));
    n=citanjeDatoteke_user(niz,ime_dat);
    printf("Operateri:\n");
    printf("USER                 IME                  PREZIME              STATUS\n");
    printf("=====================================================================\n");
    for(i=0; i<n; i++)
        printf("%-20s %-20s %-20s %-7s\n" ,niz[i].user, niz[i].ime, niz[i].prezime,
               ((niz[i].status == 1) ? "Admin" : "Operater"));
    printf("=====================================================================\n\n");
    free(niz);

}

void izdavanje_racuna(int broj_racuna, char ime_ucvora[21], char* ime_icvora, char kategorija, double racun, char ime_dat[21])
{
	FILE *dat;
	if ((dat = fopen(ime_dat, "w"))!=NULL)
	{
		fseek(dat, 0, SEEK_END);
		fprintf(dat, "Br. Racuna   Ulaz    Izlaz   Kategorija    Cijena\n");
		fprintf(dat, "%04d         %-5s   %-5s   %c             %4.2lf\n", broj_racuna, ime_ucvora, ime_icvora, kategorija, racun);
	}
	fclose(dat);
	printf("Br. Racuna   Ulaz    Izlaz   Kategorija    Cijena\n");
	printf("%04d         %-5s   %-5s   %c             %4.2lf\n", broj_racuna, ime_ucvora, ime_icvora, kategorija, racun);
}

void putarina(char* ime_icvora, STATISTIKA *s)
{
    static int broj_racuna;
    int n,i,c=100, sati,minuta;
    double racun=0;
    SYSTEMTIME str_t;
    GetSystemTime(&str_t);    //vrijeme izdavanja racuna
    char ulaz[21], kategorija;
    printf("Ulazni cvor: ");
    scanf("%s", ulaz);
    printf("Kategorija: Auto[a], Kombi[b], Autobus[c], Kamion[d]: "); //kategorija vozila
    scanf("\n%c", &kategorija);
    printf("Vrijeme ulaska na autoput: \n");
    printf("Sati: ");
    scanf("%d", &sati);
    printf("Minuta: ");
    scanf("%d", &minuta);
    system("cls");

    DIONICA *niz;
    niz=(DIONICA *)malloc(c*sizeof(DIONICA));
    n=citanjeDatoteke_dionica(niz,"Dionice.txt");   //citanje dionica iz datoteke i upisivanje u niz
    i = seq_search_dionice(niz, n, ulaz, ime_icvora); //pretrazivanje

    if(i==-1)       //ukoliko je unesena pogresna dionica autoputa
        printf("Dionica ne postoji!\n");
    else
    {
        if(((str_t.wHour+1-sati)<niz[i].sat) || (((str_t.wHour+1-sati)==niz[i].sat) && ((str_t.wMinute-minuta)<niz[i].minut)))
        {               //ukoliko je doslo do prekoracenja brzine i vozac je stigao za manje vrijeme od dozvoljenog
            racun=100;  //dobija kaznu
            printf("Prekoracenje brzine, kazna 100KM\n\n");
        }
        if(kategorija=='a')
          { racun+=niz[i].duzina*0.2; s->stanjeA++; s->suma++; s->racun+=racun;}
        else if(kategorija=='b')
          { racun+=niz[i].duzina*0.3; s->stanjeB++; s->suma++; s->racun+=racun;}
        else if(kategorija=='c')
          { racun+=niz[i].duzina*0.4; s->stanjeC++; s->suma++; s->racun+=racun;}
        else if(kategorija=='d')
          { racun+=niz[i].duzina*0.5; s->stanjeD++; s->suma++; s->racun+=racun;}
        broj_racuna++;

        char ime_dat[21];
        char broj[15];
        sprintf(broj, "%d", broj_racuna);
        strcpy(ime_dat,broj);   //svaki racun se smjesta u novu datoteku
        strcat(ime_dat, ".txt");//svaka datoteka se zove broj_racuna.txt
        izdavanje_racuna(broj_racuna, ulaz, ime_icvora, kategorija, racun, ime_dat);
    }
}


#endif // KORISNIK_H_INCLUDED
