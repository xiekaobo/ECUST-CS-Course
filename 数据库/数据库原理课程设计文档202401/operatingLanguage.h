//数据库操作
//连接 / 切换数据库： use <数据库名称>;		//无则创建,有则使用
//删除数据库 ：		  db.dropDatabase();		//请首先确保正在使用该数据库。
//展示数据库所有信息：db.showDatabase(); //请首先确保正在使用该数据库。
//
//集合操作
//创建集合db.createCollection("<集合名称>");
//删除集合db.deleteCollection("<集合名称>");
//查询集合db.inquiryCollection("<集合名称>");
//展示集合db.showCollection("<集合名称>");
//
//文档操作
//创建文档db.<集合名称>.createDocument("<文档名称>", "<文档内容>”);
//删除文档db.<集合名称>.deleteDocument("<文档名称>");
//修改文档db.<集合名称>.updateDocument("<文档名称>", "<文档内容>”);
//查询文档db.<集合名称>.inquiryDocument("<文档名称>");
//展示文档db.<集合名称>.showDocument("<文档名称>");

#include"dataStructure.h"

using namespace std;

vector<char> instruction;	//操作指令
int index = 0;				//指令索引
int sym;					//单词类型
string id;					//标识符
float num_f;				//实数数值

//符号枚举
enum sym_Type {
	IDENT,      //标识符
	NUM_REAL,	//实数
	ERR,		//错误
	DOT,		//小数点
	LEFTP,		//左括号
	RIGHTP,		//右括号
	QUOTATION,	//引号
	SEMICOLON,	//分号
	COMMA,		//逗号
};

//获取字符
char getch() {
	if (index == instruction.size()) return EOF;
	return instruction[index++];
}

//获取单词
int getsym() {
	string nowSym = "";
	char ch = getch();
	while (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r') {
		ch = getch();
	} //过滤空格、制表符、换行符、回车符
	if (ch == EOF) {
		sym = EOF;
		return sym;
	}
	else if (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z') {//开头是字母
		do {
			nowSym += ch;
			ch = getch();
		} while (((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9')) && ch != EOF);
		index--;
		if (ch != EOF) {
			sym = IDENT;
			id = nowSym;
			return sym;
		}
		else {
			sym = ERR;
			return sym;
		}
	}
	//开头是数字
	else if (ch >= '0' && ch <= '9') {
		int integer = 0;
		float real = 0;
		do {
			nowSym += ch;
			integer = 10 * integer + ch - '0';
			ch = getch();
		} while ((ch >= '0' && ch <= '9') && ch != EOF);//获取完整数值(获取小数点前整数)
		if (ch != EOF) {
			if (ch == '.') {//数值后是小数点
				ch = getch();//检查小数点后一位字符
				if (ch >= '0' && ch <= '9') {//小数点后是数字，确定为实数
					nowSym += '.';
					real = (float)integer;
					float k = 1;//小数位
					do {
						nowSym += ch;
						k /= 10;
						real += k * (ch - '0');
						ch = getch();
					} while ((ch >= '0' && ch <= '9') && ch != EOF);//获取完整小数部分
					index--;
					if (ch != EOF) {
						sym = NUM_REAL;//单词类型为实数
						num_f = real;
						return sym;
					}
					else {
						sym = ERR;
						return sym;
					}
				}
				else {
					sym = ERR;
					return sym;
				}
			}
			else {
				index--;
				sym = NUM_REAL;
				num_f = float(integer);
				return sym;
			}
		}
		else {
			sym = ERR;
			return sym;
		}
	}
	else if (ch == '.') {
		sym = DOT;
		id = ".";
		return sym;
	}
	else if (ch == '(') {
		sym = LEFTP;
		id = "(";
		return sym;
	}
	else if (ch == ')') {
		sym = RIGHTP;
		id = ")";
		return sym;
	}
	else if (ch == '"') {
		sym = QUOTATION;
		id = "\"";
		return sym;
	}
	else if (ch == ';') {
		sym = SEMICOLON;
		id = ";";
		return sym;
	}
	else if (ch == ',') {
		sym = COMMA;
		id = ",";
		return sym;
	}
	else {
		sym = -1;
		return sym;
	}
	return EOF;
}

//数据库操作
void useDatabase();			//连接/切换数据库
void dropDatabase();		//删除数据库
void showDatabase();		//展示数据库

//集合操作
void createCollection();	//创建集合
void deleteCollection();	//删除集合
void inquiryCollection();	//查询集合
void showCollection();		//展示集合

//文档操作
void createDocument();		//创建文档
void deleteDocument();		//删除文档
void updateDocument();		//修改文档
void inquiryDocument();		//查询文档
void showDocument();		//展示文档

//错误处理
void errorSolution() {
	cout << "命令错误" << endl;
}

string tempCol;//记录指令中的集合名称

//指令识别
void identifyInstruction() {
	index = 0;
	if (getsym() == IDENT) {
		if (id == "use")
			useDatabase();
		else if (id == "db") {
			if (getsym() == DOT && getsym() == IDENT) {
				tempCol = id;
				if (id == "dropDatabase")
					dropDatabase();
				else if (id == "showDatabase")
					showDatabase();
				else if (id == "createCollection")
					createCollection();
				else if (id == "deleteCollection")
					deleteCollection();
				else if (id == "inquiryCollection")
					inquiryCollection();
				else if (id == "showCollection")
					showCollection();
				else if (getsym() == DOT && getsym() == IDENT) {
					if (id == "createDocument")
						createDocument();
					else if (id == "deleteDocument")
						deleteDocument();
					else if (id == "updateDocument")
						updateDocument();
					else if (id == "inquiryDocument")
						inquiryDocument();
					else if (id == "showDocument")
						showDocument();
					else
						errorSolution();
				}
				else
					errorSolution();
			}
			else
				errorSolution();
		}
		else
			errorSolution();
	}
	else
		errorSolution();
}

void useDatabase() {
	string temp;
	if (getsym() == IDENT) {
		temp = id;
		if (getsym() == SEMICOLON) {
			user_now.insertDatabase(temp);
			databasePath = userPath / temp;
			cout << "数据库切换成功,当前数据库路径："<< databasePath << endl;
		}
	}
	else
		errorSolution();
}


void dropDatabase() {
	if (getsym() == LEFTP && getsym() == RIGHTP && getsym() == SEMICOLON) {
		if (databasePath != userPath) {
			user_now.deleteDatabase(databasePath.filename().string());
			databasePath = userPath;
		}
		else
			errorSolution();
	}
	else
		errorSolution();
};

void showDatabase() {
	if (getsym() == LEFTP && getsym() == RIGHTP && getsym() == SEMICOLON) {
		if (databasePath != userPath) {
			user_now.findDatabase(databasePath.filename().string())->showDatabase();
		}
		else
			errorSolution();
	}
	else
		errorSolution();
};

void createCollection() {
	if (getsym() == LEFTP && getsym() == QUOTATION && getsym() == IDENT) {
		string temp = id;
		if (getsym() == QUOTATION && getsym() == RIGHTP && getsym() == SEMICOLON) {
			if (databasePath != userPath) {
				user_now.findDatabase(databasePath.filename().string())->insertCollection(temp);
			}
			else
				errorSolution();
		}else
			errorSolution();
	}
	else
		errorSolution();
};

void deleteCollection() {
	if (getsym() == LEFTP && getsym() == QUOTATION && getsym() == IDENT) {
		string temp = id;
		if (getsym() == QUOTATION && getsym() == RIGHTP && getsym() == SEMICOLON) {
			if (databasePath != userPath) {
				user_now.findDatabase(databasePath.filename().string())->deleteCollection(temp);
			}
			else
				errorSolution();
		}
		else
			errorSolution();
	}
	else
		errorSolution();
};

void inquiryCollection() {
	if (getsym() == LEFTP && getsym() == QUOTATION && getsym() == IDENT) {
		string temp = id;
		if (getsym() == QUOTATION && getsym() == RIGHTP && getsym() == SEMICOLON) {
			if (databasePath != userPath) {
				user_now.findDatabase(databasePath.filename().string())->findCollection(temp);
			}
			else
				errorSolution();
		}
		else
			errorSolution();
	}
	else
		errorSolution();
};

void showCollection() {
	if (getsym() == LEFTP && getsym() == QUOTATION && getsym() == IDENT) {
		string temp = id;
		if (getsym() == QUOTATION && getsym() == RIGHTP && getsym() == SEMICOLON) {
			if (databasePath != userPath) {
				user_now.findDatabase(databasePath.filename().string())->findCollection(temp)->showCollection();
			}
			else
				errorSolution();
		}
		else
			errorSolution();
	}
	else
		errorSolution();
};

void createDocument() {
	if (getsym() == LEFTP && getsym() == QUOTATION && getsym() == IDENT) {
		Document tempDuc = Document();
		tempDuc.document_name = id+".txt";
		if (getsym() == QUOTATION && getsym() == COMMA && getsym() == QUOTATION && getsym() == IDENT) {
			tempDuc.content = id;
			if (getsym() == QUOTATION && getsym() == RIGHTP && getsym() == SEMICOLON) {
				if (databasePath != userPath) {
					user_now.findDatabase(databasePath.filename().string())->findCollection(tempCol)->insertDocument(tempDuc);
				}
				else
					errorSolution();
			}
			else
				errorSolution();
		}
		else
			errorSolution();
	}
	else
		errorSolution();
};


void deleteDocument() {
	if (getsym() == LEFTP && getsym() == QUOTATION && getsym() == IDENT) {
		string temp = id + ".txt";
		if (getsym() == QUOTATION && getsym() == RIGHTP && getsym() == SEMICOLON) {
			if (databasePath != userPath) {
				user_now.findDatabase(databasePath.filename().string())->findCollection(tempCol)->deleteDocument(temp);
			}
			else
				errorSolution();
		}
		else
			errorSolution();
	}
	else
		errorSolution();
};

void updateDocument() {
	if (getsym() == LEFTP && getsym() == QUOTATION && getsym() == IDENT) {
		string tempDuc = id + ".txt";
		if (getsym() == QUOTATION && getsym() == COMMA && getsym() == QUOTATION && getsym() == IDENT) {
			string tempCon = id;
			if (getsym() == QUOTATION && getsym() == RIGHTP && getsym() == SEMICOLON) {
				if (databasePath != userPath) {
					user_now.findDatabase(databasePath.filename().string())->findCollection(tempCol)->updateDocument(tempDuc, tempCon);
				}
				else
					errorSolution();
			}
			else
				errorSolution();
		}
		else
			errorSolution();
	}
	else
		errorSolution();
};

void inquiryDocument() {
	if (getsym() == LEFTP && getsym() == QUOTATION && getsym() == IDENT) {
		string temp = id + ".txt";
		if (getsym() == QUOTATION && getsym() == RIGHTP && getsym() == SEMICOLON) {
			if (databasePath != userPath) {
				user_now.findDatabase(databasePath.filename().string())->findCollection(tempCol)->findDocument(temp);
			}
			else
				errorSolution();
		}
		else
			errorSolution();
	}
	else
		errorSolution();
};

void showDocument() {
	if (getsym() == LEFTP && getsym() == QUOTATION && getsym() == IDENT) {
		string temp = id + ".txt";
		if (getsym() == QUOTATION && getsym() == RIGHTP && getsym() == SEMICOLON) {
			if (databasePath != userPath) {
				user_now.findDatabase(databasePath.filename().string())->findCollection(tempCol)->findDocument(temp)->showDocument();
			}
			else
				errorSolution();
		}
		else
			errorSolution();
	}
	else
		errorSolution();
};