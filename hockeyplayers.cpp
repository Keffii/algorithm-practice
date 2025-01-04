#include <iostream> 
#include <cstdlib> 
#include <ctime> 
#include <vector> 
#include <fstream>

class hockeyPlayer{
    public:
    int id;
    std::string Player;
    int jersey;
    std::string teamName;
};

//Tänk på ett nattduksbord och flytta runt i vector använd least recently used.
//Om spelaren finns i vectorn, flytta den till första platsen och returna.
//Om spelaren inte finns i vectorn, lägg till den på första platsen och ta bort den sista.
//Om vectorn är full, ta bort den sista.
//Sök efter ID med GetPlayer bland de 10k spelarna i filen hockeyplayers.txt.



class LRUCache{
public:
     Player *GetPlayer(int id);
private:
    hockeyPlayer cache[10];
};

void hockeyPlayers(){ 
    srand(time(0));

    std::vector<std::string> firstNames = {"Henrik", "Erik", "Lars", "Johan", "Anders"}; 
    std::vector<std::string> lastNames = {"Svensson", "Johansson", "Karlsson", "Nilsson", "Larsson"}; 


    std::ofstream outFile("hockeyplayers.txt");
    if(!outFile){
        std::cerr << "Error opening file for writing" << std::endl;
        return;
    }

    int numNames = 10000; 
    for(int i = 0;i < numNames; ++i){ 
        int firstNameIndex = rand() % firstNames.size();
        int lastNameIndex = rand() % lastNames.size(); 

        std::string fullName = firstNames[firstNameIndex] + " " + lastNames[lastNameIndex]; 
        outFile << fullName << std::endl; 
    }

    outFile.close();
}