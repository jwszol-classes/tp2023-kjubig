#include <iostream>
#include <queue>
#include <vector>
using namespace std;

class Osoba
{
public:
    float pietroDo;
    int waga = 70;


    Osoba(float doPietra) : pietroDo((int)doPietra) {}
    Osoba(float doPietra, int wag) : pietroDo((int)doPietra), waga(wag) {}
};

class Pietro : public queue<Osoba>
{
public:

};

class Winda
{
public:
    vector<Osoba> pasazerowie;
    float nrPietra = 0;
    int maxWaga = 600;
    int aktualnaWaga = 0;

    Winda(int maxWag) : maxWaga(maxWag) {}
    Winda() {}
};

class SystemWindy
{
public:
    vector<Pietro> pietra;
    Winda winda;

    SystemWindy(int iloscPieter) : pietra(vector<Pietro>(iloscPieter)) {}
    SystemWindy() {}

    void dodajOsobe(int pietro, Osoba os)
    {
        if (pietro >= 0 && pietro < (int)pietra.size())
        {
            pietra[pietro].push(os);
        }
        else
        {
            cout << "Pietro " << pietro << " nie istnieje" << endl;
        }
    }
};


int main()
{
    SystemWindy systemWindy;
    systemWindy.dodajOsobe(0, Osoba(3));
    cout << systemWindy.pietra[0].front().pietroDo << endl;
    return 0;
}
