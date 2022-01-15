#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/stat.h>

int main (int argc, char* argv[]) 
{
    int barrelhoney=atoi(argv[1]);
    printf("Вместительность бочки %d грамм\n", barrelhoney);
    int initialamount=atoi(argv[2]);
    printf("Начальное количество меда в бочке =  %d грамм\n", initialamount);
    int bee=atoi(argv[3]);
    printf("Количество пчел %d \n", bee);
    int quantity=atoi (argv[4]);
    int time=atoi(argv[5]);
    printf("Медведь потребляет по  %d грамм меда каждые %d секунд\n", quantity, time);    
    //int gramm=atoi(argv[6]);
    printf("Каждая пчела приносит по  %s грамм \n", argv[6]);
    pid_t pid;
    int porciya=0, length, cont=0, mq_id;
    char str1[100];
    key_t ipckey;
    struct {long type; char text[100];}mymsg;
    length=sizeof(mymsg)-sizeof(long);
    ipckey=ftok("/tmp/foo", 42);
    mq_id = msgget(ipckey, IPC_CREAT | 0666);
    //for (int i=1; i<=bee; i++)
    if (!(pid=fork())) 
    {
       for (int i=1;initialamount<=barrelhoney;i++)
        {
            memset (mymsg.text,0,100);
            strcpy(mymsg.text,argv[6]);
            mymsg.type=1;
            msgsnd(mq_id, &mymsg,length,0);
            sleep (2);
        }
        return 0;
    }
    for (int i=1;initialamount<=barrelhoney;i++)
    {
    msgrcv(mq_id, &mymsg,length,1,0);
    printf("Пчела принесла %s грамм меда\n",  mymsg.text);
    initialamount+=atoi(mymsg.text);
    printf("В бочке %d грамм меда\n", initialamount);}
    msgctl (mq_id, IPC_RMID,0);
    return 0;
}
