#include "IterativeDeepening.h"
#include <thread>

using namespace std;

int ID(time_t tmax,char pmax,Damier& damier,Table& ttable,int joueur){

    int prof(1),mc;
    int score[2]={0,0};
    bool time_left(true);
    time_t t0=time(NULL);

    while(time_left){
        //on fait une copie de ttable en cas d'arrêt prématuré de MTD-f
        Table* table_tmp=new Table(ttable);
        try{
            MTD(score[prof%2],ttable,damier,joueur,prof,tmax,t0);
        }
        catch(char const* fin){
            ttable=*table_tmp;

        }

        mc=ttable[hashage(damier,joueur)%TABLE_SIZE]->getC();

        delete table_tmp;

        if(prof>=pmax || (time(NULL)-t0)>tmax){
            time_left=false;
        }

        printf("prof :%d meilleurcoup :%d vh :%d vb:%d\n",prof,mc,ttable[hashage(damier,joueur)%TABLE_SIZE]->getU(),ttable[hashage(damier,joueur)%TABLE_SIZE]->getL());

        printf("%d ",ttable[hashage(damier,joueur)%TABLE_SIZE]->getC());

        printf("\n");
        prof++;

    }

    printf("pmax : %d\n",prof-1);
    return mc;
}
