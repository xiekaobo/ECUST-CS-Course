#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <string>
#include <sstream>
#include <iomanip>

#include <direct.h>
#include <io.h>

#include <fstream>

using namespace std;

const int inf = 0x3f3f3f3f;

struct Tables {
	string name;
	string pathName;
	vector<string>colName;//列名称
	vector<string>type;
	vector<int>size;
	FILE* fp;
};

class myDBMS {
	vector<Tables*>tab;
	bool open;
public:
	string cmd;
	string prePath;//数据库的文件路径

	myDBMS() {
		cmd = "";
		prePath = "";
		open = false;
		//建库删库,建表删表,增删改查
		cout << "请按以下规则输入命令语句(命令不分大小写)" << endl;
		cout << "新建数据库: create database 数据库名字" << endl;
		cout << "删除数据库: drop database 数据库名字" << endl;
		cout << "打开数据库: open database 数据库名字" << endl;
		cout << "关闭数据库: close database 数据库名字" << endl;
		cout << "添加新表  : create table  表名" << endl;
		cout << "            (" << endl;
		cout << "            列1(字段)名 数据类型1(大小:若为1可省略)," << endl;
		cout << "            列2(字段)名 数据类型2(大小:若为1可省略)," << endl;
		cout << "            …          …" << endl;
		cout << "            )" << endl;
		cout << "删除旧表  : drop table 表名" << endl;
		cout << "查看全表  : query all from 表名" << endl;
		cout << "查询单值  : query 列名 from 表名 where 列名 = 值(值可为all,表全部范围)" << endl;
		cout << "插入      : insert into 表名(field1,field2,…) values(value1,value2,…)" << endl;
		cout << "修改      : update 列名 = 新值 from 表名 where 列名 = 值(值可为all,表全部范围)" << endl;
		cout << "删除      : delete from 表名 where 列名 = 值(值可为all,表全部范围)" << endl;
		cout << "退出程序  : exit" << endl;
	}
	~myDBMS() {
		for (int i = 0; i < tab.size(); i++) {
			if (tab[i]->fp != NULL)
				fclose(tab[i]->fp);
			delete tab[i];
		}
		tab.resize(0);
		cmd = "";
		prePath = "";
	}

	void transfer();//转为小写
	void openDataBase(string);//打开数据库
	void closeDataBase();//关闭数据库
	void myCreateDataBase(string); //建立数据库	
	void myDropDataBase(string); //删除数据库	
	void myCreateTable(string); //创建表
	void myDropTable(string); //删除表
	void myInsert(string, string); //插入数据
	void myDelete(string, string); //删除数据
	void myUpdate(string, string, string, string); //更新数据
	void myQuery(string, string, string); //查询数据

	int posIsNos(string);//辅助函数
};

void myDBMS::transfer() {
	for (int i = 0; i < cmd.size(); i++)
		cmd[i] = tolower(cmd[i]);
}

void myDBMS::openDataBase(string dataBaseName) {
	if (open) {
		cout << "请先关闭当前打开的数据库" << endl;
		return;
	}
	string pathName = "C:\\Users\\24208\\Downloads\\数据库原理课程设计文档202401\\数据库原理课程设计文档202401\\" + dataBaseName;
	if (0 != access(pathName.c_str(), 0))printf("该数据库不存在");
	else {
		prePath = pathName + "\\";
		cout << "打开数据库成功" << endl;
		open = true;
	}
}

void myDBMS::closeDataBase() {//和析构函数相同
	for (int i = 0; i < tab.size(); i++) {
		if (tab[i]->fp != NULL)
			fclose(tab[i]->fp);
		delete tab[i];
	}
	tab.resize(0);
	cmd = "";
	prePath = "";
	open = false;
}

//C:\Users\TKwang\source\repos\Project1
void myDBMS::myCreateDataBase(string dataBaseName) {//建立数据库
	string pathName = "C:\\Users\\24208\\Downloads\\数据库原理课程设计文档202401\\数据库原理课程设计文档202401\\" + dataBaseName;
	if (0 != access(pathName.c_str(), 0)) {
		if (0 == mkdir(pathName.c_str()))//返回0表示创建成功,-1表示失败
			cout << "创建成功" << endl;
		else
			cout << "创建失败" << endl;
		return;
	}
	cout << "该数据库已存在" << endl;
}

void myDBMS::myDropDataBase(string dataBaseName) {//删除数据库
	string pathName = "C:\\Users\\24208\\Downloads\\数据库原理课程设计文档202401\\数据库原理课程设计文档202401\\" + dataBaseName;
	if (0 == access(pathName.c_str(), 0)) {
		pathName = "rd " + pathName;
		if (0 == system(pathName.c_str()))
			cout << "删除数据库" << dataBaseName << "成功" << endl;
		else
			cout << "删除数据库" << dataBaseName << "失败" << endl;
		return;
	}
	cout << "数据库" << dataBaseName << "不存在" << endl;
}

void myDBMS::myCreateTable(string tableName) {//建立表
	vector<string>colName;
	vector<string>type;
	vector<int>size;
	string tmp;
	getchar();
	getline(cin, tmp);
	getline(cin, tmp);
	while (tmp != ")") {
		stringstream ss(tmp);
		string x;
		ss >> x; colName.push_back(x);
		ss >> x;
		int pos = x.find('(');
		if (pos == string::npos) {
			type.push_back(x);
			size.push_back(1);
		}
		else {
			type.push_back(x.substr(0, pos));
			int num = 0;
			for (int i = pos + 1; i < x.length() - 1; i++)
				num = num * 10 + x[i] - '0';
			size.push_back(num);
		}
		getline(cin, tmp);
	}
	tableName += ".txt";
	string pathName = prePath + tableName;
	//cout << pathName.c_str() << endl;
	if (0 != access(pathName.c_str(), 0)) {
		Tables* ptr = new Tables;
		ptr->name = tableName;
		ptr->pathName = pathName;
		ptr->colName = colName;
		ptr->type = type;
		ptr->size = size;
		ptr->fp = fopen(pathName.c_str(), "w");
		string wrin;
		wrin.clear();
		for (int i = 0; i < colName.size(); i++)
			wrin += colName[i] + ";" + type[i] + ";" + to_string(size[i]) + ";";
		wrin += "\n";
		fprintf(ptr->fp, wrin.c_str());
		fclose(ptr->fp);
		tab.push_back(ptr);
		cout << "创建新表成功!" << endl;
		return;
	}
	cout << "该表已经存在!" << endl;
}

void myDBMS::myDropTable(string tableName) {//删除表
	tableName += ".txt";
	string pathName = prePath + tableName;
	if (0 != access(pathName.c_str(), 0))
		cout << "该表不存在!" << endl;
	else {
		for (int i = 0; i < tab.size(); i++)
			if (tab[i]->name == tableName) {
				if (tab[i]->fp != NULL)
					fclose(tab[i]->fp);
				delete tab[i];
				tab.erase(tab.begin() + i);
			}
		remove(pathName.c_str());
		cout << "删除成功!" << endl;
	}
}

int myDBMS::posIsNos(string tableName) {
	string pathName = prePath + tableName + ".txt";
	if (0 != access(pathName.c_str(), 0)) {
		cout << "该表不存在!" << endl;
		return -1;
	}
	FILE* tempfptr = fopen(pathName.c_str(), "r");
	char contant[100];
	fscanf(tempfptr, "%s", contant);
	string tmp = contant;
	for (int i = 0; i < tmp.size(); i++)
		if (tmp[i] == ';')
			tmp[i] = ' ';
	stringstream check(tmp);
	string x, y, z;
	Tables* nxt = new Tables;
	nxt->name = tableName;
	while (check >> x) {
		check >> y >> z;
		nxt->colName.push_back(x);
		nxt->type.push_back(y);
		nxt->size.push_back(atoi(z.c_str()));
	}
	nxt->pathName = pathName;
	tab.push_back(nxt);
	fclose(tempfptr);
	return tab.size() - 1;
}

void myDBMS::myInsert(string tableName, string value) {//插入数据
	if (!open) {
		cout << "无选中数据库!" << endl;
		return;
	}
	int pos = inf;
	for (int i = 0; i < tab.size(); i++)
		if (tab[i]->name == tableName) {
			pos = i; break;
		}
	if (pos == inf)
		pos = posIsNos(tableName);
	if (pos == -1)return;
	stringstream ss(value);
	string tmp2; ss >> tmp2;
	tab[pos]->fp = fopen(tab[pos]->pathName.c_str(), "a");
	for (int i = 0; i < tab[pos]->type.size(); i++) {
		string tmp = tab[pos]->type[i];
		//cout << "tmp:" << tmp << endl;
		if (tmp == "int") {
			int x; ss >> x;
			fprintf(tab[pos]->fp, "%d", x);
		}
		else if (tmp == "float") {
			float x; ss >> x;
			fprintf(tab[pos]->fp, "%f", x);
		}
		else if (tmp == "double") {
			double x; ss >> x;
			fprintf(tab[pos]->fp, "%f", x);
		}
		else if (tmp == "char") {
			if (tab[pos]->size[i] == 1) {
				char x; ss >> x;
				fprintf(tab[pos]->fp, "%c", x);
			}
			else {
				int cnt = tab[pos]->size[i];
				char* x = new char[cnt];
				ss >> x;
				fprintf(tab[pos]->fp, "%s", x);
				delete x;
			}
		}
		if (i != tab[pos]->type.size() - 1)
			fprintf(tab[pos]->fp, "%c", ' ');
	}
	fprintf(tab[pos]->fp, "%c", '\n');
	fclose(tab[pos]->fp);
	cout << "插入成功!" << endl;
}

void myDBMS::myDelete(string tableName, string isWhere) {//删除数据
	if (!open) {
		cout << "无选中数据库!" << endl;
		return;
	}
	int pos = inf;
	for (int i = 0; i < tab.size(); i++)
		if (tab[i]->name == tableName) {
			pos = i; break;
		}
	if (pos == inf)
		pos = posIsNos(tableName);
	if (pos == -1)return;
	stringstream ss(isWhere);
	int wherePos = inf;
	string typeName, toValue, whr, deng;
	ss >> whr >> typeName >> deng >> toValue;
	for (int i = 0; i < tab[pos]->colName.size(); i++) {
		//cout << " " << tab[pos]->colName[i] << endl;
		if (tab[pos]->colName[i] == typeName) {
			wherePos = i;
			break;
		}
	}
	string pathName2 = prePath + "tmp.txt";
	FILE* tmpfptr = fopen(pathName2.c_str(), "w");
	char sentence[1024];
	tab[pos]->fp = fopen(tab[pos]->pathName.c_str(), "r");
	fgets(sentence, 1024, tab[pos]->fp);
	fputs(sentence, tmpfptr);
	bool flag = true;
	if (toValue.length() == 3 && tolower(toValue[0]) == 'a' && tolower(toValue[1]) == 'l' && tolower(toValue[2]) == '1')
		flag = false;
	if (flag) {
		while (!feof(tab[pos]->fp)) {
			memset(sentence, 0, sizeof(sentence));
			fgets(sentence, 1024, tab[pos]->fp);
			stringstream myTmp(sentence);
			//cout << "sentence " << sentence << endl;
			string x;
			for (int i = 0; i <= wherePos; i++)
				myTmp >> x;
			if (x == toValue) continue;
			fputs(sentence, tmpfptr);
		}
	}
	fclose(tmpfptr);
	fclose(tab[pos]->fp);
	remove(tab[pos]->pathName.c_str());
	if (0 == rename(pathName2.c_str(), tab[pos]->pathName.c_str()))
		cout << "删除成功!" << endl;
	else
		cout << "删除失败!" << endl;
}

void myDBMS::myUpdate(string tableName, string toColName, string newValue, string isWhere) {//更新数据
	if (!open) {
		cout << "无选中数据库!" << endl;
		return;
	}
	int pos = inf;
	for (int i = 0; i < tab.size(); i++)
		if (tab[i]->name == tableName) {
			pos = i; break;
		}
	if (pos == inf)
		pos = posIsNos(tableName);
	if (pos == -1)return;
	stringstream ss(isWhere);
	int wherePos = inf, updataPos = inf;
	string typeName, toValue, whr, deng;
	ss >> whr >> typeName >> deng >> toValue;
	for (int i = 0; i < tab[pos]->colName.size(); i++) //找到范围对应的colName下标
		if (tab[pos]->colName[i] == typeName) {
			wherePos = i;
			break;
		}
	for (int i = 0; i < tab[pos]->colName.size(); i++) //找到需要修改的colName下标
		if (tab[pos]->colName[i] == toColName) {
			updataPos = i;
			break;
		}
	string pathName2 = prePath + "tmp.txt";
	FILE* tmpfptr = fopen(pathName2.c_str(), "w");
	char sentence[1024];
	tab[pos]->fp = fopen(tab[pos]->pathName.c_str(), "r");
	fgets(sentence, 1024, tab[pos]->fp);
	fputs(sentence, tmpfptr);
	bool flag = true;
	if (toValue.length() == 3 && tolower(toValue[0]) == 'a' && tolower(toValue[1]) == 'l' && tolower(toValue[2]) == 'l')
		flag = false;
	if (!flag) {//全部修改
		while (!feof(tab[pos]->fp)) {
			for (int i = 0; i < tab[pos]->type.size(); i++) {
				string tmp = tab[pos]->type[i];
				//cout << "tmp:" << tmp << endl;
				if (tmp == "int") {
					int x; fscanf(tab[pos]->fp, "%d", &x);
					if (i == updataPos)
						x = atoi(newValue.c_str());
					fprintf(tmpfptr, "%d", x);
				}
				else if (tmp == "float") {
					float x; fscanf(tab[pos]->fp, "%f", &x);
					if (i == updataPos)
						x = atof(newValue.c_str());
					fprintf(tmpfptr, "%f", x);
				}
				else if (tmp == "double") {
					double x; fscanf(tab[pos]->fp, "%lf", &x);
					if (i == updataPos)
						x = atof(newValue.c_str());
					fprintf(tmpfptr, "%f ", x);
				}
				else if (tmp == "char") {
					if (tab[pos]->size[i] == 1) {
						char x; fscanf(tab[pos]->fp, "%c", &x);
						if (i == updataPos)
							x = newValue[0];
						fprintf(tmpfptr, "%c", x);
					}
					else {
						int cnt = tab[pos]->size[i];
						char* x = new char[cnt];
						fscanf(tab[pos]->fp, "%s", x);
						if (i == updataPos) {
							strcpy(x, newValue.c_str());
							x[newValue.length()] = NULL;
						}
						fprintf(tmpfptr, "%s", x);
						delete x;
					}
				}
				if (i != tab[pos]->type.size() - 1)
					fprintf(tmpfptr, "%c", ' ');
			}
			fprintf(tmpfptr, "%c", '\n');
		}
	}
	else {//范围内修改
		while (!feof(tab[pos]->fp)) {
			memset(sentence, 0, sizeof(sentence));
			fgets(sentence, 1024, tab[pos]->fp);
			stringstream myTmp(sentence);
			string x;
			for (int i = 0; i <= wherePos; i++)
				myTmp >> x;
			if (x == toValue) {
				stringstream myTmp2(sentence);
				string input;
				input.clear();
				for (int i = 0; i < tab[pos]->colName.size(); i++) {
					myTmp2 >> x;
					if (i == updataPos)
						input += newValue;
					else
						input += x;
					if (i != tab[pos]->colName.size() - 1)
						input += " ";
					else
						input += "\n";
				}
				//cout << "input = " << input;
				fputs(input.c_str(), tmpfptr);
			}
			else
				fputs(sentence, tmpfptr);
		}
	}
	fclose(tmpfptr);
	fclose(tab[pos]->fp);
	remove(tab[pos]->pathName.c_str());
	if (0 == rename(pathName2.c_str(), tab[pos]->pathName.c_str()))
		cout << "更新成功!" << endl;
	else
		cout << "更新失败!" << endl;
}

void myDBMS::myQuery(string toColName, string tableName, string isWhere = "") {//查询数据
	if (!open) {
		cout << "无选中数据库!" << endl;
		return;
	}
	int pos = inf;
	for (int i = 0; i < tab.size(); i++)
		if (tab[i]->name == tableName) {
			pos = i; break;
		}
	if (pos == inf)
		pos = posIsNos(tableName);
	if (pos == -1)return;
	tab[pos]->fp = fopen(tab[pos]->pathName.c_str(), "r");

	char contant[1024];
	//fscanf(tab[pos]->fp, "%s", contant);
	fgets(contant, sizeof(contant), tab[pos]->fp);
	if (isWhere == "") {//全输出
		int len = strlen(contant);
		for (int i = 0; i < len; i++)
			if (contant[i] == ';')
				contant[i] = ' ';
		stringstream ss(contant);
		string x;
		for (int i = 0; i < tab[pos]->size.size(); i++) {//先输出colNames
			int width = 15;
			if (tab[pos]->size[i] != 1)
				width = tab[pos]->size[i];
			ss >> x;
			cout << left << setw(width) << x;
			ss >> x;
			ss >> x;
		}
		cout << endl;
		//fgets(contant, sizeof(contant), tab[pos]->fp);
		while (!feof(tab[pos]->fp)) {
			memset(contant, 0, sizeof(contant));
			fgets(contant, sizeof(contant), tab[pos]->fp);
			if (strlen(contant) == 0)break;
			stringstream out(contant);
			string x;
			for (int i = 0; i < tab[pos]->type.size(); i++) {
				out >> x;
				int width = 15;
				if (tab[pos]->size[i] != 1)
					width = tab[pos]->size[i];
				string tmp = tab[pos]->type[i];
				if (tmp == "int")
					cout << left << setw(width) << atoi(x.c_str());
				else if (tmp == "float" || tmp == "double")
					cout << left << setw(width) << atof(x.c_str());
				else if (tmp == "char")
					cout << left << setw(width) << x;
			}
			cout << endl;
		}
	}
	else {
		stringstream ss(isWhere);
		int wherePos = inf, aimPos = inf;
		string typeName, toValue, whr, deng;
		ss >> whr >> typeName >> deng >> toValue;
		for (int i = 0; i < tab[pos]->colName.size(); i++) //找到规定范围colName下标
			if (tab[pos]->colName[i] == typeName) {
				wherePos = i;
				break;
			}
		for (int i = 0; i < tab[pos]->colName.size(); i++) //找到规定范围colName下标
			if (tab[pos]->colName[i] == toColName) {
				aimPos = i;
				break;
			}
		while (!feof(tab[pos]->fp)) {
			memset(contant, 0, sizeof(contant));
			fgets(contant, sizeof(contant), tab[pos]->fp);
			stringstream myTmp(contant);
			string x, check, out;
			for (int i = 0; i < tab[pos]->colName.size(); i++) {
				myTmp >> x;
				if (i == wherePos)check = x;
				if (i == aimPos)out = x;
			}
			if (check == toValue) {
				int width = 15;
				if (tab[pos]->size[aimPos] != 1)
					width = tab[pos]->size[aimPos];
				string tmp = tab[pos]->type[aimPos];
				if (tmp == "int")
					cout << left << setw(width) << atoi(out.c_str()) << endl;
				else if (tmp == "float")
					cout << left << setw(width) << atof(out.c_str()) << endl;
				else if (tmp == "double")
					cout << left << setw(width) << atof(out.c_str()) << endl;
				else if (tmp == "char")
					cout << left << setw(width) << out << endl;
			}
		}
	}
	fclose(tab[pos]->fp);
}

int main(void) {
	myDBMS db;
	while (cin >> db.cmd) {
		db.transfer();
		//cout << "db.cmd = " << db.cmd << endl;
		if (db.cmd == "exit")break;
		if (db.cmd == "create") {
			string name;
			cin >> db.cmd >> name;
			db.transfer();
			//cout << "db.cmd:" << db.cmd << " name:" << name << endl;
			if (db.cmd == "database")
				db.myCreateDataBase(name);
			else if (db.cmd == "table")
				db.myCreateTable(name);
			else cout << "命令语句有误!" << endl;
		}
		else if (db.cmd == "drop") {
			string name;
			cin >> db.cmd >> name;
			db.transfer();
			if (db.cmd == "database")
				db.myDropDataBase(name);
			else if (db.cmd == "table")
				db.myDropTable(name);
			else cout << "命令语句有误!" << endl;
		}
		else if (db.cmd == "open") {
			string name;
			cin >> db.cmd >> name;
			db.openDataBase(name);
		}
		else if (db.cmd == "close") {
			string name;
			cin >> db.cmd >> name;
			db.transfer();
			if (db.cmd == "database")
				db.closeDataBase();
			else cout << "命令语句有误!" << endl;
		}
		else if (db.cmd == "insert") {
			//insert into 表名(field1,field2,…) values(value1,value2,…)"
			string value, name;
			cin >> db.cmd >> name >> value;
			vector<string>colName;
			int pos = name.find('(');
			for (int i = 0; i < value.length(); i++)
				if (value[i] == ',' || value[i] == '(' || value[i] == ')')
					value[i] = ' ';
			//cout << "value:" << value << endl;
			db.myInsert(name.substr(0, pos), value);
		}
		else if (db.cmd == "delete") {
			//delete from 表名 where 范围
			string name;
			cin >> db.cmd >> name;
			string isWhere;
			getline(cin, isWhere);
			db.myDelete(name, isWhere);
		}
		else if (db.cmd == "update") {
			//update 列名 = 新值 from 表名 where 列名 = 值(值可为all, 表全部范围)
			string toColName, deng, newValue, tableName, isWhere;
			cin >> toColName >> deng >> newValue >> db.cmd >> tableName;
			getline(cin, isWhere);
			db.myUpdate(tableName, toColName, newValue, isWhere);
		}
		else if (db.cmd == "query") {
			//"查看全表  : query all from 表名" 
			//"查询单值  : query 列名 from 表名 where 列名 = 值(值可为all,表全部范围)" 
			string toColName, tableName;
			cin >> toColName >> db.cmd >> tableName;
			if (db.cmd.length() == 3 && tolower(db.cmd[0]) == 'a' && tolower(db.cmd[1]) == 'l' && tolower(db.cmd[2]) == 'l') {
				db.myQuery(toColName, tableName);
			}
			else {
				string isWhere;
				getline(cin, isWhere);
				db.myQuery(toColName, tableName, isWhere);
			}
		}
		else {
			string tmp;
			getline(cin, tmp);
			cout << "输入命令错误,请检查!" << endl;
		}
	}
	return 0;
}
