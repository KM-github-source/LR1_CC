#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iomanip>

#include "symbolTable.h"

using namespace std;

string SymbolTable::getName(int place)
{
    return table_list.back()[place].value;
}

void SymbolTable::mkTable(int quad)
{
    table_entrys.push_back(quad);
    table_list.push_back({});
    table_map_list.push_back({});
    table_list.back().push_back({});		//为函数自身留一个位置
}

int SymbolTable::addVar(string value, ArgType type, bool is_inst, string newtype, string newname)
{
    if ("" == newname)
    {
        //自动生成新名称
        if (1 >= table_list.size())
            newname = "G";
        else
            newname = "T";
        newname += to_string(table_list.back().size());
    }
    if (value == "")	//临时变量的特殊处理
        value = "T" + to_string(table_list.back().size());
    table_list.back().push_back({ value, type, is_inst, newtype, newname });
    table_map_list.back()[value] = table_list.back().size() - 1;		//id -> 符号表中的下标
    return table_list.back().size() - 1;
}

int SymbolTable::addGlobalVar(string value, ArgType type, bool is_inst, string newtype, string newname)
{
    if ("" == newname)
        newname += "G" + (table_list.back().size());
    if (value == "")	//临时变量的特殊处理
        value = "G" + to_string(table_list.front().size());
    table_list.front().push_back({ value, type, is_inst, newtype, newname });
    table_map_list.front()[value] = table_list.front().size() - 1;		//id -> 符号表中的下标
    return table_list.front().size() - 1;
}

void SymbolTable::displayTable(ofstream& des)
{
    const int width = 12;
    for (int i = 0; i < table_list.size(); i++)
    {
        //全局符号表
        if (i == 0)
        {
            des << i << " Global SymbolTable:\n";
            des << setiosflags(ios::left) << setw(width) << "tmp_name" << setw(width) << "name/value" << setw(width) << "type" << setw(width) << "is_inst" << setw(width) << "entry" << "\n";
        }
        else
        {
            des << i << " F" << i << " SymbolTable:\n";
            des << setiosflags(ios::left) << setw(width) << "tmp_name" << setw(width) << "name/value" << setw(width) << "type" << setw(width) << "is_inst" << setw(width) << "entry" << "\n";
            des << setw(width) << " ";
            des << setw(width) << table_list[i][0].value;
            des << setw(width) << ITEMTYPE2STR.at(table_list[i][0].type);
            des << setw(width) << (table_list[i][0].is_inst ? "true" : "false");
            des << setw(width) << table_entrys[i] << "\n";
        }
        for (int k = 1; k < table_list[i].size(); k++)
        {
            string tmp_name = "T" + to_string(k) + ":";
            des << setw(width) << tmp_name;
            des << setw(width) << table_list[i][k].value;
            des << setw(20) << table_list[i][k].newname;
//            des << setw(width) << ITEMTYPE2STR.at(table_list[i][k].type);
//            des << setw(width) << table_list[i][k].newtype;
            des << setw(width) << (table_list[i][k].is_inst ? "true" : "false") << "\n";
        }
        des << "\n";
    }
}

void SymbolTable::clear()
{
    this->table_list.clear();
    this->table_entrys.clear();
    this->funcname2index.clear();
    this->table_map_list.clear();
}


SymbolTable symbol_table;	//全局定义符号表对象

const std::map<ArgType, std::string> ITEMTYPE2STR = {
    {ArgType::t_int_var,"int"},
    {ArgType::t_int_func,"int_func"},
    {ArgType::t_void_func,"void_func"},
};
