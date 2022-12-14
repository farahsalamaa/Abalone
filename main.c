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
    printf("\t-l pvp=> joueur contre joueur sous gtk\n");
    printf("\t-l noir => joueur noir contre ia blanc sous gtk\n");
    printf("\t-l blanc => joueur blanc contre ia noir sous gtk\n");
    printf("\t-ia => ia contre ia sous gtk\n");
    printf("\t--r_ia => joueur contre ia aléatoire\n");
 
    printf("\t--port XXXX => créer un serveur (ex:2000)\n");
    printf("\t--connect XXX.XXX.XXX.XXX:YYYY (ex:127.0.0.1:2000)=> se connecter au serveur\n");

}

/**
 * \fn main(int argc, char **argv)
 * \brief 
 * \param argc Longueur de l'entrée
 * \param argv Les inputs de l'utilisateur
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
        else if(strcmp("--terminator", argv[1]) == 0) {
            play_terminator();
        }
    	 else if(strcmp("--pvp", argv[1]) == 0){ // on lance le mode joueur contre joueur
    	 	play_game();
    	}
        else if(strcmp("--r_ia", argv[1]) == 0){ // on lance le mode joueur contre ia aléatoire
            play_game_random_ia();
        }
         else if(strcmp("--port", argv[1]) == 0){
			play_game_server(argv[2]);
		}
		else if(strcmp("--connect", argv[1]) == 0){
			play_game_client(argv[2]);
		}
        else if(strcmp("-ia", argv[1]) == 0){
    	 	play_game_gtk3(argc, argv);
    	}
         
        else if(strcmp("-l", argv[1]) == 0){
          	if(strcmp("noir", argv[2]) == 0){
    	 	play_game_gtk2(argc, argv);
    	 	
    	 	}
    	 	if(strcmp("blanc", argv[2]) == 0){
    	 	play_game_gtk2(argc, argv);
    	 	
    	 	}
    	 	if(strcmp("pvp", argv[2]) == 0){
    	 	play_game_gtk(argc, argv);
    	 	
    	 	}
          }
          	
   
    	 
    
    	else{

        	fprintf(stderr,"Option invalide : %s !\n./abalone --help pour voir les options\n", argv[1]);
        	return EXIT_FAILURE;

   	 }
	return 0;
	
}
