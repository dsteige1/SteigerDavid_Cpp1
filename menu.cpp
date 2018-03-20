#include <iostream>
#include "header.h"

using namespace std;

int menu(){
    char action;

    cout << "Please choose one of the following options" << endl;
    cout << "1.     [p]rint the xml" << endl;
    cout << "2.     p[r]int the txt" << endl;
    cout << "3.     [c]onvert the the data sets into new file" << endl;
    cout << "4.     [h]elp me!" << endl << endl;
    cout << "Your choice: ";
    cin >> action;

    switch(action){
    case 'p':
        printXML();
        break;
    case 'r':
        printTXT();
        break;
    case 'c':
        convert();
        break;
    case 'h':
        help();
        break;
    default:
        cout << endl << "###########################################" << endl;
        cout <<         "This is not an option. Try 'h' to get help." << endl;
        cout <<         "###########################################" << endl << endl;

        menu();

        break;
    }
    return 0;
}
