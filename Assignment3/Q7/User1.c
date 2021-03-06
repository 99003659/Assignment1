#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
  
int main()
{

    int fd;

    //FIFO file path
    char* user1 = "/tmp/user1";

    mkfifo(user1 0666);

    char arr1[80], arr2[80];
    while (1)
    {
        //open file in write only
        fd = open(user1, O_WRONLY);

        //taking input arr2 from user
        fgets(arr2, 80, stdin);

        //write the input arr2 on user1
        write(fd, arr2, strlen(arr2)+1);
        close(fd);

        //opening arr2 in read only
        fd = open(user1, O_RDONLY);

        //read from user1
        read(fd, arr1, sizeof(arr1));

        printf("User2: %s\n", arr1);
        close(fd); 
    }

    return 0;

}