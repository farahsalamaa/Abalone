#include"mouvement_test.h"
#include<assert.h>

void test_type_mvt_ligne(){
    Mouvement m;
    Coord c1;
    c1.x = 1;
    c1.y = 1;
    m.start = c1;
    Coord c2;
    c2.x = 1;
    c2.y = 0;
    m.end = c2;
    assert(type_mvt(m) == MVT_LIGNE);
}

void test_type_mvt_largeur(){
    Mouvement m;
    Coord c1;
    c1.x = 0;
    c1.y = 0;
    m.start = c1;
    Coord c2;
    c2.x = 1;
    c2.y = 1;
    m.end = c2;
    assert(type_mvt(m) == MVT_LARGEUR);
}
void test_area_mvt(){
    Mouvement m;
    Coord c1;
    c1.x = 0;
    c1.y = 0;
    m.start = c1;
    Coord c2;
    c2.x = 1;
    c2.y = 2;
    m.end = c2;
    assert(area_mvt(m)==6);
}

void orientation_grp_test_horiz(){
    Mouvement m;
    Coord c1;
    c1.x = 0;
    c1.y = 0;
    m.start = c1;
    Coord c2;
    c2.x = 0;
    c2.y = 1;
    m.end = c2;
    assert(orientation_grp(m)==HORIZONTAL);
}

void orientation_grp_test_verti(){
    Mouvement m;
    Coord c1;
    c1.x = 0;
    c1.y = 0;
    m.start = c1;
    Coord c2;
    c2.x = 1;
    c2.y = 0;
    m.end = c2;
    assert(orientation_grp(m)==VERTICAL);
}
void length_mvt_largeur_l2_test(){ 
    Mouvement m;
    Coord c1;
    c1.x = 0;
    c1.y = 0;
    m.start = c1;
    Coord c2;
    c2.x = 1;
    c2.y = 1;
    m.end = c2;
    assert(length_mvt(m)==L_2);
}
void length_mvt_largeur_l1_test(){
    Mouvement m;
    Coord c1;
    c1.x = 0;
    c1.y = 0;
    m.start = c1;
    Coord c2;
    c2.x = 1;
    c2.y = 0;
    m.end = c2;
    assert(length_mvt(m)==L_1);
}
void length_mvt_largeur_l3_test(){
    Mouvement m;
    Coord c1;
    c1.x = 6;
    c1.y = 1;
    m.start = c1;
    Coord c2;
    c2.x = 5;
    c2.y = 3;
    m.end = c2;
    assert(length_mvt(m)==L_3);
}
void length_mvt_ligne_l1_test(){
    Mouvement m;
    Coord c1;
    c1.x = 6;
    c1.y = 1;
    m.start = c1;
    Coord c2;
    c2.x = 6;
    c2.y = 0;
    m.end = c2;
    assert(length_mvt(m)==L_1);
}
void length_mvt_ligne_l2_test(){
    Mouvement m;
    Coord c1;
    c1.x = 0;
    c1.y = 0;
    m.start = c1;
    Coord c2;
    c2.x = 2;
    c2.y = 0;
    m.end = c2;
    assert(length_mvt(m)==L_2);
}
void length_mvt_ligne_l3_test(){
    Mouvement m;
    Coord c1;
    c1.x = 6;
    c1.y = 3;
    m.start = c1;
    Coord c2;
    c2.x = 6;
    c2.y = 0;
    m.end = c2;
    assert(length_mvt(m)==L_3);
}
void voisin_carre_test(){
    Mouvement m;
    Coord c1;
    c1.x = 1;
    c1.y = 1;
    m.start = c1;
    Coord c2;
    c2.x = 2;
    c2.y = 2;
    m.end = c2;
    int x0 = c1.x;
    int y0 = c1.y;
    int x1 = c2.x;
    int y1 = c2.y;
    PAbalone b=new_abalone();
    Coord v = voisin_carre(b->board,m);
    assert(v.x == 1);
    assert(v.y == 2);
}
void direction_mvt_right_test(){ 
    Mouvement m;
    Coord c1;
    c1.x = 0;
    c1.y = 0;
    m.start = c1;
    Coord c2;
    c2.x = 0;
    c2.y = 1;
    m.end = c2;
    PAbalone a = new_abalone();
    assert(direction_mvt(a->board,m)==DIR_RIGHT);
}
void direction_mvt_left_test(){ 
    Mouvement m;
    Coord c1;
    c1.x = 6;
    c1.y = 1;
    m.start = c1;
    Coord c2;
    c2.x = 6;
    c2.y = 0;
    m.end = c2;
    PAbalone a = new_abalone();
    assert(direction_mvt(a->board,m)==DIR_LEFT);
}
void direction_mvt_up_test(){ 
    Mouvement m;
    Coord c1;
    c1.x = 7;
    c1.y = 0;
    m.start = c1;
    Coord c2;
    c2.x = 6;
    c2.y = 0;
    m.end = c2;
    PAbalone a = new_abalone();
    assert(direction_mvt(a->board,m)==DIR_UP);
}
void validate_mvt_test1(){
    Mouvement m;
    Coord c1;
    c1.x = 6;
    c1.y = 1;
    m.start = c1;
    Coord c2;
    c2.x = 5;
    c2.y = 1;
    m.end = c2;
    PAbalone a=new_abalone();
    //assert(validate_mvt_ligne_2(m)==VALIDATION_OK);
    assert(validate_mvt(a->board,a->player,m)==VALIDATION_OK);
}
void validate_mvt_test2(){
    Mouvement m;
    Coord c1;
    c1.x = 6;
    c1.y = 1;
    m.start = c1;
    Coord c2;
    c2.x = 5;
    c2.y = 2;
    m.end = c2;
    PAbalone a=new_abalone();
    assert(validate_mvt(a->board,a->player,m)==ERROR_NOT_A_MOVEMENT);
}
void exec_mvt_test(){
    Mouvement m;
    Coord c1;
    c1.x = 0;
    c1.y = 0;
    m.start = c1;
    Coord c2;
    c2.x = 0;
    c2.y = 1;
    m.end = c2;
    PAbalone a =new_abalone();
    assert(a->board[0][1]);
}
void finalise_mvt_test(){
    Mouvement m;
    Coord c1;
    c1.x = 6;
    c1.y = 1;
    m.start = c1;
    Coord c2;
    c2.x = 5;
    c2.y = 1;
    m.end = c2;
    PAbalone a =new_abalone();
    debug("%d",validate_mvt(a->board,a->player,m));
    assert(finalise_mvt(a->board,a->player,m)==VALIDATION_OK);
}
void string_to_mouvement_test(){
    Mouvement m;
    assert(string_to_mouvement("A1:B1",&m)==0);
}
/* Ces fonctions ne sont pas à tester comme ca. il faut les tester avec validate mvt, car ce sont des fonctions filles.
void validate_mvt_piece_test(){
    Mouvement m;
    Coord c1;
    c1.x = 0;
    c1.y = 0;
    m.start = c1;
    Coord c2;
    c2.x = 0;
    c2.y = 1;
    m.end = c2;
    PAbalone a = new_abalone();
    assert(validate_mvt(a->board,a->player,m)==ERROR_WRONG_COLOR);
}

void validate_mvt_bounds_test(){
    Mouvement m;
    Coord c1;
    c1.x = 0;
    c1.y = 9;
    m.start = c1;
    Coord c2;
    c2.x = 0;
    c2.y = 1;
    m.end = c2;
    assert(validate_mvt_bounds(m)==ERROR_OUT_OF_BOUNDS);
}

void validate_mvt_ligne_1_test(){
    Mouvement m;
    Coord p[2];
    PAbalone a = new_abalone();
    string_to_coord("A1:A2", &p);
    coord_to_mouvement(a, &m, &p);
    assert(validate_mvt_ligne_1(a,m)==ERROR_BLOCKED);
}
void validate_mvt_ligne_2_test(){
    Mouvement m;
    Coord p[2];
    PAbalone a = new_abalone();
    string_to_coord("H3:F3", &p);
    coord_to_mouvement(a, &m, &p);
    assert(validate_mvt_ligne_2(a,m)==VALIDATION_OK);
}
void validate_mvt_ligne_3_test(){
    PMouvement m;
    Coord p[2];
    PAbalone a = new_abalone();
    string_to_coord("G2:G4", &p);
    coord_to_mouvement(a, &m, &p);
    assert(validate_mvt_ligne_3(a,m)==ERROR_NOT_ENOUGH_STRENGTH);
}*/
void test_mouvement() {
    test_type_mvt_ligne();
    test_type_mvt_largeur();
    test_area_mvt();
    orientation_grp_test_horiz();
    orientation_grp_test_verti();
    length_mvt_largeur_l1_test();
    length_mvt_largeur_l2_test();
    length_mvt_largeur_l3_test();
    length_mvt_ligne_l1_test();
    length_mvt_ligne_l2_test();
    length_mvt_ligne_l3_test();
    voisin_carre_test();
    direction_mvt_right_test();
    direction_mvt_left_test();
    direction_mvt_up_test();
    validate_mvt_test1();
    validate_mvt_test2();
    exec_mvt_test();
    finalise_mvt_test();
    string_to_mouvement_test();
    /*validate_mvt_piece_test();
    validate_mvt_bounds_test();
    validate_mvt_ligne_1_test();
    validate_mvt_ligne_2_test();
    validate_mvt_ligne_3_test();*/
    // TODO: Appeler toutes les fonctions de test de ce module
}