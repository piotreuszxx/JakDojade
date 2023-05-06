#pragma once
#include <iostream>
#include "Punkt.cpp"
using namespace std;

class ListaXY
{
public:
	Punkt* pierwszy;
	Punkt* ostatni;

	ListaXY()
	{
		pierwszy = nullptr;
		ostatni = nullptr;
	}

	void DodajPunkt(int x, int y)
	{
		Punkt* nowy = new Punkt;
		nowy->x = x;
		nowy->y = y;

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

	void WypiszListe()
	{

		Punkt* tmp = pierwszy;
		while (tmp)
		{
			cout<< tmp->x << " " << tmp->y;
			cout << endl;
			tmp = tmp->nastepny;
		}
	}

	void ZwolnijListe()
	{
		Punkt* tmp = pierwszy;
		while (tmp)
		{
			Punkt* tmp2 = tmp;
			tmp = tmp->nastepny;
			delete tmp2;
		}
		pierwszy = nullptr;
		ostatni = nullptr;
	}
};   