#include "IA_main.h"
#include "IA_ab.h"
#define MAXI 2147483647
#define MINI -2147483648

using namespace std;

int alphaBeta2(Damier* damier,int joueur,char prof,int alpha,int beta,bool maxnode)
{

    int val;

    if(prof==0){
        return heuristique(damier,joueur);
    }

    if(maxnode){
        val=MINI;
        for(int i(-1);i<8;i++){
            for(int j(0);j<8;j++){//pas optimal

                if(estValide(damier,joueur,i,j)){

                    if(val<beta){
                        Damier* fils=new Damier(*damier);
                        joueCoup(fils,joueur,i,j);
                        val=maxi(val,alphaBeta2(fils,joueur,prof-1,alpha,beta,false));
                        alpha=maxi(alpha,val);
                        delete fils;
                    }
                    else{//on arrete la le noeud ne vaudra pas plus de beta
                        i=8;
                        j=8;


                    }
                }

            }
        }

    }
    else{ //noeud min
        val=MAXI;
        for(int i(-1);i<8;i++){
            for(int j(0);j<8;j++){//pas optimal

                if(estValide(damier,3-joueur,i,j)){

                    if(val>alpha){
                        Damier* fils=new Damier(*damier);
                        joueCoup(fils,3-joueur,i,j);
                        val=mini(val,alphaBeta2(fils,joueur,prof-1,alpha,beta,true));
                        beta=mini(val,beta);
                        delete fils;
                    }
                    else{
                        i=8;
                        j=8;

                    }
                }
            }
        }
    }



    return val;
}

int joueCoupIA2(Damier* damier,int joueur,char prof)
{
    int vmax(MINI),val(MINI);
    int alpha(MINI),beta(MAXI);
    int meilleurcoup=-2;


    for(int i(-1);i<8;i++){
        for(int j(0);j<8;j++){

            if(estValide(damier,joueur,i,j)){

                if(val<beta){
                    Damier* fils=new Damier(*damier);
                    joueCoup(fils,joueur,i,j);
                    val=alphaBeta2(fils,joueur,prof-1,alpha,beta,false);
                    if(val>vmax){
                        vmax=val;
                        meilleurcoup=i*10+j;
                    }
                    alpha=maxi(alpha,vmax);
                    delete fils;
                }
                else{//on arrete la le noeud ne vaudra pas plus de beta
                    i=8;
                    j=8;

                }
            }
        }
    }
    printf("%d \n",vmax);
    return meilleurcoup;
}
