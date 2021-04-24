# BlockChain et simulation de transactions en C

Ce projet est encore en développement. Ceci est un projet pour l'UT3 du grupe 26.

## Installation 

Ce projet est développé entièrement en C.

```

$ git clone https://github.com/JavierPelegrin/BlockChain-C.git

```

Le répertoire téléchargé contient un `makefile` et donc en exécutent la commande `make` le code sera compilé.

Un binaire exécutable est donc généré dans le répertoire `bin/` et appelé `Projet`.

## Exécution (En développent)

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

50964

Block Genesis: 0000e4b3ac413f4d1cd84ff2165875ae8f104cec9585f777040c18615ffcf086



This is transaction 1 : Source user27-Destination user90, quantite: 10bnb

This is transaction 2 : Source user63-Destination user26, quantite: 41bnb

This is transaction 3 : Source user26-Destination user72, quantite: 37bnb

63844

Block 0: 00003b1e4ab80f8399209aa56c8648ee6ed6a6465a3d0590afbf701b8ffc67f8



This is transaction 1 : Source user68-Destination user67, quantite: 30bnb

This is transaction 2 : Source user82-Destination user30, quantite: 13bnb

62793

Block 1: 0000af538acabb30f32ddaa4c21a7f36504f5a791a217b399cd6edc1603fe517



This is transaction 1 : Source user67-Destination user35, quantite: 30bnb

This is transaction 2 : Source user2-Destination user22, quantite: 9bnb

This is transaction 3 : Source user69-Destination user67, quantite: 44bnb

....

```

Cela est les informations plus importantes d'un block.

En premier lieu :

- les transaction de 1 à 5 sauf pour la première transaction, celle de la coinBase vers le Creator

- les user sont choisi au hasard entre 0 et 99

- le montant est aussi choisi au hasard entre 1 et 50.



Après la transaction on trouve le nonce, ce nombre est un `long int` qui est utilisé pour que le hash256 satisfait la difficulté de la blockchain.



La dernière information est le index du block puis le hash du block qui satisfais bien la dificulté par défaut de 4.



## Auteurs du projet

- **Javier Pelegrin Garcia** - développeur - Documentation
