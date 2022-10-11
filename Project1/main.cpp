#include <iostream>
#include <set>
#include <string>
#include <map>
#include <fstream>
#include <queue>

// dla 0, 4 => dziala
// 4,0
bool isConnected(auto a, auto b, std::map<std::string, std::set<std::string>> edges) {
    if (a > b) return isConnected(b, a, edges);
    if (edges[a].count(b)) return true;
    return false;
}

std::string parseString(std::string& line) {
    std::string name;
    
    do {
        name += line[0];
        line.erase(0, 1);
    } while (line[0] != ',');

    line.erase(0, 2);
    return name;
}

void createEdge(std::map<std::string, std::set<std::string>>& edges, std::string line) {
    std::string edge{};
    edge = parseString(line);
    line += ',';

    while (!line.empty()) {
        std::string friendName = parseString(line);
        edges[edge].insert(friendName);
    }
}


void readFromFile(std::map<std::string, std::set<std::string>>& edges) {
    std::fstream file{};
    std::string line{};
    file.open("C:\\Users\\FGKN34\\Desktop\\Motorola\\week_11_SI\\BredthFirstOA\\Project1\\database.csv");

    while (true) {
        std::getline(file, line);
        if (line != "END") {
            //std::cout << line << std::endl;
            createEdge(edges, line);
        }
        else
            break;
    }
    file.close();
}

void showFriends(std::map<std::string, std::set<std::string>> edges, std::string person) {

    for (auto& e : edges) {
        if (e.first == person) {
            std::cout << person << "'s friends are: " << std::endl;
            for (auto& v : e.second) {
                std::cout << v << std::endl;
            }
        }   
    }
}

//REKURENCJAAA <3

void listFriendsOfFriends(std::map<std::string, std::set<std::string>> edges,std::string person, int distance, std::set<std::string> &allFriends) {
    
    if (distance > 0) {
        for (auto& e : edges) {
            if (e.first == person) {
                for (auto& v : e.second) {
                    if (allFriends.count(v) == 0) {
                        allFriends.insert(v);
                        listFriendsOfFriends(edges, v, distance - 1, allFriends);
                    }
                }
            }
        }
    }
    
}

void showSetOfFriends(std::set<std::string > edges) {
    for (auto& e : edges) {
        std::cout << e << std::endl;
    }
}
void showSetOfFriends(std::vector<std::string > edges) {
    for (auto& e : edges) {
        std::cout << e << std::endl;
    }
}

//void showFriendsOfFriends(std::map<std::string, std::set<std::string>> edges, std::string person, int distance) { //powtarzalne, wyswietla w nieczytelny sposob
//
//    if (distance > 0) {
//        for (auto& e : edges) {
//            if (e.first == person) {
//                std::cout << person << "'s friends are: " << std::endl;
//                for (auto& v : e.second) {
//                    std::cout << "  " << v << std::endl;
//                    showFriendsOfFriends(edges, v, distance - 1);
//                }
//            }
//        }
//    }
//
//}

int minimumDistance(std::string nodeStart, std::string nodeEnd, std::map<std::string, std::set<std::string>> edges)
{  // BFS -  breadth-first search, BFS
    std::queue< std::string > toCheckBasic;
    std::queue<std::pair<std::string, int >> toCheck;

    std::set<std::string> visited; // odwiedzone

    // 0. inicjalizacja
    toCheck.push(std::make_pair(nodeStart, 0));

    while (!toCheck.empty()) {
        // 1. wez nastepny z kolejki
        auto cur = toCheck.front();
        toCheck.pop();
        // 2. wez jego sasiadow
        auto neighbours = edges[cur.first];
        for (auto it = neighbours.begin(); it != neighbours.end(); ++it) {
            if (!visited.contains(*it))
            { // jesli ten sasiad nie byl jeszcze odwiedzony
                toCheck.push(make_pair(*it, cur.second + 1));
            }
        }
        // 3. czy to jest ten ktorego szukamy?
        if (cur.first == nodeEnd) {
            return cur.second;
        }
        visited.insert(cur.first);
    }

    return -1;
}

std::vector<std::string> shortestPaths(std::string nodeStart, std::string nodeEnd, std::map<std::string, std::set<std::string>> edges)
{  // BFS -  breadth-first search, BFS
    std::queue< std::string > toCheckBasic;
    std::queue<std::pair<std::string, std::vector<std::string>>> toCheck;

    std::set<std::string> visited; // odwiedzone

    // 0. inicjalizacja
    std::vector<std::string> ebebe;
    ebebe.push_back(nodeStart);
    toCheck.push(std::make_pair(nodeStart, ebebe));

    while (!toCheck.empty()) {
        // 1. wez nastepny z kolejki
        auto cur = toCheck.front();
        toCheck.pop();
        // 2. wez jego sasiadow
        auto neighbours = edges[cur.first];
        for (auto it = neighbours.begin(); it != neighbours.end(); ++it) {
            if (!visited.contains(*it))
            { // jesli ten sasiad nie byl jeszcze odwiedzony
                std::vector<std::string> abba = cur.second;
                abba.push_back(*it);
                toCheck.push(make_pair(*it, abba));
            }
        }
        // 3. czy to jest ten ktorego szukamy?
        if (cur.first == nodeEnd) {
            return cur.second;
        }
        visited.insert(cur.first);
    }
    std::vector<std::string> empty{ "cos", "poszlo", "zle" };
    return empty;
}


int main()
{

    std::map<std::string, std::set<std::string>> edges;
    readFromFile(edges);
    
    //lvl -1
    //showFriends(edges, "Axel Kibo"); 
    // 
    //lvl 0
    //std::set<std::string> allFriends;
    //listFriendsOfFriends(edges, "Axel Kibo", 3, allFriends);
    //showSetOfFriends(allFriends);
    //
    // lvl 1
    //std::cout<<"Minimal distance beetwen Axel Kibo and Karleigh Winfred is "<< minimumDistance("Axel Kibo", "Karleigh Winifred", edges);
    //
    //lvl 2
    std::vector<std::string> shortestPath;
    shortestPath = shortestPaths("Alec Aurora", "Cooper Lydia", edges);
    showSetOfFriends(shortestPath);
    
    //DONE!

    return 0;
}
