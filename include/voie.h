#ifndef __VOIE__
#define  __VOIE__

typedef struct struct_voie{
  int id;
  int nbTrainAct;
  int nbMaxTrain;
  struct struct_voie** voieLeft;
  struct struct_voie** voieRight;
  int sens;
    //  -1 = vers la gauche
    //  0 = dans les 2 sens
    //  1 = vers la droite

  int typeTrain[3];
    //  [0] = autorise TGV
    //  [1] = autorise GL
    //  [2] = autorise M
}Voie;

void func_voie(Voie* v);
void init_voieA(Voie* voie); // Voie 0
void init_voieB(Voie* voie); // Voie 1
void init_voieC(Voie* voie); // Voie 2
void init_voieD(Voie* voie); // Voie 3
void init_voieTGV(Voie* voie); // Voie 4
void init_voieMG(Voie* voie); // Voie 5
void init_voieMD(Voie* voie); // Voie 6
void init_voieGL(Voie* voie); // Voie 7
void init_voieTUN(Voie* voie); // Voie 8
void init_voieLIGNE(Voie* voie); // Voie 9
#endif
