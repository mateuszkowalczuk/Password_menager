#include "Application.h"
#include <iostream>
using std::cout, std::cin, std::endl;

/****************************
  główna metoda aplikacji
****************************/
void Application::start() {
    path = select.userChoice();
    password = check.password();
    check.timestamp(path);
    content = code.decode(path, password);

    application = true;
    while (application) {
        cout<<"1. Search passwords\n2. Sort passwords\n3. Add password\n4. Edit password\n5. Remove password\n"
              "6. Add category\n7. Remove category\n8. Exit\nSelect option: ";
        cin>>userChoice;
        cout<<endl;
        switch (userChoice) {
            case 1 : {
                action.search(content);
                break;
            }
            case 2 : {
                action.sort(content);
                break;
            }
            case 3 : {
                content.push_back(action.addPassword(content, password, path));
                break;
            }
            case 4 : {
                action.editPassword(content);
                break;
            }
            case 5 : {
                content = action.removePassword(content, password, path);
                break;
            }
            case 6 : {
                content[0] = action.addCategory(content, password, path);
                cout<<endl;
                break;
            }
            case 7 : {
                content = action.removeCategory(content, password, path);
                cout<<endl;
                break;
            }
            case 8 : {
                application = false;
                break;
            }
        }
    }
}