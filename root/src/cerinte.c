#include <tree.h>

List *cerinta2(FILE *output, List *list)
{
    list = eliminateLowScores(list);
    printList(list, output);
    return list;
}

List *cerinta3(FILE *output, List *list)
{
    Stack *winners;
    Queue *queue;
    List *clasament;
    createQueue(&queue);
    makeQueue(queue, list);
    createStack(&winners);
    clasament = NULL;
    while (!isEmptyQueue(queue))
    {
        printQueue(queue, output);
        while (!isEmptyQueue(queue))
        {
            push(&winners, deWinner(queue));
            de(queue);
        }
        printWinners(winners, output);
        if (winners->size == 8)
            clasament = createClasament(winners);
        remakeQueue(queue, winners);
    }
    deleteQueue(queue);
    deleteStack(&winners);
    return clasament;
}

void cerinta4(FILE *output, List *list)
{
    tree_node *root;
    root = createBST(list);
    if (checkBST(root, INT_MAX, 0))
    {
        fprintf(output, "\nTOP 8 TEAMS:\n");
        printInOrder(root, output);
        fflush(output);
    }
    else
        fprintf(output, "\nIS NOT BINARY SEARCH TREE.\n");
    deleteTree(root);
}

void cerinta5(FILE *output, List *list)
{
    tree_node *avl = NULL;
    avl = createAVL(list);
    if (checkAVL(avl))
    {
        fprintf(output, "\nTHE LEVEL 2 TEAMS ARE: \n");
        printL2(avl, 0, output);
        fflush(output);
    }
    else
        fprintf(output, "\nIS NOT AVL TREE.\n");
    deleteTree(avl);
}
