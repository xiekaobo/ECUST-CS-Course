#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <cstring>

enum	INSTRUCT_ENUM {
	JMP_INSTRUCT,				//直接跳转到地址为操作数的指令
	JPC_INSTRUCT,				//条件跳转.如果栈顶数据等于零,则跳转执行地址为操作数的指令,否则执行下一条指令
	ALLOCATE_INSTRUCT,	//分配内存,栈顶指针增加操作数
	INSTANT_INSTRUCT,		//直接将操作数的值压入栈顶
	LOAD_INSTRUCT,			//取某层过程的相对地址为操作数的内存的值到栈顶
	STORE_INSTRUCT,			//把栈顶数据存到某层过程的相对地址为操作数的内存中
	CALL_INSTRUCT,				//调用过程,返回地址压栈
	ENDCALL_INSTRUCT,		//结束过程,退栈,返回到原调用过程处
	NEGATIVE_INSTRUCT,	//取负操作,将栈顶数据取负后仍放在栈顶
	ADD_INSTRUCT,				//加法指令,取出栈顶数据和次栈顶数据的和再放到栈顶
	SUB_INSTRUCT,				//减法指令,取出栈顶数据和次栈顶数据的差再放到栈顶
	MULTI_INSTRUCT,			//相乘指令,取出栈顶数据和次栈顶数据的积再放到栈顶
	DIVID_INSTRUCT,			//相除指令,取出栈顶数据和次栈顶数据的商再放到栈顶
	ODD_INSTRUCT,				//判断栈顶数据是否为奇数.如果是,则栈顶数据为1,否则为0
	EQL_INSTRUCT,				//取出并判断栈顶数据和次栈顶数据是否相同.如果相同,则栈顶数据为1,否则为0
	NEQ_INSTRUCT,				//取出并判断栈顶数据和次栈顶数据是否不相同.如果相同,则栈顶数据为0,否则为1
	LES_INSTRUCT,				//取出并判断次栈顶数据是否小于栈顶数据.如果是,则栈顶数据为1,否则为0
	LEQ_INSTRUCT,				//取出并判断次栈顶数据是否小于等于栈顶数据.如果是,则栈顶数据为1,否则为0
	GTR_INSTRUCT,				//取出并判断次栈顶数据是否大于栈顶数据.如果是,则栈顶数据为1,否则为0
	GEQ_INSTRUCT,				//取出并判断次栈顶数据是否大于等于栈顶数据.如果是,则栈顶数据为1,否则为0个
	OUT_INSTRUCT,				//生成输出指令,输出栈顶数据
	IN_INSTRUCT,					//生成输人指令,读取数据到栈顶
};
//虚拟机指令结构
struct INSTRUCT_STRUCT
{
	enum INSTRUCT_ENUM		eInstruct;		//虚拟机指令
	int											nLevel;			//引用层与声明层的层次差
	int											nOperand;	//操作数,根据不同指令而不同
};

#define		MAX_NUMBER_INSTRUCTS					200		//最多的虚拟机指令数
#define		STACK_SIZE												500

extern		INSTRUCT_STRUCT			g_Instructs[MAX_NUMBER_INSTRUCTS];

int GetBase(int nNum, int* pStack, int nStackCurrentBase);
void PrintInInterprete(int nNo, int Stack[], int nStackTop, enum INSTRUCT_ENUM CurrentInstruct);
int InstructFromEnumToString(enum INSTRUCT_ENUM eInstruct, char* szString);
void InitializeInterpret(int Stack[]);

//解释程序
void Interpreter()
{
	INSTRUCT_STRUCT		CurrentInstruct;//指令寄存器存放当前虚拟指令

	int	nNo = 1;
	int	nInstructsIndex;//程序地址寄存器
	int	nStackBase;
	int	nStackTop;//地址寄存器
	int	nLevel;
	int	nBase, nAddress;
	int	Stack[STACK_SIZE];//数据存储器,数据栈

	InitializeInterpret(Stack);//初始化数据栈

	printf("\nInterpret Start\n");

	nStackTop = 0;//数据栈顶为零
	nStackBase = 0;
	nInstructsIndex = 0;
	Stack[0] = Stack[1] = Stack[2] = 0;

	do {
		CurrentInstruct = g_Instructs[nInstructsIndex];//读当前指令到指令寄存器CurrentInstruct
		nInstructsIndex++;//准备下一条指令

		PrintInInterprete(nNo, Stack, nStackTop, CurrentInstruct.eInstruct);//打印数据栈
		nNo++;

		switch (CurrentInstruct.eInstruct)//根据当前指令操作码
		{
		case JMP_INSTRUCT://直接跳转到地址为操作数的指令
			nInstructsIndex = CurrentInstruct.nOperand;
			break;
		case JPC_INSTRUCT://条件跳转.如果栈顶数据等于零,则跳转执行地址为操作数的指令,否则执行下一条指令
			nStackTop--;
			if (Stack[nStackTop] == 0)
				nInstructsIndex = CurrentInstruct.nOperand;
			break;
		case INSTANT_INSTRUCT://直接将操作数的值压入栈顶
			Stack[nStackTop] = CurrentInstruct.nOperand;
			nStackTop++;
			break;
		case LOAD_INSTRUCT://取某层过程的相对地址为操作数的内存的值到栈顶
			nLevel = CurrentInstruct.nLevel;
			nBase = GetBase(nLevel, Stack, nStackBase);
			nAddress = nBase + CurrentInstruct.nOperand;
			Stack[nStackTop] = Stack[nAddress];
			nStackTop++;
			break;
		case STORE_INSTRUCT://把栈顶数据存到某层过程的相对地址为操作数的内存中
			nStackTop--;
			nLevel = CurrentInstruct.nLevel;
			nBase = GetBase(nLevel, Stack, nStackBase);
			nAddress = nBase + CurrentInstruct.nOperand;
			Stack[nAddress] = Stack[nStackTop];
			break;
		case CALL_INSTRUCT:	//调用过程,返回地址压栈
			Stack[nStackTop] = GetBase(CurrentInstruct.nLevel, Stack, nStackBase);//将父过程基地址压入栈
			Stack[nStackTop + 1] = nStackBase;//本过程基地址入栈,此两项用于GetBase函数
			Stack[nStackTop + 2] = nInstructsIndex;//将当前指令指针入栈
			nStackBase = nStackTop;//改变基地址指针值为新过程的基地址
			nInstructsIndex = CurrentInstruct.nOperand;//跳转
			break;
		case ENDCALL_INSTRUCT:	//结束过程,退栈,返回到原调用过程处
			nStackTop = nStackBase;
			nInstructsIndex = Stack[nStackTop + 2];
			nStackBase = Stack[nStackTop + 1];
			break;
		case ALLOCATE_INSTRUCT://分配内存,栈顶指针增加操作数
			nStackTop += CurrentInstruct.nOperand;
			break;
		case NEGATIVE_INSTRUCT://取负操作,将栈顶数据取负后仍放在栈顶
			Stack[nStackTop - 1] = -Stack[nStackTop - 1];
			break;
		case ADD_INSTRUCT://加法指令,取出栈顶数据和次栈顶数据的和再放到栈顶
			nStackTop--;
			Stack[nStackTop - 1] = Stack[nStackTop - 1] + Stack[nStackTop];
			break;
		case SUB_INSTRUCT://减法指令,取出栈顶数据和次栈顶数据的差再放到栈顶
			nStackTop--;
			Stack[nStackTop - 1] = Stack[nStackTop - 1] - Stack[nStackTop];
			break;
		case MULTI_INSTRUCT://相乘指令,取出栈顶数据和次栈顶数据的积再放到栈顶
			nStackTop--;
			Stack[nStackTop - 1] = Stack[nStackTop - 1] * Stack[nStackTop];
			break;
		case DIVID_INSTRUCT://相除指令,取出栈顶数据和次栈顶数据的商再放到栈顶
			nStackTop--;
			Stack[nStackTop - 1] = Stack[nStackTop - 1] / Stack[nStackTop];//相除结果放在原nStackTop-2中
			break;
		case ODD_INSTRUCT://判断栈顶数据是否为奇数.如果是,则栈顶数据为1,否则为0
			Stack[nStackTop - 1] = Stack[nStackTop - 1] % 2;
			break;
		case EQL_INSTRUCT://取出并判断栈顶数据和次栈顶数据是否相同.如果相同,则栈顶数据为1,否则为0
			nStackTop--;
			Stack[nStackTop - 1] = (Stack[nStackTop - 1] == Stack[nStackTop]);
			break;
		case NEQ_INSTRUCT://取出并判断栈顶数据和次栈顶数据是否不相同.如果相同,则栈顶数据为0,否则为1
			nStackTop--;
			Stack[nStackTop - 1] = (Stack[nStackTop - 1] != Stack[nStackTop]);
			break;
		case LES_INSTRUCT://取出并判断次栈顶数据是否小于栈顶数据.如果是,则栈顶数据为1,否则为0
			nStackTop--;
			Stack[nStackTop - 1] = (Stack[nStackTop - 1] < Stack[nStackTop]);
			break;
		case LEQ_INSTRUCT://取出并判断次栈顶数据是否小于等于栈顶数据.如果是,则栈顶数据为1,否则为0
			nStackTop--;
			Stack[nStackTop - 1] = (Stack[nStackTop - 1] <= Stack[nStackTop]);
			break;
		case GTR_INSTRUCT://取出并判断次栈顶数据是否大于栈顶数据.如果是,则栈顶数据为1,否则为0
			nStackTop--;
			Stack[nStackTop - 1] = (Stack[nStackTop - 1] > Stack[nStackTop]);
			break;
		case GEQ_INSTRUCT://取出并判断次栈顶数据是否大于等于栈顶数据.如果是,则栈顶数据为1,否则为0个
			nStackTop--;
			Stack[nStackTop - 1] = (Stack[nStackTop - 1] >= Stack[nStackTop]);
			break;
		case OUT_INSTRUCT://生成输出指令,输出栈顶数据
			printf("OUT_INSTRUCT=%d\n", Stack[nStackTop - 1]);
			nStackTop--;
			break;
		case IN_INSTRUCT://生成输人指令,读取数据到栈顶
			printf("IN_INSTRUCT=");
			scanf("%d", &Stack[nStackTop]);
			nStackTop++;
			break;
		}
	} while (nInstructsIndex != 0);
}
//通过过程基址求上一层过程的基址
int GetBase(int nNum, int* pStack, int nStackCurrentBase)
{
	int nStackIndex;

	nStackIndex = nStackCurrentBase;
	while (nNum > 0)
	{
		nStackIndex = pStack[nStackIndex];
		nNum--;
	}
	return nStackIndex;
}

void InitializeInterpret(int Stack[])//初始化数据栈
{
	int	i;

	for (i = 0; i < STACK_SIZE; Stack[i++] = -1);
}

void PrintInInterprete(int nNo, int Stack[], int nStackTop, enum INSTRUCT_ENUM eInstruct)//打印数据栈
{
	int		i;
	char		strInstruct[100];

	InstructFromEnumToString(eInstruct, strInstruct);
	printf("%-4d", nNo);
	for (i = 0; i <= nStackTop; i++)
		printf("%-3d", Stack[i]);
	printf("%-20s\n", strInstruct);
}
