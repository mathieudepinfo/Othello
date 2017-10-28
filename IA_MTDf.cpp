#include "IA_MTDf.h"

int MTD(int f,Table* ttable,Damier* root,int joueur,char prof)
{
    int val=f;
    int haute=MAXI;
    int basse=MINI;
    int x;

    while(haute>basse)
    {
        if(val==basse){
            x=val+1;
        }
        else{
            x=val;
        }
        val=alphaBeta(ttable,root,joueur,prof,x-1,x);
        if(val<x){
            haute=val;
        }
        else{
            basse=val;
        }
        #ifdef DEBUG
        printf("b=%d  h=%d \n",basse,haute);
        #endif // DEBUG
        update(ttable);
    }

    return val;
}

void update(Table* ttable){


    for(int i(0);i<TABLE_SIZE;i++){
        if((*ttable)[i]->distance!=255 && (*ttable)[i]->vhaute!=(*ttable)[i]->vbasse){
            (*ttable)[i]->distance=255;
        }
    }
}
