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
    //��������,����˵�����͸�ֵ���ȵ�
    int table_i;		//�������ڵķ��ű��±�
    int item_i;			//�����ڷ��ű��е��±�
    int place;			//��Ǹ÷��ս����Ӧ�ķ��ű���
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
    //���ս������,���ڴ���ջ��
    VarAttr		var_attr;
    BoolAttr	bool_attr;
    CtrlAttr	ctrl_attr;
    FunAttr		fun_attr;
};
struct TokenInfo
{
    //�ʷ���Ԫ��������Ϣ
    int line;
    int col;
    std::string why;
};
struct Token		//�ķ����ŵı�ʶ��������,���ڴ��������ջ��
{
    Tag tag;
    VN_Attr attr;
    std::string value;			//������/ֵ
    TokenInfo info;
};

class Lexer
{
private:
    char peek;
    int line;		//��ǰ��
    int col;		//��ǰ��
    ifstream file_in;

    bool getNextChar(char&, const bool = true);

public:
    Lexer();
    ~Lexer();

    //�������ļ�
    bool openFile(const char*);

    //�������
    void clear_data();

    //��ȡ��һ���ʷ���Ԫ
    State getNextLexical(Token& next_token);
    //ɨ�������ļ�������ʷ��������
    State scanFile(const char*);
};

#endif // !LEXER_H
