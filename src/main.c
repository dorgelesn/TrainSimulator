#include "../include/global.h"

int main(int argc, char const *argv[]) {
  int i;

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
  init_voieA(&tabVoie[0]);
  init_voieB(&tabVoie[1]);
  init_voieC(&tabVoie[2]);
  init_voieD(&tabVoie[3]);
  init_voieTGV(&tabVoie[4]);
  init_voieMG(&tabVoie[5]);
  init_voieMD(&tabVoie[6]);
  init_voieGL(&tabVoie[7]);
  init_voieTUN(&tabVoie[8]);
  init_voieLIGNE(&tabVoie[9]);

  tid = malloc((nbTrain)*sizeof(pthread_t));

  for (i = 0; i < (nbTrain); i++) {
    pthread_create(&tid[i],0,(void *(*)())func_train, init_Train(i));
    usleep(5000);
  }

  for (i = 0; i < (nbTrain); i++) {
    pthread_join(tid[i],NULL);
  }

  //penser à delete les malloc
  /*for (i = NB_VOIE; i < (NB_VOIE+nbTrain); i++) {
    free(&tid[i]);
  }*/
  //free(&tabVoie);
  //free(&tid);
  exit(0);
}
