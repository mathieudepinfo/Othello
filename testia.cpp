#include "testia.h"

void test(){

    int setup[8][8]=
    {
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
    };

    int cont[8][8]=
    {
        {3,5,5,5,5,5,5,3},
        {5,8,8,8,8,8,8,5},
        {5,8,8,8,8,8,8,5},
        {5,8,8,8,8,8,8,5},
        {5,8,8,8,8,8,8,5},
        {5,8,8,8,8,8,8,5},
        {5,8,8,8,8,8,8,5},
        {3,5,5,5,5,5,5,3},
    };

    Table* table1=new Table();
    Table* table2=new Table();
    int c1(-10),c2(-10),v1(0),v2(0),prof(0),joueur(0),cpt(0),next(0),k(0),l(0);
    int seed=(int)time(NULL);
    srand (seed);
    printf("AB_memory vs AB_MTD , seed :%d \n",seed);

    Damier* damier2=new Damier(setup);
    for(int i=0;i<100;i++){
        joueur=1+rand()%2;
        k=rand()%8;
        l=rand()%8;
        joueCoup(*damier2,joueur,k,l);
        for(int i(0);i<8;i++){
            for(int j(0);j<8;j++){

                if(estValide(*damier2,joueur,i,j)){
                    printf("%d%d ",i,j);
                }
            }
        }
        printf("\n");
        prof=5;//+rand()%5;

        c1=ID(3,prof-1,*damier2,*table2,joueur);
        v1=(*table2)[hashage(*damier2,joueur)%TABLE_SIZE]->getL();
        table2->reset();

        v2=alphaBetaTT(*table1,*damier2,joueur,prof,MINI,MAXI,prof);
        c2=(*table2)[hashage(*damier2,joueur)%TABLE_SIZE]->getC();
        table1->reset();
        printf("%d ",i);
        if(c1!=c2){
            printf("\n");
            damier2->affiche();
            printf("ABm coup:%d val: %d , MTD coup: %d vbasse: %d \n joueur :%d prof :%d \n",c2,v2,c1,v1,joueur,prof);
            sleep(1);
            cpt++;
        }
    }

    printf(" \n taux de différence : %f \n",((float)cpt)/100.0);

}
