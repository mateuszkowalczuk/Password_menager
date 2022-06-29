#include "Select.h"
#include <iostream>
#include <filesystem>
#include <vector>
using std::cout, std::cin, std::endl;
namespace fs = std::filesystem;

/*****************************************************************************
  metoda dająca użytkownikowi wybór w jaki sposób chce dostarczyć ścieżke
*****************************************************************************/
int Select::typeChoice() {
    correct = false;
    while (!correct){
        cout<<"1. Choose File\n2. Enter absolute path\nSelect number: ";
        cin>>choice;
        if (choice == 1 || choice == 2) correct = true;
        else cout<<"Incorrect value. Try again!"<<endl;
    }
    return choice;
}

/**********************************************************
  główna metoda klasy dostarczająca wybraną ściężkę
***********************************************************/
string Select::userChoice() {
    switch (typeChoice()) {
        case 1:
            return fileChoice();
        case 2:
            return path();
    }
}

/*********************************************************
  metoda wybierająca jeden z plików z folderu programu
*********************************************************/
string Select::fileChoice() {
    int numberOfFiles = 0, index = 0;
    cout<<"\nFiles: "<<endl;

    /** zliczenie ilości pliów w folderze i ich wyświetlenie **/
    for (const auto& entry : fs::directory_iterator("/Users/mateuszkowalczuk/IdeaProjects/PJC/Projekt/Files"))
        cout<<++numberOfFiles<<". "<<entry.path()<<endl;

    /** stworzenie tablicy wypełnionej ścieżkami plików z folderu programu **/
    string files[numberOfFiles];
    for (const auto& entry : fs::directory_iterator("/Users/mateuszkowalczuk/IdeaProjects/PJC/Projekt/Files"))
        files[index++] = entry.path();

    /** wybranie pliku z folderu **/
    correct = false;
    while (!correct){
        cout<<"\nChoose file number: ";
        cin>>choice;
        if (choice >= 1 && choice <= numberOfFiles) correct = true;
        else cout<<"Incorrect number. Try again!"<<endl;
    }

    return files[choice-1];
}

/***************************************************
  metoda do wprowadzenia własnej ścieżki do pliku
***************************************************/
string Select::path() {
    correct = false;
    while (!correct){
        cout<<"\nEnter absolute path: ";
        cin>>absolutePath;
        file.open(absolutePath);
        if (file.is_open()) {
            file.close();
            correct = true;
        } else cout<<"Incorrect path. Try again!"<<endl;
    }
    return absolutePath;
}