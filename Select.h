#ifndef PROJEKT_SELECT_H
#define PROJEKT_SELECT_H
#include <string>
#include <fstream>
using std::string, std::fstream;

/*****************************************************************************
  klasa dostarczająca ścieżkę do wybranego pliku głównej metodzie aplikacji
*****************************************************************************/
class Select {
private:
    int choice;
    bool correct;
    string absolutePath;
    fstream file;
    int typeChoice();
    string fileChoice();
    string path();
public:
    string userChoice();
};

#endif //PROJEKT_SELECT_H