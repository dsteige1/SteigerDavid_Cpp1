//#include <iostream>
#include <fstream>

using namespace std;

class ClscanData{
private:
    int anzahlScans;
    char *ID[10], *ort[20], *KM[10];
public:
    void druckeData();
    char *zeigeID(int id) {return ID[id];}
    char *zeigeOrt(int id) {return ort[id];}
    char *zeigeKM(int id) {return KM[id];}
    void verarbeiteTXT(ifstream&);
};
