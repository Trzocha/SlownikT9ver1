#include <iostream>
#include "funkcje.h"

using namespace std;

int main()
{
    slownik();
	return 0;
}

void slownik()
{
int ilosc_wprowadzen = 0;
int ilosc_szukan = 0;
Litera *tab_pocz[8];

	for(int i=0;i<8;i++) tab_pocz[i]=NULL;

	cin>>ilosc_wprowadzen;

	for(int j=0;j<ilosc_wprowadzen;j++)
		wprowadz_slowa(tab_pocz);

	cin>>ilosc_szukan;
	for(int i=0;i<ilosc_szukan;i++)
		szukaj_wg_klucza(tab_pocz);
}
