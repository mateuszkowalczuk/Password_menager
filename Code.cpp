#include "Code.h"
#include <iostream>
using std::cout, std::endl, std::getline;

/***************************************************************************
  metoda dostarczają sumę liczb reprezentujących pojedyncze litery hasła
***************************************************************************/
int Code::codePassword(const string& password) {
    codeSum = 0;
    char codeTab[password.length() + 1];
    strcpy(codeTab, password.c_str());
    for (int n = 0; n < password.length(); n++)
        codeSum += codeTab[n];
    return codeSum;
}

/*********************************************************************
  metoda kodująca i zwracająca do pliku jego zmodyfikowane wartości
*********************************************************************/
void Code::code(vector<string> vec, const string& password, const string& path) {

    /** przygotowanie wektora z timestampem **/
    std::vector<string> timeVec;
    file.open(path,std::ios::in);
    if(file.is_open()) {
        line = "";
        int index = 0;
        while (getline(file, line) && index++ != 6) {
            tmp = line[0];
            timeVec.push_back(tmp);
        }
        file.close();
    }

    /** przygotowanie wektora do zwrócenia przez połączenie wektora z timestampem i wektora z hasłami **/
    std::vector<string> retVec;

    int lenght = 0;
    if (vec.size() < timeVec.size()) lenght = timeVec.size() - vec.size();

    tmp = "";
    for (int i = 0; i < (vec.size() + lenght); i++)
        if (i < 6 && vec.size() > i) retVec.push_back(timeVec[i] + vec[i]);
        else if (i < 6) retVec.push_back(timeVec[i]);
        else retVec.push_back(vec[i]);

    /** zakodowanie zmienionych wartości w pliku **/
    tmp = "";
    for (int i = 0; i < retVec.size(); i++) {
        char tab[retVec[i].size()];
        strcpy(tab, retVec[i].c_str());
        for (int n = 0; n < retVec[i].size(); n++){
            if (i > 5 || n != 0) tmp += (char)(tab[n]+codePassword(password));
            else tmp += (char)(tab[n]);
        }
        tmp += "\n";
    }

    /** nadpisanie pliku z nowymi wartościami **/
    file.open(path,std::ios::out);
    if(file.is_open()){
        file<<tmp;
        file.close();
    }
}

/**********************************************************************
  metoda dekodująca plik po otworzeniu aplikacji i dostarczeniu pliku
**********************************************************************/
vector<string> Code::decode(const string& path, const string& password){

    /** odczyt wartości z pliku i zapisanie ich do wektora **/
    file.open(path,std::ios::in);
    if(file.is_open()){
        line = "";
        while (std::getline(file,line))
            content.push_back(line);
        file.close();
    }

    /** usunięcie z pierwszych 6 linijek timestampa **/
    for (int i = 0; i < 6; ++i) {
        tmp = "";
        char tab[content[i].size()];
        strcpy(tab, content[i].c_str());
        for (int n = 0; n < content[i].length(); n++)
            if (n != 0) tmp += tab[n];
        content[i] = tmp;
    }

    /** usunięcie pustych linijek **/
    vector<string> vecTmp;
    for (int i = 0; i < content.size(); ++i)
        if (!content[i].empty()) vecTmp.push_back(content[i]);
    content = vecTmp;

    /** podział na hasła **/
    vector<string> vecPass;
    if (content.size() == 0) vecPass.push_back("");
    else for (int i = 0; i < content.size(); ++i)
            vecPass.push_back(content[i] + " ");
    tmp = "";
    for (int i = 0; i < vecPass.size(); ++i)
        tmp += vecPass[i];

    /** odkodowanie wektora **/
    if (!tmp.empty()){
        for (int i = 0; i < vecPass.size(); ++i) {
            tmp = "";
            char cTab[vecPass[i].size()];
            strcpy(cTab, vecPass[i].c_str());
            for (int n = 0; n < vecPass[i].length(); n++)
                if (n != vecPass[i].length()-1) tmp += cTab[n]-codePassword(password);
            vecPass[i] = tmp;
        }
    }

    return vecPass;
}