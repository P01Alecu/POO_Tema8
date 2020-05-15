#include <iostream>
#include <string>
#include <stdlib.h>
#include <list>
#include <unordered_map>

using namespace std;

float manopera = 10;

class abstract{     //in cerinta scria ca aceasta clasa abstracta trebuie sa aiba doar metoda de calcul...
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
    int index;  //incrementat automat la vanzarea unui produs
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
    float calcul(int, bool);
    int id(){
        return id_pizza;}

    bool operator<(pizza& p){
        return calcul(0, false)<p.calcul(0, false);
    }
    void operator +=(int);
    int get_index(){
        return index;
    };
};
pizza::pizza(int id_pizza = 0, string nume = "", int numar_ingrediente = 0, string* ingrediente = NULL, int* cantitate_ingrediente = NULL,int* pret_unitar = NULL){
    index = 0;
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
    //delete[] ingrediente;
    //delete[] cantitate_ingrediente;
    //delete[] pret_unitar;
    cout << "\nDestructor\n";
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

void pizza::operator+=(int x){
    index+=x;
}






/////////////////////////////////////////////////////////////////////class Meniu
template <class t> class meniu{
    //t *v;
    unordered_map<int, list <t>> *v;
    int nr;
public:
    meniu(){
        v = new unordered_map<int, list<t>>;
    };
    ~meniu(){};

    friend istream& operator>>(istream& in, meniu<t> &g){
        cout << "Adaugati un produs in meniu! \n";
        cout << "Cate produse vrei sa adaugi? ";
        int i;
        in >> i;
        while(i <= 0){
            cout << "Ati introdus un numar invalid. Va rugam introduceti un numar > 0 SAU -1 pentru a anula!! ";
            in >> i;
            if(i == -1)
                break;
        }
        while(i > 0){
            t temp;
            bool ok = true;
            in >> temp;
            int id_pizza = temp.id();
            //Verifica daca exista deja id_ul respectiv in meniu
            auto vf = g.v[0].find(id_pizza);
            if(vf != g.v[0].end()){
                cout << "Deja exista in meniu un produs cu acest id, doriti sa il inlocuiti??  (1/0): ";
                in >> ok;
                if(ok)
                    g.v[0][id_pizza].pop_back();
            }
            if(ok)
                g.v[0][id_pizza].push_back(temp);
            i--;
        }

        return in;
    }

    friend ostream& operator<<(ostream& out, meniu<t> &g){
        unordered_map<int, list<pizza>>::iterator i;
        i = g.v[0].begin();
        //Verifica daca exista produse in meniu
        if(i != g.v[0].end()){
            out << "Afisare meniu: \n";
        }
        else
            out << "Nu exista produse in meniu! \n";


        while(i != g.v[0].end()){
            out << (i->second).front();
            i++;
        }
        return out;
    }
    void operator+=(t p){       // +=pizza
        int id_pizza = p.id();
        (*v)[id_pizza].push_back(p);
    };
    void operator=(meniu& p){
        unordered_map<int, list<pizza>>::iterator i = p.v[0].begin();
        while(i != p.v[0].end()){
            v[0][p.v[0].first] = p.v[0].second;
            i++;
        }

    }
    int get_pizza(){    //exemplificare dynamic cast  ->returneaza numarul de pizza din meniu
        t *temp = new t;
        unordered_map<int, list<pizza>>::iterator i = v[0].begin();
        int numar = 0 ;

        while(i != v[0].end()){
            temp[0] = (i->second).front();
            cout << temp[0]<<endl;//////////////////////
            pizza *temporar= dynamic_cast<pizza*>(temp);
            if(temporar)
                numar++;
            i++;
        }
        return numar;
    }
};














void menu_output(){
    cout << "-Alecu Florin Gabriel-Grupa 211-Proiect 3-Problema 8-\n";
    cout << "1. Adauga produse in meniu.\n";
    cout << "2. Afisaza produsele din meniu.\n";
    cout << "3. Afisaza cate pizza sunt in meniu. --Folosind dynamic cast\n";
    cout << "4. \n";
    cout << "\n0. Iesire\n";
}
void menu(){
    int option;
    meniu<pizza> p;
    do{
        menu_output();
        cin >> option;
        switch(option){
        case 0:
            exit(EXIT_SUCCESS);
        case 1:
            cin >> p;
            break;
        case 2:
            cout << p;
            break;
        case 3:{
            cout << "In meniu sunt " << p.get_pizza() << " pizza.\n";
            break;
        }
        default:
            cout << "Input invalid!!\n";
        }
        system("pause");
        system("cls");

    }while(option !=0 );
}

int main()
{
/*
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
    //cout << a1;
    temp_nume[0] = "Jalapenos";
    temp_nume[1] = "Mozzarella";
    temp_cantitate[0] = 1;
    temp_cantitate[1] = 2;
    temp_pret[0] = 2;
    temp_pret[1] = 3;
    pizza a2(2, "Pepperoni", 2, temp_nume, temp_cantitate, temp_pret);
    //cout << a2;
    delete[] temp_nume;
    delete[] temp_cantitate;
    delete[] temp_pret;

*/

    menu();


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
    */
    return 0;
}
