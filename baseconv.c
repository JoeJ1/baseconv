#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

int power(int m, int e) {
    if(e==0) return 1;
    else if (e % 2){
        return(m*power(m,e-1));
    }else{
        int temp = power(m,e/2);
        return(temp*temp);
    }
}

unsigned numdigits(const unsigned n){ // Count the digits in a number 
    if(n<10) return 1;
    return 1 + numdigits(n/10);
}

int basetodec(char *number,int base,char *charset){
    int sum = 0;
    for(int i=strlen(number)-1; i>=0; i--){
        sum+= (int)(strchr(charset, number[i])-charset)*power(base,strlen(number)-1-i); 
    }
    return(sum);
}

// FIXME: REVERSE FINAL OUTPUT
char *dectobase(int number, int base, char *charset){
    const int len = numdigits(number);
    char *digits = malloc(len+2);
    int i = 0;
    if(number==0) return("0");
    while(number!=0){
        char c = charset[number%base];
        digits[i]=("%c",c);
        i++;
        number /= base; 
    }
    /*char temp;
    int k;
    for(i = 0,k=len-1; i<len/2;i++,k--){
        temp = digits[k];
        digits[k] = digits[i];
        digits[i] = temp;
    }*/
    char *digits_p = digits;
    return(digits_p);
}

int main(int argc, char *argv[]){
    
    char *charset = "0123456789abcdefghijklmnopqrstuvwxyz";
    int opt; 
    int lower = 0;

    while((opt = getopt(argc, argv, "hic:")) !=-1){
        switch(opt){
            case 'h':
                printf("Convert a <number> <from> one base <to> another.\n");
                printf("Usage: baseconv [options] (<number> <from> <to>)\n");
                printf("Example: baseconv \'1bfa\' 16 10\nreturns: 7612\n\n");

                printf("\t-h\t\tShows this screen.\n");
                printf("\t-c <value>\tThe character set used for conversion (default 0123456789abcdefghijklmnopqrstuvwxyz).\n");
                printf("\t-i\t\tDisables case sensitivity for character set, making all input characters lowercase.\n");
                return(0);
            case 'c':
                charset = optarg;
                break;
            case 'i':
                lower = 1;
                break;
            case '?':
                if(optopt == 'c'){
                    printf("Usage: baseconv [options] (<number> <from> <to>)\n");
                    fprintf(stderr, "Option -%c requires an argument.\n",optopt);
                }else{
                    fprintf(stderr, "Unkown option character `\\x%x.\n",optopt);
                }
                return(1);
        }
    }
    
    int args = 0;
    for(; optind < argc; optind++){
        args++;
    }
    if(args!=3){
        printf("Usage: baseconv [options] (<number> <from> <to>)\n");
        printf("try 'baseconv -h' for more info.");
        return(1);
    }
    char *number = argv[optind-3];
    if(lower) for (; *number; number++) *number = tolower(*number); // Make lowercase
    int from = atoi(argv[optind-2]);
    int to = atoi(argv[optind-1]);
    int decimal = basetodec(number,from,charset);
    char *base = dectobase(decimal,to,charset);
    printf(base);
    return(0);
}
