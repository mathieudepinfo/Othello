#include "Damier.h"

using namespace std;

Damier::Damier(int setup[8][8],int cont[8][8])
{
    this->nbpion=0;
    for(int i(0);i<8;i++){
        for(int j(0);j<8;j++){
            this->cases[i][j]=setup[i][j];
            this->contigues[i][j]=cont[i][j];
            if(this->cases[i][j]!=0){
                this->nbpion++;
            }
        }
    }

}

int Damier::getV(int i,int j)
{

    return this->cases[i][j];
}

void Damier::setV(int new_val,int i,int j)
{
    this->cases[i][j]=new_val;
}

void Damier::affiche()
{
    for(int i(0);i<8;i++){
        cout<<i<<"|";
        for(int j(0);j<8;j++){
            if(this->cases[i][j]==0){
                cout<< "  | ";
            }
            else{
                cout<< this->cases[i][j]<<" | ";
            }


        }
        cout<<"\n";
    }

}



