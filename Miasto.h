#pragma once
#include "ListaMiast.h"
#define inf 999999999
class Miasto
{
public:
	int x = -5, y = -5;
	char* nazwa;
	int dl_nazwy = -6; // razem z '\0'
	int odleglosc = 0;
	int hash = -3;

	Miasto* poprzednie;
	Miasto* nastepne;
	ListaMiast* lista_sasiadow;
	Miasto();
	void WypiszSasiadow();
};