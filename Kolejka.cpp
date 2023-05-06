#pragma once
#include <iostream>
#include "Miasto.h"
#include "Punkt.cpp"
using namespace std;

class KolejkaMiast
{
public:
	Miasto* pierwsze;
	Miasto* ostatnie;
	int ile;

	KolejkaMiast()
	{
		pierwsze = nullptr;
		ostatnie = nullptr;
		ile = 0;
	}

	int Ilosc()
	{
		return ile;
	}

	void Push(char* nazwa, int dl, int x, int y)
	{
		Miasto* nowe = new Miasto;
		nowe->nazwa = nazwa;
		nowe->dl_nazwy = dl;
		nowe->x = x;
		nowe->y = y;

		if (pierwsze == nullptr)
			pierwsze = nowe;
		else
		{
			Miasto* temp = ostatnie;
			temp->nastepne = nowe;
		}
		ostatnie = nowe;
		ile++;
	}

	void Pop()
	{
		if (pierwsze == nullptr)
			return;
		else
		{
			Miasto* temp = pierwsze;
			char* nazwa = temp->nazwa;
			int dl_nazwy = temp->dl_nazwy;
			int x = temp->x;
			int y = temp->y;
			pierwsze = temp->nastepne;
			delete temp->nazwa;
			delete temp;
			ile--;
			/*
			cout << "Usunieto: ";
			for(int i = 0; i < dl_nazwy; i++)
				cout << nazwa[i];
			cout << " " << x << " " << y << endl;
			*/
		}
	}

	Punkt Front()
	{
		Punkt p;
		if(pierwsze != nullptr)
		{
			p.x = pierwsze->x;
			p.y = pierwsze->y;
		}
		else
		{
			p.x = -1;
			p.y = -1;
		}
		return p;
	}

	void WypiszKolejke()
	{
		Miasto* temp = pierwsze;
		for (int i = 0; i < ile; i++)
		{
			cout<< temp->nazwa << " " << temp->x << " " << temp->y << endl;
			temp = temp->nastepne;
		}
	}

	void ZwolnijKolejke()
	{
		int l = ile;
		for (int i = 0; i < l; i++)
			Pop();
		//cout << "Kolejka zostala zwolniona" <<endl;
	}
};