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

void test_mouvement() {
    test_type_mvt_ligne();
    test_type_mvt_largeur();
    // TODO: Appeler toutes les fonctions de test de ce module
}