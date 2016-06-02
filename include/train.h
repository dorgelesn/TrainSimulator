#ifndef __TRAIN__
#define __TRAIN__

typedef struct {
  int id;
  int sens;
    //  -1  = vers la gauche
    //   1  = vers la droite
  int priorite;
    //  [0] = autorise TGV
    //  [1] = autorise GL
    //  [2] = autorise M
  Voie* position;
}Train;

void fonc_train(Train* trn);

#endif
