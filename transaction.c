#include <stdio.h>

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "BlockChain.h"
#include "mine.h"
#include "sha256.h"
#include "transaction.h"
#include "sha256_utils.h"

/*
  Creer une Queue dynamique pour pouvoir louer entre 1 et TRANSACTION_MAX
  transactions
*/

struct s_Transaction{
  char *timestamp;
  int Emeteur;
  int Recepteur;
  int montant;
};

void create1Transaction(Block **b, int i){
  (*b)->transaction[i] = malloc(sizeof(Transaction));
  (*b)->transaction[i]->Emeteur = (rand() % 100);
  (*b)->transaction[i]->Recepteur = (rand() % 100);
  while ((*b)->transaction[i]->Emeteur == (*b)->transaction[i]->Recepteur){
    (*b)->transaction[i]->Recepteur = (rand() % 100);
  }
  (*b)->transaction[i]->timestamp = getTimeStamp();
  (*b)->transaction[i]->montant = (rand() % 50)+1;
}

void createNTransaction(Block **b){
  int i;
  for(i = 0; i < (*b)->nbrTransaction; i++){
    create1Transaction(b, i);
  }
}

void createGenesisT(Block **t){
  (*t)->transaction[0] = malloc(sizeof(Transaction));
  (*t)->transaction[0]->Emeteur = -1;
  (*t)->transaction[0]->Recepteur = 0;
  (*t)->transaction[0]->montant = 50;
  (*t)->transaction[0]->timestamp = getTimeStamp();
}

char *TurnChar(Transaction **t, int i){
  if (t[i]->Emeteur == -1){
    return "Genesis";
  }
  char *temp = malloc(sizeof(int));
  char *transac = malloc(sizeof(char)*50);
  sprintf(temp, "%d",t[i]->Emeteur);
  strcpy(transac,"Source user");
  strcat(transac,temp);
  strcat(transac,"-Destination user");
  sprintf(temp, "%d",t[i]->Recepteur);
  strcat(transac,temp);
  strcat(transac,", quantite: ");
  sprintf(temp,"%d",t[i]->montant);
  strcat(transac,temp);
  strcat(transac,"bnb");
  free(temp);
  return transac;
}

float aleatMiner(float recompense, int indexBlock){
  int miner = rand()%100;
  if (indexBlock == 0 || miner == 0){
    printf("Le miner Creator a mine le block, coinBase recompense: %f\n",recompense );
  }else{
    printf("Le miner %d a mine le block, coinBase recompense: %f\n",rand()%100,recompense);
  }
  indexBlock++;
  recompense = recompense/((indexBlock%25 == 0)+1);
  return recompense;
}
