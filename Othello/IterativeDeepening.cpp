#include "IterativeDeepening.h"

using namespace std;

int ID(time_t tmax,char pmax,Damier& damier,Table& ttable,int joueur){

    int prof(1),mc;		
    int score[2]={0,0}; //score pour les profondeurs paires et impaires
    bool time_left(true);
    time_t t0=time(NULL);

    while(time_left){
        //on fait une copie de ttable en cas d'arrêt prématuré de MTD-f
        Table* table_tmp=new Table(ttable);
        try{
			if (damier.getNp() < 50) {
				MTD(score[prof % 2], ttable, damier, joueur, prof,heuristiqueMilieuDePartie, tmax, t0);
			}
			else {
				MTD(score[prof % 2], ttable, damier, joueur, prof, heuristiqueFinDePartie, tmax, t0);
			}
        }
        catch(char const* fin){ //fin prématurée quand on arrive ici
			std::cout << fin << std::endl;
            ttable=*table_tmp;
        }

        mc=ttable[hashage(damier,joueur)%TABLE_SIZE]->getC(); //on récupère le meilleur coup dans la table

        delete table_tmp;

        if(prof>=pmax || (time(NULL)-t0)>tmax){ //condition d'arrêt
            time_left=false;
        }

        printf("prof :%d meilleurcoup :%d vh :%d vb:%d\n",prof,mc,ttable[hashage(damier,joueur)%TABLE_SIZE]->getU(),ttable[hashage(damier,joueur)%TABLE_SIZE]->getL());

        printf("%d\n ",ttable[hashage(damier,joueur)%TABLE_SIZE]->getC());

        printf("\n");
        prof++;

    }

    printf("pmax : %d\n",prof-1);
    return mc;
}
