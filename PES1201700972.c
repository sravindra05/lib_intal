#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"intal.h"
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
    x->number=malloc(sizeof(char)*1000);
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
int ctoi(char c) {return c-'0';}
void strrev(unsigned char *str)
{
	int i;
	int j;
	unsigned char a;
	unsigned len = strlen((const char *)str);
	for (i = 0, j = len - 1; i < j; i++, j--)
	{
		a = str[i];
		str[i] = str[j];
		str[j] = a;
	}
}
char* helper_multiply(char* intal1, char* intal2) {
    int l1 = strlen(intal1);
    int l2 = strlen(intal2);
    int i, j, k = 0, c = 0;
    char *r = (char *) malloc (l1+l2+1); // add one byte for the zero terminating string
    int temp;

    strrev(intal1);
    strrev(intal2);
    for (i = 0;i <l1+l2; i++) {
        r[i] = 0 + '0';
    }

    for (i = 0; i <l1; i ++) {
        c = 0; k = i;
        for (j = 0; j < l2; j++) {
            temp = ctoi(intal1[i]) * ctoi(intal2[j]);
            temp = temp + c + ctoi(r[k]);
            c = temp /10;
            r[k] = temp%10 + '0';

            k++;
        }
        if (c!=0) {
            r[k] = c + '0';
            k++;
        }
    }

    r[k] = '\0';
    strrev(r);
    strrev(intal1);
    strrev(intal2);
    return r;
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


char* intal_add(const char* intal1, const char* intal2){
    num *n1=read_num(intal1);
    num *n2=read_num(intal2);
    int max_len=n1->len + n2->len+1;
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
    char *res= helper_multiply(n1->number,n2->number);
    return res;
}

char* intal_mod(const char* intal1, const char* intal2){
    if(intal_compare(intal1,intal2)==-1){
        char *res=malloc(sizeof(char)*strlen(intal1));
        strcpy(res,intal1);
        return res;
    }
    else if(intal_compare(intal1,intal2)==0){
        return "0";
    }
    else{
        

    }
}

int intal_max(char **arr, int n){
    char *max=malloc(sizeof(char)*1000);
    strcpy(max,"0");
    int i=0;
    int m;
    while(i<n){
        if(intal_compare(arr[i],max)==1){
            m=i;
            strcpy(max,arr[i]);
        }
        i++;
    }
    return m;
}
int intal_min(char **arr, int n){
    char *min=malloc(sizeof(char)*1000);
    int i=0;
    while(i<1000){
        min[i]='9';
        i++;
    }
    i=0;
    int m;
    while(i<n){
        if(intal_compare(arr[i],min)==-1){
            m=i;
            strcpy(min,arr[i]);
        }
        i++;
    }
    return m;
}
int intal_search(char **arr, int n, const char* key){
    int i=0;
    while(i<n){
        if(strcmp(arr[i],key)==0)
            return i;
        i++;
    }
    return -1;
}
int binsearch_helper(char **arr,int l, int r,const char* key) 
{ 
    if (r >= l) { 
        int m = l + (r - l) / 2; 
        if (strcmp(arr[m],key) == 0) 
            return m; 
  
        if (intal_compare(arr[m],key)==1) 
            return binsearch_helper(arr, l, m - 1, key); 
  
        return binsearch_helper(arr, m + 1, r, key); 
    } 
  
    
    return -1; 
} 
  
int intal_binsearch(char **arr, int n, const char* key){
    return binsearch_helper(arr,0,n-1,key);
}
char* intal_fibonacci(unsigned int n){
    char *i1=malloc(sizeof(char)*1000);
    char *i2=malloc(sizeof(char)*1000);
    char *i3=malloc(sizeof(char)*1000);
    strcpy(i1,"0");
    strcpy(i2,"1");
    if(n==0)
        return i1;
    if(n==1)
        return i2;
    int i=2;
    while(i<=n){
        //printf("hi\n");
        strcpy(i3,intal_add(i1,i2));
        strcpy(i1,i2);
        strcpy(i2,i3);
        i++;
    }
    return i3;

}
int main(){
    char a[10][100] = {	"1234512345123451234512345",
						"543215432154321543215432154321",
						"0",
						"1234512345123451234512345",
						"1234512345123451234512344",
						"12",
						"265252859812191058636308480000000",
						"265252859812191058636308480000000",
						"5432154321543215432154321",
						"3" };
    /*char **arr=malloc(sizeof(char *)*10);
    int i=0;
    while(i<10){
        arr[i]=malloc(sizeof(char)*1000);
        scanf("%s",arr[i]);
        i++;
    }*/
    printf("%s\n",intal_fibonacci(1000));
    
}