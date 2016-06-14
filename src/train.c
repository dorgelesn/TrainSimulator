#include "../include/global.h"

void func_train(Train* trn){
  printf("Création du Train %d qui part de %d et va %d\n",trn->id, trn->startPos->id,trn->sens);
  while (trn->position != trn->endPos) {
    move(trn);
  }
  printf("Je suis arrivé\n");
  pthread_exit(NULL);
  /*while (getNextVoie != NULL) {
    if (trn->position == &tabVoie[9]) {
      if (canStartFromLigne(trn)) {
        move(trn);
      }
    }else if (trn->position == &tabVoie[8]) {
      move(trn);
    }else if (trn->position == &tabVoie[7]) {
      if (canStartFromGarage(trn)) {
        move(trn);
      }
    }else if (trn->position == &tabVoie[6]) {
      if (canStartFromGarage(trn)) {
        move(trn);
      }
    }else if (trn->position == &tabVoie[5]) {
      if (canStartFromGarage(trn)) {
        move(trn);
      }
    }else if (trn->position == &tabVoie[4]) {
      if (canStartFromGarage(trn)) {
        move(trn);
      }
    }else if (trn->position == &tabVoie[2]) {
      if (canStartFromGare(trn)) {
        move(trn);
      }
    }else if (trn->position == &tabVoie[0]) {
      if (canStartFromGare(trn)) {
        move(trn);
      }
    }


    if (trn->position->id == trn->endPos->id) {
      printf("End point free\n");
      pthread_exit(NULL);
    }
  }*/
}

void move(Train* train_train_quotidien){
  pthread_mutex_lock(&mutex);
  Voie* onTheWay = getNextVoieTRAIN(train_train_quotidien);

  if (onTheWay->reserve) {
    printf("Le train n°%d attend que la voie %d soit libre\n", train_train_quotidien->id, onTheWay->id);
  }else{
    pthread_cond_signal(&voieA);
    printf("Départ !!\n");
    train_train_quotidien->position = onTheWay;
    printf("Le train %d est sur la voie %d\n", train_train_quotidien->id, train_train_quotidien->position->id);
    usleep(5000);
  }
  pthread_mutex_unlock(&mutex);
}

Voie* getNextVoieTRAIN(Train* train_train_quotidien) {
  return getNextVoie(train_train_quotidien->position, train_train_quotidien->sens, train_train_quotidien->priorite);
}

Voie* getNextVoie(Voie* position, int sens, int priorite) {
  if (sens == -1) {
    if (position->nbVoieLeft != 0) {
      for (int i = 0; i < position->nbVoieLeft; i++) {
        if (position->voieLeft[i]->typeTrain[priorite] == 1) {
          return position->voieLeft[i];
        }
      }
    }
  }else{
    if (position->nbVoieRight != 0) {
      for (int i = 0; i < position->nbVoieRight; i++) {
        if (position->voieRight[i]->typeTrain[priorite] == 1) {
          return position->voieRight[i];
        }
      }
    }
  }
  return NULL;
}

bool canStartFromLigne(Train* train_train_quotidien){
  Voie* tunnel = getNextVoieTRAIN(train_train_quotidien);
  Voie* garage = getNextVoie(getNextVoieTRAIN(train_train_quotidien), train_train_quotidien->sens, train_train_quotidien->priorite);

  if (tunnel->nbTrainAct < tunnel->nbMaxTrain) {
    if (!(tunnel->reserve)) {
      if (garage->typeTrain[2] == 1) {
        printf("La marchandise est libre pour partir de Ligne\n");
        return true;
      }
      else if(garage->typeTrain[1] == 1){
        if (garage->currentSens == -1 || garage->currentSens == 0) {
          printf("La GL est libre pour partir de Ligne\n");
          return true;
        }
      }
      else if(garage->typeTrain[0] == 1){
        if (garage->currentSens == -1 || garage->currentSens == 0) {
          printf("Les TGV est libre de partir de Ligne\n");
          return true;
        }
      }
    }
  }
  return false;
}

bool canStartFromGarage(Train* train_train_quotidien){
  Voie* gare = getNextVoieTRAIN(train_train_quotidien);

  if (gare->nbTrainAct < gare->nbMaxTrain) {
    if (!(gare->reserve)) {
      printf("Le train est libre de partir du Garage\n");
      return true;
    }
  }
  return false;
}

bool canStartFromGare(Train* train_train_quotidien){
  Voie* garage = getNextVoieTRAIN(train_train_quotidien);

  if (garage->nbTrainAct < garage->nbMaxTrain) {
    if (!(garage->reserve)) {
      if (garage->typeTrain[2] == 1) {
        printf("La marchandise est libre pour partir de la gare\n");
        return true;
      }
      else if(garage->typeTrain[1] == 1){
        if (garage->currentSens == -1 || garage->currentSens == 0) {
          printf("Le train GL est libre de partir de la gare\n");
          return true;
        }
      }
      else if(garage->typeTrain[0] == 1){
        if (garage->currentSens == -1 || garage->currentSens == 0) {
          printf("Le train TGV est libre de partir de la gare\n");
          return true;
        }
      }
    }
  }
  return false;
}

Train* init_Train(int i){
  Train* train_train = malloc(sizeof(Train));
  int random = rand()%3+1;
  printf("%d\n", random);
  switch (random) {
    case 1:
    {
      train_train->startPos = &tabVoie[0];
      train_train->endPos = &tabVoie[9];
      train_train->position = calloc(1,sizeof(Voie));
      train_train->position = train_train->startPos;
      train_train->id = i;
      train_train->sens = 1;
      train_train->priorite = 2;
    }
    break;

    case 2:
    {
      train_train->startPos = &tabVoie[2];
      train_train->endPos = &tabVoie[9];
      train_train->position = calloc(1,sizeof(Voie));
      train_train->position = train_train->startPos;
      train_train->id = i;
      train_train->sens = 1;
      train_train->priorite = 0;
    }
    break;

    case 3:
    {
      train_train->startPos = &tabVoie[9];
      train_train->endPos = &tabVoie[1];
      train_train->position = calloc(1,sizeof(Voie));
      train_train->position = train_train->startPos;
      train_train->id = i;
      train_train->sens = -1;
      train_train->priorite = 0;
    }
    break;

  }
  return train_train;
}
