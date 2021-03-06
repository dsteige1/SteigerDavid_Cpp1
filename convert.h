#include <iostream>
#include <fstream>

using namespace std;

class ClattToken {
    private:
        int anzahlAtt;
        char *attName[10];
        char *attValue[10];
    public:
        int getAttList(char *eingabe);
        char *zeigeAttName(int id) {return attName[id];}
        char *zeigeAttWert(int id) {return attValue[id];}
        int zahlAtt() {return anzahlAtt;}
};

class ClToken {
    private:
        void druckeXMLEbene(int ebene, char ausgabe[30]);
        char tokenName[64];
        ClToken *tokenChild;
        ClToken *tokenSibling;
        char *tokenInhalt;
    public:
        ClToken();
        char *name() { return tokenName; }
        ClToken *child() { return tokenChild; }
        char *inhalt() { return tokenInhalt; }
        void convertData(int ebene, char ausgabe[30]);
        int getToken(ifstream &datei);
        ClattToken att;
};

enum zustand {istStartTag,
              istEndTag,
              zwischenTags,
              inNamen,
              erwarteAttributWert,
              erwarteAttributNamen,
              verarbeiteAttributWert
             };

int menu();
