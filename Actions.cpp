#include "Actions.h"
#include "Code.h"
#include <iostream>
#include <ctime>
using std::cout, std::cin, std::endl;
Code code;

/*************************************************************************************
  metoda wyszukiwająca, wyświetlająca hasła, które posiadają w nazwie podany parametr
*************************************************************************************/
void Actions::search(vector<string> vec) {
    if (!vec[1].empty()){
        cout<<"What password you want to find? Enter parameter: ";
        cin>>parameter;
        cout<<"Finded passwords: "<<endl;
        for (int i = 1; i < vec.size(); ++i) {
            tmp = "";
            char tab[vec[i].size()];
            strcpy(tab, vec[i].c_str());
            for (int j = 0; j < vec[i].size(); j++){
                if (tab[j] != '\n' && j != 0) tmp += tab[j];
                if (tmp.length() > 1 && tmp == parameter) {
                    cout<<vec[i]<<endl;
                    j = vec[i].size();
                }
            }
        }
        cout<<endl;
    } else cout<<"There are no password to search. Enter passwords first\n"<<endl;
}

/*********************************************************
  metoda wyświetlająca posortowaną po nazwie listę haseł
*********************************************************/
void Actions::sort(vector<string> vec) {
    if (!vec[1].empty()) {
        std::sort(vec.begin()+1, vec.end());
        cout<<"Sorted list of passwords by names: "<<endl;
        for (int i = 1; i < vec.size(); ++i)
            cout<<vec[i]<<endl;
        cout<<endl;
    } else cout<<"There are no password to sort. Enter passwords first\n"<<endl;
}

/**************************************
  metoda dodająca nowe hasło do pliku
**************************************/
string Actions::addPassword(vector<string> vec, string password, string path) {
    if (vec[0].empty()) {
        cout<<"There are no categories to choose. Add category first\n"<<endl;
        return "";
    } else {
        content = "";

        /** wprowadzanie nazwy do hasła **/
        cout<<"Enter name for password: ";
        content += add();

        /** wprowadzanie lub wybranie wygenerowanego hasła **/
        content += passwordChoice();

        /** wybranie kategorii **/
        cout<<vec[0]<<endl;
        cout<<"Enter one of category from list: ";
        condition = true;
        char categories[vec[0].length() + 1];
        strcpy(categories, vec[0].c_str());
        int index = 0;
        while (condition){
            if (index > 0) cout<<"Incorrect category. Try again: ";
            cin>>in;
            category = "";
            for (int i = 0; i < vec[0].length(); i++){
                if (categories[i] != ' ') category += categories[i];
                if (in == (string)category) {
                    condition = false;
                    content += "\n" + in;
                    i = vec[0].length();
                }
                if (categories[i] == ' ') category = "";
            }
            index++;
        }

        /** opcja wybrania strony **/
        cout<<"You want to enter website?(y/n) ";
        condition = true;
        while (condition) {
            cin >> playerChoice;
            if (playerChoice == 'y') {
                cout << "Enter website: ";
                content += add();
                condition = false;
            } else if (playerChoice == 'n') condition = false;
            else cout<<"Wrong character. Select again: ";
        }

        /** opcja wybrania loginu **/
        cout<<"You want to enter login? (y/n) ";
        condition = true;
        while (condition) {
            cin >> playerChoice;
            if (playerChoice == 'y') {
                cout << "Enter login: ";
                content += add();
                condition = false;
            } else if (playerChoice == 'n') condition = false;
            else cout<<"Wrong character. Select again: ";
        }

        /** zakodowanie nowego hasła **/
        vec.push_back(content);
        code.code(vec, password, path);
        cout<<endl;

        return content;
    }
}

/***********************************************************************
  metoda pozwalająca na wprowadzanie lub wybranie wygenerowanego hasła
***********************************************************************/
string Actions::passwordChoice() {
    srand(time(nullptr));
    tmp = "";
    condition = true;
    int intIn;
    while(condition){
        cout<<"1. Enter password\n2. Generate password\nSelect number: ";
        cin>>intIn;
        if (intIn == 1 || intIn == 2) condition = false;
        else cout<<"Wrong value. Try again: ";
    }
    switch (intIn) {
        /** podanie własnego hasła **/
        case 1 : {
            condition = true;
            while (condition) {
                cout << "Enter password: ";
                cin >> tmp;

                if (tmp.length() <= 4) {
                    bool con = true;
                    while (con) {
                        cout << "Password is weak. You want to change them?(y/n) ";
                        cin >> in;
                        if (in == "y") {
                            con = false;
                        }
                        else if (in == "n") {
                            con = false;
                            condition = false;
                        }
                        else cout<<"Wrong character. Try again: ";
                    }
                } else if (tmp.length() >= 5 && tmp.length() <= 8) {
                    bool con = true;
                    while (con) {
                        cout << "Password is moderate. You want to change them?(y/n) ";
                        cin >> in;
                        if (in == "y") {
                            con = false;
                        }
                        else if (in == "n") {
                            con = false;
                            condition = false;
                        }
                        else cout<<"Wrong character. Try again: ";
                    }
                } else {
                    cout<<"Password is strong"<<endl;
                    condition = false;
                }
            }
            return "\n" + tmp;
        }
        /** wygenerowanie hasła **/
        case 2 : {
            int number;
            string capital, small, special, choice;

            string pass = "0123456789";

            cout<<"Choose parameters. Number of characters: ";
            condition = true;
            while (condition){
                cin>>number;
                if (number < 8 || number > 20) cout<<"Password is to short/long. Try again: ";
                else condition = false;
            }
            cout<<"Capital letters?(y/n): ";
            condition = true;
            while (condition){
                cin>>capital;
                if (capital == "y") {
                    pass += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
                    condition = false;
                }
                else if (capital == "n") condition = false;
                else cout<<"Incorrect character. Try again: ";
            }
            cout<<"Small letters?(y/n): ";
            condition = true;
            while (condition){
                cin>>small;
                if (capital == "y") {
                    pass += "abcdefghijklmnopqrstuvwxyz";
                    condition = false;
                }
                else if (capital == "n") condition = false;
                else cout<<"Incorrect character. Try again: ";
            }
            cout<<"Special letters?(y/n): ";
            condition = true;
            while (condition){
                cin>>special;
                if (capital == "y") {
                    pass += "!@#$%^&*?/";
                    condition = false;
                }
                else if (capital == "n") condition = false;
                else cout<<"Incorrect character. Try again: ";
            }

            condition = true;
            while (condition){
                cout<<"Generated password: ";
                for (int i = 0; i < number; ++i) {
                    tmp += pass[rand()%pass.length()];
                }

                cout<<tmp<<"\nTake them(y) or generated again(n)?";
                bool secCon = true;
                while (secCon){
                    cin>>choice;
                    if (choice == "y") {
                        secCon = false;
                        condition = false;
                    }
                    else if (choice == "n") {
                        secCon = false;
                        tmp = "";
                    }
                    else cout<<"Incorrect character. Try again: ";
                }
            }
            return "\n" + tmp;
        }
    }
}

/***************************************
  metoda zwracająca wprowadzoną wartość
***************************************/
string Actions::add() {
    cin>>in;
    return "\n" + in;
}

/***************************************
  metoda wyświetlająca zawartość pliku
***************************************/
void Actions::editPassword(vector<string> vec) {
    for (int i = 0; i < vec.size(); ++i)
        if (i == 0) cout<<(i+1)<<". Categories: "<<vec[i]<<endl;
        else cout<<(i+1)<<". Password: "<<vec[i]<<endl;
    cout<<endl;
}

/*********************************
  metoda usuwająca wybrane hasło
*********************************/
vector<string> Actions::removePassword(vector<string> vec, string password, string path) {
    if (!vec[1].empty()) {
        for (int i = 1; i < vec.size(); ++i) {
            cout<<i<<"."<<vec[i]<<endl;
        }

        /** wybranie hasła do usunięcia i zatwierdzenie usunięcia **/
        condition = true;
        while (condition){
            cout<<"Enter password to remove: ";
            cin>>in;
            for (int i = 1; i < vec.size(); ++i) {
                tmp = "";
                char tab[vec[i].size()];
                strcpy(tab, vec[i].c_str());
                for (int j = 0; j < vec[i].size(); j++){
                    if (j-1 != in.length()) {
                        tmp += tab[j];
                    } else j = vec[i].size();
                }
                string decision;
                if ("\n" + in == tmp) {
                    cout<<"Are you sure?(y/n) ";
                    bool c = true;
                    while (c){
                        cin>>decision;
                        if (decision == "y") {
                            cout<<"\nPasssword removed"<<endl;
                            condition = false;
                            c = false;
                        }
                        else if (decision == "n") {
                            condition = true;
                            c = false;
                        }
                        else cout<<"Incorrect character. Try again: ";
                    }

                    if (!condition) {
                        vec.erase(vec.begin()+i);
                        i--;
                    }
                }
            }
        }

        /** zakodowanie **/
        code.code(vec, password, path);
        cout<<endl;

        return vec;
    } else {
        cout<<"There are no password to remove. Enter password first\n"<<endl;
        return vec;
    }
}

/********************************
  metoda dodąca nową kategorię
********************************/
string Actions::addCategory(vector<string> mainVector, const string& password, const string& path){
    if (!mainVector[0].empty()) {
        cout<<"Current categories: "<<mainVector[0]<<"\nEnter new category: ";

        /** sprawdzenie czy kategoria istnieje i jeśli tak to dodanie jej do wektora i zakodowanie w pliku **/
        condition = true;
        char categories[mainVector[0].length() + 1];
        strcpy(categories, mainVector[0].c_str());
        while (condition){
            condition = false;
            cin>>in;
            category = "";
            for (int i = 0; i < mainVector[0].length(); i++){
                if (categories[i] != ' ') category += categories[i];
                if (in == (string)category) {
                    condition = true;
                    cout<<"Category already exists. Try again: ";
                    i = mainVector[0].length();
                }
                if (categories[i] == ' ') category = "";
            }
        }
        mainVector[0] += in + " ";
        code.code(mainVector, password, path);

        return mainVector[0];
    }
    /** pierwsze dodanie kategorii **/
    else {
        cout<<"Enter new category: ";
        cin>>in;
        mainVector[0] = in + " ";

        code.code(mainVector, password, path);

        return mainVector[0];
    }
}

/*************************************
  metoda usuwająca wybraną kategorię
*************************************/
vector<string> Actions::removeCategory(vector<string> vec, string password, string path) {
    if (!vec[0].empty()){
        tmp = "";

        /** zliczenie kategorii**/
        int index = 0;
        char categorie[vec[0].length() + 1];
        strcpy(categorie, vec[0].c_str());
        for (int i = 0; i < vec[0].length(); i++)
            if (categorie[i] == ' ') index++;

        /** stworzenie tablicy przechowującej kategorie **/
        string cat[index];
        index = 0;
        cout<<vec[0]<<"\nChoose from list category to remove: ";
        char categories[vec[0].length() + 1];
        strcpy(categories, vec[0].c_str());
        for (int i = 0; i < vec[0].length(); i++){
            if (categories[i] != ' ') tmp += categories[i];
            else {
                cat[index++] = tmp;
                tmp = "";
            }
        }

        /** wybranie kategorii do usunięcia i sprawdzenie czy istnieje tak w tablicy**/
        condition = true;
        while (condition){
            cin>>in;
            for (int i = 0; i < index; ++i) {
                if (in == cat[i]) condition = false;
            }
            if (condition) cout<<"Incorrect category. Try again: ";
        }

        /** dostarczenie kategorii jakie zostały**/
        tmp = "";
        for (int i = 0; i < index; ++i)
            if (in != cat[i]) tmp += cat[i] + " ";

        /** zakodowanie**/
        vec[0] = tmp;
        code.code(vec, password, path);

        return vec;
    } else {
        cout<<"No categories to remove!"<<endl;
        return vec;
    }
}