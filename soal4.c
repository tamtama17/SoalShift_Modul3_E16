#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{
    int inp,flag=1,arr[100],j,i,angka,pow;
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
        printf("\n%d\n", inp);
    }
}
