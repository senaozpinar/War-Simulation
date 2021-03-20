#include "Character.h"

Character::Character(string _name, string _type, int _attack, int _defense, int _remainingHealth, int _nMaxRounds) {
	this->isAlive = true;
	this->name = _name;
	this->type = _type;
	this->attack = _attack;
	this->defense = _defense;
	this->remainingHealth = _remainingHealth;
	this->healthHistory = new int[_nMaxRounds + 1];
	this->healthHistory[0] = _remainingHealth;
	this->nRoundsSinceSpecial = 0;
}

Character::Character(const Character& character) {
	this->isAlive = true;
	this->name = character.name;
	this->type = character.type;
	this->attack = character.attack;
	this->defense =character.defense;
	this->remainingHealth = character.remainingHealth;
	this->healthHistory = new int[character.nMaxRounds + 1];
	this->healthHistory[0] = character.remainingHealth;
	this->nRoundsSinceSpecial = 0;
}

Character& Character::operator=(const Character& character) {
	if(this == &character){
		return *this;
	}
	this->name = character.name;
	this->type = character.type;
	this->attack = character.attack;
	this->defense = character.defense;
	this->remainingHealth =character.remainingHealth;
	this->healthHistory[0] = character.remainingHealth;
	return *this;
}

bool Character::operator<(const Character& other) {
	if(this->defense < other.attack){
		this->remainingHealth = this->remainingHealth - (other.attack - this->defense);
		if(this->remainingHealth <= 0){
			this->isAlive = false;
			this->remainingHealth = 0;
		}
		return true;
	}
	return false;
}

Character::~Character() {
	//delete[] this->healthHistory;
}