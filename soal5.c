#include <stdio.h>
#include <string.h>

int main()
{
    FILE *novel = fopen("Novel.txt", "r");

    size_t pos = ftell(novel);
    fseek(novel, 0, SEEK_END);
    size_t len = ftell(novel);
    fseek(novel, pos, SEEK_SET);

    char text[len+1];
    fgets (text, len+1, novel);
    printf("%s\n\n", text);

    char *key = "Ifah";

    int key_len = strlen(key);
    int count = 0;

    char *where = text;

    if (key_len)
        while ((where = strstr(where, key))) {
            where += key_len;
            count++;
        }
    printf("%d\n", count);
    fclose(novel);
}
