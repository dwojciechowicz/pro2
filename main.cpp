#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>
#include "zespolona.h"

using namespace std;

int j;
//vector <string> lista;//tu zapisuje rownania wpisywane przez uzytkownika
vector <string> zmienne;//tu zapisuje nazwy zmiennych
vector <Zespolona<double> > wynik;

int rownanie(const string sprawdzany);//sprawdza czy wprowadzony ciag znaków jest prawidłowym rownaniem
void menu();
string toONP(string wyrazenie);
bool isDzialanie(char z);
Zespolona <double> oblicz(string onp);

int main()
{
    string c;
    menu();
    cin >> c;
    //string onp = toONP(c);
    //cout << onp << endl;
    //cout << oblicz(onp) << endl;
    while (c != "end")//wczytywanie równanie
    {
        if (rownanie(c) == 0)
        {
            cout << "Blednie podane rownanie!" << endl;
            break;
        }
        string nazwaZmiennej = c.substr(0,1);
        zmienne.push_back(nazwaZmiennej);
        string tresc = c.substr(2);
        tresc = toONP(tresc);
        wynik.push_back(oblicz(tresc));
        cin >> c;
    }
    for (int i = 0; i < zmienne.size(); i++)
    {
        cout << zmienne[i] << "=" << wynik[i] << endl;
    }
    cin >> c; //pozostawiony cin aby nie zamknal sie program po skonczeniu dzialania
    return 0;
}

int rownanie(const string sprawdzany)
{
    int dlugosc;
    int a,b,c;
    int lewy=0;//liczy ilosc lewych nawiasów
    int prawy=0;//i prawych
    dlugosc=sprawdzany.length();
    if(sprawdzany[0]=='i')
        return 0;
    b=sprawdzany.find_first_of("(");
    c=sprawdzany.find_first_of(")");
    if(c<b)
        return 0;
    b=sprawdzany.find_last_of("(");
    c=sprawdzany.find_last_of(")");
    if(b>c)
        return 0;
    dlugosc = sprawdzany.length();
    //for (j = 1; j<dlugosc; j++)
    //{
    if (sprawdzany[1] == '=')
    {
        j=1;
        for(a=j+1; a<dlugosc; a++)
        {
            if(sprawdzany[a]<40||sprawdzany[a]>122||sprawdzany[a]==','||(sprawdzany[a]>57&&sprawdzany[a]<65)||(sprawdzany[a]>90&&sprawdzany[a]<97))
                return 0;
            if(sprawdzany[0]==sprawdzany[a])
                return 0;
            if(sprawdzany[a]=='(')
                lewy++;
            if (sprawdzany[a]==')')
                prawy++;
        }
        if (lewy!=prawy)
        {
            return 0;
        }
        for (a = j; a<(dlugosc - 1); a++)
        {
            if(isDzialanie(sprawdzany[a]))
                if(isDzialanie(sprawdzany[a+1])&&sprawdzany[a+1]!='-')
                {
                    return 0;
                }
            if((isdigit(sprawdzany[a])&&isalpha(sprawdzany[a+1])&&sprawdzany[a+1]!='i')||(isdigit(sprawdzany[a+1])&&isalpha(sprawdzany[a]))||((sprawdzany[a+1]=='(')&&isalpha(sprawdzany[a]))||((sprawdzany[a]==')')&&isalpha(sprawdzany[a+1]))
               || ((sprawdzany[a+1]=='(')&&isdigit(sprawdzany[a]))||((sprawdzany[a]==')')&&isdigit(sprawdzany[a+1]))||(isalpha(sprawdzany[a])&&isalpha(sprawdzany[a+1])))
                return 0;
        }
        if(sprawdzany[j+1]=='*'||sprawdzany[j+1]=='/')
            return 0;
        return j;
    }
    //}
    return 0;
}
void menu()
{
    cout << "Oto kalkulator do liczb zespolonych." << endl;
    cout << "Aby wpisac rownanie zacznij od podania jednoliterowej (roznej od i) nazwy zmiennej." << endl;
    cout << "Aby przejsc do wpisywania kolejnego rownania nacisnij enter." << endl;
    cout << "Aby zakonczyc wpisywanie wpisz: end." << endl;
}

bool isDzialanie(char z)
{
    if (z == '+' || z == '-' || z == '*' || z == '/')
        return true;
    else return false;
}
string toONP(string wyrazenie)
{
    string onp, analiza;
    stack <char> stos;
    for (int i = 0; i < wyrazenie.size(); i++)
    {
        analiza = "";
        if (isdigit(wyrazenie[i]))   //czytamy do konca liczbe
        {
            analiza += wyrazenie[i];
            int j;
            for (j = i+1; j < wyrazenie.size(); j++)
            {
                if (wyrazenie[j] == 'i')
                {
                    analiza += 'i';
                    break;
                }
                else if (isdigit(wyrazenie[j]) || wyrazenie[j]=='.')
                    analiza += wyrazenie[j];
                else
                {
                    j--;
                    break;
                }
            }
            i = j;
            onp += analiza + " ";
        }
        else if (wyrazenie[i] == 'i')
        {
            onp += "1i ";
        }
        else if (wyrazenie[i] >= 'a' && wyrazenie[i] <= 'z')
        {
            onp += wyrazenie[i];
            onp += " ";
        }
        else if (wyrazenie[i] == ' ')
        {
            continue;
        }
        else   //znak: ()+-/*
        {
            char znak = wyrazenie[i];
            switch (znak)
            {
            case '+':
                ;
            case '-':
                while (stos.size() && stos.top() != '(')
                {
                    onp += stos.top();
                    onp += " ";
                    stos.pop();
                }
                stos.push(znak);
                break;
            case '*':
                ;
            case '/':
                while (stos.size() && stos.top() != '(' && stos.top() != '+' && stos.top() != '-')
                {
                    onp += stos.top();
                    onp += " ";
                    stos.pop();
                }
                stos.push(znak);
                break;
            case '(':
                stos.push('(');
                break;
            case ')':
                while (stos.top() != '(')
                {
                    onp += stos.top();
                    onp += " ";
                    stos.pop();
                }
                stos.pop();
                break;
            }
        }
    }
    while(stos.size())
    {
        onp += stos.top();
        onp+=" ";
        stos.pop();
    }
    return onp;
}
Zespolona <double> oblicz(string onp)
{
    stack <Zespolona<double> > stos;
    string an;
    Zespolona<double> z1, z2;
    while (true)
    {
        an = onp.substr(0, min(onp.find("\n"), onp.find(" ")));
        if (an.empty())//koniec danych!
            break;
        onp.erase(0, an.size() + 1);
        if (an.size() > 1 && an[an.size() - 1] == 'i')  //urojona
        {
            an.erase(an.size() - 1);
            double im = stod(an);
            //Zespolona <double> z(0, im);
            stos.push(Zespolona<double>(0,im));
        }
        else if (isdigit(an[0]))   //zwykla liczba
        {
            double re = stod(an);
            stos.push(Zespolona<double>(re, 0));
        }
        else if(isDzialanie(an[0]))  //dzialanie: +-*/
        {
            z2 = stos.top();
            stos.pop();
            z1 = stos.top();
            stos.pop();
            switch (an[0])
            {
            case '+':
                stos.push(z1 + z2);
                break;
            case '-':
                stos.push(z1 - z2);
                break;
            case '*':
                stos.push(z1 * z2);
                break;
            case '/':
                stos.push(z1 / z2);
                break;
            }
        }
        else  //zmienna->wstawic jej wartosc na stos
        {
            int i=0;
            for (i = 0; i < zmienne.size(); i++)
                if (zmienne[i] == an) break;
            stos.push(wynik[i]);
        }
    }
    return stos.top();
}
