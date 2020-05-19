#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "intal.h"

int max_int(char* intal1,char* intal2)
{
    int l1 = strlen(intal1);
    int l2 = strlen(intal2);

    if(l1==l2)
        return 0;
    else
    {
        if(l1>l2)
            return 1;
        else
            return 2;
    }
}

char* read_intal(const char* intal)
{
    char *s=malloc(sizeof(char)*strlen(intal));
    strcpy(s,intal);
    return s;
}

char* pad_int(char* intal,int len)
{
    int diff = len-strlen(intal);
    char* ret = (char*)malloc(sizeof(char)*len);
    for(int i=0;i<diff;i++)
    {
        ret[i]='0';
    }
    for(int i=0;i<strlen(intal);i++)
    {
        ret[i+diff] = intal[i];
    }
    // intal = (char*)realloc(intal,sizeof(char)*len);
    // strcpy(intal,ret);
    return ret;
}

int match_len(char** intal1,char** intal2)
{
    int m = max_int(*intal1,*intal2);
    char* res;
    // printf("be\n");
    if(m!=0)
    {
        // printf("gah\n");
        if(m==1)
        {
            // printf("1\n");
            res = pad_int(*intal2,strlen(*intal1));
            *intal2 = (char*)malloc(sizeof(char)*strlen(*intal1));
            strcpy(*intal2,res);
        }
        else
        {
            // printf("2\n");
            res = pad_int(*intal1,strlen(*intal2));
            *intal1 = (char*)malloc(sizeof(char)*strlen(*intal2));
            strcpy(*intal1,res);
        }
        // printf("done\n");
    }
    // printf("la\n");
    return(strlen(*intal1));
}

int ctoi(char c)
{
    return(c-'0');
}

char itoc(int i)
{
    return(i+'0');
}

char* intal_add(const char* intal1, const char* intal2)
{
    // printf("here\n");
    char* res;
    int carry=0;
    int sum;
    char c;
    char* i1=malloc(sizeof(char)*(strlen(intal1)+1));
    char* i2=malloc(sizeof(char)*(strlen(intal2)+1));

    strcpy(i1,intal1);
    strcpy(i2,intal2);

    int n1 = strlen(intal1);
    int n2 = strlen(intal2);

    // printf("%s,%s\n",i1,i2);

    int l = match_len(&i1,&i2);

    // printf("lala\n");

    res = (char*)malloc(sizeof(char)*(n1+n2+1));

    for(int i=l-1;i>=0;i--)
    {
        sum = ctoi(i1[i])+ctoi(i2[i])+carry;
        carry = sum/10;
        res[i] = itoc(sum%10);
    }
    // printf("DD: %s\n",res);
    if(carry!=0)
    {
        c = itoc(carry);
        int l=strlen(res);
        char* new_res=malloc(sizeof(char)*(n1+n2+10));
        new_res[0]=c;
        // printf("PP: %s\n",res);
        // printf("all %s\n",res);
        // printf("len: %d\n",strlen(res));
        for(int i=0;i<l;i++)
        {
            // printf("%d\n",i);
            new_res[i+1]=res[i];
            // printf("%d: %s\n",i,new_res);
        }
        // // strcat(new_res,res);
        // printf("kkk\n");
        // printf("%s\t%s\t%s\n",intal1,intal2,new_res);
        free(i1);
        free(i2);
        free(res);
        return(new_res);
    }
    // printf("%s\t%s\t%s\n",intal1,intal2,res);
    free(i1);
    free(i2);
    // printf("%p\t",res);
    return(res);
}

int intal_compare(const char* intal1,const char* intal2)
{
    char* i1=malloc(sizeof(char)*strlen(intal1));
    char* i2=malloc(sizeof(char)*strlen(intal2));

    strcpy(i1,intal1);
    strcpy(i2,intal2);

    int m = max_int(i1,i2);
    // if(m==1)
    //     return 1;
    // else if(m==2)
    //     return -1;
    // else
    // {
        // int l = strlen(intal1);

    int l = match_len(&i1,&i2);
    int i=0;
    while(i<l)
    {
        if(i1[i]>i2[i])
            return 1;
        else if(i2[i]>i1[i])
            return -1;
        i++;
    }
    return 0;
    // }
}

char* intal_diff(const char* intal1,const char*intal2)
{
    
    int comp = intal_compare(intal1,intal2);

    char* i1=malloc(sizeof(char)*strlen(intal1));
    char* i2=malloc(sizeof(char)*strlen(intal2));

    strcpy(i1,intal1);
    strcpy(i2,intal2);

    int l = match_len(&i1,&i2);
    char* n1=malloc(sizeof(char)*l);
    char* n2=malloc(sizeof(char)*l);
    char* res = (char*)malloc(sizeof(char)*l);
    int borrow;

    // printf("%s,%s,%d\n",intal1,intal2,comp);

    if(comp==1)
    {
        strcpy(n1,i1);
        // n1 = intal1;
        strcpy(n2,i2);
        // n2 = intal2;
    }
    else if(comp==-1)
    {
        strcpy(n1,i2);
        // n1 = intal2;
        strcpy(n2,i1);
        // n2 = intal1;
    }
    else
        return "0";
    // printf("%s,%s\n",n1,n2);
    
    for(int i=l-1;i>=0;i--)
    {
        
        if(ctoi(n1[i])<ctoi(n2[i]))
        {
            // printf("^^^%c,%c\n",n1[i],n2[i]);

            int j=1;
            while(n1[i-j]=='0')
            {
                // printf("&&&%d,%d,%c\n",i,j,n1[i-j]);
                n1[i-j]='9';
                // printf("&&&%d,%d,%c\n",i,j,n1[i-j]);
                j++;
            }
            n1[i-j] = itoc(ctoi(n1[i-j])-1);

            // n1[i-1] = itoc(ctoi(n1[i-1])-1);
            borrow=10+ctoi(n1[i]);  
        }
        else
            borrow = ctoi(n1[i]);
        // printf("%d,%s\n",borrow,n1);
        res[i]=itoc(borrow-ctoi(n2[i]));
    }
    // printf("lala\n");
    int i=0;
    int count=0;
    while(i<l)
    {
        if(res[i]=='0')
            count++;
        else
            break;
        i++;
    }
    // printf("%d\n",count);
    if(count!=0)
    {
        char* new_res=(char*)malloc(sizeof(char)*(l-count));
        for(int j=0;j<(l-count);j++)
        {
            new_res[j]=res[j+count];
        }
        // printf("%s\n",new_res);
        return(new_res);
    }
    // printf("res: %s\n",res);
    return(res);
}

char* itoa(int n)
{
    int len=0;
    int p=n;
    while(n>0){
        len++;
        n = n/10;
    }

    char *res = (char*)malloc(sizeof(char)*len);
    for(int i=len-1;i>=0;i--)
    {
        res[i]=itoc(p%10);
        p=p/10;
    }
    return(res);
}

// char* mul(char* n1,char n2,int unit)
// {
//     int carry=0;
//     int prod;
//     int mul = ctoi(n2);
//     // int trailing_zeros=unit/10;
//     char* res=(char*)malloc(sizeof(char)*(strlen(n1)+unit));
//     // printf("%lu,%lu,%d\n",strlen(n1),strlen(res),unit);
//     for(int i=strlen(n1);i<strlen(n1)+unit;i++)
//     {
//         res[i]='0';
//         // printf("here\n");
//     }

//     if(n2=='0')
//         return "0";

//     for(int i=strlen(n1)-1;i>=0;i--)
//     {
//         prod = ctoi(n1[i])*mul;
//         prod = prod+carry;
//         res[i] = itoc(prod%10);
//         carry = prod/10;
//         // printf("%c,%d,%c,%d\n",n1[i],mul,res[i],carry);
//     }
//     if(carry>0)
//     {
//         char* new_res = (char*)malloc(sizeof(char)*(strlen(res)+1));
//         new_res[0] = itoc(carry);
//         strcat(new_res,res);
//         return new_res;
//     }
//     printf("re:%s\n",res);
//     return res;
// }

char* intal_multiply(const char* intal1, const char* intal2)
{
    int res=0;
    // char* temp=malloc(sizeof(char)*(strlen(intal1)+strlen(intal2)));
    char* temp;
    int m = intal_compare(intal1,intal2);
    // char* n1;
    // char* n2;
    // char* prod;

    // if(m==1)
    // {
    //     n1 = malloc(sizeof(char)*strlen(intal1));
    //     n2 = malloc(sizeof(char)*strlen(intal2));
    //     strcpy(n1,intal1);
    //     strcpy(n2,intal2);
    // }
    // else
    // {
    //     n1 = malloc(sizeof(char)*strlen(intal2));
    //     n2 = malloc(sizeof(char)*strlen(intal1));
    //     strcpy(n1,intal2);
    //     strcpy(n2,intal1);
    // }

    // strcpy(temp,n1);

    if(!strcmp(intal1,"0") || !strcmp(intal2,"0"))
    {
        return "0";
    }

    temp=(char*)malloc(sizeof(char)*(strlen(intal1)+strlen(intal2)+1));

    // char *mul=(char*)malloc(sizeof(char))

    if(m==1)
    {
        
        strcpy(temp,intal1);
        char* d=malloc(sizeof(char)*1);
        d[0]='1';
        char* n2 = malloc(sizeof(char)*strlen(intal2));
        // n2="1";
        char* res=(char*)malloc(sizeof(char)*(strlen(intal1)+strlen(intal2)+10));
        strcpy(n2,intal2);
        while(strcmp(n2,"1")!=0)
        {
            // printf("tb: %s, %s\n",temp,intal1);
            strcpy(res,intal_add(temp,intal1));
            temp=(char*)malloc(sizeof(char)*(strlen(intal1)+strlen(intal2)+1));
            strcpy(temp,res);
            // printf("ta: %s\n",temp);
            // printf("nb: %s\n",n2);
            // n2 = intal_add(n2,d);
            strcpy(n2,intal_diff(n2,"1"));
            // printf("na: %s\n",n2);
            // printf("tt: %s\n\n",temp);

        }
    }
    else
    {
        strcpy(temp,intal2);
        char* d=malloc(sizeof(char)*1);
        d[0]='1';
        char* n2 = malloc(sizeof(char)*strlen(intal1));
        // n2="1";
        strcpy(n2,intal2);
        while(strcmp(n2,"1")!=0)
        {
            // printf("tb: %s\n",temp);
            strcpy(temp,intal_add(temp,intal2));
            // printf("ta: %s\n",temp);
            // printf("nb: %s\n",n2);
            // n2 = intal_add(n2,d);
            strcpy(n2,intal_diff(n2,"1"));
            // printf("na: %s\n",n2);
            // printf("tt: %s\n\n",temp);

        }
    }
    return(temp);
}

    
//     // while(strcmp(n2,"1")!=0)
//     // {
//     //     printf("tb: %s\n",temp);
//     //     temp = intal_add(temp,n1);
//     //     printf("ta: %s\n",temp);
//     //     // printf("nb: %s\n",n2);
//     //     n2 = intal_diff(n2,"1");
//     //     // printf("na: %s\n",n2);
//     //     printf("tt: %s\n\n",temp);

//     // }
//     // printf("m: %s\t",temp);
//     return(temp);
// }

// char* intal_multiply(char* intal1,char* intal2)
// {
//     int l1 = strlen(intal1);
//     int l2 = strlen(intal2);

//     if(l1==0 || l2==0)
//         return "0";
    
//     int res[l1+l2];

//     int i_n1=0;
//     int i_n2=0;

//     for(int i=l1-1;i>=0;i--)
//     {
//         int carry=0;
//         int n1=ctoi(intal1[i]);

//         i_n2=0;

//         for(int j=l2-1;j>=0;j--)
//         {
//             int n2 = ctoi(intal2[j]);
//             // printf("%d\n",j);

//             int sum = n1*n2 + res[i_n1+i_n2];

//             carry = sum/10;
//             res[i_n1+i_n2] = sum%10;

//             i_n2++;
//         }

//         if(carry>0)
//         {
//             res[i_n1+i_n2] += carry; 
//         }
//         i_n1++;
//     }

//     int i=l1+l2-1;
//     while(i>=0 && res[i]==0)
//     {
//         i--;
//     }

//     if(i==-1)
//         return "0";
    
//     char* s=malloc(sizeof(char)*(sizeof(res)/sizeof(int)));
//     int j=0;
//     while(i>=0)
//     {
//         s[j]=itoc(res[i--]);
//         j++;
//     }
//     // printf("%s\n",s);
//     for(int i=0;i<sizeof(res)/sizeof(int);i++)
//     {
//         printf("%d",res[i]);
//     }
//     printf("\n");
//     return(s);
// }

// char* strrev(char *str){
//     char c, *front, *back;

//     if(!str || !*str)
//         return str;
//     for(front=str,back=str+strlen(str)-1;front < back;front++,back--){
//         c=*front;*front=*back;*back=c;
//     }
//     return str;
// }

// char* intal_multiply(const char* intal1, const char* intal2) {
//     int l1 = strlen(intal1);
//     int l2 = strlen(intal2);
//     int i, j, k = 0, c = 0;
//     char *r = (char *) malloc (l1+l2+1); // add one byte for the zero terminating string
//     int temp;

//     char* i1=malloc(sizeof(char)*strlen(intal1));

//     // strcpy(i1,intal1);
//     for(int i=0;i<strlen(intal1);i++)
//     {
//         i1[i]=intal1[i];
//     }
//     i1[strlen(intal1)]='\0';
//     // strcpy(i1,read_intal(intal1));
//     printf("%s\t%s\n",i1,intal1);
//     // i1[strlen(i1)]='\0';

//     char* i2=malloc(sizeof(char)*strlen(intal2));

//     // strcpy(i2,intal2);

//     for(int i=0;i<strlen(intal2);i++)
//     {
//         i2[i]=intal2[i];
//     }
//     i2[strlen(intal2)]='\0';
//     printf("%s\t%s\n",i2,intal2);

//     strrev(i1);
//     printf("%s\n",i1);
//     strrev(i2);

//     // for (i = 0;i <l1+l2; i++) {
//     //     r[i] = 0 + '0';
//     // }

//     for (i = 0; i <l1; i ++) {
//         c = 0; k = i;
//         for (j = 0; j < l2; j++) {
//             temp = ctoi(intal1[i]) * ctoi(intal2[j]);
//             temp = temp + c + ctoi(r[k]);
//             c = temp /10;
//             r[k] = temp%10 + '0';

//             k++;
//         }
//         if (c!=0) {
//             r[k] = c + '0';
//             k++;
//         }
//     }

//     r[k] = '\0';
//     strrev(r);
//     // strrev(intal1);
//     // strrev(intal2);
//     return r;
// }


// char* intal_mod(char* intal1, char* intal2)
// {
//     char* n1;
//     char* n2;

//     int m=intal_compare(intal1,intal2);
//     if(m==1)
//     {
//         n1=intal1;
//         n2=intal2;
//     }
//     else if(m==-1)
//     {
//         // printf("noop\n");
//         return(intal1);
//     }
//     else
//         return("0");

//     while(intal_compare(n1,n2)>=0){
//         // printf("%s,%s\n",n1,n2);
//         n1 = intal_diff(n1,n2);
//         // printf("%s\n",n1);
//     }
//     printf("done.\n");
//     return(n1);
// }

char* intal_mod(const char* intal1, const char* intal2)
{
    int m = intal_compare(intal1,intal2);
    // printf("done\n");

    // char* i1=malloc(sizeof(char)*strlen(intal1));

    if(m==0)
        return 0;
    else if(m==-1)
        return(intal1);
    
    char *s = malloc(sizeof(char)*strlen(intal1));
    strncpy(s,intal1,strlen(intal2));
    // printf("S: %s\n",s);
    int i=strlen(intal2)-1;
    while(i<strlen(intal1))
    {
        // printf("%d\n",i);
        while(intal_compare(s,intal2)<0)
        {
            if(i<strlen(intal1)-1)
            {
                i++;
                // printf("$$%s\n",s);
                s[strlen(s)]=intal1[i];
                s[strlen(s)]='\0';
                // printf("%s\t%c\n",s,intal1[i]);
            }
            else
            {
                char *res=malloc(sizeof(char)*strlen(s));
                int j=0;
                while(j<strlen(s))
                    if(s[j]=='0')
                        j++;
                    else
                        break;
                    
                if(j==strlen(s))
                    return("0");
                else
                {
                    int k=0;
                    while(j<strlen(s))
                    {
                        res[k]=s[j];
                        k++;
                        j++;
                    }
                }
                return(res);
            } 
        }

        while(intal_compare(s,intal2)>=0)
        {
            strcpy(s,intal_diff(s,intal2));
        }
    }
    return("");
}

char* intal_pow(const char* intal1, unsigned int intal2)
{
    if(intal2==0)
        return("1");
    else if(!strcmp(intal1,"0"))
        return("0");
    else if(!strcmp(intal1,"1"))
        return("1");
    else if(intal2==1)
    {
        // printf("here\n");
        return(intal1);
    }
    else
    {
        char* prod = malloc(sizeof(char)*(strlen(intal1)*intal2+1));
        strcpy(prod,intal1);

        unsigned int temp=intal2;
        // printf("%d\n",temp);
        // printf("%s,%s,%d\n",prod,intal2,strcmp(intal2,"0"));

        while(temp>1)
        {
            // printf("%s,%s\n",prod,intal1);
            // printf("%d,%s,%s\n",temp,prod,intal1);
            strcpy(prod,intal_multiply(prod,intal1));
            // printf("%s\n",prod);
            temp--;
            // if(temp>950)
            //     printf("%d\t",temp);
            // intal2 = intal_diff(intal2,"1");
        }
        return(prod);
    }
}

char* gcd(const char* intal1, const char* intal2)
{
    if(strcmp(intal1,"0")==0)
        return(intal2);
    // printf("%s\t%s\n",intal1,intal2);
    return(gcd(intal_mod(intal2,intal1),intal1));
}

char* intal_gcd(const char* intal1, const char* intal2)
{
    if(strcmp(intal1,"0")==0 && strcmp(intal2,"0")==0)
        return "0";
    
    int m = intal_compare(intal1,intal2);

    if(m==0)
        return(intal1);
    if(m==1)
    {
        // char* temp=malloc(sizeof(char)*strlen(intal2));
        // strcpy(temp,intal2);

        // while(strcmp(temp,"1")!=0)
        // {
        //     if(strcmp(intal_mod(intal2,temp),"0")==0 && strcmp(intal_mod(intal1,temp),"0")==0)
        //         return(temp);
        //     // printf("ta:%s\n",temp);
        //     strcpy(temp,intal_diff(temp,"1"));
        //     // printf("tb:%s\n\n",temp);
        // }
        // return("1");
        return(gcd(intal2,intal1));
    }
    else
    {
        // char* temp=malloc(sizeof(char)*strlen(intal1));
        // strcpy(temp,intal1);

        // while(strcmp(temp,"1")!=0)
        // {
        //     if(strcmp(intal_mod(intal1,temp),"0")==0 && strcmp(intal_mod(intal2,temp),"0")==0)
        //         return(temp);
        //     // printf("ta:%s\n",temp);
        //     strcpy(temp,intal_diff(temp,"1"));
        //     // printf("tb:%s\n\n",temp);
        // }
        // return("1");
        return(gcd(intal1,intal2));
    }
    return(gcd(intal1,intal2));
}


char* fibo(unsigned int n)
{
    // printf("here");
    if(n==0)
        return("1");
    if(n==1)
        return("1");
    printf("%d\t",n);
    int k=n/2;
    if(n%2==0)
    {
        return(intal_add(intal_multiply(fibo(k),fibo(k)),intal_multiply(fibo(k-1),fibo(k-1))));
    }
    else
    {
        return(intal_add(intal_multiply(fibo(k),fibo(k+1)),intal_multiply(fibo(k-1),fibo(k))));
    }  
}

char* intal_fibonacci(unsigned int n)
{
    char *i1=malloc(sizeof(char)*1000);
    char *i2=malloc(sizeof(char)*1000);
    char *i3=malloc(sizeof(char)*1000);
    // char *i3;
    strcpy(i1,"0");
    strcpy(i2,"1");
    if(n==0)
        return i1;
    if(n==1)
        return i2;
    int i=2;
    // printf("%d\n",i<=n);
    // char* temp;

    while(i<=n){
        // printf("inside");
        // printf("%d\t",i);
        // free(i3);
        char* temp;
        temp = intal_add(i1,i2);
        // printf("%p\t",temp);
        strcpy(i3,temp);
        free(temp);
        strcpy(i1,i2);
        strcpy(i2,i3);
        i++;
    }
    // printf("\n");
    free(i1);
	free(i2);
    return i3;
}

int main()
{
    // char* intal1=(char*)malloc(sizeof(char)*100);
    // char* intal2=(char*)malloc(sizeof(char)*100);
    // // int res;

    // strcpy(intal1,"250000000001");
    // strcpy(intal2,"2");

    char* res;
    // printf("%lu\n",strlen(intal1));
    // printf("tada:%c\n",intal1[strlen(intal1)+5]);

    // intal2 = pad_int(intal2,strlen(intal1));
    // match_len(&intal1,&intal2);
    // res = intal_add(intal1,intal2);
    // res = intal_compare(intal1,intal2);
    // res = intal_diff(intal1,intal2);
    // res = intal_multiply(intal1,intal2);
    // res = intal_mod(intal1,intal2);
    // res = mul(intal1,intal2[0],1);
    // res = intal_pow(intal1,intal2);
    // res = intal_gcd(intal2,intal1);
    res = intal_fibonacci(190);
    printf("%s\n",res);
    // res=fibo(100);
    // printf("%s\n",fibo(100));
    // printf("hello\n");
    // printf("%s\t%s\t%s\n",intal1,intal2,res);
    // free(intal1);
    // free(intal2);
    free(res);
    return 0;
}

// int main(int argc, char const *argv[]) {
// 	int n = 12;
// 	char **a = (char**) malloc(n * sizeof(char*));
// 	for(int i = 0; i < n; i++) {
// 		a[i] = (char*) malloc(1001 * sizeof(char));
// 	}
	
// 	strcpy(a[0], "1234512345123451234512345");
// 	strcpy(a[1], "543215432154321543215432154321");
// 	strcpy(a[2], "0");
// 	strcpy(a[3], "1234512345123451234512345");
// 	strcpy(a[4], "1234512345123451234512344");
// 	strcpy(a[5], "12");
// 	strcpy(a[6], "265252859812191058636308480000000");
// 	strcpy(a[7], "265252859812191058636308480000000");
// 	strcpy(a[8], "5432154321543215432154321");
// 	strcpy(a[9], "3");
// 	strcpy(a[10], "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
// 	strcpy(a[11], "1230231922161117176931558813276752514640713895736833715766118029160058800614672948775360067838593459582429649254051804908512884180898236823585082482065348331234959350355845017413023320111360666922624728239756880416434478315693675013413090757208690376793296658810662941824493488451726505303712916005346747908623702673480919353936813105736620402352744776903840477883651100322409301983488363802930540482487909763484098253940728685132044408863734754271212592471778643949486688511721051561970432780747454823776808464180697103083861812184348565522740195796682622205511845512080552010310050255801589349645928001133745474220715013683413907542779063759833876101354235184245096670042160720629411581502371248008430447184842098610320580417992206662247328722122088513643683907670360209162653670641130936997002170500675501374723998766005827579300723253474890612250135171889174899079911291512399773872178519018229989376");
// 	char *result1;
// 	int index1;

// 	result1 = intal_add(a[0], a[1]);
// 	if(!result1) {
// 		printf("Test intal_add FAILED.\n");
// 	} else {
// 		if(0 == strcmp(result1, "543216666666666666666666666666")) {
// 			printf("Test intal_add PASSED\n");
// 		} else {
// 			printf("Test intal_add FAILED.\nYour answer: %s\nExpected answer: %s\n", result1, "543216666666666666666666666666");
// 		}
// 		free(result1);
// 	}

// 	index1 = intal_compare(a[0], a[1]);
// 	if(-1 == index1) {
// 		printf("Test intal_compare PASSED\n");
// 	} else {
// 		printf("Test intal_compare FAILED.\nYour answer: %d\nExpected answer: %d\n", index1, -1);
// 	}

// 	result1 = intal_diff(a[0], a[1]);
// 	if(!result1) {
// 		printf("Test intal_diff FAILED.\n");
// 	} else {
// 		if(0 == strcmp(result1, "543214197641976419764197641976")) {
// 			printf("Test intal_diff PASSED\n");
// 		} else {
// 			printf("Test intal_diff FAILED.\nYour answer: %s\nExpected answer: %s\n", result1, "543214197641976419764197641976");
// 		}
// 		free(result1);
// 	}

// 	result1 = intal_multiply(a[8], a[5]);
//     //result1 = intal_multiply("1000000000000000","10");
//     //result1 = intal_multiply("4","2");
// 	if(!result1) {
// 		printf("Test intal_multiply FAILED.\n");
// 	} else {
// 		if(0 == strcmp(result1, "65185851858518585185851852")) {
// 			printf("Test intal_multiply PASSED\n");
// 		} else {
// 			printf("Test intal_multiply FAILED.\n.Your answer: %s\nExpected answer: %s\n", result1, "65185851858518585185851852");
// 		}
// 		free(result1);
// 	}

// 	result1 = intal_mod(a[3], a[4]);
// 	if(!result1) {
// 		printf("Test intal_mod FAILED.\n");
// 	} else {
// 		if(0 == strcmp(result1, "1")) {
// 			printf("Test intal_mod PASSED\n");
// 		} else {
// 			printf("Test intal_mod FAILED.\nYour answer: %s\nExpected answer: %s\n", result1, "1");
// 		}
// 		free(result1);
// 	}

// 	result1 = intal_mod("978", "5");
// 	if(!result1) {
// 		printf("Test intal_mod FAILED.\n");
// 	} else {
// 		if(0 == strcmp(result1, "3")) {
// 			printf("Test intal_mod PASSED\n");
// 		} else {
// 			printf("Test intal_mod FAILED.\nYour answer: %s\nExpected answer: %s\n", result1, "3");
// 		}
// 		free(result1);
// 	}

// 	result1 = intal_mod(a[0], a[5]);
// 	if(!result1) {
// 		printf("Test intal_mod FAILED.\n");
// 	} else {
// 		if(0 == strcmp(result1, "9")) {
// 			printf("Test intal_mod PASSED\n");
// 		} else {
// 			printf("Test intal_mod FAILED.\nYour answer: %s\nExpected answer: %s\n", result1, "9");
// 		}
// 		free(result1);
// 	}

// 	result1 = intal_pow(a[5], 3);
// 	if(!result1) {
// 		printf("Test intal_pow FAILED.\n");
// 	} else {
// 		if(0 == strcmp(result1, "1728")) {
// 			printf("Test intal_pow PASSED\n");
// 		} else {
// 			printf("Test intal_pow FAILED.\nYour answer: %s\nExpected answer: %s\n", result1, "1728");
// 		}
// 		free(result1);
// 	}

// 	result1 = intal_pow("10", 999);
// 	if(!result1) {
// 		printf("Test intal_pow FAILED.\n");
// 	} else {
// 		if(0 == strcmp(result1, a[10])) {
// 			printf("Test intal_pow PASSED\n");
// 		} else {
// 			printf("Test intal_pow FAILED.\nYour answer: %s\nExpected answer: %s\n", result1, a[10]);
// 		}
// 		free(result1);
// 	}

// 	result1 = intal_pow("2", 3000);
// 	if(!result1) {
// 		printf("Test intal_pow FAILED.\n");
// 	} else {
// 		if(0 == strcmp(result1, a[11])) {
// 			printf("Test intal_pow PASSED\n");
// 		} else {
// 			printf("Test intal_pow FAILED.\nYour answer: %s\nExpected answer: %s\n", result1, a[11]);
// 		}
// 		free(result1);
// 	}
//     // printf("done\n");

// 	result1 = intal_gcd(a[0], a[5]);
// 	if(!result1) {
// 		printf("Test intal_gcd FAILED.\n");
// 	} else {
// 		if(0 == strcmp(result1, "3")) {
// 			printf("Test intal_gcd PASSED\n");
// 		} else {
// 			printf("Test intal_gcd FAILED.\nYour answer: %s\nExpected answer: %s\n", result1, "3");
// 		}
// 		free(result1);
// 	}

// 	// result1 = intal_fibonacci(3);
// 	// if(!result1) {
// 	// 	printf("Test intal_fibonacci FAILED.\n");
// 	// } else {
// 	// 	if(0 == strcmp(result1, "2")) {
// 	// 		printf("Test intal_fibonacci PASSED\n");
// 	// 	} else {
// 	// 		printf("Test intal_fibonacci FAILED.\nYour answer: %s\nExpected answer: %s\n", result1, "2");
// 	// 	}
// 	// 	free(result1);
// 	// }

// 	// result1 = intal_fibonacci(1000);
// 	// if(!result1) {
// 	// 	printf("Test intal_fibonacci FAILED.\n");
// 	// } else {
// 	// 	if(0 == strcmp(result1, "43466557686937456435688527675040625802564660517371780402481729089536555417949051890403879840079255169295922593080322634775209689623239873322471161642996440906533187938298969649928516003704476137795166849228875")) {
// 	// 		printf("Test intal_fibonacci PASSED\n");
// 	// 	} else {
// 	// 		printf("Test intal_fibonacci FAILED.\nYour answer: %s\nExpected answer: %s\n", result1, "43466557686937456435688527675040625802564660517371780402481729089536555417949051890403879840079255169295922593080322634775209689623239873322471161642996440906533187938298969649928516003704476137795166849228875");
// 	// 	}
// 	// 	free(result1);
// 	// }

// 	// result1 = intal_factorial(30);
// 	// if(!result1) {
// 	// 	printf("Test intal_factorial FAILED.\n");
// 	// } else {
// 	// 	if(0 == strcmp(result1, a[6])) {
// 	// 		printf("Test intal_factorial PASSED\n");
// 	// 	} else {
// 	// 		printf("Test intal_factorial FAILED.\nYour answer: %s\nExpected answer: %s\n", result1, a[6]);
// 	// 	}
// 	// 	free(result1);
// 	// }

// 	// result1 = intal_factorial(100);
// 	// if(!result1) {
// 	// 	printf("Test intal_factorial FAILED.\n");
// 	// } else {
// 	// 	if(0 == strcmp(result1, "93326215443944152681699238856266700490715968264381621468592963895217599993229915608941463976156518286253697920827223758251185210916864000000000000000000000000")) {
// 	// 		printf("Test intal_factorial PASSED\n");
// 	// 	} else {
// 	// 		printf("Test intal_factorial FAILED.\nYour answer: %s\nExpected answer: %s\n", result1, "93326215443944152681699238856266700490715968264381621468592963895217599993229915608941463976156518286253697920827223758251185210916864000000000000000000000000");
// 	// 	}
// 	// 	free(result1);
// 	// }

// 	// result1 = intal_bincoeff(10, 8);
// 	// if(!result1) {
// 	// 	printf("Test intal_bincoeff FAILED.\n");
// 	// } else {
// 	// 	if(0 == strcmp(result1, "45")) {
// 	// 		printf("Test intal_bincoeff PASSED\n");
// 	// 	} else {
// 	// 		printf("Test intal_bincoeff FAILED.\nYour answer: %s\nExpected answer: %s\n", result1, "45");
// 	// 	}
// 	// 	free(result1);
// 	// }

// 	// result1 = intal_bincoeff(1000, 900);
// 	// if(!result1) {
// 	// 	printf("Test intal_bincoeff FAILED.\n");
// 	// } else {
// 	// 	if(0 == strcmp(result1, "63850511926305130236698511142022274281262900693853331776286816221524376994750901948920974351797699894319420811933446197797592213357065053890")) {
// 	// 		printf("Test intal_bincoeff PASSED\n");
// 	// 	} else {
// 	// 		printf("Test intal_bincoeff FAILED.\nYour answer: %s\nExpected answer: %s\n", result1, "63850511926305130236698511142022274281262900693853331776286816221524376994750901948920974351797699894319420811933446197797592213357065053890");
// 	// 	}
// 	// 	free(result1);
// 	// }

// 	// index1 = intal_max(a, 10);
// 	// if(6 == index1) {
// 	// 	printf("Test intal_max PASSED\n");
// 	// } else {
// 	// 	printf("Test intal_max FAILED.\nYour answer: %d\nExpected answer: %d\n", index1, 6);
// 	// }

// 	// index1 = intal_min(a, 10);
// 	// if(2 == index1) {
// 	// 	printf("Test intal_min PASSED\n");
// 	// } else {
// 	// 	printf("Test intal_min FAILED.\nYour answer: %d\nExpected answer: %d\n", index1, 2);
// 	// }

// 	// index1 = intal_search(a, 10, a[7]);
// 	// if(6 == index1) {
// 	// 	printf("Test intal_search PASSED\n");
// 	// } else {
// 	// 	printf("Test intal_search FAILED.\nYour answer: %d\nExpected answer: %d\n", index1, 6);
// 	// }

// 	// intal_sort(a, 10);
// 	// index1 = intal_binsearch(a, 10, "3");
// 	// if(1 == index1) {
// 	// 	printf("Test intal_binsearch and probably intal_sort PASSED\n");
// 	// } else {
// 	// 	printf("Test intal_binsearch and probably intal_sort FAILED.\nYour answer: %d\nExpected answer: %d\n", index1, 1);
// 	// }

// 	// result1 = coin_row_problem(a+1, 2);
// 	// if(0 == strcmp("12", result1)) {
// 	// 	printf("Test coin_row_problem PASSED\n");
// 	// } else {
// 	// 	printf("Test coin_row_problem FAILED.\nYour answer: %s\nExpected answer: %s\n", result1, "12");
// 	// }

// 	return 0;
// }
