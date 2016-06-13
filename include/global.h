#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdbool.h>

#include "aiguillage.h"
#include "voie.h"
#include "train.h"

#define NB_VOIE 10
#define NB_AIGUILLAGE 4

int nbTrain;
Voie* tabVoie;
pthread_mutex_t mutex;
pthread_t* tid;
pthread_cond_t voieA, voieB, voieC, voieD, voieTGV, voieMG, voieMD, voieGL, voieTUN, voieLIGNE;
