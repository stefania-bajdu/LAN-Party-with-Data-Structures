#include <tree.h>

int max(int x, int y)
{
    if (x > y)
        return x;
    else
        return y;
}

tree_node *createBSTNode(teamNode *team)
{
    tree_node *newNode;
    newNode = (tree_node *)malloc(sizeof(tree_node));
    newNode->team = copyData(team);
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 0;
    return newNode;
}

tree_node *insertInBST(tree_node *root, teamNode *team)
{
    if (!root)
        return createBSTNode(team);
    if (medie(team) == medie(root->team))
    {
        if (strcmp(team->teamName, root->team->teamName) < 0)
            root->left = insertInBST(root->left, team);
        else
            root->right = insertInBST(root->right, team);
    }
    else if (medie(team) < medie(root->team))
        root->left = insertInBST(root->left, team);
    else
        root->right = insertInBST(root->right, team);
    return root;
}

tree_node *createBST(List *list)
{
    tree_node *root = NULL;
    teamNode *copy;
    for (copy = list->head; copy != NULL; copy = copy->next)
        root = insertInBST(root, copy);
    return root;
}

bool checkBST(tree_node *root, float max, float min)
{
    bool x, y;
    if (!root)
        return true;
    if (medie(root->team) < min)
        return false;
    if (medie(root->team) > max)
        return false;
    x = checkBST(root->right, max, medie(root->team));
    y = checkBST(root->left, medie(root->team), min);
    if (x && y)
        return true;
    else
        return false;
}

void printL2(tree_node *root, int level, FILE *output)
{
    if (!root)
        return;
    if (level == 2)
        fprintf(output, "%s\n", root->team->teamName);
    else
    {
        printL2(root->right, level + 1, output);
        printL2(root->left, level + 1, output);
    }
}

void printInOrder(tree_node *root, FILE *output)
{
    if (!root)
        return;
    printInOrder(root->right, output);
    fprintf(output, "%s", root->team->teamName);
    fprintf(output, "%*c  %.2f\n", (int)(35 - strlen(root->team->teamName)), '-', medie(root->team));
    printInOrder(root->left, output);
}

void deleteTree(tree_node *root)
{
    if (root)
    {
        if (root->left)
            deleteTree(root->left);
        if (root->right)
            deleteTree(root->right);
        deleteNodeData(root->team);
        free(root->team);
        free(root);
    }
    else
        return;
}
