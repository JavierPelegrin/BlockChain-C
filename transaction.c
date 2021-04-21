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

void create1Transaction(Block *t, int i){
  t->transaction[i] = malloc(sizeof(Transaction));
  t->transaction[i]->Emeteur = (rand() % 100);
  t->transaction[i]->Recepteur = (rand() % 100);
  while (t->transaction[i]->Emeteur == t->transaction[i]->Recepteur){
    t->transaction[i]->Recepteur = (rand() % 100);
  }
  t->transaction[i]->timestamp = getTimeStamp();
  t->transaction[i]->montant = (rand() % 50)+1;
}

void createNTransaction(Block *b){
  int i;
  if(b->index == 0){
    for(i = 1; i < b->nbrTransaction; i++){

      create1Transaction(b, i);
    }
  }else{
    for(i = 0; i < b->nbrTransaction; i++){
      create1Transaction(b, i);
    }
  }
}

void createGenesisT(Block *t){
  t->transaction[0] = malloc(sizeof(Transaction));
  t->transaction[0]->Emeteur = -1;
  t->transaction[0]->Recepteur = 0;
  t->transaction[0]->montant = 50;
  t->transaction[0]->timestamp = getTimeStamp();
}


char *TurnChar(Transaction **t, int i){
  if (t[i]->Emeteur == -1){
    return "Source CoinBase-Destination Creator, quantite: 50bnb";
  }
  char *temp = malloc(sizeof(int));
  char *transac = malloc(50);
  sprintf(temp, "%d",t[i]->Emeteur);
  strcat(transac,"Source user");
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
