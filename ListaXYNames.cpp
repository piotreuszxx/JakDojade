#pragma once
#include <iostream>
#include "PunktName.cpp"
using namespace std;

class ListaXYNames
{
public:
	PunktName* pierwszy;
	PunktName* ostatni;

	ListaXYNames()
	{
		pierwszy = nullptr;
		ostatni = nullptr;
	}

	void DodajPunktName(int x, int y, char* name, int dl_name)
	{
		PunktName* nowy = new PunktName;
		nowy->x = x;
		nowy->y = y;
		nowy->name = name;
		nowy->dl_name = dl_name;

		if (pierwszy == nullptr)
		{
			pierwszy = nowy;
			nowy->nastepny = nullptr;
			//nowy->poprzedni = nullptr;
			ostatni = nowy;
		}
		else
		{
			if (pierwszy == ostatni)
			{
				ostatni = nowy;
				ostatni->nastepny = nullptr;
				pierwszy->nastepny = ostatni;
				//ostatni->poprzedni = pierwszy;
			}
			else
			{
				ostatni->nastepny = nowy;
				//nowy->poprzedni = ostatni;
				ostatni = nowy;
			}

		}
	}

	char* FindNameForXY(int x, int y)
	{
		PunktName* temp = pierwszy;
		while(temp)
		{
			if(strcmp())
			temp = temp->nastepny;
		}
	}

	void WypiszListe()
	{

		PunktName* tmp = pierwszy;
		while (tmp)
		{
			cout << tmp->x << " " << tmp->y;
			cout << endl;
			tmp = tmp->nastepny;
		}
	}

	void ZwolnijListe()
	{
		PunktName* tmp = pierwszy;
		while (tmp)
		{
			PunktName* tmp2 = tmp;
			tmp = tmp->nastepny;
			delete tmp2->name;
			delete tmp2;
		}
		pierwszy = nullptr;
		ostatni = nullptr;
	}
};