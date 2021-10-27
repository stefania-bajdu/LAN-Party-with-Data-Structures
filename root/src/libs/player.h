#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct player
{
    char *firstName;
    char *secondName;
    int points;
} player;

typedef struct teamNode
{
    int numberOfPlayers;
    const char *teamName;
    player **players; //vector de pointeri pentru jucatorii unei echipe
    struct teamNode *next;
} teamNode;

typedef struct List
{
    int numberOfTeams;
    teamNode *head;
} List;

teamNode *makeTeamNode(FILE *, teamNode *);
player *makePlayerNode(char *, char *, int);
List *makeList(FILE *);
void deleteNodeData(teamNode *);
void deleteList(List **);
void printList(List *, FILE *);
int punctaj(teamNode *);
int *scoresArr(List *, int);
int lowestScore(int *, int);
int maxPower(int);
List *eliminateLowScores(List *);
FILE *openFile(const char *, const char *);
teamNode *merge(teamNode *, teamNode *);
void partition(teamNode *, teamNode **, teamNode **);
void mergesort(teamNode **);
char *trimWhiteSpace(char *);
float medie(teamNode *);