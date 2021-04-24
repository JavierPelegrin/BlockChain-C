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

int main(int argc, char **argv){
  BlockChain *f;
  int d, n, t;
  d = 4;
  n = 50;
  t = 5;
  for (int i = 0;i < argc; i++){
    printf("argv[%d] : \'%s\' \n",i,argv[i]);
  }
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
        printf("cambio n en 3\n");
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
    }if (argc > 7){
      fprintf(stderr, "Error: %s [OPTION] [INTEGER]\n",argv[0]);
      return 1;
    }
  }
  printf("Les options sont :\n\tDificulte = %d\n\tNombre Max de blocks = %d\n\tNombre max de transaction = %d\n\n",d,n,t);
  f = createBlockChain(d,t);
  for(int k = 0; k < blockchainSize(f); k++){
    printf("This is transaction %d : %s\n", k, BlockTransaction(f,k));
  }
  printf("This is BlockMerkleRoot of the block:\n\t %s\n",BlockMerkleRoot(f));
  printf("Block Genesis: %s\n\n", blockHash(f));

  for(int i = 0; i < n; i++){
    createBlock(f,t);
    for(int k = 0; k < blockchainSize(f); k++){
      printf("This is transaction %d : %s\n", k+1, BlockTransaction(f,k));
    }
    printf("This is BlockMerkleRoot of the block:\n\t %s\n",BlockMerkleRoot(f));
    printf("Block %d: %s\n\n",i,blockHash(f));
  }
  return 0;
}
