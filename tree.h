//
// Created by dunka on 08.11.2019.
//

#ifndef TREE_TREE_H
#define TREE_TREE_H

#include <cstdlib>
#include <cstdio>

enum tree {
    RIGHT         = 0,
    LEFT          = 1,
    PUT_OK        = 10,
    ADRESS_ERROR  = -1,
    SIDE_ERROR    = - 2,
    POISON        = -91,


};


struct element {
    char* question;
    struct element* prev;
    struct element* left;
    struct element* right;
};


#define NullPTRRRRRR_YA_SGOREL(what)                                \
{                                                                   \
    if (what == nullptr)                                            \
    {                                                               \
        printf ("ERRRRORRR NUUUUULPTRRRRRRRR!!!!!!!!!!!");          \
        return ADRESS_ERROR;                                        \
    }                                                               \
}

struct element* CreateElement (char* question)
{
    struct element* new_elem = (struct element*) calloc (1, sizeof (struct element));

    new_elem->question = question;
    new_elem->prev = nullptr;
    new_elem->right = nullptr;
    new_elem->left  = nullptr;

    return new_elem;
}


int Merge (struct element* what, struct element* node, int side)
{
    NullPTRRRRRR_YA_SGOREL (node);
    NullPTRRRRRR_YA_SGOREL (what);

    if ((side != RIGHT) && (side != LEFT))
    {
        printf ("ERROR SIDE IS NOT RIGHT");
        return SIDE_ERROR;
    }

    struct element* tmp = nullptr;

    if (side == RIGHT)
    {
        tmp = node->right;
    }

    if (side == LEFT)
    {
        tmp = node->left;
    }

    //printf ("%p   ", tmp);

    if (tmp == nullptr)
    {
        what->right = nullptr;
        what->left  = nullptr;
        what->prev  = node;

        if (side == RIGHT)
        {
            node->right = what;
            //printf ("%p", node->left);
        }

        if (side == LEFT)
        {
            node->left = what;
            //printf ("%p", node->left);
        }

        return PUT_OK;
    }

    what->prev  = node;
    what->right = tmp->right;
    what->left  = tmp->left;
}


int DeleteUnderNode (struct element* node)
{
    NullPTRRRRRR_YA_SGOREL (node)

    node->question = nullptr;
    node->prev     = nullptr;
    node->left     = nullptr;
    node->right    = nullptr;

    if (node->right != nullptr)
    {
        DeleteUnderNode (node->right);
    }

    if (node->left != nullptr)
    {
        DeleteUnderNode (node->left);
    }

    free (node);
}

void DeleteTree (struct element* node)
{
    DeleteUnderNode (node);
}

int Announce (struct element* node, FILE* out)
{
    NullPTRRRRRR_YA_SGOREL (node)

    fprintf (out, "Node%p [shape=record,label=\"{  adress = %p | value = %s | prev = %p |{ <l%p> left = %p| <r%p> right = %p  }}\"];\n",
             node, node, node->question, node->prev, node, node->left, node, node->right);

    if (node->right != nullptr)
    {
        Announce (node->right, out);
    }

    if (node->left != nullptr)
    {
        Announce (node->left, out);
    }
}

int PaintTree (struct element* node, FILE* out)
{
    NullPTRRRRRR_YA_SGOREL (node)

    if (node->left  != nullptr)         fprintf (out, "Node%p:<l%p> -> Node%p:<%p>;\n", node, node, node->left,  node->left);
    if (node->right != nullptr)         fprintf (out, "Node%p:<r%p> -> Node%p:<%p>;\n", node, node, node->right, node->right);
    if (node->prev  != nullptr)         fprintf (out, "Node%p -> Node%p;\n", node, node->prev);

    if (node->right != nullptr)
    {
        PaintTree (node->right, out);
    }

    if (node->left != nullptr)
    {
        PaintTree (node->left, out);
    }
}

int Dump (struct element* node)
{
    NullPTRRRRRR_YA_SGOREL (node)

    FILE* out = fopen ("tree.dot", "w");

    fprintf (out, "digraph structs {\nrankdir=HR;\n");

    Announce (node, out);
    PaintTree (node, out);

    fprintf (out, "\n}");

    fclose (out);

    system ("D:\\Graphiz\\bin\\dot.exe tree.dot -T png -o tree.png");
    system ("tree.png");
}

int PaintTree_s (struct element* node, FILE* out)
{
    NullPTRRRRRR_YA_SGOREL (node)

    if (node->left  != nullptr)         fprintf (out, "\"%s?\" -> \"%s?\"[label=\"нет\"];\n", node->question, node->left->question);
    if (node->right != nullptr)         fprintf (out, "\"%s?\" -> \"%s?\"[label=\"да\"];\n", node->question, node->right->question);

    if (node->right != nullptr)
    {
        PaintTree_s (node->right, out);
    }

    if (node->left != nullptr)
    {
        PaintTree_s (node->left, out);
    }
}

int Show (struct element* node)
{
    NullPTRRRRRR_YA_SGOREL (node)

    FILE* out = fopen ("show.dot", "w");

    fprintf (out, "digraph structs {\nrankdir=HR;\nedge[color=\"darkgreen\",fontcolor=\"blue\",fontsize=15];\n");

    PaintTree_s (node, out);

    fprintf (out, "\n}");

    fclose (out);

    system ("D:\\Graphiz\\bin\\dot.exe show.dot -T png -o show.png");
    system ("show.png");
}


#endif //TREE_TREE_H
