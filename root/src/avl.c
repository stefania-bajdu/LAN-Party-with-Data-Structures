#include <tree.h>

tree_node *createAVL(List *list)
{
    tree_node *root = NULL;
    teamNode *copy;
    for (copy = list->head; copy != NULL; copy = copy->next)
        root = insertInAVL(root, copy);
    return root;
}

tree_node *rebalance(tree_node *root, teamNode *team)
{
    root->height = 1 + max(height(root->left), height(root->right));
    int k = balanceFactor(root);
    if (k > 1)
    {
        if (medie(team) == medie(root->left->team))
        {
            if (strcmp(team->teamName, root->left->team->teamName) < 0)
                return rightRotation(root);
            else
                return LRRotation(root);
        }
        else if (medie(team) < medie(root->left->team))
            return rightRotation(root);
        else
            return LRRotation(root);
    }
    if (k < -1)
    {
        if (medie(team) == medie(root->right->team))
        {
            if (strcmp(team->teamName, root->right->team->teamName) < 0)
                return RLRotation(root);
            else
                return leftRotation(root);
        }
        else if (medie(team) > medie(root->right->team))
            return leftRotation(root);
        else
            return RLRotation(root);
    }
    return root;
}

tree_node *insertInAVL(tree_node *root, teamNode *team)
{
    if (!root)
        return createBSTNode(team);
    if (medie(team) == medie(root->team))
    {
        if (strcmp(team->teamName, root->team->teamName) < 0)
            root->left = insertInAVL(root->left, team);
        else
            root->right = insertInAVL(root->right, team);
    }
    else if (medie(team) < medie(root->team))
        root->left = insertInAVL(root->left, team);
    else
        root->right = insertInAVL(root->right, team);

    return rebalance(root, team);
}

tree_node *rightRotation(tree_node *z) //cazul LL
{
    tree_node *y, *x;
    y = z->left;
    x = y->right;

    y->right = z;
    z->left = x;

    z->height = max(height(z->left), height(z->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

tree_node *leftRotation(tree_node *z) //cazul RR
{
    tree_node *y, *x;
    y = z->right;
    x = y->left;

    y->left = z;
    z->right = x;

    z->height = max(height(z->left), height(z->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

tree_node *LRRotation(tree_node *z) //rotatie la stanga + dreapta
{
    z->left = leftRotation(z->left);
    return rightRotation(z);
}

tree_node *RLRotation(tree_node *z) //rotatie la dreapta + stanga
{
    z->right = rightRotation(z->right);
    return leftRotation(z);
}

int balanceFactor(tree_node *root)
{
    if (!root)
        return 0;
    return height(root->left) - height(root->right);
}

int height(tree_node *root)
{
    if (!root)
        return -1;
    return root->height;
}

bool checkAVL(tree_node *root)
{
    if (!root)
        return true;
    int leftHeight, rightHeight, difference;
    leftHeight = height(root->left);
    rightHeight = height(root->right);
    if (leftHeight > rightHeight)
        difference = leftHeight - rightHeight;
    else
        difference = rightHeight - leftHeight;
    if (difference <= 1 && checkAVL(root->left) && checkAVL(root->right))
        return true;
    else
        return false;
}
