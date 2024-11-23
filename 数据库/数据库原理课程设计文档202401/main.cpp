#include"operatingLanguage.h"

using namespace std;
namespace fs = std::filesystem;

vector<Database> databases_now;

int main() {
    //获取登录用户名
    fs::path userloadingPath = "D:\\ABC.txt";
    ifstream inputFile(userloadingPath);
    if (inputFile.is_open()) {
        getline(inputFile, user_now.userName);
        inputFile.close();
    }
    else {
        std::cerr << "获取登录用户失败" << std::endl;
    }

    //初始化非关系型数据库
    Initial(user_now.userName);

    //指令操作
    string line;
    while(true){
        cout << "\n请输入指令：" << endl;
        getline(cin, line);
        // 检查退出条件
        if (line == "exit") {
            cout << "系统已退出" << endl;;
            break;
        }
        else {
            instruction.assign(line.begin(), line.end());
            identifyInstruction();
        }
    }
    return 0;
}
