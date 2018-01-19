#include "IA_main.h"


void possibilites(std::vector<int>& coups,const Damier& damier,int joueur)
{
 
	int coup_a_ajouter;
    //on teste le passage de tour
    if(estValide(damier,joueur,-1)){
		
		coup_a_ajouter = -10;
		coups.push_back(coup_a_ajouter);
        return;
    }
    else{

        for(int i(0);i<8;++i){
            for(int j(0);j<8;++j){
                if(estValide(damier,joueur,i,j)){
					coup_a_ajouter = i*10+j;

					coups.push_back(coup_a_ajouter); //si le coup est valide on l'ajoute   
                }
            }
        }
    }
}

///=====================================================================

bool inList(int i,int j,std::vector<int*>& coups)
{
    for(auto c : coups){
        if(c[0]==i && c[1]==j){
            return true;
        }
    }
    return false;
}

///=====================================================================

int coefMobi(int nombrePionsTotal) {
	//les valeurs ont été choisies arbitrairement
	//en partant du principe que sur la fin de partie la mobilité est moins importante
	switch (nombrePionsTotal / 10) {
	case 0:
		return 5;
	case 1:
		return 8;
	case 2:
		return 10;
	case 3:
		return 10;
	case 4:
		return 10;
	case 5:
		return 4;
	}
	return 0;
}

///=====================================================================

int deltaMobilite(const Damier& damier, int joueur) {

	int cpt1(0), cpt2(0);

	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (estValide(damier, joueur, i, j)) {
				++cpt1;
			}
			else if (estValide(damier, joueur, i, j)) {
				++cpt2;
			}
		}
	}

	return cpt1 - cpt2;
}

///=====================================================================

int heuristiqueMilieuDePartie(const Damier& damier, int joueur)
{
	static int dir[4][2] = { {-1,0},{1,0},{0,1},{0,-1} }; //représente les directions possibles (sans compter les diagonales)
	static int coins[4][2] = { {0,0},{0,7},{7,7},{7,0} }; //représente les coins du damier
	int sc(0), cpt(1);


	int points[8][8] = { //poids des différentes cases à l'état initial

			{ 500 ,-150, 30, 10, 10, 30,-150, 500},
			{-150 ,-250,  0,  0,  0,  0,-250,-150},
			{ 30  ,  0 ,  1,  2,  2,  1,  0 , 30 },
			{ 10  ,  0 ,  2, 16, 16,  2,  0 , 10 },
			{ 10  ,  0 ,  2, 16, 16,  2,  0 , 10 },
			{ 30  ,  0 ,  1,  2,  2,  1,  0 , 30 },
			{-150 ,-250,  0,  0,  0,  0,-250,-150},
			{ 500 ,-150, 30, 10, 10, 30,-150, 500}
	};

	////controle des coins très importants en milieu de partie////
	int jc(0), ci(0), cj(0), di(0), dj(0);

	for (int c(0); c < 4; ++c) {
		ci = coins[c][0]; cj = coins[c][1];
		jc = damier.getV(ci, cj); //jc = joueur qui controle le coin
		if (jc != 0) {	//pour chaque coin, s'il est controlé on met à jour les valeurs des cases adjacentes
			switch (c) {
			case 0:	//coin en haut à gauche
				points[0][1] = 250; points[1][0] = 250; points[1][1] = 0; points[0][2] = 0; points[2][0] = 0;
				break;
			case 1: //coin en haut à droite
				points[0][6] = 250; points[1][7] = 250; points[1][6] = 0; points[5][0] = 0; points[2][7] = 0;
				break;
			case 2: //coin en bas à droite
				points[7][6] = 250; points[6][7] = 250; points[6][6] = 0; points[5][7] = 0; points[7][5] = 0;
				break;
			case 3: //coin en bas à gauche
				points[7][1] = 250; points[6][0] = 250; points[6][1] = 0; points[7][2] = 0; points[5][0] = 0;
				break;
			}

			//controle des bords important si les coins sont pris
			for (int d = 0; d < 4; ++d) {
				di = dir[d][0];
				dj = dir[d][1];
				cpt = 1;
				while (((ci + cpt*di) < 8) && ((ci + cpt*di) >= 0) && ((cj + cpt*dj) < 8) && ((cj + cpt*dj) >= 0)
					&& (damier.getV(ci + cpt*di, cj + cpt*dj) == jc)) {
					points[ci + cpt*di][cj + cpt*dj] = 100;
					++cpt;
				}

			}
		}
	}

	//calcul du sc

	for (int i(0); i < 8; i++) {
		for (int j(0); j < 8; j++) {
			if (damier.getV(i, j) == joueur) {
				sc += points[i][j];
			}
			else if (damier.getV(i, j) == 3 - joueur) {
				sc -= points[i][j];
			}
		}
	}

	if(damier.getNp()>50) sc += 10*score(damier, joueur);
	sc += coefMobi(damier.getNp())*deltaMobilite(damier, joueur);

    return sc;
}

///=====================================================================

int heuristiqueFinDePartie(const Damier& damier, int joueur) {
	return score(damier, joueur);
}