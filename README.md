# TrainSimulator
Pour le projet LO41 à l'UTBM, nous avions pour but de modéliser le fonctionnement d'un réseau ferroviaire à partir d'algorithmes chargés de la coordination de l'ensemble des voies.
Dans notre sujet nous tiendrons compte des priorités que chaque train possède, de son sens de circulation ainsi que la capacité des voies. Ces contraintes permette de définir un ordre de déplacement et d'envisager des solutions pour éviter les collisions ou l'interblocage.

#Compilation

Un MAKEFILE a été implémenté donc il suffit de faire un make

#Execution

Il suffit d'executer le fichier bin/trainsimulator ou de faire make run
Par défaut il y aura une instance avec 2 trains de chaque type.

#Configuration (optionelle)

Il possible de passer en argument le nombre de train souhaité. Ainsi le premier argument représente le nombre de TGV, le deuxième le nombre de Train GL et enfin le troisième le nombre de Train de Marchandises.
Le sens est donné de façon aléatoire au train lors de leur initialisation

