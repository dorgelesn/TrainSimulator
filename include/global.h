#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#include "voie.h"
#include "train.h"

#define NB_VOIE 13
#define NB_AIGUILLAGE 4
#define MAX_TRAIN 10000000
#define TGV_PRIORITY 98
#define GL_PRIORITY 50
#define M_PRIORITY 10

int nbTrain; //nombre totale de train
int nbTGV, nbGL, nbM;
Voie* tabVoie; //tableau de l'ensemble des voies
pthread_mutex_t mutex; //mutex principal
pthread_t* tid; //tableau de threads pour les trains
