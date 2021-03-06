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

struct s_BlockChain {
  int Dificulty;
  int size;
  int nbrTransaction;
  Block *Genesis;
  Block *lastBlock;
};


/*!
   \brief "Optenir le jour et l'heure"
   \return "char* du jour et heure, ex: Fri Jan 19 13 :40 :09 2018"
*/
char *getTimeStamp(){
  time_t ltime;
  time(&ltime);
  return ctime(&ltime);
}

/*!
   \brief "creation de la BlockChain avec inisialitation du genesis"
   \post "le hash du block a un nombre de 0 au debut egale a DIFICULTY"
   \return "Structure BlockChain avec premier block genesis"
*/
BlockChain *createBlockChain(int Dificulty,int nbrTransactionMax){
  BlockChain *blockChain = malloc(sizeof(BlockChain));
  Block *block = malloc(sizeof(Block));
  blockChain->Dificulty = Dificulty;
  blockChain->size = 1;
  blockChain->nbrTransaction = nbrTransactionMax;
  block->index = 0;
  block->timestamp = getTimeStamp();
  block->nbrTransaction = 1;
  block->transaction = malloc(block->nbrTransaction*S_TRANSACTION_SIZE);
  createGenesisT(&block);
  //createNTransaction(&block);
  //strcpy(block->merkleRoot,calculmerkleRoot(block));
  strcpy(block->hashPrev, "0000000000000000000000000000000000000000000000000000000000000000");
  mineBlock(&block,0);
  block->next = NULL;
  block->prev = NULL;
  blockChain->Genesis = block;
  blockChain->lastBlock = block;
  return blockChain;
}

/*!
   \brief "creation et ajout d'un block deja miner avec c'est transaction
   a une BlockChain"
   \param "BlockChain"
   \post "le hash du block a un nombre de 0 au debut egale a DIFICULTY"
*/
void createBlock(BlockChain *blockChain){
  Block *block = malloc(sizeof(Block));
  block->index = blockChain->size;
  blockChain->size++;
  block->timestamp = getTimeStamp();
  block->nbrTransaction = (rand() % blockChain->nbrTransaction)+1;
  strcpy(block->hashPrev, blockChain->lastBlock->hash);
  block->transaction = malloc(blockChain->nbrTransaction*S_TRANSACTION_SIZE);
  createNTransaction(&block);
  strcpy(block->merkleRoot,calculmerkleRoot(block));
  mineBlock(&block,blockChain->Dificulty);

  blockChain->lastBlock->next = block;
  block->prev = blockChain->lastBlock;
  block->next = NULL;
  blockChain->lastBlock = block;
}

/*!
   \brief "Effacer un block et recalculer les hash et markleTree
   des blocks suivantes (fonction cheater)"
   \param "une BlockChain, position du block"
   \pre "Le nombre de block de la blockChain doit etre inferieur ou egale
   a @position"
   \post "Les hash des block suivants sont conformes a DIFICULTY,
   le block de la position @position a etait effacer"
*/
void removeBlock(BlockChain *blockChain, int position){
  /*
    Cette fonction devra effacer le block en position @position
    et recalculer donc toutes les hash
  */
  (void)blockChain;
  (void)position;
}


Block *blockFirst(BlockChain *blockChain){
  return blockChain->lastBlock;
}

int blockchainSize(BlockChain *blockChain){
  return blockChain->size;
}

int blockNbrTransactions(BlockChain * blockChain){
  return blockChain->lastBlock->nbrTransaction;
}

int indexLastBlock(BlockChain *blockChain){
  return blockChain->lastBlock->index;
}

char *blockHash(BlockChain *blockChain){
  printf("This is nonce number: %ld\n", blockChain->lastBlock->nonce);
  return blockChain->lastBlock->hash;
}

char *BlockMerkleRoot(BlockChain *blockChain){
  return blockChain->lastBlock->merkleRoot;
}

char *BlockTransaction(BlockChain *blockChain, int i){
  return TurnChar(blockChain->lastBlock->transaction,i);
}
