#include <stdio.h>

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "BlockChain.h"
#include "transaction.h"
#include "mine.c"
#include "miner.h"
#include "sha256.h"
#include "sha256_utils.h"

struct s_ListMiner {
  Miner *Genesis;
  int size;
};

struct s_Miner {
  int index;
  int argent;
  Miner *next;
};

ListMiner *createList(int nombreMineur){
  ListMiner *l = malloc(sizeof(ListMiner));
  Miner *miner = malloc(sizeof(Miner));
  int i;
  l->size = 1;
  miner->index = 0;
  miner->next = NULL;
  miner->argent = 50;
  l->Genesis = miner;
  for (i = 1; i < nombreMineur; i++){
    l = *minerPush(l,i);
  }
  return l;
}

ListMiner *minerPush(ListMiner l, int index){
  Miner miner = malloc(sizeof(miner));
  miner.index = index;
  l.size++;
  miner.next = NULL;
  miner.argent = 50;
  l->
}

void aleatMiner(ListMiner *listMiner){
  /*
    Cette fonction devra choisir un mineur aleatoire de la liste,
    miner un block (creer un block), etatribuer a se miner une somme
    d'argent dependent de combient de block existend deja.
  */
  printf("%d\n",listMiner->size);
  (void)listMiner;
}
