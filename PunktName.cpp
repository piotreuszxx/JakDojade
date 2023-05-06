#pragma once

class PunktName
{
public:
	int x, y;
	int odleglosc = 0;
	char* name;
	int dl_name;
	PunktName* nastepny;
	PunktName* poprzedni;
	PunktName()
	{
		x = -4;
		y = -4;
		name = nullptr;
		nastepny = nullptr;
		poprzedni = nullptr;
	}
};