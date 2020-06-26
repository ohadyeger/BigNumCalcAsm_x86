
// C program for array implementation of stack
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// A structure to represent a stack
typedef struct bignum
{   
    long num_of_digits;
    int sign;
    char *digit;
    
}bignum;

#define MAX_CAPACITY 1024;
#define PLUS 1
#define MINUS -1
////////////////////////////////stack/////////
int top;
unsigned capacity;
bignum* array;
////////////////////////////////////////////////////////


 extern void adds(bignum* a, bignum * b,bignum * c);
 extern void subt(bignum* a, bignum * b,bignum * c);
 extern void mult(bignum* a, bignum * b,bignum * c);
 extern void divide_by_2(bignum * a,bignum * ans);
 
 void subtract_bignum(bignum* a, bignum* b,bignum * c,int tofree);
 void add_bignums(bignum* a, bignum* b,bignum * c,int tofree);
 char * multiply_bignum(bignum* a, bignum* b,bignum * c,int tofree);
 void divide_bignum(bignum *a,bignum *b,bignum * result,bignum *factor);

void createStack()
{
    
    capacity = MAX_CAPACITY;
    top = -1;
    array =  malloc(capacity * sizeof(bignum));//freed

}
 
// Stack is full when top is equal to the last index
int isFull()
{   return top == capacity - 1; }
 
// Stack is empty when top is equal to -1
int isEmpty()
{   return top == -1;  }
 
// Function to add an item to stack.  It increases top by 1
void push( bignum *item)
{
    if (isFull())
        return;
   array[++top] = *item;
}
 
// Function to remove an item from stack.  It decreases top by 1
bignum* pop()
{
    if (isEmpty())
        return NULL;
    return &array[top--];
}
// Driver program to test above functions

void EmptyStack(){
    bignum *popped;
    while(!isEmpty())
    {   
        popped = pop();
        free(popped->digit);
    }
    return;
}

char *append_char( char *str, char ch )
{
    int length = strlen( str );
    char *str2;

    str2 = ( char * )realloc( str, length + 2  );
    if (!str2) {
        free(str);
        return NULL;
    }
    str = str2;

    str[length] = ch;
    str[length+1] = 0;

    return str;//freed
}


int compare_bignum(bignum *a, bignum *b)
{
	int i;				/* counter */

	if ((a->sign == MINUS) && (b->sign == PLUS)) 
            return(MINUS);//a<b
	if ((a->sign == PLUS) && (b->sign == MINUS))
            return(PLUS);//a>b
         if(a->num_of_digits>b->num_of_digits)return PLUS;
         if(a->num_of_digits<b->num_of_digits)return MINUS;
         
       
	for (i = 0; i<a->num_of_digits; i++) {
		if (a->digit[i] > b->digit[i]) return(PLUS * a->sign);
		if (b->digit[i] > a->digit[i]) return(MINUS * a->sign);
	}

	return 0;
}


//has to fix
void zero_remove(bignum *n)
{
        
        int i;
        long numtmp = n->num_of_digits;
        int flag=0;
        for(i=0;i<strlen(n->digit);i++){
            if(n->digit[i]=='0'|| n->digit[i]==0){
                n->num_of_digits--;
                flag =1;
                
            }else break;
        
        }
        
        if(flag==1){//means we have zero padding
            char * copy =calloc((n->num_of_digits+1),1);
            strcpy(copy,(n->digit+(numtmp-(n->num_of_digits))));

            free (n->digit);
            n->digit=copy;
            
        }
        
        if ((n->num_of_digits == 0) && (n->digit[0] == 0))
		n->sign = PLUS;
}



long max(long a, long b)
{
	if (a > b) return(a); else return(b);
}



void add_bignums(bignum* a,bignum* b,bignum* c ,int tofree){
    
    
    if (a->sign == b->sign) c->sign = a->sign;
      else {
            if (a->sign == MINUS) {
                    a->sign = PLUS;
                    subtract_bignum(b,a,c,0);
                    a->sign = MINUS;
            } else {
                        b->sign = PLUS;
                        subtract_bignum(a,b,c,0);
                        b->sign = MINUS;
            }
            return;

        }
    
    c->num_of_digits = (max(a->num_of_digits,b->num_of_digits)+2);
    c->digit=calloc(c->num_of_digits+2,1);
   // c->digit[c->num_of_digits+1]=0;
    if(a->num_of_digits==0){
        strcpy(c->digit,b->digit);
        c->num_of_digits=b->num_of_digits;
        //zero_remove(c);
        return;
    }
    else if(b->num_of_digits==0){
        strcpy(c->digit,a->digit);
        zero_remove(c);
        return;
    }
    adds(a,b,c);
        
    zero_remove(c);
    if (tofree){
        free(a->digit);
        free(b->digit);
    }
   // push(c);
    
    
    
}

void subtract_bignum(bignum* a, bignum* b,bignum * c, int tofree){
    
        if ((a->sign == MINUS) || (b->sign == MINUS)) {
                b->sign = -1 * b->sign;
                add_bignums(a,b,c,0);
                b->sign = -1 * b->sign;
                return;
        }

        if (compare_bignum(a,b) == -1) {
                subtract_bignum(b,a,c,0);
                c->sign = MINUS; 
                return;
    }
    
    c->num_of_digits = max(a->num_of_digits,b->num_of_digits)+1;
    c->digit=(char*)calloc(c->num_of_digits+1,1);
    c->digit[c->num_of_digits]=0;
    c->sign=PLUS;
    
    
    subt(a,b,c);
    
    if(tofree){
        free(a->digit);
        free(b->digit);
    }
    zero_remove(c);
    return;
    
}


char * multiply_bignum(bignum * a, bignum * b,bignum * ans,int tofree){
    
    
            ans->num_of_digits = a->num_of_digits + b->num_of_digits+1;
            char * ad = NULL;
            ans->digit =calloc(ans->num_of_digits+1,1);
             ad =ans->digit;
            ans->sign=PLUS;
            mult (a,b,ans);
            zero_remove(ans);
            ans->sign = a->sign * b->sign;
            if(tofree){
            free(a->digit);
            free(b->digit);
   
                
            }
            return ad;
}
//////////////////////////////////////////////////////////////////////////////////////

void  copyBN(bignum* n,bignum * toCopy){
    //if(n->digit == NULL) free(n->digit);
    n->num_of_digits=toCopy->num_of_digits;
    n->sign=toCopy->sign;
    free(n->digit);
    n->digit=calloc(max(n->num_of_digits,toCopy->num_of_digits)+2,1);
    strcpy(n->digit,toCopy->digit);
    //afree(toCopy->digit);
    //toCopy->digit = NULL;
    return;
    
}
long count_char(bignum * a){
    long i ;
    long count=0;
    for(i=0;i<strlen(a->digit);i++){
        if(a->digit[i]>='0' && a->digit[i]<='9')
            count++;
    }
    return count;
}

void divide_2(bignum * a, bignum * ans){
    if(a->num_of_digits==0)return;
    
    ans->digit=calloc(a->num_of_digits+2,1);
    ans->num_of_digits=a->num_of_digits;
    ans->sign=PLUS;
    divide_by_2(a,ans);
    ans->num_of_digits=count_char(ans);
    zero_remove(ans);
    ans->digit[ans->num_of_digits]=0;
    ans->sign = a->sign;
    return;
}




void divide_helper(bignum* num1,bignum* num2,bignum * result,bignum *factor ){
    
    if(compare_bignum(num1,num2)==-1){
            bignum divided2;
            divide_2(num2,&divided2);
            copyBN(num2,&divided2);
            free(divided2.digit);
            divided2.num_of_digits=0;
            divide_2(factor,&divided2);
            copyBN(factor,&divided2);
            free(divided2.digit);
        return;
    }
        bignum ans;
        char* ane = NULL;
        bignum two = {.num_of_digits=1,.sign=PLUS,.digit="2"};
        ane=multiply_bignum(num2,&two,&ans,0);
        copyBN(num2,&ans);
        free(ane);
        ane=multiply_bignum(factor,&two,&ans,0);
        copyBN(factor,&ans);
        free(ane);
        divide_helper(num1,num2,result,factor);
        if(compare_bignum(num1,num2)>=0){
           add_bignums(result,factor,&ans,0);
           copyBN(result,&ans);
           free(ans.digit);
           subtract_bignum(num1,num2,&ans,0);
           copyBN(num1,&ans);
           free(ans.digit);
      
        }
            bignum divided3;
            divide_2(num2,&divided3);
            copyBN(num2,&divided3);
            free(divided3.digit);
            divided3.num_of_digits=0;
            divide_2(factor,&divided3);
            copyBN(factor,&divided3);
               free(divided3.digit);

        return;
        
    
}




void divide_bignum(bignum * a, bignum * b,bignum * result,bignum * factor){
     int asign = a->sign;
     int bsign = b->sign;
     a->sign=PLUS;
     b->sign=PLUS;
      divide_helper(a,b,result,factor);
      a->sign=asign;
      b->sign=bsign;
      if(compare_bignum(a,b)>=0){
          bignum ans;
          subtract_bignum(a,b,&ans,0);
          copyBN(a,&ans);
          add_bignums(result,factor,&ans,0);
          copyBN(result,&ans);
          
    }
    result->sign = asign*bsign;
    result->digit[result->num_of_digits]=0;
    result -> num_of_digits = count_char(result);
    free(factor->digit);
    free(a->digit);
    free(b->digit);
      return;
}

////////////////////////////////////////////////////////////////////////////////////////

void release_BN(bignum* a, bignum * b){
    free(a->digit);
    a->digit = NULL;
    free(b->digit);
    b->digit = NULL;
}

void print_BN(){
    if(!isEmpty()){
    bignum * res = &array[top];
    if(res->num_of_digits==0){
        putchar('0');
    }
    else if(res->sign==MINUS)
        putchar('-');
    printf("%s\n",res->digit);
    
    //free(res->digit);
    }
    return;
}


 
int main(int argc, char **argv)
{
 char *str = calloc(2,1);
 int dig = 0;
 int toPush=0;
 int sig=PLUS;
 int i;
 bignum* num1;
 bignum* num2;
createStack();
 while((i=getchar())!=EOF) { 

        if((i>='0' && i<='9')){
          
           str = append_char(str,i);
           dig++;
           toPush |=1;
    }
       else{
            if(toPush==1){
            char * digits=calloc(dig+1,1);
            digits[dig]=0;
            strcpy(digits, str);
            //str = (char*)realloc(str,1);
            str[0]=0;
            bignum num = {.num_of_digits=dig,.sign=sig,.digit=digits};
            push(&num);
            dig =0;
            toPush=0;
            sig=PLUS;
            }  
            if (i=='_')
            sig=MINUS;
            
             switch(i){
        
        case '+': 
            if(top>=1){
                bignum ans;
                 num1 = pop();
                 num2 = pop();
                add_bignums(num2,num1,&ans,1);
                ans.digit[ans.num_of_digits]=0;
                push(&ans);
                
                
            }
            break;
        case '/'://do div
            if(top>=1){
                 num1 = pop();
                 num2 = pop();
                zero_remove(num1);
                zero_remove(num2);
                if(num1->num_of_digits>0){
                bignum res={.num_of_digits=0,.sign=PLUS};
                res.digit=calloc(2,1);
                bignum factor={.num_of_digits=1,.sign=PLUS};
                factor.digit=calloc(2,1);
                
                factor.digit[0]='1';
                factor.digit[1]=0;
                res.digit[0]=0;
               
                divide_bignum(num2,num1,&res,&factor);
                res.digit[res.num_of_digits]=0;
                push(&res);}
                
                
            }
            
            break;
        case '*'://mul
            if(top>=1){
                bignum ans;
                 num1 = pop();
                 num2 = pop();
                multiply_bignum(num2,num1,&ans,1);
                ans.digit[ans.num_of_digits]=0;
                push(&ans);
                
            }
            
            
            break;
        case '-': //sub
            if(top>=1){
                bignum ans;
                 num1 = pop();
                 num2 = pop();
                subtract_bignum(num2,num1,&ans,1);
                ans.digit[ans.num_of_digits]=0;
                push(&ans);

                }
            break;
        case 'p'://print remsult at top of stack
            print_BN();
            break;
        case 'c'://clear the stack(move pointer to begining)
            EmptyStack();
            break;
        case 'q':
            EmptyStack();
            free(str);
            free(array);
            return 0;
            break;
        default:
            break;        
    }
    
    }

}

EmptyStack();
free(str);
free(array);
 return 0;

}