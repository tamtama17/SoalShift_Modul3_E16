#include <stdio.h>
#include <string.h>

FILE *fp;

int main(int argc, char** argv)
{
    fp = fopen("Novel.txt", "r");
    int i;

    size_t pos = ftell(fp);
    fseek(fp, 0, SEEK_END);
    size_t len = ftell(fp);
    fseek(fp, pos, SEEK_SET);

    char text[len];
    fgets (text, len, fp);

    for(i=1;i<argc;i++){
        char *key = argv[i];

        int key_len = strlen(key);
        int count = 0;

        char *where = text;
        if (key_len)
            while ((where = strstr(where, key))) {
                where += key_len;
                count++;
            }
        printf("%s : %d\n", key, count);
    }
    fclose(fp);
}
