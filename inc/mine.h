#ifndef __MINE_H__
#define __MINE_H__

#include <stdbool.h>
#include "sha256_utils.h"
#include "transaction.h"
#include "BlockChain.h"

void calculHash(char hash[SHA256_BLOCK_SIZE*2+1], char *infos);

void createHash(Block *block);

bool verifieHash(char *hash, int d);

void mineBlock(Block *block, int Dificulty);

char *calculmerkleRoot(Block *block);

#endif
