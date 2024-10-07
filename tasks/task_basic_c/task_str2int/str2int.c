#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>



int str2int(const char *str){
    int number = 0;
    int step = 1;
    for (int i=strlen(str)-2; i>=0; i--){
        switch(str[i]){
            case '0': number+=0*step; break;
            case '1': number+=1*step; break;
            case '2': number+=2*step; break;
            case '3': number+=3*step; break;
            case '4': number+=4*step; break;
            case '5': number+=5*step; break;
            case '6': number+=6*step; break;
            case '7': number+=7*step; break;
            case '8': number+=8*step; break;
            case '9': number+=9*step; break;
        }
        step*=10;
    }
    return number;
    
    return 0;
}

int main(void){
    char line[256]={0};
    fgets(line, 256, stdin);
    for (int i=0; i<strlen(line)==1; i++){
        if (isalpha(line[i])){
            printf("есть буква");
            break;
        }
    }int number = 0;
    printf ("%d\n", str2int(line));
}