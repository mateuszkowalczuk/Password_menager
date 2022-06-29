#ifndef PROJEKT_CHECK_H
#define PROJEKT_CHECK_H
#include <string>
#include <fstream>
using std::string, std::fstream;

/************************************************************************************************************
  klasa dostarczjąca do głównej metody gry hasło wpisane przez użytkownika i timestamp ostatniego logowania
************************************************************************************************************/
class Check {
private:
    string userPassword;
    string lastTimestamp;
    fstream file;
    void getTimestamp(const string& path);
    void setTimestamp(const string& path);
public:
    string password();
    void timestamp(const string& path);
};

#endif //PROJEKT_CHECK_H