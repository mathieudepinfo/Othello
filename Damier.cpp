#include "Damier.h"

using namespace std;

void Damier::init(Damier* damier,const int setup[8][8])
{
    for(int i(0);i<8;i++){
        for(int j(0);j<8;j++){
            damier->setV(setup[i][j],i,j);
            if(damier->getV(i,j)!=0){
                damier->iNp();
            }
        }
    }
}

Damier::Damier(const Damier& damier){
    init(this,damier.cases);
}

Damier::Damier(const int setup[8][8]){
    init(this,setup);
}

void Damier::affiche()
{
    for(int i(0);i<8;i++){
        cout<<i<<"|";
        for(int j(0);j<8;j++){
            if(this->getV(i,j)==0){
                cout<< "  | ";
            }
            else{
                cout<< this->getV(i,j)<<" | ";
            }
        }
        cout<<"\n";
    }
}



