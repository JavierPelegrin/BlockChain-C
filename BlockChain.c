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
  Block block[BLOCKCHAIN_SIZE_MAX];
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
BlockChain *createBlockChain(){
  BlockChain *blockChain = malloc(sizeof(BlockChain));
  Block block;
  blockChain->Dificulty = DIFICULTY;
  blockChain->size = 1;
  block.index = 0;
  block.timestamp = getTimeStamp();
  block.nbrTransaction = (rand() % TRANSACTION_MAX)+1;
  createGenesisT(&block);
  createNTransaction(&block);
  strcpy(block.merkleRoot,calculmerkleRoot(&block));
  mineBlock(&block);
  strcpy(block.hashPrev,block.hash);
  blockChain->block[0] = block;
  return blockChain;
}

/*!
   \brief "creation et ajout d'un block deja miner avec c'est transaction
   a une BlockChain"
   \param "BlockChain"
   \post "le hash du block a un nombre de 0 au debut egale a DIFICULTY"
*/
void createBlock(BlockChain *blockChain){
  Block block, lastBlock;
  lastBlock = blockFirst(blockChain);
  block.index = blockChain->size;
  blockChain->size++;
  block.timestamp = getTimeStamp();
  block.nbrTransaction = (rand() % TRANSACTION_MAX)+1;
  strcpy(block.hashPrev, lastBlock.hash);
  createNTransaction(&block);
  strcpy(block.merkleRoot,calculmerkleRoot(&block));
  mineBlock(&block);
  blockChain->block[block.index] = block;
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


Block blockFirst(BlockChain *blockChain){
  return blockChain->block[blockChain->size-1];
}

int blockchainSize(BlockChain *blockChain){
  return blockChain->block[blockChain->size-1].nbrTransaction;
}

char *blockHash(BlockChain *blockChain){
  printf("This is nonce number: %ld\n", blockChain->block[blockChain->size-1].nonce);
  return blockChain->block[blockChain->size-1].hash;
}

char *BlockMerkleRoot(BlockChain *blockChain){
  return blockChain->block[blockChain->size-1].merkleRoot;
}

char *BlockTransaction(BlockChain *blockChain, int i){
  return TurnChar(blockChain->block[blockChain->size-1].transaction,i);
}
