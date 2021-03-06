#include<pthread.h>
#include<semaphore.h>
#include<stdio.h>

int Max_Svalue = 10;
int stack[10];
int top = -1;
int data;

/*
*funtion to check the stack is empty or not
*/
int emptyStack()
{
    if(top == -1)
        return -1;
    else 
        return 0;

}

/*
*funtion to check the stack is full or not
*/

int fullStack()
{
    if(top == Max_Svalue)
        return 1;
    else 
        return 0;    
}

/*
*funtion to return to the return the top value of the stack without removing it  
*/

int peek()
{
    return stack[top];
}

/*
* to remove the top most element of the stack as it follow FIFO
*/

int pop()
{

    if(!emptyStack())
    {
        data = stack[top];
        top = top -1;
        return data;
    }
    else
    {   
        //printf("Couldn't retrieve data, this stack is empty\n");
        printf("is this a stack or a lays packet......\n");
    }
}

/*
*to add an element in the stack
*/

int push(data)
{
    if(!fullStack())
    {
        top = top+1;
        stack[top] = data;
    }

    else
    {
        //printf("couldn't insert data as the stack is full\n");
        printf("sorry buddy, this stack is full...try somewhere else \n");
    }
}

pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;
sem_t s1;

/*
* push operation from the producer
*/

void* producer_func(void* pv)
{
    int i;
    printf("push the operation of 1,2,3,4,5,6,7 \n");
    pthread_mutex_lock(&m1);    //locking the mutex

    //pushing the given data into stack

    push(1);
    push(2);
    push(3);                
    push(4);
    push(5);
    push(6);
    push(7);

    pthread_mutex_unlock(&m1);      //unlocking the mutex
    sem_post(&s1);

}

/*
* pop operation from the consumer
*/

void* consumer_func(void* pv)		
{
	int i;
	printf("poping all the values from the stack\n");
	sem_wait(&s1);			//changing sequence lead to deadlock
	pthread_mutex_lock(&m1);
	
	pop();
	pop();
    pop();
    pop();
    pop();
    pop();
    pop();
	
	pthread_mutex_unlock(&m1);
}

int main()
{
    printf("\n\nPRODUCER CONSUMER PROBLEM USING SEMAPHORES IN STACK \n\n");
    pthread_t pt1,pt2;	//thread handles
	sem_init(&s1,0,0);
	pthread_create(&pt1,NULL,producer_func,NULL);
	pthread_create(&pt2,NULL,consumer_func,NULL);
	pthread_join(pt1,NULL);
	pthread_join(pt2,NULL);
	printf("Top element in stack: %d\n" ,peek());
	printf("Full stack: %s\n" , fullStack()?"true":"false");
   	printf("Empty stack: %s\n" , emptyStack()?"true":"false");
	sem_destroy(&s1);
	pthread_mutex_destroy(&m1);
	printf("main--Thank you\n");
	return 0;
}