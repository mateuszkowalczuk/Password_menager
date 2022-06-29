#ifndef PROJEKT_APPLICATION_H
#define PROJEKT_APPLICATION_H
#include "Select.h"
#include "Check.h"
#include "Code.h"
#include "Actions.h"
#include <iostream>
#include <fstream>
#include <vector>
using std::string, std::fstream, std::vector;

/*************************************************************************************************************
  główna klasa aplikacji dostarczająca metode, w której są wykonywane wszystkie operacje na pliku z hasłami
*************************************************************************************************************/
class Application {
private:
    Select select;
    Check check;
    Code code;
    vector<string> content;
    Actions action;
    string path;
    string password;
    int userChoice;
    bool application;
public:
    void start();
};

#endif //PROJEKT_APPLICATION_H