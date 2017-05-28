#include <iostream>
#include "funkcje.h"

using namespace std;

struct Litera
{
char slowo_klucz[100];
Litera *next;
int liczba;
Litera *wsk_ciala[8];
Litera(){next = NULL; for(int i=0;i<8;i++) wsk_ciala[i] = NULL; liczba = 0; slowo_klucz[0]='\0';}
};

//-----------------------------------------------------------------------------------
void wczytaj_buffor(char buff[])
{
	scanf("%s",buff);
}
int dl_buff(char buff[])
{
int licznik=0;
	while(buff[licznik] >=97 && buff[licznik] <=122)
		licznik++;
return licznik;
}
int ktory_nr(char buff[],int i)
{
	if(buff[i]>=97 && buff[i]<=99){return 0;}                          //2 abc
	else if (buff[i]>=100 && buff[i]<=102){return 1;}                  //3 def
	else if (buff[i]>=103 && buff[i]<=105){return 2;}                  //4 ghi
	else if (buff[i]>=106 && buff[i]<=108){return 3;}                  //5 jkl
	else if (buff[i]>=109 && buff[i]<=111){return 4;}                  //6 mno
	else if (buff[i]>=112 && buff[i]<=115){return 5;}                  //7 pqrs
	else if (buff[i]>=116 && buff[i]<=118){return 6;}                  //8 tuv
	else if (buff[i]>=119 && buff[i]<=122){return 7;}                  //9 wxyz

return 0;
}

void poczatek_slowa(Litera *&PListy,int cyfra)
{
	if(PListy == NULL)
	{
		Litera *nowy = new Litera;

			nowy->liczba = cyfra+2;
			PListy = nowy;
	}
}

void cialo_slowa(Litera *&KListy,int cyfra)        //dodawanie za wskaznik chodzacy
{
	if(KListy->wsk_ciala[cyfra] == NULL)
	{
		Litera *nowy = new Litera;

			nowy->liczba = cyfra+2;
			KListy->wsk_ciala[cyfra] = nowy;
			KListy = nowy;
	}else if (KListy != NULL)
		KListy = KListy->wsk_ciala[cyfra];

}

void wstaw_slowo_klucz(Litera *&klucz,char buff[],int dl)
{
Litera *nowy = new Litera;
Litera *wsk_za_kluczem = NULL;

	if(klucz->next == NULL)                             //jak jest wiecej slow o takim samym kodzie tworze LISTE
		klucz->next = nowy;
	else if(klucz->next != NULL)                        //na poczatek , w srodek czy na koniec
		wstaw_leksyko(klucz,nowy,wsk_za_kluczem,buff,dl);

	for(int i=0;i<dl+1;i++)
			nowy->slowo_klucz[i] = buff[i];
}

void wypisz_slowa(Litera *&slowa)
{
Litera *pom = NULL;
	pom = slowa;
	while(pom != NULL)
	{
	cout<<pom->slowo_klucz<<" ";
	pom = pom->next;
	}
}

void wczytaj_kod(char kod[])
{
	scanf("%s",kod);
}

int dl_kodu(char kod[])
{
int licznik=0;
	while(kod[licznik] >= 48 && kod[licznik] <=57)
		licznik++;
return licznik;
}

bool przeszukaj_drzewo(Litera *elementy[],char kod[],int dl_kodu)
{
int ktory_el;
int licznik = 0;
Litera *ide = NULL;
bool odp=0;

	ktory_el = kod[licznik]-50;         //zamiana z char na int -2(50) wg oznaczenia tablicowego
	ide = elementy[ktory_el];
	licznik+=1;

	odp = po_galezi(ide,kod,dl_kodu,licznik);

return odp;
}
bool po_galezi(Litera *&galazka,char kod[],int dl_kodu,int &licznik)
{
int ktory_el=0;
Litera *ide;
bool odp = 0;

	if(dl_kodu>licznik)
	{
		ktory_el = kod[licznik]-50;
		ide = galazka->wsk_ciala[ktory_el];
		if(ide !=NULL)
		{
			licznik+=1;
			odp = po_galezi(ide,kod,dl_kodu,licznik);
		}
	}else     //dl_kodu == licznik
		odp = szukajDalej_poGalezi(galazka);

return odp;
}

void wprowadz_slowa(Litera *tab_pocz[])
{
Litera *koniec = NULL;
char buffor[100]={' '};
int dl_buffora=0;
int cyfra=0;

	 wczytaj_buffor(buffor);
	 dl_buffora = dl_buff(buffor);

	 cyfra = ktory_nr(buffor,0);               //cyfra mowi od ktorego wskaznka zaczynam
	 poczatek_slowa(tab_pocz[cyfra],cyfra);
	 koniec = tab_pocz[cyfra];

	 for(int i=1;i<dl_buffora;i++)             //budowanie ciala slowa
	 {
	 cyfra = ktory_nr(buffor,i);
	 cialo_slowa(koniec,cyfra);
	 }

	 wstaw_slowo_klucz(koniec,buffor,dl_buffora);
}

void szukaj_wg_klucza(Litera *tab_pocz[])
{
int dlugosc_kodu=0;
char kod[100]={' '};
bool odp = 0;

		wczytaj_kod(kod);
		dlugosc_kodu = dl_kodu(kod);
		odp = przeszukaj_drzewo(tab_pocz,kod,dlugosc_kodu);

		if(odp == false) cout<<"-\n";
}
bool szukajDalej_poGalezi(Litera *&ide)
{
Litera *pom = NULL;
bool odp = 0;
bool p =0;

	if(ide->next != NULL)
	{
		 wypisz_slowa(ide->next);
		 p=1;
	}

	for(int i=0;i<8;i++)
	{
		if(ide->wsk_ciala[i] != NULL)
		{
			pom = ide->wsk_ciala[i];
			odp = szukajDalej_poGalezi(pom);
		}
	}
return (odp || p);
}
void wstaw_leksyko(Litera *&klucz,Litera *&nowy,Litera *&wsk_za_kluczem,char buff[],int dl)
{
int wynik=0;

	if(klucz!=NULL)
		wynik = porownaj(klucz,buff,dl);
	else wynik = 0;

	switch(wynik)						//w zaleznosci jaki ciag i gdzie wstawiony bedzie
	{
	case 0: 							//na poczatek
		if(wsk_za_kluczem == NULL)
			dodaj_na_pocz(klucz,nowy);
		else if(klucz == NULL)
			dodaj_na_koniec(wsk_za_kluczem,nowy);
		else
			dodaj_przed_elK(klucz,wsk_za_kluczem,nowy);
		break;
	case 1:								//idz dalej w liscie
		wsk_za_kluczem = klucz;
		klucz = klucz->next;
		wstaw_leksyko(klucz,nowy,wsk_za_kluczem,buff,dl);
		break;
	};
}
int porownaj(Litera *&klucz,char buff[],int dl)
{
	for(int i=0;i<dl;i++)
	{
		if(klucz->slowo_klucz[i] < buff[i])
			return 1;
		else if(klucz->slowo_klucz[i] > buff[i])
			return 0;
	}
return 0;
}

void dodaj_na_pocz(Litera *&klucz,Litera *&nowy)
{
Litera *pom=NULL;

		pom = klucz->next;
		klucz->next = nowy;
		nowy->next = pom;
}
void dodaj_przed_elK(Litera *&klucz,Litera *&wsk_za_kluczem,Litera *&nowy)
{
	wsk_za_kluczem->next = nowy;
	nowy->next = klucz;
}
void dodaj_na_koniec(Litera *&wsk_za_kluczem,Litera *&nowy)
{
	wsk_za_kluczem->next = nowy;
}
