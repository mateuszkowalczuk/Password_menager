#ifndef PROJEKT_CODE_H
#define PROJEKT_CODE_H
#include <string>
#include <fstream>
#include <vector>
using std::string, std::fstream, std::vector;

/**************************************************************************************
  klasa odpowiadająca za odkodowywanie pliku i jego zakodowanie po modyfikacji danych
**************************************************************************************/
class Code {
private:
    vector<string> content;
    fstream file;
    string line;
    string tmp;
    int codeSum;
public:
    int codePassword(const string& password);
    void code(vector<string> vec, const string& password, const string& path);
    vector<string> decode(const string& path, const string& password);
};

#endif //PROJEKT_CODE_H