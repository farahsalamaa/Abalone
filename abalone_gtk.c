#include <stdlib.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "debug.h"
#include "abalone_terminal.h"
#include "mouvement.h"
#include "const.h"


 time_t start;
struct Board{
	GtkWidget* drawing_area;
	GtkWidget* label;
	GtkWidget* label_error;
	GtkWidget* label_error2;
	GtkWidget* message;
	GtkWidget* message3;
	PAbalone game;
	//gpointer data;
};
typedef struct Board* PBoard;

PBoard new_board(GtkWidget* drawing_area, GtkWidget* label,GtkWidget* label_error,GtkWidget* label_error2,GtkWidget* message,GtkWidget* message3,PAbalone game){
	PBoard board= malloc(sizeof(struct Board));
	board->label = label;
	board->label_error = label_error;
	board->label_error2 = label_error2;
	board->drawing_area = drawing_area;
	board->message = message;
	board->message3 = message3;
	board->game= game;
	//board->data;
	return board;
}

void label_joueur(PAbalone game,GtkWidget* label );
void label_msg(PAbalone game,GtkWidget* label_error );
void label_msg2(PAbalone game,GtkWidget* label_error2 );
void do_drawing(cairo_t *cr);
void do_drawing2(cairo_t *cr);
void do_drawing3(cairo_t *cr);
void on_destroy(GtkWidget *widget, gpointer data);
void button_cb(GtkWidget *widget, gpointer data,int argc, char **argv);
void button_cb2(GtkWidget *widget, gpointer data,int argc, char **argv);
void button_cb3(GtkWidget *widget, gpointer data,int argc, char **argv);
gboolean draw_cb(GtkWidget *widget, cairo_t *cr, gpointer data);
void onActivateEntry(GtkEntry *entry, gpointer data);
 void draw_black_ball(cairo_t *cr,int i,int j);
  void draw_white_ball(cairo_t *cr,int i,int j,PAbalone game);
void msg(PAbalone game,GtkWidget* message );
void game_gtk_random_ia(PBoard board, gchar* text);
void game_gtk(PBoard board, gchar* text);
 void onActivateEntry2(GtkEntry *entry, gpointer data);
 void game_gtk_random_ia2(PBoard board, gchar* text);
 void game_gtk_random_ia_v_ia(PBoard board, gchar* text);
 void onActivateEntry3(GtkEntry *entry, gpointer data);
 void msg3(PAbalone game,GtkWidget* message,gchar* histomove);
 
int button_clicked;
int compteur_tour;
int game_mode;

char* board_historique[5];
int cpt_board=0;

 
void play_game_gtk(int argc, char **argv){

 GtkWidget *window;    
 GtkWidget *vBox;    
 GtkWidget *button;    
 GtkWidget *drawing_area; 
 GtkWidget* message;
 GtkWidget* message3;
 GtkWidget* label;
 GtkWidget* label_error;
  GtkWidget* label_error2;
  GtkWidget *monimage;//Declaration  
    GtkWidget *image;//Declaration  
 //GtkWidget *message;
 //button_clicked = FALSE;  
 
 //PAbalone game = malloc(1000);
 //game=new_abalone();
 
 PAbalone game=new_abalone();

 
 /* Initialisation of GTK+ */    
 gtk_init(&argc, &argv);  
 compteur_tour=1;

	
start = time(NULL);  
 /* Creation of main window */    
 window = gtk_window_new(GTK_WINDOW_TOPLEVEL);    
 /* Center window on screen */    
 gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);    
 /* Default window size */    
 gtk_window_set_default_size(GTK_WINDOW(window), 320, 200);    
 /* Set window title */    
 gtk_window_set_title(GTK_WINDOW(window), "Abalone");
 
 
 
    /* Creation of a vertical box */    
 vBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
 /* Insertion of the box in the window */    
 gtk_container_add(GTK_CONTAINER(window), vBox);
 /* Creation of the drawing area */    
 drawing_area = gtk_drawing_area_new();    
  /*! creation du label d'en haut */	
	label = gtk_label_new(NULL);
	gtk_box_pack_start(GTK_BOX(vBox), label, FALSE, FALSE, 0);
	message = gtk_label_new(NULL);
	label_error = gtk_label_new(NULL);
	label_error2 = gtk_label_new(NULL);
	
	
/*
monimage = gtk_image_new_from_file("./win.gif");  
 gtk_box_pack_start(GTK_BOX(vBox), monimage, FALSE, FALSE, 0);
*/

 /* Set a minimum size */    
	 gtk_widget_set_size_request(drawing_area, 420, 420);    
 /* Insertion of the drawing area in the box */    
 gtk_box_pack_start(GTK_BOX(vBox), drawing_area, TRUE, TRUE, 10);    
  PBoard board = new_board(drawing_area,label,label_error,label_error2,message,message3,game);	
  
  //game->player = COULEUR_BLANC;
  
 label_joueur(board->game, board->label);


 


 gtk_box_pack_start(GTK_BOX(vBox), message, FALSE, FALSE, 0);
 
 gtk_box_pack_start(GTK_BOX(vBox), label_error, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(vBox), label_error2, FALSE, FALSE, 0);
   label_msg(board->game, board->label_error);
      label_msg2(board->game, board->label_error2);
      gchar* start="start";
       msg3(board->game, board->message,start);
     // msg(board->game, board->message);
 /* Creation of a button */    
 button = gtk_button_new_with_label("Rejouer");    
 /* Connection of signal named "clicked" */    
 g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(button_cb), drawing_area);    

 
 
 /* Insertion of the message in the box */    
 //gtk_box_pack_start(GTK_BOX(vBox), message, FALSE, FALSE, 0); 
 
  /* Creation of a text zone */
 GtkWidget* entry = gtk_entry_new();
 /* Connection to the signal named "activate" */
  g_signal_connect(G_OBJECT(entry), "activate", G_CALLBACK(onActivateEntry),board);
 /* Insertion in vBox */
 gtk_box_pack_start(GTK_BOX(vBox), entry, FALSE, TRUE, 0);
 
  /* Insertion of the button in the box */    
 gtk_box_pack_start(GTK_BOX(vBox), button, FALSE, FALSE, 0);   
 
 /* Signals used to draw the content of the widget */    
 g_signal_connect(drawing_area, "draw", G_CALLBACK(draw_cb), board);  
 


   
 /* Connection of signal named "destroy" */    
 g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(on_destroy), NULL);    
 /* Make window and all its content visible */    
 gtk_widget_show_all(window); 
 gtk_widget_hide(label_error);   
  gtk_widget_hide(label_error2);   
   // gtk_widget_hide(monimage);   
 /* Start main event loop */    
 gtk_main();    
 //return EXIT_SUCCESS;
 
 }
 
 
void play_game_gtk2(int argc, char **argv){

 GtkWidget *window;    
 GtkWidget *vBox;    
 GtkWidget *button;    
 GtkWidget *drawing_area; 
 GtkWidget* message;
 GtkWidget* message3;
 GtkWidget* label;
 GtkWidget* label_error;
  GtkWidget* label_error2;
  GtkWidget *monimage;//Declaration  
    GtkWidget *image;//Declaration  
 //GtkWidget *message;
 //button_clicked = FALSE;  
 
 //PAbalone game = malloc(1000);
 //game=new_abalone();
 
 PAbalone game=new_abalone();

 
 /* Initialisation of GTK+ */    
 gtk_init(&argc, &argv);  
 

	
start = time(NULL);  
 /* Creation of main window */    
 window = gtk_window_new(GTK_WINDOW_TOPLEVEL);    
 /* Center window on screen */    
 gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);    
 /* Default window size */    
 gtk_window_set_default_size(GTK_WINDOW(window), 320, 200);    
 /* Set window title */    
 gtk_window_set_title(GTK_WINDOW(window), "Abalone");
 
 
 
    /* Creation of a vertical box */    
 vBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
 /* Insertion of the box in the window */    
 gtk_container_add(GTK_CONTAINER(window), vBox);
 /* Creation of the drawing area */    
 drawing_area = gtk_drawing_area_new();    
  /*! creation du label d'en haut */	
	label = gtk_label_new(NULL);
	gtk_box_pack_start(GTK_BOX(vBox), label, FALSE, FALSE, 0);
	message = gtk_label_new(NULL);
	label_error = gtk_label_new(NULL);
	label_error2 = gtk_label_new(NULL);
	
	
/*
monimage = gtk_image_new_from_file("./win.gif");  
 gtk_box_pack_start(GTK_BOX(vBox), monimage, FALSE, FALSE, 0);
*/

 /* Set a minimum size */    
	 gtk_widget_set_size_request(drawing_area, 420, 420);    
 /* Insertion of the drawing area in the box */    
 gtk_box_pack_start(GTK_BOX(vBox), drawing_area, TRUE, TRUE, 10);    
  PBoard board = new_board(drawing_area,label,label_error,label_error2,message,message3,game);	

  if(strcmp("blanc", argv[2]) == 0 || game_mode==5){ //Le game_mode pour lorsqu'on fait rejouer que l'ia noir commence son coup car on a plus argv en mémoire
  	game_mode=5;
  	play_random_move(game->board,game->player);
  	game->player = COULEUR_BLANC;

  }
  else if(strcmp("noir", argv[2]) == 0){
  	
  	game->player = COULEUR_NOIR;
  }

 label_joueur(board->game, board->label);

 gtk_box_pack_start(GTK_BOX(vBox), message, FALSE, FALSE, 0);
 
 gtk_box_pack_start(GTK_BOX(vBox), label_error, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(vBox), label_error2, FALSE, FALSE, 0);
   label_msg(board->game, board->label_error);
      label_msg2(board->game, board->label_error2);
      msg(board->game, board->message);
 /* Creation of a button */    
 button = gtk_button_new_with_label("Rejouer");    
 /* Connection of signal named "clicked" */    
 g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(button_cb2), drawing_area);    

 
 
 /* Insertion of the message in the box */    
 //gtk_box_pack_start(GTK_BOX(vBox), message, FALSE, FALSE, 0); 
 
  /* Creation of a text zone */
 GtkWidget* entry = gtk_entry_new();
 /* Connection to the signal named "activate" */
  g_signal_connect(G_OBJECT(entry), "activate", G_CALLBACK(onActivateEntry2),board);
 /* Insertion in vBox */
 gtk_box_pack_start(GTK_BOX(vBox), entry, FALSE, TRUE, 0);
 
  /* Insertion of the button in the box */    
 gtk_box_pack_start(GTK_BOX(vBox), button, FALSE, FALSE, 0);   
 
 /* Signals used to draw the content of the widget */    
 g_signal_connect(drawing_area, "draw", G_CALLBACK(draw_cb), board);  
 


   
 /* Connection of signal named "destroy" */    
 g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(on_destroy), NULL);    
 /* Make window and all its content visible */    
 gtk_widget_show_all(window); 
 gtk_widget_hide(label_error);   
  gtk_widget_hide(label_error2);   
   // gtk_widget_hide(monimage);   
 /* Start main event loop */    
 gtk_main();    
 //return EXIT_SUCCESS;
 
 }
 
 
 void play_game_gtk3(int argc, char **argv){

 GtkWidget *window;    
 GtkWidget *vBox;    
 GtkWidget *button;    
 GtkWidget *drawing_area; 
 GtkWidget* message;
  GtkWidget* message3;
 GtkWidget* label;
 GtkWidget* label_error;
  GtkWidget* label_error2;
  GtkWidget *monimage;//Declaration  
    GtkWidget *image;//Declaration  
 //GtkWidget *message;
 //button_clicked = FALSE;  
 
 //PAbalone game = malloc(1000);
 //game=new_abalone();
 
 PAbalone game=new_abalone();

 compteur_tour=0;
 game_mode=6;
 /* Initialisation of GTK+ */    
 gtk_init(&argc, &argv);  
 
	
start = time(NULL);  
 /* Creation of main window */    
 window = gtk_window_new(GTK_WINDOW_TOPLEVEL);    
 /* Center window on screen */    
 gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);    
 /* Default window size */    
 gtk_window_set_default_size(GTK_WINDOW(window), 320, 200);    
 /* Set window title */    
 gtk_window_set_title(GTK_WINDOW(window), "Abalone");
 
 
 
    /* Creation of a vertical box */    
 vBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
 /* Insertion of the box in the window */    
 gtk_container_add(GTK_CONTAINER(window), vBox);
 /* Creation of the drawing area */    
 drawing_area = gtk_drawing_area_new();    
  /*! creation du label d'en haut */	
	label = gtk_label_new(NULL);
	gtk_box_pack_start(GTK_BOX(vBox), label, FALSE, FALSE, 0);
	message = gtk_label_new(NULL);
	label_error = gtk_label_new(NULL);
	label_error2 = gtk_label_new(NULL);
	
	
	
/*
monimage = gtk_image_new_from_file("./win.gif");  
 gtk_box_pack_start(GTK_BOX(vBox), monimage, FALSE, FALSE, 0);
*/

 /* Set a minimum size */    
	 gtk_widget_set_size_request(drawing_area, 420, 420);    
 /* Insertion of the drawing area in the box */    
 gtk_box_pack_start(GTK_BOX(vBox), drawing_area, TRUE, TRUE, 10);    
  PBoard board = new_board(drawing_area,label,label_error,label_error2,message,message3,game);	
  
  //game->player = COULEUR_BLANC;
  
 label_joueur(board->game, board->label);


 


 gtk_box_pack_start(GTK_BOX(vBox), message, FALSE, FALSE, 0);
 
 gtk_box_pack_start(GTK_BOX(vBox), label_error, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(vBox), label_error2, FALSE, FALSE, 0);
   label_msg(board->game, board->label_error);
      label_msg2(board->game, board->label_error2);
      msg(board->game, board->message);
 /* Creation of a button */    
 button = gtk_button_new_with_label("Rejouer");    
 /* Connection of signal named "clicked" */    
 g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(button_cb3), drawing_area);    

 
 
 /* Insertion of the message in the box */    
 //gtk_box_pack_start(GTK_BOX(vBox), message, FALSE, FALSE, 0); 
 
  /* Creation of a text zone */
 GtkWidget* entry = gtk_entry_new();
 /* Connection to the signal named "activate" */
  g_signal_connect(G_OBJECT(entry), "activate", G_CALLBACK(onActivateEntry3),board);
 /* Insertion in vBox */
 gtk_box_pack_start(GTK_BOX(vBox), entry, FALSE, TRUE, 0);
 
  /* Insertion of the button in the box */    
 gtk_box_pack_start(GTK_BOX(vBox), button, FALSE, FALSE, 0);   
 
 /* Signals used to draw the content of the widget */    
 g_signal_connect(drawing_area, "draw", G_CALLBACK(draw_cb), board);  
 


   
 /* Connection of signal named "destroy" */    
 g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(on_destroy), NULL);    
 /* Make window and all its content visible */    
 gtk_widget_show_all(window); 
 gtk_widget_hide(label_error);   
  gtk_widget_hide(label_error2);   
   // gtk_widget_hide(monimage);   
 /* Start main event loop */    
 gtk_main();    
 //return EXIT_SUCCESS;
 
 }
 
 
 void on_destroy(GtkWidget *widget, gpointer data){    /* Halt main event loop */    
 gtk_main_quit();
 }

 void clear(cairo_t *cr){    /* Save current context */    
 cairo_save(cr);    
 cairo_set_source_rgb(cr, 1, 1, 1);    
 cairo_paint(cr);    /* Restore context */    
 cairo_restore(cr);
 }
 
 void draw_black_ball(cairo_t *cr,int i,int j){
 
 	/*cairo_pattern_t *r1; 
 	cairo_translate(cr, 70, 70);
  
  	r1 = cairo_pattern_create_radial(30, 30, 10, 30, 30, 90);
  	cairo_pattern_add_color_stop_rgba(r1, 0, 1, 1, 1, 1);
  	cairo_pattern_add_color_stop_rgba(r1, 1, 0.6, 0.6, 0.6, 1);
  	cairo_set_source(cr, r1);
  	cairo_arc(cr, 0, 0, 17, 0, M_PI * 2);
  	cairo_fill(cr);
  	cairo_pattern_destroy(r1);*/
  	/*cairo_set_line_width(cr,4);
  	cairo_set_source_rgb(cr,0.69,0.19,0);*/
  	cairo_arc(cr, 70+40*i, 70+40*j , 15, 0, 2 * M_PI);
	//cairo_stroke_preserve(cr);
	cairo_set_source_rgba(cr,0,0,0,1);
	cairo_fill (cr);
 }
 
  void draw_white_ball(cairo_t *cr,int i,int j,PAbalone game){
 
 	/*cairo_pattern_t *r2; 
  	cairo_translate(cr, 70+40*j, 70+40*i);
  
  	r2 = cairo_pattern_create_radial(0, 0, 9, 0, 0, 35);  
  	cairo_pattern_add_color_stop_rgb(r2, 0, 0, 0, 0);
  	cairo_pattern_add_color_stop_rgb(r2, 0.8, 1, 1, 0);
  	cairo_set_source(cr, r2);
  	cairo_arc(cr, 0, 0, 17, 0, M_PI * 2);
  	cairo_fill(cr);  
  	cairo_pattern_destroy(r2);*/
  	/*cairo_set_line_width(cr,4);
  	cairo_set_source_rgb(cr,0.69,0.19,0);
  	cairo_arc(cr, 70+40*i, 70+40*j , 17, 0, 2 * M_PI);*/
  	cairo_arc(cr, 70+40*i, 70+40*j , 17, 0, 2 * M_PI);
  	//cairo_set_source_rgba(cr,255,255,255,0.33);
  	//cairo_stroke_preserve(cr);
	cairo_set_source_rgba(cr,255,255,255,1);
	cairo_fill (cr);
	

	
	
 }


void draw(cairo_t *cr,PAbalone game){ 

	
   	/* Save current context */    
	cairo_save(cr);
	
	cairo_pattern_t *pat1;  
	if (game->player==COULEUR_BLANC){
   
  		pat1 = cairo_pattern_create_linear(0.0, 0.0,  650.0, 650.0);

  		gdouble j;
  		gint count = 1;
  		for ( j = 0.1; j < 1; j += 0.1 ) {
      		if (( count % 2 ))  {
          		cairo_pattern_add_color_stop_rgb(pat1, j, 162, 0, 255);
      		} else { 
          		cairo_pattern_add_color_stop_rgb(pat1, j, 0, 255, 240);
      		}
   		count++;
  		}
  	}
  	else {
   
  		pat1 = cairo_pattern_create_linear(0.0, 0.0,  650.0, 650.0);

  		gdouble j;
  		gint count = 1;
  		for ( j = 0.1; j < 1; j += 0.1 ) {
      		if (( count % 2 ))  {
          		cairo_pattern_add_color_stop_rgb(pat1, j, 1, 0.4, 0);
      		} else { 
          		cairo_pattern_add_color_stop_rgb(pat1, j, 0.9,0 , 0);
      		}
   			count++;
  		}
  	}


  	cairo_rectangle(cr, 0, 0, 600, 600);
  	cairo_set_source(cr, pat1);
  	cairo_fill(cr);  
  
  	cairo_pattern_destroy(pat1);
  	/*! dessin du fond de damier, couleur beige */
	cairo_rectangle(cr, 10 + 40, 10 + 40, 320, 320);
   	cairo_set_source_rgb(cr,0.9294117, 0.811764, 0.6352);
   	cairo_fill(cr);
   	
	
	/*! ajout des cases marron sur le fond beige, obtention du damier */
	for (int i = 0; i < 4; i++){
		for (int j=0; j<4; j++) {
        	cairo_rectangle(cr, 40 + 40+10 + 40 * 2 * i, 10+j*40*2 + 40, 40, 40);
		    cairo_set_source_rgb(cr,0.6862745, 0.5333333, 0.38431372);
		    cairo_fill(cr);
		    cairo_rectangle(cr, 40 + 10 + 40 * 2 * i, 40+10+j*40*2 + 40, 40, 40);
		    cairo_set_source_rgb(cr,0.6862745, 0.5333333, 0.38431372);
		    cairo_fill(cr);
		}
	}

	
	
	/*! affichage des numeros des cases en abscisses */
	cairo_set_font_size(cr, 16);
	cairo_set_source_rgb(cr, 255, 255, 255);
	
	cairo_move_to(cr, 40 + 25, 40);
	cairo_show_text(cr, "1");
	cairo_move_to(cr, 40*2 + 25, 40);
	cairo_show_text(cr, "2");
	cairo_move_to(cr, 40*3 + 25, 40);
	cairo_show_text(cr, "3");
	cairo_move_to(cr, 40*4 + 25, 40);
	cairo_show_text(cr, "4");
	cairo_move_to(cr, 40*5 + 25, 40);
	cairo_show_text(cr, "5");
	cairo_move_to(cr, 40*6 + 25, 40);
	cairo_show_text(cr, "6");
	cairo_move_to(cr, 40*7 + 25, 40);
	cairo_show_text(cr, "7");
	cairo_move_to(cr, 40*8 + 25, 40);
	cairo_show_text(cr, "8");



	/*! affichage des lettres des cases en ordonnees */
	cairo_move_to(cr, 30, 40 + 35);
	cairo_set_source_rgb(cr, 255, 255, 255);
	cairo_show_text(cr, "A");
	cairo_move_to(cr, 30, 2*40 + 35);
	cairo_show_text(cr, "B");
	cairo_move_to(cr, 30, 3*40 + 35);
	cairo_show_text(cr, "C");
	cairo_move_to(cr, 30, 4*40 + 35);
	cairo_show_text(cr, "D");
	cairo_move_to(cr, 30, 5*40 + 35);
	cairo_show_text(cr, "E");
	cairo_move_to(cr, 30, 6*40 + 35);
	cairo_show_text(cr, "F");
	cairo_move_to(cr, 30, 7*40 + 35);
	cairo_show_text(cr, "G");
	cairo_move_to(cr, 30, 8*40 + 35);
	cairo_show_text(cr, "H");
	
	
	//cairo_pattern_t *r1; 
	//cairo_pattern_t *r2;
	
	/*! dessin des pions en fonction de leur position */
	for (int i=0; i<8; i++){
		for (int j=0; j<8; j++){
			
			
			switch (game->board[j][i]) {
				
				//! affichage pions blancs 
				case 'B':
				
					draw_white_ball(cr,i,j,game);		
					break;

				
				//! affichage pions noirs 
				case 'N':
				
					draw_black_ball(cr,i,j);
					break;

			}
			
		}
	}
	
	

	if (game->state==STATE_WON_BLANC) do_drawing(cr);
	else if (game->state==STATE_WON_NOIR) do_drawing2(cr);
	else if (game->state==STATE_TIMEOUT) do_drawing3(cr);

 	cairo_restore(cr);
}
 
 /**
* \fn label_joueur
* \brief permet de changer le label du haut en fonction du joueur a qui c'est le tour
*/
void msg(PAbalone game,GtkWidget* message ){
	gchar* str;
	GtkWidget* vBox;
	vBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	if (game_mode==6){
		str=  g_locale_to_utf8("<span foreground=\"#FFFFFF\">Faites \"Entrée\" pour que l'ia joue un coup</span>", -1, NULL, NULL, NULL);  
	}
	else {
	 str=  g_locale_to_utf8("<span foreground=\"#FFFFFF\">Inserez votre mouvement, ex : \"B1:C3\"</span>", -1, NULL, NULL, NULL);  
	  
	 }
	gtk_label_set_markup(GTK_LABEL(message), str);
	
	g_free(str);
	
}

void msg3(PAbalone game,GtkWidget* message3,gchar* histomove){
	gchar* str;
	
	/*gchar* msg="<span foreground=\"#FFFFFF\">		Inserez votre mouvement, ex : \"B1:C3\"</span>\n1 : <span foreground=\"#FF0000\"><b>A1:B2</b></span> 2 : <span foreground=\"#00FF00\"><b>E1:E2</b></span> 2 : <span foreground=\"#00FF00\"><b>E1:E2</b></span> 2 : <span foreground=\"#00FF00\"><b>E1:E2</b></span> 2 : <span foreground=\"#00FF00\"><b>E1:E2</b></span> 2 : <span foreground=\"#00FF00\"><b>E1:E2</b></span>";
	//gchar* msg2="\n2 : <span foreground=\"#00FF00\"><b>E1:E2</b></span>";
	*/
	
	GtkWidget* vBox;
	vBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	if (histomove=="start"){
		str=  g_locale_to_utf8("<span foreground=\"#FFFFFF\">Inserez votre mouvement, ex : \"B1:C3\"</span>", -1, NULL, NULL, NULL); 
	}
	else {
	 //str=  g_locale_to_utf8("<span foreground=\"#FFFFFF\">Inserez votre mouvement, ex : \"B1:C3\"</span>", -1, NULL, NULL, NULL);  
	  str=  g_locale_to_utf8(histomove, -1, NULL, NULL, NULL);  
	  
	 }
	gtk_label_set_markup(GTK_LABEL(message3), str);
	
	g_free(str);
	
}

void label_joueur(PAbalone game,GtkWidget* label ){
	gchar* str;
	GtkWidget* vBox;
	vBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	if (game->player==COULEUR_BLANC) str= g_locale_to_utf8("\nC'est au tour des <span foreground=\"#FF0000\"><b>Blancs</b></span> de jouer",-1, NULL, NULL, NULL);
	else  str= g_locale_to_utf8("\nC'est au tour des <span foreground=\"#FF0000\"><b>Noirs</b></span> de jouer",-1, NULL, NULL, NULL);
	/*! affectation du texte balise au label*/
	gtk_label_set_markup(GTK_LABEL(label), str);
	g_free(str);
}

void label_msg(PAbalone game,GtkWidget* label_error ){
	GtkWidget* vBox;
	gchar* str=g_locale_to_utf8("Le coup est <span foreground=\"#00FF00\"><b>valide</b></span>\n",-1, NULL, NULL, NULL);
	vBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	/*! affectation du texte balise au label */
	gtk_label_set_markup(GTK_LABEL(label_error), str);
	g_free(str);
}

void label_msg2(PAbalone game,GtkWidget* label_error2 ){
	GtkWidget* vBox;
	gchar* str=g_locale_to_utf8("Le coup n'est pas <span foreground=\"#FF0000\"><b>valide</b></span>\n",-1, NULL, NULL, NULL);
	vBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	/*! affectation du texte balise au label */
	gtk_label_set_markup(GTK_LABEL(label_error2), str);
	g_free(str);
}
 
void do_drawing(cairo_t *cr){  
  	cairo_pattern_t *pat; 

  
  	cairo_set_source_rgb(cr, 0, 0, 0.1);
  	cairo_paint(cr);
    GdkPixbuf *pix;
    GError *err = NULL;
    /* Create pixbuf */
    pix = gdk_pixbuf_new_from_file("./gameover.jpg", &err);
    if(err)
    {
        printf("Error : %s\n", err->message);
        g_error_free(err);
    	//return FALSE;
    }
    gdk_cairo_set_source_pixbuf(cr, pix, 0, 150);
    cairo_paint(cr);
  	cairo_paint(cr);
  
  
  	gint h = 31;
  
  	cairo_select_font_face(cr, "Serif", CAIRO_FONT_SLANT_ITALIC, 
    	CAIRO_FONT_WEIGHT_BOLD);
  	cairo_set_font_size(cr, h);
  
  	pat = cairo_pattern_create_linear(0, 15, 0, h*0.8);
  	cairo_pattern_set_extend(pat, CAIRO_EXTEND_REPEAT);
  	cairo_pattern_add_color_stop_rgb(pat, 0.0, 1, 0.6, 0);
  	cairo_pattern_add_color_stop_rgb(pat, 0.5, 1, 0.3, 0);
                  
  	cairo_move_to(cr, 15, 260);
  	cairo_text_path(cr, "Les blancs ont gagné !");
  	cairo_set_source(cr, pat);
  	cairo_fill(cr);
}

void do_drawing2(cairo_t *cr){  
  	cairo_pattern_t *pat; 
  
  	cairo_set_source_rgb(cr, 0, 0, 0.1);
  	cairo_paint(cr);
    GdkPixbuf *pix;
    GError *err = NULL;
    /* Create pixbuf */
    pix = gdk_pixbuf_new_from_file("./gameover.jpg", &err);
    if(err)
    {
        printf("Error : %s\n", err->message);
        g_error_free(err);
     	//return FALSE;
    }
    gdk_cairo_set_source_pixbuf(cr, pix, 0, 150);
    cairo_paint(cr);
  	cairo_paint(cr);
  
  	gint h = 31;
  
  	cairo_select_font_face(cr, "Serif", CAIRO_FONT_SLANT_ITALIC, 
      	CAIRO_FONT_WEIGHT_BOLD);
  	cairo_set_font_size(cr, h);
  
  	pat = cairo_pattern_create_linear(0, 15, 0, h*0.8);
  	cairo_pattern_set_extend(pat, CAIRO_EXTEND_REPEAT);
  	cairo_pattern_add_color_stop_rgb(pat, 0.0, 1, 0.6, 0);
  	cairo_pattern_add_color_stop_rgb(pat, 1, 1, 1, 0);
                  
  	cairo_move_to(cr, 15, 260);
  	cairo_text_path(cr, "Les noirs ont gagné !");
  	cairo_set_source(cr, pat);
  	cairo_fill(cr);
}

void do_drawing3(cairo_t *cr){  
  	cairo_pattern_t *pat; 
  
  	cairo_set_source_rgb(cr, 0, 0, 0.1);
  	cairo_paint(cr);
    GdkPixbuf *pix;
    GError *err = NULL;
    /* Create pixbuf */
    pix = gdk_pixbuf_new_from_file("./gameover.jpg", &err);
    if(err)
    {
        printf("Error : %s\n", err->message);
        g_error_free(err);
     	//return FALSE;
    }
    gdk_cairo_set_source_pixbuf(cr, pix, 0, 150);
    cairo_paint(cr);
  	gint h = 31;
  
  	cairo_select_font_face(cr, "Serif", CAIRO_FONT_SLANT_ITALIC, 
      	CAIRO_FONT_WEIGHT_BOLD);
  	cairo_set_font_size(cr, h);
  
  	pat = cairo_pattern_create_linear(0, 15, 0, h*0.8);
  	cairo_pattern_set_extend(pat, CAIRO_EXTEND_REPEAT);
  	cairo_pattern_add_color_stop_rgb(pat, 0.0, 1, 0.6, 0);
  	cairo_pattern_add_color_stop_rgb(pat, 1, 1, 1, 0);
                  
  	cairo_move_to(cr, 115, 260);
  	cairo_text_path(cr, "Match nul !");
  	cairo_set_source(cr, pat);
  	cairo_fill(cr);
}


void button_cb(GtkWidget *widget, gpointer data,int argc, char **argv){
	play_game_gtk(argc,argv);
}
void button_cb2(GtkWidget *widget, gpointer data,int argc, char **argv){
	play_game_gtk2(argc,argv);
}
void button_cb3(GtkWidget *widget, gpointer data,int argc, char **argv){
	play_game_gtk3(argc,argv);
}

void game_gtk_random_ia(PBoard board, gchar* text){
	if (strcmp(text, "exit")==0 ){
		exit(0);
	}
	if (board->game->player == COULEUR_NOIR){
		printf("Tour des Noirs :\n");
	}else{
		printf("Tour des Blancs :\n");
	}

	
	Mouvement mvt;
	//char* a1=malloc(6*sizeof(char));
	int error;
	
	
	
	string_to_mouvement(text,&mvt);
	
	error = finalise_mvt(board->game->board,board->game->player,mvt);
	
	if(error) print_error(error);
	
	if (!error){
		gtk_widget_hide(board->label_error2);   
		gtk_widget_show(board->label_error);   
		if (board->game->player == COULEUR_NOIR){
		
			board->game->player = COULEUR_BLANC;
			play_random_move(board->game->board,board->game->player);
			printf("Tour des Blancs :\n");
			
			board->game->player = COULEUR_NOIR;
			
		}/*else{
			board->game->player = COULEUR_NOIR;
			printf("Tour des Noirs :\n");
		}*/
		
	}
	else {
		gtk_widget_hide(board->label_error);   
		gtk_widget_show(board->label_error2);   
	}
	
	
	
	if(board->game->state == STATE_INITIALIZED){
			board->game->timer += 1;
	}else{
			int time_elapsed = difftime(time(NULL),start);
			board->game->timer += time_elapsed;
	}
	board->game->state = etat(board->game);

	gtk_widget_queue_draw(board->drawing_area);
	switch(board->game->state){
		case STATE_INITIALIZED:
		    printf("la partie est initialisé\n");
			break;
		case STATE_WON_BLANC:
			gtk_widget_hide(board->label_error2); 
			gtk_widget_hide(board->label_error); 
			gtk_widget_hide(board->label); 
			gtk_widget_hide(board->message); 
		
		    printf("les blancs ont gagné !!!\n");
			break;
		case STATE_WON_NOIR:
			gtk_widget_hide(board->label_error2); 
			gtk_widget_hide(board->label_error); 
			gtk_widget_hide(board->label); 
			gtk_widget_hide(board->message); 
			
		    printf("les noirs ont gagné !!!\n");
		  
			break;
		case STATE_TIMEOUT:
			gtk_widget_hide(board->label_error2); 
			gtk_widget_hide(board->label_error); 
			gtk_widget_hide(board->label); 
			gtk_widget_hide(board->message); 
	
		    printf("la partie s'est fini en égalité\n");
	
			break;
	
	
	}
	
}

void game_gtk_random_ia2(PBoard board, gchar* text){
	if (strcmp(text, "exit")==0 ){
		exit(0);
	}
	if (board->game->player == COULEUR_NOIR){
		printf("Tour des Noirs :\n");
	}else{
		printf("Tour des Blancs :\n");
	}

	
	Mouvement mvt;
	//char* a1=malloc(6*sizeof(char));
	int error;
	
	
	
	string_to_mouvement(text,&mvt);
	
	error = finalise_mvt(board->game->board,board->game->player,mvt);
	
	if(error) print_error(error);
	if (!error){
		gtk_widget_hide(board->label_error2);   
		gtk_widget_show(board->label_error);   
		if (board->game->player == COULEUR_BLANC){
		
			board->game->player = COULEUR_NOIR;
			
			printf("Tour des Blancs :\n");
			play_random_move(board->game->board,board->game->player);
			board->game->player = COULEUR_BLANC;
			gtk_widget_queue_draw(board->drawing_area);
			
		}else{
			board->game->player = COULEUR_BLANC;
			printf("Tour des Noirs :\n");
		}
		
	}
	else {
		gtk_widget_hide(board->label_error);   
		gtk_widget_show(board->label_error2);   
	}
	
	
	if(board->game->state == STATE_INITIALIZED){
			board->game->timer += 1;
	}else{
			int time_elapsed = difftime(time(NULL),start);
			board->game->timer += time_elapsed;
	}
	board->game->state = etat(board->game);

	gtk_widget_queue_draw(board->drawing_area);
	switch(board->game->state){
		case STATE_INITIALIZED:
		    printf("la partie est initialisé\n");
			break;
		case STATE_WON_BLANC:
			gtk_widget_hide(board->label_error2); 
			gtk_widget_hide(board->label_error); 
			gtk_widget_hide(board->label); 
			gtk_widget_hide(board->message); 
		
		    printf("les blancs ont gagné !!!\n");
			break;
		case STATE_WON_NOIR:
			gtk_widget_hide(board->label_error2); 
			gtk_widget_hide(board->label_error); 
			gtk_widget_hide(board->label); 
			gtk_widget_hide(board->message); 
			
		    printf("les noirs ont gagné !!!\n");
		  
			break;
		case STATE_TIMEOUT:
			gtk_widget_hide(board->label_error2); 
			gtk_widget_hide(board->label_error); 
			gtk_widget_hide(board->label); 
			gtk_widget_hide(board->message); 
	
		    printf("la partie s'est fini en égalité\n");
	
			break;
	
	
	}
	
}

 void game_gtk_random_ia_v_ia(PBoard board, gchar* text){
 	
 	if (strcmp(text, "exit")==0 ){
		exit(0);
	}
 	if (strcmp(text, "")==0 ){
		//while (board->game->state==STATE_INITIALIZED){
		//g_timeout_add(300,(GSourceFunc)gtk_widget_queue_draw,(void*)board->drawing_area);
			//gtk_widget_queue_draw(board->drawing_area);
		//while (i<5){
			//board->game->player = COULEUR_NOIR;
			//gtk_widget_queue_draw(board->drawing_area);
			if (board->game->player == COULEUR_NOIR){
				play_random_move(board->game->board,board->game->player);
				board->game->player = COULEUR_BLANC;
				//gtk_widget_queue_draw(board->drawing_area);
				
			
			printf("Tour des Blancs :\n");
			//play_random_move(board->game->board,board->game->player);
			//board->game->player = COULEUR_NOIR;
			
			}else{
			play_random_move(board->game->board,board->game->player);
				board->game->player = COULEUR_NOIR;
				//gtk_widget_queue_draw(board->drawing_area);
			printf("Tour des Noirs :\n");
			}
		
			gtk_widget_queue_draw(board->drawing_area);
		
		
			board->game->state = etat(board->game);
			//g_timeout_add(500,(GSourceFunc)gtk_widget_queue_draw,(void*)board->drawing_area);
			//gtk_widget_queue_draw(board->drawing_area);
			//gdk_threads_add_idle((GSourceFunc)gtk_widget_queue_draw,(void*)board->drawing_area);
			//sleep(1);
			//gtk_widget_queue_draw(board->drawing_area);
			switch(board->game->state){
				case STATE_INITIALIZED:
		    		printf("la partie est initialisé\n");
				break;
				case STATE_WON_BLANC:
			gtk_widget_hide(board->label_error2); 
			gtk_widget_hide(board->label_error); 
			gtk_widget_hide(board->label); 
			gtk_widget_hide(board->message); 
		
		    printf("les blancs ont gagné !!!\n");
		     exit(0);
			break;
		case STATE_WON_NOIR:
			gtk_widget_hide(board->label_error2); 
			gtk_widget_hide(board->label_error); 
			gtk_widget_hide(board->label); 
			gtk_widget_hide(board->message); 
			
		    printf("les noirs ont gagné !!!\n");
		    exit(0);
		  
			break;
		case STATE_TIMEOUT:
			gtk_widget_hide(board->label_error2); 
			gtk_widget_hide(board->label_error); 
			gtk_widget_hide(board->label); 
			gtk_widget_hide(board->message); 
	
		    printf("la partie s'est fini en égalité\n");
		     exit(0);
	
			break;
	
	
								}
		
			compteur_tour+=1;
			printf("C'est le coup numéro : %i\n",compteur_tour);
			
		//}
	}

 }
 
 
gchar* msg_final;
gchar* msg_coup;
gchar* msg_coup2;
gchar* msg_coup3;
char* move_board[1000];
 
void game_gtk(PBoard board, gchar* text){
 	
	if (strcmp(text, "exit")==0 ){
		exit(0);
	}
	/*if (board->game->player == COULEUR_NOIR){
		printf("Tour des Noirs :\n");
	}else{
		printf("Tour des Blancs :\n");
	}*/
	Mouvement mvt;
	//char* a1=malloc(6*sizeof(char));
	int error;
	char* string=text;
	char dest2[1000];
	char dest3[1500];
	gchar* msg_coup;
	string_to_mouvement(text,&mvt);
	error = finalise_mvt(board->game->board,board->game->player,mvt);
	if(error) print_error(error);
	if (cpt_board==2) cpt_board=0;
	
	board_historique[cpt_board]=string;
	char string2[20];
	sprintf(string2,"%d",compteur_tour);
	//printf("LA valeur est %s",string2);

	char final[]="</b></span>";
	char med[]=" : <span foreground=\"#FF0000\"><b>";
	char med2[]=" : <span foreground=\"#00FF00\"><b>";
	char dest[500]="<span foreground=\"#FFFFFF\">	Inserez votre mouvement, ex : \"B1:C3\"</span>\n Le dernier coup joué est le numéro ";
	strcat(dest,string2);
	if (board->game->player==COULEUR_NOIR){
	strcat(dest,med);
	}
	else {
	strcat(dest,med2);
	}
	strcat(dest,board_historique[cpt_board]);
	strcat(dest,final);
	 msg_final=dest;
/*	if (compteur_tour==1){
	strcat(dest,string2);
	strcat(dest,med);
	strcat(dest,board_historique[cpt_board]);
	strcat(dest,final);

	move_board[compteur_tour-1]=dest;
	printf("%s",move_board[compteur_tour-1]);
	}
	
	if (compteur_tour==2){
	
	//char final2[]="</b></span>";
	char med2[]=" : <span foreground=\"#00FF00\"><b>";
	strcpy(dest2,move_board[compteur_tour-2]);
	
	strcat(dest2,string2);
	strcat(dest2,med2);
	strcat(dest2,board_historique[cpt_board]);
	
	strcat(dest2,final);
	
	move_board[compteur_tour-1]=dest2;
		
	}
	if (compteur_tour>2){
	//char final3[]="</b></span>";
	
	strcpy(dest3,move_board[compteur_tour-2]);
	printf("\n %s",move_board[compteur_tour-2]);
	strcat(dest3,string2);
	strcat(dest3,med);
	strcat(dest3,board_historique[cpt_board]);
	strcat(dest3,final);
	
	move_board[compteur_tour-1]=dest3;
	}
	
	switch(compteur_tour){
		case 1:
		   msg_final=move_board[0];
			break;
		case 2:
		msg_final=move_board[1];
		
		   
			break;
		case 3:
			msg_final=move_board[2];
		//msg="<span foreground=\"#FFFFFF\">		Inserez votre mouvement, ex : \"B1:C3\"</span>\n1 : <span foreground=\"#FF0000\"><b>A1:B2</b></span> 2 : <span foreground=\"#00FF00\"><b>E1:E2</b></span> 3 : <span foreground=\"#FF0000\"><b>E1:E2</b></span>";
			
		 
		  
			break;
		case 4:
		//msg="<span foreground=\"#FFFFFF\">		Inserez votre mouvement, ex : \"B1:C3\"</span>\n1 : <span foreground=\"#FF0000\"><b>A1:B2</b></span> 2 : <span foreground=\"#00FF00\"><b>E1:E2</b></span> 3 : <span foreground=\"#FF0000\"><b>E1:E2</b></span>4 : <span foreground=\"#00FF00\"><b>E1:E2</b></span>";
	
			break;
		case 5:
			//msg="<span foreground=\"#FFFFFF\">		Inserez votre mouvement, ex : \"B1:C3\"</span>\n1 : <span foreground=\"#FF0000\"><b>A1:B2</b></span> 2 : <span foreground=\"#00FF00\"><b>E1:E2</b></span> 3 : <span foreground=\"#FF0000\"><b>E1:E2</b></span> 4 : <span foreground=\"#00FF00\"><b>E1:E2</b></span> 5 : <span foreground=\"#FF0000\"><b>E1:E2</b></span> 2 : <span foreground=\"#00FF00\"><b>E1:E2</b></span>";
			break;
	
		//default:
			
	
	}
	/*gchar* msg="<span foreground=\"#FFFFFF\">		Inserez votre mouvement, ex : \"B1:C3\"</span>\n1 : <span foreground=\"#FF0000\"><b>A1:B2</b></span> 2 : <span foreground=\"#00FF00\"><b>E1:E2</b></span> 2 : <span foreground=\"#00FF00\"><b>E1:E2</b></span> 2 : <span foreground=\"#00FF00\"><b>E1:E2</b></span> 2 : <span foreground=\"#00FF00\"><b>E1:E2</b></span> 2 : <span foreground=\"#00FF00\"><b>E1:E2</b></span>";
*/
	
	
	
	
	cpt_board+=1;
	/*printf("%i : ",compteur_tour);
	//printf(text);
	printf("%s",board_historique[0]);
	printf("\n");*/
	
	
	if(error) print_error(error);
	 
	
	if(board->game->state == STATE_INITIALIZED){
			board->game->timer += 1;
	}else{
			int time_elapsed = difftime(time(NULL),start);
			board->game->timer += time_elapsed;
	}
	board->game->state = etat(board->game);
	if (!error){
		compteur_tour+=1;
		 
		 
		 
		msg3(board->game, board->message,msg_final);
		
		
		
		
		
		gtk_widget_hide(board->label_error2);   
		gtk_widget_show(board->label_error);   
		if (board->game->player == COULEUR_NOIR){
		
			board->game->player = COULEUR_BLANC;
			printf("Tour des Blancs :\n");
		}else{
			board->game->player = COULEUR_NOIR;
			printf("Tour des Noirs :\n");
		}
		
	}
	else {
		gtk_widget_hide(board->label_error);   
		gtk_widget_show(board->label_error2);   
	}
	gtk_widget_queue_draw(board->drawing_area);
	switch(board->game->state){
		case STATE_INITIALIZED:
		    printf("la partie est initialisé\n");
			break;
		case STATE_WON_BLANC:
			gtk_widget_hide(board->label_error2); 
			gtk_widget_hide(board->label_error); 
			gtk_widget_hide(board->label); 
			gtk_widget_hide(board->message); 
		
		    printf("les blancs ont gagné !!!\n");
			break;
		case STATE_WON_NOIR:
			gtk_widget_hide(board->label_error2); 
			gtk_widget_hide(board->label_error); 
			gtk_widget_hide(board->label); 
			gtk_widget_hide(board->message); 
			
		    printf("les noirs ont gagné !!!\n");
		  
			break;
		case STATE_TIMEOUT:
			gtk_widget_hide(board->label_error2); 
			gtk_widget_hide(board->label_error); 
			gtk_widget_hide(board->label); 
			gtk_widget_hide(board->message); 
	
		    printf("la partie s'est fini en égalité\n");
	
			break;
	
	
	}

	
 
 }
 
 // void onActivateEntry(GtkEntry *entry, gpointer data,GtkWidget* drawing_area){    
 
 void onActivateEntry(GtkEntry *entry, gpointer data){    
 	const gchar *text;    /* Recuperation du texte contenu dans le GtkEntry */    
 	PBoard board = (PBoard) data;
 	text = gtk_entry_get_text(GTK_ENTRY(entry));
 	
 	
 	
 	
 	game_gtk((PBoard) board,(gchar*) text);
 	//game_gtk_random_ia((PBoard) board,(gchar*) text);
 	
 	
 	gtk_entry_set_text(GTK_ENTRY(entry), "");
	//gtk_widget_queue_draw(board->drawing_area);
	label_joueur(board->game, board->label);
	// gtk_widget_show(board->label_error);   
 	//label_msg(board->game, board->label_error);
 }
  
 void onActivateEntry2(GtkEntry *entry, gpointer data){    
 	const gchar *text;    /* Recuperation du texte contenu dans le GtkEntry */    
 	PBoard board = (PBoard) data;
 	text = gtk_entry_get_text(GTK_ENTRY(entry));
 	
 	
 	
 	
 	//game_gtk((PBoard) board,(gchar*) text);
 	if (board->game->player == COULEUR_NOIR){
 	game_gtk_random_ia((PBoard) board,(gchar*) text);
 	}
 	else if (board->game->player == COULEUR_BLANC) {
 	game_gtk_random_ia2((PBoard) board,(gchar*) text);
 	}
 	
 	gtk_entry_set_text(GTK_ENTRY(entry), "");
	//gtk_widget_queue_draw(board->drawing_area);
	label_joueur(board->game, board->label);
	// gtk_widget_show(board->label_error);   
 	//label_msg(board->game, board->label_error);
 }
 
  void onActivateEntry3(GtkEntry *entry, gpointer data){    
 	const gchar *text;    /* Recuperation du texte contenu dans le GtkEntry */    
 	PBoard board = (PBoard) data;
 	text = gtk_entry_get_text(GTK_ENTRY(entry));

 	game_gtk_random_ia_v_ia((PBoard) board,(gchar*) text);
 	
 	
 	gtk_entry_set_text(GTK_ENTRY(entry), "");
	//gtk_widget_queue_draw(board->drawing_area);
	label_joueur(board->game, board->label);
	// gtk_widget_show(board->label_error);   
 	//label_msg(board->game, board->label_error);
 }
 
 /* Redraw the widget. Note that the ::draw * signal receives a ready-to-be-used cairo_t that is already * clipped to only draw the exposed areas of the widget */

 gboolean draw_cb(GtkWidget *widget, cairo_t *cr, gpointer data){    
 	//GtkWidget *drawing_area = data;    
 	PBoard data2 = (PBoard) data;
 	clear(cr);    
 	draw(cr,data2->game); 
 	//draw(cr);   
 	return FALSE;
 }
 