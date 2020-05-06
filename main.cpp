#include <iostream>
#include <string>
#include <stdlib.h>
#include <list>
#include <unordered_map>

using namespace std;

float manopera = 10;

class abstract{
public:
    virtual float calcul(int, bool);
};

float abstract::calcul(int km = 0, bool online = false){
    return 0;
}
///////////////////////////////////pizza
class pizza:protected abstract{
protected:
    int id_pizza;
    string nume;
//ingrediente\/
    int numar_ingrediente;
    bool alocat = false;    //retine daca s-a alocat memorie ptr ingrediente, cantitatea lor si pret
    string *ingrediente;     //denumiri ingrediente
    int *cantitate_ingrediente;
    int *pret_unitar;

public:
    pizza(int, string, int, string*, int*, int*);
    ~pizza();

    void citire(istream& in);
    void afisare(ostream& out);
    friend istream& operator>>(istream&, pizza&);
    friend ostream& operator<<(ostream&, pizza&);
    void operator=(const pizza&);
    float calcul(int, bool);        //modificare metoda calcul pret
    int id(){
    return id_pizza;}

    bool operator<(pizza& p){
        return calcul(0, false)<p.calcul(0, false);
    }
};
pizza::pizza(int id_pizza = 0, string nume = "", int numar_ingrediente = 0, string* ingrediente = NULL, int* cantitate_ingrediente = NULL,int* pret_unitar = NULL){
    this->id_pizza = id_pizza;
    this->nume = nume;
    try{
        if(numar_ingrediente<0)
            throw numar_ingrediente;
    }catch(int x){
        cout << "Eroare constructor, nu putem avea numar negativ de ingrediente!\n";
        exit(EXIT_FAILURE);
    }
    this->numar_ingrediente = numar_ingrediente;
    if (numar_ingrediente > 0){
        alocat = true;
        this->ingrediente = new string[numar_ingrediente];
        this->cantitate_ingrediente = new int[numar_ingrediente];
        this->pret_unitar = new int[numar_ingrediente];
        for(int i =0; i< numar_ingrediente; i++){
            this->ingrediente[i] = ingrediente[i];
            this->cantitate_ingrediente[i] = cantitate_ingrediente[i];
            try{
                if(cantitate_ingrediente[i]<0)
                    throw cantitate_ingrediente[i];
            }catch(int x){
                cout << "Eroare constructor, nu putem avea cantitate negativa de ingrediente!\n";
                exit(EXIT_FAILURE);
            }
            this->pret_unitar[i] = pret_unitar[i];
            try{
                if(pret_unitar[i]<0)
                    throw pret_unitar[i];
            }catch(int x){
                cout << "Eroare constructor, nu putem avea un pret unitar negativ!\n";
                exit(EXIT_FAILURE);
            }
        }
    }
}
pizza::~pizza(){
    delete[] ingrediente;
    delete[] cantitate_ingrediente;
    delete[] pret_unitar;
}

void pizza::citire(istream& in){
    cout << "Introdu noul id al pizzei: ";
    try{
        in >> id_pizza;
    }
    catch(int c){

    }
    cout << "\nIntrodu numele pizzei: ";
    in >> nume;

    cout << "\nIntrodu numarul ingredientelor: ";
    in >> numar_ingrediente;
    while(numar_ingrediente < 0){
        cout << "\nNu putem avea un numar negativ de ingrediente!! Introdu un numar valid!";
        cout << "\nIntrodu numarul ingredientelor: ";
        in >> numar_ingrediente;
    }

    if(numar_ingrediente > 0){
        if(alocat){
            delete[] ingrediente;
            delete[] cantitate_ingrediente;
            delete[] pret_unitar;
        }
        alocat = true;
        ingrediente = new string[numar_ingrediente];
        cantitate_ingrediente = new int[numar_ingrediente];
        pret_unitar = new int[numar_ingrediente];
        for(int i = 0; i < numar_ingrediente; i++){
            cout << "\nNumele ingredientului " << i+1 << ": ";
            in >> ingrediente[i];
            cout << "\nCantitatea necesara de " << ingrediente[i] << ": ";
            in >> cantitate_ingrediente[i];
            while(cantitate_ingrediente[i] < 0){
                cout << "\nNu putem avea numar negativ pentru cantitatea de ingrediente! Te rog introdu un numar valid!";
                cout << "\nCantitatea necesara de " << ingrediente[i] << ": ";
                in >> cantitate_ingrediente[i];
            }
            cout << "\nPretul (pe unitate) pentru " << ingrediente[i] << ": ";
            in >> pret_unitar[i];
            while(pret_unitar[i] < 0){
                cout << "\nNu putem avea numar negativ pentru pretul ingredientelor!! Te rog introdu un pret valid!!";
                cout << "\nPretul (pe unitate) pentru " << ingrediente[i] << ": ";
                in >> pret_unitar[i];
            }
        }
    }
}
istream& operator>>(istream& in, pizza& p){
    p.citire(in);
    return in;
}

void pizza::afisare(ostream& out){
    cout << id_pizza << "\t" << nume << "\t" << numar_ingrediente << " ingrediente\n";
    if(numar_ingrediente > 0){
        cout << "\tLista ingrediente(nume cantitate pret):\n";
        for(int i=0; i<numar_ingrediente; i++){
            cout << "\t\t" << ingrediente[i] << "\t" << cantitate_ingrediente[i] << "\t" << pret_unitar[i] << endl;
        }
    }
}
ostream& operator<<(ostream& out, pizza& p){
    p.afisare(out);
    return out;
}
void pizza::operator=(const pizza& p){
    id_pizza = p.id_pizza;
    nume = p.nume;
    numar_ingrediente = p.numar_ingrediente;
    if(numar_ingrediente > 0){
        if(alocat){
            delete[] ingrediente;
            delete[] cantitate_ingrediente;
            delete[] pret_unitar;
        }
        alocat = true;
        ingrediente = new string[numar_ingrediente];
        cantitate_ingrediente = new int[numar_ingrediente];
        pret_unitar = new int[numar_ingrediente];
        for(int i = 0; i < numar_ingrediente; i++){
            ingrediente[i] = p.ingrediente[i];
            cantitate_ingrediente[i] = p.cantitate_ingrediente[i];
            pret_unitar[i] = p.pret_unitar[i];
        }
    }
}

float pizza::calcul(int km = 0, bool online = false){
    int temp = 0;
    if (numar_ingrediente > 0)
        for(int i=0; i<numar_ingrediente; i++)
            temp += cantitate_ingrediente[i]*pret_unitar[i];
    if(online)
        while(km > 0)
            temp += temp*5/100;
    return temp;
}







/////////////////////////////////////////////////////////////////////class Meniu
template <class t> class meniu{
    //t *v;
    unordered_map<int, list <pizza>> *v;
    int index;          //se incrementeaza automat la cumpararea unui produs           suprascriere += !!!!!
    int nr;
public:
    re(){return 5;}
};


















int main()
{
    string *temp_nume = new string[2];
    temp_nume[0] = "Ardei gras";
    temp_nume[1] = "Carnati";
    int *temp_cantitate = new int [2];
    temp_cantitate[0] = 1;
    temp_cantitate[1] = 2;
    int *temp_pret = new int [2];
    temp_pret[0] = 1;
    temp_pret[1] = 1;
    pizza a1(1, "Capriciosa", 2, temp_nume, temp_cantitate, temp_pret);
    cout << a1;
    temp_nume[0] = "Jalapenos";
    temp_nume[1] = "Mozzarella";
    temp_cantitate[0] = 1;
    temp_cantitate[1] = 2;
    temp_pret[0] = 2;
    temp_pret[1] = 3;
    pizza a2(2, "Pepperoni", 2, temp_nume, temp_cantitate, temp_pret);
    cout << a2;
    delete[] temp_nume;
    delete[] temp_cantitate;
    delete[] temp_pret;






    //unordered_map<int, pizza> x;


    list <pizza> a;
    a.push_back(a1);

    //pizza a1(1,"nume1");
    /*
    pizza a2(2,"nume2");
    a.push_back(a1);
    a.push_back(a2);

    //iterator
    list <pizza>::iterator i;
    for(i=a.begin(); i != a.end(); i++)
        cout << *i;
    a.sort();
    //dupa sortare
    for(i=a.begin(); i != a.end(); i++)
        cout << *i;
    meniu <pizza> q;



    unordered_map<int, char> x = {{1, 'a'}, {2,'b'}};   */
    /*          vf daca inputul este int
    int *a;
    a = new int[5];/*
    if(cin >> a[0]){
        cout << "ok";
    }else
        cout << "nu";
    cout << a[0];
    */
    return 0;
}
