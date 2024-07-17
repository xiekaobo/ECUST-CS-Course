#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <cstring>
#define		MAX_LENGTH_OF_A_WORD				10		//一个单词的最多字符个数
#define		MAX_NUMBER_OF_WORDS					1000	//可识别的最多单词个数

enum	WORD_TYPE_ENUM {//单词类型枚举值
	INVALID_WORD,
	IDENTIFIER,
	NUMBER,
	CONST,
	VAR,
	PROCEDURE,
	BEGIN,
	END,
	IF,
	THEN,
	WHILE,
	DO,
	WRITE,
	READ,
	CALL,
	LEFT_PARENTHESIS,
	RIGHT_PARENTHESIS,
	COMMA,
	SEMICOLON,
	PERIOD,
	PLUS,
	MINUS,
	MULTIPLY,
	DIVIDE,
	ODD,
	EQL,
	NEQ,
	LES,
	LEQ,
	GTR,
	GEQ,
	ASSIGN,
	DTA,
	SL_COMMENT,
	ML_COMMENT,
	BOOL,
	TRUE,
	FALSE,
	FLOAT,
	ELSE,
	FOR
};

struct	WORD_STRUCT{//一个单词的数据结构
				char												szName[MAX_LENGTH_OF_A_WORD];//单词名字的字符串
				enum WORD_TYPE_ENUM		eType;//单词类型枚举值
				double												nNumberValue;//数单词的值
				int												nLineNo;//在源代码文件中单词所在的行数
};

extern	WORD_STRUCT			g_Words[MAX_NUMBER_OF_WORDS];
extern	int									g_nWordsIndex;
extern	int									g_nInstructsIndex;

int BlockParsing(int nIndentNum);
int OneConstantParsing(int nIndentNum);
int OneVariableParsing(int nIndentNum);
int StatementParsing(int nIndentNum);
int ConditionParsing(int nIndentNum);
int ExpressionParsing(int nIndentNum);
int TermParsing(int nIndentNum);
int FactorParsing(int nIndentNum);
void PrintInParsing(int nWordsIndex,int nIndentNum,char *pString);

int ParsingAnalysis()//语法分析
{
	printf("\n----------------Parsing Begin!--------------\n");
	printf("No  Line--(Word)-----\n");

	g_nWordsIndex=0;//g_nWordsIndex是已识别单词的序号

	//程序由分程序Block开始
	PrintInParsing(g_nWordsIndex,0,"BlockParsing");//打印"BlockParsing"
	BlockParsing(1);//"分程序"Block语法分析

	if(g_Words[g_nWordsIndex].eType==PERIOD)
	{//分程序Block后面以点'.'结束
		PrintInParsing(g_nWordsIndex,0,"PERIOD");//打印"PERIOD"
		printf("----------------Parsing Successfull Finished!--------------\n");
		return OK;
	}
	else
		return ERROR;
}
//"分程序"Block语法分析
int BlockParsing(int nIndentNum)//nIndentNum是打印时要缩进的空格数
{
	if(g_Words[g_nWordsIndex].eType==CONST)//如果单词是"const"
	{
		PrintInParsing(g_nWordsIndex,nIndentNum,"CONST");//打印调试信息

		g_nWordsIndex++;//取下一个单词
		PrintInParsing(g_nWordsIndex,nIndentNum,"OneConstantParsing");//打印调试信息
		OneConstantParsing(nIndentNum+1);//一个"常量声明"语法分析

		while(g_Words[g_nWordsIndex].eType==COMMA)//如果后面有逗号','
		{
			PrintInParsing(g_nWordsIndex,nIndentNum,"COMMA");//打印调试信息

			g_nWordsIndex++;//取下一个单词
			PrintInParsing(g_nWordsIndex,nIndentNum,"OneConstantParsing");//打印调试信息
			OneConstantParsing(nIndentNum+1);//必须再处理一个"常量声明"
		}

		if(g_Words[g_nWordsIndex].eType==SEMICOLON)//常量声明最后以分号';'结束
		{
			PrintInParsing(g_nWordsIndex,nIndentNum,";");//打印调试信息
			g_nWordsIndex++;//取下一个单词
		}
		else
			return ERROR;//错误,漏掉了逗号或者分号
	}
	if(g_Words[g_nWordsIndex].eType==VAR)//如果单词是"var"
	{
		PrintInParsing(g_nWordsIndex,nIndentNum,"VAR");//打印调试信息

		g_nWordsIndex++;//取下一个单词
		PrintInParsing(g_nWordsIndex,nIndentNum,"OneVariableParsing");//打印调试信息
		OneVariableParsing(nIndentNum+1);//一个"变量声明"语法分析

		while(g_Words[g_nWordsIndex].eType==COMMA)//如果后面有逗号','
		{
			PrintInParsing(g_nWordsIndex,nIndentNum,"COMMA");//打印调试信息

			g_nWordsIndex++;//取下一个单词
			PrintInParsing(g_nWordsIndex,nIndentNum,"OneVariableParsing");//打印调试信息
			OneVariableParsing(nIndentNum+1);//必须再处理一个"变量声明"
		}

		if(g_Words[g_nWordsIndex].eType==SEMICOLON)//变量声明最后以分号';'结束
		{
			PrintInParsing(g_nWordsIndex,nIndentNum,";");//打印调试信息
			g_nWordsIndex++;//取下一个单词
		}
		else
			return ERROR;
	}
	/*if (g_Words[g_nWordsIndex].eType == IDENTIFIER)//一个变量声明就是标识符
	{
		PrintInParsing(g_nWordsIndex, nIndentNum, "IDENTIFIER");//打印调试信息
		g_nWordsIndex++;//取下一个单词

		return OK;
	}*/
	while (g_Words[g_nWordsIndex].eType==PROCEDURE)//如果单词是"procedure",则进入"函数定义"语法分析
	{
		PrintInParsing(g_nWordsIndex,nIndentNum,"PROCEDURE");//打印调试信息

		g_nWordsIndex++;//取下一个单词
		if(g_Words[g_nWordsIndex].eType==IDENTIFIER)//"procedure"后应为标识符
		{
			PrintInParsing(g_nWordsIndex,nIndentNum,"IDENTIFIER");//打印调试信息
			g_nWordsIndex++;//取下一个单词
		}
		else
			return ERROR;

		if(g_Words[g_nWordsIndex].eType==SEMICOLON)//标识符后应是分号';'
		{
			PrintInParsing(g_nWordsIndex,nIndentNum,";");//打印调试信息
			g_nWordsIndex++;//取下一个单词
		}
		else
			return ERROR;//漏掉了分号

		PrintInParsing(g_nWordsIndex,nIndentNum,"BlockParsing");//打印调试信息
		BlockParsing(nIndentNum+1);//在"函数定义"中,分号后面是"分程序"Block

		if(g_Words[g_nWordsIndex].eType==SEMICOLON)//"分程序"Block后面应是分号';'
		{
			PrintInParsing(g_nWordsIndex,nIndentNum,";");//打印调试信息
			g_nWordsIndex++;//取下一个单词
		}
		else
			return ERROR;//漏掉了分号
	}
	
	PrintInParsing(g_nWordsIndex,nIndentNum,"StatementParsing");//打印调试信息
	StatementParsing(nIndentNum+1);//"分程序"Block中必须有"语句"

	return OK;
}
//一个"常量声明"语法分析
int OneConstantParsing(int nIndentNum)//nIndentNum是打印时要缩进的空格数
{
	if(g_Words[g_nWordsIndex].eType==IDENTIFIER)//一个常量声明以标识符开头
	{
		PrintInParsing(g_nWordsIndex,nIndentNum,"IDENTIFIER");//打印调试信息

		g_nWordsIndex++;//取下一个单词
		if(g_Words[g_nWordsIndex].eType==EQL)//标识符后面应是'='
		{
			PrintInParsing(g_nWordsIndex,nIndentNum,"EQL");//打印调试信息

			g_nWordsIndex++;//取下一个单词
			if(g_Words[g_nWordsIndex].eType==NUMBER)//'='后面的单词应是数
			{
				PrintInParsing(g_nWordsIndex,nIndentNum,"NUMBER");//打印调试信息

				g_nWordsIndex++;//取下一个单词
				return OK;
			}
			if (g_Words[g_nWordsIndex].eType == FLOAT)//'='后面的单词应是数
			{
				PrintInParsing(g_nWordsIndex, nIndentNum, "FLOAT");//打印调试信息

				g_nWordsIndex++;//取下一个单词
				return OK;
			}
            else
				return ERROR;
		}
		else
			return ERROR;
	}
	else
		return ERROR;

	return ERROR;
}
//一个"变量声明"语法分析
int OneVariableParsing(int nIndentNum)//nIndentNum是打印时要缩进的空格数
{
	if(g_Words[g_nWordsIndex].eType==IDENTIFIER)//一个变量声明就是标识符
	{
		PrintInParsing(g_nWordsIndex,nIndentNum,"IDENTIFIER");//打印调试信息
		g_nWordsIndex++;//取下一个单词

		return OK;
	}
	else
		return ERROR;

	return ERROR;
}
//一条"语句"语法分析
int StatementParsing(int nIndentNum)//nIndentNum是打印时要缩进的空格数
{
	int		nResult;

	switch(g_Words[g_nWordsIndex].eType)//当前单词类型是
	{
	case IDENTIFIER://如果第一个单词是标识符,应按照"赋值语句"处理
				PrintInParsing(g_nWordsIndex,nIndentNum,"IDENTIFIER");//打印调试信息

				g_nWordsIndex++;//取下一个单词
				if(g_Words[g_nWordsIndex].eType==ASSIGN)//标识符后面应是赋值号单词":="
				{
					PrintInParsing(g_nWordsIndex,nIndentNum,"ASSIGN");//打印调试信息

					g_nWordsIndex++;//取下一个单词
					PrintInParsing(g_nWordsIndex,nIndentNum,"ExpressionParsing");//打印调试信息
					nResult=ExpressionParsing(nIndentNum+1);//赋值号单词":="后面应是表达式

					return nResult;
				}
				else
					return ERROR;//没有检测到':='符号
				if (g_Words[g_nWordsIndex].eType == SEMICOLON) // 分号';'，赋值语句结束
				{
					PrintInParsing(g_nWordsIndex, nIndentNum, (char*)";");
					g_nWordsIndex++;
					return nResult;  	// 若前面都分析成功，返回 nResult值为OK
				}
				else
					return ERROR;
				break;

	case IF://如果第一个单词是"if",按"条件语句"处理
				/*PrintInParsing(g_nWordsIndex,nIndentNum,"IF");//打印调试信息

				g_nWordsIndex++;//取下一个单词
				PrintInParsing(g_nWordsIndex,nIndentNum,"ConditionParsing");//打印调试信息
				ConditionParsing(nIndentNum+1);//"if"后是"条件"Condition

				if(g_Words[g_nWordsIndex].eType==THEN)//"条件"后应有"then"
				{
					PrintInParsing(g_nWordsIndex,nIndentNum,"THEN");//打印调试信息

					g_nWordsIndex++;//取下一个单词
					PrintInParsing(g_nWordsIndex,nIndentNum,"StatementParsing");//打印调试信息
					nResult=StatementParsing(nIndentNum+1);//"then"后应是"语句"

					return nResult;
				}
				else
					return ERROR;//缺少then

				break; */ 
				PrintInParsing(g_nWordsIndex, nIndentNum, (char*)"IF");
				g_nWordsIndex++;
				if (g_Words[g_nWordsIndex].eType == LEFT_PARENTHESIS)  // if +左括号'('
				{
					PrintInParsing(g_nWordsIndex, nIndentNum, (char*)"LEFT_PARENTHESIS");
					g_nWordsIndex++;
					PrintInParsing(g_nWordsIndex, nIndentNum, (char*)"ConditionParsing");
					ConditionParsing(nIndentNum + 1);     //  if + '(' + 条件Condition

					if (g_Words[g_nWordsIndex].eType == RIGHT_PARENTHESIS)
					{								//  + ')'，表示括号中的条件结束
						PrintInParsing(g_nWordsIndex, nIndentNum, (char*)"RIGHT_PARENTHESIS");
						g_nWordsIndex++;
					}
					else
					{
						printf("缺少右括号！");
						return ERROR;   // 缺少 ')'
					}
					PrintInParsing(g_nWordsIndex, nIndentNum, (char*)"StatementParsing");
					nResult = StatementParsing(nIndentNum + 1);  //  ')' 结束以后 + 语句

					if (g_Words[g_nWordsIndex].eType == ELSE) 	//  +  else 
					{
						PrintInParsing(g_nWordsIndex, nIndentNum, (char*)"ELSE");
						g_nWordsIndex++;
						PrintInParsing(g_nWordsIndex, nIndentNum, (char*)"StatementParsing");
						nResult = StatementParsing(nIndentNum + 1);  // else结束以后 + 语句
					}

					return nResult;
				}
				else
				{
					printf("缺少左括号！");
					return ERROR;   //  缺少 '('
				}
				break;
	case FOR:
		PrintInParsing(g_nWordsIndex, nIndentNum, (char*)"FOR");
		g_nWordsIndex++;
		if (g_Words[g_nWordsIndex].eType == LEFT_PARENTHESIS) // for +左括号'('
		{
			PrintInParsing(g_nWordsIndex, nIndentNum, (char*)"LEFT_PARENTHESIS");
			g_nWordsIndex++;
			if (g_Words[g_nWordsIndex].eType == IDENTIFIER)
			{	//  <赋值语句> (标识符 := 表达式)，可省略
				PrintInParsing(g_nWordsIndex, nIndentNum, (char*)"IDENTIFIER");
				g_nWordsIndex++;
				if (g_Words[g_nWordsIndex].eType == ASSIGN)  //  + ":="
				{
					PrintInParsing(g_nWordsIndex, nIndentNum, (char*)"ASSIGN");
					g_nWordsIndex++;
					PrintInParsing(g_nWordsIndex, nIndentNum, (char*)"ExpressionParsing");
					ExpressionParsing(nIndentNum + 1);    //  + 表达式
				}
				else
					return ERROR;
			}

			if (g_Words[g_nWordsIndex].eType == SEMICOLON)   // + 分号';'
			{
				PrintInParsing(g_nWordsIndex, nIndentNum, (char*)";");
				g_nWordsIndex++;
			}
			else
				return ERROR;

			PrintInParsing(g_nWordsIndex, nIndentNum, (char*)"ConditionParsing");
			ConditionParsing(nIndentNum + 1);	// <条件语句>

			if (g_Words[g_nWordsIndex].eType == SEMICOLON)   // + 分号';'
			{
				PrintInParsing(g_nWordsIndex, nIndentNum, (char*)";");
				g_nWordsIndex++;
			}
			else
				return ERROR;

			if (g_Words[g_nWordsIndex].eType == IDENTIFIER) {	//  <赋值语句> (标识符 := 表达式)，可省略
				PrintInParsing(g_nWordsIndex, nIndentNum, (char*)"IDENTIFIER");
				g_nWordsIndex++;
				if (g_Words[g_nWordsIndex].eType == ASSIGN)  //  + ":="
				{
					PrintInParsing(g_nWordsIndex, nIndentNum, (char*)"ASSIGN");
					g_nWordsIndex++;
					PrintInParsing(g_nWordsIndex, nIndentNum, (char*)"ExpressionParsing");
					ExpressionParsing(nIndentNum + 1);    //  + 表达式
				}
				else
					return ERROR;
			}

			if (g_Words[g_nWordsIndex].eType == RIGHT_PARENTHESIS)
			{	//  + ')'，for()括号中的三个语句结束
				PrintInParsing(g_nWordsIndex, nIndentNum, (char*)"RIGHT_PARENTHESIS");
				g_nWordsIndex++;
			}
			else
				return ERROR;   // 缺少 ')'

			PrintInParsing(g_nWordsIndex, nIndentNum, (char*)"StatementParsing");
			nResult = StatementParsing(nIndentNum + 1);	// for( ; ; ) 结束后 + 语句
			return nResult;
		}
		else
			return ERROR;   //  缺少 '('
		break;
	case WHILE://如果第一个单词是"while",准备按照"循环语句"处理
				PrintInParsing(g_nWordsIndex,nIndentNum,"WHILE");//打印调试信息

				g_nWordsIndex++;//取下一个单词

				PrintInParsing(g_nWordsIndex,nIndentNum,"ConditionParsing");//打印调试信息
				ConditionParsing(nIndentNum+1);//"while"后面应是"条件"

				if(g_Words[g_nWordsIndex].eType==DO)//"条件"后面应是单词"do"
				{
					PrintInParsing(g_nWordsIndex,nIndentNum,"DO");//打印调试信息

					g_nWordsIndex++;//取下一个单词

					PrintInParsing(g_nWordsIndex,nIndentNum,"StatementParsing");//打印调试信息
					nResult=StatementParsing(nIndentNum+1);//"do"后面应是"一条语句"

					return nResult;
				}
				else
					return ERROR;//缺少do

				break;

	case BEGIN://如果第一个单词是"begin",准备按照"复合语句"处理
				PrintInParsing(g_nWordsIndex,nIndentNum,"BEGIN");//打印调试信息

				g_nWordsIndex++;//取下一个单词

				PrintInParsing(g_nWordsIndex,nIndentNum,"StatementParsing");//打印调试信息
				StatementParsing(nIndentNum+1);//"begin"后面应是一条语句

				while(g_Words[g_nWordsIndex].eType==SEMICOLON)//只要语句后面还有';'
				{
					PrintInParsing(g_nWordsIndex,nIndentNum,";");//打印调试信息

					g_nWordsIndex++;//取下一个单词

					PrintInParsing(g_nWordsIndex,nIndentNum,"StatementParsing");//打印调试信息
					StatementParsing(nIndentNum+1);//";"后面应是"一条语句"
                }

				if(g_Words[g_nWordsIndex].eType==END)//复合语句最后必须是"end"
				{
					PrintInParsing(g_nWordsIndex,nIndentNum,"END");//打印调试信息

					g_nWordsIndex++;//取下一个单词
					return OK;
				}
				else
					return ERROR;//缺少end或分号

				break;

	case READ://如果第一个单词是"read",准备按照"读语句"处理
				PrintInParsing(g_nWordsIndex,nIndentNum,"READ");//打印调试信息

				g_nWordsIndex++;//取下一个单词
				if(g_Words[g_nWordsIndex].eType==LEFT_PARENTHESIS)//"read"后面应是左括号'('
				{
					PrintInParsing(g_nWordsIndex,nIndentNum,"LEFT_PARENTHESIS");//打印调试信息
					do{//一条"读语句"应至少有一个变量标识符
						g_nWordsIndex++;//取下一个单词

						if(g_Words[g_nWordsIndex].eType==IDENTIFIER)//后面应是一个标识符
						{
							PrintInParsing(g_nWordsIndex,nIndentNum,"IDENTIFIER");//打印调试信息
							g_nWordsIndex++;//取下一个单词
						}
						else
							return ERROR;//格式错误,

						if(g_Words[g_nWordsIndex].eType==COMMA)//打印调试信息
							PrintInParsing(g_nWordsIndex,nIndentNum,"COMMA");
					}while(g_Words[g_nWordsIndex].eType==COMMA);//如果标识符后面还有一个逗号','

					if(g_Words[g_nWordsIndex].eType==RIGHT_PARENTHESIS)//最后应是右括号')'
					{
						PrintInParsing(g_nWordsIndex,nIndentNum,"RIGHT_PARENTHESIS");//打印调试信息
						g_nWordsIndex++;//取下一个单词
						return OK;
					}
					else
						return ERROR;//格式错误,应是右括号
				}
				else
					return ERROR;//格式错误,应是左括号

				break;

	case WRITE://如果第一个单词是"write",准备按照"写语句"处理
				PrintInParsing(g_nWordsIndex,nIndentNum,"WRITE");//打印调试信息

				g_nWordsIndex++;//取下一个单词
				if(g_Words[g_nWordsIndex].eType==LEFT_PARENTHESIS)//"write"后面应是左括号'('
				{
					PrintInParsing(g_nWordsIndex,nIndentNum,"(");//打印调试信息

					do{//一条"写语句"应至少有一个或多个变量标识符
						g_nWordsIndex++;//取下一个单词
						if(g_Words[g_nWordsIndex].eType==IDENTIFIER)//后面应是一个标识符
						{
							PrintInParsing(g_nWordsIndex,nIndentNum,"IDENTIFIER");//打印调试信息
							g_nWordsIndex++;//取下一个单词
						}
						else
							return ERROR;//格式错误,

						if(g_Words[g_nWordsIndex].eType==COMMA)//打印调试信息
							PrintInParsing(g_nWordsIndex,nIndentNum,"COMMA");
					}while(g_Words[g_nWordsIndex].eType==COMMA);//如果标识符后面有一个逗号','

					if(g_Words[g_nWordsIndex].eType==RIGHT_PARENTHESIS)//最后应是右括号')'
					{
						PrintInParsing(g_nWordsIndex,nIndentNum,")");//打印调试信息

						g_nWordsIndex++;//取下一个单词
						return OK;
					}
					else
						return ERROR;//格式错误,应是右括号
				}
				else
					return ERROR;//格式错误,应是左括号

				break;

	case CALL://如果第一个单词是"call",准备按照"调用函数语句"处理
				PrintInParsing(g_nWordsIndex,nIndentNum,"CALL");//打印调试信息

				g_nWordsIndex++;//取下一个单词
				if(g_Words[g_nWordsIndex].eType==IDENTIFIER)//"call"后面应是一个标识符,过程名
				{
					PrintInParsing(g_nWordsIndex,nIndentNum,"IDENTIFIER");//打印调试信息

					g_nWordsIndex++;//取下一个单词
					return OK;
				}
				else
					return ERROR;

				break;
	case SL_COMMENT:
				PrintInParsing(g_nWordsIndex, nIndentNum, "SL_COMMENT");//打印调试信息
				g_nWordsIndex++;//取下一个单词
				break;
	default:	return ERROR;
	}

	return ERROR;
}
//"条件"语法分析
int ConditionParsing(int nIndentNum)//nIndentNum是打印时要缩进的空格数
{
	if(g_Words[g_nWordsIndex].eType==ODD)//如果有"odd"单词
	{
		PrintInParsing(g_nWordsIndex,nIndentNum,"ODD");//打印调试信息

		g_nWordsIndex++;//取下一个单词

		PrintInParsing(g_nWordsIndex,nIndentNum,"ExpressionParsing");//打印调试信息
		ExpressionParsing(nIndentNum+1);//"odd"单词后面应有一个"表达式"
	}
	else
	{
		PrintInParsing(g_nWordsIndex,nIndentNum,"ExpressionParsing");//打印调试信息
		ExpressionParsing(nIndentNum+1);//条件可以是一个"表达式"

		if(		g_Words[g_nWordsIndex].eType==EQL		//如果后面有逻辑运算符
			||	g_Words[g_nWordsIndex].eType==NEQ
			||	g_Words[g_nWordsIndex].eType==LES 
			||	g_Words[g_nWordsIndex].eType==LEQ
			||	g_Words[g_nWordsIndex].eType==GTR
			||	g_Words[g_nWordsIndex].eType==GEQ)
		{
			PrintInParsing(g_nWordsIndex,nIndentNum,"LOGICAL_OP");//打印调试信息

			g_nWordsIndex++;//取下一个单词
			PrintInParsing(g_nWordsIndex,nIndentNum,"ExpressionParsing");//打印调试信息
			ExpressionParsing(nIndentNum+1);//则继续处理后面第二个"表达式"
		}
		else
			return ERROR;//缺少右括号
	}
	return OK;
}
//"表达式"语法分析
int ExpressionParsing(int nIndentNum)//nIndentNum是打印时要缩进的空格数
{
	if(g_Words[g_nWordsIndex].eType==PLUS || g_Words[g_nWordsIndex].eType==MINUS)
	{//如果开头有正负号,则此时表达式应被看作一个正的或负的项
		PrintInParsing(g_nWordsIndex,nIndentNum,"PLUS/MINUS");//打印调试信息
		g_nWordsIndex++;//取下一个单词
	}

	PrintInParsing(g_nWordsIndex,nIndentNum,"TermParsing");//打印调试信息
	TermParsing(nIndentNum+1);//表达式可以是一个"项"

	while(g_Words[g_nWordsIndex].eType==PLUS || g_Words[g_nWordsIndex].eType==MINUS)
	{//如果"项"后面还有'+'或'-'
		PrintInParsing(g_nWordsIndex,nIndentNum,"PLUS/MINUS");//打印调试信息

		g_nWordsIndex++;//取下一个单词
		PrintInParsing(g_nWordsIndex,nIndentNum,"TermParsing");//打印调试信息
		TermParsing(nIndentNum+1);//则后面还有"项"
	}
	return OK;
}
//"项"语法分析
int TermParsing(int nIndentNum)//nIndentNum是打印时要缩进的空格数
{
	PrintInParsing(g_nWordsIndex,nIndentNum,"FactorParsing");//打印调试信息
	FactorParsing(nIndentNum+1);//"项"可以是一个"因子"

	while(g_Words[g_nWordsIndex].eType==MULTIPLY || g_Words[g_nWordsIndex].eType==DIVIDE)
	{//如果"因子"后面还有单词'*'或'/'
		PrintInParsing(g_nWordsIndex,nIndentNum,"MULTI/DIVISION");//打印调试信息

		g_nWordsIndex++;//取下一个单词
		PrintInParsing(g_nWordsIndex,nIndentNum,"FactorParsing");//打印调试信息
		FactorParsing(nIndentNum+1);//则后面还有"因子"
	}
	return OK;
}
//"因子"语法分析
int FactorParsing(int nIndentNum)
{
	switch(g_Words[g_nWordsIndex].eType)
	{
	case IDENTIFIER://因子可以是一个常量或变量
					PrintInParsing(g_nWordsIndex,nIndentNum,"IDENTIFIER");//打印调试信息

					g_nWordsIndex++;//取下一个单词
					return OK;

	case NUMBER:	//因子可以是一个数
					PrintInParsing(g_nWordsIndex,nIndentNum,"NUMBER");//打印调试信息

					g_nWordsIndex++;//取下一个单词
					return OK;

	case LEFT_PARENTHESIS:	//如果看到左括号'('
					PrintInParsing(g_nWordsIndex,nIndentNum,"(");//打印调试信息

					g_nWordsIndex++;//取下一个单词
					PrintInParsing(g_nWordsIndex,nIndentNum,"ExpressionParsing");//打印调试信息
					ExpressionParsing(nIndentNum+1);//左括号'('后面应是"表达式"

					if(g_Words[g_nWordsIndex].eType==RIGHT_PARENTHESIS)//"表达式"后面应是右括号')'
					{
						PrintInParsing(g_nWordsIndex,nIndentNum,")");//打印调试信息

						g_nWordsIndex++;//取下一个单词
						return OK;
					}
					else
						return ERROR;//缺少右括号
					break;

	default:		return ERROR;
	}
	return OK;
}
void PrintInParsing(int nWordsIndex,int nIndentNum,char *pString)//打印调试信息
{
	int		i;
	char	strText[100];

	printf("%-4d%-4d%-12s",nWordsIndex+1,g_Words[nWordsIndex].nLineNo,g_Words[nWordsIndex].szName);
	printf("%-1s","|");
	for (i=0;i<nIndentNum;i++)
		printf("  ");
	printf("%-1s"," ");

	sprintf(strText,"(%d)%s",nIndentNum,pString);
	printf("%-15s\n",strText);
}
