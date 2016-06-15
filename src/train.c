#include "../include/global.h"

void func_train(Train* trn){
  printf("Création du Train %d qui part de %d et va %d\n",trn->id, trn->startPos->id,trn->sens);

  while (trn->position != trn->endPos) {
    move(trn);
  }
  pthread_mutex_lock(&mutex);
  printf("Train %d est arrivé\n", trn->id);
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
      printf("Le train n°%d départ de la voie %d pour aller vers %d\n", train_train_quotidien->id, train_train_quotidien->position->id, nextVoie->id);
      train_train_quotidien->position->nbTrainAct--;
      train_train_quotidien->position->reserve = false;
      train_train_quotidien->position->reserveId = -1;
      pthread_cond_signal(&train_train_quotidien->position->voieLibre);
      train_train_quotidien->position = nextVoie;
      train_train_quotidien->position->nbTrainAct++;
      printf("Le train %d est sur la voie %d\n", train_train_quotidien->id, train_train_quotidien->position->id);
      usleep(5000);
    }
  }
  pthread_mutex_unlock(&mutex);
}

/*
 * Fonction de réservation qui test si les voies peuvent être empruntées
 */
bool canStart(Train* train_train_quotidien){
  Voie* nextVoie = getNextVoieTRAIN(train_train_quotidien);
  Voie* previousVoie = train_train_quotidien->position;
  while (!nextVoie->canStop) {
    if ((nextVoie->reserve && nextVoie->reserveId != train_train_quotidien->id) || nextVoie->nbTrainAct == nextVoie->nbMaxTrain || (nextVoie->currentSens != 0 && nextVoie->currentSens != train_train_quotidien->sens)) {
      printf("Le Train n°%d est en ATTENTE (Voie %d non libre)\n", train_train_quotidien->id, nextVoie->id);
      pthread_cond_wait(&nextVoie->voieLibre, &mutex);
      /*while (previousVoie != train_train_quotidien->position) {
      }*/
    }else{
      printf("Voie N° %d reserved\n", nextVoie->id);
      nextVoie->reserve = true;
      nextVoie->reserveId = train_train_quotidien->id;
    }
    //printf("Next voie %d\n", nextVoie->id);
    nextVoie = getNextVoie(nextVoie, train_train_quotidien->sens, train_train_quotidien->priorite);
    //printf("Next next voie %d\n", nextVoie->id);

  }
  return true;
}

/*
 * Recherche de la prochaine voie après celle actuelle
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
 * Recherche d'autorisation pour rouler
 */
void aiguillage(Train* trn){

}

/*
 * Initialisation des Trains
 */
Train* init_Train(int i, int random){
  Train* train_train = malloc(sizeof(Train));
  //int random = rand()%3+1;
  //random = 4;
  //printf("%d\n", random);
  switch (random) {
    case 1:
    {
      //Train de marchandise qui part de la voie A et va vers la voie LIGNE
      train_train->startPos = &tabVoie[0];
      train_train->endPos = &tabVoie[9];
      train_train->position = calloc(1,sizeof(Voie));
      train_train->position = &tabVoie[10];
      //ajouter un compteur de train en attente ?
      train_train->id = i;
      train_train->sens = 1;
      train_train->priorite = 2;
    }
    break;

    case 2:
    {
      //Train TGV qui part de la voie C et va vers la voie LIGNE
      train_train->startPos = &tabVoie[2];
      train_train->endPos = &tabVoie[9];
      train_train->position = calloc(1,sizeof(Voie));
      train_train->position = &tabVoie[11];
      train_train->id = i;
      train_train->sens = 1;
      train_train->priorite = 0;
    }
    break;

    case 3:
    {
      //Train qui part de la voie LIGNE et va vers la gauche
      train_train->startPos = &tabVoie[9];
      train_train->endPos = &tabVoie[3];
      train_train->position = calloc(1,sizeof(Voie));
      train_train->position = &tabVoie[12];
      train_train->id = i;
      train_train->sens = -1;
      train_train->priorite = (rand()%2);
    }
    break;

    case 4:
    {
      //Train marchandise qui part de la voie LIGNE et va vers la gauche
      train_train->startPos = &tabVoie[9];
      train_train->endPos = &tabVoie[1];
      train_train->position = calloc(1,sizeof(Voie));
      train_train->position = &tabVoie[12];
      train_train->id = i;
      train_train->sens = -1;
      train_train->priorite = 2;
    }
    break;

  }
  return train_train;
}
