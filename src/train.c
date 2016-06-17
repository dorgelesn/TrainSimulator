#include "../include/global.h"

void func_train(Train* trn){
  printf("## Création du Train %d qui part de %d et va %d ##\n",trn->id, trn->startPos->id,trn->sens);

  while (trn->position != trn->endPos) {
    move(trn);
    usleep(200000);
  }
  pthread_mutex_lock(&mutex);
  printf(" >>> Train %d est arrivé <<<\n", trn->id);
  trn->position->nbTrainAct--;
  trn->position->reserve = false;
  trn->position->reserveId = -1;
  pthread_cond_signal(&trn->position->voieLibre);
  pthread_mutex_unlock(&mutex);

  pthread_exit(NULL);
}

void move(Train* train_train_quotidien){
  pthread_mutex_lock(&mutex);
  Voie* nextVoie = getNextVoieTRAIN(train_train_quotidien);
  if (nextVoie != NULL) {
    if (canStart(train_train_quotidien)) {
      printf("Le Train n°%d départ de la voie %d pour aller vers %d\n", train_train_quotidien->id, train_train_quotidien->position->id, nextVoie->id);
      // On enlève le train de la voie actuelle
      train_train_quotidien->position->nbTrainAct--;
      // On enlève la réservation sur la voie qu'on va quitter
      train_train_quotidien->position->reserve = false;
      train_train_quotidien->position->reserveId = -1;
      // On réinitialise le sens courant de la voie
      train_train_quotidien->position->currentSens = train_train_quotidien->position->sens;

      pthread_cond_broadcast(&train_train_quotidien->position->voieLibre); // le broadcast est une précaution si jamais il y a des trains qui pourraient ne jamais être réveillés.
      // ça y est le train a officiellement changé de voie :)
      train_train_quotidien->position = nextVoie;
      // On adapte le sens de la voie
      train_train_quotidien->position->currentSens = train_train_quotidien->sens;
      // On ajoute le train dans le décompte de la voie
      train_train_quotidien->position->nbTrainAct++;

      printf("Le Train n°%d est sur la Voie %d\n", train_train_quotidien->id, train_train_quotidien->position->id);
      if (train_train_quotidien->position->id == 4) {
        //printf("Nombre train sur 4 :  %d\n", train_train_quotidien->position->nbTrainAct);
        //printf("########################### Sens train : %d\t\t\tSens Voie : %d\t\t\tSens courant : %d\n", train_train_quotidien->sens,train_train_quotidien->position->sens, train_train_quotidien->position->currentSens);
        printf(" !!! Petite PAUSE au Garage !!!\n");
        usleep(5000);

      }else if (train_train_quotidien->position->id == 2) {
        printf(" !!! Petite PAUSE à la Gare !!!\n");
        usleep(5000);
      }
      usleep(50);
    }
  }
  pthread_mutex_unlock(&mutex);

}

/*
 * Petite fonction permettant de réserver une voie et empêcher les autres véhicules de l'empreinter
 */
void makeReservation(Train* train_train_quotidien, Voie* nextVoie){
  printf("Le Train n°%d a reservé la Voie n°%d\n", train_train_quotidien->id, nextVoie->id);
  usleep(5000);
  // reservation de la voie
  nextVoie->reserve = true;
  nextVoie->reserveId = train_train_quotidien->id;
  nextVoie->currentSens = train_train_quotidien->sens;
  // ajout de la voie à la liste de réservation du train
  train_train_quotidien->reservationTab[train_train_quotidien->nbReservation] = nextVoie;
  train_train_quotidien->nbReservation++;
}

/*
 * Fonction de réservation qui test si les voies peuvent être empruntées
 */
bool canStart(Train* train_train_quotidien){
  bool inProgress = true;
  Voie* nextVoie = getNextVoieTRAIN(train_train_quotidien);

  while (inProgress){
    if ((nextVoie->reserve && nextVoie->reserveId != train_train_quotidien->id) || nextVoie->nbTrainAct == nextVoie->nbMaxTrain || (nextVoie->currentSens != 0 && nextVoie->currentSens != train_train_quotidien->sens)) {
      // On réinitialise le tableau de réservation du train
      for (int j = 0; j < train_train_quotidien->nbReservation; j++) {
        train_train_quotidien->reservationTab[j]->reserve = false;
        train_train_quotidien->reservationTab[j]->reserveId = -1;
        train_train_quotidien->reservationTab[j]->currentSens = train_train_quotidien->reservationTab[j]->sens;
      }
      train_train_quotidien->nbReservation = 0;
      printf("Le Train n°%d est en ATTENTE (Voie %d non libre)\n", train_train_quotidien->id, nextVoie->id);
      pthread_cond_wait(&nextVoie->voieLibre, &mutex);
      nextVoie = train_train_quotidien->position;
      printf("Le Train n°%d se REVEILLE et recommence à réserver de %d \n\n",train_train_quotidien->id, nextVoie->id);
    }else{
      makeReservation(train_train_quotidien, nextVoie);
      if (nextVoie->canStop || nextVoie->id == train_train_quotidien->endPos->id) {
        printf("Arrêt réservation pour train n°%d\n", train_train_quotidien->id);
        inProgress = false;
      }
    }
    //printf("Next voie %d\n", nextVoie->id);
    nextVoie = getNextVoie(nextVoie, train_train_quotidien->sens, train_train_quotidien->priorite);
    //printf("Next next voie %d\n", nextVoie->id);

  }
  return true;
}

/*
 * Recherche de la voie suivante par rapport à la position du train
 */
Voie* getNextVoieTRAIN(Train* train_train_quotidien) {
  return getNextVoie(train_train_quotidien->position, train_train_quotidien->sens, train_train_quotidien->priorite);
}
Voie* getNextVoie(Voie* position, int sens, int priorite) {
  if (sens == -1) {
    if (position->nbVoieLeft != 0) {
      for (int i = 0; i < position->nbVoieLeft; i++) {
        if (position->voieLeft[i]->typeTrain[priorite] == 1) {
          if (position->voieLeft[i]->sens == sens || position->voieLeft[i]->sens == 0) {
            return position->voieLeft[i];
          }
        }
      }
    }
  }else{
    if (position->nbVoieRight != 0) {
      for (int i = 0; i < position->nbVoieRight; i++) {
        if (position->voieRight[i]->typeTrain[priorite] == 1) {
          if (position->voieRight[i]->sens == sens || position->voieRight[i]->sens == 0) {
            return position->voieRight[i];
          }
        }
      }
    }
  }
  return NULL;
}


/*
 * Initialisation des Trains
 */
Train* init_Train(int i, int type, int sens){
  Train* train_train = malloc(sizeof(Train));
  //type = 4;
  //printf("%d\n", type);
  train_train->id = i;
  train_train->priorite = type;
  train_train->sens = sens;
  train_train->reservationTab = malloc(3*sizeof(Voie*));
  train_train->nbReservation = 0;
  for (int j = 0; j < 3; j++) {
    train_train->reservationTab[j] = NULL;
  }

  if (type == 2) {
    //Train M qui part :
    //    soit de la voie A pour aller vers la voie LIGNE (si sens = 1)
    //    soit de la voie LIGNE pour aller vers la voie B (si sens = -1)
    if (train_train->sens == 1) {
      train_train->startPos = &tabVoie[0];
      train_train->endPos = &tabVoie[12];
      train_train->position = calloc(1,sizeof(Voie));
      train_train->position = &tabVoie[10];
    }else{
      train_train->startPos = &tabVoie[9];
      train_train->endPos = &tabVoie[1];
      train_train->position = calloc(1,sizeof(Voie));
      train_train->position = &tabVoie[12];
    }
  }else{
    //Train TGV ou GL qui part :
    //    soit de la voie C pour aller vers la voie LIGNE (si sens = 1)
    //    soit de la voie LIGNE pour aller vers la voie C (si sens = -1)
    if (train_train->sens == 1) {
      train_train->startPos = &tabVoie[2];
      train_train->endPos = &tabVoie[12];
      train_train->position = calloc(1,sizeof(Voie));
      train_train->position = &tabVoie[11];
    }else{
      train_train->startPos = &tabVoie[9];
      train_train->endPos = &tabVoie[3];
      train_train->position = calloc(1,sizeof(Voie));
      train_train->position = &tabVoie[12];
    }
  }
  return train_train;
}
