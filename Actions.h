#ifndef PROJEKT_ACTIONS_H
#define PROJEKT_ACTIONS_H
#include <string>
#include <fstream>
#include <vector>
using std::string, std::fstream, std::vector;

/*********************************************************************************************************************
  klasa dostarczająca do głównej metody aplikacji zestaw metod, odpowiadających komendom, czyli działaniom na plikach
*********************************************************************************************************************/
class Actions {
private:
    string parameter;
    string content;
    string in;
    string category;
    string tmp;
    char playerChoice;
    bool condition;
public:
    void search(vector<string> vec);
    void sort(vector<string> vec);
    string addPassword(vector<string> vec, string password, string path);
    string passwordChoice();
    string add();
    void editPassword(vector<string> vec);
    vector<string> removePassword(vector<string> vec, string password, string path);
    string addCategory(vector<string> content, const string& password, const string& path);
    vector<string> removeCategory(vector<string> vec, string password, string path);
};

#endif //PROJEKT_ACTIONS_H