/*!
   \file "main.c"
   \brief "main du Project bonobo central banck"
   Project S4 Université Toulouse 3, Creation d'une BlockChain, simulation de
   crypto monais
   \author "PELEGRIN GARCIA Javier"
   \date "10"/"04"/"2021"
*/
/*
dfile para documentacion de file.
dfunc para documentacion de funciones
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sha256.h"
#include "sha256_utils.h"
#include "mine.h"
#include "BlockChain.h"
#include "transaction.h"

int main(){
  BlockChain *f;
  // ListMiner *l = createList(5);
  int i;
  // aleatMiner(l);
  f = createBlockChain();
  for(int k = 0; k < blockchainSize(f); k++){
    printf("This is transaction %d : %s\n", k, BlockTransaction(f,k));
  }
  printf("This is BlockMerkleRoot of the block:\n\t %s\n",BlockMerkleRoot(f));
  printf("Block Genesis: %s\n\n", blockHash(f));

  for(i = 0; i < 1000; i++){
    createBlock(f);
    for(int k = 0; k < blockchainSize(f); k++){
      printf("This is transaction %d : %s\n", k+1, BlockTransaction(f,k));
    }
    printf("This is BlockMerkleRoot of the block:\n\t %s\n",BlockMerkleRoot(f));
    printf("Block %d: %s\n\n",i,blockHash(f));
  }
  return 0;
}
