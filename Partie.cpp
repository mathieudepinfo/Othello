#include "Partie.h"

using namespace std;
void playerVSIA(int player)
{
    //position initiale
    int setup[8][8]=
    {
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,1,2,0,0,0},
        {0,0,0,2,1,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
    };
    int cont[8][8]=
    {
        {3,5,5,5,5,5,5,3},
        {5,8,8,8,8,8,8,5},
        {5,8,7,6,6,7,8,5},
        {5,8,6,5,5,6,8,5},
        {5,8,6,5,5,6,8,5},
        {5,8,7,6,6,7,8,5},
        {5,8,8,8,8,8,8,5},
        {3,5,5,5,5,5,5,3},
    };

    Damier* dam=new Damier(setup,cont);
    Table* ttable=new Table();

    int joueur=1;
    int i(0),j(0);
    int coup(0);
    string s;
    while(!testFin(dam)){

        dam->affiche();
        if(joueur==player){
            do{
                getline(cin,s);
                coup=stoi(s);
                if(coup==-1){
                    i=-1;
                    j=0;
                }
                else{
                    i=coup/10;
                    j=coup%10;
                }

            }while(!estValide(dam,joueur,i,j));

        }
        else{
            //profondeur de 4
            coup=joueCoupIA(ttable,dam,joueur,4);

            if(coup<0){
                i=-1;
                j=0;
            }
            else{
                i=coup/10;
                j=coup%10;
            }
        }

        cout<< i<<" "<<j<<" "<<joueur<<"\n";
        joueCoup(dam,joueur,i,j);
        joueur=3-joueur;
    }

    delete ttable;
    delete dam;

}

void IAVSIA(int prof)
{

    //position initiale
    int setup[8][8]=
    {
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,1,2,0,0,0},
        {0,0,0,2,1,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
    };

    int cont[8][8]=
    {
        {3,5,5,5,5,5,5,3},
        {5,8,8,8,8,8,8,5},
        {5,8,7,6,6,7,8,5},
        {5,8,6,5,5,6,8,5},
        {5,8,6,5,5,6,8,5},
        {5,8,7,6,6,7,8,5},
        {5,8,8,8,8,8,8,5},
        {3,5,5,5,5,5,5,3},
    };

    Damier* dam=new Damier(setup,cont);

    Table* ttable=new Table();

    int joueur=1;
    int i(0),j(0);
    int coup(0);
    string s;
    while(!testFin(dam)){

        dam->affiche();

        if(joueur==2){
        printf("avec memoire \n");
        coup=joueCoupIA(ttable,dam,joueur,prof);
        }
        else{
            printf("sans memoire \n");
            coup=joueCoupIA2(dam,joueur,prof);
        }
        if(coup<0){
            i=-1;
            j=0;
        }
        else{
            i=coup/10;
            j=coup%10;
        }


        cout<< i<<" "<<j<<" "<<joueur<<"\n";
        joueCoup(dam,joueur,i,j);
        joueur=3-joueur;
    }
    dam->affiche();
    cout<<score(dam,2)<<"\n";

    delete ttable;
    delete dam;

}
