#ifndef __VOIE__
#define  __VOIE__

typedef struct struct_voie{
  int id;
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
void init_voieA(Voie* voie);
void init_voieB(Voie* voie);
void init_voieC(Voie* voie);
#endif
