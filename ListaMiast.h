#pragma once
#include <iostream>
#include "Punkt.cpp"
using namespace std;

class Miasto;

class ListaMiast
{
public:
	Miasto* pierwsze;
	Miasto* ostatnie;

	ListaMiast();

	void DodajMiasto(char* nazwa, int dl, int x, int y, int odleglosc, int hash);
	void DodajSasiada(char* nazwa_miasta, char* nazwa_sasiada, int dl, int x, int y, int odleglosc, int hash);

	void DodajLot(char* nazwa_skad, char* nazwa_dokad, int dl_dokad, ListaMiast* hashtable, int rozmiarHT, int odleglosc_lotu, int hash);

	Punkt XYMiastaONazwie(char* nazwa_miasta);
	void WypiszListe();
	void WypiszListeReverse();

	void UsunMiasto(int a);

	void ZwolnijListe();
};