Salutations !

+-------------------+
|    Crédits         |
+-------------------+

Projet réalisé durant l'immersion 2022 par le groupe 6 composé de:
-Corentin LEANDRE
-Thomas KEPPLER
-Pierre GIEN
-Ludovic ERTZER
-Ameen MOHD FAIRUZ
-yahya EL AILI
-Farah SALAMA
-Alex GIOVANNETTI

+-------------------+
|   UTILISATION	    |
+-------------------+


le jeu peut se lancer avec plusieur option : ./abalone -option
        -l pvp=> joueur contre joueur sous gtk
	-l noir => joueur noir contre ia blanc sous gtk
	-l blanc => joueur blanc contre ia noir sous gtk
	-ia => ia contre ia sous gtk
	--r_ia => joueur contre ia aléatoire
	-s XXXX => créer un serveur ia (ex:2000)
	-c XXX.XXX.XXX.XXX:YYYY (ex:127.0.0.1:2000)=> se connecter au serveur ia
	--port XXXX => créer un serveur (ex:2000)
	--connect XXX.XXX.XXX.XXX:YYYY (ex:127.0.0.1:2000)=> se connecter au serveur
	--help => avoir la liste des options. 


+-----------------------------+
|   REPARTION DES FICHIERS    |
+-----------------------------+
:
- main -> options
- abalon_terminal -> modeèle + terminal
- mouvement -> validation/légalité + effectuer le mouvement
- abalone_gtk -> modele et jeut en interface gtk.
- client -> creation la partie client du resau
- serveur-> creation la pertie serveur du resau
- ia -> implementation des ia aleatoir et ia min_max
- abalone_threads -> version threadée du jeu, modèle / vue
 

+-------------------------------+
|   COVERAGE ET DOCUMENTATION   |
+-------------------------------+

- https://app.codecov.io/gh/farahsalamaa/Abalone
- https://farahsalamaa.github.io/Abalone

