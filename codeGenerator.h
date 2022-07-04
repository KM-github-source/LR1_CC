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
    int arg1_p;		//是否为全局变量
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
    //待用位置
    int useLoc;
    //活跃信息，true表示活跃
    bool isActive;
};

struct InfoTableRow
{
    //中间四元式代码
    int code;
    //左值、左操作数、右操作数
    std::vector<InfoPair> params;
};

struct CodeBlock
{
    int start;
    int end;
    //符号表下标
    int tablePoin;
    //后缀基本块起始下标
    std::vector<int> suffix;
    //变量，0代表全局变量，1代表局部变量，遇到新情况时可以继续扩展
    std::vector<std::vector<int>> vars;
    std::vector<std::vector<int>> linkedP;
    //入口活跃变量
    std::vector<std::vector<int>> activeVars;
    //待用活跃信息链表
    //For全局变量
    std::vector<std::vector<InfoPair>> linkedInfoG;
    std::map<int, int> mapForG;
    //For局部变量
    std::vector<std::vector<InfoPair>> linkedInfoL;
    std::map<int, int> mapForL;
    //待用活跃信息表
    std::vector<InfoTableRow> infoTable;
    //寄存器类
    //变量存在哪些寄存器
    std::vector<std::vector<int>> AVALUE;
    //寄存器中包含哪些变量
    std::vector<std::vector<int>> RVALUE;
};

/* new here */

class CodeGenerator
{
private:
    Token err_token;		//语义分析错误信息
    std::vector<Code> code_list;
    std::vector<TarCode> tarCode_list;

private:
    //一系列辅助方法
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
    State transAssignBina(Token&, const std::vector<Token>&);	//双目运算
    State transAssignCmp(Token&, const std::vector<Token>&);	//比较运算符

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
    State transArr(Token&, const std::vector<Token>&);		//arr_item -> id [ expr ]或者二维
    State transParam(Token&, const std::vector<Token>&);		//arr_item -> id [ expr ]或者二维

public:
    //code中参数的类型
    static const int ARG_GLOBALVAR		= 0;
    static const int ARG_LOCALVAR		= 1;
    static const int ARG_INST			= 2;
    static const int ARG_CALLFUNC		= 3;
    static const int ARG_REG            = 4;    //普通寄存器
    static const int ARG_PREG           = 5;    //存放参数的寄存器
    static const int ARG_RReg           = 6;    //存放函数返回值的寄存器
    static const int ARG_RAReg          = 7;    //存放返回地址的寄存器
    static const int REG_NUM            = 8;

    /* new here */
    std::vector<int> entrances;
    std::vector<CodeBlock> codeblocks;
    //防止DAG图中的环导致死循环递归
    std::vector<int> visitedBlocks;
    //从code_list下标映射到codeblocks中对应基本块的下标
    std::map<int, int> LISTtoCB;

    std::vector<int> jmps;
    std::map<int, int> jmpToNo;
    //用于判断是否已经加入过jmps
    std::map<int, int> jmpSingle;

    //函数下标
    std::vector<int> funcPoins;

    //用于保存函数调用的参数
    std::map<string, int> valueToReg;

    //函数对应参数数量
    std::vector<int> funcParamNum;

    //变量对应内存起始地址(偏移量)
    std::vector<std::map<string, int>> varAddrs;
    //空闲空间起始指针
    std::vector<int> startP;

    /* new here */
    std::map<int, State(CodeGenerator::*)(Token&, const std::vector<Token>&)> translate_map;	//函数指针表,每个产生式分配一个翻译动作.无动作则不赋值

public:
    CodeGenerator();
    State writeCodeToFile(const char*);
    State writeInfoTable(const char* des_path);
    State writeTarCodeToFile(const char* des_path);
    //for mips
    State writeTarCodeToFile2(const char* des_path);

    /* new here */
    State writeCode(ostream& des, int l, int r);
    //划分基本块
    State generateBBlock();
    State preOperate();
    //为某一基本块生成待用活跃信息链
    State addFirstInfo(CodeBlock &codeBlock, int arg, int kind, bool active);
    State addInfo(CodeBlock &codeBlock, int arg, int kind);
    State generateFirstInfoList(CodeBlock &codeBlock);
    State generateInfoList(CodeBlock &codeBlock);
    bool codeBLoop(CodeBlock &codeBlock);
    State getSonActiveVar(CodeBlock &codeBlock);
    State addLink(InfoTableRow &nowRow, CodeBlock &codeBlock, int paramPos, int arg, bool isGlobal, int useloc);    //添加变量初始信息链头
    bool isInMyVars(CodeBlock &codeBlock, int arg, int kind);
    State addActiveVars(CodeBlock &codeBlock);      //从子基本块中的活跃变量补充自身活跃变量
    State completeInfoTable(CodeBlock &codeBlock);  //生成待用活跃信息链并用其完整信息表
    //为全部基本块生成待用活跃信息表
    State generateInfoTable(int start, int end);
    State generateAllInfoTable();

    //寄存器类处理函数
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

    const Token& getErrorToken();		//返回出错信息
    State clear_code();
};

#endif // !CODEGENERATOR_H
