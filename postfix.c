/*
 * postfix.c
 *
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10 //임시로 연산자와 피연산자를 저장하는 스택의 크기
#define MAX_EXPRESSION_SIZE 20 //식의 크기. infix와 postfix의 크기

/* stack 내에서 우선순위, lparen = 0 가장 낮음 */
//열거형 선언. 우선순위를 정해줌. 해당 숫자를 반환
typedef enum{
	lparen = 0,  /* ( 왼쪽 괄호 */
	rparen = 9,  /* ) 오른쪽 괄호*/
	times = 7,   /* * 곱셈 */
	divide = 6,  /* / 나눗셈 */
	plus = 5,    /* + 덧셈 */
	minus = 4,   /* - 뺄셈 */
	operand = 1 /* 피연산자 */
} precedence;

//연산, 연산자, 피연산자 등을 저장할 공간 생성.
char infixExp[MAX_EXPRESSION_SIZE];   	/* infix expression을 저장하는 배열 */
char postfixExp[MAX_EXPRESSION_SIZE];	/* postfix로 변경된 문자열을 저장하는 배열 */
char postfixStack[MAX_STACK_SIZE];	/* postfix로 변환을 위해 필요한 스택 */
int evalStack[MAX_STACK_SIZE];		/* 계산을 위해 필요한 스택 */

/*stack에서 값이 들어왔다 나가는 top의 위치 설정.
-1로 설정하면 스택을 올리고 값을 삽입하고
0이면 값을 삽입한 후 스택의 수치를 올린다.*/
int postfixStackTop = -1;  /* postfixStack용 top */
int evalStackTop = -1;	   /* evalStack용 top */

//postfix를 구하고 이를 통해 구한 결과값.
int evalResult = 0;	   /* 계산 결과를 저장 */

void postfixpush(char x);//infix를 postfix로 변환시 '연산자'를 postfixStack에 저장한다.
char postfixPop();//postfixStack에서 postfixExp로 보내고 postfixStack에 있는 값을 지운다.

void evalPush(int x);//postfix로 변환한 식을 계산해서 결과를 만들어줄 때 evalStack에 저장하는 함수.
int evalPop();//evalResult로 값을 보낼 때 evalStack에 top을 지우는 함수

void getInfix();//사용자로부터 식을 입력받는 함수.

precedence getToken(char symbol);/*getToken은 열거형 precedence안에 있는 값 중에서만 반환한다는 뜻!
연산기호를 받아서 우선순위 숫자를 반환.*/
precedence getPriority(char x);//우선순위를 결정하는 함수. getToken을 호출한다.

void charCat(char* c);//*infix에서 postfix로 변환할때 이어붙혀주는 식
void toPostfix();//infix -> postfix로 바꾸는 함수
void debug();//각각 무슨무슨 값 들어있는지 설명
void reset();//초기화
void evaluation();//결과값 구하는 함수

int main()
{
	char command;//사용자 입력 저장하는 변수

	printf("---[2018038074]---[임종훈]---");

	do{
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			getInfix();
			break;
		case 'p': case 'P':
			toPostfix();
			break;
		case 'e': case 'E':
			evaluation();
			break;
		case 'd': case 'D':
			debug();
			break;
		case 'r': case 'R':
			reset();
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

void postfixPush(char x)
{
    postfixStack[++postfixStackTop] = x;
}

char postfixPop()
{
    char x;
    if(postfixStackTop == -1)
        return '\0';
    else {
    	x = postfixStack[postfixStackTop--];
    }
    return x;
}

void evalPush(int x)
{
    evalStack[++evalStackTop] = x;
}

int evalPop()
{
    if(evalStackTop == -1)
        return -1;
    else
        return evalStack[evalStackTop--];
}

/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */
void getInfix()
{
    printf("Type the expression >>> ");
    scanf("%s",infixExp);
}

precedence getToken(char symbol)
{
	switch(symbol) {
	case '(' : return lparen;
	case ')' : return rparen;
	case '+' : return plus;
	case '-' : return minus;
	case '/' : return divide;
	case '*' : return times;
	default : return operand;
	}
}

precedence getPriority(char x)
{
	return getToken(x);
}

/**
 * 문자하나를 전달받아, postfixExp에 추가
 */
void charCat(char* c)
{
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1);//새로운 함수
	else
		strncat(postfixExp, c, 1);
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix()
{
	/* infixExp의 문자 하나씩을 읽기위한 포인터 */
	char *exp = infixExp;
	char x; /* 문자하나를 임시로 저장하기 위한 변수 */

	/* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
	while(*exp != '\0')
	{
		/* 필요한 로직 완성 */

	}

	/* 필요한 로직 완성 */

}
void debug()
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);
	printf("postExp =  %s\n", postfixExp);
	printf("eval result = %d\n", evalResult);

	printf("postfixStack : ");
	for(int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]);

	printf("\n");

}

void reset()
{
	infixExp[0] = '\0';
	postfixExp[0] = '\0';

	for(int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';
         
	postfixStackTop = -1;
	evalStackTop = -1;
	evalResult = 0;
}

void evaluation()
{
	/* postfixExp, evalStack을 이용한 계산 */
}

