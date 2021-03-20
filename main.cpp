#include "Character.h"
#include <fstream>
#include <vector>

using namespace std;

bool theWarIsOver(const vector<Character>& community){
	if(!community[0].isAlive){
		return true;
	}
	if(!community[1].isAlive && !community[2].isAlive && !community[3].isAlive && !community[4].isAlive){
		return true;
	}
	return false;
}

int findCharacter(string char_name, vector<Character>& community){
	int theOneNo = -1;
	for(int i = 0; i < 5; i++){
		if(community[i].name != char_name){
			string s = community[i].name;
			if(s[0] > char_name[0]){
				theOneNo = i;
			}
			int j = 1;
			if (s[0] == char_name[0]){
				while(s[j]==char_name[j]){
					j++;
				}
				if(s[j] > char_name[j]){
					theOneNo = i;
				}
			}
		}
	}
	if(theOneNo == -1){
		for(int i = 0; i < 5; i++){
		if(community[i].name != char_name){
			string s = community[i].name;
			if(s[0] < char_name[0]){
				theOneNo = i;
			}
			int j = 1;
			if (s[0] == char_name[0]){
				while(s[j]==char_name[j]){
					j++;
				}
				if(s[j] < char_name[j]){
					theOneNo = i;
				}
			}
		}
	}
	}
	return theOneNo;
}

void letsAttack(string attacker_name, string defender_name, string specOrNot, int roundNo, vector<Character>& community_1, vector<Character>& community_2){
	int turn = roundNo % 2;
	int attacker_no;
	int defender_no;

	if(turn == 1){
		for(int i = 0; i < 5; i++){
			if(community_1[i].name == attacker_name){
				if(community_1[i].isAlive){
					attacker_no = i;
				}
				else{
					attacker_no = findCharacter(attacker_name, community_1);
				}
			}
			if(community_2[i].name == defender_name){
				if(community_2[i].isAlive){
					defender_no = i;
				}
				else{
					defender_no = findCharacter(defender_name, community_2);
				}
			}
		}
		if(specOrNot == "SPECIAL"){
			if(community_1[attacker_no].type == "Elves"){
				if(community_1[attacker_no].nRoundsSinceSpecial >= 10){
					community_1[0].remainingHealth += (community_1[attacker_no].remainingHealth) / 2;
					community_1[attacker_no].remainingHealth = (community_1[attacker_no].remainingHealth) / 2;
					community_1[attacker_no].nRoundsSinceSpecial = 0;
				}
			}
			if(community_1[attacker_no].type == "Dwarfs"){
				if(community_1[attacker_no].nRoundsSinceSpecial >= 20){
					if(community_1[defender_no] < community_1[attacker_no]){
						community_2[defender_no].healthHistory[roundNo] = community_2[defender_no].remainingHealth;
					}
					community_1[attacker_no].nRoundsSinceSpecial = 0;
				}
			}
			if(community_1[attacker_no].type == "Wizards"){
				if(community_1[attacker_no].nRoundsSinceSpecial >= 50){
					int for1 = roundNo-1;
					int for2 = roundNo-1;
					int for3 = roundNo-1;
					int personToRevive = -1;
					if(!community_1[1].isAlive){
						while(community_1[1].healthHistory[for1]==0){
							for1--;
						}
						personToRevive = 1;
					}
					if(!community_1[2].isAlive){
						while(community_1[2].healthHistory[for2]==0){
							for2--;
						}
						if(for2 > for1){
							personToRevive = 2;
						}
					}
					if(!community_1[3].isAlive){
						while(community_1[3].healthHistory[for3]==0){
							for3--;
						}
						if( for3 > for1 && for3 > for2){
							personToRevive = 3;
						}
					}
					if(personToRevive != -1){
					community_1[personToRevive].isAlive = true;
					community_1[personToRevive].remainingHealth = community_1[personToRevive].healthHistory[0];
					}
				}
			}
		}
		if(community_2[defender_no] < community_1[attacker_no]){
			community_2[defender_no].healthHistory[roundNo] = community_2[defender_no].remainingHealth;
		}

	}
	//community2's turn
	else{
		for(int i = 0; i < 5; i++){
			if(community_2[i].name == attacker_name){
				if(community_2[i].isAlive){
				//attacker = &community_2[i];
				attacker_no = i;
				}
				else{
					attacker_no = findCharacter(attacker_name, community_2);
				}
			}
			if(community_1[i].name == defender_name){
				if(community_1[i].isAlive){
					defender_no = i;
				}
				else{
					defender_no = findCharacter(defender_name, community_1);
				}
			}
		}
		if(specOrNot == "SPECIAL"){
			if(community_2[attacker_no].type == "Elves"){
				if(community_2[attacker_no].nRoundsSinceSpecial >= 10){
					community_2[0].remainingHealth += (community_2[attacker_no].remainingHealth) / 2;
					community_2[attacker_no].remainingHealth = (community_2[attacker_no].remainingHealth) / 2;
					community_2[attacker_no].nRoundsSinceSpecial = 0;
				}
			}
			if(community_2[attacker_no].type == "Dwarfs"){
				if(community_2[attacker_no].nRoundsSinceSpecial >= 20){
					if(community_1[defender_no] < community_2[attacker_no]){
						community_1[defender_no].healthHistory[roundNo] = community_1[defender_no].remainingHealth;
					}
					community_2[attacker_no].nRoundsSinceSpecial = 0;
				}
			}
			if(community_2[attacker_no].type == "Wizards"){
				if(community_2[attacker_no].nRoundsSinceSpecial >= 50){
					int for1 = roundNo-1;
					int for2 = roundNo-1;
					int for3 = roundNo-1;
					int personToRevive = -1;
					if(!community_2[1].isAlive){
						while(community_2[1].healthHistory[for1]==0){
							for1--;
						}
						personToRevive = 1;
					}
					if(!community_2[2].isAlive){
						while(community_2[2].healthHistory[for2]==0){
							for2--;
						}
						if(for2 > for1){
							personToRevive = 2;
						}
					}
					if(!community_2[3].isAlive){
						while(community_2[3].healthHistory[for3]==0){
							for3--;
						}
						if( for3 > for1 && for3 > for2){
							personToRevive = 3;
						}
					}
					if(personToRevive != -1){
					community_2[personToRevive].isAlive = true;
					community_2[personToRevive].remainingHealth = community_2[personToRevive].healthHistory[0];
					}
				}
			}
		}
		if(community_1[defender_no] < community_2[attacker_no]){
			community_1[defender_no].healthHistory[roundNo] = community_1[defender_no].remainingHealth;
		}
	}

	vector<Character>::iterator it;
	for(it = community_1.begin(); it!= community_1.end(); it++){
		*((*it).healthHistory + roundNo) = (*it).remainingHealth;
		(*it).nRoundsSinceSpecial++;
	}
	for(it = community_2.begin(); it!= community_2.end(); it++){
		*((*it).healthHistory+ roundNo)= (*it).remainingHealth;
		(*it).nRoundsSinceSpecial++;
	}

}


int main(int argc, char* argv[]) {

	string infile_name = argv[1];
	string outfile_name =argv[2];

	ifstream infile;
	ofstream outfile;
	infile.open(infile_name);
	outfile.open(outfile_name);

	int nMaxRounds;
	infile >> nMaxRounds;

	int numOfMemOfAComm = 5;
	vector<Character> community1;
	vector<Character> community2;

	//Settling the first community.
	for(int i = 0; i < numOfMemOfAComm; i++){
		string name, type;
		int attack, defense, remainingHealth;

		infile >> name >> type >> attack >> defense >> remainingHealth;
		community1.push_back(Character(name, type, attack, defense, remainingHealth, nMaxRounds));
	}

	//Settling the second community.
	for(int i = 0; i < numOfMemOfAComm; i++){
		string name, type;
		int attack, defense, remainingHealth;

		infile >> name >> type >> attack >> defense >> remainingHealth;
		community2.push_back(Character(name, type, attack, defense, remainingHealth, nMaxRounds));
	}

		vector<Character>* c1 = &community1;
		vector<Character>* c2 = &community2;

	//Reads each round of war and sends them to be simulated
	int i;
	int turn;
	for(i = 1; i <= nMaxRounds; i++){
		string attacker_name, defender_name, specOrNot;
		infile >> attacker_name >> defender_name >> specOrNot;
		turn = i % 2;
		letsAttack(attacker_name, defender_name, specOrNot, i, community1, community2 );
		if(turn == 1){
			if(theWarIsOver(community2)){
			outfile << "Community-1" << '\n';
			outfile << i << '\n';
			break;
			}
		}
		else{
			if(theWarIsOver(community1)){
				outfile << "Community-2" << '\n';
				outfile << i << '\n';
				break;
			}
		}
	}


	int numOfCasulties =0;
	for(int i = 0;i < 5; i++) {
		if(!(community1[i].isAlive)){
			numOfCasulties++;
		}
	}
	for(int i = 0;i < 5; i++){
		if(!(community1[i].isAlive)){
			numOfCasulties++;
		}
	}

	if(i == nMaxRounds +1){
	outfile << "Draw" << '\n';
	outfile << nMaxRounds << '\n';
	}

	outfile << numOfCasulties << '\n';

	//printing to file the first community
	for(int i = 0; i < numOfMemOfAComm; i++){
		outfile << (*c1)[i].name << " ";
		for(int j = 0; j < nMaxRounds + 1; j++){
			outfile << (*c1)[i].healthHistory[j] << ' ';
		}
		outfile << endl;
	}

	//printing to file the second community
	for(int i = 0; i < numOfMemOfAComm; i++){
		outfile << (*c2)[i].name << " ";
		for(int j = 0; j < nMaxRounds + 1; j++){
			outfile << (*c2)[i].healthHistory[j] << ' ';
		}
		outfile << endl;
	}

	infile.close();
	outfile.close();

    return 0;
}