#include <iostream>
#include <fstream>
#include <string.h>
#include "scan.h"
#include "convert.h"

using namespace std;


/*void ClToken::convertData(int ebene){
    ifstream eingabeTXT;

    ClscanData *scan;

    eingabeTXT.open("cars_scan.txt");

    scan = new ClscanData();
    scan->verarbeiteTXT(eingabeTXT);

    eingabeTXT.close();

    druckeXMLEbene(ebene);
    cout << "<" << name();

    if (att.zahlAtt() > 0){
        for (int i = 0; i < att.zahlAtt(); i++){

            cout << " "<< att.zeigeAttName(i) << "=" << '"' <<  att.zeigeAttWert(i) << '"' << " ";

            for (int j=0; j<scan->anzahlScans; j++){
                if (!strcmp(scan->zeigeID(j), att.zeigeAttWert(i))){

                    cout << "location=" << '"' << scan->zeigeOrt(j) << '"' << " ";

                    cout << "km=" << '"' << scan->zeigeKM(j) << '"' ;
                }
            }
        }
    }

    if(tokenChild != NULL){
        cout << ">" << endl;
        tokenChild->convertData(ebene+1);
        druckeXMLEbene(ebene);
        cout << "</" << name() << ">" << endl;
    }
    else{
        cout << ">" << inhalt() << "</" << name() << ">" << endl;
    }

    if(tokenSibling != NULL) tokenSibling->convertData(ebene);

}

void ClToken::druckeXMLEbene(int ebene){
    while (ebene > 0){
        cout << "   ";
        ebene = ebene - 1;
    }
}*/

void ClToken::convertData(int ebene, char ausgabe[30]){
    ifstream eingabeTXT;
    ofstream output;

    ClscanData *scan;

    eingabeTXT.open("cars_scan.txt");

    scan = new ClscanData();
    scan->verarbeiteTXT(eingabeTXT);

    eingabeTXT.close();

    druckeXMLEbene(ebene, ausgabe);

    output.open(ausgabe, ios::app);

    //ios::app puts me into 'append-mode'.
    //Otherwhise the file would be overwritten every turn of the recursion.
    //I found that handy method here:
    //https://www.go4expert.com/articles/understanding-read-write-append-file-t29965/#append-files

    output << "<" << name();

    if (att.zahlAtt() > 0){
        for (int i = 0; i < att.zahlAtt(); i++){

            output << " "<< att.zeigeAttName(i) << "=" << '"' <<  att.zeigeAttWert(i) << '"' << " ";

            for (int j=0; j<scan->anzahlScans; j++){
                if (!strcmp(scan->zeigeID(j), att.zeigeAttWert(i))){

                    output << "location=" << '"' << scan->zeigeOrt(j) << '"' << " ";

                    output << "km=" << '"' << scan->zeigeKM(j) << '"' ;
                }
            }
        }
    }

    output.close();

    if(tokenChild != NULL){

        output.open(ausgabe, ios::app);

        output << ">" << endl;

        output.close();

        tokenChild->convertData(ebene+1, ausgabe);
        druckeXMLEbene(ebene, ausgabe);

        output.open(ausgabe, ios::app);

        output << "</" << name() << ">" << endl;

        output.close();
    }
    else{
        output.open(ausgabe, ios::app);

        output << ">" << inhalt() << "</" << name() << ">" << endl;

        output.close();
    }

    if(tokenSibling != NULL) tokenSibling->convertData(ebene, ausgabe);

}

void ClToken::druckeXMLEbene(int ebene, char ausgabe[30]){
    while (ebene > 0){
        ofstream output;

        output.open(ausgabe, ios::app);

        output << "   ";
        ebene = ebene - 1;

        output.close();
    }
}

int convert(){
    ifstream eingabeXML;
    ClToken *token;
    char outputName[20];

    cout << "Please type the name of the output-file (including suffix '.xml')." << endl;
    cout << "Name: ";
    cin >> outputName;

    eingabeXML.open("databank_cars.xml");

    token=new ClToken();
    if (token->getToken(eingabeXML) != 0){
        token->convertData(0, outputName);
    }

    eingabeXML.close();

    cout << "__________________________________________" <<endl;
    menu();

    return 0;
}
