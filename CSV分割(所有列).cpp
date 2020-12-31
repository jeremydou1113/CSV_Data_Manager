//
//  CSV分割(所有列).cpp
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
//  3. 在Edit Scheme-Options中调整本程序的Working Directory，将需要处理的CSV文件移动到与本程序相同的Working Directory，请确保Working Directory中没有已经存在名为result.csv, result.txt, remainder.csv, remainder.txt的文件
//  4. 务必将CSV文件名改为英文或数字，并确保在之后的输入中名字正确，并在初始数据导出时确保CSV中的数据都是文本格式
//  5. 点击Xcode上方菜单栏的“播放”按钮启动程序
//  6. 按程序提示进行一步步的操作
//  7. 程序结束后前往Working Directory查看result.csv, result.txt, remainder.csv, remainder.txt文件
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
    string file_name;
    int num_line = 0;
    int num_items_read_result = 0;
    int num_items_read_remainder = 0;
    
    cout << "欢迎使用CSV数据整理工具，本程序可以读取单个百万量级的CSV文件，根据用户需要，从特定行数对CSV文件进行分割，最后给出分割后CSV文件，和剩余CSV文件\n";
    cout << "注意：本程序只会含有CSV文件中的全部列数据，如需包含第一列，请使用CSV分割(第一列).cpp\n";
    cout << "在开始使用程序前，在原始数据导出时请将CSV中的数据全部手动更换为文本格式\n";
    cout << "请注意：C++最高可处理的整数数字范围为-2147483648到2147483647\n";
    cout << "在使用本程序前，请先设置Edit Scheme中的Options中设置Working Directory\n";
    cout << "并把需要整理的CSV文件与本程序放置于同一个Working Directory中\n";
    cout << "请确保Working Directory中没有已经存在名为result.csv, result.txt, remainder.csv, remainder.txt的文件\n";
    
    cout << "\n";
    
    cout << "请问需要分割的CSV文件名是什么？\n";
    cout << "请输入CSV文件的文件名（要求：文件名必须是英文名或数字，不要使用中文输入法，输入时请包括.csv后缀，输入完成点击回车键): \n";
    cin >> file_name;
    cout << "\n";
    cout << "请问想从此CSV文件中的哪一行进行分割?\n";
    cout << "请输入数字 (例：如输入3，本程序将会把CSV文件中第一行到第三行的信息分割成一个文件，剩余行信息分割到另外一个文件): \n";
    cin >> num_line;
    ifstream CSVFile(file_name);
    if(!CSVFile.is_open()) {
        throw std::runtime_error("文件无法打开/文件找不到/文件名错误");
    }
    
    string first_row;
    getline(CSVFile, first_row);
    
    ofstream Result_txt_File("result.txt");
    ofstream Result_csv_File("result.csv");
    
    ofstream Remainder_txt_File("remainder.txt");
    ofstream Remainder_csv_File("remainder.csv");
    
    Result_txt_File << first_row;
    Result_csv_File << first_row;
    for (int i = 0; i < num_line; ++i) {
        string first_col_content;
        string rest_cols;
        getline(CSVFile, first_col_content, ',');
        getline(CSVFile, rest_cols); // 读取第一列后的数据
        Result_txt_File << first_col_content << ", " << rest_cols << endl;
        Result_csv_File << first_col_content << ", " << rest_cols << endl;
        num_items_read_result++;
    }
    
    Remainder_csv_File << first_row;
    Remainder_txt_File << first_row;
    while (CSVFile.good()) {
        string first_col_content;
        string rest_cols;
        getline(CSVFile, first_col_content, ',');
        getline(CSVFile, rest_cols); // 读取第一列后的数据
        Remainder_txt_File << first_col_content << ", " << rest_cols << endl;
        Remainder_csv_File << first_col_content << ", " << rest_cols << endl;
        num_items_read_remainder++;
    }
    
    cout << "\n";
    cout << "*****************\n";
    cout << "***处理中，请稍候***\n";
    cout << "*****************\n";
    
    cout << "\n";
    cout << "**************************************\n";
    cout << "***分割结束，被分割文件中，共计" << num_items_read_result << "行有效信息***\n";
    cout << "**************************************\n";
    
    cout << "\n";
    
    cout << "********************************************************\n";
    cout << "***请前往本程序所在文件夹查看分割文件result.csv, result.txt***\n";
    cout << "********************************************************\n";
    
    cout << "\n";
    cout << "***************************************\n";
    cout << "***整理结束，分割剩余文件中，共计" << num_items_read_remainder << "行有效信息***\n";
    cout << "***************************************\n";
    
    cout << "\n";
    
    cout << "*****************************************************************\n";
    cout << "***请前往本程序所在文件夹查看分割剩余文件remainder.csv, remainder.txt***\n";
    cout << "*****************************************************************\n";
    
    cout << "\n";
    
    CSVFile.close();
    
    Result_txt_File.close();
    Result_csv_File.close();
    Remainder_txt_File.close();
    Remainder_csv_File.close();
    
    return 0;
}

