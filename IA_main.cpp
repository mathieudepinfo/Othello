#include "IA_main.h"


using namespace std;

void possibilites(int coups[64][2],Damier& damier,int& n_coups,int joueur)
{
    n_coups=0;
    //on teste le passage de tour
    if(estValide(damier,joueur,-1)){
        n_coups++;
        coups[0][0]=-1;coups[0][1]=0;
        return;
    }
    else{

        for(int i(0);i<8;i++){
            for(int j(0);j<8;j++){
                if(estValide(damier,joueur,i,j)){
                    coups[n_coups][0]=i;coups[n_coups][1]=j;
                    n_coups++;
                }
            }
        }
    }
}

bool inList(int i,int j,int coups[64][2],int n_coups)
{
    for(int k=0;k<n_coups;k++){
        if(coups[k][0]==i && coups[k][1]==j){
            return true;
        }
    }
    return false;
}

void possibilites(int coups[64][2],Damier& damier,int& n_coups,int joueur,Table& ttable, unsigned int cle)
{
    n_coups=0;

    if(estValide(damier,joueur,-1)){
        n_coups++;
        coups[0][0]=-1;coups[0][1]=0;
        return;
    }

    if(ttable.isIn(cle) && ttable[cle]->getC()!=-10){

        coups[0][0]=ttable[cle]->getC()%10;
        coups[0][1]=ttable[cle]->getC()/10;
        n_coups++;
    }

    for(int i(0);i<8;i++){
        for(int j(0);j<8;j++){
            if(estValide(damier,joueur,i,j)){
                coups[n_coups][0]=i;coups[n_coups][1]=j;
                n_coups++;
            }
        }
    }
}

int heuristique(Damier& damier,int joueur)
{
    static int dir[4][2]={{-1,0},{1,0},{0,1},{0,-1}};
    static int coins[4][2]={{0,0},{0,7},{7,7},{7,0}};
    int s(0),cpt(1);

    if(damier.getNp()<60){
        int points[8][8]={
            { 500 ,-150, 30, 10, 10, 30,-150, 500},
            {-150 ,-250,  0,  0,  0,  0,-250,-150},
            { 30  ,  0 ,  1,  2,  2,  1,  0 , 30 },
            { 10  ,  0 ,  2, 16, 16,  2,  0 , 10 },
            { 10  ,  0 ,  2, 16, 16,  2,  0 , 10 },
            { 30  ,  0 ,  1,  2,  2,  1,  0 , 30 },
            {-150 ,-250,  0,  0,  0,  0,-250,-150},
            { 500 ,-150, 30, 10, 10, 30,-150, 500}
            };

        //controlecoin

        int jc(0),ci(0),cj(0),di(0),dj(0);

        for(int c(0);c<4;c++){
            ci=coins[c][0];cj=coins[c][1];
            jc=damier.getV(ci,cj);
            if(jc!=0){
                switch (c){
                case 0:
                    points[0][1]=250;points[1][0]=250;points[1][1]=0;points[0][2]=0;points[2][0]=0;
                    break;
                case 1:
                    points[0][6]=250;points[1][7]=250;points[1][6]=0;points[5][0]=0;points[2][7]=0;
                    break;
                case 2:
                    points[7][6]=250;points[6][7]=250;points[6][6]=0;points[5][7]=0;points[7][5]=0;
                    break;
                case 3:
                    points[7][1]=250;points[6][0]=250;points[6][1]=0;points[7][2]=0;points[5][0]=0;
                    break;
                }

                for(int d=0;d<4;d++){
                    di=dir[d][0];
                    dj=dir[d][1];
                    cpt=1;
                    while(((ci+cpt*di)<8) && ((ci+cpt*di)>=0) && ((cj+cpt*dj)<8) && ((cj+cpt*dj)>=0)
                          && (damier.getV(ci+cpt*di,cj+cpt*dj)==jc)){
                        points[ci+cpt*di][cj+cpt*dj]=250;
                        cpt++;
                    }

                }
            }
        }

        //calcul du score
        for(int i(0);i<8;i++){
            for(int j(0);j<8;j++){
                if(damier.getV(i,j)==joueur){
                    s+=points[i][j];
                }
                else if(damier.getV(i,j)==3-joueur){
                    s-=points[i][j];
                }
            }
        }
    }
    else{
        for(int i(0);i<8;i++){
            for(int j(0);j<8;j++){
                if(damier.getV(i,j)==joueur){
                    s+=10;
                }
                if(damier.getV(i,j)==3-joueur){
                    s-=10;
                }

            }
        }
    }
    return s;
}



