#include <player.h>

char *trimWhiteSpace(char *string)
{
    while (isspace(*string))
        string++;
    int size = strlen(string);
    char *copy = (char *)malloc(size * sizeof(char));
    int i = 0, k = 0;
    while (i < size)
    {
        if (!isspace(string[i]))
            copy[k++] = string[i];
        else if (!isspace(string[i + 1]) && string[i + 1] != '\n' && i + 1 != size)
        {
            copy[k++] = ' ';
            copy[k++] = string[i + 1];
            i++;
        }
        i++;
    }
    copy[k] = '\0';
    string = (char *)realloc(copy, (k + 1) * sizeof(char));
    return string;
}

player *makePlayerNode(char *first, char *second, int points)
{
    player *newNode = (player *)malloc(sizeof(player));
    newNode->firstName = strdup(first);
    newNode->secondName = strdup(second);
    newNode->points = points;
    return newNode;
}

teamNode *makeTeamNode(FILE *input, teamNode *next)
{
    teamNode *newNode = (teamNode *)malloc(sizeof(teamNode));
    int size, i = 0, points;
    char name[80], auxFirst[80], auxSecond[80];
    fscanf(input, "%d", &size);
    fgets(name, 80, input);
    newNode->numberOfPlayers = size;
    newNode->teamName = strdup(trimWhiteSpace(name));
    newNode->players = (player **)malloc(size * sizeof(player *));
    for (i = 0; i < size; i++)
        if (fscanf(input, "%s%s%d", auxFirst, auxSecond, &points) == 3)
            newNode->players[i] = makePlayerNode(auxFirst, auxSecond, points);
    newNode->next = next;
    return newNode;
}

List *makeList(FILE *input)
{
    int i;
    List *list = (List *)malloc(sizeof(List));
    list->head = NULL;
    fscanf(input, "%d", &list->numberOfTeams);
    for (i = 0; i < list->numberOfTeams; i++)
        list->head = makeTeamNode(input, list->head);
    return list;
}

void deleteNodeData(teamNode *oldNode)
{
    int i;
    for (i = 0; i < oldNode->numberOfPlayers; i++)
    {
        free(oldNode->players[i]->firstName);
        free(oldNode->players[i]->secondName);
        free(oldNode->players[i]);
    }
    free(oldNode->players);
}

int punctaj(teamNode *start)
{
    int i, punctaj = 0;
    for (i = 0; i < start->numberOfPlayers; i++)
        punctaj += start->players[i]->points;
    return punctaj;
}

float medie(teamNode *team)
{
    float medie;
    medie = (float)punctaj(team) / team->numberOfPlayers;
    return medie;
}

void deleteList(List **list)
{
    teamNode *headcopy;
    while ((*list)->head)
    {
        headcopy = (*list)->head->next;
        deleteNodeData((*list)->head);
        free((*list)->head);
        (*list)->head = headcopy;
    }
    free(*list);
    *list = NULL;
}

/*
*   Construirea vectorului de punctaje pentru folosirea in eliminarea punctajelor cele mai mici
*/

int *scoresArr(List *list, int size)
{
    int *scores, i = 0;
    teamNode *copy = list->head;
    scores = (int *)malloc(size * sizeof(int));
    while (i < size)
    {
        scores[i++] = punctaj(copy);
        copy = copy->next;
    }
    return scores;
}

/*
*   Sa gasesc cel mai mic punctaj dintr-un vector de punctaje si apoi il setez egal cu maximul
*  pentru ca la o reapelare a functiei sa nu returneze tot timpul acelasi minim.
*/

int lowestScore(int *array, int size)
{
    int min, max, i;
    max = min = array[0];
    for (i = 0; i < size; i++)
    {
        if (array[i] < min)
            min = array[i];
        else if (array[i] > max)
            max = array[i];
    }
    for (i = 0; i < size; i++)
        if (array[i] == min)
        {
            array[i] = max;
            break;
        }
    return min;
}

int maxPower(int currentNumber)
{
    int pi = 1;
    while (pi < currentNumber / 2 + 1)
        pi *= 2;
    return pi;
}

/* 
*   Eliminarea a celor mai mici punctaje astfel incat sa ramanem cu un numar n maxim
*   astfel incat n sa fie o putere a lui 2.
*/

List *eliminateLowScores(List *list)
{
    int i = 0, times, *scores, lowest, number;
    teamNode *erase, *copy = list->head;
    number = list->numberOfTeams;
    scores = scoresArr(list, number);
    times = maxPower(number);
    for (i = 0; i < number - times; i++)
    {
        lowest = lowestScore(scores, number);
        if (punctaj(list->head) == lowest)
        {
            erase = list->head;
            list->head = list->head->next;
            deleteNodeData(erase);
            free(erase);
        }
        else
        {
            for (copy = list->head; copy != NULL; copy = copy->next)
                if (punctaj(copy->next) == lowest)
                {
                    erase = copy->next;
                    copy->next = copy->next->next;
                    deleteNodeData(erase);
                    free(erase);
                    break;
                }
        }
    }
    free(scores);
    scores = NULL;
    list->numberOfTeams = times;
    return list;
}

void printList(List *list, FILE *output)
{
    teamNode *copy;
    if (!list->head)
        fprintf(output, "ERROR: List is empty");
    for (copy = list->head; copy != NULL; copy = copy->next)
        fprintf(output, "%s\n", copy->teamName);
    fflush(output);
}

FILE *openFile(const char *filename, const char *mode)
{
    FILE *file = fopen(filename, mode);
    if (!file)
    {
        printf("Fisierul %s nu a putut fi deschis!", filename);
        exit(1);
    }
    return file;
}

/*
*   Ordonarea listei descrescator in functie de punctaje, iar daca punctajele sunt egale,
* descrescator in functie de numele echipei folosinf mergesort.
*/

teamNode *merge(teamNode *leftList, teamNode *rightList) //interclasare ordonata a doua liste
{
    teamNode *result;
    if (!leftList)
        return rightList;
    if (!rightList)
        return leftList;
    if (punctaj(leftList) == punctaj(rightList))
    {
        if (strcmp(leftList->teamName, rightList->teamName) > 0)
        {
            result = leftList;
            result->next = merge(leftList->next, rightList);
        }
        else
        {
            result = rightList;
            result->next = merge(leftList, rightList->next);
        }
    }
    else if (punctaj(leftList) > punctaj(rightList))
    {
        result = leftList;
        result->next = merge(leftList->next, rightList);
    }
    else
    {
        result = rightList;
        result->next = merge(leftList, rightList->next);
    }
    return result;
}

void partition(teamNode *head, teamNode **leftList, teamNode **rightList)
{
    teamNode *fast, *slow;
    if (head == NULL || head->next == NULL)
    {
        *leftList = head;
        *rightList = NULL;
    }
    slow = head;
    fast = head->next;
    while (fast)
    {
        fast = fast->next;
        if (fast)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }
    *leftList = head;
    *rightList = slow->next;
    slow->next = NULL;
}

void mergesort(teamNode **head)
{
    teamNode *copy = *head, *left, *right;
    if (copy == NULL || copy->next == NULL)
        return;
    partition(copy, &left, &right);
    mergesort(&left);
    mergesort(&right);
    *head = merge(left, right);
}