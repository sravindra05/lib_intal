#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int ctoi(char c) {

    return c-'0';

}
char *strip(char *s){
    int j=0;
    char *n=malloc(sizeof(char)*strlen(s));
    if(s[j]!='0')
        return s;
    while(s[j]=='0'){
        j++;
    }
    printf("Non zero element found at %d\n",j);
    if(j==strlen(s)){
        return "0";
    }
    int ind = 0;
    while(s[j]!='\0'){
        n[ind]=s[j];
        j++;
        ind++;
    }
    return s;
}
int main(){
    printf("%s\n",strip("00"));
}