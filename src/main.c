#include "../include/global.h"

void initialisation(){
  //Initialisation du mutex
  pthread_mutex_init(&mutex, NULL);

  //Initialisation des voies
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
    init_voieStartA(&tabVoie[10]);
    init_voieStartC(&tabVoie[11]);
    init_voieStartLIGNE(&tabVoie[12]);

  //Initialisation tableau des threads de train
  tid = malloc((nbTrain)*sizeof(pthread_t));
}

pthread_attr_t ordonnancement(pthread_attr_t tattr, struct sched_param param, int priority){
  // Initialisation avec attributs par défaut
  pthread_attr_init(&tattr);
  // Sauvegarde des paramètres actuels
  pthread_attr_getschedparam (&tattr, &param);
  // Changement politique ordonnancement
  pthread_attr_setschedpolicy(&tattr, SCHED_FIFO);
  // Changement priorité
  param.sched_priority = priority;
  // Application nouveau paramètres
  pthread_attr_setschedparam(&tattr, &param);

  return tattr;
}

int randomSens(){
  int s;
  if ((rand()%2+1) == 1){
    return (int)pow((-1),1);
  }else{
    return (int)pow((-1),2);
  }
}

int main(int argc, char const *argv[]) {
  int i, sens, typeTrain;
  pthread_attr_t tattr;
  struct sched_param param;

  //Paramètres du problème
  if (argc == 1) {
    nbTGV = 1000;
    nbGL = 1000;
    nbM = 1000;
  }
  else{
    nbTGV = atoi(argv[1]);
    nbGL = atoi(argv[2]);
    nbM = atoi(argv[3]);
  }
  nbTrain = nbTGV + nbGL + nbM;

  initialisation();

  for (i = 0; i < nbTGV; i++) {
    //Création des TGV
    tattr = ordonnancement(tattr, param, TGV_PRIORITY);
    if (i%2 == 1) {
      sens = 1;
    }else{
      sens = -1;
    }
    pthread_create(&tid[i],&tattr,(void *(*)())func_train, init_Train(i, 0, sens));
    //usleep(5000);
  }
  //Création des trains de Grandes Lignes (GL)
  for (i = nbTGV; i < (nbTGV+nbGL); i++) {
    tattr = ordonnancement(tattr, param, GL_PRIORITY);
    sens = randomSens();
    pthread_create(&tid[i],&tattr,(void *(*)())func_train, init_Train(i, 1, sens));
    //usleep(5000);
  }
  //Création des trains de Marchandises (M)
  for (i = (nbTGV+nbGL); i < (nbM+nbTGV+nbGL); i++) {
    tattr = ordonnancement(tattr, param, M_PRIORITY);
    if (i%2 == 1) {
      sens = 1;
    }else{
      sens = -1;
    }
    //sens = 1;//randomSens();
    pthread_create(&tid[i],&tattr,(void *(*)())func_train, init_Train(i, 2, sens));
    //usleep(5000);
  }

  for (i = 0; i < (nbTrain); i++) {
    pthread_join(tid[i],NULL);
  }

  //penser à delete les malloc
  /*for (i = NB_VOIE; i < (NB_VOIE+nbTrain); i++) {
    free(&tid[i]);
  }*/
  pthread_mutex_destroy(&mutex);
  free(tabVoie);
  free(tid);
  exit(0);
}
