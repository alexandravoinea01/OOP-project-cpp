//Etapa 1
//  Am ales sa implementez un salon cosmetic si mi-am construit 4 clase: Angajat, Client, Programare si Procedura.
//  Am comentat toate testele din int main() pentru a nu se face confuzii in urmatorul fel:
      /*    tot ce tine de clasa Angajat   */
      /*    tot ce tine de clasa Client   */
      /*    tot ce tine de clasa Programare   */
      /*    tot ce tine de clasa Procedura   */
//  Testele din int main() sunt pentru setteri si getteri (la Angajat), pentru cin, cout si functionalitati,
//  precum si pentru toti constructorii.
//  Clasa care are toate tipurile de parametrii, toti setterii si toti getterii este clasa Angajat.


//Etapa 2
//  Am adaugat clasele Marire, Sporuri, Manichiurista si ClientFidel.
        //Marire - interfata
        //Sporuri - clasa abstracta si mosteneste Marire
        //Manichiurista - mosteneste Angajat
        //ClientFidel - mosteneste Client
//  Angajat mosteneste Sporuri, deci ierarhia este:
//      Marire -> Sporuri -> Angajat -> Manichiurista
//  Functia virtuala pura calculeazaMarire() din Marire este suprascrisa in Angajat (pentru a pastra Sporuri clasa abstracta)

//  Am modificat clasa Programare: acum are ca atribut un obiect de tip Client (pentru ilustrarea conceptului HAS A)

//  Pentru toate aceste clase am facut constructorii, destructorul, operatorul =, operatorul de citire si de afisare,
//  cu mentiunea ca i-am virtualizat in Sporuri pentru a-i chema in Angajat, iar pe cei din Angajat ii chem in Manichiurista.
//  Pentru clasa Manichiurista am facut toti setterii si toti getterii, desi nu ii folosesc.

//  Am lasat comentarii si pe parcursul codului.


//Etapa 3
//  Am implementat list-ul in main. Am facut un list de proceduri pe care il citesc din fisierul proceduri.in si il afisez
//  in fisierul proceduri.out. Lista de proceduri nu poate fi modificata in meniul interactiv.
//  In meniul interactiv am implementat un vector de clienti, un set de programari si un map de angajati (cheie:valoare) = (codAngajat:Angajat).
//  Tot in meniul interactiv am creat un vector de string-uri asociat unor proceduri pentru care exista reducerea de 7% pentru fiecare procedura.
//  Aceste pachete promotionale se pot calcula cu ajutorul comenzii 10 din meniu.

#include <iostream>
#include <fstream>
#include <string.h>
#include <iterator>
#include <vector>
#include <map>
#include <list>
#include <set>
using namespace std;

ifstream f("proceduri.in");
ofstream g("proceduri.out");


//interfata
class Marire{
    public:
        virtual void calculeazaMarire()=0;
};

//clasa abstracta -- mosteneste metoda virtuala pura din Marire si nu o suprascrie
class Sporuri:public Marire{
protected:
    bool aLucratInWeekend;
    int nrOreLucrateInWeekend;
    int nrZileDeConcediuLuate; //se refera la zilele de concediu luate in ultima luna
                               //cu cat si-a luat mai putine zile de concediu, cu atat este marirea mai mare
public:
        //toti constructorii si destructorul
    Sporuri();
    Sporuri(bool aLucratInWeekend, int nrOreLucrateInWeekend, int nrZileDeConcediuLuate);
    Sporuri(const Sporuri& spor);
    ~Sporuri(){};

        //operatorii
    Sporuri& operator=(const Sporuri& spor);

    virtual ostream& AfisareVirtuala(ostream& out)const;
    virtual istream& CitireVirtuala (istream& in);

    friend istream& operator>> (istream& in, Sporuri& spor);
    friend ostream& operator<< (ostream& out, const Sporuri& spor);

};

    Sporuri::Sporuri(){
        this->aLucratInWeekend = 0;
        this->nrOreLucrateInWeekend = 0;
        this->nrZileDeConcediuLuate = 31; //dat fiind ca numarul de zile de concediu mai mare = marire mai mica
                                          //presupun ca angajatii pleaca de la marire = 0;
    }

    Sporuri::Sporuri(bool aLucratInWeekend, int nrOreLucrateInWeekend, int nrZileDeConcediuLuate){
        this->aLucratInWeekend = aLucratInWeekend;
        this->nrOreLucrateInWeekend = nrOreLucrateInWeekend;
        this->nrZileDeConcediuLuate = nrZileDeConcediuLuate;
    }

    Sporuri::Sporuri(const Sporuri& spor){
        this->aLucratInWeekend = spor.aLucratInWeekend;
        this->nrOreLucrateInWeekend = spor.nrOreLucrateInWeekend;
        this->nrZileDeConcediuLuate = spor.nrZileDeConcediuLuate;
    }

    Sporuri& Sporuri:: operator=(const Sporuri& spor){
        if(this!=&spor){
            this->aLucratInWeekend = spor.aLucratInWeekend;
            this->nrOreLucrateInWeekend = spor.nrOreLucrateInWeekend;
            this->nrZileDeConcediuLuate = spor.nrZileDeConcediuLuate;
        }
        return *this;
    }

    ostream& Sporuri::AfisareVirtuala (ostream& out) const{
        if(aLucratInWeekend == 1)
            out<<"Angajatul a lucrat " << nrOreLucrateInWeekend << " de ore in week-end.";
        else
            out<<"Angajatul nu a lucrat in week-end.";
        out<<"\nAngajatul si-a luat "<<nrZileDeConcediuLuate<<" zile de concediu in ultima luna.\n";
        return out;
    }

    istream& Sporuri::CitireVirtuala(istream& in){
        cout<<"Introduceti 1 daca angajatul a lucrat in week-end, si 0 altfel: ";
        in>>aLucratInWeekend;
        if (aLucratInWeekend == 1){
            cout<<"\nIntroduceti cate ore a lucrat in week-end: ";
            in>>nrOreLucrateInWeekend;
        }
        else nrOreLucrateInWeekend = 0;
        cout<<"\nIntroduceti nr. de zile de concediu luate in ultima luna: ";
        in>>nrZileDeConcediuLuate;
        cout<<endl;
        return in;
    }

    ostream& operator<<(ostream & out,const Sporuri& spor){
        return spor.AfisareVirtuala(out);
    }

    istream& operator>>(istream & in, Sporuri& spor){
        return spor.CitireVirtuala(in);
    }


class Angajat:public Sporuri{
protected:
    static int nrAngajati;
    const int codAngajat;
    int nrZileLucrate;  // in ultima luna -- dimensiunea vectorilor nrOreLucrateInUltimeleNZile si bacsisInUltimeleNZile
    bool maiMultDe5AniDeExperienta;
    char* numePrenume;
    char initialaTata;
    float rating; // nota angajatului pe baza clientilor sai (ex: 7,8/10)
    int* nrOreLucrateInUltimeleNZile;   //din ultima luna
    float* bacsisInUltimeleNZile;   //din ultima luna
    double salariu;
    int nrProceduri;    //dimensiunea vectorului proceduri
    string* proceduri; //ce proceduri poate face angajatul (ex: manichiura, tuns, vopsit, etc.)
    string specializare; //procedura pe care lucreaza de obicei (ex: vopsit)

public:

//constructori si destructor
    Angajat();
    Angajat(int nrZileLucrate, bool maiMultDe5AniDeExperienta, char* numePrenume, char initialaTata, float rating,
            int* nrOreLucrateInUltimeleNZile, float* bacsisInUltimeleNZile, double salariu, int nrProceduri,
            string* proceduri, string specializare, bool aLucratInWeekend, int nrOreLucrateInWeekend, int nrZileDeConcediuLuate);
    Angajat(char* numePrenume, bool maiMultDe5AniDeExperienta, int nrProceduri, string* proceduri, string specializare);
    Angajat(const Angajat &ang);
    ~Angajat();

//operatori
    Angajat& operator=(const Angajat& ang);

    string operator[](int index);   //il folosesc pentru stringul de proceduri
    explicit operator int();        //il folosesc pentru salariu

    const Angajat& operator++();    //pre-incrementeaza rating-ul angajatului
    const Angajat& operator++(int);  //post-incrementeaza rating-ul angajatului

    bool operator==(Angajat& ang);  //dupa nume, prenume si initiala tatalui
    bool operator< (Angajat& ang);  //dupa nr. de zile lucrate

    double operator+(double marire);    //adauga o marire la salariu si intoarce un double
    float operator-(float rating);      //scade rating-ul angajatului cu un float si intoarce un float

    virtual ostream& AfisareVirtuala(ostream& out)const;
    virtual istream& CitireVirtuala (istream& in);


//functionalitate
    void promovare (Angajat* ang, int n);

//setters si getters pt fiecare atribut
    int getNrZileLucrate();
    void setNrZileLucrate(int nrZileLucrate);
    bool getMaiMultDe5AniDeExperienta();
    void setMaiMultDe5AniDeExperienta(bool maiMultDe5AniDeExperienta);
    char* getNumePrenume();
    void setNumePrenume(char* numePrenume);
    char getInitialaTata();
    void setInitialaTata(char initialaTata);
    float getRating();
    void setRating(float rating);
    int* getNrOreLucrateInUltimeleNZile();
    void setNrOreLucrateInUltimeleNZile(int* nrOreLucrateInUltimeleNZile);
    float* getBacsisInUltimeleNZile();
    void setBacsisInUltimeleNZile(float* bacsisInUltimeleNZile);
    double getSalariu();
    void setSalariu(double salariu);
    int getNrProceduri();
    void setNrProceduri(int nrProceduri);
    string* getProceduri();
    void setProceduri(string* proceduri);
    string getSpecializare();
    void setSpecializare(string specializare);

    int getCodAngajat();
    int getNrAngajati();

//suprascrierea metodei virtuale pure
    void calculeazaMarire();
};

    int Angajat::nrAngajati = 0;

//constructori si destructor
    Angajat::Angajat():codAngajat(++nrAngajati), Sporuri(){
        this->nrZileLucrate = 0;
        this->maiMultDe5AniDeExperienta = 0;
        this->numePrenume = new char[strlen("Lipsa") + 1];
        strcpy(this->numePrenume, "Lipsa");
        this->initialaTata = '-';
        this->rating = 0;
        this->nrOreLucrateInUltimeleNZile = NULL;
        this->bacsisInUltimeleNZile = NULL;
        this->salariu = 0;
        this->nrProceduri = 0;
        this->proceduri = NULL;
        this->specializare = "Niciuna";
    }
    Angajat::Angajat(int nrZileLucrate, bool maiMultDe5AniDeExperienta, char* numePrenume, char initialaTata,
                     float rating, int* nrOreLucrateInUltimeleNZile, float* bacsisInUltimeleNZile, double salariu,
                     int nrProceduri, string* proceduri, string specializare, bool aLucratInWeekend,
                     int nrOreLucrateInWeekend, int nrZileDeConcediuLuate):codAngajat(++nrAngajati), Sporuri(aLucratInWeekend,
                     nrOreLucrateInWeekend, nrZileDeConcediuLuate){
        this->nrZileLucrate = nrZileLucrate;
        this->maiMultDe5AniDeExperienta = maiMultDe5AniDeExperienta;
        this->numePrenume = new char[strlen(numePrenume) + 1];
        strcpy(this->numePrenume, numePrenume);
        this->initialaTata = initialaTata;
        this->rating = rating;
        this->nrOreLucrateInUltimeleNZile = new int[this->nrZileLucrate];
        for (int i=0; i<this->nrZileLucrate; i++)
            this->nrOreLucrateInUltimeleNZile[i] = nrOreLucrateInUltimeleNZile[i];
        this->bacsisInUltimeleNZile = new float[this->nrZileLucrate];
        for (int i=0; i<this->nrZileLucrate; i++)
            this->bacsisInUltimeleNZile[i] = bacsisInUltimeleNZile[i];
        this->salariu = salariu;
        this->nrProceduri = nrProceduri;
        this->proceduri = new string[this->nrProceduri];
        for (int i=0; i<this->nrProceduri; i++)
            this->proceduri[i] = proceduri[i];
        this->specializare = specializare;
    }
    Angajat::Angajat(char* numePrenume, bool maiMultDe5AniDeExperienta, int nrProceduri, string* proceduri,
                     string specializare):codAngajat(++nrAngajati), Sporuri(){
        this->numePrenume = new char[strlen(numePrenume) + 1];
        strcpy(this->numePrenume, numePrenume);
        this->maiMultDe5AniDeExperienta = maiMultDe5AniDeExperienta;
        this->nrProceduri = nrProceduri;
        this->proceduri = new string[this->nrProceduri];
        for (int i=0; i<this->nrProceduri; i++)
            this->proceduri[i] = proceduri[i];
        this->specializare = specializare;
        this->nrZileLucrate = 0;
        this->initialaTata = '-';
        this->rating = 0;
        this->nrOreLucrateInUltimeleNZile = NULL;
        this->bacsisInUltimeleNZile = NULL;
        this->salariu = 0;
    }
    Angajat::Angajat(const Angajat &ang):codAngajat(ang.codAngajat), Sporuri(ang){
        this->nrZileLucrate = ang.nrZileLucrate;
        this->maiMultDe5AniDeExperienta = ang.maiMultDe5AniDeExperienta;
        this->numePrenume = new char[strlen(ang.numePrenume) + 1];
        strcpy(this->numePrenume, ang.numePrenume);
        this->initialaTata = ang.initialaTata;
        this->rating = ang.rating;
        this->nrOreLucrateInUltimeleNZile = new int[this->nrZileLucrate];
        for (int i=0; i<this->nrZileLucrate; i++)
            this->nrOreLucrateInUltimeleNZile[i] = ang.nrOreLucrateInUltimeleNZile[i];
        this->bacsisInUltimeleNZile = new float[this->nrZileLucrate];
        for (int i=0; i<this->nrZileLucrate; i++)
            this->bacsisInUltimeleNZile[i] = ang.bacsisInUltimeleNZile[i];
        this->salariu = ang.salariu;
        this->nrProceduri = ang.nrProceduri;
        this->proceduri = new string[this->nrProceduri];
        for (int i=0; i<this->nrProceduri; i++)
            this->proceduri[i] = ang.proceduri[i];
        this->specializare = ang.specializare;
    }
    Angajat::~Angajat(){
        if(this->numePrenume)
            delete[] this->numePrenume;
        if(this->nrOreLucrateInUltimeleNZile)
            delete[] this->nrOreLucrateInUltimeleNZile;
        if(this->bacsisInUltimeleNZile)
            delete[] this->bacsisInUltimeleNZile;
        if(this->proceduri)
            delete[] this->proceduri;
    }

    Angajat& Angajat::operator=(const Angajat& ang){
        if (this != &ang){
            if(this->numePrenume)
                delete[] this->numePrenume;
            if(this->nrOreLucrateInUltimeleNZile)
                delete[] this->nrOreLucrateInUltimeleNZile;
            if(this->bacsisInUltimeleNZile)
                delete[] this->bacsisInUltimeleNZile;
            if(this->proceduri)
                delete[] this->proceduri;

            Sporuri::operator=(ang);

            this->nrZileLucrate = ang.nrZileLucrate;
            this->maiMultDe5AniDeExperienta = ang.maiMultDe5AniDeExperienta;

            this->numePrenume = new char[strlen(ang.numePrenume) + 1];
            strcpy(this->numePrenume, ang.numePrenume);

            this->initialaTata = ang.initialaTata;
            this->rating = ang.rating;
            this->nrOreLucrateInUltimeleNZile = new int[this->nrZileLucrate];
            for (int i=0; i<this->nrZileLucrate; i++)
                this->nrOreLucrateInUltimeleNZile[i] = ang.nrOreLucrateInUltimeleNZile[i];

            this->bacsisInUltimeleNZile = new float[this->nrZileLucrate];
            for (int i=0; i<this->nrZileLucrate; i++)
                this->bacsisInUltimeleNZile[i] = ang.bacsisInUltimeleNZile[i];

            this->salariu = ang.salariu;
            this->nrProceduri = ang.nrProceduri;

            this->proceduri = new string[this->nrProceduri];
            for (int i=0; i<this->nrProceduri; i++)
                this->proceduri[i] = ang.proceduri[i];

            this->specializare = ang.specializare;
        }
        return *this;
    }

    string Angajat :: operator[](int index){
        if (index < this->nrProceduri && index >= 0)
            return this->proceduri[index];
        else{
            string a = "Index out of range";
            return a;
        }
    }

    Angajat::operator int(){
        return (int)this->salariu;
    }

    const Angajat& Angajat::operator++(){
        this->rating++;
        return *this;
    }

    const Angajat& Angajat::operator++(int){
        Angajat aux(*this);
        this->rating++;
        return aux;
    }

    bool Angajat::operator==(Angajat& ang){
        if(strcmp(this->numePrenume, ang.numePrenume)==0 && this->initialaTata == ang.initialaTata)
            return true;
        else
            return false;
    }

    bool Angajat::operator< (Angajat &ang){
        if (this->nrZileLucrate < ang.nrZileLucrate)
            return true;
        else
            return false;
    }

    double Angajat::operator+(double marire){
        return this->salariu + marire;
    }

    float Angajat::operator-(float rating){
        return this->rating - rating;
    }

    ostream& Angajat::AfisareVirtuala(ostream& out) const{
        out<<"Nume si prenume: "<<numePrenume<<endl;
        out<<"Initiala tatalui: "<<initialaTata<<endl;
        out<<"Cod angajat: "<<codAngajat<<endl;
        if (rating > 10)
            out<<"Are nota 10/10.\n";
        else
            out<<"Are nota "<<rating<<"/10.\n";
        if (maiMultDe5AniDeExperienta)
            out<<"Are mai mult de 5 ani de experienta in domeniu.\n";
        else
            out<<"Nu are mai mult de 5 ani de experienta in domeniu.\n";
        if (nrZileLucrate > 0){
            out<<"Angajatul a lucrat "<<nrZileLucrate<<" zile in ultima luna.\n";
            out<<"In ultimele "<<nrZileLucrate<<" zile a lucrat ";
            for(int i=0; i<nrZileLucrate; i++)
                out<<nrOreLucrateInUltimeleNZile[i]<<" ";
            out<<"ore.\n";
            out<<"In ultimele "<<nrZileLucrate<<" zile a primit ";
            for(int i=0; i<nrZileLucrate; i++)
                out<<bacsisInUltimeleNZile[i]<<" ";
            out<<"bacsis.\n";
        }
        else
            out<<"Nu a lucrat in ultimele luni.\n";
        if(salariu > 0)
            out<<"Are salariul de "<<salariu<<" lei.\n";
        Sporuri::AfisareVirtuala(out);
        if(nrProceduri > 0){
            out<<"Stie sa faca "<<nrProceduri<<" proceduri: ";
            for(int i=0; i<nrProceduri; i++)
                out<<proceduri[i]<<" ";
            out<<endl;
            out<<"Dar specializarea este "<<specializare<<".\n";
        }
        else
            out<<"Nu stie sa faca nicio procedura";
        out<<endl;
        return out;
    }

    istream& Angajat::CitireVirtuala(istream& in){
        cout<<"Apasati enter pentru a introduce un angajat. ";
        cin.get();
        cout<<"\nIntroduceti nume si prenume: \n";
        char aux[100];
        in.get(aux,99);
        if (numePrenume!=NULL)
            delete[] numePrenume;
        numePrenume = new char[strlen(aux)+1];
        strcpy(numePrenume, aux);

        cout<<"\nIntroduceti initiala tatalui: ";
        in>>initialaTata;
        cout<<"\nAre mai mult de 5 ani de experienta?\n0 - NU\n1 - DA\n";
        in>>maiMultDe5AniDeExperienta;
        cout<<"\nIntroduceti rating-ul angajatului: ";
        in>>rating;

        cout<<"\nIntroduceti nr. zile lucrate: ";
        in>>nrZileLucrate;
        if (nrOreLucrateInUltimeleNZile!=NULL)
            delete[] nrOreLucrateInUltimeleNZile;
        nrOreLucrateInUltimeleNZile = new int[nrZileLucrate];
        cout<<"\nIntroduceti nr. de ore lucrate in fiecare din cele "<<nrZileLucrate<<" zile lucrate: ";
        for (int i=0; i<nrZileLucrate; i++){
            in>>nrOreLucrateInUltimeleNZile[i];
            cout<<" ";
        }
        cout<<"\nIntroduceti bacsisul primit in fiecare din cele "<<nrZileLucrate<<" zile lucrate: ";
        if (bacsisInUltimeleNZile!=NULL)
            delete[] bacsisInUltimeleNZile;
        bacsisInUltimeleNZile = new float[nrZileLucrate];
        for (int i=0; i<nrZileLucrate; i++){
            in>>bacsisInUltimeleNZile[i];
            cout<<" ";
        }
        cout<<"\nIntroduceti salariul: ";
        in>>salariu;
        cout<<endl;
        Sporuri::CitireVirtuala(in);
        cout<<"\nIntroduceti nr. de proceduri pe care le poate face: ";
        in>>nrProceduri;
        cout<<"\nIntroduceti pe acelasi rand procedurile pe care le poate face: ";
        if (proceduri!=NULL)
            delete[] proceduri;
        proceduri = new string[nrProceduri];
        for (int i=0; i<nrProceduri; i++){
            in>>proceduri[i];
            cout<<" ";
        }
        cout<<"\nIntroduceti specializare angajatului: ";
        in>>specializare;
        cout<<endl;
        return in;
    }

//functionalitate
    void Angajat::promovare(Angajat ang[], int n){
        int* medie;
        medie = NULL;
        int sumaOre = 0;
        medie = new int[n];
        for (int i = 0; i < n; i++){
            sumaOre = 0;
            if (ang[i].nrOreLucrateInUltimeleNZile != NULL && ang[i].nrZileLucrate != 0){
                for (int j = 0; j < ang[i].nrZileLucrate; j++)
                    sumaOre += ang[i].nrOreLucrateInUltimeleNZile[j];
                medie[i] = sumaOre / ang[i].nrZileLucrate;
            }
            else{
                medie[i] = 0;
            }
        }
        char* numeP;
        numeP = NULL;
        int maxMedie = 0;
        for (int i=0; i<n; i++){
            if (medie[i] > maxMedie){
                maxMedie = medie[i];
                if (numeP != NULL){
                    delete[] numeP;

                }
                numeP = new char[strlen(ang[i].numePrenume) + 1];
                strcpy(numeP, ang[i].numePrenume);
            }
        }
        if (numeP != NULL)
            cout<<"Va fi promovat angajatul "<<numeP<<", avand o medie de "<<maxMedie<<" ore/zi lucrate in ultima luna.";
        else{
            cout<<"Exista un angajat care nu a lucrat deloc";
        }
        delete[] medie;
        delete[] numeP;
    }

//setters si getters

    int Angajat::getNrZileLucrate(){
        return this->nrZileLucrate;
    }
    void Angajat::setNrZileLucrate(int nrZileLucrate){
        this->nrZileLucrate = nrZileLucrate;
    }

    bool Angajat::getMaiMultDe5AniDeExperienta(){
        return this->maiMultDe5AniDeExperienta;
    }
    void Angajat::setMaiMultDe5AniDeExperienta(bool maiMultDe5AniDeExperienta){
        this->maiMultDe5AniDeExperienta = maiMultDe5AniDeExperienta;
    }

    char* Angajat::getNumePrenume(){
        return this->numePrenume;
    }
    void Angajat::setNumePrenume(char* numePrenume){
        if (this->numePrenume != NULL)
            delete[] this->numePrenume;
        this->numePrenume = new char[strlen(numePrenume)+1];
        strcpy(this->numePrenume, numePrenume);
    }

    char Angajat::getInitialaTata(){
        return this->initialaTata;
    }
    void Angajat::setInitialaTata(char initialaTata){
        this->initialaTata = initialaTata;
    }

    float Angajat::getRating(){
        if (this->rating <= 10)
            return this->rating;
        else return 10;
    }
    void Angajat::setRating(float rating){
        if (rating <= 10)
            this->rating = rating;
        else this->rating = 10;
    }

    int* Angajat::getNrOreLucrateInUltimeleNZile(){
        return this->nrOreLucrateInUltimeleNZile;
    }
    void Angajat::setNrOreLucrateInUltimeleNZile(int* nrOreLucrateInUltimeleNZile){
        if (this->nrOreLucrateInUltimeleNZile != NULL)
            delete[] this->nrOreLucrateInUltimeleNZile;
        this->nrOreLucrateInUltimeleNZile = new int[this->nrZileLucrate];
        for (int i=0; i<this->nrZileLucrate; i++)
            this->nrOreLucrateInUltimeleNZile[i] = nrOreLucrateInUltimeleNZile[i];
    }

    float* Angajat::getBacsisInUltimeleNZile(){
        return this->bacsisInUltimeleNZile;
    }
    void Angajat::setBacsisInUltimeleNZile(float* bacsisInUltimeleNZile){
        if (this->bacsisInUltimeleNZile != NULL)
            delete[] this->bacsisInUltimeleNZile;
        this->bacsisInUltimeleNZile = new float[this->nrZileLucrate];
        for (int i=0; i<this->nrZileLucrate; i++){
            this->bacsisInUltimeleNZile[i] = bacsisInUltimeleNZile[i];
        }
    }

    double Angajat::getSalariu(){
        return this->salariu;
    }
    void Angajat::setSalariu(double salariu){
        this->salariu = salariu;
    }

    int Angajat::getNrProceduri(){
        return this->nrProceduri;
    }
    void Angajat::setNrProceduri(int nrProceduri){
        this->nrProceduri = nrProceduri;
    }

    string* Angajat::getProceduri(){
        return this->proceduri;
    }
    void Angajat::setProceduri(string* proceduri){
        if (this->proceduri != NULL)
            delete[] this->proceduri;
        this->proceduri = new string[this->nrProceduri];
        for (int i=0; i<this->nrProceduri; i++)
            this->proceduri[i] = proceduri[i];
    }

    string Angajat::getSpecializare(){
        return this->specializare;
    }
    void Angajat::setSpecializare(string specializare){
        this->specializare = specializare;
    }

    int Angajat::getCodAngajat(){
        return this->codAngajat;
    }

    int Angajat::getNrAngajati(){
        return this->nrAngajati;
    }

    void Angajat::calculeazaMarire(){
        double marire = 0;
        if (this->aLucratInWeekend){
            marire = marire + 0.02 * this->salariu;
            marire += this->salariu * this->nrOreLucrateInWeekend / 200;
        }
        if (this->nrZileDeConcediuLuate <= 5)
            marire += 0.03 * this->salariu;
        else if (this->nrZileDeConcediuLuate >= 15)
            marire = 0;

        if(marire==0)
            cout<<"Angajatul n-a primit nicio marire.\n";
        else
            cout<<"Angajatul a primit marirea de "<<marire<<" lei, ceea ce i-a marit salariul la "<< this->salariu + marire <<" lei.";
    }

class Manichiurista:public Angajat{
    private:
        int nrCuloriDisponibile;
        string* culoriDisponibile;
    public:
        Manichiurista();
        Manichiurista(int nrZileLucrate, bool maiMultDe5AniDeExperienta, char* numePrenume, char initialaTata, float rating,
                      int* nrOreLucrateInUltimeleNZile, float* bacsisInUltimeleNZile, double salariu, int nrProceduri,
                      string* proceduri, string specializare, int nrCuloriDisponibile, string* culoriDisponibile, bool aLucratInWeekend,
                      int nrOreLucrateInWeekend, int nrZileDeConcediuLuate);

        Manichiurista(const Manichiurista &man);
        ~Manichiurista();

        Manichiurista& operator=(const Manichiurista &man);

        virtual ostream& AfisareVirtuala(ostream& out)const;
        virtual istream& CitireVirtuala (istream& in);

        int getNrCuloriDisponibile();
        void setNrCuloriDisponibile(int nrCuloriDisponibile);
        string* getCuloriDisponibile();
        void setCuloriDisponibile(string* culoriDisponibile);
};

    Manichiurista::Manichiurista():Angajat(){
        this->nrCuloriDisponibile = 0;
        this->culoriDisponibile = NULL;
    }

    Manichiurista::Manichiurista(int nrZileLucrate, bool maiMultDe5AniDeExperienta, char* numePrenume, char initialaTata, float rating,
                      int* nrOreLucrateInUltimeleNZile, float* bacsisInUltimeleNZile, double salariu, int nrProceduri,
                      string* proceduri, string specializare, int nrCuloriDisponibile, string* culoriDisponibile, bool aLucratInWeekend,
                      int nrOreLucrateInWeekend, int nrZileDeConcediuLuate) : Angajat(nrZileLucrate,
                      maiMultDe5AniDeExperienta, numePrenume, initialaTata, rating,
                      nrOreLucrateInUltimeleNZile, bacsisInUltimeleNZile, salariu, nrProceduri,
                      proceduri, specializare, aLucratInWeekend, nrOreLucrateInWeekend, nrZileDeConcediuLuate){
        this->nrCuloriDisponibile = nrCuloriDisponibile;
        this->culoriDisponibile = new string[this->nrCuloriDisponibile];
        for(int i=0; i<this->nrCuloriDisponibile; i++)
            this->culoriDisponibile[i] = culoriDisponibile[i];
    }


    Manichiurista::Manichiurista(const Manichiurista &man):Angajat(man){
        this->nrCuloriDisponibile = man.nrCuloriDisponibile;
        this->culoriDisponibile = new string[this->nrCuloriDisponibile];
        for(int i=0; i<this->nrCuloriDisponibile; i++)
            this->culoriDisponibile[i] = man.culoriDisponibile[i];
    }

    Manichiurista::~Manichiurista(){
        if(this->culoriDisponibile != NULL)
            delete[] this->culoriDisponibile;
    }

    Manichiurista& Manichiurista::operator=(const Manichiurista& man){
        if(this!=&man){
            if(this->culoriDisponibile!=NULL)
                delete[] this->culoriDisponibile;
            this->nrCuloriDisponibile = man.nrCuloriDisponibile;
            this->culoriDisponibile = new string[this->nrCuloriDisponibile];
            for(int i=0;i<this->nrCuloriDisponibile; i++)
                this->culoriDisponibile[i] = man.culoriDisponibile[i];
            Angajat::operator=(man);
        }
        return *this;
    }

    ostream& Manichiurista::AfisareVirtuala (ostream& out) const{
        Angajat::AfisareVirtuala(out);
        out<<"\nNr. de culori disponibile pentru oja: "<< nrCuloriDisponibile<<".\n";
        out<<"Culori disponibile: ";
        if (culoriDisponibile!=NULL)
            for(int i=0; i<nrCuloriDisponibile; i++){
                out<<culoriDisponibile[i]<<" ";
            }
        else
            out<<"-";
        out<<endl;
        return out;
    }

    istream& Manichiurista::CitireVirtuala(istream& in){
        Angajat::CitireVirtuala(in);
        cout<<"Introduceti nr. culori disponibile: ";
        in>>nrCuloriDisponibile;
        cout<<"Introduceti culorile disponibile: ";
        if(culoriDisponibile!=NULL)
            delete[] culoriDisponibile;
        culoriDisponibile = new string[nrCuloriDisponibile];
        for(int i=0; i<nrCuloriDisponibile; i++){
            in>>culoriDisponibile[i];
        }
        return in;
    }

    int Manichiurista::getNrCuloriDisponibile(){
        return this->nrCuloriDisponibile;
    }
    void Manichiurista::setNrCuloriDisponibile(int nrCuloriDisponibile){
        this->nrCuloriDisponibile = nrCuloriDisponibile;
    }

    string* Manichiurista::getCuloriDisponibile(){
        return this->culoriDisponibile;
    }
    void Manichiurista::setCuloriDisponibile(string* culoriDisponibile){
        if (this->culoriDisponibile != NULL)
            delete[] this->culoriDisponibile;
        this->culoriDisponibile = new string[this->nrCuloriDisponibile];
        for (int i=0; i<this->nrCuloriDisponibile; i++)
            this->culoriDisponibile[i] = culoriDisponibile[i];
    }


class Client{
protected:
    char* nume;
    string prenume;
    bool aMaiFostLaAcestSalon;
    int varsta;
    char sex; //B - barbat, F - femeie
    char* adresaEmail;
public:
//constructori si destructor
    Client();
    Client(char* nume, string prenume, bool aMaiFostLaAcestSalon, int varsta, char sex, char* adresaEmail);
    Client(char* nume, string prenume);
    Client(const Client &cli);
    ~Client();

    Client& operator=(const Client& cli);
    const Client& operator++();     //pre-incrementeaza varsta si intoarce tot obiectul
    const Client operator++(int);   //post-incrementeaza varsta si intoarce tot obiectul
    bool operator==(Client& cli);   //dupa adresa de email
    bool operator< (Client& cli);   //dupa varsta

    friend ostream& operator<<(ostream& out, const Client &c);
    friend istream& operator>>(istream& in, Client &c);

//functionalitate
    void acordParinte();
};

//constructori si destructor
    Client::Client(){
        this->nume = NULL;
        this->prenume = "Lipsa";
        this->aMaiFostLaAcestSalon = 0;
        this->varsta = -1;
        this->sex = '-';
        this->adresaEmail = NULL;
    }
    Client::Client(char* nume, string prenume, bool aMaiFostLaAcestSalon, int varsta, char sex, char* adresaEmail){
        this->nume = new char[strlen(nume)+1];
        strcpy(this->nume, nume);
        this->prenume = prenume;
        this->aMaiFostLaAcestSalon = aMaiFostLaAcestSalon;
        this->varsta = varsta;
        this->sex = sex;
        this->adresaEmail = new char[strlen(adresaEmail)+1];
        strcpy(this->adresaEmail, adresaEmail);
    }
    Client::Client(char* nume, string prenume){
        this->nume = new char[strlen(nume)+1];
        strcpy(this->nume, nume);
        this->prenume = prenume;
        this->aMaiFostLaAcestSalon = 0;
        this->varsta = -1;
        this->sex = '-';
        this->adresaEmail = NULL;
    }

    Client::Client(const Client &cli){
        if(cli.nume == NULL){
            this->nume = NULL;
        }
        else{
            this->nume = new char[strlen(cli.nume)+1];
            strcpy(this->nume, cli.nume);
        }
        this->prenume = cli.prenume;
        this->aMaiFostLaAcestSalon = cli.aMaiFostLaAcestSalon;
        this->varsta = cli.varsta;
        this->sex = cli.sex;
        if(cli.adresaEmail == NULL){
            this->adresaEmail = NULL;
        }
        else{
            this->adresaEmail = new char[strlen(cli.nume)+1];
            strcpy(this->adresaEmail, cli.adresaEmail);
        }
    }
    Client::~Client(){
        if (this->nume)
            delete[] this->nume;
        if (this->adresaEmail)
            delete[] this->adresaEmail;
    }

//operatori
    Client& Client::operator=(const Client& cli){
        if (this != &cli){
            if (this->nume != NULL){
                delete[] this->nume;
                this->nume = NULL;
            }
            if (this->adresaEmail != NULL){
                delete[] this->adresaEmail;
                this->adresaEmail = NULL;
            }
            if (cli.nume != NULL){
                this->nume = new char[strlen(cli.nume)+1];
                strcpy(this->nume, cli.nume);
            }
            this->prenume = cli.prenume;
            this->aMaiFostLaAcestSalon = cli.aMaiFostLaAcestSalon;
            this->varsta = cli.varsta;
            this->sex = cli.sex;
            if (cli.adresaEmail != NULL){
                this->adresaEmail = new char[strlen(cli.adresaEmail)+1];
                strcpy(this->adresaEmail, cli.adresaEmail);
            }
        }
        return *this;
    }

    const Client& Client::operator++(){
        this->varsta++;
        return *this;
    }

    const Client Client::operator++(int){
        Client aux(*this);
        this->varsta++;
        return aux;
    }

    bool Client::operator==(Client& cli){
        if (strcmp(this->adresaEmail, cli.adresaEmail)==0)
            return true;
        else
            return false;
    }

    bool Client::operator< (Client& cli){
        if(this->varsta < cli.varsta)
            return true;
        else
            return false;
    }

    ostream& operator<<(ostream& out, const Client& c){
        if (c.nume == NULL)
            out<<"Nume: "<<'-';
        else
            out<<"Nume: "<<c.nume;
        out<<"\nPrenume: "<<c.prenume;
        if (c.aMaiFostLaAcestSalon)
            out<<"\nA mai fost la acest salon.\n";
        else
            out<<"\nNu a mai fost la acest salon.\n";
        out<<"Varsta: "<<c.varsta;
        out<<"\nSex: ";
        if (c.sex == 'F')
            out<<"Femeie";
        else out<<"Barbat";
        if (c.adresaEmail == NULL)
            out<<"\nAdresa de email: "<<'-';
        else
            out<<"\nAdresa de email: "<<c.adresaEmail;
        cout<<endl;
        return out;
    }

    istream& operator>>(istream& in, Client& c){
        cout<<"Introduceti numele clientului: ";
        char aux[100];
        in>>aux;
        if(c.nume!=NULL)
            delete[] c.nume;
        c.nume = new char[strlen(aux)+1];
        strcpy(c.nume, aux);
        cout<<"\nIntroduceti prenumele clientului: ";
        in>>c.prenume;
        cout<<"\nAti mai fost la acest salon?\n0 - NU\n1 - DA\n";
        in>>c.aMaiFostLaAcestSalon;
        cout<<"\nIntroduceti sexul (B - barbat, F - femeie): ";
        in>>c.sex;
        cout<<"\nIntroduceti varsta: ";
        in>>c.varsta;
        cout<<"\nIntroduceti adresa de email: ";
        char aux2[100];
        in>>aux2;
        if (c.adresaEmail != NULL)
            delete[] c.adresaEmail;
        c.adresaEmail = new char[strlen(aux2)+1];
        strcpy(c.adresaEmail, aux2);
        return in;
    }

//functionalitate
    void Client::acordParinte(){
        if (this->varsta >= 18)
            cout<<"\nOK\n";
        else{
            cout<<"\nAveti nevoie de acordul unui parinte. \nEste necesar sa-l avem pe parinte in baza noastra de date.\n";
            Client parinte;
            cin>>parinte;
            if (strcmp(this->nume, parinte.nume) != 0)
                cout<<"\nNe pare rau, numele de familie nu coincide. Operatiune esuata.\n";
            else
                cout<<"\nOperatiune reusita.\n";
        }
    }

class ClientFidel:public Client{
private:
    int nrAni; //de cati ani vine la salonul nostru
    int reducere; //reducere de fidelitate 5% - cel putin 2 ani
                  //                      10% - pentru mai mult de 5 ani
public:
    //toti constructorii + destructor
    ClientFidel();
    ClientFidel(char* nume, string prenume, bool aMaiFostLaAcestSalon, int varsta, char sex, char* adresaEmail, int nrAni);
    ClientFidel(char* nume, string prenume, int nrAni);
    ClientFidel(const ClientFidel &clif);
    ~ClientFidel(){};

    //operatori redefiniti
    ClientFidel& operator=(const ClientFidel& cli);

    friend ostream& operator<<(ostream& out, const ClientFidel &c);
    friend istream& operator>>(istream& in, ClientFidel &c);
};

    ClientFidel::ClientFidel():Client(){
        this->nrAni = 0;
        this->reducere = 0;
    }

    ClientFidel::ClientFidel(char* nume, string prenume, bool aMaiFostLaAcestSalon, int varsta, char sex, char* adresaEmail,
                             int nrAni): Client(nume, prenume, aMaiFostLaAcestSalon, varsta, sex, adresaEmail){
        this->nrAni = nrAni;
        if (this->nrAni >= 2 && this->nrAni < 5)
            this->reducere = 5;
        else if (this->nrAni >= 5)
            this->reducere = 10;
        else
            this->reducere = 0;

        //nu primesc reducere ca parametru in constructori niciodata pentru ca il setez automat in functie de this->nrAni
    }

    ClientFidel::ClientFidel(char* nume, string prenume, int nrAni):Client(nume, prenume){
        this->nrAni = nrAni;
        if (this->nrAni >= 2 && this->nrAni < 5)
            this->reducere = 5;
        else if (this->nrAni >= 5)
            this->reducere = 10;
        else
            this->reducere = 0;
    }

    ClientFidel::ClientFidel(const ClientFidel &cli):Client(cli){
        this->nrAni = cli.nrAni;
        this->reducere = cli.reducere;
    }

    ClientFidel& ClientFidel::operator=(const ClientFidel& cli){
        if(this!=&cli){
            Client::operator= (cli);
            this->nrAni = cli.nrAni;
            this->reducere = cli.reducere;
        }
        return *this;
    }

    ostream& operator<<(ostream& out, const ClientFidel &cli){
        out<<(Client&)cli;
        if(cli.nrAni >= 2){
            out<<"\nSunteti clientul nostru de "<<cli.nrAni<<" ani";
            out<<" si vi se aplica o reducere de "<<cli.reducere<<"% la orice serviciu ales.\n";
        }
        else{
            out<<"\nNu vi se aplica nicio reducere.\nReducerea se aplica la clientii de peste 2 ani.\n";
        }
        return out;
    }

    istream& operator>>(istream& in, ClientFidel &cli){
        in>>(Client&)cli;
        if (cli.aMaiFostLaAcestSalon == 1){
            cout<<"\nIntroduceti numarul de ani de cand frecventati salonul nostru: ";
            in>>cli.nrAni;
            if (cli.nrAni >= 2 && cli.nrAni < 5)
                cli.reducere = 5;
            else if (cli.nrAni >= 5)
                cli.reducere = 10;
            else
                cli.reducere = 0;
            cout<<"\nVi se aplica o reducere de "<<cli.reducere<<"% la orice serviciu ales.\n";
        }
        return in;
    }

class Programare{
private:
    Client cli;
    int zi;
    int luna;
    int nrProceduriDorite;
    string* proceduriDorite;
    char* ora;

public:
//constructori si destructor
    Programare();
    Programare(int zi, int luna, int nrProceduriDorite, string* proceduriDorite, char* ora, Client &cli);
    Programare(int zi, int luna, char* ora, Client &cli);
    Programare(const Programare &prog);
    ~Programare();


//operatori
    Programare& operator=(const Programare& prog);

    bool operator==(Programare& prog);  //dupa zi si luna
    bool operator< (const Programare& prog) const;  //dupa zi

    int operator+(int x);           //aduna x la nrProceduriDorite
    Programare& operator-(int x);   //taie ultimele x proceduriDorite din vector

    friend ostream& operator<<(ostream& out, const Programare& p);
    friend istream& operator>>(istream& in, Programare& p);


//functionalitate
    bool esteLiber (Programare* programariDejaFacute, int nrProgramariDejaFacute);

};

//constructori si destructor
    Programare::Programare(){
        this->zi = 0;
        this->luna = 0;
        this->nrProceduriDorite = 0;
        this->proceduriDorite = NULL;
        this->ora = NULL;
    }
    Programare::Programare(int zi, int luna, int nrProceduriDorite, string* proceduriDorite, char* ora, Client &cli){
        this->cli = cli;
        this->zi = zi;
        this->luna = luna;
        this->nrProceduriDorite = nrProceduriDorite;
        this->proceduriDorite = new string[this->nrProceduriDorite];
        for(int i=0; i<this->nrProceduriDorite; i++)
            this->proceduriDorite[i] = proceduriDorite[i];
        this->ora = new char[strlen(ora)+1];
        strcpy(this->ora, ora);
    }
    Programare::Programare(int zi, int luna, char* ora, Client &cli){
        this->cli = cli;
        this->zi = zi;
        this->luna = luna;
        this->ora = new char[strlen(ora)+1];
        strcpy(this->ora, ora);

        this->nrProceduriDorite = 0;
        this->proceduriDorite = NULL;
    }
    Programare::Programare(const Programare &prog){
        this->cli = prog.cli;
        this->zi = prog.zi;
        this->luna = prog.luna;
        this->nrProceduriDorite = prog.nrProceduriDorite;
        this->proceduriDorite = new string[this->nrProceduriDorite];
        for(int i=0; i<this->nrProceduriDorite; i++)
            this->proceduriDorite[i] = prog.proceduriDorite[i];
        this->ora = new char[strlen(prog.ora)+1];
        strcpy(this->ora, prog.ora);
    }
    Programare::~Programare(){
        if (this->proceduriDorite)
            delete[] this->proceduriDorite;
        if (this->ora)
            delete[] this->ora;
    }

    Programare& Programare::operator=(const Programare& prog){
        if (this!=&prog){
            if (this->proceduriDorite)
                delete[] this->proceduriDorite;
            if (this->ora)
                delete[] this->ora;
            this->cli = prog.cli;
            this->zi = prog.zi;
            this->luna = prog.luna;
            this->nrProceduriDorite = prog.nrProceduriDorite;
            this->proceduriDorite = new string[this->nrProceduriDorite];
            for(int i=0; i<this->nrProceduriDorite; i++)
                this->proceduriDorite[i] = prog.proceduriDorite[i];
            this->ora = new char[strlen(prog.ora)+1];
            strcpy(this->ora, prog.ora);
        }
        return *this;
    }

    bool Programare::operator==(Programare& prog){
        if(this->zi == prog.zi && this->luna == prog.luna && strcmp(this->ora, prog.ora)==0)
            return true;
        else
            return false;
    }

    bool Programare::operator<(const Programare& prog) const{
        if(this->luna < prog.luna)
                return true;
        else if (this->luna > prog.luna)
            return false;
        else{
            if(this->zi < prog.zi)
                return true;
            else if (this->zi > prog.zi)
                return false;
            else{
                if(strcmp(this->ora, prog.ora) < 0)
                    return true;
                else return false;
            }
        }
    }

    int Programare::operator+(int x){
        return this->nrProceduriDorite + x;
    }

    Programare& Programare::operator-(int x){
        Programare *p = new Programare(*this);
        this->nrProceduriDorite -= x;
        p->nrProceduriDorite = this->nrProceduriDorite;
        p->proceduriDorite = new string[this->nrProceduriDorite];
        for(int i=0; i<this->nrProceduriDorite; i++)
            p->proceduriDorite[i] = this->proceduriDorite[i];
        return *p;
    }

    ostream& operator<<(ostream& out, const Programare& p){
        out<<p.cli;
        out<<"Zi: "<<p.zi;
        out<<"\nLuna: "<< p.luna;
        out<<"\nNr. proceduri: "<<p.nrProceduriDorite;
        out<<"\nProceduri dorite: ";
        if (p.proceduriDorite == NULL)
            out<<"-";
        else
            for (int i=0;i<p.nrProceduriDorite;i++)
                out<<p.proceduriDorite[i]<<" ";
        if (p.ora == NULL)
            out<<"\nOra: "<<'-';
        else
            out<<"\nOra: "<<p.ora;
        out<<endl;
        return out;
    }

    istream& operator>>(istream& in, Programare& p){
        in>>p.cli;
        cout<<"Introduceti ziua: ";
        in>>p.zi;
        cout<<"\nIntroduceti luna (numar): ";
        in>>p.luna;
        cout<<"\nIntroduceti nr. de proceduri dorite: ";
        in>>p.nrProceduriDorite;

        cout<<"\nIntroduceti procedurile dorite: ";

        if (p.proceduriDorite!=NULL)
            delete[] p.proceduriDorite;
        p.proceduriDorite = new string[p.nrProceduriDorite];
        for (int i=0; i<p.nrProceduriDorite; i++){
            in>>p.proceduriDorite[i];
            cout<<" ";
        }
        cout<<"\nIntroduceti ora (hh:mm, ex: 06:00): ";
        char aux2[100];
        in>>aux2;
        if(p.ora!=NULL)
            delete[] p.ora;
        p.ora = new char[strlen(aux2)+1];
        strcpy(p.ora, aux2);
        return in;
    }

//functionalitate
    bool Programare::esteLiber(Programare* programariDejaFacute, int nrProgramariDejaFacute){

        int ora, minut;
        if (this->ora == NULL){
            cout<<"\nNu ati cerut sa verificati disponibilitatea.\n";
            return false;
        }
        ora = (this->ora[0] - '0') * 10 + (this->ora[1] - '0');
        minut = (this->ora[3] - '0') * 10 + (this->ora[4] - '0');
        if (ora > 19) return false;
        if (ora == 19 && minut > 0) return false;
        if (ora < 8) return false;

        if (programariDejaFacute == NULL){
            return true;
        }
        else{
            int ok = 0;     //presupun ca e ocupat, totodata presupun ca orice procedura dureaza 1 ora,
                            //dar si ca toti clientii vor sa-si faca procedurile una dupa alta:
                            //ex: daca vrea clientul manichiura si pedichiura de la 12:30,
                            //angajatul va fi ocupat de la 12:30 la 14:30
            int ora_i, minut_i;

            while(ok == 0){
                ok = 1;     //presupun ca e liber
                for (int i=0; i<nrProgramariDejaFacute; i++){

                    ora_i = (programariDejaFacute[i].ora[0] - '0') * 10 + (programariDejaFacute[i].ora[1] - '0');
                    minut_i = (programariDejaFacute[i].ora[3] - '0') * 10 + (programariDejaFacute[i].ora[4] - '0');
                    if (programariDejaFacute[i].zi == this->zi && programariDejaFacute[i].luna== this->luna &&
                        ora_i + programariDejaFacute[i].nrProceduriDorite >= ora){

                        if (minut < minut_i)
                            return false;
                        if (ora_i > ora + this->nrProceduriDorite)
                            return true;
                        if (ora == ora_i)
                            return false;
                    }
                }
            }

        }
        return true;
    }

class Procedura{
private:
    char* nume;
    float pret;
    int nrCulori; //daca procedura presupune culori (ex: vopsit) nrCulori >= 1 si reprezinta nr culorilor de pe stoc,
                  // si daca nu (ex: tuns), nrCulori=0
    string* culoriPosibile; //in caz ca presupune, exista o lista limitata de culori
public:
//consructori si destructor
    Procedura();
    Procedura(char* nume, float pret, int nrCulori, string* culoriPosibile);
    Procedura(char* nume, float pret);
    Procedura(const Procedura &proc);
    ~Procedura();

//operatori
    Procedura& operator=(const Procedura& proc);
    const Procedura& operator--();      //pre-decrementarea (?) pretului
    const Procedura operator--(int);    //post-decrementarea (?) pretului
    bool operator==(Procedura& proc);   //dupa nume si pret
    bool operator< (Procedura& proc);   //dupa pret
    Procedura& operator+(Procedura proc);      //concateneaza doua proceduri si ofera reducere la pretul total
    float operator-(float reducere);           //scade pretul procedurii cu reducere si intoarce un float

    friend ostream& operator<<(ostream& out, const Procedura& pr);
    friend istream& operator>>(istream& in, Procedura& pr);

    friend ofstream& operator<<(ofstream& out, const Procedura& pr);
    friend ifstream& operator>>(ifstream& in, Procedura& pr);

//functionalitate
    void adaugaCulori (int nrCuloriAdaugate, string* culoriAdaugate); //aceasta functie adauga culori la vectorul de
                                                                         //culori posibile, marindu-i dimensiunea

//getteri pentru vectorul culori posibile si pentru nrCulori posibile (dimensiunea vectorului)
    string* getCuloriPosibile();
    int getNrCuloriPosibile();
};

//consructori si destructor
    Procedura::Procedura(){
        this->nume = NULL;
        this->pret = 0;
        this->nrCulori = 0;
        this->culoriPosibile = NULL;
    }
    Procedura::Procedura(char* nume, float pret, int nrCulori, string* culoriPosibile){
        this->nume = new char[strlen(nume)+1];
        strcpy(this->nume, nume);
        this->pret = pret;
        this->nrCulori = nrCulori;
        this->culoriPosibile = new string[this->nrCulori];
        for (int i=0; i<this->nrCulori; i++)
            this->culoriPosibile[i] = culoriPosibile[i];
    }
    Procedura::Procedura(char* nume, float pret){
        this->nume = new char[strlen(nume)+1];
        strcpy(this->nume, nume);
        this->pret = pret;
        this->nrCulori = 0;
        this->culoriPosibile = NULL;
    }
    Procedura::Procedura(const Procedura &proc){
        this->nume = new char[strlen(proc.nume)+1];
        strcpy(this->nume, proc.nume);
        this->pret = proc.pret;
        this->nrCulori = proc.nrCulori;
        this->culoriPosibile = new string[this->nrCulori];
        for (int i=0; i<this->nrCulori; i++)
            this->culoriPosibile[i] = proc.culoriPosibile[i];
    }
    Procedura::~Procedura(){
        if (this->nume)
            delete[] this->nume;
        if (this->culoriPosibile)
            delete[] this->culoriPosibile;
    }
    Procedura& Procedura::operator=(const Procedura& proc){
        if (this!=&proc){
            if (this->nume)
                delete[] this->nume;
            if (this->culoriPosibile)
                delete[] this->culoriPosibile;
            this->nume = new char[strlen(proc.nume)+1];
            strcpy(this->nume, proc.nume);
            this->pret = proc.pret;
            this->nrCulori = proc.nrCulori;
            this->culoriPosibile = new string[this->nrCulori];
            for (int i=0; i<this->nrCulori; i++)
                this->culoriPosibile[i] = proc.culoriPosibile[i];
        }
        return *this;
    }

    const Procedura& Procedura::operator--(){
        this->pret--;
        return *this;
    }

    const Procedura Procedura::operator--(int){
        Procedura aux(*this);
        this->pret--;
        return aux;
    }

    bool Procedura::operator==(Procedura& proc){
        if(strcmp(this->nume, proc.nume)==0 && this->pret == proc.pret)
            return true;
        else
            return false;
    }

    bool Procedura::operator<(Procedura& proc){
        if (this->pret < proc.pret)
            return true;
        else
            return false;
    }

    Procedura& Procedura::operator+(Procedura proc){
        Procedura *p = new Procedura(*this);
        p->nume = strcat(p->nume, " + ");
        p->nume = strcat(p->nume, proc.nume);
        p->pret = p->pret + proc.pret - 0.1*(p->pret + proc.pret);
        p->nrCulori = p->nrCulori + proc.nrCulori;
        if (p->culoriPosibile != NULL)
            delete[] p->culoriPosibile;
        p->culoriPosibile = new string[p->nrCulori];
        for(int i=0; i<this->nrCulori; i++)
            p->culoriPosibile[i] = this->culoriPosibile[i];
        for(int i=this->nrCulori; i<p->nrCulori; i++)
            p->culoriPosibile[i] = proc.culoriPosibile[i - this->nrCulori];
        return *p;
    }

    float Procedura::operator-(float reducere){
        return this->pret - reducere;
    }

    ostream& operator<<(ostream& out, const Procedura& pr){
        out<<endl;
        if (pr.nume == NULL)
            out<<"Nume: "<<'-';
        else
            out<<"Nume: "<<pr.nume;
        out<<"\nPret: "<<pr.pret;
        if (pr.nrCulori != 0){
            out<<"\nNr. culori: "<<pr.nrCulori;
            out<<"\nCulori posibile: ";
            for (int i=0;i<pr.nrCulori;i++)
                out<<pr.culoriPosibile[i]<<" ";
            out<<endl;
        }
        else
            out<<"\nNu sunt necesare culori pentru aceasta procedura.\n";
        return out;
    }

    istream& operator>>(istream& in, Procedura& pr){
        cout<<"\nIntroduceti numele procedurii: ";
        char aux[100];
        in>>aux;
        if(pr.nume!=NULL)
            delete[] pr.nume;
        pr.nume = new char[strlen(aux)+1];
        strcpy(pr.nume, aux);
        cout<<"\nIntroduceti pretul procedurii: ";
        in>>pr.pret;
        cout<<"\nIntroduceti nr. culori posibile pentru procedura: ";
        in>>pr.nrCulori;
        if(pr.nrCulori==0)
            delete[] pr.culoriPosibile;
        else{
            cout<<"\nIntroduceti culorile posibile: ";
            if(pr.culoriPosibile!=NULL)
                delete[] pr.culoriPosibile;
            pr.culoriPosibile = new string[pr.nrCulori];
            for (int i=0; i<pr.nrCulori; i++){
                in>>pr.culoriPosibile[i];
                cout<<" ";
            }
        }
        return in;
    }

    ofstream& operator<<(ofstream& out, const Procedura& pr){
        out<<endl;
        if (pr.nume == NULL)
            out<<"Nume: "<<'-';
        else
            out<<"Nume: "<<pr.nume;
        out<<"\nPret: "<<pr.pret;
        if (pr.nrCulori != 0){
            out<<"\nNr. culori: "<<pr.nrCulori;
            out<<"\nCulori posibile: ";
            for (int i=0;i<pr.nrCulori;i++)
                out<<pr.culoriPosibile[i]<<" ";
            out<<endl;
        }
        else
            out<<"\nNu sunt necesare culori pentru aceasta procedura.\n";
        return out;
    }

    ifstream& operator>>(ifstream& in, Procedura& pr){
        char aux[100];
        in>>aux;
        if(pr.nume!=NULL)
            delete[] pr.nume;
        pr.nume = new char[strlen(aux)+1];
        strcpy(pr.nume, aux);
        in>>pr.pret;
        in>>pr.nrCulori;
        if(pr.nrCulori==0)
            delete[] pr.culoriPosibile;
        else{
            if(pr.culoriPosibile!=NULL)
                delete[] pr.culoriPosibile;
            pr.culoriPosibile = new string[pr.nrCulori];
            for (int i=0; i<pr.nrCulori; i++){
                in>>pr.culoriPosibile[i];
                cout<<" ";
            }
        }
        return in;
    }

    void Procedura::adaugaCulori(int nrCuloriAdaugate, string* culoriAdaugate){
        string* aux;
        int dimAux;
        if(this->culoriPosibile != NULL){
            dimAux = this->nrCulori + nrCuloriAdaugate;
            aux = new string[dimAux];
            for (int i = 0; i<this->nrCulori; i++)
                aux[i] = this->culoriPosibile[i];
            for (int i=this->nrCulori; i < dimAux; i++)
                aux[i] = culoriAdaugate[i-this->nrCulori];
            delete[] this->culoriPosibile;
        }
        else{
            dimAux = nrCuloriAdaugate;
            aux = new string[dimAux];
            for (int i = 0; i < dimAux; i++)
                aux[i] = culoriAdaugate[i];
        }
        this->culoriPosibile = new string[dimAux];
        this->nrCulori = dimAux;
        for (int i = 0; i < this->nrCulori; i++)
                this->culoriPosibile[i] = aux[i];

        for (int i = 0; i < dimAux; i++)
                cout<< this->culoriPosibile[i]<< " ";
        delete[] aux;
    }

    string* Procedura::getCuloriPosibile(){
        return this->culoriPosibile;
    }

    int Procedura::getNrCuloriPosibile(){
        return this->nrCulori;
    }


class MeniuInteractiv
{
private:
    static MeniuInteractiv *obiect;
    MeniuInteractiv(){};
public:
    static MeniuInteractiv* getInstance(){
        if(!obiect)
            obiect = new MeniuInteractiv();
        return obiect;
    }
    void meniu(){
        int k = 1;
        vector <Client> clienti;
        map <int, Angajat> angajati;
        set <Programare> programari;

        string proceduri[5];
        proceduri[0] = "Manichiura";
        proceduri[1] = "Pedichiura";
        proceduri[2] = "Tuns";
        proceduri[3] = "Vopsit";
        proceduri[4] = "Coafat";

        int preturi[5];
        preturi[0] = 25;
        preturi[1] = 30;
        preturi[2] = 25;
        preturi[3] = 50;
        preturi[4] = 40;

        while(k==1){
            cout<<"\n0 Stop";
            cout<<"\n1 Afisare angajati";
            cout<<"\n2 Detalii despre un angajat";
            cout<<"\n3 Adauga angajat";
            cout<<"\n4 Sterge angajat";
            cout<<"\n5 Afisare clienti";
            cout<<"\n6 Adauga client";
            cout<<"\n7 Adauga o programare";
            cout<<"\n8 Sterge o programare";
            cout<<"\n9 Afisare programari";
            cout<<"\n10 Calculare pret pentru proceduri";
            cout<<"\n\n";
            int comanda;
            cin>>comanda;
            switch(comanda){
                case 0:{
                    k=0;
                    break;
                }
                case 1:{
                    if(angajati.size() == 0)
                        cout<<"Nu exista niciun angajat. Puteti adauga un angajat apasand tasta 3.\n";
                    else{
                        map<int, char*>::iterator it;
                        for (auto it = angajati.begin(); it != angajati.end(); it++){
                            cout<<endl<<it->first<<"\t"<<it->second.getNumePrenume();
                        }
                    }
                    cout<<endl;
                    break;

                }
                case 2:{
                    if (angajati.size()==0)
                        cout<<"Nu exista niciun angajat. Puteti adauga un angajat apasand tasta 3.\n";
                    else{
                        cout<<"\nIntroduceti codul angajatului pentru care doriti sa vedeti mai multe detalii.\n";
                        int cod;
                        cin>>cod;
                        if(cod > angajati.size() || cod < 1)
                            cout<<"\nCodul este gresit. Incercati din nou.\n";
                        else
                            cout<<angajati[cod];
                    }
                    break;

                }
                case 3:{
                    cout<<"\nIntroduceti tasta 1 pentru a introduce o manichiurista, 0 altfel\n";
                    int comanda3;
                    cin>>comanda3;

                    if(comanda3 == 0){
                        Angajat ang;
                        cin>>ang;
                        angajati.insert(pair<int, Angajat>(ang.getCodAngajat(), ang));
                    }
                    else{
                        Manichiurista man;
                        cin>>man;
                        angajati.insert(pair<int, Angajat>(man.getCodAngajat(), man));
                    }
                    break;

                }
                case 4:{
                    if (angajati.size()==0)
                        cout<<"Nu puteti sterge pentru ca nu exista niciun angajat. Puteti adauga un angajat apasand tasta 3.\n";
                    else{
                        cout<<"\nIntroduceti codul angajatului pe care doriti sa il stergeti.\n";
                        int cod;
                        cin>>cod;
                        if(cod > angajati.size() || cod < 1)
                            cout<<"\nCodul este gresit. Incercati din nou.\n";
                        else
                            angajati.erase(cod);
                    }
                    break;

                }
                case 5:{
                    if(clienti.size()==0)
                        cout<<"\nNu exista niciun client. Puteti adauga un client apasand tasta 6.\n";
                    else{
                        for (auto it = clienti.begin(); it != clienti.end(); it++)
                            cout<<endl<<(*it)<<endl;
                    }
                    break;
                }
                case 6:{
                    cout<<"\nIntroduceti tasta 1 pentru a introduce un client fidel, 0 altfel\n";
                    int comanda2;
                    cin>>comanda2;

                    if(comanda2 == 0){
                        Client cli;
                        cin>>cli;
                        clienti.push_back(cli);
                    }
                    else{
                        ClientFidel clif;
                        cin>>clif;
                        clienti.push_back(clif);
                    }
                    break;
                }
                case 7:{
                    Programare prog;
                    cin>>prog;
                    programari.insert(prog);
                    break;

                }
                case 8:{
                    if(programari.size() == 0)
                        cout<<"Nu puteti sterge pentru ca nu exista nicio programare. Puteti adauga o programare apasand tasta 7.\n";
                    else{
                        cout<<"\nIntroduceti numarul programarii pe care doriti sa o stergeti.\n";
                        int cod;
                        cin>>cod;
                        if(cod > programari.size() || cod < 1)
                            cout<<"\nCodul este gresit. Incercati din nou.\n";
                        else{
                            set <Programare> :: iterator it1;
                            it1 = programari.begin();
                            for (int i=0; i<cod-1; i++)
                                it1++;
                            programari.erase(it1);
                        }
                    }
                    break;

                }
                case 9:{
                    if(programari.size() == 0)
                        cout<<"\nNu exista nicio programare. Puteti adauga o programare apasand tasta 7.\n";
                    else
                        for(auto it = programari.begin(); it != programari.end(); it++)
                            cout<<(*it)<<endl;
                    break;
                }
                case 10:{
                    int nrProceduri;
                    cout<<"\nReducerile se aplica pentru urmatoarele servicii:";
                    cout<<"\n1 Manichiura";
                    cout<<"\n2 Pedichiura";
                    cout<<"\n3 Tuns";
                    cout<<"\n4 Vopsit";
                    cout<<"\n5 Coafat";

                    cout<<"\nIntroduceti numarul de proceduri diferite pentru care doriti sa aflati pretul promotional si apoi codul procedurilor.";
                    cout<<"\nExemplu: 1 1 - o procedura si aceea este manichiura.\n";

                    int codProceduri[5];
                    cin>>nrProceduri;
                    for (int i = 0; i<nrProceduri; i++)
                        cin>>codProceduri[i];
                    double suma = 0;
                    for (int i=0; i<nrProceduri; i++)
                        suma += preturi[codProceduri[i]-1];
                    double reducere = 7 * nrProceduri * suma / 100;
                    suma = suma - reducere;
                    cout<<"\nPachetul promotional costa "<<suma<<" lei. Beneficiati de o reducere de "<<reducere<<" lei.\n";
                }
            }
        }
    }
};

MeniuInteractiv* MeniuInteractiv::obiect=0;

int main()
{
    list <Procedura> proceduri;

    Procedura p1, p2, p3, p4, p5, p6, p7, p8, p9;
    f>>p1;
    proceduri.push_back(p1);
    f>>p2;
    proceduri.push_back(p2);
    f>>p3;
    proceduri.push_back(p3);
    f>>p4;
    proceduri.push_back(p4);
    f>>p5;
    proceduri.push_back(p5);
    f>>p6;
    proceduri.push_back(p6);
    f>>p7;
    proceduri.push_back(p7);
    f>>p8;
    proceduri.push_back(p8);
    f>>p9;
    proceduri.push_back(p9);

    for(auto it=proceduri.begin(); it != proceduri.end(); it++)
        g<<*it;


    MeniuInteractiv *meniulMeu = meniulMeu->getInstance();
    meniulMeu->meniu();

    f.close();
    g.close();
    return 0;
}
