#include "Damier.h"

using namespace std;

Damier::Damier(int setup[8][8])
{
    for(int i(0);i<8;i++){
        for(int j(0);j<8;j++){
            cases[i][j]=setup[i][j];
        }
    }
}

int Damier::getV(int i,int j)
{

    return cases[i][j];
}

void Damier::setV(int new_val,int i,int j)
{
    cases[i][j]=new_val;
}

void Damier::affiche()
{
    for(int i(0);i<8;i++){
        cout<<i<<"|";
        for(int j(0);j<8;j++){
            if(cases[i][j]==0){
                cout<< "  | ";
            }
            else{
                cout<< cases[i][j]<<" | ";
            }


        }
        cout<<"\n";
    }
}



