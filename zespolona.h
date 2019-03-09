//plik naglowkowy klasy liczby zespolonej
#ifndef ZESPOLONA_H_
#define ZESPOLONA_H_
#include <iostream>

template <class Type>
class Zespolona
{
private:
    Type * rzeczywista;
    Type * urojona;
public:
    Zespolona()
    {
        rzeczywista=new Type;
        *rzeczywista=0;
        urojona=new Type;
        *urojona=0;
    }
    Zespolona(Type x,Type y)
    {
        rzeczywista=new Type;
        *rzeczywista=x;
        urojona=new Type;
        *urojona=y;
    }
    Zespolona(const Zespolona & z)
    {
        rzeczywista=new Type;
        *rzeczywista=*z.rzeczywista;
        urojona=new Type;
        *urojona=*z.urojona;
    }
    ~Zespolona()
    {
        delete rzeczywista;
        delete urojona;
    }
    Zespolona & operator=(const Zespolona & z)
    {
        if(this==&z)
            return *this;
        delete rzeczywista;
        rzeczywista=new Type;
        *rzeczywista=*z.rzeczywista;
        delete urojona;
        urojona=new Type;
        *urojona=*z.urojona;
    }
    Zespolona operator+(const Zespolona & z) const
    {
        Zespolona suma;
        *suma.rzeczywista=*rzeczywista+*z.rzeczywista;
        *suma.urojona=*urojona+*z.urojona;
        return suma;
    }
    Zespolona operator-(const Zespolona & z) const
    {
        Zespolona roznica;
        *roznica.rzeczywista=*rzeczywista-*z.rzeczywista;
        *roznica.urojona=*urojona-*z.urojona;
        return roznica;
    }
    Zespolona operator*(const Zespolona & z) const
    {
        Zespolona iloczyn;
        *iloczyn.rzeczywista=(*rzeczywista*(*z.rzeczywista))-(*urojona*(*z.urojona));
        *iloczyn.urojona=(*urojona*(*z.rzeczywista))+(*rzeczywista*(*z.urojona));
        return iloczyn;
    }
    Zespolona operator/(const Zespolona & z) const
    {
        Zespolona iloraz;
        int pomoc;
        pomoc=*z.rzeczywista*(*z.rzeczywista)+(*z.urojona)*(*z.urojona);
        *iloraz.rzeczywista=(*rzeczywista*(*z.rzeczywista))+(*urojona*(*z.urojona));
        *iloraz.rzeczywista=*iloraz.rzeczywista/pomoc;
        *iloraz.urojona=(*urojona*(*z.rzeczywista))-(*rzeczywista*(*z.urojona));
        *iloraz.urojona=*iloraz.urojona/pomoc;
        return iloraz;
    }
    friend std::ostream & operator<<(std::ostream & os, const Zespolona & z)
    {
        if(*z.rzeczywista!=0)
        {
            if(*z.urojona>0)
                os<<*z.rzeczywista<<"+"<<*z.urojona<<"i";
            else if(*z.urojona==0)
                os<<*z.rzeczywista;
            else
                os<<*z.rzeczywista<<*z.urojona<<"i";
        }
        else
        {
            if(*z.urojona==0)
                os<<0;
            else
                os<<*z.urojona<<"i";
        }
        return os;
    }
};
#endif
