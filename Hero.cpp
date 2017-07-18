#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iostream>
#include "Hero.h"
#define _CRT_SECURE_NO_WARNINGS

//////////////////////////////////////////////
// Default constructor
Hero::Hero () {

	m_name[0] = '\0';
	m_health = 0;
	m_maximumHealth = 0;
	m_attack = 0;
}

///////////////////////////////////////////////////
// Constructor
//
Hero::Hero (const char name[], int maximumHealth, int attack) {
	strcpy(m_name, name);
	m_health = maximumHealth;
	m_maximumHealth = maximumHealth;
	m_attack = attack;
}

/////////////////////////////////////////////////////////
// ostream helper overloaded operator <<
//
std::ostream& operator<<(std::ostream& out, const Hero& h) {
	//outputs the name of a hero
	out << h.m_name;
	return out;
}



/////////////////////////////////////////////////
// Hero::isEmpty ()
// return true if the Hero object is uninitialized
//
bool Hero::isEmpty() const {
	bool empty;
	//check for the safe state
	if (m_name[0] == '\0' && m_maximumHealth == 0 && m_attack == 0 && m_health == 0) {
		empty = true;
	} else {
		empty = false;
	}//if (m_name[0] == '\0' && m_maximumHealth == 0 && m_attack == 0 && m_health == 0)
	return empty;
}


int  Hero::getAttack () const   {
	return m_attack;
}

bool Hero::isAlive () const {
	return m_health > 0;
}
/////////////////////////////////////////////////
// sets the Hero object's health back to full

void Hero::respawn() {
	//restores hp
	m_health = m_maximumHealth;
}
void Hero::deductHealth(int attack) {
	m_health -= attack;
//	std::cout<<"!!!!!!!!!!!!!!!!!!!!!!"<<m_health;

}

//////////////////////////////////////////////////////////////////
// Global helper function
// compute the damage that A inflicts on B
// and of B on A
//
void  applyDamage(Hero &A, Hero &B) {
	if (A.Hero::m_health > 0 && B.m_health > 0) {
		A.m_health -= B.m_attack;
		B.m_health -= A.m_attack;
	}
	//if A's HP <= 0 then it's 0 (meaning A's dead)
	if (A.m_health <= 0) {
		A.m_health = 0;
	}
	//if B's HP <= 0 then it's 0 (meaning B's dead)
	if (B.m_health <= 0) {
		B.m_health = 0;
	}
}

//////////////////////////////////////////////////////////////////
// Global helper operator
// rather than type in fight(hercules, theseus), we use an operator
// so you can type in hercules * theseus
//
// returns a reference to the winner object
//
// so that if hercules is stronger,
// (hercules * theseus) == hercules
// will be true.
//
// note the inputs are const, so that you can be sure that the heros will be unharmed during the fight.
//
const Hero &operator*(const Hero &first, const Hero &second) {
	// Display the names of the people fighting

	std::cout << "AncientBattle! " << first << " vs " << second << " : ";

	// We want our heroes to exit the battle unharmed, so
	// we make the input arguments const.
	// So how can we modify the objects during the fight?
	// We make copies of them.
	Hero A = first;
	Hero B = second;
	const Hero *winner = nullptr;

	// Now A will fight B, and winner will point to the winner.
	// Main fight loop
	unsigned int rounds = 0;
	// loop while both are still alive
	// fight for 100 rounds
	while (A.isAlive() && B.isAlive() && rounds < 100) {
		rounds++;
		applyDamage(A, B);
	}

	// if we got here, then one Hero is dead, or if both are alive then it was a draw.
	bool draw;

	if (A.isAlive() && B.isAlive()) { draw = true; }
	else { draw = false; }

	// if it was a draw, then we decide by tossing an unfair coin and always
	// declare that A was the winner.
	if (draw) {
		winner = &first;
	} else if (A.isAlive()) {
		winner = &first;
	} else {
		winner = &second;
	}

	// print out the winner
	std::cout << "Winner is " << *winner << " in " << rounds << " rounds." << std::endl;

	// return a reference to the winner
	return *winner;
}
