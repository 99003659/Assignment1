#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <pthread.h>
#define MAx 7

sem_t empty;
sem_t full;
int item;
int cir_queue[MAX];
int front = -1;
int rear = -1;
void insert(item);
void delete();
void* prod(void* pp)
{
    sem_wait(&empty);
    scanf("%d",&item);
    insert(item);
    printf("\n");
    sem_post(&full);
}
void* cons(void* pp)
{
    sem_wait(&full);
    delete();
    sem_post(&empty);
}

void insert(int item)
{
    if((front == 0 && rear == MAX-1) || (front == rear+1))
    {
        printf("Circular Queue Overflow n");
        return;
    }
    else if(front == -1)
    {
        front = 0;
        rear = 0;
        cir_queue[rear] = item ;

    }
    else if(rear == MAX-1 && front!= 0)
        {   rear = 0;
            cir_queue[rear] = item ;
            //printf("Element Produced : %d\n",item);
        }
    else
        {   rear = rear+1;
            cir_queue[rear] = item ;
            //printf("Element Produced : %d\n",item);
        }
    }
    printf("Element Produced : %d\n",item);
}

void delete()
{
if(front == -1)
{
printf("Queue Underflown");
return ;
}

int data = cir_queue[front]; 
cir_queue[front] = -1; 

if(front == rear)
{
front = -1;
rear=-1;
}
else
{
if(front == MAX-1)
front = 0;
else
front = front+1;
}
printf("Element Consumed : %d\n",cir_queue[front]);
}


int main()
{
  int item;
   sem_init(&empty,0,MAX);
    sem_init(&full,0,0);
    pthread_t pro[8],con[8];
   printf("Enter the items to be produced and consumed of buffer 8\n ");
   for(int i = 0; i < 8; i++) {
    pthread_create(&pro[i], NULL, (void *)prod, NULL);
    }
     for(int i = 0; i < 8; i++) {
        pthread_create(&con[i], NULL, (void *)cons,NULL);
    }
     for(int i = 0; i < 8; i++) {
        pthread_join(pro[i], NULL);
    }
    for(int i = 0; i < 8; i++) {
        pthread_join(con[i], NULL);
    }
       sem_destroy(&empty);
    sem_destroy(&full);
return 0;
}


