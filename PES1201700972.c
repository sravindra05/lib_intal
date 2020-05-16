#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"intal.h"
int ctoi(char c) {return c-'0';}

typedef struct num{
    char *number;
    int len;
}num;

num* read_num(const char *s);

num* read_num(const char *s){
    num *x=malloc(sizeof(num));
    int i = 0;
    while(s[i]!='\0'){
        i++;
    }
    x->len=i;
    x->number=malloc(sizeof(char)*i);
    strcpy(x->number,s);
    return x; 
}
char *strip(char *s){
    int j=0;
    char *n=malloc(sizeof(char)*strlen(s));
    if(s[j]!='0')
        return s;
    while(s[j]=='0'){
        j++;
    }
    if(j==strlen(s)){
        return "0";
    }
    //printf("Non zero element found at %d\n",j);
    int ind = 0;
    while(s[j]!='\0'){
        n[ind]=s[j];
        j++;
        ind++;
    }
    return n;
}
char* intal_add(const char* intal1, const char* intal2){
    num *n1=read_num(intal1);
    num *n2=read_num(intal2);
    int max_len=n1->len + n2->len;
    char *sum=malloc(sizeof(char)*max_len);
    if(n2->len>n1->len){
        num *t=n2;
        n2=n1;
        n1=t;
    }
    int j=n2->len + n1->len;
    int d=n1->len - n2->len;
    sum[j]='\0';
    j--;
    int carry=0;
    int s=0;
    for(int i = n2->len -1;i>=0;i--){
        if(!carry){
            s =ctoi(n1->number[d+i])+ctoi(n2->number[i]);
            if(s>=10){
                carry=1;
                s=s%10;
            }
            else{
                carry=0;
            }
            
            sum[j]=s+'0';
            j--;
        }
        else{
            s = ctoi(n1->number[d+i])+ctoi(n2->number[i])+carry;
            if(s>=10){
                carry=1;
                s=s%10;
            }
            else{
                carry=0;
            }
            sum[j]=s+'0';
            j--;
        }

    }
    int i= d-1;
    while(i>=0){
        if(!carry){
            sum[j]=n1->number[i];
            j--;
        }
        else{
            s = ctoi(n1->number[i])+carry;
            if(s>=10){
                carry=1;
                s%=10;
                
            }
            else{
                carry=0;
            }
            sum[j]=s+'0';
            j--;

        }
        i--;
    }
    while(j>=0){
        if(carry){
            sum[j]='1';
            carry=0;
            j--;
            continue;
        }
        sum[j]='0';
        j--;
    }
    return strip(sum);
}
char* helper_add(char* intal1, char* intal2){
    num *n1=read_num(intal1);
    num *n2=read_num(intal2);
    int max_len=n1->len + n2->len;
    char *sum=malloc(sizeof(char)*max_len);
    if(n2->len>n1->len){
        num *t=n2;
        n2=n1;
        n1=t;
    }
    int j=n2->len + n1->len;
    int d=n1->len - n2->len;
    sum[j]='\0';
    j--;
    int carry=0;
    int s=0;
    for(int i = n2->len -1;i>=0;i--){
        if(!carry){
            s =ctoi(n1->number[d+i])+ctoi(n2->number[i]);
            if(s>=10){
                carry=1;
                s=s%10;
            }
            else{
                carry=0;
            }
            
            sum[j]=s+'0';
            j--;
        }
        else{
            s = ctoi(n1->number[d+i])+ctoi(n2->number[i])+carry;
            if(s>=10){
                carry=1;
                s=s%10;
            }
            else{
                carry=0;
            }
            sum[j]=s+'0';
            j--;
        }

    }
    int i= d-1;
    while(i>=0){
        if(!carry){
            sum[j]=n1->number[i];
            j--;
        }
        else{
            s = ctoi(n1->number[i])+carry;
            if(s>=10){
                carry=1;
                s%=10;
                
            }
            else{
                carry=0;
            }
            sum[j]=s+'0';
            j--;

        }
        i--;
    }
    while(j>=0){
        if(carry){
            sum[j]='1';
            carry=0;
            j--;
            continue;
        }
        sum[j]='0';
        j--;
    }
    return strip(sum);
}
int intal_compare(const char* intal1, const char* intal2){
    num *n1=read_num(intal1);
    num *n2=read_num(intal2);
    if(n1->len>n2->len){
        return 1;
    }
    if(n1->len<n2->len){
        return -1;
    }
    else{
        for(int i=0;i<n1->len;i++){
            if(ctoi(n2->number[i])>ctoi(n1->number[i])){
                return -1;
            }
            if(ctoi(n2->number[i])<ctoi(n1->number[i])){
                return 1;
            }
        
        }
        return 0;
    }
}
char* intal_diff(const char* intal1, const char* intal2){
    num *n1,*n2;
    if(intal_compare(intal1,intal2)==1){
        n1=read_num(intal1);
        n2=read_num(intal2);
       
    }
    else if(intal_compare(intal1,intal2)==-1){
        n1=read_num(intal2);
        n2=read_num(intal1);
    }
    else{
        return "0";
    }
     char *diff=malloc(sizeof(char)*(n1->len+1));
     
        int j=n1->len;
        diff[j]='\0';
        
        j--;
        int i=n2->len-1;
        int b;
        int d=n1->len - n2->len;
        while(i>=0){
            if(ctoi(n1->number[d+i])>=ctoi(n2->number[i])){
            
                diff[j]=(ctoi(n1->number[d+i])-ctoi(n2->number[i]))+'0';
                j--;
            }
            else{
                //printf("Hi %d\n",i);
                diff[j]=(10+ctoi(n1->number[d+i])-ctoi(n2->number[i]))+'0';
                b=d+i-1;
                while(n1->number[b]=='0'){
                    
                    b--;
                }
                n1->number[b]=ctoi(n1->number[b])-1+'0';
                b++;
                while(b<d+i){
                    n1->number[b]='9';
                    b++;
                }
                //printf("%s\n",n1->number);
                j--;
            }
            i--;
        }
        i=d-1;
        while(i>=0){
            diff[j]=n1->number[i];
            
            j--;
            i--;
        }
        return strip(diff);
}
char* intal_multiply(const char* intal1, const char* intal2){
    num *n1,*n2;
    if(intal_compare(intal1,intal2)==1){
        n2=read_num(intal1);
        n1=read_num(intal2);
       
    }
    else{
        n2=read_num(intal2);
        n1=read_num(intal1);
    }
    char *c;
    char *res=malloc(sizeof(char)*(n1->len+n2->len+1));
    strcpy(res,"0");
    while(strcmp(n1->number,"0")!=0){
        strcpy(res,helper_add(res,n2->number));
        c=intal_diff(n1->number,"1");
        //printf("%s\n",c);
        strcpy(n1->number,c);
    }
    return res;
}
int main(){
    printf("%s\n",intal_multiply("999","9999"));
    
}