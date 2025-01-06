#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

class HockeyPlayer {
public:
    int id;
    int jersey;
    std::string name;
    std::string teamName;
    
    HockeyPlayer(int _id = 0, std::string _name = "", int _jersey = 0, std::string _team = "") 
        : id(_id), name(_name), jersey(_jersey), teamName(_team) {}
};

class LRUCache {
private:
    std::vector<HockeyPlayer> cache;
    const int MAX_SIZE = 10;
    
    HockeyPlayer readPlayerFromFile(int id) {
        std::ifstream file("hockeyplayers.txt");
        std::string line;
        
        while (getline(file, line)) {
            std::istringstream iss(line);
            int playerId;
            int jersey;
            std::string name;
            std::string team;
            
            if (iss >> playerId) {
                std::getline(iss, name, '"');
                std::getline(iss, name, '"');
                iss >> jersey >> team;
                if (playerId == id) {
                    return HockeyPlayer(playerId, name, jersey, team);
                }
            }
        }
        return HockeyPlayer();
    }

public:
    HockeyPlayer* GetPlayer(int id) {
        for (auto it = cache.begin(); it != cache.end(); ++it) {
            if (it->id == id) {
                HockeyPlayer player = *it;
                cache.erase(it);
                cache.insert(cache.begin(), player);
                return &cache[0];
            }
        }
        
        HockeyPlayer player = readPlayerFromFile(id);
        if (player.id == 0) return nullptr; 
        
        if (cache.size() >= MAX_SIZE) {
            cache.pop_back();
        }
        cache.insert(cache.begin(), player);
        return &cache[0];
    }
};

void generatePlayerFile() {
    std::ofstream outFile("hockeyplayers.txt");
    if (!outFile) {
        std::cerr << "Error opening file for writing" << std::endl;
        return;
    }

    std::vector<std::string> firstNames = {"Henrik", "Erik", "Lars", "Johan", "Anders"};
    std::vector<std::string> lastNames = {"Svensson", "Johansson", "Karlsson", "Nilsson", "Larsson"};
    std::vector<std::string> teamNames = {"Leksands IF", "Frölunda HC", "Djurgårdens IF", "Färjestad BK", "HV71"};
    int numPlayers = 100000;

    srand(time(0));
    for (int i = 0; i < numPlayers; ++i) {
        int firstNameIndex = rand() % firstNames.size();
        int lastNameIndex = rand() % lastNames.size();
        int teamNameIndex = rand() % teamNames.size();
        int jerseyNumber = rand() % 23 + 1;

        std::string fullName = firstNames[firstNameIndex] + " " + lastNames[lastNameIndex];
        outFile << i + 1 << " " << fullName << " " << jerseyNumber << " " << teamNames[teamNameIndex] << std::endl;
    }

    outFile.close();
}

void hockeyPlayers() {
    generatePlayerFile();
    LRUCache cache;
    int playerid;
    std::cout << "Enter player id: ";
    std::cin >> playerid;
    HockeyPlayer* player = cache.GetPlayer(playerid);
    if (player) {
        std::cout << "Player found: " << player->name << std::endl;
    } else {
        std::cout << "Player not found" << std::endl;
    }
}