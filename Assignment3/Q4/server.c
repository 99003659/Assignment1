#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
// Define message queue structure
struct msg_buffer 
{
   long message_type;
   char text_message[100];
} message;

int main() 
{
   key_t my_key;
   int msg_id;
   my_key = ftok("progfile", 65); //create unique key
   msg_id = msgget(my_key, 0666 | IPC_CREAT); //create message queue and return id
   msgrcv(msg_id, &message, sizeof(message), 1, 0); //used to receive message
   // display the message
   printf("Received Message is : %s \n", message.text_message);

   char str[100];
   str = message.text_message;
   
   for (int i = 0; str[i] !=''; i++)
	{
		if (isalpha(str[i]))
		{
			if (islower(str[i]))
				str[i] = toupper(str[i]);
			else	
            str[i] = tolower(str[i]);
		}
	}

   message.text_message = str;
  
   msgsnd(msg_id, &message, sizeof(message), 0); 
   
   printf("Sent message is : %s \n", message.text_message);
   return 0;
}
