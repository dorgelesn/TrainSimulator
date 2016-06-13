#ifndef __TRAIN__
#define __TRAIN__

typedef struct {
  int id;
  int sens;
    //  -1  = vers la gauche
    //   1  = vers la droite
  int priorite;
    //  [0] = TGV
    //  [1] = GL
    //  [2] = M
  Voie* position;
  Voie* startPos;
  Voie* endPos;
}Train;

void func_train(Train* trn);
Voie* getNextVoieTRAIN(Train* train_train_quotidien);
Voie* getNextVoie(Voie* position, int sens, int priorite);
void move(Train* train_train_quotidien);

bool canStartFromLigne(Train* train_train_quotidien);
bool canStartFromGarage(Train* train_train_quotidien);
bool canStartFromGare(Train* train_train_quotidien);

Train* init_Train(int i);

#endif
