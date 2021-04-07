/*
 * circularQ.c
 *
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element;//입력받는 원소의 자료형을 한꺼번에 바꾸어줄 수 있게 이름을 따로 붙혀준다.
typedef struct {
	element queue[MAX_QUEUE_SIZE];//원소는 MAX_QUEUE_SIZE-1개 저장할 수 있다.
	int front, rear;
}QueueType;


QueueType *createQueue();//Queue 생성함수. 반환값이 구조체의 포인터임을 확인. 즉, 동적할당한 장소의 주소를 반환.

int freeQueue(QueueType *cQ);//동적할당한 Que의 메모리 free하는 함수

int isEmpty(QueueType *cQ);//queue가 비어있는지 확인
/*front와 rear의 관계에 따라 비어있는지 아닌지 체크한다. 1은 비어있음, 0은 비어있지 않음을 의미함.
*/

int isFull(QueueType *cQ);//queue가 차있는지 확인. queue의 원소 수와 maxsize의 관계를 비교하거나
/*front와 rear의 관계에 따라서 확인한다. 다만, 원형queue에서는 비어있을 때와 차있을 때를 잘 구분해주어야 함.*/

void enQueue(QueueType *cQ, element item);//queue에 특정 item을 삽입. item을 입력해 원소로 만든다.
/*1. isFull검사를 실행하여 queue가 가득 찼으면 에러를 반환하는 전처리*/

void deQueue(QueueType *cQ, element* item);//queue에 
/*1. isEmpty 검사를 실행하여 queue가 비어있으면 에러를 반환하는 전처리*/

void printQ(QueueType *cQ);/*원형큐의 원소를 전부 출력. 있는 것만 출력한다.
추가로 디버그와 print한 Queue의 순서는 다를 수 있음을 생각하기.*/

void debugQ(QueueType *cQ);//??
/*원형 queue안에 무엇무엇이 들어있는지 알려주는 함수. 처음과 끝, ordered list의 순서마다
어떤 원소가 들어있는지 출력한다. - 값이 비어있는 곳도 출력하며 front가 queue의 자리를 하나 차지하고, rear는 후방 위치만 표기*/

element getElement();//원소를 입력받는 함수

int main(void)
{
	QueueType *cQ = createQueue();//MAX_QUEUE_SIZE에 따라 동적할당을 한 후, 주소를 반환
	element data;
	char command;//사용자가 입력하는 메뉴

	do{
		printf("---[2018038074]---[임종훈]---");
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			data = getElement();//원소 입력 함수 호출
			enQueue(cQ, data);//Queue 입력함수
			break;
		case 'd': case 'D':
			deQueue(cQ, &data);//원소 제거
			break;
		case 'p': case 'P':
			printQ(cQ);
			break;
		case 'b': case 'B':
			debugQ(cQ);
			break;
		case 'q': case 'Q'://프로그램을 종료하기 전 동적할당 했던 메모리를 해제한다.
   	        freeQueue(cQ);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');


	return 1;
}

QueueType *createQueue()
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType));//cQ에는 동적할당한 heap영역의 주소가 저장됨.
	cQ->front = 0;
	cQ->rear = 0;//cQ에는 주소가 저장되어 있으므로 ->로 접근해야 함.
	return cQ;
}

int freeQueue(QueueType *cQ)
{
    if(cQ == NULL) return 1;//동적할당 안 되어 있는 경우
    free(cQ);
    return 1;
}

element getElement()
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item);
	return item;//원소 반환.
}


/* complete the function */
int isEmpty(QueueType *cQ)
{
    if(cQ->front == cQ->rear){//front와 rear가 가르키는 큐의 위치가 같을 때 큐가 비어있다.
        return 1;
    }
    return 0;
}

/* complete the function */
int isFull(QueueType *cQ)
{
    if(cQ->front == 0){//만약 front가 0이라면
        if(cQ->rear == MAX_QUEUE_SIZE-1){//rear가 최대값 -1의 위치에 있을 때가 큐가 가득 찬 것이다.
            return 1;
        }
    }
    else{//그 외의 경우에는 rear이 front의 하나 뒤에 있을 때가 full
        if(cQ->front-1 == cQ->rear){
            return 1;
        }
    }
    return 0;
}


/* complete the function */
void enQueue(QueueType *cQ, element item)
{
    if(isFull(cQ)==1){//전처리 검사
        printf("Circular Queue is full!");
        return ;
    }
    cQ->rear = (cQ->rear+1)%MAX_QUEUE_SIZE;//rear가 가르키는 값 1증가. 마지막 값이었다면 처음으로 돌리기

	cQ->queue[cQ->rear] = item;//item 삽입
	return ;
}

/* complete the function */
void deQueue(QueueType *cQ, element *item)
{
    if(isEmpty(cQ)==1){//전처리 검사
        printf("Circular Queue is empty!");
        return ;   
    }
	cQ->front = (cQ->front+1)%MAX_QUEUE_SIZE;//front가 지정하는 위치만 바꿔주고 굳이 이전 값을 지워주지는 않음.


    return ;
}


void printQ(QueueType *cQ)
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE;//front가 가르키고 있는 다음 위치부터 
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;//while문에서 같았을 때, 반복문을 탈출해야 하므로 rear+1 해서 전부 출력할 수 있게 함.

	printf("Circular Queue : [");

	i = first;
	while(i != last){//큐 안에 들어있는 원소들 출력. i == last이면 탈출하므로 rear+1을 한 것
		printf("%3c", cQ->queue[i]);
		i = (i+1)%MAX_QUEUE_SIZE;//다음 원소로 이동

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)
{
	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)//큐 마다 무엇이 들어있는지 확인.
	{
		if(i == cQ->front) {//front가 가르키고 있는 값이면
			printf("  [%d] = front\n", i);//front의 위치임을 출력.
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);//이외에는 저장된 값 출력

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);//각각 위치 출력
}
