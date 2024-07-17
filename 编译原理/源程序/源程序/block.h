#ifndef RUN_PL0_BLOCK_H
#define RUN_PL0_BLOCK_H
#include "getsym.h"

//操作类型枚举
enum OPR_TYPE {//满足将1置为栈顶
    ReturnOpr, // return，结束被调用过程，返回调用点并退栈
    /*
    (sp <- bp - 1;
    bp <- stack[sp + 2];
    pc <- stack[sp + 3];)
    */
    MinusOpr, //取负
    /*
    (- stack[sp] )
    */
    AddOpr, //加
    /*
    (sp <- sp – 1 ;
    stack[sp] <- stack[sp] + stack[sp + 1])
    */
    SubOpr, //减
    /*
    (sp <- sp – 1 ;
    stack[sp] <- stack[sp] - stack[sp + 1])
    */
    MulOpr, //乘
    /*
    (sp <- sp – 1 ;
    stack[sp] <- stack[sp] * stack[sp + 1])
    */
    DivOpr, //整数除div
    /*
    sp <- sp – 1 ;
    stack[sp] <- (int)(stack[sp] / stack[sp + 1])
    */
    OddOpr, // odd，对2取模，
    /*
    (stack[sp] <- stack % 2)
    */
    ModOpr, //取模
    /*
    (sp <- sp – 1 ;
    stack[sp] <- stack[sp] % stack[sp + 1])
    */
    EquOpr, //等于
    /*
    (sp <- sp – 1 ;
    stack[sp] <- stack[sp] == stack[sp + 1])
    */
    NeqOpr, //不等于
    /*
    (sp <- sp – 1 ;
    stack[sp] <- stack[sp] != stack[sp + 1])
    */
    LessOpr, //小于
    /*
    (sp <- sp – 1 ;
    stack[sp] <- stack[sp] < stack[sp + 1])
    */
    EgreOpr, //大于等于
    /*
    (sp <- sp – 1 ;
    stack[sp] <- stack[sp] >= stack[sp + 1])
    */
    GreOpr, //大于
    /*
    (sp <- sp – 1 ;
    stack[sp] <- stack[sp] > stack[sp + 1])
    */
    ElessOpr, //小于等于
    /*
    (sp <- sp – 1 ;
    stack[sp] <- stack[sp] <= stack[sp + 1])
    */
    WriteOpr, // write(输出栈顶)
    /*
    print (stack[sp]);
    sp <- sp – 1;
    */
    ChaLineOpr, //输出换行
    /*
    print ('\n');
    */
    ReadOpr, //读入栈顶
    /*
    scan(stack[sp]);
    sp <- sp + 1;
    */
    AndOpr,//且运算
    /*
    (sp <- sp – 1 ;
    stack[sp] <- stack[sp] && stack[sp + 1]) 
    */
    OrOpr,//或运算
    /*
    (sp <- sp – 1 ;
    stack[sp] <- stack[sp] || stack[sp + 1])
    */
    AntiOpr,//非运算
    /*
    stack[sp] <- !stack[sp] 
    */
    RDivOpr, //实数除'/'
    /*
    (sp <- sp – 1 ;
    stack[sp] <- stack[sp] / stack[sp + 1])
    */
};

//语法分析错误
enum ERROR_GRAMMAR {
    const_state_end_wrong,//常数语句结尾错误
    number_wrong,//数错误
    const_assign_wrong,//常数定义错误
    identifier_wrong, //不是标识符
    var_state_end_wrong,//变量说明的结束错误
    var_no_type_wrong,//变量无类型
    var_type_wrong,//变量类型错误
    procedure_state_end_wrong,//过程语句结束错误
    procedure_name_redefined,//过程名与其他名字重复
    procedure_head_wrong,//过程首部结束错
    not_procedure_name,//不是过程名
    var_assign_wrong,//不是变量赋值
    Boolean_assign_wrong,//Bollean变量赋值错误
    integer_assign_wrong,//integer变量赋值错误
    expression_in_factor_wrong,//因子中包含的表达式的错误结束
    factor_wrong,//增加因子错误
    if_then_wrong,//if语句错误
    condition_wrong, //不是正确的比较运算符
    while_do_wrong,//while语句错误
    exit_wrong,//exit语句错误
    exit_IsNotIn_while,//exit语句不在循环中
    read_end_wrong,//read结束错误
    read_wrong,//read错误
    read_var_wrong,//被读入的不是变量
    read_Boolean_wrong,//Boolean类型变量无法被读入
    write_end_wrong,//write语句结束错误
    write_wrong,//write语句错误
    complex_end_wrong,//不是正确符合语句结束，或者中间语句缺少分号
    wrong_program_end,//错误的过程结束
    var_undefined,//未定义
    var_wrong,//不是变量
    var_redefined,//变量重定义
    const_redefined,//常量重定义,
    call_end_wrong,//过程调用结束错误
    real_para_wrong,//形参与实参个数不等
};

string rightType = "Boolean";  //赋值语句右边的类型，全局，real没有赋值限制，integer不能赋real型，Boolean只能赋Boolean型
int paraCount = 0;   //记录定义过程时，参数的数量
int exitCount = 0;      //记录exit退出循环语句未回填数量
int GLoopLevel = 0;     //记录循环层数，全局
int procedureLevel = 0; //记录层数，全局
int tx = 0;             //名字表索引，全局
int dx = 3;             //每层的局部相对地址，全局
int cx = 0;             //代码集合的索引，指向下一条地址，全局

//退出循环exitList结构体
struct ExitList{
    int cx;//用于存储执行exit后，产生跳转指令的地址，等循环分析完后根据此地址回填
    int LoopLevel;//记录循环的层数，只回填当前层次的循环
};

//语法树结点
struct treeNode {
    string element;
    vector<treeNode *> child;
    explicit treeNode(string e) {//防止类构造函数的隐式自动转换
        element = e; // NOLINT
        for (auto &it : child)
            it = nullptr;
    }
};

//语法分析名字表元素
struct tableEle {
    string name;//变量、(常量)或过程名
    string kind;//名字种类：const，var，procedure
    string type;//名字类型：integer，real，Boolean
    float value;//表示常量的值
    int level;//嵌套层次
    int addr;//(偏移)相对于所在嵌套过程基地址的地址，procedure记录的是该过程的第一条指令地址
    int paranum;//用于保存过程的参数数量
    tableEle() {//默认值
        name = "";
        kind = "";
        type = "";
        value = -1;
        level = -1;
        addr = -1;
        paranum = -1;
    }
};

vector<ExitList> exitList; //退出循环列表
vector<tableEle> tables; //语法分析名字表

//找到名字在名字表的位置，没找到返回-1，表示没有重定义，或未定义
int findAddrInTable(string &s) {
    for (int i = (int)tables.size() - 1; i >= 0; --i)
        if (s == tables[i].name && tables[i].level <= procedureLevel)
            return i;
    return -1;
}

void printTables() {
    cout << "名字表" << endl;
    for (int i = 0; i < tables.size(); ++i) {
        if(tables[i].kind=="const")
            cout << i << ": " << tables[i].name << " " << tables[i].kind << " " << tables[i].type << " " <<tables[i].value << endl;
        if(tables[i].kind=="var")
            cout << i << ": " << tables[i].name << " " << tables[i].kind << " " << tables[i].type << " " << tables[i].level << " " << tables[i].addr << endl;
        if(tables[i].kind=="procedure")
            cout << i << ": " << tables[i].name << " " << tables[i].kind << " " << tables[i].type << " " << tables[i].level << " " << tables[i].addr << " " << tables[i].paranum <<endl;
    }
}

struct codeEle {//目的代码元素
    string func;//操作码
    int level_d;//层次差 （标识符引用层减去定义层），需要沿着静态链走的次数
    float offset;//不同操作含义不同
};
vector<codeEle> codes; //目的代码表

void addCode(string str, int lev, float off) {
    codeEle coe;
    coe.func = str;
    coe.level_d = lev;
    coe.offset = off;
    codes.push_back(coe);
    cx++;//中间代码数加1
}

void printCodes() {
    cout << "目标代码序列" << endl;
    for (int i = 0; i < codes.size(); ++i)
        cout << i << ": " << codes[i].func << " " << codes[i].level_d << " " << codes[i].offset << endl;
}

void printTreeNode(treeNode *root, int level) {
    if (root != nullptr) {
        for (int i = 0; i < level; ++i)
            cout << " |";
        cout << " *" << root->element << endl;
        for (auto &it : root->child)//取出所有孩子
            printTreeNode(it, level + 1);//递归
    }
}

string sym;//全局单词变量类型

bool error_grammar = false;

void error_exc(int error_grammar_type); //错误处理
void BLOCK(treeNode *tn);               //语法分析入口程序
void subBlock(treeNode *tn);            //分程序
void const_BLOCK(treeNode *tn);         //常量说明
void const_def(treeNode *tn);           //常量定义
int var_BLOCK(treeNode *tn);            //变量说明
void procedure_BLOCK(treeNode *tn);     //过程说明
void procedure_head(treeNode *tn);      //过程首部
void sen_BLOCK(treeNode *tn);           //语句
void assi_sen(treeNode *tn);            //赋值语句
void condition_sen(treeNode *tn);       //条件语句
void do_while_sen(treeNode *tn);        //当型循环语句
void exit_sen(treeNode* tn);            //退出循环语句
void proc_call_sen(treeNode *tn);       //过程调用语句
void read_sen(treeNode *tn);            //读语句
void write_sen(treeNode *tn);           //写语句
void complex_sen(treeNode *tn);         //复合语句
void rel_expression(treeNode *tn);      //关系表达式
void expression(treeNode *tn);          //表达式
//void condition(treeNode *tn);           //条件
void item(treeNode *tn);                //项
void factor(treeNode *tn);              //因子

//错误处理
void error_exc(int error_grammar_type) {
    error_grammar = true;
    int temp_line = lineSum + 1;
    switch (error_grammar_type) {
    case const_state_end_wrong:
        cout << "常量说明结束错误 in line " << temp_line << endl;
        break;
    case number_wrong:
        cout << "无符号整数或实数错误 in line " << temp_line << endl;
        break;
    case const_assign_wrong:
        cout << "常数赋值错误 in line " << temp_line << endl;
        break;
    case identifier_wrong:
        cout << "标识符错误 in line " << temp_line << endl;
        break;
    case var_state_end_wrong:
        cout << "变量说明结束错误 in line " << temp_line << endl;
        break;
    case var_no_type_wrong:
        cout << "变量无类型 in line " << temp_line << endl;
        break;
    case var_type_wrong:
        cout << "变量类型错误 in line " << temp_line << endl;
        break;
    case procedure_state_end_wrong:
        cout << "过程说明结束错误 in line " << temp_line << endl;
        break;
    case procedure_name_redefined:
        cout << "过程名字与其他名字重复 in line " << temp_line << endl;
        break;
    case procedure_head_wrong:
        cout << "过程首部错误 in line " << temp_line << endl;
        break;
    case not_procedure_name:
        cout << "调用非过程名 in line " << temp_line << endl;
        break;

    case var_assign_wrong:
        cout << "变量赋值错误 in line " << temp_line << endl;
        break;
    case Boolean_assign_wrong:
        cout << "Boolean变量不能赋整数和实数 in line " << temp_line << endl;
        break;
   case integer_assign_wrong:
        cout << "integer变量不能赋实数 in line " << temp_line << endl;
        break;
    case expression_in_factor_wrong:
        cout << "因子中的表达式错误 in line " << temp_line << endl;
        break;
    case factor_wrong:
        cout << "因子中错误 in line " << temp_line << endl;
        break;
    case if_then_wrong:
        cout << "if_then语句错误 in line " << temp_line << endl;
        break;
    case condition_wrong:
        cout << "比较运算错误 in line " << temp_line << endl;
        break;
    case while_do_wrong:
        cout << "while_do语句错误 in line " << temp_line << endl;
        break;
    case exit_wrong:
        cout << "exit退出循环语句错误 in line " << temp_line << endl;
        break;
    case exit_IsNotIn_while:
        cout << "exit退出循环语句不在循环中 in line " << temp_line << endl;
        break;
    case read_end_wrong:
        cout << "read语句结束错误 in line " << temp_line << endl;
        break;
    case read_wrong:
        cout << "read语句错误 in line " << temp_line << endl;
        break;
    case read_var_wrong:
        cout << "被读入的不是变量 in line " << temp_line << endl;
        break;
    case read_Boolean_wrong:
        cout << "Boolean类型变量无法被读入 in line " << temp_line << endl;
        break;

    case write_end_wrong:
        cout << "write语句结束错误 in line " << temp_line << endl;
        break;
    case write_wrong:
        cout << "write语句错误 in line " << temp_line << endl;
        break;
    case complex_end_wrong:
        cout << "不是正确复合语句结束，或者中间语句缺少分号 in line " << temp_line << endl;
        break;
    case wrong_program_end:
        cout << "wrong program end in line " << temp_line << endl;
        break;
    case var_undefined:
        cout << "有未定义的变量 in line " << temp_line << endl;
        break;
    case var_wrong:
        cout << "被赋值的不是变量 in line " << temp_line << endl;
        break;
    case var_redefined:
        cout << "重复定义的变量 in line " << temp_line << endl;
        break;
    case const_redefined:
        cout << "重复定义的常量 in line " << temp_line << endl;
        break;
    case call_end_wrong:
        cout << "过程调用结束错误 in line " << temp_line << endl;
        break;
    case real_para_wrong:
        cout << "形参与实参个数不等 in line " << temp_line << endl;
        break;
    default:
        break;
    }
    exit(0);
}
//语法分析入口程序
void BLOCK(treeNode *tn) {
    sym = GETSYM();
    auto *subBlockt = new treeNode("分程序");
    tn->child.push_back(subBlockt);//压入一个孩子
    subBlock(subBlockt);//转入分程序处理
    if (sym == ".") {
        tn->child.push_back(new treeNode("."));
        sym = GETSYM();
        //添加代码
        addCode("opr", 0, ReturnOpr);//结束被调用过程，返回调用点并退栈
        //
        cout << "Grammar analysis complete" << endl;
        // cout << "the chart of integer has " << integerArray.size() << " items." << endl;
        // cout << "the chart of identifier has " << identifierArray.size() << " items" << endl;
    } 
    else
        error_exc(wrong_program_end);
}
//分程序
void subBlock(treeNode *tn) {
    addCode("jmp", 0, -1); //跳转到语句部分，-1表示等待回填
    int tmpCodeAddr = cx - 1;
    int varcount = 0;
    if (sym == "const") {//单词为const
        auto *const_BLOCKt = new treeNode("常量说明部分");
        tn->child.push_back(const_BLOCKt);//压入为分程序孩子
        const_BLOCK(const_BLOCKt); //常量说明
    }
    if (sym == "var") {
        auto *var_BLOCKt = new treeNode("变量说明部分");
        tn->child.push_back(var_BLOCKt);//压入为分程序孩子
        varcount = var_BLOCK(var_BLOCKt); //变量说明
    }    if (sym == "procedure") {
        auto *procedure_BLOCKt = new treeNode("过程说明部分");
        tn->child.push_back(procedure_BLOCKt);//压入为分程序孩子
        procedure_BLOCK(procedure_BLOCKt); //过程说明
    }
    auto *sen_BLOCKt = new treeNode("语句");
    tn->child.push_back(sen_BLOCKt);
    //添加代码
    addCode("int", 0, varcount + 3);
    codes[tmpCodeAddr].offset = cx - 1;//指向上一条
    //
    sen_BLOCK(sen_BLOCKt); //语句
}
//常量说明
void const_BLOCK(treeNode *tn) {
    if (sym == "const") {
        tn->child.push_back(new treeNode("const"));//将const压入常量说明
        sym = GETSYM();//获取下一个单词，为下一步判断做准备
        auto *const_deft = new treeNode("常量定义");//创建常量定义结点
        tn->child.push_back(const_deft);
        const_def(const_deft);//进入常量定义部分，将该常量定义结点传入
        while (sym == ",") {
            tn->child.push_back(new treeNode(","));
            sym = GETSYM();
            auto *const_defts = new treeNode("常量定义");
            tn->child.push_back(const_defts);
            const_def(const_defts);
        }
        if (sym == ";") {
            tn->child.push_back(new treeNode(";"));
            sym = GETSYM();
        } else
            error_exc(const_state_end_wrong); //常量说明的错误结束
    } 
    else
        return;//没有直接返回
}
//常量定义
void const_def(treeNode *tn) {
    if (sym == "identifier") {
        auto *idt = new treeNode(debugId);//标识符名称结点
        tn->child.push_back(new treeNode("标识符"));
        tn->child.back()->child.push_back(idt);
        //添加名字表
        int labelAddr = findAddrInTable(debugId);//查看是否重定义
        if (labelAddr != -1)
            error_exc(const_redefined);
        tableEle tabe;
        tabe.name = debugId;
        tabe.kind = "const";
        //
        sym = GETSYM();
        if (sym == "=") {
            tn->child.push_back(new treeNode("="));
            sym = GETSYM();
            if (sym == "int_number") {
                auto *numt = new treeNode(Int_debugNum);
                tn->child.push_back(new treeNode("无符号整数"));
                tn->child.back()->child.push_back(numt);
                //添加名字表
                tabe.value = Int_debugNumber;
                tabe.type = "integer";
                tables.push_back(tabe);
                tx++;//名字表索引加1
                
                sym = GETSYM();
            }
            else if (sym=="real_number") {
                auto* numt2 = new treeNode(Real_debugNum);
                tn->child.push_back(new treeNode("实数"));
                tn->child.back()->child.push_back(numt2);
                //添加名字表
                tabe.value = Real_debugNumber;
                tabe.type = "real";
                tables.push_back(tabe);
                tx++;//名字表索引加1

                sym = GETSYM();//记住取下一个单词类型
            }
            else
                error_exc(number_wrong); //不是数字
        } 
        else
            error_exc(const_assign_wrong); //不是常量赋值
    } 
    else
        error_exc(identifier_wrong); //不是标识符
}
//变量说明，‘:’后加类型
int var_BLOCK(treeNode *tn) {
    if (sym == "var") {
        int varNumber = 0;//变量数目
        tn->child.push_back(new treeNode("var"));
        sym = GETSYM();
        int temp_tx = tx;//记录变量最开始的下标
        tableEle tabe;//变量名字表项
        if (sym == "identifier") {
            auto *idt = new treeNode(debugId);
            tn->child.push_back(new treeNode("标识符"));
            tn->child.back()->child.push_back(idt);//压入标识符的孩子，标识符名字
            //添加名字表
            int labelAddr = findAddrInTable(debugId);
            if (labelAddr != -1)
                error_exc(var_redefined);
            tabe.name = debugId;
            tabe.kind = "var";
            tabe.addr = dx++;
            tabe.level = procedureLevel;
            tables.push_back(tabe);
            tx++;
            varNumber++;
            //
            sym = GETSYM();
        } 
        else
            error_exc(identifier_wrong); //不是标识符
        while (sym == ",") {
            tn->child.push_back(new treeNode("，"));
            sym = GETSYM();
            if (sym == "identifier") {
                auto *idt = new treeNode(debugId);
                tn->child.push_back(new treeNode("标识符"));
                tn->child.back()->child.push_back(idt);
                //添加名字表
                int labelAddr = findAddrInTable(debugId);
                if (labelAddr != -1)
                    error_exc(var_redefined);//重定义
                tabe.name = debugId;
                tabe.kind = "var";
                tabe.addr = dx++;
                tabe.level = procedureLevel;
                tables.push_back(tabe);
                tx++;
                varNumber++;
                //
                sym = GETSYM();//取下一个单词类型
            } 
            else
                error_exc(identifier_wrong); //不是标识符
        }
        if (sym == ":") {//必须跟‘:’，否则变量无类型
            tn->child.push_back(new treeNode("："));//语法树
            sym = GETSYM();
            if (sym == "integer" || sym == "real" || sym == "Boolean") {
                tn->child.push_back(new treeNode("类型"));
                tn->child.back()->child.push_back(new treeNode(sym));
                for (int j = temp_tx; j < tx; j++) {//添加temp_tx，到tx-1下标变量的type
                    tables[j].type = sym;
                }
                sym = GETSYM();//取下一个单词类型
            }
            else
                error_exc(var_type_wrong);//类型错误
        }
        else
            error_exc(var_no_type_wrong);//无类型
        if (sym == ";") {
            tn->child.push_back(new treeNode(";"));
            sym = GETSYM();//取下一个单词类型，判断是否是关键字
        } 
        else
            error_exc(var_state_end_wrong); //变量说明的结束错误

        while (!IsKey) {//下一个单词不是关键字则继续定义，这部分重复上述变量说明
            temp_tx = tx;//记录变量最开始的下标
            tableEle tabe;//变量名字表项
            if (sym == "identifier") {
                auto* idt = new treeNode(debugId);
                tn->child.push_back(new treeNode("标识符"));
                tn->child.back()->child.push_back(idt);//压入标识符的孩子，标识符名字
                //添加名字表
                int labelAddr = findAddrInTable(debugId);
                if (labelAddr != -1)
                    error_exc(var_redefined);
                tabe.name = debugId;
                tabe.kind = "var";
                tabe.addr = dx++;
                tabe.level = procedureLevel;
                tables.push_back(tabe);
                tx++;
                varNumber++;
                //
                sym = GETSYM();
            }
            else
                error_exc(identifier_wrong); //不是标识符
            while (sym == ",") {
                tn->child.push_back(new treeNode("，"));
                sym = GETSYM();
                if (sym == "identifier") {
                    auto* idt = new treeNode(debugId);
                    tn->child.push_back(new treeNode("标识符"));
                    tn->child.back()->child.push_back(idt);
                    //添加名字表
                    int labelAddr = findAddrInTable(debugId);
                    if (labelAddr != -1)
                        error_exc(var_redefined);//重定义
                    tabe.name = debugId;
                    tabe.kind = "var";
                    tabe.addr = dx++;
                    tabe.level = procedureLevel;
                    tables.push_back(tabe);
                    tx++;
                    varNumber++;
                    //
                    sym = GETSYM();//取下一个单词类型
                }
                else
                    error_exc(identifier_wrong); //不是标识符
            }
            if (sym == ":") {//必须跟‘:’，否则变量无类型
                tn->child.push_back(new treeNode("："));//语法树
                sym = GETSYM();
                if (sym == "integer" || sym == "real" || sym == "Boolean") {
                    tn->child.push_back(new treeNode("类型"));
                    tn->child.back()->child.push_back(new treeNode(sym));
                    for (int j = temp_tx; j < tx; j++) {//添加temp_tx，到tx-1下标变量的type
                        tables[j].type = sym;
                    }
                    sym = GETSYM();//取下一个单词类型
                }
                else
                    error_exc(var_type_wrong);//类型错误
            }
            else
                error_exc(var_no_type_wrong);//无类型
            if (sym == ";") {
                tn->child.push_back(new treeNode(";"));
                sym = GETSYM();//取下一个单词类型，判断是否是关键字
            }
            else
                error_exc(var_state_end_wrong); //变量说明的结束错误
        }
        return varNumber;
    } 
    else
        return -1;
}
//过程说明
void procedure_BLOCK(treeNode *tn) {
    if (sym == "procedure") {
        //进入一个过程，增加层数，局部相对地址恢复为3
        procedureLevel++;
        dx = 3;
        auto *procedure_headt = new treeNode("过程首部");
        tn->child.push_back(procedure_headt);
        procedure_head(procedure_headt);
        auto *subBlockt = new treeNode("分程序");
        tn->child.push_back(subBlockt);
        subBlock(subBlockt);
        if (sym == ";") {
            tn->child.push_back(new treeNode(";"));
            //添加代码
            addCode("opr", 0, ReturnOpr);
            procedureLevel--; //过程结束，降低层数
            
            sym = GETSYM();
            while (sym == "procedure") {
                auto *procedure_BLOCKt = new treeNode("过程说明部分");
                tn->child.push_back(procedure_BLOCKt);
                procedure_BLOCK(procedure_BLOCKt);
            }
        } 
        else
            error_exc(procedure_state_end_wrong); //过程说明的结束错误
    } 
    else
        return;
}
//过程首部
void procedure_head(treeNode *tn) {
    if (sym == "procedure") {
        int temp_pro_tx = 0;//保存过程名的下标
        paraCount = 0;//形参变量数目，每次过程定义时设置初值0
        tn->child.push_back(new treeNode("procedure"));
        sym = GETSYM();
        if (sym == "identifier") {
            auto *idt = new treeNode(debugId);
            tn->child.push_back(new treeNode("标识符"));
            tn->child.back()->child.push_back(idt);//压入为标识符的孩子
            //添加名字表
            int labelAddr = findAddrInTable(debugId);
            if (labelAddr != -1)
                error_exc(procedure_name_redefined);
            tableEle tabe;
            tabe.name = debugId;
            tabe.kind = "procedure";
            tabe.addr = cx;//指明分程序的入口
            tabe.level = procedureLevel - 1; //过程的层数应该隶属于过程的上一层，0层定义的过程名属于0层
            tables.push_back(tabe);
            temp_pro_tx = tx;//保存过程名的下标
            tx++;
            //
            sym = GETSYM();
            if (sym == "(") {
                tn->child.push_back(new treeNode("("));
                sym = GETSYM();
                int temp_tx = tx;//记录变量最开始的下标
                tableEle tabe;//变量名字表项
                if (sym == "identifier") {
                    auto* idt = new treeNode(debugId);
                    tn->child.push_back(new treeNode("标识符"));
                    tn->child.back()->child.push_back(idt);//压入标识符的孩子，标识符名字
                    //添加名字表
                    int labelAddr = findAddrInTable(debugId);
                    if (labelAddr != -1)
                        error_exc(var_redefined);
                    tabe.name = debugId;
                    tabe.kind = "var";
                    tabe.addr = dx++;
                    tabe.level = procedureLevel;
                    tables.push_back(tabe);
                    tx++;
                    paraCount++;
                    //
                    sym = GETSYM();
                }
                else
                    error_exc(identifier_wrong); //不是标识符
                while (sym == ",") {
                    tn->child.push_back(new treeNode("，"));
                    sym = GETSYM();
                    if (sym == "identifier") {
                        auto* idt = new treeNode(debugId);
                        tn->child.push_back(new treeNode("标识符"));
                        tn->child.back()->child.push_back(idt);
                        //添加名字表
                        int labelAddr = findAddrInTable(debugId);
                        if (labelAddr != -1)
                            error_exc(var_redefined);//重定义
                        tabe.name = debugId;
                        tabe.kind = "var";
                        tabe.addr = dx++;
                        tabe.level = procedureLevel;
                        tables.push_back(tabe);
                        tx++;
                        paraCount++;
                        //
                        sym = GETSYM();//取下一个单词类型
                    }
                    else
                        error_exc(identifier_wrong); //不是标识符
                }
                if (sym == ":") {//必须跟‘:’，否则变量无类型
                    tn->child.push_back(new treeNode("："));//语法树
                    sym = GETSYM();
                    if (sym == "integer" || sym == "real" || sym == "Boolean") {
                        tn->child.push_back(new treeNode("类型"));
                        tn->child.back()->child.push_back(new treeNode(sym));
                        for (int j = temp_tx; j < tx; j++) {//添加temp_tx，到tx-1下标变量的type
                            tables[j].type = sym;
                        }
                        sym = GETSYM();//取下一个单词类型
                    }
                    else
                        error_exc(var_type_wrong);//类型错误
                }
                else
                    error_exc(var_no_type_wrong);//无类型
                //遇到“;”继续定义形参，重复上述步骤
                while (sym == ";") {
                    tn->child.push_back(new treeNode("；"));
                    sym = GETSYM();
                    int temp_tx = tx;//记录变量最开始的下标
                    tableEle tabe;//变量名字表项
                    if (sym == "identifier") {
                        auto* idt = new treeNode(debugId);
                        tn->child.push_back(new treeNode("标识符"));
                        tn->child.back()->child.push_back(idt);//压入标识符的孩子，标识符名字
                        //添加名字表
                        int labelAddr = findAddrInTable(debugId);
                        if (labelAddr != -1)
                            error_exc(var_redefined);
                        tabe.name = debugId;
                        tabe.kind = "var";
                        tabe.addr = dx++;
                        tabe.level = procedureLevel;
                        tables.push_back(tabe);
                        tx++;
                        paraCount++;
                        //
                        sym = GETSYM();
                    }
                    else
                        error_exc(identifier_wrong); //不是标识符
                    while (sym == ",") {
                        tn->child.push_back(new treeNode("，"));
                        sym = GETSYM();
                        if (sym == "identifier") {
                            auto* idt = new treeNode(debugId);
                            tn->child.push_back(new treeNode("标识符"));
                            tn->child.back()->child.push_back(idt);
                            //添加名字表
                            int labelAddr = findAddrInTable(debugId);
                            if (labelAddr != -1)
                                error_exc(var_redefined);//重定义
                            tabe.name = debugId;
                            tabe.kind = "var";
                            tabe.addr = dx++;
                            tabe.level = procedureLevel;
                            tables.push_back(tabe);
                            tx++;
                            paraCount++;
                            //
                            sym = GETSYM();//取下一个单词类型
                        }
                        else
                            error_exc(identifier_wrong); //不是标识符
                    }
                    if (sym == ":") {//必须跟‘:’，否则变量无类型
                        tn->child.push_back(new treeNode("："));//语法树
                        sym = GETSYM();
                        if (sym == "integer" || sym == "real" || sym == "Boolean") {
                            tn->child.push_back(new treeNode("类型"));
                            tn->child.back()->child.push_back(new treeNode(sym));
                            for (int j = temp_tx; j < tx; j++) {//添加temp_tx，到tx-1下标变量的type
                                tables[j].type = sym;
                            }
                            sym = GETSYM();//取下一个单词类型
                        }
                        else
                            error_exc(var_type_wrong);//类型错误
                    }
                    else
                        error_exc(var_no_type_wrong);//无类型

                }
                if (sym == ")") {
                    tn->child.push_back(new treeNode(")"));
                    sym = GETSYM();
                }
                else {
                    error_exc(procedure_head_wrong);//过程首部错误
                }
            }
            if (sym == ";") {//过程首部以分号结束
                tn->child.push_back(new treeNode(";"));
                sym = GETSYM();
                //回填参数数量
                tables[temp_pro_tx].paranum = paraCount;
            } else
                error_exc(procedure_head_wrong); //过程首部结束错的
        } else
            error_exc(identifier_wrong); //不是标识符
    } else
        return;
}
//分程序的语句
void sen_BLOCK(treeNode *tn) {
    if (sym == "identifier") {
        auto *assi_sent = new treeNode("赋值语句");
        tn->child.push_back(assi_sent);//压入为语句的孩子
        assi_sen(assi_sent);
    } 
    else if (sym == "if") {
        auto *condition_sent = new treeNode("条件语句");
        tn->child.push_back(condition_sent);
        condition_sen(condition_sent);
    } 
    else if (sym == "while") {
        auto *do_while_sent = new treeNode("当型循环语句");
        tn->child.push_back(do_while_sent);
        do_while_sen(do_while_sent);
    } 
    else if (sym == "exit") {
        auto *exit_sent = new treeNode("退出循环语句");
        tn->child.push_back(exit_sent);
        exit_sen(exit_sent);
    } 

    else if (sym == "call") {
        auto *proc_call_sent = new treeNode("过程调用语句");
        tn->child.push_back(proc_call_sent);
        proc_call_sen(proc_call_sent);
    } 
    else if (sym == "read") {
        auto *read_sent = new treeNode("读语句");
        tn->child.push_back(read_sent);
        read_sen(read_sent);
    } 
    else if (sym == "write") {
        auto *write_sent = new treeNode("写语句");
        tn->child.push_back(write_sent);
        write_sen(write_sent);
    } 
    else if (sym == "begin") {
        auto *complex_sent = new treeNode("复合语句");
        tn->child.push_back(complex_sent);
        complex_sen(complex_sent);
    }
}
//赋值语句
void assi_sen(treeNode *tn) {
    if (sym == "identifier") {
        auto *idt = new treeNode(debugId);
        tn->child.push_back(new treeNode("标识符"));
        tn->child.back()->child.push_back(idt);
        string tmp = debugId; //保存待赋值的变量
        int labelAddr = findAddrInTable(tmp);
        if (labelAddr == -1)
            error_exc(var_undefined);
        if(tables[labelAddr].kind!="var")
            error_exc(var_wrong);//被赋值的不是变量
        rightType = "Boolean";//每次执行赋值语句，需要将右部类型设置为Boolean
        string leftType = tables[labelAddr].type;//保存被赋值标识符的类型
        sym = GETSYM();
        if (sym == ":=") {
            tn->child.push_back(new treeNode(":="));
            sym = GETSYM();
            auto * rel_expressiont = new treeNode("比较表达式");
            tn->child.push_back(rel_expressiont);
            rel_expression(rel_expressiont);
            //添加代码
            int level_diff = abs(tables[labelAddr].level - procedureLevel);//记录层差，运行时静态链会使用
            addCode("sto", level_diff, tables[labelAddr].addr);//将栈顶的值存入层差为level_diff，偏移量为tables[labelAddr].addr的单元
            //
            if (leftType == "Boolean" && rightType!="Boolean") {
                error_exc(Boolean_assign_wrong);//Boolean赋值错误
            }
            else if (leftType == "integer" && rightType == "real") {
                error_exc(integer_assign_wrong);//integer赋值错误
            }
        } 
        else
            error_exc(var_assign_wrong); //不是变量赋值
    } else
        return;
}

 //关系表达式
void rel_expression(treeNode* tn) {
    auto* expressiont0 = new treeNode("表达式");//符号左边
    tn->child.push_back(expressiont0);
    expression(expressiont0);
    if (sym == "=" || sym == "<>" || sym == "<" || sym == "<=" || sym == ">" || sym == ">=") {
        string opr = sym;
        auto* idt = new treeNode(sym);
        tn->child.push_back(new treeNode("条件运算符"));
        tn->child.back()->child.push_back(idt);
        sym = GETSYM();
        auto* expressiont1 = new treeNode("表达式");//符号右边
        tn->child.push_back(expressiont1);
        expression(expressiont1);
        //添加代码
        if (opr == "=")
            addCode("opr", 0, EquOpr); //=运算
        else if (opr == "<>")
            addCode("opr", 0, NeqOpr); //<>运算
        else if (opr == "<")
            addCode("opr", 0, LessOpr); //<运算
        else if (opr == "<=")
            addCode("opr", 0, ElessOpr); //<=运算
        else if (opr == ">")
            addCode("opr", 0, GreOpr); //>运算
        else if (opr == ">=")
            addCode("opr", 0, EgreOpr); //>=运算

    }

}

//表达式
void expression(treeNode *tn) {
    if (sym == "+" || sym == "-") {
        tn->child.push_back(new treeNode(sym));
        string opr = sym;
        sym = GETSYM();
        //添加代码
        if (opr == "-")
            addCode("opr", 0, MinusOpr); //取负运算
        //
    }
    auto *itemt = new treeNode("项");
    tn->child.push_back(itemt);
    item(itemt);
    while (sym == "+" || sym == "-" || sym == "or") {//增加or
        auto *idt = new treeNode(sym);
        tn->child.push_back(new treeNode("加减或运算符"));
        tn->child.back()->child.push_back(idt);
        string opr = sym; //暂存运算符
        sym = GETSYM();
        auto *itemts = new treeNode("项");
        tn->child.push_back(itemts);
        item(itemts);
        //添加代码
        if (opr == "+")
            addCode("opr", 0, AddOpr); //+运算
        else if (opr == "-")
            addCode("opr", 0, SubOpr); //-运算
        else if (opr == "or")
            addCode("opr", 0, OrOpr);//or运算
        //
    }
}
//项
void item(treeNode *tn) {
    auto factort = new treeNode("因子");
    tn->child.push_back(factort);
    factor(factort);
    while (sym == "*" || sym == "/" || sym == "mod" || sym == "and" || sym == "div" || sym == "%") {
        string opr = sym;//暂存运算符
        auto *idt = new treeNode(sym);
        tn->child.push_back(new treeNode("乘除取余且运算符"));
        tn->child.back()->child.push_back(idt);
        sym = GETSYM();
        auto factorts = new treeNode("因子");
        tn->child.push_back(factorts);
        factor(factorts);
        //添加代码，运算代码在2个因子代码加了之后加
        if (opr == "*")
            addCode("opr", 0, MulOpr); //*运算
        else if (opr == "/")
            addCode("opr", 0, RDivOpr); // 实数/运算
        else if (opr == "div")
            addCode("opr", 0, DivOpr); // 整数div运算
        else if (opr == "mod" || sym == "%")
            addCode("opr", 0, ModOpr); // mod运算
        else if (opr == "and")
            addCode("opr", 0, AndOpr); // and运算
        
    }
}

//因子
void factor(treeNode *tn) {
    if (sym == "identifier" || sym == "int_number" || sym == "real_number" || sym == "true" || sym == "false") {
        string tmp;
        treeNode *idt;
        if (sym == "identifier") {
            tmp = "标识符";
            idt = new treeNode(debugId);
            //添加代码
            int labelAddr = findAddrInTable(debugId);
            if (labelAddr == -1)
                error_exc(var_undefined);
            if (tables[labelAddr].kind == "const") {
                addCode("lit", 0, tables[labelAddr].value);
                if (tables[labelAddr].type == "integer" && rightType == "Boolean") {//将Boolean类型改为integer
                    rightType = "integer";
                }
                else if (tables[labelAddr].type == "real" && rightType != "real") {//将非real类型改为real类型
                    rightType = "real";
                }
            }
            else if (tables[labelAddr].kind == "var") {
                int level_diff = abs(tables[labelAddr].level - procedureLevel);//记录层差，运行时静态链会使用
                addCode("lod", level_diff, tables[labelAddr].addr);
                if (tables[labelAddr].type == "integer" && rightType == "Boolean") {//将Boolean类型改为integer
                    rightType = "integer";
                }
                else if (tables[labelAddr].type == "real" && rightType != "real") {//将非real类型改为real类型
                    rightType = "real";
                }
            }   
            
        } 
        else if(sym == "int_number"){
            tmp = "无符号整数";
            idt = new treeNode(Int_debugNum);
            //添加代码
            addCode("lit", 0, Int_debugNumber);
            if (rightType=="Boolean") {
                rightType = "integer";
            }
        }
        else if(sym == "real_number"){
            tmp = "实数";
            idt = new treeNode(Real_debugNum);
            //添加代码
            addCode("lit", 0, Real_debugNumber);
            if (rightType == "Boolean" || rightType == "integer") {
                rightType = "real";
            }
        }
        else if(sym == "true"){
            tmp = "布尔值";
            idt = new treeNode("true");
            //添加代码
            addCode("lit", 0, 1);
        }
        else if(sym == "false"){
            tmp = "布尔值";
            idt = new treeNode("false");
            //添加代码
            addCode("lit", 0, 0);
        }
        tn->child.push_back(new treeNode(tmp));
        tn->child.back()->child.push_back(idt);
        sym = GETSYM();
    } 
    else if (sym == "not") {//取反
        tn->child.push_back(new treeNode("not"));//构建语法树
        auto* factort = new treeNode("因子");
        tn->child.push_back(factort);
        sym = GETSYM();
        factor(factort);

        //添加代码
        addCode("opr", 0, AntiOpr); // not运算
    }
    else if (sym == "odd") {//奇数为1，偶数为0
        tn->child.push_back(new treeNode("odd"));//构建语法树
        sym = GETSYM();
        if (sym == "(") {
            tn->child.push_back(new treeNode("("));
            sym = GETSYM();
            auto* expressiont = new treeNode("表达式");
            tn->child.push_back(expressiont);
            expression(expressiont);
            if (sym == ")") {
                tn->child.push_back(new treeNode(")"));
                sym = GETSYM();
            }
            else
                error_exc(expression_in_factor_wrong); //因子中包含的表达式的错误结束
        }
        else
            error_exc(factor_wrong);

        //添加代码
        addCode("opr", 0, OddOpr); // odd运算
    }
    else if (sym == "(") {
        tn->child.push_back(new treeNode("("));
        sym = GETSYM();
        auto * rel_expressiont = new treeNode("比较表达式");
        tn->child.push_back(rel_expressiont);
        rel_expression(rel_expressiont);
        if (sym == ")") {
            tn->child.push_back(new treeNode(")"));
            sym = GETSYM();
        } 
        else
            error_exc(expression_in_factor_wrong); //因子中包含的表达式的错误结束
    }
    else
        error_exc(factor_wrong);
}
//条件语句
void condition_sen(treeNode *tn) {
    if (sym == "if") {
        tn->child.push_back(new treeNode("if"));
        sym = GETSYM();
        auto *rel_expressiont = new treeNode("比较表达式");
        tn->child.push_back(rel_expressiont);
        rel_expression(rel_expressiont);
        if (sym == "then") {
            tn->child.push_back(new treeNode("then"));
            sym = GETSYM();
            auto *sen_BLOCKt = new treeNode("语句");
            tn->child.push_back(sen_BLOCKt);
            //添加代码
            addCode("jpc", 0, -1); //地址等待回填
            int tmp = cx - 1;//tmp指向的是jpc指令的地址
            //
            sen_BLOCK(sen_BLOCKt);

            addCode("jmp", 0, -1);//无条件调到else之后，或调到下一条
            int tmp2 = cx - 1;
            //语句结束之后回填
            codes[tmp].offset = cx; //这里跳转的地址其实是if条件为假跳转的地址
            if (sym == "else") {
                tn->child.push_back(new treeNode("else"));
                auto* sen_BLOCKt2 = new treeNode("语句");
                tn->child.push_back(sen_BLOCKt2);

                sym = GETSYM();
                sen_BLOCK(sen_BLOCKt2);
            }
            codes[tmp2].offset = cx;//回填else后语句目标代码生成完的后一条指令的地址
            //
        }
        //if()
        else
            error_exc(if_then_wrong); //不是正确的if语句
    } else
        return;
}
//条件
//void condition(treeNode *tn) {
//    if (sym != "odd") {
//        auto * expressiont0 = new treeNode("表达式");//符号左边
//        tn->child.push_back(expressiont0);
//        expression(expressiont0);
//        if (sym == "=" || sym == "<>" || sym == "<" || sym == "<=" || sym == ">" || sym == ">=") {
//            string opr = sym;
//            auto *idt = new treeNode(sym);
//            tn->child.push_back(new treeNode("条件运算符"));
//            tn->child.back()->child.push_back(idt);
//            sym = GETSYM();
//            auto* expressiont1 = new treeNode("表达式");//符号右边
//            tn->child.push_back(expressiont1);
//            expression(expressiont1);
//            //添加代码
//            if (opr == "=")
//                addCode("opr", 0, EquOpr); //=运算
//            else if (opr == "<>")
//                addCode("opr", 0, NeqOpr); //<>运算
//            else if (opr == "<")
//                addCode("opr", 0, LessOpr); //<运算
//            else if (opr == "<=")
//                addCode("opr", 0, ElessOpr); //<=运算
//            else if (opr == ">")
//                addCode("opr", 0, GreOpr); //>运算
//            else if (opr == ">=")
//                addCode("opr", 0, EgreOpr); //>=运算
//
//            //
//        } 
//        else
//            error_exc(condition_wrong); //不是正确的比较运算符
//    } 
//    else {
//        string opr = sym;
//        tn->child.push_back(new treeNode("odd"));
//        sym = GETSYM();
//        auto *expressiont2 = new treeNode("表达式");
//        tn->child.push_back(expressiont2);
//        expression(expressiont2);
//        //添加代码
//        addCode("opr", 0, OddOpr); // odd运算
//        //
//    }
//}
//过程调用语句
void proc_call_sen(treeNode *tn) {
    if (sym == "call") {
        tn->child.push_back(new treeNode("call"));
        sym = GETSYM();
        if (sym == "identifier") {
            int real_paranum = 0;//记录实参的个数
            auto *idt = new treeNode(debugId);
            tn->child.push_back(new treeNode("标识符"));
            tn->child.back()->child.push_back(idt);
            //添加代码
            int labelAddr = findAddrInTable(debugId);//找到过程名在名字表中的位置
            if (labelAddr == -1)
                error_exc(var_undefined);
            if (tables[labelAddr].kind != "procedure") {
                error_exc(not_procedure_name);//被调用的不是过程
            }
            sym = GETSYM();
            if (sym == "(") {//如果过程没有参数，则不用加括号
                tn->child.push_back(new treeNode("("));
                sym = GETSYM();
                auto* rel_expressiont = new treeNode("比较表达式");
                tn->child.push_back(rel_expressiont);
                rel_expression(rel_expressiont);
                real_paranum++;//实参个数加1
                while (sym == ",") {
                    tn->child.push_back(new treeNode(","));
                    sym = GETSYM();
                    auto* rel_expressionts = new treeNode("比较表达式");
                    tn->child.push_back(rel_expressionts);
                    rel_expression(rel_expressionts);
                    real_paranum++;//实参个数加1
                }
                if (sym == ")") {
                    tn->child.push_back(new treeNode(")"));
                    sym = GETSYM();
                }
                else
                    error_exc(call_end_wrong); //不是正确的call语句结束
            }
            //判断实参与形参个数是否相等
            if(real_paranum!= tables[labelAddr].paranum)
                error_exc(real_para_wrong);//实参与形参个数不等
            //添加pas指令，实参上移3个单位
            addCode("pas", 0, real_paranum);
            float entryCode = codes[tables[labelAddr].addr].offset;
            //float entryCode = tables[labelAddr].addr;//这样就多一步jmp跳转
            addCode("cal", abs(tables[labelAddr].level - procedureLevel), entryCode);
            //
            //sym = GETSYM();
        } else
            error_exc(identifier_wrong); //不是标识符
    } 
    else
        return;
}
//当型循环语句
void do_while_sen(treeNode *tn) {
    if (sym == "while") {
        GLoopLevel++;//进入循环，循环层数+1
        tn->child.push_back(new treeNode("while"));
        int tmpCodeAddr = cx;//此时cx指向下一条循环将要生成的指令
        auto * rel_expressiont = new treeNode("条件");
        tn->child.push_back(rel_expressiont);

        sym = GETSYM();
        rel_expression(rel_expressiont);
        if (sym == "do") {
            tn->child.push_back(new treeNode("do"));
            sym = GETSYM();
            auto *sen_BLOCKt = new treeNode("语句");
            tn->child.push_back(sen_BLOCKt);
            //添加代码
            addCode("jpc", 0, -1); // while条件非真跳转
            int tmpCodeId = cx - 1;
            //
            sen_BLOCK(sen_BLOCKt);
            //添加代码
            addCode("jmp", 0, tmpCodeAddr); //跳转回while
            //回填非真跳转
            codes[tmpCodeId].offset = cx;
            //
            while (exitCount) {//存在exit语句
                if (exitList[exitCount - 1].LoopLevel == GLoopLevel) {//外层循环的exit最先加入
                    codes[exitList[exitCount - 1].cx].offset = cx;//exit语句生成的指令跳转地址回填
                    exitCount--;
                    exitList.pop_back();
                }
                else
                    break;
            }

            GLoopLevel--;//退出循环，循环层数-1；
        } 
        else
            error_exc(while_do_wrong); //不是正确的while_do语句
    } 
    else
        return;
}

//退出循环语句
void exit_sen(treeNode* tn) {
    if (sym == "exit") {
        tn->child.push_back(new treeNode("exit"));
        sym = GETSYM();
        if (sym == "(") {
            tn->child.push_back(new treeNode("("));
            sym = GETSYM();
            if (sym == ")") {
                tn->child.push_back(new treeNode(")"));
                sym = GETSYM();
                if (GLoopLevel) {
                    ExitList eexit;//结构体元素
                    addCode("jmp", 0, -1);//等待循环结束回填

                    eexit.cx = cx - 1;//cx-1表示指向刚生成的跳转指令的地址
                    eexit.LoopLevel = GLoopLevel;//记录循环层数
                    exitCount++;
                    exitList.push_back(eexit);
                }
                else
                    error_exc(exit_IsNotIn_while); //exit语句不在循环中
            }
            else
                error_exc(exit_wrong); //不是正确的exit语句
        }
        else
            error_exc(exit_wrong); //不是正确的exit语句
    }
}

//读语句
void read_sen(treeNode *tn) {
    if (sym == "read") {
        tn->child.push_back(new treeNode("read"));
        //添加代码
        addCode("opr", 0, ReadOpr); // read运算
        //
        sym = GETSYM();
        if (sym == "(") {
            tn->child.push_back(new treeNode("("));
            sym = GETSYM();
            if (sym == "identifier") {
                auto *idt = new treeNode(debugId);
                tn->child.push_back(new treeNode("标识符"));
                tn->child.back()->child.push_back(idt);
                //添加代码
                int labelAddr = findAddrInTable(debugId);
                if (labelAddr == -1)
                    error_exc(var_undefined);
                if (tables[labelAddr].kind != "var")
                    error_exc(read_var_wrong);//被读入的不是变量
                if(tables[labelAddr].type=="Boolean")
                    error_exc(read_Boolean_wrong);//Boolean类型变量无法被读入
                addCode("sto", abs(tables[labelAddr].level - procedureLevel), tables[labelAddr].addr);//每读入一个就存在变量对应的位置
                //
                sym = GETSYM();
            } else
                error_exc(identifier_wrong); //不是标识符
            while (sym == ",") {
                tn->child.push_back(new treeNode(","));
                //添加代码
                addCode("opr", 0, ReadOpr); // read运算
                //
                sym = GETSYM();
                if (sym == "identifier") {
                    auto *idt = new treeNode(debugId);
                    tn->child.push_back(new treeNode("标识符"));
                    tn->child.back()->child.push_back(idt);
                    //添加代码
                    int labelAddr = findAddrInTable(debugId);
                    if (labelAddr == -1)
                        error_exc(var_undefined);
                    if (tables[labelAddr].kind != "var")
                        error_exc(read_var_wrong);//被读入的不是变量
                    if (tables[labelAddr].type == "Boolean")
                        error_exc(read_Boolean_wrong);//Boolean类型变量无法被读入
                    addCode("sto", abs(tables[labelAddr].level - procedureLevel), tables[labelAddr].addr);
                    //
                    sym = GETSYM();
                }
            }
            if (sym == ")") {
                tn->child.push_back(new treeNode(")"));
                sym = GETSYM();
            } else
                error_exc(read_end_wrong); //不是正确的read语句结束
        } else
            error_exc(read_wrong); //不是正确的read语句
    } else
        return;
}
//写语句
void write_sen(treeNode *tn) {
    if (sym == "write") {
        tn->child.push_back(new treeNode("write"));
        sym = GETSYM();
        if (sym == "(") {
            tn->child.push_back(new treeNode("("));
            sym = GETSYM();
            auto *rel_expressiont = new treeNode("比较表达式");
            tn->child.push_back(rel_expressiont);
            rel_expression(rel_expressiont);
            //添加代码
            addCode("opr", 0, WriteOpr); // write运算
            addCode("opr", 0, ChaLineOpr);
            //
            while (sym == ",") {
                tn->child.push_back(new treeNode(","));
                sym = GETSYM();
                auto * rel_expressionts = new treeNode("比较表达式");
                tn->child.push_back(rel_expressionts);
                rel_expression(rel_expressionts);
                //添加代码
                addCode("opr", 0, WriteOpr); // write运算
                addCode("opr", 0, ChaLineOpr);
                //
            }
            if (sym == ")") {
                tn->child.push_back(new treeNode(")"));
                sym = GETSYM();
            } else
                error_exc(write_end_wrong); //不是正确的write语句结束
        } else
            error_exc(write_wrong); //不是正确的write语句
    } else
        return;
}
//复合语句，语句的
void complex_sen(treeNode *tn) {
    if (sym == "begin") {
        tn->child.push_back(new treeNode("begin"));
        sym = GETSYM();
        auto *sen_BLOCKt = new treeNode("语句");
        tn->child.push_back(sen_BLOCKt);
        sen_BLOCK(sen_BLOCKt);
        while (sym == ";") {
            tn->child.push_back(new treeNode(";"));
            sym = GETSYM();
            auto *sen_BLOCKts = new treeNode("语句");
            tn->child.push_back(sen_BLOCKts);
            sen_BLOCK(sen_BLOCKts);
        }
        if (sym == "end") {
            tn->child.push_back(new treeNode("end"));
            sym = GETSYM();
        } 
        else
            error_exc(complex_end_wrong); //不是正确的复合语句结束
    } 
    else
        return;
}
#endif // RUN_PL0_BLOCK_H
