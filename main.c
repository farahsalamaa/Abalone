#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "abalone_terminal.h"
#include "abalone_gtk.h"

/**
 * \file main.c
 * \brief Fonction d'execution dans le terminal
*/

/**
 * \fn afficheOptions()
 * \brief Fonction qui affiche les options utilisable sur terminal
*/
void afficheOptions(){
    /* affiche toutes les options de lancement du programme */
    printf("Liste des options : \n");
    printf("\t--pvp => joueur contre joueur\n");
    printf("\t--r_ia => joueur contre ia aléatoire\n");
    printf("\t--gtk => lancer le mode gtk\n");
    printf("\t--port XXXX => créer un serveur (ex:2000)\n");
    printf("\t--connect XXX.XXX.XXX.XXX:YYYY (ex:127.0.0.1:2000)=> se connecter au serveur\n");

}

/**
 * \fn main(int argc, char **argv)
 * \brief 
 * \param argc longueur de l'entrée
 * \param argv les inputs de l'utilisateur
*/
int main(int argc, char **argv){

	if(argc < 2){ // vérifie qu'on a bien une option

        	fprintf(stderr, "Il  faut une option pour lancer le programme !\n./abalone --help pour voir les options\n");
        	return EXIT_FAILURE;

    	}
    	if(strcmp("--help", argv[1]) == 0){ // affichage des options
        	afficheOptions();
        	return EXIT_SUCCESS;
    	}
    	 else if(strcmp("--pvp", argv[1]) == 0){ // on lance le mode joueur contre joueur
    	 	play_game();
    	 }
         else if(strcmp("--r_ia", argv[1]) == 0){ // on lance le mode joueur contre ia aléatoire
             play_game_random_ia();
         }
    	 else if(strcmp("--gtk", argv[1]) == 0){
    	 	play_game_gtk(argc, argv);
    	 }
    
    	else{

        	fprintf(stderr,"Option invalide : %s !\n./abalone --help pour voir les options\n", argv[1]);
        	return EXIT_FAILURE;

   	 }
	return 0;
	
}
