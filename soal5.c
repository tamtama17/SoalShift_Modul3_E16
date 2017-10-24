#include <stdio.h>
#include <string.h>
#include <pthread.h>

FILE *fp;

void *cari(void* arg)
{
    fp = fopen("Novel.txt", "r");

    size_t pos = ftell(fp);
    fseek(fp, 0, SEEK_END);
    size_t len = ftell(fp);
    fseek(fp, pos, SEEK_SET);

    char text[len+1];
    fgets (text, len+1, fp);
    
    char *key = (char *)arg;
    int key_len = strlen(key);
    int count = 0;

    char *where = text;
    if (key_len)
        while ((where = strstr(where, key))) {
            where += key_len;
            count++;
        }
    printf("%s : %d\n", key, count);
    fclose(fp);
}

int main(int argc, char** argv)
{
    int i;
    pthread_t tid[argc-1];

    for(i=1;i<argc;i++){
        pthread_create(&(tid[i-1]), NULL, &cari, (void*)argv[i]);
        pthread_join(tid[i-1], NULL);
    }
}
