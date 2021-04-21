#ifndef __MINER_H__
#define __MINE_H__

#include <sha256_utils.h>
#include "BlockChain.h"
#include "transaction.h"

typedef struct s_ListMiner ListMiner;
typedef struct s_Miner Miner;


ListMiner *createList(int nombreMineur);

void aleatMiner(ListMiner *listMiner);

#endif
