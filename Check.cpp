#include "Check.h"
#include <iostream>
#include <vector>
using std::cout, std::cin, std::endl, std::getline;

/************************************************************
  metoda dostarczająca hasło wprowadzone przez użytkownika
************************************************************/
string Check::password() {
    cout<<"Enter password: ";
    cin>>userPassword;
    cout<<endl;
    return userPassword;
}

/****************************
  metoda obsługi timestampa
****************************/
void Check::timestamp(const string& path) {
    getTimestamp(path);
    setTimestamp(path);
}

/***************************************************
  metoda zwracająca timestamp ostatniego logowania
***************************************************/
void Check::getTimestamp(const string& path) {
    lastTimestamp = "";

    /** odczytanie timestampa z pierwszych 6 linijek pliku **/
    file.open(path,std::ios::in);
    if(file.is_open()){
        string line;
        int index = 0;
        while (getline(file,line) && index++ != 6)
            lastTimestamp += line[0];
        file.close();
    }

    /** wyświetlenie timestampa **/
    if (!lastTimestamp.empty()) {
        char time[lastTimestamp.length() + 1];
        strcpy(time, lastTimestamp.c_str());
        cout << "timestamp - ";
        for (int i = 0; i < lastTimestamp.length(); i++) {
            if (i == 2 || i == 4) cout << ":";
            cout << time[i];
        }
        cout << endl;
    } else cout<<"First file open, timestamp does not exist"<<endl;
}

/************************************************************
  metoda ustawiająca timestamp na czas bieżącego zalogowania
*************************************************************/
void Check::setTimestamp(const string& path) {

    /** dostarczenie wartości z czasem **/
    time_t currectTime = time(nullptr);
    tm *lt = localtime(&currectTime);
    string h, m, s;
    h = std::to_string(lt->tm_hour);
    if (h.length() == 1) {
        string tmp = h;
        h = "0" + tmp;
    }
    m = std::to_string(lt->tm_min);
    if (m.length() == 1) {
        string tmp = m;
        m = "0" + tmp;
    }
    s = std::to_string(lt->tm_sec);
    if (s.length() == 1) {
        string tmp = s;
        s = "0" + tmp;
    }
    string setTime = h+m+s;

    /** zapełnienie wektora wartościami z pliku **/
    std::vector<string> vec;
    file.open(path,std::ios::in);
    if(file.is_open()){
        string line;
        while (getline(file,line))
            vec.push_back(line);
        file.close();
    }

    /** uzupelnienie wektora do liczby 6 lini **/
    if (vec.size() < setTime.length()) {
        int g = setTime.length() - vec.size();
        for (int i = 0; i < g; ++i)
            vec.push_back("");
    }

    /** dodanie wartości timestampa do początku kolejnych początku linii wektora z usunięciem starych wartości timestampa **/
    char time[setTime.length() + 1];
    strcpy(time, setTime.c_str());
    for (int i = setTime.length() - 1; i >= 0; i--){
        string newTmp, tmp = vec[i];
        vec[i] = time[i];
        char removeFirstLine[tmp.length() + 1];
        strcpy(removeFirstLine, tmp.c_str());
        for (int i = 0; i < tmp.length(); i++)
            if (i != 0) newTmp += removeFirstLine[i];
        tmp = newTmp;
        vec[i] = time[i] + tmp;
    }

    /** przygotowanie zmiennej odpowiadającej nowemu zapisawi w pliku **/
    string con;
    for (int i = 0; i < vec.size(); ++i)
        con += vec[i] + "\n";

    /** nadpisanie zawartości z nowym timestampem do pliku **/
    file.open(path,std::ios::out);
    if(file.is_open()){
        file<<con;
        file.close();
    }
}