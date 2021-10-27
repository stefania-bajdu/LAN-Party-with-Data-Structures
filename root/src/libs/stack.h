#include <player.h>

typedef struct queue_node
{
    teamNode *team1, *team2;
    struct queue_node *next;
} queue_node;

typedef struct queue
{
    queue_node *front, *rear;
} Queue;

typedef struct stack_node
{
    teamNode *team;
    struct stack_node *next;
} stack_node;

typedef struct stack
{
    int size;
    stack_node *head;
} Stack;

stack_node *createStackNode(teamNode *, stack_node *);
void createStack(Stack **);
void deleteStack(Stack **);
void push(Stack **, teamNode *);
teamNode *pop(Stack **);
bool isEmptyStack(Stack *);
queue_node *createQueueNode(teamNode *, teamNode *);
void createQueue(Queue **);
void en(Queue *, teamNode *, teamNode *);
void makeQueue(Queue *, List *);
teamNode *deWinner(Queue *);
teamNode *deLoser(Queue *);
void de(Queue *);
void deleteQueueNode(queue_node *);
void deleteQueue(Queue *);
bool isEmptyQueue(Queue *);
void printQueue(Queue *, FILE *);
void printWinners(Stack *, FILE *);
void remakeQueue(Queue *, Stack *);
List *createClasament(Stack *);
teamNode *copyData(teamNode *);