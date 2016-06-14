#include "../include/global.h"

void func_voie(Voie* v){
  printf("Création de la Voie %d\n", v->id);

}

void init_voieA(Voie* v){
  v->id = 0;
  v->reserve = false;
  pthread_cond_init(&v->voieLibre, NULL);

  v->nbTrainAct = 0;
  v->nbMaxTrain = 1;
  v->voieLeft = NULL;
  v->nbVoieLeft = 0;
  v->voieRight = malloc(4*sizeof(Voie*));
  v->voieRight[0] = &tabVoie[4];
  v->voieRight[1] = &tabVoie[5];
  v->voieRight[2] = &tabVoie[6];
  v->voieRight[3] = &tabVoie[7];
  v->nbVoieRight = 4;
  v->sens = v->currentSens = 1;
  v->typeTrain[0] = 1;
  v->typeTrain[1] = 0;
  v->typeTrain[2] = 0;
}

void init_voieB(Voie* v){
  v->id = 1;
  v->reserve = false;
  pthread_cond_init(&v->voieLibre, NULL);

  v->nbTrainAct = 0;
  v->nbMaxTrain = 1;
  v->voieLeft = NULL;
  v->nbVoieLeft = 0;
  v->voieRight = malloc(4*sizeof(Voie*));
  v->voieRight[0] = &tabVoie[4];
  v->voieRight[1] = &tabVoie[5];
  v->voieRight[2] = &tabVoie[6];
  v->voieRight[3] = &tabVoie[7];
  v->nbVoieRight = 4;
  v->sens = v->currentSens = -1;
  v->typeTrain[0] = 1;
  v->typeTrain[1] = 0;
  v->typeTrain[2] = 0;
}

void init_voieC(Voie* v){
  v->id = 2;
  v->reserve = false;
  pthread_cond_init(&v->voieLibre, NULL);

  v->nbTrainAct = 0;
  v->nbMaxTrain = 1;
  v->voieLeft = NULL;
  v->nbVoieLeft = 0;
  v->voieRight = malloc(4*sizeof(Voie*));
  v->voieRight[0] = &tabVoie[4];
  v->voieRight[1] = &tabVoie[5];
  v->voieRight[2] = &tabVoie[6];
  v->voieRight[3] = &tabVoie[7];
  v->nbVoieRight = 4;
  v->sens = v->currentSens = 1;
  v->typeTrain[0] = 1;
  v->typeTrain[1] = 1;
  v->typeTrain[2] = 0;
}

void init_voieD(Voie* v){
  v->id = 3;
  v->reserve = false;
  pthread_cond_init(&v->voieLibre, NULL);

  v->nbTrainAct = 0;
  v->nbMaxTrain = 1;
  v->voieLeft = NULL;
  v->nbVoieLeft = 0;
  v->voieRight = malloc(4*sizeof(Voie*));
  v->voieRight[0] = &tabVoie[4];
  v->voieRight[1] = &tabVoie[5];
  v->voieRight[2] = &tabVoie[6];
  v->voieRight[3] = &tabVoie[7];
  v->nbVoieRight = 4;
  v->sens = v->currentSens = -1;
  v->typeTrain[0] = 1;
  v->typeTrain[1] = 1;
  v->typeTrain[2] = 0;
}

void init_voieTGV(Voie* v){
  v->id = 4;
  v->reserve = false;
  pthread_cond_init(&v->voieLibre, NULL);

  v->nbTrainAct = 0;
  v->nbMaxTrain = 5;
  v->voieLeft = malloc(4*sizeof(Voie*));
  v->voieLeft[0] = &tabVoie[1];
  v->voieLeft[1] = &tabVoie[2];
  v->voieLeft[2] = &tabVoie[3];
  v->voieLeft[3] = &tabVoie[4];
  v->nbVoieLeft = 4;

  v->voieRight = malloc(sizeof(Voie*));
  v->voieRight[0] = &tabVoie[8];
  v->nbVoieRight = 1;
  v->sens = v->currentSens = 0;
  v->typeTrain[0] = 1;
  v->typeTrain[1] = 0;
  v->typeTrain[2] = 0;
}

void init_voieMG(Voie* v){
  v->id = 5;
  v->reserve = false;
  pthread_cond_init(&v->voieLibre, NULL);

  v->nbTrainAct = 0;
  v->nbMaxTrain = 5;
  v->voieLeft = malloc(4*sizeof(Voie*));
  v->voieLeft[0] = &tabVoie[1];
  v->voieLeft[1] = &tabVoie[2];
  v->voieLeft[2] = &tabVoie[3];
  v->voieLeft[3] = &tabVoie[4];
  v->nbVoieLeft = 4;

  v->voieRight = malloc(sizeof(Voie*));
  v->voieRight[0] = &tabVoie[8];
  v->nbVoieRight = 1;

  v->sens = v->currentSens = 0;
  v->typeTrain[0] = 0;
  v->typeTrain[1] = 0;
  v->typeTrain[2] = 1;
}

void init_voieMD(Voie* v){
  v->id = 6;
  v->reserve = false;
  pthread_cond_init(&v->voieLibre, NULL);

  v->nbTrainAct = 0;
  v->nbMaxTrain = 5;
  v->voieLeft = malloc(4*sizeof(Voie*));
  v->voieLeft[0] = &tabVoie[1];
  v->voieLeft[1] = &tabVoie[2];
  v->voieLeft[2] = &tabVoie[3];
  v->voieLeft[3] = &tabVoie[4];
  v->nbVoieLeft = 4;

  v->voieRight = malloc(sizeof(Voie*));
  v->voieRight[0] = &tabVoie[8];
  v->nbVoieRight = 1;

  v->sens = v->currentSens = 0;
  v->typeTrain[0] = 0;
  v->typeTrain[1] = 0;
  v->typeTrain[2] = 1;
}

void init_voieGL(Voie* v){
  v->id = 7;
  v->reserve = false;
  pthread_cond_init(&v->voieLibre, NULL);

  v->nbTrainAct = 0;
  v->nbMaxTrain = 5;
  v->voieLeft = malloc(4*sizeof(Voie*));
  v->voieLeft[0] = &tabVoie[1];
  v->voieLeft[1] = &tabVoie[2];
  v->voieLeft[2] = &tabVoie[3];
  v->voieLeft[3] = &tabVoie[4];
  v->nbVoieLeft = 4;

  v->voieRight = malloc(sizeof(Voie*));
  v->voieRight[0] = &tabVoie[8];
  v->nbVoieRight = 1;

  v->sens = v->currentSens = 0;
  v->typeTrain[0] = 0;
  v->typeTrain[1] = 1;
  v->typeTrain[2] = 0;
}

void init_voieTUN(Voie* v){
  v->id = 8;
  v->reserve = false;
  pthread_cond_init(&v->voieLibre, NULL);

  v->nbTrainAct = 0;
  v->nbMaxTrain = 1;
  v->voieLeft = malloc(4*sizeof(Voie*));
  v->voieLeft[0] = &tabVoie[4];
  v->voieLeft[1] = &tabVoie[5];
  v->voieLeft[2] = &tabVoie[6];
  v->voieLeft[3] = &tabVoie[7];
  v->nbVoieLeft = 4;


  v->voieRight = malloc(sizeof(Voie*));
  v->voieRight[0] = &tabVoie[9];
  v->nbVoieRight = 1;

  v->sens = v->currentSens = 0;
  v->typeTrain[0] = 1;
  v->typeTrain[1] = 1;
  v->typeTrain[2] = 1;
}

void init_voieLIGNE(Voie* v){
  v->id = 9;
  v->reserve = false;
  pthread_cond_init(&v->voieLibre, NULL);

  v->nbTrainAct = 0;
  v->nbMaxTrain = 1;
  v->voieLeft = malloc(sizeof(Voie*));
  v->voieLeft[0] = &tabVoie[8];
  v->nbVoieLeft = 1;

  v->voieRight = NULL;
  v->nbVoieRight = 0;

  v->sens = v->currentSens = 0;
  v->typeTrain[0] = 1;
  v->typeTrain[1] = 1;
  v->typeTrain[2] = 1;
}
