#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H

#include "common.h"
#include "tag.h"
#include "symbolTable.h"
#include "lexer.h"

#define DEFAULT_LOC -1

struct TarCode
{
    std::string op;
    int arg1;
    int arg2;
    int arg3;
    int arg1_p;
    int arg2_p;
    int arg3_p;
};

struct Code
{
    //Tag op;
    std::string op;
    int arg1;
    int arg2;
    int result;
    int arg1_p;		//�Ƿ�Ϊȫ�ֱ���
    int arg2_p;
    int result_p;
    //new
    std::string sarg1;
    std::string sarg2;
    std::string sresult;
    int last_index;
};

/* new here */

struct InfoPair
{
    //����λ��
    int useLoc;
    //��Ծ��Ϣ��true��ʾ��Ծ
    bool isActive;
};

struct InfoTableRow
{
    //�м���Ԫʽ����
    int code;
    //��ֵ������������Ҳ�����
    std::vector<InfoPair> params;
};

struct CodeBlock
{
    int start;
    int end;
    //���ű��±�
    int tablePoin;
    //��׺��������ʼ�±�
    std::vector<int> suffix;
    //������0����ȫ�ֱ�����1����ֲ����������������ʱ���Լ�����չ
    std::vector<std::vector<int>> vars;
    std::vector<std::vector<int>> linkedP;
    //��ڻ�Ծ����
    std::vector<std::vector<int>> activeVars;
    //���û�Ծ��Ϣ����
    //Forȫ�ֱ���
    std::vector<std::vector<InfoPair>> linkedInfoG;
    std::map<int, int> mapForG;
    //For�ֲ�����
    std::vector<std::vector<InfoPair>> linkedInfoL;
    std::map<int, int> mapForL;
    //���û�Ծ��Ϣ��
    std::vector<InfoTableRow> infoTable;
    //�Ĵ�����
    //����������Щ�Ĵ���
    std::vector<std::vector<int>> AVALUE;
    //�Ĵ����а�����Щ����
    std::vector<std::vector<int>> RVALUE;
};

/* new here */

class CodeGenerator
{
private:
    Token err_token;		//�������������Ϣ
    std::vector<Code> code_list;
    std::vector<TarCode> tarCode_list;

private:
    //һϵ�и�������
    void gen(std::string, int, int, int, int = CodeGenerator::ARG_LOCALVAR, int = CodeGenerator::ARG_LOCALVAR, int = CodeGenerator::ARG_LOCALVAR, string = "", string = "", string = "", int = 0);
    void genTar(std::string op, int arg1, int arg2, int arg1_p, int arg2_p, int arg3 = -1, int arg3_p = -1);
    int merge(int list_1, int list_2);
    void backpatch(int back_list, int quad);

    State transGetpos(Token&, const std::vector<Token>&);
    State transMktable(Token&, const std::vector<Token>&);

    State transDeclareVar(Token&, const std::vector<Token>&);
    State transDeclareFunc(Token&, const std::vector<Token>&);
    State transDeclareProgram(Token&, const std::vector<Token>&);

    State transStatKeep(Token&, const std::vector<Token>&);
    State transStatStr2StatStr(Token&, const std::vector<Token>&);

    State transAssign(Token&, const std::vector<Token>&);
    State transAssignKeep(Token&, const std::vector<Token>&);
    State transAssignBina(Token&, const std::vector<Token>&);	//˫Ŀ����
    State transAssignCmp(Token&, const std::vector<Token>&);	//�Ƚ������

    State transBoolKeep(Token&, const std::vector<Token>&);
    State transBoolOr(Token&, const std::vector<Token>&);
    State transBoolAnd(Token&, const std::vector<Token>&);
    State transBoolNot(Token&, const std::vector<Token>&);
    State transBoolCmp(Token&, const std::vector<Token>&);

    State transDo_jump(Token&, const std::vector<Token>&);
    State transIf_then(Token&, const std::vector<Token>&);
    State transIf_then_else(Token&, const std::vector<Token>&);
    State transWhile(Token&, const std::vector<Token>&);
    State transReturn(Token&, const std::vector<Token>&);

    //State transFactorNumorId(Token&, const std::vector<Token>&);
    State transFactor_Func(Token&, const std::vector<Token>&);			//factor -> id ( argus )
    //State transArgus_Null(Token&, const std::vector<Token>&);			//argus ->
    //State transArgus_ArgusList(Token&, const std::vector<Token>&);		//argus -> argu_list
    State transPreExpr_ExprPreExpr(Token&, const std::vector<Token>&);	//pre_expr ->, expr pre_expr
    State transArgulist_ExprPreExpr(Token&, const std::vector<Token>&);	//argu_list -> expr pre_expr
    //State transFactor_lbExprrb(Token&, const std::vector<Token>&);		//factor -> ( expr )
    //State transTerm_TermxFactor(Token&, const std::vector<Token>&);	//term -> term * factor
    //State transTerm_Factor(Token&, const std::vector<Token>&);			//term -> factor

    //new
    State transArr(Token&, const std::vector<Token>&);		//arr_item -> id [ expr ]���߶�ά
    State transParam(Token&, const std::vector<Token>&);		//arr_item -> id [ expr ]���߶�ά

public:
    //code�в���������
    static const int ARG_GLOBALVAR		= 0;
    static const int ARG_LOCALVAR		= 1;
    static const int ARG_INST			= 2;
    static const int ARG_CALLFUNC		= 3;
    static const int ARG_REG            = 4;    //��ͨ�Ĵ���
    static const int ARG_PREG           = 5;    //��Ų����ļĴ���
    static const int ARG_RReg           = 6;    //��ź�������ֵ�ļĴ���
    static const int ARG_RAReg          = 7;    //��ŷ��ص�ַ�ļĴ���
    static const int REG_NUM            = 8;

    /* new here */
    std::vector<int> entrances;
    std::vector<CodeBlock> codeblocks;
    //��ֹDAGͼ�еĻ�������ѭ���ݹ�
    std::vector<int> visitedBlocks;
    //��code_list�±�ӳ�䵽codeblocks�ж�Ӧ��������±�
    std::map<int, int> LISTtoCB;

    std::vector<int> jmps;
    std::map<int, int> jmpToNo;
    //�����ж��Ƿ��Ѿ������jmps
    std::map<int, int> jmpSingle;

    //�����±�
    std::vector<int> funcPoins;

    //���ڱ��溯�����õĲ���
    std::map<string, int> valueToReg;

    //������Ӧ��������
    std::vector<int> funcParamNum;

    //������Ӧ�ڴ���ʼ��ַ(ƫ����)
    std::vector<std::map<string, int>> varAddrs;
    //���пռ���ʼָ��
    std::vector<int> startP;

    /* new here */
    std::map<int, State(CodeGenerator::*)(Token&, const std::vector<Token>&)> translate_map;	//����ָ���,ÿ������ʽ����һ�����붯��.�޶����򲻸�ֵ

public:
    CodeGenerator();
    State writeCodeToFile(const char*);
    State writeInfoTable(const char* des_path);
    State writeTarCodeToFile(const char* des_path);
    //for mips
    State writeTarCodeToFile2(const char* des_path);

    /* new here */
    State writeCode(ostream& des, int l, int r);
    //���ֻ�����
    State generateBBlock();
    State preOperate();
    //Ϊĳһ���������ɴ��û�Ծ��Ϣ��
    State addFirstInfo(CodeBlock &codeBlock, int arg, int kind, bool active);
    State addInfo(CodeBlock &codeBlock, int arg, int kind);
    State generateFirstInfoList(CodeBlock &codeBlock);
    State generateInfoList(CodeBlock &codeBlock);
    bool codeBLoop(CodeBlock &codeBlock);
    State getSonActiveVar(CodeBlock &codeBlock);
    State addLink(InfoTableRow &nowRow, CodeBlock &codeBlock, int paramPos, int arg, bool isGlobal, int useloc);    //��ӱ�����ʼ��Ϣ��ͷ
    bool isInMyVars(CodeBlock &codeBlock, int arg, int kind);
    State addActiveVars(CodeBlock &codeBlock);      //���ӻ������еĻ�Ծ�������������Ծ����
    State completeInfoTable(CodeBlock &codeBlock);  //���ɴ��û�Ծ��Ϣ��������������Ϣ��
    //Ϊȫ�����������ɴ��û�Ծ��Ϣ��
    State generateInfoTable(int start, int end);
    State generateAllInfoTable();

    //�Ĵ����ദ����
    State initialReg(CodeBlock &codeBlock);
    int getReg(CodeBlock &codeBlock, int result, int arg1, int arg2, int result_p, int arg1_p, int arg2_p, int tableRow);

    int getRegNo(CodeBlock &codeBlock, int arg, int arg_p);
    State updateLinkP(CodeBlock &codeBlock, int result, int arg1, int arg2, int result_p, int arg1_p, int arg2_p);
    State updateRegA(CodeBlock &codeBlock, int reg, int arg, int arg_p);
    State updateReg(CodeBlock &codeBlock, int reg, int arg, int arg_p);
    State genStore(CodeBlock &codeBlock, int result, int arg1, int arg2, int result_p, int arg1_p, int arg2_p);
    State genTarCodeBlock(CodeBlock &codeBlock);
    State genTarCode();
    //for mips
    State getVarForJ(int &reg_no, int arg, int arg_p, CodeBlock &codeBlock, Code &now, int i);
    State getVarForBnez(int &reg_no, int arg, int arg_p, CodeBlock &codeBlock, Code &now, int i);
    State genTarCodeBlock2(CodeBlock &codeBlock);
    State genTarCode2();
    /* new here */

    const Token& getErrorToken();		//���س�����Ϣ
    State clear_code();
};

#endif // !CODEGENERATOR_H
