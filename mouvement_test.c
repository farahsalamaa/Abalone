#include"mouvement_test.h"
#include<assert.h>

void test_type_mvt_ligne(){
    Mouvement m;
    Coord c1;
    c1.x = 0;
    c1.y = 0;
    m.start = c1;
    Coord c2;
    c2.x = 2;
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
    assert(orientation_grp(c1,c2)==HORIZONTAL);
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
    assert(orientation_grp(c1,c2)==VERTICAL);
}
// il manque le test sur les autres largeurs pour les 2 mvts
void length_mvt_largeur_test(){ //mvt_largeur pour L_2
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

void length_mvt_ligne_test(){ //mvt_ligne pour L_2
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

    PAbalone a = new_abalone();
    Coord v = voisin_carre(a,m);
    assert(v.x == 1);
    assert(v.y == 2);
}

void direction_mvt_test(){ 
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
    assert(direction_mvt(a,m)==DIR_RIGHT);
}

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
    assert(validate_mvt(a,m)==ERROR_WRONG_COLOR);
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
    //assert(validate_mvt_ligne_3(a,m)==ERROR_NOT_ENOUGH_STRENGTH);
}
void test_mouvement() {
    test_type_mvt_ligne();
    test_type_mvt_largeur();
    test_area_mvt();
    orientation_grp_test_horiz();
    orientation_grp_test_verti();
    length_mvt_largeur_test();
    length_mvt_ligne_test();
    voisin_carre_test();
    direction_mvt_test();
    validate_mvt_piece_test();
    validate_mvt_bounds_test();
    validate_mvt_ligne_1_test();
    validate_mvt_ligne_2_test();
    validate_mvt_ligne_3_test();
    // TODO: Appeler toutes les fonctions de test de ce module
}