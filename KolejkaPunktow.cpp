#pragma once
#include <iostream>
#include "Punkt.cpp"
using namespace std;

class KolejkaPunktow
{
public:
	Punkt* pierwszy;
	Punkt* ostatni;
	int ile;

	KolejkaPunktow()
	{
		pierwszy = nullptr;
		ostatni = nullptr;
		ile = 0;
	}

	int Ilosc()
	{
		return ile;
	}

	void Push(int x, int y, int o)
	{
		Punkt* nowe = new Punkt;
		nowe->x = x;
		nowe->y = y;
		nowe->odleglosc = o;

		if (pierwszy == nullptr)
			pierwszy = nowe;
		else
		{
			Punkt* temp = ostatni;
			temp->nastepny = nowe;
		}
		ostatni = nowe;
		ile++;
	}

	void Pop()
	{
		if (pierwszy == nullptr)
			return;
		else
		{
			Punkt* temp = pierwszy;
			int x = temp->x;
			int y = temp->y;
			int o = temp->odleglosc;
			pierwszy = temp->nastepny;
			delete temp;
			ile--;
			//cout << "Usunieto: ";
			//cout << " " << x << " " << y << " " << o << endl;
		}
	}

	Punkt Front()
	{
		Punkt p;
		if (pierwszy != nullptr)
		{
			p.x = pierwszy->x;
			p.y = pierwszy->y;
			p.odleglosc = pierwszy->odleglosc;
		}
		else
		{
			p.x = -1;
			p.y = -1;
			p.odleglosc = -1;
		}
		return p;
	}

	void WyswietlKolejke()
	{
		Punkt* temp = pierwszy;
		for (int i = 0; i < ile; i++)
		{
			cout << temp->x << " " << temp->y << " " << temp->odleglosc << endl;
			temp = temp->nastepny;
		}
	}

	void ZwolnijKolejke()
	{
		int l = ile;
		for (int i = 0; i < l; i++)
			Pop();
		//cout << "Kolejka zostala zwolniona" << endl;
	}
};