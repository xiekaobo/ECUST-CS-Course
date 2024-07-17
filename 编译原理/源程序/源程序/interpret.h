
#ifndef RUN_PL0_INTERPRET_H
#define RUN_PL0_INTERPRET_H
#include "block.h"
#include <stack>
//codeEle currentCode;    //指令寄存器
int paranum = 0;        //参数个数
int pcReg;              //下一条目标指令地址
int spReg;              //栈顶寄存器，top
int bpReg;              //基地址寄存器，sp
//vector<int> runningStack;//运行栈
vector<float> runningStack;//运行栈

//名字表中var的value没有设置，在解释执行的时候赋值

void Interpret()
{
    cout << "开始执行" << endl;
    bool code_end = false;
    int cIndex = 0;     //代码序列索引
    //初始化运行栈，并添加静态链、动态链、返回地址
    runningStack.clear();
    runningStack.push_back(0);   //静态链入栈，直接外层
    runningStack.push_back(0);   //动态链入栈，老sp
    runningStack.push_back(0);   //返回地址入栈
    spReg = -1;
    pcReg = 0;
    bpReg = 0;
    while (cIndex < codes.size() && !code_end) {
        pcReg++;
        if (codes[cIndex].func == "lit") {
            spReg++;
            runningStack.push_back(codes[cIndex].offset);
        }
        else if (codes[cIndex].func == "lod") {//将层差
            spReg++;
            int tmpBpReg = bpReg;
            for (int i = 0; i < codes[cIndex].level_d; ++i)
                tmpBpReg = runningStack[tmpBpReg];        //根据当前过程的静态链查找层差大于0的基地址
            runningStack.push_back(runningStack[tmpBpReg + (int)codes[cIndex].offset]);
        }
        else if (codes[cIndex].func == "sto") {
            int tmpBpReg = bpReg;
            for (int i = 0; i < codes[cIndex].level_d; ++i)
                tmpBpReg = runningStack[tmpBpReg];        //根据当前过程的静态链查找层差大于0的基地址
            runningStack[tmpBpReg + (int)codes[cIndex].offset] = runningStack.back();
            runningStack.pop_back();
            spReg--;
        }
        else if (codes[cIndex].func == "cal") {
            int tmpBpReg = bpReg;
            for (int i = 0; i < codes[cIndex].level_d; ++i)
                tmpBpReg = runningStack[tmpBpReg];        //根据当前过程的静态链查找到真正的静态外层
            //runningStack.push_back(tmpBpReg);      //静态链
            //runningStack.push_back(bpReg);  //动态链，老sp
            //runningStack.push_back(pcReg);  //返回地址
            //pas指令已经开辟了空间
            runningStack[spReg + 1] = tmpBpReg;      //静态链
            runningStack[spReg + 2] = bpReg;  //动态链，老sp
            runningStack[spReg + 3] = pcReg; //返回地址
            bpReg = spReg + 1;              //修改基地址寄存器
            pcReg = codes[cIndex].offset;   //修改pc值
        }
        else if (codes[cIndex].func == "int") {//为变量开辟空间
            int tmpSpace = (int)codes[cIndex].offset - 3;
            runningStack.resize(runningStack.size()+tmpSpace);
            spReg = spReg + codes[cIndex].offset + paranum;//将栈顶指针移到最后一个变量上
        }
        else if (codes[cIndex].func == "jmp") {
            pcReg = codes[cIndex].offset;
        }
        else if (codes[cIndex].func == "jpc") {
            if (runningStack[spReg] == 0) {
                pcReg = codes[cIndex].offset;
            }
            spReg--;
            runningStack.pop_back();
        }
        else if (codes[cIndex].func == "pas") {
            paranum = (int)codes[cIndex].offset;//被调用过程的实参个数
            runningStack.resize(runningStack.size() + 3);//之后将实参整体往上以3个单元
            for (int k = paranum; k > 0; k--) {
                runningStack[spReg + 3] = runningStack[spReg];
                spReg--;//最后栈顶指针回到了，被调用过程的静态链前一个单位
            }
        }
        else if (codes[cIndex].func == "opr") {
            switch ((int)codes[cIndex].offset) {
                case ReturnOpr: {
                    if (pcReg == codes.size()) {
                        code_end = true;
                        cout << "程序结束" << endl;
                    }
                    int count = (int)runningStack.size() - bpReg;
                    spReg = bpReg - 1;
                    bpReg = runningStack[spReg+2];      //动态链内容，修改基地址寄存器
                    pcReg = runningStack[spReg+3];      //修改pc寄存器，此处栈位置是返回地址
                    //出栈
                    runningStack.resize(runningStack.size()-count);
                    break;
                }
                case MinusOpr: {
                    runningStack[spReg] = -runningStack[spReg];
                    break;
                }
                case AddOpr: {
                    spReg--;
                    runningStack[spReg] += runningStack[spReg+1];
                    runningStack.pop_back();
                    break;
                }
                case SubOpr: {
                    spReg--;
                    runningStack[spReg] -= runningStack[spReg+1];
                    runningStack.pop_back();
                    break;
                }
                case MulOpr: {
                    spReg--;
                    runningStack[spReg] *= runningStack[spReg+1];
                    runningStack.pop_back();
                    break;
                }
                case DivOpr: {
                    spReg--;
                    runningStack[spReg] = (int)(runningStack[spReg] / runningStack[spReg+1]);
                    runningStack.pop_back();
                    break;
                }
                case OddOpr: {
                    runningStack[spReg] = (int)runningStack[spReg] % 2;
                    break;
                }
                case ModOpr: {
                    spReg--;
                    runningStack[spReg] = (int)runningStack[spReg] % (int)runningStack[spReg + 1];
                    runningStack.pop_back();
                    break;
                }
                case EquOpr: {
                    spReg--;
                    runningStack[spReg] = (runningStack[spReg] == runningStack[spReg+1]);
                    runningStack.pop_back();
                    break;
                }
                case NeqOpr: {
                    spReg--;
                    runningStack[spReg] = (runningStack[spReg] != runningStack[spReg+1]);
                    runningStack.pop_back();
                    break;
                }
                case LessOpr: {
                    spReg--;
                    runningStack[spReg] = (runningStack[spReg] < runningStack[spReg+1]);
                    runningStack.pop_back();
                    break;
                }
                case EgreOpr: {
                    spReg--;
                    runningStack[spReg] = (runningStack[spReg] >= runningStack[spReg+1]);
                    runningStack.pop_back();
                    break;
                }
                case GreOpr: {
                    spReg--;
                    runningStack[spReg] = (runningStack[spReg] > runningStack[spReg+1]);
                    runningStack.pop_back();
                    break;
                }
                case ElessOpr: {
                    spReg--;
                    runningStack[spReg] = (runningStack[spReg] <= runningStack[spReg+1]);
                    runningStack.pop_back();
                    break;
                }
                case WriteOpr: {
                    cout << "向屏幕输出：" << runningStack.back();
                    spReg--;
                    runningStack.pop_back();
                    break;
                }
                case ChaLineOpr: {
                    cout << endl;
                    break;
                }
                case ReadOpr: {
                    spReg++;
                    int cinTmp;
                    cout << "从键盘读入：";
                    cin >> cinTmp;
                    getchar();
                    runningStack.push_back(cinTmp);
                    //cout << "输入完成" << endl;
                    break;
                }
                case AndOpr: {
                    spReg--;
                    runningStack[spReg] = (runningStack[spReg] && runningStack[spReg + 1]);
                    runningStack.pop_back();
                    break;
                }
                case OrOpr: {
                    spReg--;
                    runningStack[spReg] = (runningStack[spReg] || runningStack[spReg + 1]);
                    runningStack.pop_back();
                    break;
                }
                case AntiOpr: {
                    runningStack[spReg] = !runningStack[spReg];
                    break;
                }
                case RDivOpr: {
                    spReg--;
                    runningStack[spReg] = runningStack[spReg] / runningStack[spReg + 1];
                    runningStack.pop_back();
                    break;
                }
                default: {
                    break;
                }
            }
        }
        cIndex = pcReg;
    }
}

#endif //RUN_PL0_INTERPRET_H
