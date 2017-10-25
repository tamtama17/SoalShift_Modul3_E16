#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>

char name[2][101];
char test[2][16];
int hole[2][16];
int count[2];
int point[2];
int turn, winner;
pthread_t tid[2];

void printPoint () {
    printf ("Score\n");
    printf ("%s: %d\n", name[0], point[0]);
    printf ("%s: %d\n", name[1], point[1]);
    printf ("\n");
}

void printHole (int p) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++)
            printf ("%d ", hole[p][4*i+j]);
        printf ("\n");
    }
    printf ("\n");
}

void printGuess (int p) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++)
            printf ("%c ", test[p][4*i+j]);
        printf ("\n");
    }
    printf ("\n");
}

void info1 (int p) {
    system ("clear");
    printPoint ();
    printHole (p);
    printf ("%s Turn!\n", name[p]);
    printf ("Enter 1-4 numbers. (Enter '0') to stop.\n");
    printf ("> ");
}

void info2 (int p) {
    system ("clear");
    printPoint ();
    printGuess ((p+1) % 2);
    printf ("%s Turn!\n", name[p]);
    printf ("Guess 4 numbers.\n");
    printf ("> ");
}

int plantMine (int p, int opp) {
    if (winner)
        return winner;

    int h;

    for (int i = 0; i < 4; i++) {
        info1 (p);
        scanf ("%d", &h);

        if (--h == -1) {
            if (i > 0)
                break;
            else {
                i--;
                break;
            }
        }

        if (hole[p][h] != 0) {
            printf ("Lubang sudah diisi!\n");
            i--;
            continue;
        }

        hole[p][h] = 1;
        count[p]++;

        if (i < 3 && count[p] == 16)
            return (winner = opp+1);
    }

    info1 (p);
    sleep (1);
    printf ("\n");
    turn = opp;
    return 0;
}

int guessMine (int p, int opp) {
    if (winner)
        return winner;

    int h;

    for (int i = 0; i < 4; i++) {
        info2 (p);
        scanf ("%d", &h);
        h--;

        if (test[opp][h] != '?') {
            printf ("Lubang sudah pernah dicoba!\n");
            i--;
            continue;
        }

        if (hole[opp][h] == 0) {
            test[opp][h] = 'O';
            point[p]++;
            if (point[p] == 10)
                return (winner = p+1);
        }
        else if (hole[opp][h] == 1) {
            test[opp][h] = 'X';
            point[opp]++;
            if (point[opp] == 10)
                return (winner = opp+1);
        }
    }

    info2 (p);
    sleep (1);
    printf ("\n");
    return 0;
}

void *player1 () {
    int p = 0;
    int opp = (p + 1) % 2;
    int winner;

    while (1) {
        if (plantMine (p, opp))
            break;
        while (turn == opp);
        if (guessMine (p, opp))
            break;
    }

    turn = opp;
}

void *player2 () {
    int p = 1;
    int opp = (p + 1) % 2;
    int winner;

    while (1) {
        while (turn == opp);
        if (guessMine (p, opp))
            break;
        if (plantMine (p, opp))
            break;
    }

    turn = opp;
}

int main (int argc, char **argv) {
    printf ("Player 1 Name: ");
    scanf ("%s", name[0]);

    printf ("Player 2 Name: ");
    scanf ("%s", name[1]);

    for (int i = 0; i < 16; i++)
        test[0][i] = test[1][i] = '?';

    if (pthread_create (&tid[0], NULL, &player1, NULL))
        return 0;
    if (pthread_create (&tid[1], NULL, &player2, NULL))
        return 0;

    for (int i = 0; i < 2; i++)
        pthread_join (tid[i], NULL);

    system ("clear");
    printf ("%s wins.\n", name[winner-1]);
    return 0;
}
