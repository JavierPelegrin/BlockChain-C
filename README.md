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



#### Exemple pour effectuer une exécution

```
$ ./bin/Projet -d 7 -n 50 -t 12
```

## Test d'exécution

Après une exécution sans paramètres on reçoit sur le terminal :

```
This is transaction 0 : Source CoinBase-Destination Creator, quantite: 50bnb
This is transaction 1 : Source user86-Destination user77, quantite: 16bnb
This is transaction 2 : Source user93-Destination user35, quantite: 37bnb
This is transaction 3 : Source user92-Destination user49, quantite: 22bnb
This is BlockMerkleRoot of the block:
	 090fc831c4801708518342c9201573c2faa7442c5c356022933a96af2ee4069d
This is nonce number: 40620
Block Genesis: 00007205a585bef0f660724919cb3a226f40ac2f225fab47d7bf636f86d83093

This is transaction 1 : Source user27-Destination user90, quantite: 10bnb
This is transaction 2 : Source user63-Destination user26, quantite: 41bnb
This is transaction 3 : Source user26-Destination user72, quantite: 37bnb
This is BlockMerkleRoot of the block:
	 993655b7a613654bfa0944cef1e0ba9ff87827c234000c904ea06aa63e93e168
This is nonce number: 71880
Block 0: 00008f8b108d33c673571a603c4f41cc05df5eb5605f731be1e9c3d2e930a27a

This is transaction 1 : Source user68-Destination user67, quantite: 30bnb
This is transaction 2 : Source user82-Destination user30, quantite: 13bnb
This is BlockMerkleRoot of the block:
	 16d949cefef76dca7302cfc9629253d6cd98a2773d26aaad14f73f855983889e
This is nonce number: 72609
Block 1: 0000f14a67411f0f6b7a71b71c653ad6a020cd77b4e84e73704e36d1865d6306

This is transaction 1 : Source user67-Destination user35, quantite: 30bnb
This is transaction 2 : Source user2-Destination user22, quantite: 9bnb
This is transaction 3 : Source user69-Destination user67, quantite: 44bnb
....
```

Ceci sont les informations plus importantes d'un block.

En premier lieu :

- les transaction de 1 à 5 sauf pour la première transaction, celle de la coinBase vers le Creator

- les user sont choisis au hasard entre 0 et 99

- le montant est aussi choisi au hasard entre 1 et 50.

Après on touve le merkleRoot qui est calculé avec des arbres équilibrés:

Si l'on commance avec `n` transaction le programme verifiera si `n` est égale à `2^x` avec le logarithme en base 2 et donc ajoutera les transaction nesesaires pour que `n = 2^x`

Après le merkleRoot on trouve le `nonce`, ce nombre est un `long int` qui est utilisé pour que le `hash256` satisfait la difficulté de la blockchain.

La dernière information est le `index` du block puis le `hash256` du block qui satisfait bien la dificulté par défaut de 4.



## Auteurs du projet

- **Javier Pelegrin Garcia** - développeur - Documentation
