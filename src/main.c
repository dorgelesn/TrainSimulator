#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NbTh 500      //Nombre de processus symbolisant les trains
#define N  100	//Nombre de gares

pthread_t tid[NbTh+1];
pthread_mutex_t mutex;
pthread_cond_t attendre, dormir;

//initialisations
int NbTrainAttente=0;    //Nombre de train en attente de gare

void initMutex(){
  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&attendre,NULL);
  pthread_cond_init(&dormir, NULL);
}

void garer ()
{
  pthread_mutex_lock(&mutex);
  if(NbTrainAttente>0)
  {
    pthread_cond_signal(&attendre);// dit à un train de s'installer sur le fauteuil
    usleep(15);
  }
  else{
    printf("le coiffeur dort car pas de Train \n");
    pthread_cond_wait(&dormir, &mutex);

     // dit à un train de s'installer sur le fauteuil
  }
  pthread_mutex_unlock(&mutex);

}

void train(int i)
{
  if(NbTrainAttente<N)
  {
    pthread_mutex_lock(&mutex);

    NbTrainAttente++;
    pthread_cond_signal(&dormir);// avertit le coiffeur qu'il est la et s'assoit
    printf("Le train %d avertit le coiffeur qu'il est la et s'assoit \n",i);

    // on deverouille le mutex et attend que la condition soit signalée
    pthread_cond_wait(&attendre, &mutex);// attend qu'on lui dise de s'installer
    NbTrainAttente --;
    printf("Le coiffeur invite le train %d pour s'installer et le garer \n",(int)i);

    pthread_mutex_unlock(&mutex);
  }
  else{
    printf("Le train %d ne trouve pas de place\n", i);
  }


}


void * fonc_coiffeur()
{

  while (1)  {
    garer();
    /* temps de coiffure d'un train */
    usleep(200000);
  }
}

void * fonc_train(void *i)
{
  usleep(500);
  train((int)i);

  /* temps de coiffure */
  usleep(200000);
  printf("Le train %d quitte le salon\n", (int) i);
}


int main()
{
  int num;

  initMutex();
  // creation de la thread coiffeur
  pthread_create(tid+NbTh,0,(void *(*)())fonc_coiffeur,(void*)NbTh);

  //creation des threads Train
  for(num=0;num<NbTh;num ++){
    pthread_create(tid+num,0,(void *(*)())fonc_train,(void*)num);
  }


  //attend la fin de toutes les threads Train
  for(num=0;num<NbTh;num ++)
  pthread_join(tid[num],NULL);


  /* liberation des ressources");*/

/*  for(num=0;num<NbTh;num ++)
    pthread_detach(tid[num]);*/

  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&attendre);
  pthread_cond_destroy(&dormir);


  exit(0);
}
