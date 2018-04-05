#include <iostream>
#include <fstream>
#include <string.h>
#include "scan.h"

using namespace std;

int printTXT(){

    ifstream eingabeTXT;
    ClscanData *scan;

    eingabeTXT.open("cars_scan.txt");

    scan = new ClscanData();
    scan->ladeTXT(eingabeTXT);
    scan->druckeData();

    eingabeTXT.close();

    cout << endl << "__________________________________________" <<endl;
    menu();

    return 0;
}

void ClscanData::ladeTXT(ifstream& scan){
    char zeichen;
    char puffer[100];
    int zaehler=0;
    enum zustandTXT {verarbeiteID, verarbeiteOrt, verarbeiteKm};
    enum zustandTXT zustand = verarbeiteID;

    for(scan.get(zeichen); !scan.eof(); scan.get(zeichen)){
        switch(zeichen){
        case ';':
            if (zustand==verarbeiteID){
                zustand = verarbeiteOrt;
                puffer[zaehler]='\0';
                ID[anzahlScans] = new char[zaehler+1];
                strcpy(ID[anzahlScans],puffer);
                zaehler=0;
            }
            else if (zustand==verarbeiteOrt){
                zustand = verarbeiteKm;
                puffer[zaehler]='\0';
                ort[anzahlScans] = new char[zaehler+1];
                strcpy(ort[anzahlScans],puffer);
                zaehler=0;
            }
            break;
        case '\n':
            zustand = verarbeiteID;
            puffer[zaehler]='\0';
            KM[anzahlScans] = new char[zaehler+1];
            strcpy(KM[anzahlScans],puffer);
            zaehler=0;
            anzahlScans++;
            break;
        default:
            puffer[zaehler] = zeichen;
            zaehler++;
            break;
        }
    }
}

void ClscanData::druckeData(){
    for (int i=0; i<anzahlScans; i++){
        cout << "Neuer Scan: " << endl;
        cout << "  ID: " << zeigeID(i) << endl;
        cout << "  Ort: " << zeigeOrt(i) << endl;
        cout << "  km: " << zeigeKM(i) << endl;
    }
}
