#include "../include/global.h"

int main(int argc, char const *argv[]) {
  if (argc == 1) {
    nbTrain = 10;
  }
  else{
    nbTrain = atoi(argv[1]);
  }

  /*Train* tab[NB_VOIE];
  for (int i = 0; i < NB_VOIE; i++) {
    tab[i] = malloc(sizeof(Train));
  }
  tab[1]->id = 0;
  printf("%d\n", tab[1]->id);*/

  //Initialisation tid
  tabVoie = malloc(sizeof(Voie)*NB_VOIE);

  tid = malloc((nbTrain+NB_VOIE)*sizeof(pthread_t));
  for (int i = 0; i < NB_VOIE; i++) {
    pthread_create(&tid[i],0,(void *(*)())func_voie,0); //voir pour les arguments

  }
  for (int i = NB_VOIE; i < nbTrain+NB_VOIE; i++) {
    Train* train_train;
    train_train->id = i;
    train_train->sens = -1;
    train_train->priorite = 0;

    pthread_create(&tid[i],0,(void *(*)())fonc_train,train_train);
    usleep(5000);
  }

  //penser à delete les malloc
  exit(0);
}
