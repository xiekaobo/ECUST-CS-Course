#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<vector>
#include <filesystem>
#include <fstream>
#include <string>

using namespace std;
namespace fs = std::filesystem;

// 获取桌面的绝对路径
fs::path desktopPath = fs::path(getenv("USERPROFILE")) / "Desktop";
fs::path NoSQLPath;             //非关系型数据库管理系统存储路径
fs::path userPath;              //用户数据路径
fs::path databasePath;          //当前数据库路径
fs::path newPath;               //临时路径

//文档类
class Document {
public:
    string document_name ;
    string content;

    Document() {}
    Document(string name,string s) {
        document_name = name;
        content = s;
    }

    //展示文档
    void showDocument() {
        cout << "文档名称:" << document_name << endl;
        cout << "文档内容:" << content << endl;
    }
};

//集合类
class Collection {
public:
    string collection_name ;
    vector<Document> documents;
    Collection() {}
    Collection(string name) {
        collection_name = name;
    }

    // 插入文档
    void insertDocument(Document& document) {
        if (findDocument(document.document_name)==nullptr) {
            newPath = databasePath / collection_name / document.document_name;
            ofstream outputFile(newPath);
            if (outputFile.is_open()) {
                outputFile << document.content << endl;
                outputFile.close();
            }
            else {
                std::cerr << "Error creating document." << std::endl;
            }
            documents.push_back(document);
            cout << "文档插入成功" << endl;
        }
        else {
            cout << "文档已存在" << endl;
        }
    }

    // 查询文档
    Document* findDocument(string document_name) {
        auto it = find_if(documents.begin(), documents.end(),
            [document_name](Document& doc) {
                return doc.document_name == document_name;
            });

        if (it != documents.end()) {
            cout << "文档查询成功" << endl;
            return addressof(*it);
        }
        else {
            cout << "文档查询失败" << endl;
            return nullptr;
        }
    }

    // 更新文档
    void updateDocument(string document_name, string s) {
        if (findDocument(document_name) != nullptr) {
            findDocument(document_name)->content = s;
            newPath = databasePath / collection_name / document_name;
            ofstream outputFile(newPath, ios::trunc);
            if (outputFile.is_open()) {
                outputFile << s << endl;
                outputFile.close();
                cout << "文档修改成功" << endl;
            }
            else {
                std::cerr << "文档打开失败" << std::endl;
            }
        }
        else {
            cout << "文档修改失败" << endl;
        }
    }

    // 删除文档
    void deleteDocument(string document_name) {
        if (findDocument(document_name) != nullptr) {
            newPath = databasePath / collection_name / document_name;
            fs::remove_all(newPath);
            documents.erase(std::remove_if(documents.begin(), documents.end(),
                [document_name](Document& doc) {
                    return doc.document_name == document_name;
                }),
                documents.end());
            cout << "文档删除成功" << endl;
        }
        else {
            cout << "文档删除失败" << endl;
        }
    }

    //展示集合
    void showCollection() {
        cout << "集合名称:" << collection_name << endl;
        for (int i = 0; i < documents.size(); i++)
            documents[i].showDocument();
    }
};

//数据库类
class Database {
public:
    string database_name ;
    vector<Collection> collections;
    Database() {}
    Database(string name) {
        database_name = name;
    }

    // 插入集合
    void insertCollection(string collection_name) {
        if (findCollection(collection_name) == nullptr) {
            newPath = userPath / database_name / collection_name;
            fs::create_directory(newPath);
            collections.push_back(Collection(collection_name));
            cout << "集合插入成功" << endl;
        }
        else {
            cout << "集合已存在" << endl;
        }
    }

    // 查询集合
    Collection* findCollection(string collection_name) {
        auto it = find_if(collections.begin(), collections.end(),
            [collection_name](Collection& col) {
                return col.collection_name == collection_name;
            });

        if (it != collections.end()) {
            cout << "集合查询成功" << endl;
            return addressof(*it);
        }
        else {
            cout << "集合查询失败"<<endl;
            return nullptr;
        }
    }

    // 删除集合
    void deleteCollection(string collection_name) {
        if (findCollection(collection_name) != nullptr) {
            newPath = userPath / database_name / collection_name;
            fs::remove_all(newPath);
            collections.erase(remove_if(collections.begin(), collections.end(),
                [collection_name](Collection& col) {
                    return col.collection_name == collection_name;
                }),
                collections.end());
            cout << "集合删除成功" << endl;
        }
        else {
            cout << "集合删除失败" << endl;
        }
    }

    //展示数据库
    void showDatabase() {
        cout << "数据库名称:" << database_name << endl;
        for (int i = 0; i < collections.size(); i++)
            collections[i].showCollection();
    }
};

class User {
public:
    string userName;
    vector<Database> databases;
    User() {}
    User(string name) {
        userName = name;
    }

    // 插入数据库
    void insertDatabase(string database_name) {
        if (findDatabase(database_name) == nullptr) {
            newPath = userPath / database_name;
            fs::create_directory(newPath);
            databases.push_back(Database(database_name));
            cout << "数据库插入成功" << endl;
        }
        else {
            cout << "数据库已存在" << endl;
        }
    }

    // 查询数据库
    Database* findDatabase(string database_name) {
        auto it = find_if(databases.begin(), databases.end(),
            [database_name](Database& dat) {
                return dat.database_name == database_name;
            });

        if (it != databases.end()) {
            cout << "数据库查询成功" << endl;
            return addressof(*it);
        }
        else {
            cout << "数据库查询失败" << endl;
            return nullptr;
        }
    }

    // 删除数据库
    void deleteDatabase(string database_name) {
        if (findDatabase(database_name) != nullptr) {
            newPath = userPath / database_name;
            fs::remove_all(newPath);
            databases.erase(remove_if(databases.begin(), databases.end(),
                [database_name](Database& dat) {
                    return dat.database_name == database_name;
                }),
                databases.end());
            cout << "数据库删除成功" << endl;
        }
        else {
            cout << "数据库删除失败" << endl;
        }
    }
};

User user_now = User();

void Initial(string username) {
    // 检查桌面目录是否获取
    if (fs::exists(desktopPath)) {
        std::cout << "桌面路径已获取" << std::endl;

        //创建非关系型数据库管理系统存储目录
        NoSQLPath = desktopPath / "NoSQL_store";
        if (!fs::exists(NoSQLPath)) {
            fs::create_directory(NoSQLPath);
            std::cout << "非关系型数据库目录创建成功 " << std::endl;
        }
        else {
            cout << "非关系型数据库目录已存在" << std::endl;
        }

        //创建用户目录
        userPath = NoSQLPath / username;
        databasePath = userPath;
        if (!fs::exists(userPath)) {
            fs::create_directory(userPath);
            std::cout << "登录用户第一次使用非关系型数据库管理系统，已初始化完成 " << std::endl;
        }
        else {
            try {
                //获取用户相关数据至程序运行内存
                for (auto& entry1 : fs::directory_iterator(userPath)) {//遍历用户目录
                    if (fs::is_directory(entry1.status())) {
                        user_now.databases.push_back(Database(entry1.path().filename().string()));
                        for (auto& entry2 : fs::directory_iterator(entry1.path())) {//遍历数据库目录
                            if (fs::is_directory(entry2.status())) {
                                user_now.databases.back().collections.push_back(Collection(entry2.path().filename().string()));
                                for (auto& entry3 : fs::directory_iterator(entry2.path())) {//遍历集合目录
                                    if (fs::is_regular_file(entry3.status())) {//获取文档数据
                                        Document tempDoc;
                                        tempDoc.document_name = entry3.path().filename().string();
                                        ifstream inputFile(entry3.path());
                                        if (inputFile.is_open()) {
                                            string content;
                                            while (getline(inputFile, content)) {
                                                tempDoc.content += content + '\n';
                                            }
                                            inputFile.close();
                                            user_now.databases.back().collections.back().documents.push_back(tempDoc);
                                        }
                                        else {
                                            std::cerr << "Error opening file." << std::endl;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            catch (const fs::filesystem_error& e) {
                std::cerr << "Error accessing the folder: " << e.what() << std::endl;
            }
            cout << "非关系型数据库管理系统已加载完成" << std::endl;
        }
    }
    else {
        cerr << "桌面路径未找到" << std::endl;
    }
}