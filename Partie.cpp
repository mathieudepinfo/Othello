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

    Damier* dam=new Damier(setup);

    //seeds pour la fonction de hashage, rotations=meme cle
    int randvals[8][8][2];
    int x;
    srand (time(NULL));
    for (int i(0);i<4;i++){
        for(int j(0);j<4;j++){
            for(int k(0);k<2;k++){
                x=rand();
                randvals[i][j][k]=x;
                randvals[7-i][j][k]=x;
                randvals[7-i][7-j][k]=x;
                randvals[i][7-j][k]=x;
            }
        }
    }

    Table* ttable=new Table(randvals);

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
            coup=joueCoupIA(randvals,ttable,dam,joueur,4);

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

void IAVSIA()
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

    Damier* dam=new Damier(setup);

    //seeds pour la fonction de hashage
    int randvals[8][8][2];
    srand (time(NULL));
    for (int i(0);i<8;i++){
        for(int j(0);j<8;j++){
            for(int k(0);k<2;k++){
                randvals[i][j][k]=rand();
            }
        }
    }

    Table* ttable=new Table(randvals);

    int joueur=1;
    int i(0),j(0);
    int coup(0);
    string s;
    while(!testFin(dam)){

        dam->affiche();

        //profondeur de 8
        if(joueur==2){
        printf("le rapide \n");
        coup=joueCoupIA(randvals,ttable,dam,joueur,8);
        }
        else{
            printf("le lent \n");
            coup=joueCoupIA2(dam,joueur,8);
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

    cout<<score(dam,2)<<"\n";

    delete ttable;
    delete dam;

}
