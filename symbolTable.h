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
    std::string value;      //������
    ArgType type;           //��������
    bool is_inst;           //�Ƿ�Ϊ����
    //new
    std::string newtype;
    std::string newname;	//�ڷ��ű��и��µ�����
};

class SymbolTable
{
public:
    //�ǵø�Ϊprivate
    std::vector<int> table_entrys;			//���Ӧ�ĺ�������ʼ��ַ
    std::vector<std::vector<TableItem>> table_list;
    std::vector<std::map<std::string, int>> table_map_list;
    std::map<std::string, int> funcname2index;	//������Ӧ��table_list���±�

    void mkTable(int);
    int addVar(std::string, ArgType, bool, std::string = "", std::string = "");
    int addGlobalVar(std::string, ArgType, bool, std::string = "", std::string = "");
    std::string getName(int);
    void displayTable(std::ofstream&);

    void clear();

private:

};

extern SymbolTable symbol_table;	//ȫ�ֶ�����ű����
extern const std::map<ArgType, std::string> ITEMTYPE2STR;

#endif // !SYMBOLTABLE_H
