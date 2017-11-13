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
    Table* ttable=new Table();

    int joueur=1;
    int i(0),j(0);
    int coup(0);
    string s;
    while(!testFin(*dam)){

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

            }while(!estValide(*dam,joueur,i,j));

        }
        else{
            //profondeur de 4
            alphaBeta(*dam,joueur,4,MINI,MAXI,coup);

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
        joueCoup(*dam,joueur,i,j);
        joueur=3-joueur;
    }

    delete ttable;
    delete dam;

}

void IAVSIA(char prof)
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
    cout<<heuristique(*dam,1)<<" "<<heuristique(*dam,2)<<"\n";
    Table* ttable=new Table();
    Table* ttable2=new Table();

    int joueur=1;
    int i(0),j(0);
    int c(0);
    time_t tmax;

    while(!testFin(*dam)){

        dam->affiche();

        if(joueur==1){
        printf("avec memoire :");
        //c=joueCoupIA2(*dam,joueur,prof,i);
        alphaBetaTT(*ttable,*dam,joueur,prof,MINI,MAXI,prof);
        c=(*ttable)[hashage(*dam,joueur)%TABLE_SIZE]->getC();
        printf("%d %d \n",(*ttable)[hashage(*dam,joueur)%TABLE_SIZE]->getL(),(*ttable)[hashage(*dam,joueur)%TABLE_SIZE]->getU());
        ttable->reset();
        }

        else{
            printf("MTD \n");
            //c=joueCoupIA2(*dam,joueur,prof,i);
            tmax=1;
            c=ID(tmax,prof+10,*dam,*ttable2,joueur);

            ttable2->reset();

        }

        if(c<0){
            i=-1;
            j=0;
        }
        else{
            i=c/10;
            j=c%10;
        }

        if(!estValide(*dam,joueur,i,j)){
            printf("erreur %d %d \n",i,j);
            return ;
        }
        cout<< i<<" "<<j<<" "<<joueur<<"\n";
        joueCoup(*dam,joueur,i,j);
        joueur=3-joueur;
    }
    dam->affiche();

    cout<<"1:"<<score(*dam,1)<<"\n";
    cout<<"2:"<<score(*dam,2)<<"\n";

    delete ttable;
    delete ttable2;
    delete dam;

}
