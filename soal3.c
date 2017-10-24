#include <stdio.h>
#include <pthread.h>
#define MAX 100

int statl=MAX, statk=MAX;

void *lohan()
{
    while(1){
        sleep(10);
        statl -= 15;
    }
}

void *kepiting()
{
    while(1){
        sleep(20);
        statk -= 10;
    }
}

int main()
{
    pthread_t tlohan, tkepiting;
    pthread_create(&tlohan, NULL, lohan, NULL);
    pthread_create(&tkepiting, NULL, kepiting, NULL);
    int inp;
    while(1){
        printf("STATUS HEWAN\nLohan\t : %d\nKepiting : %d\n\n", statl, statk);
        printf("1. Update status hewan\n2. Beri makan Lohan\n3. Beri makan Kepiting\nInput : ");
        scanf("%d", &inp);
        if(inp == 2) statl +=10;
        else if(inp == 3) statk +=10;
        else if(inp == 1){}
        else{
            printf("Input salah\n");
            sleep(3);
        }

        if(statl>MAX||statk>MAX||statl<=0||statk<=0){
            printf("Hewan Anda mati :(\n");
            return 0;
        }

        system("clear");
    }
}
