#include <iostream>
#include <fstream>
#include <string.h>
//#include "token.h"
#include "scan.h"
#include "convert.h"

using namespace std;

/*int ClattToken::getAttList(char *eingabe) {
    char puffer[100];
    int zaehler;
    zustand zustand;

    for (zaehler=0,zustand=inNamen, anzahlAtt=0; *eingabe!='\0'; eingabe = eingabe + 1){
        switch(*eingabe){
        case ' ':
            if (zustand == inNamen){
                zustand = erwarteAttributNamen;
                *eingabe='\0';
                zaehler=0;
            }
            else if (zustand == verarbeiteAttributWert){
                puffer[zaehler] = *eingabe;
                zaehler++;
            }
            break;
        case '=':
            if (zustand == erwarteAttributNamen){
                zustand = erwarteAttributWert;
                puffer[zaehler] = '\0';
                attName[anzahlAtt] = new char[zaehler+1];
                strcpy(attName[anzahlAtt],puffer);
                zaehler=0;
            }
            else if (zustand == verarbeiteAttributWert){
                puffer[zaehler] = *eingabe;
                zaehler++;
            }
            else cout << "Fehlerhaftes Zeichen! '='" << endl;
            break;
        case '"':
            if (zustand == erwarteAttributWert){
                zustand = verarbeiteAttributWert;
                zaehler = 0;
            }
            else if (zustand == verarbeiteAttributWert){
                zustand = erwarteAttributNamen;
                puffer[zaehler] = '\0';
                attValue[anzahlAtt] = new char[zaehler+1];
                strcpy(attValue[anzahlAtt],puffer);
                zaehler=0;
                anzahlAtt++;
            }
            else cout << "Fehlerhaftes Zeichen! '\"'" << endl;
            break;
        default:
            puffer[zaehler] = *eingabe;
            zaehler++;
            break;
        }
    }
    return 1;
}*/


/*int ClToken::getToken(ifstream &datei){
    int zaehler;
    zustand zustand;
    char zeichen;
    char puffer[100];
    ClToken *child;

    for (zaehler=0;;){
        datei.get(zeichen);
        if(datei.eof()){
            if(*tokenName == '\0' && tokenChild == NULL && tokenInhalt == NULL)
                return 0;
            return 1;
        }
        switch(zeichen){
        case '<':
            datei.get(zeichen);
            if(zeichen=='/'){
                zustand = istEndTag;
                if(zaehler!=0){
                    puffer[zaehler]='\0';
                    tokenInhalt = new char[zaehler+1];
                    strcpy(tokenInhalt,puffer);
                }
            }
            else{
                datei.putback(zeichen);
                if(*tokenName != '\0'){
                    datei.putback('<');
                    if(tokenChild == NULL){
                        tokenChild=new ClToken;
                        tokenChild->getToken(datei);
                    }
                    else{
                        for(child=tokenChild;;child=child->tokenSibling){
                            if(child->tokenSibling==NULL){
                                child->tokenSibling=new ClToken;
                                child->tokenSibling->getToken(datei);
                                break;
                            }
                        }
                    }
                }
                else zustand=istStartTag;
            }
            zaehler=0;
            break;
        case '>':
            puffer[zaehler]='\0';
            if(zustand == istEndTag){
                strcpy(tokenName,puffer);
                return 1;}
            if(zustand == istStartTag){
                att.getAttList(puffer);
                strcpy(tokenName,puffer);
            }
            zaehler=0;
            break;
        case '\n':
            break;
        default:
            puffer[zaehler]=zeichen;
            zaehler++;
            break;
        }
    }
}*/

void ClToken::convertData(int ebene){
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
}

/*void ClscanData::verarbeiteTXT(ifstream& scan){
    char zeichen;
    char puffer[100];
    int zaehler = 0;
    enum zustandTXT {verarbeiteID, verarbeiteOrt, verarbeiteKm};
    enum zustandTXT zustand = verarbeiteID;

    for(scan.get(zeichen); !scan.eof(); scan.get(zeichen)){
        switch(zeichen){
        case ';':
            if (zustand == verarbeiteID){
                zustand = verarbeiteOrt;
                puffer[zaehler] ='\0';
                ID[anzahlScans] = new char[zaehler+1];
                strcpy(ID[anzahlScans],puffer);
                zaehler=0;
            }
            else if (zustand == verarbeiteOrt){
                zustand = verarbeiteKm;
                puffer[zaehler] ='\0';
                ort[anzahlScans] = new char[zaehler+1];
                strcpy(ort[anzahlScans],puffer);
                zaehler=0;
            }
            break;
        case '\n':
            zustand = verarbeiteID;
            puffer[zaehler] ='\0';
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
}*/

int convert(){
    ifstream eingabeXML;
    ClToken *token;

    eingabeXML.open("databank_cars.xml");

    token=new ClToken();
    if (token->getToken(eingabeXML) != 0){
        token->convertData(0);
    }

    eingabeXML.close();

    cout << "__________________________________________" <<endl;
    menu();

    return 0;
}
