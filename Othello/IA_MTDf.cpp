#include "IA_MTDf.h"

using namespace std;

int MTD(int& f,Table& ttable,Damier& root,int joueur,char prof, int (heuristique)(Damier&, int),time_t tmax,time_t t0)
{
    int val=f;
    int haute=MAXI;
    int basse=MINI;
    int x;

    while(haute > basse)
    {
        if(val == basse){
            x=val+1;
        }
        else{
            x=val;
        }
        //on lance un alphabeta avec une fenetre nulle, il retourne donc forcement une upperbound ou une lowerbound
        val=alphaBetaTT(ttable,root,joueur,prof,x-1,x,heuristique,prof);

        if(val<x){
            haute=val;
        }
        else{
            basse=val;
        }

        //si on a plus de temps on arrete, attention à ce stade val et ttable peuvent avoir été modifiés sans avoir de signification
        if(tmax<time(NULL)-t0){
            throw "fini";
        }
    }

    f=val;

    return val;
}
