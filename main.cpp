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
    static int numar_total_pizza;
    int id_pizza;
    string nume;
    int index;  //incrementat automat la vanzarea unui produs prin +=
//ingrediente\/
    int numar_ingrediente;
    bool alocat = false;    //retine daca s-a alocat memorie ptr ingrediente, cantitatea lor si pret
    string *ingrediente;     //denumiri ingrediente
    int *cantitate_ingrediente;
    int *pret_unitar;
    bool vegetariana;

public:
    pizza(int, string, bool, int, string*, int*, int*);
    ~pizza();

    void citire(istream& in);
    void afisare(ostream& out);
    friend istream& operator>>(istream&, pizza&);
    friend ostream& operator<<(ostream&, pizza&);
    void operator=(const pizza&);
    float calcul(int, bool);
    int id() const{
        return id_pizza;}

    bool operator<(pizza& p){
        return calcul(0, false)<p.calcul(0, false);
    }
    void operator +=(int);
    int get_index(){
        return index;
    };
    static int static_pizza(){
        return numar_total_pizza;
    };
    bool e_vegetariana(){
        return vegetariana;
    }


};
int pizza::numar_total_pizza = 0;
pizza::pizza(int id_pizza = 0, string nume = "", bool vegetariana = false,int numar_ingrediente = 0, string* ingrediente = NULL, int* cantitate_ingrediente = NULL,int* pret_unitar = NULL){
    index = 0;
    this->id_pizza = id_pizza;
    if(id_pizza!=0 || nume != "")
        numar_total_pizza++;        //incrementare numar_total_pizza
    this->nume = nume;
    this->vegetariana = vegetariana;
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
    numar_total_pizza++;    //inc numar_total_pizza
    cout << "\nEste vegetariana? (0/1) ";
    in >> vegetariana;
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
    if(id_pizza!=0)
        numar_total_pizza++;
    nume = p.nume;
    vegetariana = p.vegetariana;
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
        while(km > 0){
            temp += temp*5/100;
            km = km - 10;
        }
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
            out << "\tPret de baza (fara livrare): " << ((i->second).front()).calcul() << endl;
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
            v[0][i->first] = i->second;
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
    float pret(int id=0, int km=0, int online=false){   //returneaza pretul unei pizza oferindu-i id-ul pizzei (si eventual km si online)
        if(v[0].find(id) != v[0].end())
            return (v[0][id]).front().calcul(km, online);
        return 0;
    }

    void comanda(){ //cumpara produs
        cout << "Introdu id-ul pizzei pe care vrei sa o cumperi: ";
        int id;
        cin >> id;

        if(v[0].find(id) != v[0].end()){
            cout << "Aceasta pizza costa: " << (v[0][id]).front().calcul() << " lei.\n";
            (v[0][id]).front() += 1;
        }
        else
            cout << "Acest id nu exista in meniu!";
    }
    void comanda_online(){
        cout << "Introdu id-ul pizzei pe care vrei sa o cumperi: ";
        int id;
        cin >> id;

        if(v[0].find(id) != v[0].end()){
            int km;
            cout << "Introdu nr km: ";
            cin >> km;
            cout << "\nAceasta pizza costa: " << (v[0][id]).front().calcul(km, true) << " lei.\n";
            (v[0][id]).front() += 1;
        }
        else
            cout << "Acest id nu exista in meniu!";
    }
    float venit_vegetarian(){
        unordered_map<int, list<pizza>>::iterator i = v[0].begin();
        float temp = 0;
        while(i != v[0].end()){
            if((i->second).front().e_vegetariana())
                temp += (i->second).front().get_index() * (i->second).front().calcul();
            i++;
        }
        if(temp == 0)
            cout << "Nu s-a vandut nicio pizza vegetariana.\n";
        return temp;
    }
    float venit(){
        unordered_map<int, list<pizza>>::iterator i = v[0].begin();
        float temp = 0;
        while(i != v[0].end()){
            temp += (i->second).front().get_index() * (i->second).front().calcul();
            i++;
        }
        if (temp==0)
            cout << "Nu s-a vandut inca nicio pizza.\n";
        return temp;
    }
};






void menu_output(){
    cout << "-Alecu Florin Gabriel-Grupa 211-Proiect 3-Problema 8-\n";
    cout << "1. Adauga produse in meniu.\n";
    cout << "2. Afisaza produsele din meniu.\n";
    cout << "3. Afisaza cate pizza sunt in meniu. --Folosind dynamic cast\n";
    cout << "4. Afisaza numarul de pizza citite in total (in tot programul). --Folosire variabila si metoda statica...\n";
    cout << "5. Comanda o pizza. \n";
    cout << "6. Comanda o pizza ONLINE.\n";
    cout << "7. Afisaza venitul din vanzarea de pizza.\n";
    cout << "8. Afisaza venitul din vanzarea de pizza vegetariana.\n";
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
        case 4:
            cout << "Numarul de pizza citite in total: " << pizza::static_pizza() << ".\n";
            break;
        case 5:
            cout << p;
            p.comanda();
            break;
        case 6:
            cout << p;
            p.comanda_online();
            break;
        case 7:
            cout << p.venit() << endl;
            break;
        case 8:
            cout << p.venit_vegetarian() << endl;
            break;
        default:
            cout << "Input invalid!!\n";
        }
        system("pause");
        system("cls");

    }while(option !=0 );
}

int main()
{
    menu();
   return 0;
}
