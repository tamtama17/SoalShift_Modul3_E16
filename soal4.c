#include <stdio.h>
#include <string.h>
#include <pthread.h>

void *faktorial(void *arg)
{
    int bil = (int *) arg;
    int hasil=1,i;
    for(i=1;i<=bil;i++){
        hasil *= i;
    }
    printf("Hasil %d! = %d\n", bil, hasil);
}

int main(int argc, char** argv)
{
    int inp,j,i,angka,pow;
    pthread_t tid[argc];
    for(j=1;j<argc;j++) {
        i=0;
        int len=strlen(argv[j]);
        inp=0;
        while(len>1) {
            pow=10;
            angka=argv[j][i];
            len--; i++;
            for(int a=1;a<len;a++) pow *= 10;
            angka = (angka-48)*pow;
            inp += angka;
        }
        inp += argv[j][strlen(argv[j])-1]-48;
        pthread_create(&(tid[j]), NULL, &faktorial, (void*)inp);
    }

    for(i=0;i<argc;i++)
        pthread_join(tid[i], NULL);
}
