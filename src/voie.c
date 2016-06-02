#include "../include/global.h"

void func_voie(Voie* v){
  printf("Coucou je suis une voie\n");
}

void init_voieA(Voie* v){
  v->id = 0;
  //v->voieLeft = ;
  //v->vRight = ;
  v->sens = 1;
  v->typeTrain[0] = 1;
  v->typeTrain[1] = 1;
  v->typeTrain[2] = 0;
}

void init_voieB(Voie* v){
  v->id = 0;
  //v->voieLeft = ;
  //v->voieRight = ;
  v->sens = -1;
  v->typeTrain[0] = 1;
  v->typeTrain[1] = 1;
  v->typeTrain[2] = 0;
}

void init_voieC(Voie* v){
  v->id = 0;
  //v->voieLeft = ;
  //v->voieRight = ;
  v->sens = 1;
  v->typeTrain[0] = 1;
  v->typeTrain[1] = 1;
  v->typeTrain[2] = 0;
}
