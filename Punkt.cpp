#pragma once

class Punkt
{
public:
	int x, y;
	int odleglosc = 0;
	Punkt* nastepny;
	Punkt* poprzedni;
	Punkt()
	{
		x = -4;
		y = -4;
		nastepny = nullptr;
		poprzedni = nullptr;
	}
};