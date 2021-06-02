/* 315CA Dinu Ion Irinel 
 * 315CA Serban Bianca-Sanziana
 */
#include "./rope.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "utils.h"

#define EMPTY ""

char *strdup(const char *s);

/* functie pentru crearea unui nou nod */
RopeNode *makeRopeNode(const char *str) {
    /* alocarea memoriei pentru nod */
    RopeNode *node = malloc(sizeof(RopeNode));
    DIE(node == NULL, "Allocation error rope_node\n");

    /* actualizare pointeri */
    node->left = NULL;
    node->right = NULL;

    /* actualizare valoare string */
    node->str = str;

    /* actualizare greutate nod cu lungimea string-ului */
    node->weight = strlen(str);

    return node;
}

/* functie pentru crearea unui nou rope */
RopeTree *makeRopeTree(RopeNode *root) {
    /* alocarea memoriei pentru rope */
    RopeTree *rope_tree = malloc(sizeof(RopeTree));
    DIE(rope_tree == NULL, "Allocation error rope_tree\n");

    /* actualizare radacina */
    rope_tree->root = root;

    return rope_tree;
}

/* functii pentru afisarea string-ului unui nod */
void printRopeNode(RopeNode *rn) {
    if (!rn) {
        return;
    }

    if (!(rn->left) && !(rn->right)) {
        printf("%s", rn->str);
        return;
    }

    printRopeNode(rn->left);
    printRopeNode(rn->right);
}

void printRopeTree(RopeTree *rt) {
    if (rt && rt->root) {
        printRopeNode(rt->root);
        printf("%s", "\n");
    }
}

/* functie pentru afisarea informatiilor unui nod */
void debugRopeNode(RopeNode *rn, int indent) {
    if (!rn) {
        return;
    }
    for (int i = 0; i < indent; ++i) {
        printf("%s", " ");
    }

    if (!strcmp(rn->str, EMPTY)) {
        printf("# %d\n", rn->weight);
    } else {
        printf("%s %d\n", rn->str, rn->weight);
    }

    debugRopeNode(rn->left, indent + 2);
    debugRopeNode(rn->right, indent + 2);
}

/* functie pentru crearea unei copii a unui rope */
RopeNode *copy_rope(RopeNode *rn) {
    if (!rn) {
        return NULL;
    }
    RopeNode *new_rn = makeRopeNode(strdup(rn->str));
    new_rn->left = copy_rope(rn->left);
    new_rn->right = copy_rope(rn->right);
    new_rn->weight = strlen(new_rn->str) + total_weight(new_rn->left);
    return new_rn;
}

/* functie pentru calcularea greutatii unui nod */
int total_weight(RopeNode *rt) {
    if (!rt) {
        return 0;
    }
    return rt->weight + total_weight(rt->right);
}

/* functie pentru concatenarea a doua rope-uri pe baza a doua ropuri intiale */
RopeTree *concat(RopeTree *rt1, RopeTree *rt2) {
    /* TODO(Dinu Ion Irinel) */
    /* crearea unei noi radacini si a unui nou rope */
    RopeNode *rt3_root = makeRopeNode((char *)strdup(EMPTY));
    RopeTree *rt3 = makeRopeTree(rt3_root);

    /* actualizarea pointerilor copii left si right */
    (rt3->root)->left = rt1->root;
    (rt3->root)->right = rt2->root;

    /* actualizarea noii greutati */
    (rt3->root)->weight = total_weight(rt3->root->left);

    return rt3;
}

/* functie pentru concatenarea a doua rope-uri pe baza a doua noduri intiale */
RopeNode *concat_nodes(RopeNode *rt1, RopeNode *rt2) {
    /* TODO(Dinu Ion Irinel) */

    /* crearea unui nou nod */
    RopeNode *rt3 = makeRopeNode((char *)strdup(EMPTY));

    /* actualizarea pointerilor left si right */
    rt3->left = rt1;
    rt3->right = rt2;

    /* actualizarea noii greutati */
    rt3->weight = total_weight(rt3->left);

    return rt3;
}

/* functii folosite pentru returnarea unui caracter de pe o pozitie dorita */
char indexRope(RopeTree *rt, int idx) {
    /* TODO(Serban Bianca-Sanziana) */
    return __indexRope(rt->root, idx);
}

char __indexRope(RopeNode *node, int idx) {
    if (node->weight <= idx && node->right != NULL) {
        /* parcurgere subarbore drept */
        return __indexRope(node->right, idx - node->weight);
    }
    if (node->left != NULL) {
        /* parcurgere subarbore stang */
        return __indexRope(node->left, idx);
    }
    /* returnarea caracterului de pe pozitia dorita */
    return node->str[idx];
}

/* functie pentru cautarea unui string cuprins intr-un interval stabilit */
char *search(RopeTree *rt, int start, int end) {
    /* TODO(Serban Bianca-Sanziana) */

    int pos = start;
    /* alocare memorie pentru string-ul rezultat */
    char *str = malloc((end - start + 1) * sizeof(char));
    DIE(str == NULL, "Allocation error string\n");

    /* initializare cu terminator de sir */
    str[0] = '\0';
    /* cat timp intervalul este valid accesam un caracter
     * si il adaugam la string-ul rezultat
     */
    while (start <= pos && pos < end) {
        char character = indexRope(rt, pos);
        /* copierea caracterului in string-ul dorit */
        strncat(str, &character, 1);
        pos++;
    }
    return str;
}


/* functii folosite pentru a imparti un rop in doua rope-uri separate */
SplitPair split(RopeTree *rt, int idx) {
    /* TODO(Dinu Ion Irinel) */
    /* crearea unui nod care pointeaza la o copie a rope-ului
     * initial care in final va reprezenta rope-ul din partea stanga
     */
    RopeNode *left_rn = copy_rope(rt->root);
    /* crearea nodului care pointeaza la rope-ul drept dorit */
    RopeNode *right_rn = makeRopeNode((char *)strdup(EMPTY));

    __split(&left_rn, &right_rn, idx);

    if (left_rn == NULL) {
        left_rn = makeRopeNode(strdup(EMPTY));
    }

    /* returnarea celor doua noduri obtinute dupa impartire */
    SplitPair pair;
    pair.left = left_rn;
    pair.right = right_rn;
    return pair;
}

void __split(RopeNode **left_rn, RopeNode **right_rn, int idx) {
    /* concatenarea celor doua noduri daca index-ul are o valoare negativa */
    if (idx <= 0) {
        *right_rn = concat_nodes(*right_rn, *left_rn);
        *left_rn = NULL;
        return;
    }
    if (idx < (int) strlen((*left_rn)->str)) {
        /* copiere string-ului stang intr-un string temporar */
        char *left_string = malloc((idx + 1) * sizeof(char));
        DIE(left_string == NULL, "Allocation error left_string\n");
        strncpy(left_string, (*left_rn)->str, idx);
        /* adaugare terminator de sir */
        left_string[idx] = '\0';
        /* crearea celor doua noduri temporarele  */
        RopeNode *aux_left_node = makeRopeNode(strdup(left_string));
        RopeNode *aux_right_node = makeRopeNode(strdup((*left_rn)->str + idx));

        /* eliberarea memoriei string-urilor si a nodului stang */
        free(left_string);
        free((void *)(*left_rn)->str);
        free((*left_rn));
        /* concatenarea celor doua noduri auxiliare */
        (*left_rn) = concat_nodes(aux_left_node, aux_right_node);
    }

    /* apelare functie pentru fiul stang */
    if ((*left_rn)->left != NULL && (*left_rn)->weight > idx) {
        __split(&(*left_rn)->left, right_rn, idx);
    }
    /* apelare functie pentru fiul drept */
    if ((*left_rn)->right != NULL) {
        __split(&(*left_rn)->right, right_rn, idx - (*left_rn)->weight);
    }

    /* actualizarea noii greutati */
    (*left_rn)->weight = total_weight((*left_rn)->left);
}

