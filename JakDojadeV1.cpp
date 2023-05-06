#include <iostream>
#include <stdio.h>
#include <cstdlib> 
#include "ListaMiast.h"
#include "ListaXY.cpp"
#include "ListaXYNames.cpp"
#include "Kolejka.cpp"
#include "KolejkaPunktow.cpp"

#define buffer 15
using namespace std;

char* Znajdz(char** tab, int x, int y, int rozmiarx, int rozmiary, int& dl)
{
    char* nazwa = nullptr;
    int lewa = 0, prawa = 0;
    int poziom = y;
    if (x > 0 && isalnum(tab[y][x - 1])) // lewa
    {
        lewa = x - 1;
        prawa = x - 1;
        while (lewa > 0 && isalnum(tab[y][lewa - 1]))
        {
            lewa--;
        }
    }
    else if (x < rozmiarx - 1 && isalnum(tab[y][x + 1])) // prawa
    {
        lewa = x + 1;
        prawa = x + 1;
        while (prawa < rozmiarx - 1 && isalnum(tab[y][prawa + 1]))
        {
            prawa++;
        }
    }
    else if (x > 0 && y > 0 && isalnum(tab[y - 1][x - 1])) // lewa gora
    {
        poziom = y - 1;
        lewa = x - 1;
        prawa = x - 1;
        while (lewa > 0 && isalnum(tab[y - 1][lewa - 1]))
        {
            lewa--;
        }
        while (prawa < rozmiarx - 1 && isalnum(tab[y - 1][prawa + 1]))
        {
            prawa++;
        }
    }
    else if (y > 0 && isalnum(tab[y - 1][x])) // gora
    {
        poziom = y - 1;
        lewa = x;
        prawa = x;
        while (lewa > 0 && isalnum(tab[y - 1][lewa - 1]))
        {
            lewa--;
        }
        while (prawa < rozmiarx - 1 && isalnum(tab[y - 1][prawa + 1]))
        {
            prawa++;
        }
    }
    else if (x < rozmiarx - 1 && y > 0 && isalnum(tab[y - 1][x + 1])) // prawa gora
    {
        poziom = y - 1;
        lewa = x + 1;
        prawa = x + 1;
        while (lewa > 0 && isalnum(tab[y - 1][lewa - 1]))
        {
            lewa--;
        }
        while (prawa < rozmiarx - 1 && isalnum(tab[y - 1][prawa + 1]))
        {
            prawa++;
        }
    }
    else if (x > 0 && y < rozmiary - 1 && isalnum(tab[y + 1][x - 1])) // lewa dol
    {
        poziom = y + 1;
        lewa = x - 1;
        prawa = x - 1;
        while (lewa > 0 && isalnum(tab[y + 1][lewa - 1]))
        {
            lewa--;
        }
        while (prawa < rozmiarx - 1 && isalnum(tab[y + 1][prawa + 1]))
        {
            prawa++;
        }
    }
    else if (y < rozmiary - 1 && isalnum(tab[y + 1][x])) // dol
    {
        poziom = y + 1;
        lewa = x;
        prawa = x;
        while (lewa > 0 && isalnum(tab[y + 1][lewa - 1]))
        {
            lewa--;
        }
        while (prawa < rozmiarx - 1 && isalnum(tab[y + 1][prawa + 1]))
        {
            prawa++;
        }
    }
    else if (x < rozmiarx - 1 && y < rozmiary - 1 && isalnum(tab[y + 1][x + 1])) // prawa dol
    {
        poziom = y + 1;
        lewa = x + 1;
        prawa = x + 1;
        while (lewa > 0 && isalnum(tab[y + 1][lewa - 1]))
        {
            lewa--;
        }
        while (prawa < rozmiarx - 1 && isalnum(tab[y + 1][prawa + 1]))
        {
            prawa++;
        }
    }
    nazwa = new char[prawa - lewa + 2];
    for (int i = 0; i < prawa - lewa + 1; i++)
    {
        nazwa[i] = tab[poziom][lewa + i];
        dl++;
    }
    nazwa[prawa - lewa + 1] = '\0';
    dl++;

    return nazwa;
}

int Input(char** tab, int rozmiarx, int rozmiary, KolejkaPunktow* kolejkaxy)
{
    int licznik = 0;
    for (int y = 0; y < rozmiary; y++)
    {
        for (int x = 0; x < rozmiarx; x++)
        {
            char znak;
            znak = getchar();
            if (znak == '*')
            {
                kolejkaxy->Push(x, y, 0);
                licznik++;
            }
            tab[y][x] = znak;
        }
        getchar();
    }
    return licznik;
}

char* WczytajNazwe(int& dl)
{
    char* temp = new char[buffer];
    int i = 1;
    temp[0] = _getchar_nolock();
    while (temp[i-1] != ' ')
    {
        temp[i] = _getchar_nolock();
        i++;
    }
    temp[i-1] = '\0';
    dl = i;
    return temp;
}

int Hash(char* nazwa, int dl, int rozmiarHT)
{
    int suma = 0;
    for (int i = 0; i < dl; i++)
    {
        suma += (nazwa[i] + 7 * i);
    }
    return suma % rozmiarHT;
}

int HashXY(int x, int y, int rozmiarHT)
{
    return ((1 / 2) * (x + y) * (x + y + 1) + y) % rozmiarHT;
}

bool MaSasiadow(char** tab, int rozmiarx, int rozmiary, int x, int y)
{
    if (y - 1 >= 0 && (tab[y - 1][x] == '*' || tab[y - 1][x] == '#'))
    {
		return true;
	}
    if (y + 1 < rozmiary && (tab[y + 1][x] == '*' || tab[y + 1][x] == '#'))
    {
		return true;
	}
    if (x - 1 >= 0 && (tab[y][x - 1] == '*' || tab[y][x - 1] == '#'))
    {
        return true;
    }
    if (x + 1 < rozmiarx && (tab[y][x + 1] == '*' || tab[y][x + 1] == '#'))
    {
		return true;
	}
    return false;
}

void WczytajLoty(ListaMiast* hashtable, int rozmiarHT)
{
    int ilosc_lotow;
    scanf_s("%d", &ilosc_lotow);
    //cin >> ilosc_lotow;
    getchar();

    for (int i = 0; i < ilosc_lotow; i++)
    {
        //cout << "Lot nr " << i + 1 << endl;
        char* skad;
        char* dokad;
        int dl_skad;
        int dl_dokad;
        int odleglosc_lotu;

        /*

        char bufor[buffer];
        int lewaspacja = 0;
        int prawaspacja;
        while (true)
        {
            char znak;
            znak = _getchar_nolock();
            bufor[lewaspacja] = znak;
            if (znak == ' ')
            {
                prawaspacja = lewaspacja + 1;
                break;
            }
            else lewaspacja++;
        }
        while (true)
        {
            char znak;
            znak = _getchar_nolock();
            bufor[prawaspacja] = znak;
            if (znak == ' ')
            {
                break;
            }
            else prawaspacja++;
        }
        //bufor[prawaspacja + 1] = '\0';

        skad = new char[lewaspacja + 1];
        dl_skad = lewaspacja + 1;

        dokad = new char[prawaspacja - lewaspacja];
        dl_dokad = prawaspacja - lewaspacja;

        for (int i = 0; i < lewaspacja; i++)
        {
            skad[i] = bufor[i];
        }
        skad[lewaspacja] = '\0';

        for (int i = 0; i < prawaspacja - lewaspacja - 1; i++)
        {
            dokad[i] = bufor[i + lewaspacja + 1];
        }
        dokad[prawaspacja - lewaspacja - 1] = '\0';

        */

        skad = WczytajNazwe(dl_skad);
        dokad = WczytajNazwe(dl_dokad);
        scanf_s("%d", &odleglosc_lotu);
        //cin >> odleglosc_lotu;
        //getchar();
        _getchar_nolock();

        int hash_skad = Hash(skad, dl_skad, rozmiarHT);
        int hash_dokad = Hash(dokad, dl_dokad, rozmiarHT);
        hashtable[hash_skad].DodajLot(skad, dokad, dl_dokad, hashtable, rozmiarHT, odleglosc_lotu, hash_dokad);
    }
}

void Dijkstra(ListaMiast* hashtable_og, int rozmiarHT, int rodzaj, char* nazwa_startowego, int dl_nazwy_startowego, char* nazwa_docelowego, int dl_nazwy_docelowego, ListaMiast* lista_wierzcholkow_og)
{
    int licznik = 0;
    while (true)
    {
        if (nazwa_startowego[licznik] != nazwa_docelowego[licznik])
            break;
        if (nazwa_startowego[licznik] == '\0' && nazwa_docelowego[licznik] == '\0')
        {
            cout << 0 << endl;
            return;
        }
        licznik++;
    }

    int sprawdzone = 0;

    Miasto** tablica_wierzcholkow = new Miasto * [rozmiarHT];
    for (int i = 0; i < rozmiarHT; i++)
    {
        tablica_wierzcholkow[i] = new Miasto;
    }
    int licznik_tablicy = 0;
    Miasto* tmp = lista_wierzcholkow_og->pierwsze;
    while (tmp)
    {
        int dl_nazwy = tmp->dl_nazwy;
        int hash = tmp->hash;
        int x = tmp->x;
        int y = tmp->y;
        char* nazwa = new char[dl_nazwy];
        for (int i = 0; i < dl_nazwy; i++)
        {
            nazwa[i] = tmp->nazwa[i];
        }
        tablica_wierzcholkow[licznik_tablicy]->nazwa = nazwa;
        tablica_wierzcholkow[licznik_tablicy]->dl_nazwy = dl_nazwy;
        tablica_wierzcholkow[licznik_tablicy]->hash = hash;
        tablica_wierzcholkow[licznik_tablicy]->x = x;
        tablica_wierzcholkow[licznik_tablicy]->y = y;
        licznik_tablicy++;
        tmp = tmp->nastepne;
    }


    bool* visited = new bool[rozmiarHT];
    for (int i = 0; i < rozmiarHT; i++)
    {
        visited[i] = false;
    }

    int* tablica_kosztow = new int[rozmiarHT];
    for (int i = 0; i < rozmiarHT; i++)
    {
        tablica_kosztow[i] = inf;
    }

    int* tablica_poprzednikow = new int[rozmiarHT];
    for (int i = 0; i < rozmiarHT; i++)
    {
        tablica_poprzednikow[i] = -1;
    }

    int indeks_wynikowy = 0;
    for (int i = 0; i < rozmiarHT; i++)
    {
        if (strcmp(tablica_wierzcholkow[i]->nazwa, nazwa_startowego) == 0)
        {
            tablica_kosztow[i] = 0;
        }
        else if (strcmp(tablica_wierzcholkow[i]->nazwa, nazwa_docelowego) == 0)
        {
            indeks_wynikowy = i;
        }
    }

    while (sprawdzone != rozmiarHT)
    {
        int min = inf + 1;
        int indeks_min = 0;
        for (int i = 0; i < rozmiarHT; i++)
        {
            if (tablica_kosztow[i] <= min && visited[i] == false)
            {
                min = tablica_kosztow[i];
                indeks_min = i;
            }
        }
        visited[indeks_min] = true;
        sprawdzone++;
        int hash_sprawdzanego = tablica_wierzcholkow[indeks_min]->hash;
        Miasto* temp = hashtable_og[hash_sprawdzanego].pierwsze;
        while (temp) // szukam tego wierzcholka w hashtable
        {
            if (tablica_wierzcholkow[indeks_min]->x == temp->x && tablica_wierzcholkow[indeks_min]->y == temp->y)
            {
                Miasto* w = temp->lista_sasiadow->pierwsze; // w to sasiedzi
                while (w)
                {
                    for (int i = 0; i < rozmiarHT; i++) // kazdego z sasiadow szukam w tablicy wierzcholkow i sprawdzam czy jest visited
                    {
                        if (tablica_wierzcholkow[i]->x == w->x && tablica_wierzcholkow[i]->y == w->y)
                        {
                            if (visited[i] == false)
                            {
                                if (tablica_kosztow[i] > (tablica_kosztow[indeks_min] + w->odleglosc))
                                {
                                    tablica_kosztow[i] = tablica_kosztow[indeks_min] + w->odleglosc;
                                    tablica_poprzednikow[i] = indeks_min;
                                }
                            }
                        }
                    }
                    w = w->nastepne;
                }
            }
            temp = temp->nastepne;
        }
    }

    //cout << "Najkrotsza droga: " << endl;
    cout << tablica_kosztow[indeks_wynikowy];
    if (rodzaj == 1)
    {
        cout << " ";
        ListaMiast* lista_wynikowa = new ListaMiast;
        int indeks = indeks_wynikowy;
        while (indeks != -1)
        {
            int dl = tablica_wierzcholkow[indeks]->dl_nazwy;
            char* nazwa = new char[dl];
            for (int i = 0; i < tablica_wierzcholkow[indeks]->dl_nazwy; i++)
            {
                nazwa[i] = tablica_wierzcholkow[indeks]->nazwa[i];
            }
            lista_wynikowa->DodajMiasto(nazwa, dl, 0, 0, 0, 0);
            indeks = tablica_poprzednikow[indeks];
        }
        //lista_wynikowa->WypiszListeReverse();
        cout << "w";
        lista_wynikowa->ZwolnijListe();
        delete lista_wynikowa;
    }

    for (int i = 0; i < rozmiarHT; i++)
    {
        delete tablica_wierzcholkow[i];
    }
    delete[] tablica_wierzcholkow;
    delete[] tablica_kosztow;
    delete[] tablica_poprzednikow;
    delete[] visited;
}

void WczytajPolecenia(ListaMiast* hashtable_og, int rozmiarHT, ListaMiast* lista_wierzcholkow)
{
    int ilosc_polecen;
    scanf_s("%d", &ilosc_polecen);
    //cin >> ilosc_polecen;
    getchar();

    for (int i = 0; i < ilosc_polecen; i++)
    {
        char* start = nullptr;
        char* koniec = nullptr;
        int dl_start;
        int dl_koniec;
        int rodzaj;

        /*
        char bufor[buffer];
        int lewaspacja = 0;
        int prawaspacja;
        while (true)
        {
            char znak;
            znak = getchar();
            bufor[lewaspacja] = znak;
            if (znak == ' ')
            {
                prawaspacja = lewaspacja + 1;
                break;
            }
            else lewaspacja++;
        }
        while (true)
        {
            char znak;
            znak = getchar();
            bufor[prawaspacja] = znak;
            if (znak == ' ')
            {
                break;
            }
            else prawaspacja++;
        }

        start = new char[lewaspacja + 1];
        dl_start = lewaspacja + 1;

        koniec = new char[prawaspacja - lewaspacja];
        dl_koniec = prawaspacja - lewaspacja;

        for (int i = 0; i < lewaspacja; i++)
        {
            start[i] = bufor[i];
        }
        start[lewaspacja] = '\0';

        for (int i = 0; i < prawaspacja - lewaspacja - 1; i++)
        {
            koniec[i] = bufor[i + lewaspacja + 1];
        }
        koniec[prawaspacja - lewaspacja - 1] = '\0';
        */

        start = WczytajNazwe(dl_start);
        koniec = WczytajNazwe(dl_koniec);

        scanf_s("%d", &rodzaj);
        //cin >> rodzaj;
        getchar();

        int hash_start = Hash(start, dl_start, rozmiarHT);
        int hash_koniec = Hash(koniec, dl_koniec, rozmiarHT);
        Dijkstra(hashtable_og, rozmiarHT, rodzaj, start, dl_start, koniec, dl_koniec, lista_wierzcholkow);
        //if(i != ilosc_polecen)
        cout << endl;
        delete[] start;
        delete[] koniec;
    }
}

int main()
{
    int rozmiarx, rozmiary, rozmiarHT;
    cin >> rozmiarx >> rozmiary;
    getchar();
    char** tab = new char* [rozmiary];
    for (int i = 0; i < rozmiary; i++)
    {
        tab[i] = new char[rozmiarx];
    }

    KolejkaPunktow* kolejkaxy = new KolejkaPunktow; // kolejka punktow, ktore sa gwiazdkami

    ListaMiast* lista_wierzcholkow = new ListaMiast; // lista wszystkich wierzcholkow

    rozmiarHT = Input(tab, rozmiarx, rozmiary, kolejkaxy);

    ListaXYNames* hashtable_XYNames = new ListaXYNames[rozmiarHT];

    Punkt* temp = kolejkaxy->pierwszy;
    while (temp)
    {
        int dl_nazwy;
        char* nazwa = Znajdz(tab, temp->x, temp->x, rozmiarx, rozmiary, dl_nazwy);
        int hash_xy = HashXY(temp->x, temp->y, rozmiarHT);
        hashtable_XYNames[hash_xy].DodajPunktName(temp->x, temp->y, nazwa, dl_nazwy);
        temp = temp->nastepny;
    }

    ListaMiast* hashtable = new ListaMiast[rozmiarHT]; // tablica list miast, ktorym przypisuje indeksy z funkcji haszujacej


    while (kolejkaxy->Ilosc())
    {
        int dl_nazwy = 0;
        Punkt punkt = kolejkaxy->Front();
        kolejkaxy->Pop(); // dealokacja punktu z kolejki

        //char* nazwa = Znajdz(tab, punkt.x, punkt.y, rozmiarx, rozmiary, dl_nazwy);
        //int hash = Hash(nazwa, dl_nazwy, rozmiarHT);

         
        hashtable[hash].DodajMiasto(nazwa, dl_nazwy, punkt.x, punkt.y, punkt.odleglosc, hash);
        lista_wierzcholkow->DodajMiasto(nazwa, dl_nazwy, punkt.x, punkt.y, punkt.odleglosc, hash);

        if (!MaSasiadow(tab, rozmiarx, rozmiary, punkt.x, punkt.y))
        {
			continue;
		}

        bool** visited = new bool* [rozmiary];
        for (int i = 0; i < rozmiary; i++)
        {
            visited[i] = new bool[rozmiarx];
            for (int j = 0; j < rozmiarx; j++)
            {
                visited[i][j] = false;
            }
        }
        visited[punkt.y][punkt.x] = true;
        KolejkaPunktow* kolejkabfs = new KolejkaPunktow; // kolejka badanych punktow
        kolejkabfs->Push(punkt.x, punkt.y, punkt.odleglosc);

        while (kolejkabfs->Ilosc())
        {
            Punkt p = kolejkabfs->Front();
            kolejkabfs->Pop();
            if (p.x > 0 && !visited[p.y][p.x - 1] && tab[p.y][p.x - 1] == '#') // lewo
            {
                visited[p.y][p.x - 1] = true;
                kolejkabfs->Push(p.x - 1, p.y, p.odleglosc + 1);
            }
            else if (p.x > 0 && !visited[p.y][p.x - 1] && tab[p.y][p.x - 1] == '*')
            {
                visited[p.y][p.x - 1] = true;
                int dl_nazwy_sasiada = 0;
                char* nazwa_sasiada = Znajdz(tab, p.x - 1, p.y, rozmiarx, rozmiary, dl_nazwy_sasiada);
                int hash_sasiada = Hash(nazwa_sasiada, dl_nazwy_sasiada, rozmiarHT);
                hashtable[hash].DodajSasiada(nazwa, nazwa_sasiada, dl_nazwy_sasiada, p.x - 1, p.y, p.odleglosc + 1, hash_sasiada);
            }

            if (p.x < rozmiarx - 1 && !visited[p.y][p.x + 1] && tab[p.y][p.x + 1] == '#') // prawo
            {
                visited[p.y][p.x + 1] = true;
                kolejkabfs->Push(p.x + 1, p.y, p.odleglosc + 1);
            }
            else if (p.x < rozmiarx - 1 && !visited[p.y][p.x + 1] && tab[p.y][p.x + 1] == '*')
            {
                visited[p.y][p.x + 1] = true;
                int dl_nazwy_sasiada = 0;
                char* nazwa_sasiada = Znajdz(tab, p.x + 1, p.y, rozmiarx, rozmiary, dl_nazwy_sasiada);
                int hash_sasiada = Hash(nazwa_sasiada, dl_nazwy_sasiada, rozmiarHT);
                hashtable[hash].DodajSasiada(nazwa, nazwa_sasiada, dl_nazwy_sasiada, p.x + 1, p.y, p.odleglosc + 1, hash_sasiada);
            }

            if (p.y > 0 && !visited[p.y - 1][p.x] && tab[p.y - 1][p.x] == '#') // gora
            {
                visited[p.y - 1][p.x] = true;
                kolejkabfs->Push(p.x, p.y - 1, p.odleglosc + 1);
            }
            else if (p.y > 0 && !visited[p.y - 1][p.x] && tab[p.y - 1][p.x] == '*')
            {
                visited[p.y - 1][p.x] = true;
                int dl_nazwy_sasiada = 0;
                char* nazwa_sasiada = Znajdz(tab, p.x, p.y - 1, rozmiarx, rozmiary, dl_nazwy_sasiada);
                int hash_sasiada = Hash(nazwa_sasiada, dl_nazwy_sasiada, rozmiarHT);
                hashtable[hash].DodajSasiada(nazwa, nazwa_sasiada, dl_nazwy_sasiada, p.x, p.y - 1, p.odleglosc + 1, hash_sasiada);
            }

            if (p.y < rozmiary - 1 && !visited[p.y + 1][p.x] && tab[p.y + 1][p.x] == '#') // dol
            {
                visited[p.y + 1][p.x] = true;
                kolejkabfs->Push(p.x, p.y + 1, p.odleglosc + 1);
            }
            else if (p.y < rozmiary - 1 && !visited[p.y + 1][p.x] && tab[p.y + 1][p.x] == '*')
            {
                visited[p.y + 1][p.x] = true;
                int dl_nazwy_sasiada = 0;
                char* nazwa_sasiada = Znajdz(tab, p.x, p.y + 1, rozmiarx, rozmiary, dl_nazwy_sasiada);
                int hash_sasiada = Hash(nazwa_sasiada, dl_nazwy_sasiada, rozmiarHT);
                hashtable[hash].DodajSasiada(nazwa, nazwa_sasiada, dl_nazwy_sasiada, p.x, p.y + 1, p.odleglosc + 1, hash_sasiada);
            }
        }
    }
    delete kolejkaxy;

    // wczytanie lotów
    WczytajLoty(hashtable, rozmiarHT);

    cout << "wczytal loty" << endl;
    WczytajPolecenia(hashtable, rozmiarHT, lista_wierzcholkow);











    // wypisywanie
    /*
    cout << "----------------" << endl;

    for (int i = 0; i < rozmiarHT; i++)
    {
        cout << i << " ";
        hashtable[i].WypiszListe();
        cout << endl;
    }

    cout << "----------------" << endl;

    for (int i = 0; i < rozmiarHT; i++)
    {
        cout << "Hashtable[" << i << "]" << endl;
        //cout << "Sasiedzi Pierwszego Miasta: " << endl;
        Miasto* temp = hashtable[i].pierwsze;
        int s = 1;
        while (temp)
        {
            cout << "Sasiedzi miasta nr " << s << ": " << endl;
            temp->WypiszSasiadow();
            s++;
            temp = temp->nastepne;
        }
    }
    */

    //Dijkstra(hashtable, rozmiarHT);// , "A", "B");

    // dealokacja

    delete lista_wierzcholkow;

    for (int i = 0; i < rozmiarHT; i++)
    {
        Miasto* temp = hashtable[i].pierwsze;
        while (temp)
        {
            temp->lista_sasiadow->ZwolnijListe();
            delete temp->lista_sasiadow;
            temp = temp->nastepne;
        }
        hashtable[i].ZwolnijListe();
    }

    for (int i = 0; i < rozmiarHT; i++)
    {
        hashtable[i].ZwolnijListe();
    }
    delete[] hashtable;

    for (int i = 0; i < rozmiary; i++)
    {
        if (tab[i])
            delete[] tab[i];
    }
    delete[] tab;

    return 0;
}