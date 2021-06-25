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

/* function for creating a new node */
RopeNode *makeRopeNode(const char *str) {
    /* node memory allocation */
    RopeNode *node = malloc(sizeof(RopeNode));
    DIE(node == NULL, "Allocation error rope_node\n");

    /* pointers update */
    node->left = NULL;
    node->right = NULL;

    /* string value update */
    node->str = str;

    /* node weight update with string length */
    node->weight = strlen(str);

    return node;
}

/* function to create a new rope */
RopeTree *makeRopeTree(RopeNode *root) {
    /* rope memory allocation */
    RopeTree *rope_tree = malloc(sizeof(RopeTree));
    DIE(rope_tree == NULL, "Allocation error rope_tree\n");

    /* root update */
    rope_tree->root = root;

    return rope_tree;
}

/* functions for displaying the string of a node */
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

/* function to display informations about a node */
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

/* function to calculate the total weight */
int total_weight(RopeNode *rt) {
    if (!rt) {
        return 0;
    }
    return rt->weight + total_weight(rt->right);
}

/* function for concatenating two ropes based on two initial ropes */
RopeTree *concat(RopeTree *rt1, RopeTree *rt2) {
    /* TODO(Dinu Ion Irinel) */
    
    /* creating a new root and a new rope */
    RopeNode *rt3_root = makeRopeNode((char *)strdup(EMPTY));
    RopeTree *rt3 = makeRopeTree(rt3_root);

    /* updating left and right child pointers */
    (rt3->root)->left = rt1->root;
    (rt3->root)->right = rt2->root;

    /* update the new weight */
    (rt3->root)->weight = total_weight(rt3->root->left);

    return rt3;
}

/* function for concatenating two strings based on two initial nodes */
RopeNode *concat_nodes(RopeNode *rt1, RopeNode *rt2) {
    /* TODO(Dinu Ion Irinel) */

    /* create a new node  */
    RopeNode *rt3 = makeRopeNode((char *)strdup(EMPTY));

    /* update pointers left and right */
    rt3->left = rt1;
    rt3->right = rt2;

    /* update the new weight */
    rt3->weight = total_weight(rt3->left);

    return rt3;
}

/* functions used to return a character to a desired position */
char indexRope(RopeTree *rt, int idx) {
    /* TODO(Serban Bianca-Sanziana) */
    
    return __indexRope(rt->root, idx);
}

char __indexRope(RopeNode *node, int idx) {
    if (node->weight <= idx && node->right != NULL) {
        /* scroll right subtree */
        return __indexRope(node->right, idx - node->weight);
    }
    if (node->left != NULL) {
        /* scroll left subtree */
        return __indexRope(node->left, idx);
    }
    /* returning the character to the desired position */
    return node->str[idx];
}

/* function for searching for a string within a set range */
char *search(RopeTree *rt, int start, int end) {
    /* TODO(Serban Bianca-Sanziana) */

    int pos = start;
    /* memory allocation for the resulting string */
    char *str = malloc((end - start + 1) * sizeof(char));
    DIE(str == NULL, "Allocation error string\n");

    /* initialization with string terminator */
    str[0] = '\0';
     /* as long as the interval is valid we access a character
      * and add it to the resulting string
      */
    while (start <= pos && pos < end) {
        char character = indexRope(rt, pos);
        /* copying the character to the desired string */
        strncat(str, &character, 1);
        pos++;
    }
    return str;
}


/* functions used to divide a rop into two separate ropes */
SplitPair split(RopeTree *rt, int idx) {
    /* TODO(Dinu Ion Irinel) */
    
    /* creating a node that points to a copy of the rope
     * initially which will eventually represent the rope on the left
     */
    RopeNode *left_rn = copy_rope(rt->root);
    /* creating the knot that points to the desired right rope */
    RopeNode *right_rn = makeRopeNode((char *)strdup(EMPTY));

    __split(&left_rn, &right_rn, idx);

    if (left_rn == NULL) {
        left_rn = makeRopeNode(strdup(EMPTY));
    }

    /* returning the two nodes obtained after splitting */
    SplitPair pair;
    pair.left = left_rn;
    pair.right = right_rn;
    return pair;
}

void __split(RopeNode **left_rn, RopeNode **right_rn, int idx) {
    /* concatenation of the two nodes if the index has a negative value */
    if (idx <= 0) {
        *right_rn = concat_nodes(*right_rn, *left_rn);
        *left_rn = NULL;
        return;
    }
    if (idx < (int) strlen((*left_rn)->str)) {
        /* copy the left string to a temporary string  */
        char *left_string = malloc((idx + 1) * sizeof(char));
        DIE(left_string == NULL, "Allocation error left_string\n");
        strncpy(left_string, (*left_rn)->str, idx);
        /* add string terminator */
        left_string[idx] = '\0';
        /* creating the two temporary nodes */
        RopeNode *aux_left_node = makeRopeNode(strdup(left_string));
        RopeNode *aux_right_node = makeRopeNode(strdup((*left_rn)->str + idx));

        /* freeing the memory of the strings and the left node */
        free(left_string);
        free((void *)(*left_rn)->str);
        free((*left_rn));
        /* concatenation of the two auxiliary nodes */
        (*left_rn) = concat_nodes(aux_left_node, aux_right_node);
    }

    /* call function for left son */
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

RopeTree *insert(RopeTree *rt, int idx, const char *str) {
    /* TODO(Dinu Ion Irinel) */
    
    /* dividing the initial string according to the index */
    SplitPair pair = split(rt, idx);
    RopeTree *new_rp = makeRopeTree(pair.left);
    /* concatenation with the first half of the string that was split */
    new_rp->root = concat_nodes(new_rp->root, makeRopeNode(str));
    /* concatenation with the second part of the string */
    new_rp->root = concat_nodes(new_rp->root, pair.right);

    return new_rp;
}

RopeTree *delete (RopeTree *rt, int start, int len) {
    /* TODO(Serban Bianca-Sanziana) */
    
    /* dividing the string according to the start index */
    SplitPair pair1 = split(rt, start);
    /* creation of the new rope with the right side obtained
     * and division based on len index
     */
    RopeTree *new_rp = makeRopeTree(pair1.right);
    SplitPair pair2 = split(new_rp, len);
    /* concatenation of the first string obtained at the first division and
     * the second string obtained at the second division
     */
    new_rp->root = concat_nodes(pair1.left, pair2.right);
    return new_rp;
}
