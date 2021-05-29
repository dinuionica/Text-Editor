#include "./rope.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "utils.h"

#define EMPTY ""

RopeNode *makeRopeNode(const char *str)
{

    /* crearea nodului */
    RopeNode *node = malloc(sizeof(RopeNode));
    DIE(node == NULL, "Allocation error rope_node\n");

    /* actualizare pointeri */
    node->left = NULL;
    node->right = NULL;

    /* actualizare valoare string */
    node->str = str;
    /* actualizare inaltime */
    node->weight = 0;

    return node;
}

RopeTree *makeRopeTree(RopeNode *root)
{

    /* creare arbore */
    RopeTree *rope_tree = malloc(sizeof(RopeTree));
    DIE(rope_tree == NULL, "Allocation error rope_tree\n");

    /* actualizare radacina */
    rope_tree->root = root;

    return rope_tree;
}

void printRopeNode(RopeNode *rn)
{
    if (!rn)
        return;

    if (!(rn->left) && !(rn->right))
    {
        printf("%s", rn->str);
        return;
    }

    printRopeNode(rn->left);
    printRopeNode(rn->right);
}

void printRopeTree(RopeTree *rt)
{
    if (rt && rt->root)
    {
        printRopeNode(rt->root);
        printf("%s", "\n");
    }
}

void debugRopeNode(RopeNode *rn, int indent)
{
    if (!rn)
        return;

    for (int i = 0; i < indent; ++i)
        printf("%s", " ");

    if (!strcmp(rn->str, EMPTY))
        printf("# %d\n", rn->weight);
    else
        printf("%s %d\n", rn->str, rn->weight);

    debugRopeNode(rn->left, indent + 2);
    debugRopeNode(rn->right, indent + 2);
}

int getTotalWeight(RopeNode *rt)
{
    if (!rt)
        return 0;

    return rt->weight + getTotalWeight(rt->right);
}

RopeTree *concat(RopeTree *rt1, RopeTree *rt2)
{
    // TODO 1. Concat - 10p

    /* crearea noului rope */
    RopeTree *rt3 = malloc(sizeof(RopeTree));
    rt3->root = malloc(sizeof(RopeNode));

    /* actualizarea pointerilor left si right */
    (rt3->root)->left = rt1->root;
    (rt3->root)->right = rt2->root;

    /* actualizare greutate */
    (rt3->root)->weight = getTotalWeight(rt1->root->left);

    (rt3->root)->str = NULL;

    return rt3;
}

char indexRope(RopeTree *rt, int idx)
{
    // TODO 2. Index - 10p
    
}

char *search(RopeTree *rt, int start, int end)
{
    // TODO 3. Search - 20p
}

SplitPair split(RopeTree *rt, int idx)
{
    // TODO 4. Split - 20p
}

RopeTree *insert(RopeTree *rt, int idx, const char *str)
{
    // TODO 5. Insert - 5p
}

RopeTree *delete (RopeTree *rt, int start, int len)
{
    // TODO 6. Delete - 5p
}

// FINAL 10p -> complex test involving all operations
