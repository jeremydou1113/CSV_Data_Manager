//
//  CSV去重整合(第一列).cpp
//  CSV_Data_Collector
//
//  Created by Chaoyao Dou at ByteDance on 2020/12/28.
//
//  本程序由窦超耀使用C++编写，仅可用作学习交流与工作中的数据处理的用途，不可用做商业盈利
//
//  使用方法：
//  1. 使用Xcode创建一个C++ Project，将原本的main.cpp文件删除后再将此cpp文件拖入
//                                或
//     将原本main.cpp中的代码全部删除，复制黏贴此处全部代码
//  2. 在Xcode右边菜单栏打开本文件的Target Membership
//  3. 在Edit Scheme-Options中调整本程序的Working Directory，将需要处理的CSV文件移动到与本程序相同的Working Directory，请确保Working Directory中没有已经存在名为result.csv和result.txt的文件
//  4. 务必将CSV文件名改为英文或数字，并确保在之后的输入中名字正确，并在初始数据导出时确保CSV中的数据都是文本格式
//  5. 点击Xcode上方菜单栏的“播放”按钮启动程序
//  6. 按程序提示进行一步步的操作
//  7. 程序结束后前往Working Directory查看result.txt以及result.csv文件
//  8. 如中途出现错误可以点击Xcode上方菜单栏”播放“按钮旁边的”中止“按钮随时中断程序并从第五步重新开始尝试
//

#include <stdio.h>

using namespace std;

#include <fstream>
#include <iostream>
#include <unordered_set>
#include <vector>
#include <string>

int main(int argc, const char * argv[]) {
    // Intro
    int num_files = 0;
    int num_items_read = 0;
    cout << "欢迎使用CSV数据整理工具，本程序可以读取多个百万量级的CSV文件，将每个CSV文件首列去重，然后将去重后的数据整合到文本txt以及csv文件里（第一列）\n";
    cout << "在开始使用程序前，在原始数据导出时请将CSV中的数据全部手动更换为文本格式\n";
    cout << "请注意：C++最高可处理的数字范围为-2147483648到2147483647\n";
    cout << "在使用本程序前，请先设置Edit Scheme中的Options中设置Working Directory\n";
    cout << "并把需要整理的CSV文件与本程序放置于同一个Working Directory中\n";
    cout << "请确保Working Directory中没有已经存在名为result.csv和result.txt的文件\n";
    cout << "\n";
    cout << "请问有多少个CSV文件需要进行处理？\n";
    cin >> num_files;
    cout << "\n";
    
    // 获取文件名称
    vector<string> file_names;
    cout << "请确保CSV文件的所在文件夹与本程序所在文件夹地址一致，请确保文件名输入正确，不正确的文件名或文件地址会导致程序无法读取文件\n";
    cout << "请确保本程序所在的文件夹没有已存在名叫result.txt以及result.csv的文件\n";
    for (int i = 0; i < num_files; ++i) {
        cout << "\n";
        cout << "请输入第" << i + 1 << "份CSV文件的文件名（要求：文件名必须是英文名或数字，不要使用中文输入法，输入时请包括.csv后缀，输入完成点击回车键）：\n";
        string file_name;
        cin >> file_name;
        file_names.push_back(file_name);
    }
    
    cout << "\n";
    cout << "*****************\n";
    cout << "***读取中，请稍候***\n";
    cout << "*****************\n";
    
    // 打开文件，读取文件，进行去重
    for (int i = 0; i < num_files; ++i) {
        // 打开文件，创建stream
        ifstream CSVFile(file_names[i]);
        // File Status Check
        if(!CSVFile.is_open()) {
            throw std::runtime_error("文件无法打开/文件找不到/文件名错误");
        }
        //关闭读取完的文件
        CSVFile.close();
    }
    
    cout << "\n";
    cout << "*****************\n";
    cout << "***整理中，请稍候***\n";
    cout << "*****************\n";
    
    // 存储现有data到一个unordered_set中去
    unordered_set<string> data;
    // 开始创建结果整合文件，文件名将会为result.txt以及result.csv
    ofstream Result_txt_File("result.txt");
    ofstream Result_csv_File("result.csv");
    for (int i = 0; i < num_files; ++i) {
        ifstream CSVFile(file_names[i]);
        while (CSVFile.good()) {
            string first_col_content;
            string rest_cols;
            getline(CSVFile, first_col_content, ',');
            getline(CSVFile, rest_cols); // 读取第一列后的数据
            if (data.find(first_col_content) == data.end()) { // 查重，只有不重复的数据才会被添加
                data.insert(first_col_content);
                num_items_read++;
                Result_txt_File << first_col_content << endl;
                Result_csv_File << first_col_content << endl;
            }
        }
        CSVFile.close();
    }
    
    // 关闭结果文件，数据整合完成，程序结束
    Result_txt_File.close();
    Result_csv_File.close();
    
    num_items_read--;   // 减去CSV文件中第一行的“种类名称”信息条数量
    
    cout << "\n";
    cout << "**************************\n";
    cout << "***整理结束，共计" << num_items_read << "行有效信息***\n";
    cout << "**************************\n";
    
    cout << "\n";
    cout << "********************************************************************\n";
    cout << "***整理结束，请前往程序所在文件夹查看result.txt以及result.csv文件，谢谢使用***\n";
    cout << "********************************************************************\n";
    cout << "\n";
    
    return 0;
}


