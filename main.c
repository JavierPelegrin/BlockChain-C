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
#include <time.h>
#include "sha256.h"
#include "sha256_utils.h"
#include "mine.h"
#include "BlockChain.h"
#include "transaction.h"

int main(int argc, char **argv){
  // srand(time(NULL));

  BlockChain *f;
  int d, n, t;
  float recompense = RECOMPENSE;
  d = 4;
  n = BLOCKCHAIN_SIZE_MAX;
  t = 5;
  // testMerkleTreeFunction();
  if(argc > 1){
    if (argc%2 == 0 && argc != 0){
      fprintf(stderr, "Error: %s [OPTION] [INTEGER]\n",argv[0]);
      return 1;
    }
    if (strcmp(argv[1],"-d") == 0){
      d = atoi(argv[2]);
    }else if (strcmp(argv[1],"-n") == 0){
      n = atoi(argv[2]);
    }else if (strcmp(argv[1],"-t") == 0){
      t = atoi(argv[2]);
    }else{
      fprintf(stderr, "Error: %s [OPTION] [INTEGER]\n",argv[0]);
      return 1;
    }

    if(argc > 3){
      if (strcmp(argv[3],"-d") == 0){
        d = atoi(argv[4]);
      }else if (strcmp(argv[3],"-n") == 0){
        n = atoi(argv[4]);
      }else if (strcmp(argv[3],"-t") == 0){
        t = atoi(argv[4]);
      }else{
        fprintf(stderr, "Error: %s [OPTION] [INTEGER]\n",argv[0]);
        return 1;
      }
    }
    if(argc > 5){
      if (strcmp(argv[5],"-d") == 0){
        d = atoi(argv[6]);
      }else if (strcmp(argv[5],"-n") == 0){
        n = atoi(argv[6]);
      }else if (strcmp(argv[5],"-t") == 0){
        t = atoi(argv[6]);
      }else{
        fprintf(stderr, "Error: %s [OPTION] [INTEGER]\n",argv[0]);
        return 1;
      }
    }
  }

  printf("Les options sont :\n\tDificulte = %d\n\tNombre max de blocks = %d\n\tNombre max de transaction = %d\n\n",d,n,t);
  f = createBlockChain(d,t);
  recompense = aleatMiner(recompense,indexLastBlock(f));
  for(int k = 0; k < blockNbrTransactions(f); k++){
    printf("This is transaction %d : %s\n", k+1, BlockTransaction(f,k));
  }
  printf("Block Genesis: %s\n\n", blockHash(f));

  for(int i = 0; i < n; i++){
    createBlock(f);
    recompense = aleatMiner(recompense,indexLastBlock(f));
    for(int k = 0; k < blockNbrTransactions(f); k++){
      printf("This is transaction %d : %s\n", k+1, BlockTransaction(f,k));
    }
    printf("This is BlockMerkleRoot of the block:\n\t %s\n",BlockMerkleRoot(f));
    printf("Block %d: %s\n\n",i+1,blockHash(f));
  }
  return 0;
}
