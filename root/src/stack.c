#include <stack.h>

void printQueue(Queue *queue, FILE *output)
{
    queue_node *copy;
    static int contor = 0;
    contor++;
    fprintf(output, "\n--- ROUND NO:%d\n", contor);
    for (copy = queue->front; copy != NULL; copy = copy->next)
    {
        fprintf(output, "%s", copy->team1->teamName);
        fprintf(output, "%*c%33s\n", (int)(34 - strlen(copy->team1->teamName)), '-', copy->team2->teamName);
    }
    fflush(output);
}

void printWinners(Stack *winners, FILE *output)
{
    stack_node *copy;
    static int contor = 0;
    contor++;
    fprintf(output, "\nWINNERS OF ROUND NO:%d\n", contor);
    for (copy = winners->head; copy != NULL; copy = copy->next)
    {
        fprintf(output, "%s", copy->team->teamName);
        fprintf(output, "%*c  %.2f\n", (int)(35 - strlen(copy->team->teamName)), '-', medie(copy->team));
    }
    fflush(output);
}

void createStack(Stack **stack)
{
    *stack = (Stack *)malloc(sizeof(Stack));
    (*stack)->head = (stack_node *)malloc(sizeof(stack_node));
    (*stack)->head = NULL;
    (*stack)->size = 0;
}

void createQueue(Queue **queue)
{
    *queue = (Queue *)malloc(sizeof(Queue));
    (*queue)->front = (queue_node *)malloc(sizeof(queue_node));
    (*queue)->rear = (queue_node *)malloc(sizeof(queue_node));
    (*queue)->front = NULL;
    (*queue)->rear = NULL;
}

bool isEmptyQueue(Queue *queue)
{
    if (!queue->front)
        return true;
    else
        return false;
}

bool isEmptyStack(Stack *stack)
{
    if (!stack->head)
        return true;
    else
        return false;
}

teamNode *copyData(teamNode *source)
{
    int i;
    teamNode *copy = (teamNode *)malloc(sizeof(teamNode));
    copy->numberOfPlayers = source->numberOfPlayers;
    copy->teamName = strdup(source->teamName);
    copy->players = (player **)malloc(sizeof(player *) * copy->numberOfPlayers);
    for (i = 0; i < copy->numberOfPlayers; i++)
        copy->players[i] = makePlayerNode(source->players[i]->firstName, source->players[i]->secondName, source->players[i]->points);
    copy->next = NULL;
    return copy;
}

stack_node *createStackNode(teamNode *data, stack_node *next)
{
    stack_node *newNode = (stack_node *)malloc(sizeof(stack_node));
    newNode->team = copyData(data);
    newNode->next = next;
    return newNode;
}

void push(Stack **stack, teamNode *data)
{
    if (isEmptyStack(*stack))
        (*stack)->head = createStackNode(data, NULL);
    else
        (*stack)->head = createStackNode(data, (*stack)->head);
    (*stack)->size++;
}

teamNode *pop(Stack **stack)
{
    teamNode *data;
    stack_node *copy;
    if (isEmptyStack(*stack))
        return NULL;
    data = copyData((*stack)->head->team);
    copy = (*stack)->head->next;
    deleteNodeData((*stack)->head->team);
    free((*stack)->head->team);
    free((*stack)->head);
    (*stack)->head = copy;
    (*stack)->size--;
    return data;
}

void deleteStack(Stack **stack)
{
    stack_node *copy;
    while (!isEmptyStack(*stack))
    {
        copy = (*stack)->head->next;
        deleteNodeData((*stack)->head->team);
        free((*stack)->head->team);
        free((*stack)->head);
        (*stack)->head = copy;
        (*stack)->size--;
    }
    free(*stack);
    *stack = NULL;
}

void deleteQueueNode(queue_node *oldNode)
{
    deleteNodeData(oldNode->team1);
    deleteNodeData(oldNode->team2);
    free(oldNode->team1);
    free(oldNode->team2);
}

void deleteQueue(Queue *queue)
{
    while (!isEmptyQueue(queue))
        de(queue);
    free(queue);
    queue = NULL;
}

queue_node *createQueueNode(teamNode *firstTeam, teamNode *secondTeam)
{
    queue_node *newNode = (queue_node *)malloc(sizeof(queue_node));
    newNode->team1 = copyData(firstTeam);
    newNode->team2 = copyData(secondTeam);
    return newNode;
}

void en(Queue *queue, teamNode *one, teamNode *two)
{
    if (!queue->rear)
    {
        queue->rear = createQueueNode(one, two);
        queue->rear->next = NULL;
    }
    else
    {
        queue->rear->next = createQueueNode(one, two);
        queue->rear = queue->rear->next;
        queue->rear->next = NULL;
    }
    if (!queue->front)
        queue->front = queue->rear;
}

void makeQueue(Queue *queue, List *list)
{
    teamNode *copy = list->head;
    while (copy)
    {
        en(queue, copy, copy->next);
        copy = copy->next->next;
    }
}

teamNode *deWinner(Queue *queue)
{
    teamNode *data;
    int i;
    if (punctaj(queue->front->team1) <= punctaj(queue->front->team2))
        data = copyData(queue->front->team2);
    else
        data = copyData(queue->front->team1);
    for (i = 0; i < data->numberOfPlayers; i++)
        data->players[i]->points += 1;
    return data;
}

teamNode *deLoser(Queue *queue)
{
    teamNode *data;
    if (punctaj(queue->front->team1) <= punctaj(queue->front->team2))
        data = copyData(queue->front->team1);
    else
        data = copyData(queue->front->team2);
    return data;
}

void de(Queue *queue)
{
    queue_node *copy;
    copy = queue->front->next;
    deleteQueueNode(queue->front);
    queue->front = copy;
}

void remakeQueue(Queue *queue, Stack *winners)
{
    teamNode *one, *two;
    while (!isEmptyStack(winners))
    {
        one = pop(&winners);
        two = pop(&winners);
        if (one && two)
            en(queue, one, two);
    }
}

List *createClasament(Stack *winners)
{
    List *clasament = (List *)malloc(sizeof(List));
    stack_node *copy;
    teamNode *prev;
    clasament->numberOfTeams = 8;
    clasament->head = NULL;
    for (copy = winners->head; copy != NULL; copy = copy->next)
    {
        prev = clasament->head;
        clasament->head = copyData(copy->team);
        clasament->head->next = prev;
    }
    return clasament;
}
