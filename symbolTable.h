#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <iostream>
#include <vector>
#include <map>
#include <fstream>
using namespace std;

enum class ArgType
{
    t_int_var = 0,
    t_int_func,
    t_void_func,
    t_int_arr,
};
struct TableItem
{
    std::string value;      //变量名
    ArgType type;           //数据类型
    bool is_inst;           //是否为常量
    //new
    std::string newtype;
    std::string newname;	//在符号表中更新的名称
};

class SymbolTable
{
public:
    //记得改为private
    std::vector<int> table_entrys;			//表对应的函数的起始地址
    std::vector<std::vector<TableItem>> table_list;
    std::vector<std::map<std::string, int>> table_map_list;
    std::map<std::string, int> funcname2index;	//函数对应的table_list的下标

    void mkTable(int);
    int addVar(std::string, ArgType, bool, std::string = "", std::string = "");
    int addGlobalVar(std::string, ArgType, bool, std::string = "", std::string = "");
    std::string getName(int);
    void displayTable(std::ofstream&);

    void clear();

private:

};

extern SymbolTable symbol_table;	//全局定义符号表对象
extern const std::map<ArgType, std::string> ITEMTYPE2STR;

#endif // !SYMBOLTABLE_H
