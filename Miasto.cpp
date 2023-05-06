#include "Miasto.h"

Miasto::Miasto()
{
	nazwa = nullptr;
	poprzednie = nullptr;
	nastepne = nullptr;
	lista_sasiadow = new ListaMiast;
}

void Miasto::WypiszSasiadow()
{
	lista_sasiadow->WypiszListe();
}