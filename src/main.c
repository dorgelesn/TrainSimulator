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

void armagedon() {
  // Nettoyage voie
  pthread_mutex_destroy(&mutex);
  for (int i = 0; i < NB_VOIE; i++) {
    pthread_cond_destroy(&tabVoie[i].voieLibre);
    free(tabVoie[i].voieLeft);
    free(tabVoie[i].voieRight);
  }
  free(tabVoie);
}

void armagedonSurCommande() {
  armagedon();
  for (int i = 0; i < nbTrain; i++) {
    if (tid[i] != (pthread_t)NULL) {
      pthread_cancel(tid[i]);
    }
  }
  free(tid);
  raise(SIGINT);
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
  struct sigaction sig;

  srand(time(NULL));
  sig.sa_flags = SA_SIGINFO | SA_RESETHAND;
  sig.sa_sigaction = armagedonSurCommande;
  sigaction(SIGINT,&sig,NULL);
  //Paramètres du problème
  if (argc == 1) {
    nbTGV = 2;
    nbGL = 2;
    nbM = 2;
  }
  else{
    nbTGV = atoi(argv[1]);
    nbGL = atoi(argv[2]);
    nbM = atoi(argv[3]);
  }
  nbTrain = nbTGV + nbGL + nbM;

  initialisation();

  //Création des TGV
  for (i = 0; i < nbTGV; i++) {
    tattr = ordonnancement(tattr, param, TGV_PRIORITY);
    sens = randomSens();
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
    sens = randomSens();
    pthread_create(&tid[i],&tattr,(void *(*)())func_train, init_Train(i, 2, sens));
    //usleep(5000);
  }

  for (i = 0; i < (nbTrain); i++) {
    pthread_join(tid[i],NULL);
  }

  armagedon();
  free(tid);
  exit(0);
}
