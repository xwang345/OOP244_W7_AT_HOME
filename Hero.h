#ifndef HERO_H
#define HERO_H

#include <iostream>
class Hero {
protected:
    char m_name[41];
    int  m_attack;
    int  m_maximumHealth;
    int  m_health;
public:

    // constructors
    Hero ();
    Hero (const char name[], int maximumHealth, int attack);

    // member functions
    void respawn();
    bool isAlive () const ;
    int  getAttack () const;
    void deductHealth(int);
    void display (std::ostream&) const;
    bool isEmpty () const;

    // friend helper function to insert name into ostream
    friend std::ostream& operator<<(std::ostream&, const Hero&);
    friend  void applyDamage (Hero& A, Hero& B);
};

void applyDamage (Hero& A, Hero& B);
const Hero & operator*(const Hero &, const Hero &);
std::ostream& operator<<(std::ostream&, const Hero&);

#endif
