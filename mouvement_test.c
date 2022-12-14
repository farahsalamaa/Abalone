#include"mouvement_test.h"

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
void test_type_notmvt(){
    Mouvement m;
    Coord c1;
    c1.x = 1;
    c1.y = 1;
    m.start = c1;
    Coord c2;
    c2.x = 2;
    c2.y = 4;
    m.end = c2;
    assert(type_mvt(m) == ERROR_NOT_A_MOVEMENT);
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
void orientation_grp_test_not_align(){
    Mouvement m;
    Coord c1;
    c1.x = 0;
    c1.y = 0;
    m.start = c1;
    Coord c2;
    c2.x = 1;
    c2.y = 2;
    m.end = c2;
    assert(orientation_grp(m)==ERROR_NOT_ALIGNED);
}
void length_mvt_l0_test(){ 
    Mouvement m;
    Coord c1;
    c1.x = 0;
    c1.y = 0;
    m.start = c1;
    Coord c2;
    c2.x = 0;
    c2.y = 0;
    m.end = c2;
    assert(length_mvt(m)==L_0);
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
void direction_mvt_down_test(){ 
    Mouvement m;
    Coord c1;
    c1.x = 0;
    c1.y = 0;
    m.start = c1;
    Coord c2;
    c2.x = 1;
    c2.y = 0;
    m.end = c2;
    PAbalone a = new_abalone();
    assert(direction_mvt(a->board,m)==DIR_DOWN);
}
void direction_mvt_downl2_test(){ 
    Mouvement m;
    Coord c1;
    c1.x = 1;
    c1.y = 1;
    m.start = c1;
    Coord c2;
    c2.x = 2;
    c2.y = 2;
    m.end = c2;
    PAbalone a = new_abalone();
    assert(direction_mvt(a->board,m)==DIR_DOWN);
}
void direction_mvt_downl3_test(){ 
    Mouvement m;
    Coord c1;
    c1.x = 1;
    c1.y = 1;
    m.start = c1;
    Coord c2;
    c2.x = 2;
    c2.y = 3;
    m.end = c2;
    PAbalone a = new_abalone();
    assert(direction_mvt(a->board,m)==DIR_DOWN);
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
void validate_mvt_test3(){
    Mouvement m;
    Coord c1;
    c1.x = 6;
    c1.y = 1;
    m.start = c1;
    Coord c2;
    c2.x = 5;
    c2.y = 4;
    m.end = c2;
    PAbalone a=new_abalone();
    assert(validate_mvt(a->board,a->player,m)==ERROR_UNKNOWN);
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
void string_to_mouvement_test1(){
    Mouvement m;
    assert(string_to_mouvement("A1:B1",&m)==0);
}
void string_to_mouvement_test2(){
    Mouvement m;
    assert(string_to_mouvement("A0:A1",&m)==ERROR_OUT_OF_BOUNDS);
}
void mouvement_to_string_test(){
    Mouvement m;
    Coord c1;
    c1.x = 0;
    c1.y = 0;
    m.start = c1;
    Coord c2;
    c2.x = 1;
    c2.y = 0;
    m.end = c2;
    char buffer[] = "A1:B1";
    assert(mouvement_to_string(m,buffer)==0);
}
/* Ces fonctions ne sont pas ?? tester comme ca. il faut les tester avec validate mvt, car ce sont des fonctions filles.
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
    test_type_notmvt();
    test_area_mvt();
    orientation_grp_test_horiz();
    orientation_grp_test_verti();
    orientation_grp_test_not_align();
    length_mvt_l0_test();
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
    direction_mvt_down_test();
    direction_mvt_downl2_test();
    direction_mvt_downl3_test();
    validate_mvt_test1();
    validate_mvt_test2();
    validate_mvt_test3();
    exec_mvt_test();
    finalise_mvt_test();
    string_to_mouvement_test1();
    string_to_mouvement_test2();
    mouvement_to_string_test();
    /*validate_mvt_piece_test();
    validate_mvt_bounds_test();
    validate_mvt_ligne_1_test();
    validate_mvt_ligne_2_test();
    validate_mvt_ligne_3_test();*/
    // TODO: Appeler toutes les fonctions de test de ce module
}