# BlockChain et simulation de transactions en C

Ce projet est encore en développement. Ceci est un projet pour l'UT3 du grupe 26.

## Installation

Ce projet est développé entièrement en C.

```
$ git clone https://github.com/JavierPelegrin/BlockChain-C.git
```

Le répertoire téléchargé contient un `makefile` et donc en exécutent la commande `make` le code sera compilé.

Un binaire exécutable est donc généré dans le répertoire `bin/` et appelé `Projet`.

## Exécution

Le programme pourra prendre en paramètre :

- La difficulté avec l'option `-d`
- Le nombre de block avec l'option `-n`
- Le nombre max de transaction par block avec l'option `-t`

Si le programme est appelé sans options les paramètres par défaut seront :

- Difficulté 4
- Nombre de block 1000
- Nombre max de transaction 5

La recompense par block est 50, et tous les 25 blocks elle est divisé entre 2.

#### Exemple pour effectuer une exécution

```
$ ./bin/Projet -d 7 -n 50 -t 12
```

## Test d'exécution

Après une exécution sans paramètres on reçoit sur le terminal :

```
$ ./bin/Project
Les options sont :
	Dificulte = 4
	Nombre max de blocks = 1000
	Nombre max de transaction = 5

Le miner 47 a miner le block, recompense: 50.000000
This is transaction 1 : Source CoinBase-Destination user1(Creator), quantite: 50bnb
This is BlockMerkleRoot of the block:
	 fdd5f859cbc7ab0b58d53f39448894c1052d9e8d47ff2aeb4a9eeebb70439abe
This is nonce number: 13685
Block Genesis: 0000c90c8e01160489844eb89f4cf475b620690848f0e7b08ee6039d29853280

Le miner 98 a miner le block, recompense: 50.000000
This is transaction 1 : Source user13-Destination user90, quantite: 35bnb
This is BlockMerkleRoot of the block:
	 2fab45611482239886b61b2702fe6afe7eb1ee4ec34ad94e2b6c940d4c46bb1a
This is nonce number: 27877
Block 1: 0000ef451757bfe06414750bc089cd8080a086d9f22a723c0890e2d60873bdc1

Le miner 52 a miner le block, recompense: 50.000000
This is transaction 1 : Source user17-Destination user83, quantite: 18bnb
This is transaction 2 : Source user44-Destination user17, quantite: 26bnb
This is transaction 3 : Source user57-Destination user50, quantite: 29bnb
This is transaction 4 : Source user54-Destination user47, quantite: 17bnb
....
```

Ceci sont les informations plus importantes d'un block.

En premier lieu, la recompense du miner:

La le miner est calculé aleatoirment entre 0 et 99.

Après cella :

- les transaction de 1 à 5 sauf pour la première transaction, celle de la coinBase vers le Creator
- les user sont choisis au hasard entre 0 et 99
- le montant est aussi choisi au hasard entre 1 et 50.

Après on touve le merkleRoot qui est calculé avec des arbres équilibrés:

Si l'on commance avec `n` transaction le programme verifiera si `n` est égale à `2^x` avec le logarithme en base 2 et donc ajoutera les transaction nesesaires pour que `n = 2^x`

Après le merkleRoot on trouve le `nonce`, ce nombre est un `long int` qui est utilisé pour que le `hash256` satisfait la difficulté de la blockchain.

La dernière information est le `index` du block puis le `hash256` du block qui satisfait bien la dificulté par défaut de 4.

## Auteurs du projet

- **Javier Pelegrin Garcia** - développeur - Documentation
