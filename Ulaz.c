#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>

void izdavanje_potvrde(int,char*,char*);
void main()
{
    printf("DOBRODOSLI!\n\n");
    char ime_cvora[10];
    printf("Naziv ulaznog cvora: ");
    gets(ime_cvora);
    char taster;
    char temp[10];
    FILE *dat;
    strcpy(temp,ime_cvora); strcat(temp,".txt");
    if (dat = fopen(temp, "a"))
    {
        SYSTEMTIME str_t;
        GetSystemTime(&str_t);
        fseek(dat,0,SEEK_END);
        fprintf(dat, "-----%02d/%02d/%4d %02d:%02d:%02d-----\n", str_t.wDay, str_t.wMonth,str_t.wYear,
                                                        str_t.wHour+1, str_t.wMinute, str_t.wSecond);
    }
    fclose(dat);
    int broj_potvrde=0;
    do
    {
        system("cls");
        printf("T-Izdavanje potvrde ");
        scanf("\n%c", &taster);
        if(taster=='T')izdavanje_potvrde(++broj_potvrde,ime_cvora,temp);
    }
    while(taster);
    return 0;
}

void izdavanje_potvrde(int broj_potvrde, char* ime_cvora, char* ime_dat)
{
    FILE *dat;
    if (dat = fopen(ime_dat, "a"))
    {
        SYSTEMTIME str_t;
        GetSystemTime(&str_t);
        fseek(dat,0,SEEK_END);
        fprintf(dat, "%-4s %04d %02d/%02d/%4d %02d:%02d:%02d\n", ime_cvora,broj_potvrde,str_t.wDay, str_t.wMonth,str_t.wYear,
                str_t.wHour+1, str_t.wMinute, str_t.wSecond);
    }
    fclose(dat);
}
