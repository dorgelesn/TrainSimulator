#include <pthread.h>

typedef struct Train{
  int id;
  Direction direction;
  Voie position;
}Train;

void initTrain();
void deletTrain();
