#include <vxWorks.h> /* Always include this as the first thing in every program */
#include <time.h>	/* we use clock_gettime */
#include <taskLib.h>  /* we use tasks */
#include <sysLib.h>   /* we use sysClk... */
#include <semLib.h>   /* we use semaphores */
#include <logLib.h>   /* we use logMsg rather than printf */

/* a semaphore supporting mutual exclusion */
SEM_ID mutexId, binaryId;

/* task references */
int taskSteering, taskListening;

/* function prototypes */
void steer();
void listen();

/* Global Variable */
int steerState;
int input;
int isListening;

/* a routine createM to create "mutex" semaphore - can be also done from the shell line  */
/* queue tasks on FIFO basis and deletion safety	*/
void createM()
{
	mutexId = semMCreate(SEM_Q_FIFO | SEM_DELETE_SAFE);
}

void mutex(){
	taskListening = taskSpawn("listen", 95, 0x100, (FUNCPTR)listen,0,0,0,0,0,0,0,0,0,0);
	taskSteering = taskSpawn("steer", 95,0x100,2000,(FUNCPTR)steer,0,0,0,0,0,0,0,0,0,0);
	taskDelete(taskSteering);
}

void steer(){
	steerState = 0;
	input = NULL;
	while(1){
		if(input == -1){
			isListening = 0;
		}
		//Straight -> Straight
		if(steerState == 0 && input == 0){
			steerState = 0;
			printf("Steering straight\n");
		}
		//Straight -> Left
		else if(steerState == 0 && input == 1){
			steerState = 1;
			printf("Steering left\n");
		}
		//Left -> Left
		else if(steerState == 1 && input == 1){
			printf("Steering left\n");
		}
		//Left -> Straight
		else if(steerState == 1 && input == 0){
			steerState = 0;
			printf("Steering Straight\n");
		}
		//Straight -> Right
		else if(steerState == 0 && input == 2){
			steerState = 2;
			printf("Steering Right\n");
		}
		//Right -> Right
		else if(steerState == 2 && input == 2){
			printf("Steering Right\n");
		}
		//Right -> Straigh
		else if(steerState == 2 && input == 0){
			steerState = 0;
			printf("Steering Straight\n");
		}
		else{}
	}
}

void listen()
{

}
