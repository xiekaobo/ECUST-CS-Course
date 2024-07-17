
#ifndef RUN_PL0_GETSYM_H
#define RUN_PL0_GETSYM_H
#define keywords_num 29
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;


vector<int> integerArray;//整数动态数组
vector<float> realArray;//实数动态数组
vector<string> identifierArray;//标识符动态数组
const string keywords[keywords_num] = 
{ 
	"const",	//0
	"var",		//1
	"procedure", //2
	"begin",	// 3
	"end",		//4
	"odd",		//5			 
	"if",		//6
	"then",		//7
	"call",     //8
	"while",	//9
	"do",		//10
	"read",		//11
	"write",	//12

	"type",
	"array",
	"of",
	"integer",
	"real",
	"Boolean",
	"function",
	"else",
	"exit",
	"or",
	"and",
	"not",
	"div",
	"mod",
	"true",
	"false",


};//关键字
int lineSum = 0; //记录源程序的行数，用于出错处理
//ifstream fcin;   //打开文件NOLINT
char FileBuff[1 * 1 << 20];//文件缓冲区
long long Cur = 0;//读文件的位置

bool IsKey = false;
int SYM_type;//关键字类型，编号
int Int_numValue = 0;//无符号整数的值
float Real_numValue = 0;//实数的值
string id;
//#if DEBUG
string debugId;  //词法分析产生的标识符
string Int_debugNum; //词法分析产生的无符号整数的string形式
int Int_debugNumber; //词法分析产生的无符号整数
string Real_debugNum; //词法分析产生的实数的string形式
float Real_debugNumber; //词法分析产生的实数

//#endif

//符号枚举
enum SYM_class {
	CONST_SYM,     // const
	VAR_SYM,       // var
	PROCEDURE_SYM, // procedure
	BEGIN_SYM,     // begin
	END_SYM,       // end
	ODD_SYM,       // odd
	IF_SYM,        // if
	THEN_SYM,      // then
	CALL_SYM,      // call
	WHILE_SYM,     // while
	DO_SYM,        // do
	READ_SYM,      // read
	WRITE_SYM,     // write

	TYPE_SYM,		//type
	ARRAY_SYM,		//array
	OF_SYM,			//of
	INTEGER_SYM,	//integer
	REAL_SYM,		//real
	BOOLEAN_SYM,	//Boolean
	FUNCTION_SYM,	//function
	ELSE_SYM,		//else
	EXIT_SYM,		//exit
	OR_SYM,			//or
	AND_SYM,		//and
	NOT_SYM,		//not
	INT_DIV_SYM,	//div
	MOD_SYM,		//mod
	TRUE_SYM,		//true
	FALSE_SYM,		//false
	//算符与界符
	ADD_SYM,       // +
	SUB_SYM,       // -
	MULT_SYM,      // *
	DIV_SYM,       // /
	EQUAL_SYM,     // =
	NEQUAL_SYM,    // <>
	LESS_SYM,      // <
	ELESS_SYM,     // <=
	GRE_SYM,       // >
	EGRE_SYM,      // >=
	LEFTP_SYM,     // (
	RIGHTP_SYM,    // )
	DOT_SYM,       // .
	COMMA_SYM,     // ,
	ASSI_SYM,      // :=
	COLON_SYM,      // :，增加
	SEMICOLON_SYM, // ;
	INT_NUM_SYM,	//整数
	REAL_NUM_SYM,	//实数
	//NUM_SYM,       //数字
	IDE_SYM        //标识符
};

//词法分析错误类型
enum ERROR_CODE 
{ 
	TOOLONG,	//太长
	ASSI_ERROR, //赋值错误
	ANOTHER_WORD, //标识符
	WRONG_NUMBER //数错误
};

int insertIdentifier(const string& str) //插入到标识符符号表
{
	int location = 0;
	auto itd = identifierArray.begin();//标识符动态数组的开始
	for (; itd != identifierArray.end(); ++itd) {
		if (*itd == str)
			break;
		location++;
	}
	if (itd == identifierArray.end()) {
		identifierArray.push_back(str);//将新的标识符插入
		return location;//返回标识符所在位置
	}
	else
		return location;//返回标识符所在位置
}

int insertConst(int number) //插入到常数表
{
	int location = 0;
	auto itd = integerArray.begin();//整数动态数组开始
	for (; itd != integerArray.end(); ++itd) {
		if (*itd == number)//已有的整数，结束循环
			break;
		location++;
	}
	if (itd == integerArray.end()) {
		integerArray.push_back(number);//将新的数插入
		return location;//返回整数所在位置
	}
	else
		return location;
}

int insertReal(float number) //插入到实数表
{
	int location = 0;
	auto itd = realArray.begin();//实数动态数组开始
	for (; itd != realArray.end(); ++itd) {
		if (*itd == number)//已有的实数，结束循环
			break;
		location++;
	}
	if (itd == realArray.end()) {
		realArray.push_back(number);//将新的数插入
		return location;//返回实数所在位置
	}
	else
		return location;
}

int error(int ERROR_CODE_TYPE) { // NOLINT
	switch (ERROR_CODE_TYPE) {
	case TOOLONG:
		cout << "Identifier " << id << " in line " << lineSum << " is too long" << endl;
		break;
	case ASSI_ERROR:
		cout << "wrong assignment in line " << lineSum << endl;
		break;
	case ANOTHER_WORD:
		cout << "wrong words in line " << lineSum << endl;
		break;
	case WRONG_NUMBER:
		cout << "wrong number in line " << lineSum << endl;
		break;
	default:
		break;
	}
	return -1;
}

/*template<class T>
void print_result(int sym, T name,  int value)
{
	;
	switch (sym) {
		case NUM_SYM:
			cout << "( number," << name << "," << value << " )" << endl;
			break;
		case IDE_SYM:
			cout << "( identifier," << name << "," << value << " )" << endl;
			break;
		default:
			break;
	}
}*/

/*void print_result(int sym)
{
	;
	switch (sym) {
		case CONST_SYM:
			cout << "( 'const',- )" << endl;
			break;
		case VAR_SYM:
			cout << "( 'var',- )" << endl;
			break;
		case PROCEDURE_SYM:
			cout << "( 'procedure',- )" << endl;
			break;
		case BEGIN_SYM:
			cout << "( 'begin',- )" << endl;
			break;
		case END_SYM:
			cout << "( 'end',- )" << endl;
			break;
		case ODD_SYM:
			cout << "( 'odd',- )" << endl;
			break;
		case IF_SYM:
			cout << "( 'if',- )" << endl;
			break;
		case THEN_SYM:
			cout << "( 'then',- )" << endl;
			break;
		case CALL_SYM:
			cout << "( 'call',- )" << endl;
			break;
		case WHILE_SYM:
			cout << "( 'while',- )" << endl;
			break;
		case DO_SYM:
			cout << "( 'do',- )" << endl;
			break;
		case READ_SYM:
			cout << "( 'read',- )" << endl;
			break;
		case WRITE_SYM:
			cout << "( 'write',- )" << endl;
			break;
		case ADD_SYM:
			cout << "( '+',- )" << endl;
			break;
		case SUB_SYM:
			cout << "( '-',- )" << endl;
			break;
		case MULT_SYM:
			cout << "( '*',- )" << endl;
			break;
		case DIV_SYM:
			cout << "( '/',- )" << endl;
			break;
		case EQUAL_SYM:
			cout << "( '=',- )" << endl;
			break;
		case NEQUAL_SYM:
			cout << "( '#',- )" << endl;
			break;
		case LESS_SYM:
			cout << "( '<',- )" << endl;
			break;
		case ELESS_SYM:
			cout << "( '<=',- )" << endl;
			break;
		case GRE_SYM:
			cout << "( '>',- )" << endl;
			break;
		case EGRE_SYM:
			cout << "( '>=',- )" << endl;
			break;
		case LEFTP_SYM:
			cout << "( '(',- )" << endl;
			break;
		case RIGHTP_SYM:
			cout << "( ')',- )" << endl;
			break;
		case DOT_SYM:
			cout << "( '.',- )" << endl;
			break;
		case COMMA_SYM:
			cout << "( ',',- )" << endl;
			break;
		case ASSI_SYM:
			cout << "( ':=',- )" << endl;
			break;
		case SEMICOLON_SYM:
			cout << "( ';',- )" << endl;
			break;
		default:
			break;
	}
}*/

string GETSYM() {
	IsKey = false;//初始化为false
	string strToken; //存放构成单词的字符串
	strToken = "";
	char ch; //存放最新读进的源程序字符
	ch = FileBuff[Cur]; Cur++;
	while (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r') {
		if (ch == '\n')
			lineSum++;//遇到换行符，行数加1
		ch = FileBuff[Cur]; Cur++;
	} //过滤空格、tab、换行符，并对换行符进行统计，以便于定位出错位置。
	while (ch == '/') {//增加注释,调整位置，改为循环，可以连续多行注释
		ch = FileBuff[Cur]; Cur++;
		if (ch == '/') {
			ch = FileBuff[Cur]; Cur++;
			while (ch != '\n') {//不是换行符就一直读入，不处理
				ch = FileBuff[Cur]; Cur++;
			}
			lineSum++;//遇到换行符，行数加1
			
			ch = FileBuff[Cur]; Cur++;
			while (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r') {
				if (ch == '\n')
					lineSum++;//遇到换行符，行数加1
				ch = FileBuff[Cur]; Cur++;
			} //过滤空格、tab、换行符，并对换行符进行统计，以便于定位出错位置。
		}
		else if (ch == '*') {
			ch = FileBuff[Cur]; Cur++;
			while ( FileBuff[Cur-2] != '*'||ch != '/') {//没有遇到*/则循环Cur-2的位置才是*
				if (ch == '\n')
					lineSum++;//遇到换行符，行数加1
				ch = FileBuff[Cur]; Cur++;
			}

			ch = FileBuff[Cur]; Cur++;
			while (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r') {
				if (ch == '\n')
					lineSum++;//遇到换行符，行数加1
				ch = FileBuff[Cur]; Cur++;
			} //过滤空格、tab、换行符，并对换行符进行统计，以便于定位出错位置。
		}
		else {
			Cur--;
			SYM_type = DIV_SYM;
			// print_result(SYM_type);
			return "/";
		}

	}
	if (ch == EOF) {
		return "finish";
	}
	if (isalpha(ch)) { // ch是字母，则单词可能是标识符或者关键字
		do {
			strToken += ch;
			ch = FileBuff[Cur]; 
			Cur++;
		} while (isalpha(ch) || isdigit(ch));
		id = strToken;
		if (id.size() > 10) { //关键词与标识符的大小限制为10
			error(TOOLONG);//报错
			return "error";
		}
		for (int i = 0; i < keywords_num; ++i) //查找是否属于关键字
			if (id == keywords[i]) {
				IsKey = true;
				SYM_type = i;
				break;
			}
		if (IsKey) { //关键字的输出
			;        // print_result(SYM_type);
		}
		else {     //标识符的输出
			SYM_type = IDE_SYM;
			insertIdentifier(id);
			// print_result<string>(SYM_type, id, insertIdentifier(id));
			//#if DEBUG
			debugId = id;
			//#endif
			id = "identifier";
		}
		Cur--;//回退多读字符
		return id;
	}
	else if (isdigit(ch)) {//整数和实数分析
		int count = 0;
		float real = 0;
		do {
			strToken += ch;//数字符
			count = count * 10 + ch - '0';//数值
			ch = FileBuff[Cur]; 
			Cur++;//读取位置向前移
		} while (isdigit(ch));
		SYM_type = INT_NUM_SYM;//单词类型设为整数类型
		//增加实数词法分析
		if (ch == '.') {
			strToken += ch;//加点
			ch = FileBuff[Cur];
			Cur++;//指到下一个字符
			real = (float)count;
			int i = 0;//用于记录小数点后的位数
			float add_num;
			while (isdigit(ch)) {//小数点之后的字符
				i++;
				strToken += ch;//实数字符
				add_num = ch - '0';
				for (int j = 0; j < i; j++) {
					add_num /= 10;
				}
				real += add_num;//实数值
				ch = FileBuff[Cur];
				Cur++;//读取位置向前移
			}
			SYM_type = REAL_NUM_SYM;//标记实数类型
		}
		if (isalpha(ch)) {
			error(WRONG_NUMBER);//数后面跟字符，错误数字，报错
			return "error";
		}
		if (SYM_type == REAL_NUM_SYM) {
			Real_numValue = real;
			Cur--;
			insertReal(Real_numValue);
			Real_debugNum = strToken;
			Real_debugNumber = Real_numValue;
			return "real_number";
		}
		else if(SYM_type==INT_NUM_SYM){
			Int_numValue = count;
			Cur--;
			insertConst(Int_numValue);//插入到常数表中
			// print_result<int>(SYM_type, Int_numValue, insertConst(Int_numValue));
			//#if DEBUG
			Int_debugNum = strToken;
			Int_debugNumber = Int_numValue;
			//#endif
			return "int_number";
		}
		
	}
	else if (ch == '+') {
		SYM_type = ADD_SYM;
		// print_result(SYM_type);
		return "+";
	}
	else if (ch == '-') {
		SYM_type = SUB_SYM;
		// print_result(SYM_type);
		return "-";
	}
	else if (ch == '*') {
		SYM_type = MULT_SYM;
		// print_result(SYM_type);
		return "*";
	}
	else if (ch == '=') {
		SYM_type = EQUAL_SYM;
		// print_result(SYM_type);
		return "=";
	}
	else if (ch == '<') {
		ch = FileBuff[Cur]; Cur++;
		if (ch == '=') {
			SYM_type = ELESS_SYM;
			// print_result(SYM_type);
			return "<=";
		}
		else if (ch == '>') {
			SYM_type = NEQUAL_SYM;
			return "<>";
		}
		else {
			SYM_type = LESS_SYM;
			// print_result(SYM_type);
			Cur--;

			return "<";
		}
	}
	else if (ch == '>') {
		ch = FileBuff[Cur]; Cur++;
		if (ch == '=') {
			SYM_type = EGRE_SYM;
			// print_result(SYM_type);
			return ">=";
		}
		else {
			SYM_type = GRE_SYM;
			// print_result(SYM_type);
			Cur--;

			return ">";
		}
	}
	else if (ch == '(') {
		SYM_type = LEFTP_SYM;
		// print_result(SYM_type);
		return "(";
	}
	else if (ch == ')') {
		SYM_type = RIGHTP_SYM;
		// print_result(SYM_type);
		return ")";
	}
	else if (ch == '.') {
		SYM_type = DOT_SYM;
		// print_result(SYM_type);
		return ".";
	}
	else if (ch == ',') {
		SYM_type = COMMA_SYM;
		// print_result(SYM_type);
		return ",";
	}
	else if (ch == ':') {//添加‘:’单词
		ch = FileBuff[Cur]; Cur++;
		if (ch == '=') {
			SYM_type = ASSI_SYM;
			// print_result(SYM_type);
			return ":=";
		}
		else {//
			SYM_type = COLON_SYM;
			Cur--;
			return ":";
			/*error(ASSI_ERROR);
			return "error_assi_error";*/
		}
	}
	else if (ch == ';') {
		SYM_type = SEMICOLON_SYM;
		// print_result(SYM_type);
		return ";";
	}
	else if (ch == '%') {
		SYM_type = MOD_SYM;
		// print_result(SYM_type);
		return "%";
	}
	else {
		error(ANOTHER_WORD);
		return "error";
	}
	return nullptr;
}

#endif // RUN_PL0_GETSYM_H
