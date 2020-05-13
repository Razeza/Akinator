#include <zconf.h>
#include <assert.h>
#include "stdio.h"
#include "tree.h"
#include "C:/Users/dunka/CLionProjects/mipt_ded_32/MyLib/MyLib.h"
#include "windows.h"
#include "graphics.h"



const char* namein          = "code.txt";
const char* back_gr         = "back.bmp";
const int MAX_SIZE_QUESTION = 100;

enum IS_OK {
    OK1 = 7,
    OK2 = 8,
    OK3 = 9,
};

/*!
 * Adds element to node
 * @param node
 * @param code parssed text
 * @param deep
 * @param head
 */
int Make_Element (struct element* node, struct Text* code, int deep, struct element* head);

/*!
 * Make tree from code
 * @return head of tree
 */
struct element* Make_Tree ();

/*!
 * Write element of the tree to the file
 * @param element
 * @param out file stream
 * @param deep
 */
int WriteElem (struct element* elem, FILE* out, int deep);

/*!
 * Writes code to the file
 * @param tree
 */
int Rewrite (struct element* tree);

/*!
 * Create new element and adds it to the tree
 * @param elem ent
 */
int NewElem (struct element* elem);

/*!
 * Asks questions
 * @param element
 */
int Question (struct element* elem, HDC back);

/*!
 * Akinator
 * @param head of the tree
 * @return error code
 */
int Game (struct element* head, struct Button* menu, HDC back, char* say);

/*!
 * Find element oat the end of the tree
 * @param object to find
 * @param element
 * @param answer - place to put answer
 * @return answer
 */
struct element* FindElement (const char* object, struct element* elem, struct element** answer);

/*!
 * Makes definition
 * @param object
 * @param head of th tree
 * @return error code
 */
int MakeDefinition (const char* object, struct element* head);

/*!
 * Writes definition to the std
 * @param answer
 * @param name
 */
int WriteDefinition (struct element* answer, char* name);

/*!
 * Makes Difference
 * @param object1
 * @param object2
 * @param head
 * @return error code
 */
int MakeDifference (const char* object1, const char* object2, struct element* head);

/*!
 * SAYS what is deeper
 * @param obg1
 * @param obg2
 * @return the deepest node code
 */
int WhatIsDeeper (element* obg1, element* obg2);

/*!
 * Find deep of the node
 * @param obg
 * @return
 */
int FindDeep (struct element* obg);

int main ()
{
    struct element* head = Make_Tree ();

    txCreateWindow (800, 800);

    HDC background = txLoadImage (back_gr);
    if (!background)
        txMessageBox ("!!!!!!!!!!");


    struct Button menu[] = {{MENU_PLAY,       "Play",       40, 250, 450, 550, 500},
                            {MENU_DIFF,       "Difference", 40,  25, 450, 225, 500},
                            {MENU_TREE,       "Show tree",  40, 575, 450, 775, 500},
                            {MENU_DEFINITION, "Definition", 40, 250, 550, 550, 600},
                            {MENU_EXIT,       "Exit",       40, 250, 650, 550, 700},
                            {MENU_END}};

    Game (head, menu, background, "Hi poopsik! Choose mode to play");

     return 0;
}

int Make_Element (struct element* node, struct Text* code, int deep, struct element* head)
{
    NullPTRRRRRR_YA_SGOREL (node)
    NullPTRRRRRR_YA_SGOREL (code)

    code++;
    char* check = (char*) calloc (MAX_SIZE_QUESTION, sizeof (char));
    sscanf (code->begin, "%s", check);

    int side = -1;

    if (strcmp (check, "{") == 0)
    {
        deep++;
        side = LEFT;
    }

    if (strcmp (check, "}") == 0)
    {
        side = RIGHT;
    }

    if ((side != RIGHT) && (side != LEFT))      printf ("ERROR SIDE");

    struct element* prev = node;
    if (side == RIGHT)
    {
        while (strcmp (check, "}") == 0)
        {
            deep--;
            if (deep == 0)
                return OK1;

            code++;
            sscanf (code->begin, "%s", check);

            prev = prev->prev;
        }
        deep++;
    }

    code++;

    char* question = (char*) calloc (MAX_SIZE_QUESTION, sizeof (char));
    sscanf (code->begin, "%*[\t]%[^0]", question);

    struct element* elem = CreateElement (question);

    if (side == LEFT)
    {
        Merge (elem, node, side);
        Make_Element (elem, code, deep, head);

        return OK2;
    }

    if (side == RIGHT)
    {
        Merge (elem, prev, side);
        Make_Element (elem, code, deep, head);

        return OK3;
    }

}

struct element* Make_Tree ()
{
    struct Text * code = nullptr;
    code = Input (namein);

    char* question = (char*) calloc (MAX_SIZE_QUESTION, sizeof (char));

    code++;             ///так работает функция Input, она распарсила всё на строки
                        ///++ делается всвязи синтаксисом исходника
    sscanf (code->begin, "%s", question);

    struct element* head = CreateElement (question);

    int deep = 1;
    Make_Element (head, code, deep, head);

    return head;
}

int WriteElem (struct element* elem, FILE* out, int deep)
{
    NullPTRRRRRR_YA_SGOREL (elem)
    int length = strlen (elem->question);

    if (length % 8 == 0)    length /= 8;
    else                    length = length/8 + 1;


    for (int i = 0; i< deep; i++)       fprintf (out, "\t");
                                        fprintf (out, "{\n");

    for (int i = 0; i<= deep; i++)      fprintf (out, "\t");

                                        fprintf (out, "%s\n", elem->question);

    int tmp = deep;

    if (elem->left != nullptr)
    {
        deep += length + 1;
        WriteElem (elem->left, out, deep);
    }

    if (elem->right != nullptr)
    {
        WriteElem (elem->right, out, deep);
    }

    for (int i = 0; i < tmp; i++)       fprintf (out, "\t");
                                        fprintf (out, "}\n");
}

int Rewrite (struct element* tree)
{
    NullPTRRRRRR_YA_SGOREL (tree)
    FILE* out = fopen ("C:\\Users\\dunka\\CLionProjects\\tree\\code.txt", "w");

    CopyFile ("C:\\Users\\dunka\\CLionProjects\\tree\\code.txt", "C:\\Users\\dunka\\CLionProjects\\tree\\copy.txt", FALSE);
    int deep = 0;

    WriteElem (tree, out, deep);

    fclose (out);
}

int NewElem (struct element* elem)
{
    NullPTRRRRRR_YA_SGOREL (elem)

    Say ("What did you guess?");

    struct element* answer = CreateElement (strdup (txInputBox ("What do you mean? :", "Put new elem")));

    char* question = strdup (txInputBox ("What differ yours object from mine? :", "Put new elem"));

    struct element* tmp = CreateElement (elem->question);

    Merge (answer, elem, RIGHT);
    Merge (tmp, elem, LEFT);

    elem->question = question;
}

void I_WON ()
{
    txClear ();

    txSetFillColor (TX_BLACK);
    txRectangle (0, 0, 800, 800);


    HDC win = txLoadImage ("C:\\Users\\dunka\\CLionProjects\\tree\\win.bmp");

    if (!win)
        txMessageBox ("!!!!!!!!!!");

    txBitBlt (txDC(), 0, 0, 800, 800, win, 0, 0);

    txSelectFont ("Times New Roman", 100);
    txSetColor (TX_BLUE);
    txTextOut (300, 400, "I WON");
    txTextOut (170, 500, "HEHHEHEHHE");
    Say ("I won HEHEHEHEHHEHEHEHEHEHEHEH");
}

enum question {
    YES = 0,
    NO = 1,
    QUESTION = 3,

};

int Question (struct element* elem, HDC back)
{
    NullPTRRRRRR_YA_SGOREL (elem)

    struct Button question[] = {{YES,      "YES",          40,  200, 450, 260, 490},
                                {NO,       "NO" ,          40,  500, 450, 560, 490},
                                {QUESTION, elem->question, 100, 300, 100, 300, 100},
                                {MENU_END}};

    Draw (question, back);

    txTextOut (300 + txGetTextExtentX (elem->question), 100, "?");
    Say (elem->question);

    switch (CheckMenu (question))
    {
        case YES:
        {
            if (elem->right != nullptr)
            {
                Say ("Oh my");
                txSleep (200);
                Question (elem->right, back);
            }
            else
            {
                I_WON ();
            }
            break;
        }
        case NO:
        {
            if (elem->left != nullptr)
            {
                Say ("Oh no");
                txSleep (200);
                Question (elem->left, back);
            }
            else
            {
                Say ("Oh shit, I have lost");
                NewElem (elem);
            }
            break;
        }
        case QUESTION:
        {
            CheckMenu (question);
            break;
        }
        default:
        {
            txMessageBox ("MENU ISN't RIGHT", "ERROR");
            break;
        }
    }
}

enum ToMenu {
    To_Menu = 5
};

void ToMenu (struct element* head, struct Button* menu, HDC back)
{
    struct Button Tomenu[] = {{To_Menu, "To menu", 75, 275, 650, 275 + txGetTextExtentX ("To menu"), 725},
                              {MENU_END}};
    Draw (Tomenu, back);

    switch (CheckMenu (Tomenu))
    {
        case To_Menu:
        {
            Game (head, menu, back, "Oh no, you are again");
            break;
        }
        default:
        {
            txMessageBox ("MENU ISN't RIGHT", "ERROR");
            break;
        }
    }
}

#define END 154

void  Menu (struct element* head, struct Button* menu, HDC back, char* say)
{
    Draw (menu, back);
    Say (say);

    switch (CheckMenu (menu))
    {
        case MENU_TREE:
        {
            Say ("Smotri na svou poebotoo");
            Show (head);
            Game (head, menu, back, "Nasmotrelsya?");
            break;
        }
        case MENU_DEFINITION:
        {
            Say ("Oh, you want to find definition");

            const char* object = strdup (txInputBox ("Definition of? :", "Definition"));

            MakeDefinition (object, head);
            ToMenu (head, menu, back);
            break;
        }
        case MENU_DIFF:
        {
            Say ("It is too hard, let us try");

            const char* object1 = strdup (txInputBox ("object1 :", "Put new elem"));
            const char* object2 = strdup (txInputBox ("object2 :", "Put new elem"));

            MakeDifference (object1, object2, head);
            ToMenu (head, menu, back);
            break;
        }
        case MENU_EXIT:
        {
            Say ("Are you sure? I am disappointed! See you later");
            txDeleteDC (back);
            system ("taskkill /IM tree.exe /F");
            exit (END);
        }
        case MENU_PLAY:
        {
            break;
        }
        default:
        {
            txMessageBox ("MENU ISN't RIGHT", "ERROR");
            break;
        }
    }
}

#undef END



int Game (struct element* head, struct Button* menu, HDC back, char* say)
{
    NullPTRRRRRR_YA_SGOREL (head)

    Menu (head, menu, back, say);

    Say ("Nu let us play");
    Question (head, back);

    Rewrite (head);
    ToMenu (head, menu, back);
}

struct element* FindElement (const char* object, struct element* elem, struct element** answer)
{
    assert (answer);

    if  (elem->left != nullptr)
        FindElement (object, elem->left, answer);

    if  (elem->right != nullptr)
        return FindElement (object, elem->right, answer);

    if  ((elem->left == nullptr) && (elem->right == nullptr))
        if (strcmp (object, elem->question) == 0)
            *answer = elem;
}

void Compare (const char* what, int* x, int* y)
{
    if (800 - *x < strlen (what))
    {
        *y += 16;
        *x = 0;
    }
    txTextOut (*x, *y, what);
    *x += strlen (what) * 16;
}

int WriteDefinition (struct element* answer, char* name, int x, int y)
{
    NullPTRRRRRR_YA_SGOREL (answer)
    //printf ("\n%s:  ", name);
    struct element* tmp = answer;
    answer = answer->prev;
    //printf ("tits");


    txSetColor (TX_WHITE);
    txSelectFont ("Times New Roman", 30);

    txTextOut (x, y, name);
    Say (name);
    Say ("is");
    x += strlen (name) * 16;
    txTextOut (x, y, ":");
    x += strlen (":") * 16;

    while (answer != nullptr)
    {
        if (tmp == answer->left)
        {

            Compare ("none", &x, &y);
            Compare (answer->question, &x, &y);
            Compare (",", &x, &y);
            Say ("none");
            Say (answer->question);
        }
        if (tmp == answer->right)
        {
            Compare (answer->question, &x, &y);
            Compare (",", &x, &y);
            Say (answer->question);
        }
        answer = answer->prev;
        tmp    = tmp->prev;
    }

    Compare ("that's all))", &x, &y);
    Say ("that is all");
}

int MakeDefinition (const char* object, struct element* head)
{
    NullPTRRRRRR_YA_SGOREL (head)

    struct element* answer = nullptr;
    FindElement (object, head, &answer);

    if (answer == nullptr)
    {
        txMessageBox ("NO SUCH ELEMENT!!!", "ERROR");
        Say ("Fucking stupid dick, there are no such elements");
        return 0;
    }

    int x = 0;
    int y = 0 ;

    txClear ();

    txSetFillColor (TX_BLACK);
    txRectangle (0, 0, 800, 800);
    WriteDefinition (answer, answer->question, x, y);
}

enum deep {
    OBG1_DEEPER = 789,
    OBG2_DEEPER = 524,
};

int MakeDifference (const char* object1, const char* object2, struct element* head)
{
    NullPTRRRRRR_YA_SGOREL (head)

    struct element* obg1 = nullptr;
    FindElement (object1, head, &obg1);

    struct element* obg2 = nullptr;
    FindElement (object2, head, &obg2);

    if ((obg1 == nullptr) || (obg2 == nullptr))
    {
        txMessageBox ("NO SUCH ELEMENT!!!", "ERROR");
        Say ("Fucking stupid dick, there are no such elements");
        return 0;
    }

    txClear ();

    txSetFillColor (TX_BLACK);
    txRectangle (0, 0, 800, 800);

    int TheDeepest = WhatIsDeeper (obg1, obg2);

    if (TheDeepest == OBG2_DEEPER)
    {
        struct element* tmp = obg1;
        obg1 = obg2;
        obg2 = tmp;
    }

    int x = 0;
    int y = 0;
    txSetColor (TX_WHITE);
    txSelectFont ("Times New Roman", 30);

    txTextOut (x, y, obg1->question);
    Say (obg1->question);
    Say ("is");
    x += strlen (obg1->question) * 11;
    Compare (":", &x, &y);

    struct element* tmp = obg1;
    obg1 = obg1->prev;

    while ((tmp->prev != obg2->prev) && (tmp->prev != nullptr))
    {
        if (tmp == obg1->left)
        {
            Say ("hmmm, none");
            Say (obg1->question);
            Compare ("none", &x, &y);
            Compare (obg1->question, &x, &y);
            Compare (",", &x, &y);
        }

        if (tmp == obg1->right)
        {
            Say ("I think");
            Say (obg1->question);
            Compare (obg1->question, &x, &y);
            Compare (",", &x, &y);
        }

        tmp  = tmp->prev;
        obg1 = obg1->prev;
    }

    if (tmp->prev == nullptr)
    {
        y += 20;
        x = 0;
        WriteDefinition (obg2, obg2->question, x, y);
        return 8;
    }

    if (obg1 != obg2)
    {
        if (obg1->prev->right == obg1)
        {
            Compare (obg2->prev->question, &x, &y);

            y += 20;
            x = 0;

            Compare ("And ", &x, &y);
            Compare (obg2->question, &x, &y);
            Compare (": none ",  &x, &y);
            Compare (obg2->prev->question, &x, &y);
            Say ("And"); Say (obg1->question); Say ("none"); Say (obg2->prev->question);
            y += 20;
            x = 0;

            //printf (" %s\nAnd %s : none %s\n", obg2->prev->question, obg2->question, obg2->prev->question);
        }
        else
        {
            Compare (" none ", &x, &y);
            Compare (obg2->prev->question, &x, &y);
            Say ("none");
            Say (obg2->prev->question);
            y += 20;
            x = 0;

            Compare ("And ", &x, &y);
            Compare (obg2->question, &x, &y);
            Compare (": ",  &x, &y);
            Compare (obg2->prev->question, &x, &y);
            Say ("And"); Say (obg2->question); Say (obg2->prev->question);

            //printf (" none %s\nAnd %s : %s\n", obg2->prev->question, obg2->question, obg2->prev->question);
            y += 20;
            x = 0;
        }
    }
    WriteDefinition (obg1, "The same", x, y);
}

int FindDeep (struct element* obg)
{
    int deep = 0;
    while (obg != nullptr)
    {
        deep++;
        obg = obg->prev;
    }
    return deep;
}

int WhatIsDeeper (struct element* obg1, struct element* obg2)
{
    int deep1 = FindDeep (obg1);
    int deep2 = FindDeep (obg2);

    if (deep1 > deep2)
        return OBG1_DEEPER;
    else
        return OBG2_DEEPER;
}



