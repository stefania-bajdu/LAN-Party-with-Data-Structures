@student Bajdu Stefania

Tema bonus: lanParty 

Cerinta 1:
Structurile sunt predefinite astfel incat jucatorii unei echipe sunt stocati intr-un vector de pointeri iar o echipa este caracterizata de numarul de jucatori, nume si acest vector. Se formeaza o lista cu astfel de echipe. Functia makePlayerNode() creeaza un element din vectorul de jucatori, iar makeTeamNode() creeaza un nod in lista de echipe.
Structura List reprezinta lista cu informatiile din fisierul d.in, contine numarul total de echipe si pointer catre capul listei de echipe.
Functia trimWhiteSpace() sterge spatiile de la inceputul numelui echipei.  

Cerinta 2:
Pentru calculul lui n maxim unde n este o putere a lui 2 se foloseste functia maxPower(). Functia scoresArr() construieste un vector cu toate punctajele totale ale echipelor. Functia lowestScore() returneaza punctajul minim gasit in vectorul de punctaje, iar apoi il inlocuieste cu punctajul maxim pentru ca la o reapelare a functiei sa nu fie returnat tot timpul acelasi punctaj minim. Astfel se returneaza urmatorul punctaj minim din lista de echipe. Pentru fiecare punctaj minim returnat in functia eliminateLowScores() se sterge din lista echipa cu punctajul corespunzator, incat la final ramanem cu 2^n echipe. 

Cerinta 3:
Functia copyData() primeste ca parametru un nod de echipa sursa si va returna un nou nod cu aceleasi date, pentru ca apoi sa eliberam memoria asociata nodului sursa care se afla in stiva sau in coada. Am predefinit aceasta structura pentru ca atunci cand este scos un nod din stiva sa i pot elibera memoria inainte sa modific capul stivei, dar datele returnate sa fie nemodificate.
Pentru determinarea echipei castigatoare am predefinit functia deWinner() in care se modifica si punctajele jucatorilor, iar pentru echipa pierzatoare- deLoser(). Aceste functii nu elibereaza si memoria asociata nodului de meci din queue, eliberarea se face folosind functia de().  
Functia makeQueue() populeaza coada cu elemente din lista primita ca parametru.
Cat timp exista meciuri care se pot juca scot echipele castigatoare din queue si le adaug in stiva castigatorilor apoi repopulam coada cu elemente din stiva castigatorilor folosind fuctia remakeQueue().
Pentru construirea clasamentului din stiva castigatorilor cand aceasta contine 8 echipe se foloseste functia createClasament().

Cerinta 4:
Pentru construirea arborelui binar de cautare folosind clasamentul celor 8 echipe returnat de cerinta 3, inseram pe rand in locul potrivit cate o echipa, reconstituind la fiecare pas proprietatea de bst la stanga si la dreapta.

Cerinta 5:
Folosind acelasi clasament returnat de cerinta 3 inseram pe rand astfel incat sa construim un arbore echilibrat. Refacem proprietatea de avl folosindu-ne de factorul de echilibru returnat de functia balanceFactor() care va indica gradul de echilibru al nodului primit ca parametru. Daca acest factor este mai mare decat 1, arborele nu este echilibrat in stanga, iar daca vrem sa inseram o echipa cu o medie mai mica decat a radacinii curente, tot la stanga folosim functia rightRotation() pentru a roti la dreapta. Daca nodul inserat are o medie mai mare decat a radacinii rotim dreapta-stanga folosinf RLRotation(). Analog daca factorul este mai mic decat -1 se folosesc functiile leftRotation(), LRRotation() in functie de pozitia mediei nodului ce trebuie inserat fata de radacina.
