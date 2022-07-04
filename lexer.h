#ifndef LEXER_H
#define LEXER_H

#include "tag.h"
#include "symbolTable.h"
#include <string>
#include <fstream>

using std::string;
using std::ifstream;

struct VarAttr
{
    //变量属性,用于说明语句和赋值语句等等
    int table_i;		//变量所在的符号表下标
    int item_i;			//变量在符号表中的下标
    int place;			//标记该非终结符对应的符号表项
    ArgType type;
};
struct BoolAttr
{
    int true_list;
    int false_list;
};
struct CtrlAttr
{
    int next_list;
    int quad;
};
struct FunAttr
{
    int param_num;
};
union VN_Attr
{
    //非终结符属性,用于存入栈中
    VarAttr		var_attr;
    BoolAttr	bool_attr;
    CtrlAttr	ctrl_attr;
    FunAttr		fun_attr;
};
struct TokenInfo
{
    //词法单元的其他信息
    int line;
    int col;
    std::string why;
};
struct Token		//文法符号的标识符和属性,用于存放在输入栈内
{
    Tag tag;
    VN_Attr attr;
    std::string value;			//变量名/值
    TokenInfo info;
};

class Lexer
{
private:
    char peek;
    int line;		//当前行
    int col;		//当前列
    ifstream file_in;

    bool getNextChar(char&, const bool = true);

public:
    Lexer();
    ~Lexer();

    //打开输入文件
    bool openFile(const char*);

    //清空数据
    void clear_data();

    //获取下一个词法单元
    State getNextLexical(Token& next_token);
    //扫描整个文件并输出词法分析结果
    State scanFile(const char*);
};

#endif // !LEXER_H
