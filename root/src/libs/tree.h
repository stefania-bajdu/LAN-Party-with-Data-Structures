#include <stack.h>
#define INT_MAX 1000

typedef struct tree_node
{
    teamNode *team;
    struct tree_node *left, *right;
    int height;
} tree_node;

void deleteTree(tree_node *);
void printInOrder(tree_node *, FILE *);
void printL2(tree_node *, int, FILE *);
tree_node *createBSTNode(teamNode *);
tree_node *insertInBST(tree_node *, teamNode *);
tree_node *insertInAVL(tree_node *, teamNode *);
tree_node *createBST(List *);
tree_node *createAVL(List *);
bool checkBST(tree_node *, float, float);
bool checkAVL(tree_node *);
int max(int, int);
tree_node *rightRotation(tree_node *);
tree_node *leftRotation(tree_node *);
tree_node *LRRotation(tree_node *);
tree_node *RLRotation(tree_node *);
int balanceFactor(tree_node *);
int height(tree_node *);
tree_node *rebalance(tree_node *, teamNode *);

List *cerinta2(FILE *, List *);
List *cerinta3(FILE *, List *);
void cerinta4(FILE *, List *);
void cerinta5(FILE *, List *);