#pragma once
#include <iostream>
#include "ListaMiast.h"
#include "Miasto.h"
#include <cstring>
using namespace std;

ListaMiast::ListaMiast()
{
	pierwsze = nullptr;
	ostatnie = nullptr;
}

void ListaMiast::DodajMiasto(char* nazwa, int dl, int x, int y, int o, int hash)
{
	Miasto* nowe = new Miasto;
	nowe->nazwa = nazwa;
	nowe->dl_nazwy = dl;
	nowe->x = x;
	nowe->y = y;
	nowe->odleglosc = o;
	nowe->hash = hash;

	if (pierwsze == nullptr)
	{
		pierwsze = nowe;
		nowe->nastepne = nullptr;
		//nowe->poprzednie = nullptr;
		ostatnie = nowe;
	}
	else
	{
		if (pierwsze == ostatnie)
		{
			ostatnie = nowe;
			ostatnie->nastepne = nullptr;
			pierwsze->nastepne = ostatnie;
			//ostatnie->poprzednie = pierwsze;
		}
		else
		{
			ostatnie->nastepne = nowe;
			//nowe->poprzednie = ostatnie;
			ostatnie = nowe;
		}
	}
}

void ListaMiast::DodajSasiada(char* nazwa_miasta, char* nazwa_sasiada, int dl, int x, int y, int odleglosc, int hash)
{
	Miasto* tmp = pierwsze;
	while (tmp)
	{
		if (strcmp(tmp->nazwa, nazwa_miasta) == 0)
		{
			tmp->lista_sasiadow->DodajMiasto(nazwa_sasiada, dl, x, y, odleglosc, hash);
			delete tmp->lista_sasiadow->ostatnie->lista_sasiadow; // sasiad nie ma listy sasiadow
			break;
		}
		tmp = tmp->nastepne;
	}
}

void ListaMiast::DodajLot(char* nazwa_skad, char* nazwa_dokad, int dl_dokad, ListaMiast* hashtable, int rozmiarHT, int odleglosc_lotu, int hash_dokad)
{
	Miasto* tmp = pierwsze;
	while (tmp)
	{
		if (strcmp(tmp->nazwa, nazwa_skad) == 0)
		{
			//Miasto* tmp2 = tmp->lista_sasiadow->pierwsze;
			/*
			while (tmp2)
			{
				if (strcmp(tmp2->nazwa, nazwa_dokad) == 0)
				{
					if(tmp2->odleglosc > odleglosc_lotu)
					{
						tmp2->odleglosc = odleglosc_lotu; // jesli juz jest taki sasiad, to sprawdzam, czy odleglosc jest mniejsza od tej, ktora chcemy dodac 
					}
					return;
				}
				tmp2 = tmp2->nastepne;
			}
			*/
			//int hash = Hash2(nazwa_dokad, dl_dokad, rozmiarHT);
			Punkt p = hashtable[hash_dokad].XYMiastaONazwie(nazwa_dokad);
			tmp->lista_sasiadow->DodajMiasto(nazwa_dokad, dl_dokad, p.x, p.y, odleglosc_lotu, hash_dokad); // jesli nie ma zadnego sasiada, to dodajemy lot
			delete tmp->lista_sasiadow->ostatnie->lista_sasiadow;

			break;
		}
		tmp = tmp->nastepne;
	}
}

Punkt ListaMiast::XYMiastaONazwie(char* nazwa)
{
	Miasto* tmp = pierwsze;
	while (tmp)
	{
		if (strcmp(tmp->nazwa, nazwa) == 0)
		{
			Punkt p;
			p.x = tmp->x;
			p.y = tmp->y;
			return p;
		}
		tmp = tmp->nastepne;
	}
	Punkt p2;
	p2.x = -2;
	p2.y = -2;
	return p2;
}

void ListaMiast::WypiszListe()
{

	Miasto* tmp = pierwsze;
	while (tmp)
	{
		for (int i = 0; i < tmp->dl_nazwy; i++)
		{
			cout << tmp->nazwa[i];
		}
		cout << " ";
		cout << tmp->x << " " << tmp->y << " " << tmp->odleglosc << " HASH: " << tmp->hash <<endl;
		tmp = tmp->nastepne;
	}

}
/*
void ListaMiast::WypiszListeReverse()
{
	Miasto* tmp2 = pierwsze;
	while (tmp2->nastepne != nullptr)
	{
		tmp2 = tmp2->nastepne;
	}
	while (tmp2)
	{
		if(tmp2->nastepne != nullptr && tmp2->poprzednie != nullptr)
		{
			for (int i = 0; i < tmp2->dl_nazwy -1; i++)
			{
				cout << tmp2->nazwa[i];
			}
			if(tmp2->poprzednie->poprzednie != nullptr)
				cout << " ";
		}
		tmp2 = tmp2->poprzednie;
	}
}
*/

void ListaMiast::ZwolnijListe()
{
	Miasto* tmp = pierwsze;
	while (tmp)
	{
		Miasto* tmp2 = tmp;
		tmp = tmp->nastepne;
		delete tmp2->nazwa;
		delete tmp2;
	}
	pierwsze = nullptr;
	ostatnie = nullptr;
}