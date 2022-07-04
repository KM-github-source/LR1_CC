#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <iostream>
#include <algorithm>
#include <iomanip>

#include "symbolTable.h"
#include "codeGenerator.h"
#include "lexer.h"

using namespace std;


/****************************************************************************************************************
* @Author : LeeQueue & Gaozc
* zcgg is 大撒币!	\doge
* lqgg is 小孬蛙!   \handsome
*
****************************************************************************************************************/

CodeGenerator::CodeGenerator()
{
    //产生式对应的序号
    //尽量减少产生式的改动
    const int i_program = 1;
    const int i_getpos = 18;
    const int i_dec_int_var = 4;
    const int i_dec_param_var = 13;
    const int i_in_var_dec = 16;
    const int i_dec_int_func = 5;
    const int i_dec_void_func = 6;
    const int i_mktable = 7;
    const int i_statstr2stat = 17;
    const int i_stat2ifstat = 20;
    const int i_stat2while = 21;
    const int i_stat2return = 22;
    const int i_stat2assign = 23;
    const int i_statstr2statstr = 19;
    const int i_assign = 25;
    const int i_cmp_l = 41;
    const int i_cmp_le = 42;
    const int i_cmp_g = 43;
    const int i_cmp_ge = 44;
    const int i_cmp_eq = 45;
    const int i_cmp_ne = 46;
    const int i_return = 26;
    const int i_return_expr = 27;
    const int i_expr2term = 47;
    const int i_term2factor = 50;
    const int i_factor2num = 53;
    const int i_factor2id = 55;
    const int i_factor2expr = 54;
    const int i_argus2argu_list = 58;
    const int i_expr_add = 48;
    const int i_expr_sub = 49;
    const int i_expr_times = 51;
    const int i_expr_divide = 52;
    const int i_bool2and = 32;
    const int i_and2sbool = 34;
    const int i_sbool2bool = 37;
    const int i_sbool2comp = 39;
    const int i_bool_and = 35;
    const int i_bool_or = 33;
    const int i_bool_not = 38;
    const int i_bool_comp = 40;
    const int i_sbool2expr = 36;
    const int i_if_then = 29;
    const int i_if_then_else = 30;
    const int i_do_jump = 31;
    const int i_while = 28;
    const int i_stat2call = 24;
    const int i_factor2call = 56;
    const int i_pre_expr = 61;
    const int i_argulist = 59;
    const int i_dec_1arr = 62;
    const int i_dec_2arr = 63;
    const int i_assign_arr = 64;
    const int i_1arr = 65;
    const int i_2arr = 66;
    const int i_in_var_dec_1arr = 67;
    const int i_in_var_dec_2arr = 68;
    const int i_factor2arritem = 69;
    const int i_param2paramlist = 8;
    const int i_param2e = 9;
    const int i_paramlist2preparam = 10;
    const int i_preparam2e = 11;
    const int i_preparam2preparam = 12;
    const int i_argus2e = 57;
    const int i_preexpr2e = 60;

    translate_map[i_program] = &CodeGenerator::transDeclareProgram;
    translate_map[i_getpos] = &CodeGenerator::transGetpos;
    translate_map[i_dec_int_var] = &CodeGenerator::transDeclareVar;
    translate_map[i_dec_param_var] = &CodeGenerator::transDeclareVar;
    translate_map[i_in_var_dec] = &CodeGenerator::transDeclareVar;
    translate_map[i_mktable] = &CodeGenerator::transMktable;
    translate_map[i_dec_int_func] = &CodeGenerator::transDeclareFunc;
    translate_map[i_dec_void_func] = &CodeGenerator::transDeclareFunc;
    translate_map[i_statstr2stat] = &CodeGenerator::transStatKeep;
    translate_map[i_stat2ifstat] = &CodeGenerator::transStatKeep;
    translate_map[i_stat2while] = &CodeGenerator::transStatKeep;
    translate_map[i_stat2return] = &CodeGenerator::transStatKeep;
    translate_map[i_stat2assign] = &CodeGenerator::transStatKeep;
    translate_map[i_statstr2statstr] = &CodeGenerator::transStatStr2StatStr;
    translate_map[i_assign] = &CodeGenerator::transAssign;
    translate_map[i_cmp_l] = &CodeGenerator::transAssignCmp;
    translate_map[i_cmp_le] = &CodeGenerator::transAssignCmp;
    translate_map[i_cmp_g] = &CodeGenerator::transAssignCmp;
    translate_map[i_cmp_ge] = &CodeGenerator::transAssignCmp;
    translate_map[i_cmp_eq] = &CodeGenerator::transAssignCmp;
    translate_map[i_cmp_ne] = &CodeGenerator::transAssignCmp;
    translate_map[i_return] = &CodeGenerator::transReturn;
    translate_map[i_return_expr] = &CodeGenerator::transReturn;
    translate_map[i_expr2term] = &CodeGenerator::transAssignKeep;
    translate_map[i_term2factor] = &CodeGenerator::transAssignKeep;
    translate_map[i_factor2num] = &CodeGenerator::transAssignKeep;
    translate_map[i_factor2id] = &CodeGenerator::transAssignKeep;
    translate_map[i_factor2expr] = &CodeGenerator::transAssignKeep;
    translate_map[i_argus2argu_list] = &CodeGenerator::transAssignKeep;
    translate_map[i_expr_add] = &CodeGenerator::transAssignBina;
    translate_map[i_expr_sub] = &CodeGenerator::transAssignBina;
    translate_map[i_expr_times] = &CodeGenerator::transAssignBina;
    translate_map[i_expr_divide] = &CodeGenerator::transAssignBina;
    translate_map[i_bool2and] = &CodeGenerator::transBoolKeep;
    translate_map[i_and2sbool] = &CodeGenerator::transBoolKeep;
    translate_map[i_sbool2bool] = &CodeGenerator::transBoolKeep;
    translate_map[i_sbool2comp] = &CodeGenerator::transBoolKeep;
    translate_map[i_bool_and] = &CodeGenerator::transBoolAnd;
    translate_map[i_bool_or] = &CodeGenerator::transBoolOr;
    translate_map[i_bool_not] = &CodeGenerator::transBoolNot;
    translate_map[i_bool_comp] = &CodeGenerator::transBoolCmp;
    translate_map[i_sbool2expr] = &CodeGenerator::transBoolCmp;
    translate_map[i_if_then] = &CodeGenerator::transIf_then;
    translate_map[i_if_then_else] = &CodeGenerator::transIf_then_else;
    translate_map[i_do_jump] = &CodeGenerator::transDo_jump;
    translate_map[i_while] = &CodeGenerator::transWhile;
    translate_map[i_stat2call] = &CodeGenerator::transFactor_Func;
    translate_map[i_factor2call] = &CodeGenerator::transFactor_Func;
    translate_map[i_pre_expr] = &CodeGenerator::transPreExpr_ExprPreExpr;
    translate_map[i_argulist] = &CodeGenerator::transArgulist_ExprPreExpr;
    translate_map[i_dec_1arr] = &CodeGenerator::transDeclareVar;
    translate_map[i_dec_2arr] = &CodeGenerator::transDeclareVar;
    translate_map[i_assign_arr] = &CodeGenerator::transAssign;
    translate_map[i_1arr] = &CodeGenerator::transArr;
    translate_map[i_2arr] = &CodeGenerator::transArr;
    translate_map[i_in_var_dec_1arr] = &CodeGenerator::transDeclareVar;
    translate_map[i_in_var_dec_2arr] = &CodeGenerator::transDeclareVar;
    translate_map[i_factor2arritem] = &CodeGenerator::transAssignKeep;
    translate_map[i_param2paramlist] = &CodeGenerator::transParam;
    translate_map[i_param2e] = &CodeGenerator::transParam;
    translate_map[i_paramlist2preparam] = &CodeGenerator::transParam;
    translate_map[i_preparam2e] = &CodeGenerator::transParam;
    translate_map[i_preparam2preparam] = &CodeGenerator::transParam;
    translate_map[i_argus2e] = &CodeGenerator::transParam;
    translate_map[i_preexpr2e] = &CodeGenerator::transParam;
}

State CodeGenerator::writeCodeToFile(const char* des_path)
{
    ofstream des(des_path);
    if (!des.is_open())
        return State::ERROR;

    //打印符号表
    symbol_table.displayTable(des);

    for (int i = 0; i < code_list.size(); i++) {
        des << i << "\t( ";
        des << code_list[i].op << " ,\t";

        if (code_list[i].arg1 == DEFAULT_LOC)
            des << '_';
        else {
            if (code_list[i].arg1_p == CodeGenerator::ARG_LOCALVAR)
                des << 'T';
            else if (code_list[i].arg1_p == CodeGenerator::ARG_GLOBALVAR)
                des << 'G';
            else if (code_list[i].arg1_p == CodeGenerator::ARG_CALLFUNC)
                des << 'F';
            des << code_list[i].arg1;
        }
        des << " ,\t";

        if (code_list[i].arg2 == DEFAULT_LOC)
            des << '_';
        else {
            if (code_list[i].arg2_p == CodeGenerator::ARG_LOCALVAR)
                des << 'T';
            else if (code_list[i].arg2_p == CodeGenerator::ARG_GLOBALVAR)
                des << 'G';
            des << code_list[i].arg2;
        }
        des << " ,\t";

        if (code_list[i].result == DEFAULT_LOC)
            des << '_';
        else {
            if (code_list[i].result_p == CodeGenerator::ARG_LOCALVAR)
                des << 'T';
            else if (code_list[i].result_p == CodeGenerator::ARG_GLOBALVAR)
                des << 'G';
            des << code_list[i].result;
        }
        des << " )\n";
    }
    return State::OK;
}

State CodeGenerator::writeCode(ostream& des, int l, int r)
{
    for (int i = l; i <= r; i++)
    {
        des << i << "\t( ";
        des << code_list[i].op << " ,\t";

        if (code_list[i].arg1 == DEFAULT_LOC)
            des << '_';
        else {
            if (code_list[i].arg1_p == CodeGenerator::ARG_LOCALVAR)
                des << 'T';
            else if (code_list[i].arg1_p == CodeGenerator::ARG_GLOBALVAR)
                des << 'G';
            des << code_list[i].arg1;
        }
        des << " ,\t";

        if (code_list[i].arg2 == DEFAULT_LOC)
            des << '_';
        else {
            if (code_list[i].arg2_p == CodeGenerator::ARG_LOCALVAR)
                des << 'T';
            else if (code_list[i].arg2_p == CodeGenerator::ARG_GLOBALVAR)
                des << 'G';
            des << code_list[i].arg2;
        }
        des << " ,\t";

        if (code_list[i].result == DEFAULT_LOC)
            des << '_';
        else {
            if (code_list[i].result_p == CodeGenerator::ARG_LOCALVAR)
                des << 'T';
            else if (code_list[i].result_p == CodeGenerator::ARG_GLOBALVAR)
                des << 'G';
            des << code_list[i].result;
        }
        if(l == r)
            des << " )";
        else
            des << " )\n";
    }
    return State::OK;
}

void CodeGenerator::gen(string op, int arg1, int arg2, int result, int arg1_p, int arg2_p, int result_p, string sarg1, string sarg2, string sresult, int lasti)
{
    code_list.push_back({ op, arg1, arg2, result, arg1_p, arg2_p, result_p, sarg1, sarg2, sresult, lasti });
}

void CodeGenerator::genTar(std::string op, int arg1, int arg2, int arg1_p, int arg2_p, int arg3, int arg3_p)
{
    if(op == "+")
        op = "add";
    else if(op == "-")
        op = "sub";
    else if(op == "*")
        op = "mul";
    else if(op == "/")
        op = "div";
    else if(op == "j>")
        op = "bgt";
    else if(op == "j>=")
        op = "bge";
    else if(op == "j<")
        op = "blt";
    else if(op == "j<=")
        op = "ble";
    else if(op == "j==")
        op = "beq";
    tarCode_list.push_back({ op, arg1, arg2, arg3, arg1_p, arg2_p, arg3_p });
}

int CodeGenerator::merge(int list_1, int list_2)
{
    if (list_2 != DEFAULT_LOC)
    {
        int p = list_2;
        while (code_list[p].result != DEFAULT_LOC)
            p = code_list[p].result;
        code_list[p].result = list_1;
        return list_2;
    }
    else
        return list_1;
}

void CodeGenerator::backpatch(int back_list, int quad)
{
    if (back_list == DEFAULT_LOC)
        return;
    int p = back_list;
    while (code_list[p].result != DEFAULT_LOC)
    {
        int p_tmp = code_list[p].result;
        code_list[p].result = quad;
        p = p_tmp;
    }
    code_list[p].result = quad;
}

State CodeGenerator::transGetpos(Token& left, const vector<Token>& right)
{
    //getpos ->
    left.attr.ctrl_attr.quad = code_list.size();
    return State::OK;
}
State CodeGenerator::transDeclareVar(Token& left, const vector<Token>& right)
{
    //dec -> int id ;
    //dec -> int id [ num ] ;
    //dec -> int id [ num ] [ num ] ;
    //in_var_dec -> int id
    //in_var_dec -> int id [ num ]
    //in_var_dec -> int id [ num ] [ num ]
    //param -> int id
    const string& id = right[1].value;
    const int rsize = right.size();
    if (left.tag == Tag::dec) {
        if (symbol_table.table_map_list[0].count(id)) {
            err_token = right[1];
            return State::ERROR;		//多重定义
        }
        if(6 == rsize)
        {
            symbol_table.addGlobalVar(right[1].value, ArgType::t_int_arr, false, "arr", "int arr-" + right[3].value);
            this->varAddrs[0][right[1].value] = this->startP[0];
            this->startP[0] += 4*atoi((right[3].value).c_str());
        }
        else if(9 == rsize)
        {
            symbol_table.addGlobalVar(right[1].value, ArgType::t_int_arr, false, "arr", "int arr-" + right[3].value + "-" + right[6].value);
            this->varAddrs[0][right[1].value] = this->startP[0];
            this->startP[0] += 4*atoi((right[3].value).c_str())*atoi((right[6].value).c_str());
        }
        else
        {
            symbol_table.addGlobalVar(right[1].value, ArgType::t_int_var, false, "var", "int var");
            this->varAddrs[0][right[1].value] = this->startP[0];
            this->startP[0] += 4;
        }
    }
    else {
        if (symbol_table.table_map_list.back().count(id)) {
            err_token = right[1];
            return State::ERROR;		//多重定义
        }
        if(5 == rsize)
        {
            symbol_table.addVar(right[1].value, ArgType::t_int_arr, false, "arr", "int arr-" + right[3].value);
            this->varAddrs.back()[right[1].value] = this->startP.back();
            this->startP.back() += 4*atoi((right[3].value).c_str());
        }
        else if(8 == rsize)
        {
            symbol_table.addVar(right[1].value, ArgType::t_int_arr, false, "arr", "int arr-" + right[3].value + "-" + right[6].value);
            this->varAddrs.back()[right[1].value] = this->startP.back();
            this->startP.back() += 4*atoi((right[3].value).c_str())*atoi((right[6].value).c_str());
        }
        else
        {
            symbol_table.addVar(right[1].value, ArgType::t_int_var, false, "var", "int var");
            this->varAddrs.back()[right[1].value] = this->startP.back();
            this->startP.back() += 4;
        }
    }

    if(left.tag == Tag::param)
    {
        this->funcParamNum[this->funcParamNum.size()-1]++;
        left.attr.fun_attr.param_num = 1;
    }
    return State::OK;
}
State CodeGenerator::transMktable(Token& left, const vector<Token>& right)
{
    //mktable ->
    symbol_table.mkTable(code_list.size());
    this->varAddrs.push_back(map<string, int>());
    this->startP.push_back(0);
    code_list.push_back({});	//为函数开头预留一个位置
    this->funcParamNum.push_back(0);
    return State::OK;
}

State CodeGenerator::transDeclareFunc(Token& left, const vector<Token>& right)
{
    //dec -> int id ( mktable params ) { in_dec stat_str }
    //dec -> void id ( mktable params ) { in_dec stat_str }
    if (symbol_table.funcname2index.count(right[1].value)) {
        err_token = right[1];
        return State::ERROR;	//不允许重载
    }
    symbol_table.funcname2index[right[1].value] = symbol_table.table_list.size() - 1;
    symbol_table.addGlobalVar(right[1].value, ArgType::t_int_func, false, TAG2STR.at(right[0].tag) + " fun-" + to_string(right[4].attr.fun_attr.param_num), "F" + to_string(symbol_table.table_list.size() - 1));
    auto& i = symbol_table.table_list.back()[0];
    i.value = right[1].value;
    if (STR2TAG.at(right[0].value) == Tag::kw_int)
        i.type = ArgType::t_int_func;
    else if (STR2TAG.at(right[0].value) == Tag::kw_void)
        i.type = ArgType::t_void_func;

    //回填函数名
    auto& c = code_list[symbol_table.table_entrys.back()];
    c.op = "F" + to_string(symbol_table.table_list.size() - 1) + ":";
    c.arg1 = DEFAULT_LOC;
    c.arg2 = DEFAULT_LOC;
    c.result = DEFAULT_LOC;

    if (code_list.back().op != "return")
        gen("return", DEFAULT_LOC, DEFAULT_LOC, DEFAULT_LOC);

    return State::OK;
}
State CodeGenerator::transDeclareProgram(Token& left, const vector<Token>& right)
{
    //program -> mktable dec_list
    auto& code = code_list.front();
    code.arg1 = code.arg2 = code.result = DEFAULT_LOC;
    code.op = "Program start";
    Code end_code = { "Program end",DEFAULT_LOC ,DEFAULT_LOC ,DEFAULT_LOC };
    code_list.push_back(end_code);
    return State::OK;
}
State CodeGenerator::transStatKeep(Token& left, const vector<Token>& right)
{
    /*stat_str -> stat
    * stat -> if_stat
    * stat -> while_stat
    * stat -> return_stat
    * stat -> assign_stat
    */
    left.attr.ctrl_attr.next_list = right[0].attr.ctrl_attr.next_list;
    return State::OK;
}
State CodeGenerator::transStatStr2StatStr(Token& left, const vector<Token>& right)
{
    //stat_str -> stat getpos stat_str
    backpatch(right[0].attr.ctrl_attr.next_list, right[1].attr.ctrl_attr.quad);
    left.attr.ctrl_attr.next_list = right[2].attr.ctrl_attr.next_list;
    return State::OK;
}
State CodeGenerator::transAssign(Token& left, const vector<Token>& right)
{
    //assign_stat -> id = expr ;
    //assign_stat -> arr_item = expr ;
    int result_p;
    int place;
    string arg1_str, result_str;

    if(right[0].tag == Tag::id)
    {
        if (symbol_table.table_map_list.back().count(right[0].value) == 0)
        {
            if (symbol_table.table_map_list[0].count(right[0].value) == 0)
            {
                err_token = right[0];
                return State::ERROR;
            }
            result_p = CodeGenerator::ARG_GLOBALVAR;		//表示全局
            place = symbol_table.table_map_list.front()[right[0].value];
            result_str = symbol_table.table_list.front().at(symbol_table.table_map_list.front().at(right[0].value)).newname;
        }
        else
        {
            result_p = CodeGenerator::ARG_LOCALVAR;		//表示局部
            place = symbol_table.table_map_list.back()[right[0].value];
            result_str = symbol_table.table_list.back().at(symbol_table.table_map_list.back().at(right[0].value)).newname;
        }
    }
    else
    {
        place = right[0].attr.var_attr.item_i;
        if(place == 0)
            result_p = CodeGenerator::ARG_GLOBALVAR;		//表示全局
        else
            result_p = CodeGenerator::ARG_LOCALVAR;		//表示局部
        result_str = symbol_table.table_list[right[0].attr.var_attr.table_i][right[0].attr.var_attr.item_i].newname;
    }
    arg1_str = symbol_table.table_list[right[2].attr.var_attr.table_i][right[2].attr.var_attr.item_i].newname;

    gen("=", right[2].attr.var_attr.place, DEFAULT_LOC, place, CodeGenerator::ARG_LOCALVAR, CodeGenerator::ARG_LOCALVAR, result_p, arg1_str, "", result_str);
    left.attr.ctrl_attr.next_list = DEFAULT_LOC;
    return State::OK;
}

State CodeGenerator::transAssignKeep(Token& left, const vector<Token>& right)
{
    /*expr -> term
    * term -> factor
    * factor -> num
    * factor -> id
    * argus -> argu_list
    * factor -> ( expr )
    * factor -> arr_item
    */
    if (right.size() > 1)	//factor -> ( expr )
        left.attr.var_attr = right[1].attr.var_attr;
    else {
        if (right[0].tag == Tag::id)
        {
            const string& value = right[0].value;
            int place;
            if (symbol_table.table_map_list.back().count(value) == 0)
            {	//局部没有
                if (symbol_table.table_map_list.front().count(value) == 0)
                {	//全局没有
                    err_token = right[0];
                    return State::ERROR;
                }
                left.attr.var_attr.table_i = 0;
                auto& item = symbol_table.table_list.front()[symbol_table.table_map_list.front()[value]];
//                item.value = "G" + to_string(symbol_table.table_map_list.front()[value]);
                place = symbol_table.table_map_list.front()[value];
                left.attr.var_attr.item_i = place;
//                place = symbol_table.addVar(item.value, item.type, item.is_inst);
                left.attr.var_attr.type = item.type;
                left.value = item.value;
            }
            else {
                place = symbol_table.table_map_list.back()[value];
                left.attr.var_attr.type = symbol_table.table_list.back()[place].type;
                left.value = value;
                left.attr.var_attr.table_i = symbol_table.table_list.size() - 1;
                left.attr.var_attr.item_i = place;
            }
            left.attr.var_attr.place = place;
        }
        else
        {
            left.attr.var_attr = right[0].attr.var_attr;
            left.value = right[0].value;
        }
    }
    return State::OK;
}
State CodeGenerator::transAssignBina(Token& left, const vector<Token>& right)
{
    //expr -> expr + term
    //expr -> expr - term
    //term -> term * factor
    //term -> term / factor
    /*for (const auto& i : right)
        left.value += i.value;*/
    int arg1_p = CodeGenerator::ARG_LOCALVAR;
    int arg2_p = CodeGenerator::ARG_LOCALVAR;
    if (symbol_table.table_map_list.back().count(right[0].value) == 0 && symbol_table.table_map_list.front().count(right[0].value) != 0)
        arg1_p = CodeGenerator::ARG_GLOBALVAR;

    if (symbol_table.table_map_list.back().count(right[2].value) == 0 && symbol_table.table_map_list.front().count(right[2].value) != 0)
        arg2_p = CodeGenerator::ARG_GLOBALVAR;

//    if (symbol_table.table_map_list.back().count(left.value) == 0)
//    {	//局部没有
//        if (symbol_table.table_map_list.front().count(left.value) == 0) {	//全局没有
//            err_token = left;
//            return State::ERROR;
//        }
//        result_p = CodeGenerator::ARG_GLOBALVAR;
//        auto& item = symbol_table.table_list.front()[symbol_table.table_map_list.front()[left.value]];
//        left.attr.var_attr.place = symbol_table.table_map_list.front()[left.value];
//        left.attr.var_attr.type = item.type;
//    }
//    else
//    {
//        result_p = CodeGenerator::ARG_LOCALVAR;
//        left.attr.var_attr.place = symbol_table.table_map_list.back()[left.value];
//        left.attr.var_attr.type = symbol_table.table_list.back()[left.attr.var_attr.place].type;
//    }
    left.attr.var_attr.table_i = symbol_table.table_list.size() - 1;
    left.attr.var_attr.place = symbol_table.addVar("", right[0].attr.var_attr.type, false);
    left.attr.var_attr.type = right[0].attr.var_attr.type;
    left.attr.var_attr.item_i = left.attr.var_attr.place;

    const string& sarg1 = symbol_table.table_list.at(right[0].attr.var_attr.table_i).at(right[0].attr.var_attr.item_i).newname;
    const string& sarg2 = symbol_table.table_list.at(right[2].attr.var_attr.table_i).at(right[2].attr.var_attr.item_i).newname;
    const string& sresult = symbol_table.table_list.at(left.attr.var_attr.table_i).at(left.attr.var_attr.item_i).newname;
//    gen(TAG2STR.at(right[1].tag), right[0].attr.var_attr.place, right[2].attr.var_attr.place, left.attr.var_attr.place);
    gen(TAG2STR.at(right[1].tag), right[0].attr.var_attr.place, right[2].attr.var_attr.place, left.attr.var_attr.place, arg1_p, arg2_p, CodeGenerator::ARG_LOCALVAR, sarg1, sarg2, sresult);
    return State::OK;
}
State CodeGenerator::transAssignCmp(Token& left, const vector<Token>& right)	//比较运算符
{
    /*comp_operator -> <
    * comp_operator -> <=
    * comp_operator -> >
    * comp_operator -> >=
    * comp_operator -> ==
    * comp_operator -> !=
    */
    left.tag = right.front().tag;
    return State::OK;
}
State CodeGenerator::transBoolKeep(Token& left, const vector<Token>& right)
{
    /*bool_expr -> and_expr
    * and_expr -> sbool_expr
    * sbool_expr -> ( bool_expr )
    * sbool_expr -> comp_expr
    */
    if (right[0].tag == Tag::sb_llb) {
        //sbool_expr -> ( bool_expr )
        left.attr.bool_attr = right[1].attr.bool_attr;
        left.attr.bool_attr.true_list = right[1].attr.bool_attr.true_list;
        left.attr.bool_attr.false_list = right[1].attr.bool_attr.false_list;
    }
    else {
        //剩下的三个
        left.attr.bool_attr = right[0].attr.bool_attr;
        left.attr.bool_attr.true_list = right[0].attr.bool_attr.true_list;
        left.attr.bool_attr.false_list = right[0].attr.bool_attr.false_list;
    }
    return State::OK;
}
State CodeGenerator::transBoolOr(Token& left, const vector<Token>& right)
{
    //bool_expr -> bool_expr || getpos and_expr
    backpatch(right[0].attr.bool_attr.false_list, right[2].attr.ctrl_attr.quad);
    left.attr.bool_attr.true_list = merge(right[0].attr.bool_attr.true_list, right[3].attr.bool_attr.true_list);
    left.attr.bool_attr.false_list = right[3].attr.bool_attr.false_list;
    return State::OK;
}
State CodeGenerator::transBoolAnd(Token& left, const vector<Token>& right)
{
    //and_expr -> and_expr && getpos sbool_expr
    backpatch(right[0].attr.bool_attr.true_list, right[2].attr.ctrl_attr.quad);
    left.attr.bool_attr.true_list = right[3].attr.bool_attr.true_list;
    left.attr.bool_attr.false_list = merge(right[0].attr.bool_attr.false_list, right[3].attr.bool_attr.false_list);
    return State::OK;
}
State CodeGenerator::transBoolNot(Token& left, const vector<Token>& right)
{
    //sbool_expr -> ! sbool_expr
    left.attr.bool_attr.true_list = right[1].attr.bool_attr.false_list;
    left.attr.bool_attr.false_list = right[1].attr.bool_attr.true_list;
    return State::OK;
}
State CodeGenerator::transBoolCmp(Token& left, const vector<Token>& right)
{
    /*comp_expr -> expr comp_operator expr
    * sbool_expr -> expr
    */
    int arg1_p = CodeGenerator::ARG_LOCALVAR;
    int arg2_p = CodeGenerator::ARG_LOCALVAR;
    if (symbol_table.table_map_list.back().count(right[0].value) == 0 && symbol_table.table_map_list.front().count(right[0].value) != 0)
        arg1_p = CodeGenerator::ARG_GLOBALVAR;

    if (right.size() > 1 && symbol_table.table_map_list.back().count(right[2].value) == 0 && symbol_table.table_map_list.front().count(right[2].value) != 0)
        arg2_p = CodeGenerator::ARG_GLOBALVAR;
    left.attr.bool_attr.true_list = code_list.size();
    left.attr.bool_attr.false_list = left.attr.bool_attr.true_list + 1;
    if (right.size() == 1) {
        //sbool_expr -> expr
        //判断:非0为真,0为假
//        gen("jnz", right[0].attr.var_attr.place, DEFAULT_LOC, DEFAULT_LOC, CodeGenerator::ARG_LOCALVAR, CodeGenerator::ARG_LOCALVAR, CodeGenerator::ARG_INST);
        const auto& sarg1 = symbol_table.table_list.at(right[0].attr.var_attr.table_i).at(right[0].attr.var_attr.item_i).newname;
        gen("jnz", right[0].attr.var_attr.place, DEFAULT_LOC, DEFAULT_LOC, arg1_p, CodeGenerator::ARG_LOCALVAR, CodeGenerator::ARG_INST, sarg1);
        gen("j", DEFAULT_LOC, DEFAULT_LOC, DEFAULT_LOC, CodeGenerator::ARG_LOCALVAR, CodeGenerator::ARG_LOCALVAR, CodeGenerator::ARG_INST);
    }
    else {
        //comp_expr -> expr comp_operator expr
        const auto& sarg1 = symbol_table.table_list.at(right[0].attr.var_attr.table_i).at(right[0].attr.var_attr.item_i).newname;
        const auto& sarg2 = symbol_table.table_list.at(right[2].attr.var_attr.table_i).at(right[2].attr.var_attr.item_i).newname;
        gen("j" + TAG2STR.at(right[1].tag), right[0].attr.var_attr.place, right[2].attr.var_attr.place, DEFAULT_LOC, arg1_p, arg2_p, CodeGenerator::ARG_INST, sarg1, sarg2);
        gen("j", DEFAULT_LOC, DEFAULT_LOC, DEFAULT_LOC, CodeGenerator::ARG_LOCALVAR, CodeGenerator::ARG_LOCALVAR, CodeGenerator::ARG_INST);
    }
    return State::OK;
}
State CodeGenerator::transIf_then(Token& left, const vector<Token>& right)
{
    //if_stat -> if ( bool_expr ) { getpos stat_str }
    backpatch(right[2].attr.bool_attr.true_list, right[5].attr.ctrl_attr.quad);
    left.attr.ctrl_attr.next_list = merge(right[2].attr.bool_attr.false_list, right[6].attr.ctrl_attr.next_list);
    return State::OK;
}

State CodeGenerator::transIf_then_else(Token& left, const vector<Token>& right)
{
    //if_stat -> if ( bool_expr ) { getpos stat_str } do_jump else { getpos stat_str }
    backpatch(right[2].attr.bool_attr.true_list, right[5].attr.ctrl_attr.quad);
    backpatch(right[2].attr.bool_attr.false_list, right[11].attr.ctrl_attr.quad);
    int tmp_list = merge(right[6].attr.ctrl_attr.next_list, right[8].attr.ctrl_attr.next_list);
    left.attr.ctrl_attr.next_list = merge(tmp_list, right[12].attr.ctrl_attr.next_list);
    return State::OK;
}

State CodeGenerator::transDo_jump(Token& left, const vector<Token>& right)
{
    //do_jump ->
    left.attr.ctrl_attr.next_list = code_list.size();
    gen("j", DEFAULT_LOC, DEFAULT_LOC, DEFAULT_LOC, CodeGenerator::ARG_LOCALVAR, CodeGenerator::ARG_LOCALVAR, CodeGenerator::ARG_INST);
    return State::OK;
}

State CodeGenerator::transWhile(Token& left, const vector<Token>& right)
{
    //while_stat -> while ( getpos bool_expr ) { getpos stat_str }
    backpatch(right[7].attr.ctrl_attr.next_list, right[2].attr.ctrl_attr.quad);
    backpatch(right[3].attr.bool_attr.true_list, right[6].attr.ctrl_attr.quad);
    left.attr.ctrl_attr.next_list = right[3].attr.bool_attr.false_list;
    gen("j", DEFAULT_LOC, DEFAULT_LOC, right[2].attr.ctrl_attr.quad, CodeGenerator::ARG_LOCALVAR, CodeGenerator::ARG_LOCALVAR, CodeGenerator::ARG_INST);
    return State::OK;
}

State CodeGenerator::transReturn(Token& left, const vector<Token>& right)
{
    //return_stat -> return ;
    //return_stat -> return expr ;
    if (right.size() == 2) {
        //return_stat -> return ;
        gen("return", DEFAULT_LOC, DEFAULT_LOC, DEFAULT_LOC);
    }
    else {
        //return_stat -> return expr ;
        gen("return", DEFAULT_LOC, DEFAULT_LOC, right[1].attr.var_attr.place, CodeGenerator::ARG_LOCALVAR, CodeGenerator::ARG_LOCALVAR, CodeGenerator::ARG_LOCALVAR, "", "", symbol_table.table_list.at(right[1].attr.var_attr.table_i).at(right[1].attr.var_attr.item_i).newname);
    }
    return State::OK;
}

//State CodeGenerator::transFactorNumorId(Token& left, const vector<Token>& right)
//{
//	//factor -> num
//	//factor -> id
//	left.attr.var_attr = right[0].attr.var_attr;
//	return State::OK;
//}

/***************************************************************
* 这里为factor创建一个临时变量，符号表中的string存放id ( argus )
***************************************************************/
State CodeGenerator::transFactor_Func(Token& left, const vector<Token>& right)
{
    //factor -> id ( argus )
    //stat -> id ( argus ) ;
    /*for (const auto& i : right)
        left.value += i.value;*/
    if (left.tag == Tag::factor) {
        left.attr.var_attr.place = symbol_table.addVar("", ArgType::t_int_var, false);
        left.attr.var_attr.table_i = symbol_table.table_list.size() - 1;
        left.attr.var_attr.item_i = left.attr.var_attr.place;
        left.attr.var_attr.type = ArgType::t_int_var;
        if (symbol_table.funcname2index.count(right[0].value) == 0) {
            err_token = right[0];
            return State::ERROR;
        }
        gen("call", symbol_table.funcname2index[right[0].value], DEFAULT_LOC, left.attr.var_attr.place, CodeGenerator::ARG_CALLFUNC, CodeGenerator::ARG_LOCALVAR, CodeGenerator::ARG_LOCALVAR, symbol_table.table_list.front().at(symbol_table.table_map_list.front().at(right[0].value)).newname, "", symbol_table.table_list.at(left.attr.var_attr.table_i).at(left.attr.var_attr.item_i).newname);
    }
    else {
        left.attr.ctrl_attr.next_list = DEFAULT_LOC;
        if (symbol_table.funcname2index.count(right[0].value) == 0) {
            err_token = right[0];
            return State::ERROR;
        }
        gen("call", symbol_table.funcname2index[right[0].value], DEFAULT_LOC, DEFAULT_LOC, CodeGenerator::ARG_CALLFUNC, CodeGenerator::ARG_LOCALVAR, CodeGenerator::ARG_LOCALVAR, symbol_table.table_list.front().at(symbol_table.table_map_list.front().at(right[0].value)).newname);
    }
    //("call",Function,-1,place)
    return State::OK;
}

////argus ->
////pre_expr ->
//State CodeGenerator::transArgus_Null(Token& left, const vector<Token>& right)
//{
//	left.value = "";
//	return State::OK;
//}

//State CodeGenerator::transArgus_ArgusList(Token& left, const vector<Token>& right)
//{
//	//argus -> argu_list
//	left.attr.var_attr = right[0].attr.var_attr;
//	return State::OK;
//}

State CodeGenerator::transPreExpr_ExprPreExpr(Token& left, const vector<Token>& right)
{
    //pre_expr -> , expr pre_expr
    //expr 的name
    gen("param", right[1].attr.var_attr.place, DEFAULT_LOC, DEFAULT_LOC, CodeGenerator::ARG_LOCALVAR, CodeGenerator::ARG_LOCALVAR, CodeGenerator::ARG_LOCALVAR, symbol_table.table_list.at(right[1].attr.var_attr.table_i).at(right[1].attr.var_attr.item_i).newname);
    left.attr.fun_attr.param_num = right[2].attr.fun_attr.param_num + 1;
    return State::OK;
}

State CodeGenerator::transArgulist_ExprPreExpr(Token& left, const vector<Token>& right)
{
    //argu_list -> expr pre_expr
    gen("param", right[0].attr.var_attr.place, DEFAULT_LOC, DEFAULT_LOC, CodeGenerator::ARG_LOCALVAR, CodeGenerator::ARG_LOCALVAR, CodeGenerator::ARG_LOCALVAR, symbol_table.table_list.at(right.at(0).attr.var_attr.table_i).at(right.at(0).attr.var_attr.item_i).newname);
    left.attr.fun_attr.param_num = right.at(1).attr.fun_attr.param_num + 1;
    return State::OK;
}

State CodeGenerator::transArr(Token& left, const vector<Token>& right)
{
    //arr_item -> id [ expr ]
    //arr_item -> id [ expr ] [ expr ]
    const TableItem* parr = nullptr;
    int table_i, item_i;
    if (0 == symbol_table.table_map_list.back().count(right[0].value)) {
        if (0 == symbol_table.table_map_list.front().count(right[0].value)) {
            err_token = right[0];
            err_token.info.why = "数组" + right[0].value + "未定义";
            return State::ERROR;
        }
        table_i = 0;
        item_i = symbol_table.table_map_list.front().at(right[0].value);
        parr = &symbol_table.table_list.front().at(item_i);
    }
    else {
        table_i = symbol_table.table_list.size() - 1;
        item_i = symbol_table.table_map_list.back().at(right[0].value);
        parr = &symbol_table.table_list.back().at(item_i);
    }

    if (4 >= right.size()) {
        //一维
        string newname = parr->value + "*" +
                symbol_table.table_list.at(right[2].attr.var_attr.table_i).at(right[2].attr.var_attr.item_i).value;
        if(symbol_table.table_map_list.back().count(newname) == 0)
        {
            left.attr.var_attr.item_i = symbol_table.addVar(newname, right[0].attr.var_attr.type, false, "arr", "int arr");
            int delta = atoi(symbol_table.table_list.at(right[2].attr.var_attr.table_i).at(right[2].attr.var_attr.item_i).value.c_str());
            this->varAddrs.back()[newname] = this->varAddrs.back()[right[0].value] + delta*4;
        }
        else
            left.attr.var_attr.item_i = symbol_table.table_map_list.back()[newname];
        left.attr.var_attr.place = left.attr.var_attr.item_i;
        left.attr.var_attr.type = right[0].attr.var_attr.type;
    }
    else {
        //二维
        string newname = parr->value + "*" +
                symbol_table.table_list.at(right[2].attr.var_attr.table_i).at(right[2].attr.var_attr.item_i).value + "*" +
                symbol_table.table_list.at(right[5].attr.var_attr.table_i).at(right[5].attr.var_attr.item_i).value;
        if(symbol_table.table_map_list.back().count(newname) == 0)
        {
            left.attr.var_attr.item_i = symbol_table.addVar(newname, right[0].attr.var_attr.type, false, "arr", "int arr");
            auto& arr = symbol_table.table_list.back()[symbol_table.table_map_list.back()[right[0].value]];
            int start = arr.newname.find("-", 0);
            int start2 = arr.newname.find("-", start+1);
            int end = arr.newname.length();
//            int row = atoi(arr.newname.substr(start+1, start2-start-1).c_str());
            int col = atoi(arr.newname.substr(start2+1, end-start2-1).c_str());
//            cout << col << endl;
            int x = atoi(symbol_table.table_list.at(right[2].attr.var_attr.table_i).at(right[2].attr.var_attr.item_i).value.c_str());
            int y = atoi(symbol_table.table_list.at(right[5].attr.var_attr.table_i).at(right[5].attr.var_attr.item_i).value.c_str());
            int delta = x*col+y;
            this->varAddrs.back()[newname] = this->varAddrs.back()[right[0].value] + delta*4;
        }
        else
            left.attr.var_attr.item_i = symbol_table.table_map_list.back()[newname];
        left.attr.var_attr.place = left.attr.var_attr.item_i;
        left.attr.var_attr.type = right[0].attr.var_attr.type;
    }
    left.attr.var_attr.table_i = symbol_table.table_list.size() - 1;
    return State::OK;
}

State CodeGenerator::transParam(Token& left, const vector<Token>& right)
{
    //params -> param_list
    //params ->
    //param_list -> param pre_param
    //pre_param ->
    //pre_param -> , param pre_param
    //argus ->
    //pre_expr ->
    if (0 == right.size())
        left.attr.fun_attr.param_num = 0;
    else if (1 == right.size())
        left.attr.fun_attr = right.front().attr.fun_attr;
    else if (2 == right.size())
        left.attr.fun_attr.param_num = right[0].attr.fun_attr.param_num + right[1].attr.fun_attr.param_num;
    else
        left.attr.fun_attr.param_num = right[1].attr.fun_attr.param_num + right[2].attr.fun_attr.param_num;

    return State::OK;
}

State CodeGenerator::clear_code()
{
    this->code_list.clear();
    this->entrances.clear();
    this->LISTtoCB.clear();
    this->codeblocks.clear();
    this->tarCode_list.clear();
    this->jmps.clear();
    this->jmpToNo.clear();
    this->jmpSingle.clear();
    this->visitedBlocks.clear();
    this->funcPoins.clear();
    this->funcParamNum.clear();
    this->valueToReg.clear();
    this->varAddrs.clear();
    this->startP.clear();
    return State::OK;
}

const Token& CodeGenerator::getErrorToken()				//返回出错信息
{
    return this->err_token;
}

/* new here */

State CodeGenerator::generateBBlock()
{
    if (this->code_list.size() <= 0)
        return State::ERROR;
    this->codeblocks.clear();
    //生成入口序列
    map<int, int> entrMap;
    this->entrances.push_back(0);
    entrMap[0] = 1;
    for (int i = 1; i < (int)(code_list.size()); i++)
    {
        if (code_list[i].op[0] == 'j')
        {
            if(entrMap.count(code_list[i].result) == 0)
            {
                this->entrances.push_back(code_list[i].result);
                entrMap[code_list[i].result] = 1;
            }
            if (code_list[i].op.length() > 1 && (entrMap.count(i+1) == 0))	//条件跳转
            {
                this->entrances.push_back(i+1);	//下一条语句
                entrMap[i+1] = 1;
            }
        }
        else if (code_list[i].op[0] == 'F') //函数入口
        {
            if(entrMap.count(i) == 0)
            {
                this->entrances.push_back(i);
                entrMap[i] = 1;
            }
            this->funcPoins.push_back(i);
        }
    }
    //program end
    if(entrMap.count(code_list.size()-1) == 0)
    {
        this->entrances.push_back(code_list.size()-1);
        entrMap[code_list.size()-1] = 1;
    }
    sort(this->entrances.begin(), this->entrances.end());

    //生成基本块
    for (int i = 0; i < (int)(this->entrances.size()); i++)
    {
        CodeBlock new_cb;
        new_cb.activeVars = vector<vector<int>>(2, vector<int>());
        new_cb.start = this->entrances[i];
        new_cb.end = (i + 1 < (int)(this->entrances.size()) ? this->entrances[i + 1] - 1 : code_list.size() - 1);
        LISTtoCB[new_cb.start] = codeblocks.size();	//建立映射关系
        codeblocks.push_back(new_cb);
    }
    //建立连接
    int nextFunc = 0;
    for (int i = 0; i < (int)(this->entrances.size()); i++)
    {
        int cb_i = LISTtoCB[this->entrances[i]];
        //跳转指令
        if (code_list[codeblocks[cb_i].end].op[0] == 'j')
        {
            codeblocks[cb_i].suffix.push_back(code_list[codeblocks[cb_i].end].result);
            //条件跳转
            if (code_list[codeblocks[cb_i].end].op.length() > 1 && codeblocks[cb_i].end + 1 < (int)(code_list.size()))
                codeblocks[cb_i].suffix.push_back(codeblocks[cb_i].end + 1);
        }
        else
        {
            if (codeblocks[cb_i].end + 1 < (int)(code_list.size()))
            {
                if(nextFunc == (int)(this->funcPoins.size()) || codeblocks[cb_i].end + 1 != this->funcPoins[nextFunc])
                    codeblocks[cb_i].suffix.push_back(codeblocks[cb_i].end + 1);
                else
                    nextFunc++;
            }
        }
    }

    this->visitedBlocks = vector<int>(this->codeblocks.size(), 0);

    return State::OK;
}

State CodeGenerator::preOperate()
{
    int cntP = 0;
    for(int i = 0; i < (int)(this->code_list.size()); i++)
    {
        if(code_list[i].op[0] == 'j' && this->jmpSingle.count(code_list[i].result) == 0)
        {
            this->jmps.push_back(code_list[i].result);
            this->jmpSingle[code_list[i].result] = 1;
        }
        if(code_list[i].op[0] == 'F')
        {
            cntP++;
            this->codeblocks[this->LISTtoCB[i]].tablePoin = cntP;
//            cout << this->LISTtoCB[i] << " " << cntP-1 << endl;
        }
        else
            this->codeblocks[this->LISTtoCB[i]].tablePoin = cntP;
    }
    sort(this->jmps.begin(), this->jmps.end());
    for(int i = 0; i < (int)(this->jmps.size()); i++)
        this->jmpToNo[this->jmps[i]] = i+1;
    return State::OK;
}

State CodeGenerator::addFirstInfo(CodeBlock &codeBlock, int arg, int kind, bool active)
{
    //判断活跃，加入活跃表
//    if(active)
//    {
//        codeBlock.activeVars[kind].push_back(arg);
//    }

    InfoPair ip;
    ip.useLoc = 0;
    ip.isActive = active;
    vector<InfoPair> nowpair = vector<InfoPair>(1, ip);

    if(kind == 0)
    {
        if(codeBlock.mapForG.count(arg) == 0)
        {
            codeBlock.mapForG[arg] = codeBlock.vars[kind].size();
            codeBlock.vars[kind].push_back(arg);
            codeBlock.linkedInfoG.push_back(nowpair);
        }
        else if(active)
        {
            codeBlock.linkedInfoG[codeBlock.mapForG[arg]] = nowpair;
        }
    }
    else
    {
        if(codeBlock.mapForL.count(arg) == 0)
        {
            codeBlock.mapForL[arg] = codeBlock.vars[kind].size();
            codeBlock.vars[kind].push_back(arg);
            codeBlock.linkedInfoL.push_back(nowpair);
        }
        else if(active)
        {
            codeBlock.linkedInfoL[codeBlock.mapForL[arg]] = nowpair;
        }
    }

    return State::OK;
}

State CodeGenerator::addInfo(CodeBlock &codeBlock, int arg, int kind)
{
    if(kind == 0)
    {
        if(codeBlock.mapForG.count(arg) >= 1)
            return State::OK;
        codeBlock.mapForG[arg] = codeBlock.vars[kind].size();
    }
    else
    {
        if(codeBlock.mapForL.count(arg) >= 1)
            return State::OK;
        codeBlock.mapForL[arg] = codeBlock.vars[kind].size();
    }

    codeBlock.vars[kind].push_back(arg);

    //判断出口活跃，加入活跃表
    for(int i = 0; i < (int)(codeBlock.suffix.size()); i++)
    {
        int blocki = LISTtoCB[codeBlock.suffix[i]];
        CodeBlock sonBlock = this->codeblocks[blocki];
        for(int j = 0; j < (int)(sonBlock.activeVars[kind].size()); j++)
        {
            if(sonBlock.activeVars[kind][j] == arg)
            {
                InfoPair ip;
                ip.useLoc = 0;
                ip.isActive = true;
                vector<InfoPair> nowpair = vector<InfoPair>(1, ip);
                if(kind == 0)
                    codeBlock.linkedInfoG.push_back(nowpair);
                else
                    codeBlock.linkedInfoL.push_back(nowpair);
                return State::OK;
            }
        }
    }

    //非出口活跃
    InfoPair ip;
    ip.useLoc = 0;
    ip.isActive = false;
    vector<InfoPair> nowpair = vector<InfoPair>(1, ip);
    if(kind == 0)
        codeBlock.linkedInfoG.push_back(nowpair);
    else
        codeBlock.linkedInfoL.push_back(nowpair);
    return State::OK;
}

State CodeGenerator::addLink(InfoTableRow &nowRow, CodeBlock &codeBlock, int paramPos, int arg, bool isGlobal, int useloc)
{
    InfoPair nowPair;
    //获取链中最后一个状态
    if(isGlobal)
        nowPair = codeBlock.linkedInfoG[codeBlock.mapForG[arg]][(int)(codeBlock.linkedInfoG[codeBlock.mapForG[arg]].size()-1)];
    else
        nowPair = codeBlock.linkedInfoL[codeBlock.mapForL[arg]][(int)(codeBlock.linkedInfoL[codeBlock.mapForL[arg]].size()-1)];
    //放入表项
    nowRow.params[paramPos] = nowPair;
    //更改状态链：
    InfoPair newPair = nowPair;
    newPair.useLoc = useloc;
    //左值则清空活跃
    if(paramPos == 0 && this->code_list[nowRow.code].op != "return")
        newPair.isActive = false;
    else
        newPair.isActive = true;

    if(isGlobal)
        codeBlock.linkedInfoG[codeBlock.mapForG[arg]].push_back(newPair);
    else
        codeBlock.linkedInfoL[codeBlock.mapForL[arg]].push_back(newPair);
    return State::OK;
}

bool CodeGenerator::isInMyVars(CodeBlock &codeBlock, int arg, int kind)
{
    for(int i = 0; i < (int)(codeBlock.activeVars[kind].size()); i++)
    {
        if(codeBlock.activeVars[kind][i] == arg)
            return true;
    }
    return false;
}

State CodeGenerator::addActiveVars(CodeBlock &codeBlock)
{
    for(int i = 0; i < (int)(codeBlock.suffix.size()); i++)
    {
        int blocki = LISTtoCB[codeBlock.suffix[i]];
        CodeBlock sonBlock = this->codeblocks[blocki];
        for(int j = 0; j < 2; j++)
        {
            for(int k = 0; k < (int)(sonBlock.activeVars[j].size()); k++)
            {
                if(!this->isInMyVars(codeBlock, sonBlock.activeVars[j][k], j))
                    codeBlock.activeVars[j].push_back(sonBlock.activeVars[j][k]);
            }
        }
    }
    return State::OK;
}

State CodeGenerator::completeInfoTable(CodeBlock &codeBlock)
{
    codeBlock.infoTable = vector<InfoTableRow>(codeBlock.end - codeBlock.start + 1);
    for(int i = codeBlock.end; i >= codeBlock.start; i--)
    {
        Code now = this->code_list[i];
        InfoTableRow nowRow;
        nowRow.code = i;
        nowRow.params = vector<InfoPair>(3);
        //左操作数
        if(now.arg1 != DEFAULT_LOC)
        {
            if(now.arg1_p == CodeGenerator::ARG_GLOBALVAR)
                this->addLink(nowRow, codeBlock, 1, now.arg1, true, i);
            else if(now.arg1_p == CodeGenerator::ARG_LOCALVAR)
                this->addLink(nowRow, codeBlock, 1, now.arg1, false, i);
        }

        //右操作数
        if(now.arg2 != DEFAULT_LOC)
        {
            if(now.arg2_p == CodeGenerator::ARG_GLOBALVAR)
                this->addLink(nowRow, codeBlock, 2, now.arg2, true, i);
            else if(now.arg2_p == CodeGenerator::ARG_LOCALVAR)
                this->addLink(nowRow, codeBlock, 2, now.arg2, false, i);
        }

        //左值
        if(now.result != DEFAULT_LOC)
        {
            if(now.result_p == CodeGenerator::ARG_GLOBALVAR)
                this->addLink(nowRow, codeBlock, 0, now.result, true, 0);
            else if(now.result_p == CodeGenerator::ARG_LOCALVAR)
                this->addLink(nowRow, codeBlock, 0, now.result, false, 0);
        }

        codeBlock.infoTable[i - codeBlock.start] = nowRow;
    }

    //全局变量-寻找入口活跃变量
    for(int k = 0; k < (int)(codeBlock.linkedInfoG.size()); k++)
    {
        if(codeBlock.linkedInfoG[k][(int)(codeBlock.linkedInfoG[k].size()-1)].isActive)
            codeBlock.activeVars[0].push_back(codeBlock.vars[0][k]);
    }
    //局部变量-寻找入口活跃变量
    for(int k = 0; k < (int)(codeBlock.linkedInfoL.size()); k++)
    {
        if(codeBlock.linkedInfoL[k][(int)(codeBlock.linkedInfoL[k].size()-1)].isActive)
        {
            //加判断，常量不加进去
//            auto& item = symbol_table.table_list[symbol_table.table_list.size()-1][codeBlock.vars[1][k]];
            auto& item = symbol_table.table_list[codeBlock.tablePoin][codeBlock.vars[1][k]];
            if(!item.is_inst)
                codeBlock.activeVars[1].push_back(codeBlock.vars[1][k]);
        }
    }

    this->addActiveVars(codeBlock);

    return State::OK;
}

State CodeGenerator::generateFirstInfoList(CodeBlock &codeBlock)
{
    vector<int> GList = vector<int>();
    vector<int> LList = vector<int>();
    codeBlock.vars.push_back(GList);
    codeBlock.vars.push_back(LList);
//    activeVars.push_back(GList);
//    activeVars.push_back(LList);

    for(int i = codeBlock.start; i <= codeBlock.end; i++)
    {
        Code now = this->code_list[i];
        //参数1
        if(now.arg1 != DEFAULT_LOC)
        {
            if(now.arg1_p == CodeGenerator::ARG_GLOBALVAR)
                this->addFirstInfo(codeBlock, now.arg1, 0, false);
            else if(now.arg1_p == CodeGenerator::ARG_LOCALVAR)
                this->addFirstInfo(codeBlock, now.arg1, 1, false);
        }
        //参数2
        if(now.arg2 != DEFAULT_LOC)
        {
            if(now.arg2_p == CodeGenerator::ARG_GLOBALVAR)
                this->addFirstInfo(codeBlock, now.arg2, 0, false);
            else if(now.arg2_p == CodeGenerator::ARG_LOCALVAR)
                this->addFirstInfo(codeBlock, now.arg2, 1, false);
        }
        //结果
        if(now.result != DEFAULT_LOC)
        {
            if(now.op == "return")
            {
                if(now.result_p == CodeGenerator::ARG_GLOBALVAR)
                    this->addFirstInfo(codeBlock, now.result, 0, true);
                else if(now.result_p == CodeGenerator::ARG_LOCALVAR)
                    this->addFirstInfo(codeBlock, now.result, 1, true);
            }
            else
            {
                if(now.result_p == CodeGenerator::ARG_GLOBALVAR)
                    this->addFirstInfo(codeBlock, now.result, 0, false);
                else if(now.result_p == CodeGenerator::ARG_LOCALVAR)
                    this->addFirstInfo(codeBlock, now.result, 1, false);
            }
        }
    }

    this->completeInfoTable(codeBlock);

    return State::OK;
}

bool CodeGenerator::codeBLoop(CodeBlock &codeBlock)
{
    for(int i = 0; i < (int)(codeBlock.suffix.size()); i++)
    {
        int blocki = LISTtoCB[codeBlock.suffix[i]];
        CodeBlock sonBlock = this->codeblocks[blocki];
        if(sonBlock.activeVars[0].size() == 0 && sonBlock.activeVars[1].size() == 0)
            return true;
    }
    return false;
}

//获取条件跳转的活跃变量
State CodeGenerator::getSonActiveVar(CodeBlock &codeBlock)
{
    for(int i = 0; i < (int)(codeBlock.suffix.size()); i++)
    {
        int blocki = LISTtoCB[codeBlock.suffix[i]];
        CodeBlock sonBlock = this->codeblocks[blocki];
        if(sonBlock.activeVars[0].size() == 0 && sonBlock.activeVars[1].size() == 0)
        {
            for(int i = sonBlock.end; i >= sonBlock.start; i--)
            {
                Code now = this->code_list[i];
                //左操作数
                if(now.arg1 != DEFAULT_LOC)
                {
                    if(now.arg1_p == CodeGenerator::ARG_GLOBALVAR && codeBlock.mapForG.count(now.arg1))
                        codeBlock.linkedInfoG[codeBlock.mapForG[now.arg1]][0].isActive = true;
                    else if(now.arg1_p == CodeGenerator::ARG_LOCALVAR && codeBlock.mapForL.count(now.arg1))
                        codeBlock.linkedInfoL[codeBlock.mapForL[now.arg1]][0].isActive = true;
                }

                //右操作数
                if(now.arg2 != DEFAULT_LOC)
                {
                    if(now.arg2_p == CodeGenerator::ARG_GLOBALVAR && codeBlock.mapForG.count(now.arg2))
                        codeBlock.linkedInfoG[codeBlock.mapForG[now.arg2]][0].isActive = true;
                    else if(now.arg2_p == CodeGenerator::ARG_LOCALVAR && codeBlock.mapForL.count(now.arg2))
                        codeBlock.linkedInfoL[codeBlock.mapForL[now.arg2]][0].isActive = true;
                }
            }
        }
    }
    return State::OK;
}

State CodeGenerator::generateInfoList(CodeBlock &codeBlock)
{
    vector<int> GList = vector<int>();
    vector<int> LList = vector<int>();
    codeBlock.vars.push_back(GList);
    codeBlock.vars.push_back(LList);

    for(int i = codeBlock.start; i <= codeBlock.end; i++)
    {
        Code now = this->code_list[i];
        //参数1
        if(now.arg1 != DEFAULT_LOC)
        {
            if(now.arg1_p == CodeGenerator::ARG_GLOBALVAR)
                this->addInfo(codeBlock, now.arg1, 0);
            else if(now.arg1_p == CodeGenerator::ARG_LOCALVAR)
                this->addInfo(codeBlock, now.arg1, 1);
        }
        //参数2
        if(now.arg2 != DEFAULT_LOC)
        {
            if(now.arg2_p == CodeGenerator::ARG_GLOBALVAR)
                this->addInfo(codeBlock, now.arg2, 0);
            else if(now.arg2_p == CodeGenerator::ARG_LOCALVAR)
                this->addInfo(codeBlock, now.arg2, 1);
        }
        //结果
        if(now.result != DEFAULT_LOC)
        {
            if(now.result_p == CodeGenerator::ARG_GLOBALVAR)
                this->addInfo(codeBlock, now.result, 0);
            else if(now.result_p == CodeGenerator::ARG_LOCALVAR)
                this->addInfo(codeBlock, now.result, 1);
        }
    }

    CodeBlock tmpBlock = codeBlock;

    this->completeInfoTable(codeBlock);

    if(codeBLoop(codeBlock))
    {
        //全局变量-寻找入口活跃变量
        for(int k = 0; k < (int)(codeBlock.linkedInfoG.size()); k++)
        {
            if(codeBlock.linkedInfoG[k][(int)(codeBlock.linkedInfoG[k].size()-1)].isActive)
                tmpBlock.linkedInfoG[k][0].isActive = true;
        }
        //局部变量-寻找入口活跃变量
        for(int k = 0; k < (int)(codeBlock.linkedInfoL.size()); k++)
        {
            if(codeBlock.linkedInfoL[k][(int)(codeBlock.linkedInfoL[k].size()-1)].isActive)
            {
                //加判断，常量不加进去
    //            auto& item = symbol_table.table_list[symbol_table.table_list.size()-1][codeBlock.vars[1][k]];
                auto& item = symbol_table.table_list[codeBlock.tablePoin][codeBlock.vars[1][k]];
                if(!item.is_inst)
                    tmpBlock.linkedInfoL[k][0].isActive = true;
            }
        }
        codeBlock = tmpBlock;

        this->getSonActiveVar(codeBlock);

        this->completeInfoTable(codeBlock);
    }

    return State::OK;
}

//为一个函数生成待用活跃信息表
State CodeGenerator::generateInfoTable(int start, int end)
{
    if(this->codeblocks.size() == 0)
        return State::ERROR;
    if(start < 0 || start >= (int)(this->codeblocks.size()))
        return State::ERROR;

    this->visitedBlocks[start] = 1;
    for(int i = 0; i < (int)(codeblocks[start].suffix.size()); i++)
    {
        int blocki = LISTtoCB[codeblocks[start].suffix[i]];
//        this->generateInfoList(this->codeblocks[blocki], activeVars);
        if(this->visitedBlocks[blocki] == 0)
            this->generateInfoTable(blocki, end);
    }
    if(start == end)
        this->generateFirstInfoList(this->codeblocks[start]);
    else
        this->generateInfoList(this->codeblocks[start]);

    return State::OK;
}

State CodeGenerator::generateAllInfoTable()
{
    this->preOperate();
    for(int i = 0; i < (int)(this->funcPoins.size()); i++)
    {
        //计算出函数的第一个基本块
        int codeP = this->LISTtoCB[this->funcPoins[i]];
        int endP;   //计算出函数的最后一个基本块
        if(i == (int)(this->funcPoins.size() - 1))
            endP = (int)(this->codeblocks.size() - 2);
        else
            endP = this->LISTtoCB[this->funcPoins[i+1]] - 1;
        this->generateInfoTable(codeP, endP);
    }
    return State::OK;
}

State CodeGenerator::writeInfoTable(const char *des_path)
{
    ofstream des(des_path);
    if (!des.is_open())
        return State::ERROR;


    for(int i = 0; i < (int)(this->codeblocks.size()); i++)
    {
        des << "code_block_" << i << ": " << endl;
        des << "四元式\t\t\t\t\t\t\t\t左值\t\t左操作数\t\t右操作数" << endl;
        for(int j = (int)(codeblocks[i].infoTable.size() - 1); j >= 0; j--)
        {
            InfoTableRow newRow = codeblocks[i].infoTable[j];
            this->writeCode(des, newRow.code, newRow.code);
            des << "\t\t\t\t";
            for(int k = 0; k < 3; k++)
            {
                if(newRow.params[k].useLoc == 0)
                    des << "(^, " << (newRow.params[k].isActive ? "y" : "^") << ")\t\t";
                else
                    des << "(" << newRow.params[k].useLoc << ", " << (newRow.params[k].isActive ? "y" : "^") << ")\t\t";
            }
            des << endl;
        }
        des << endl;
    }

    return State::OK;
}

State CodeGenerator::writeTarCodeToFile(const char *des_path)
{
    ofstream des(des_path);
    if (!des.is_open())
        return State::ERROR;

    int table_p = 0;
    for(int i = 0; i < (int)(this->tarCode_list.size()); i++)
    {
        TarCode nowCode = this->tarCode_list[i];
        //程序开始，跳转到main函数
        if (i == 0)
        {
            des << ".test\n";
            des << "j F" << symbol_table.funcname2index["main"] << "\n";
            continue;
        }   //程序末尾，增加end标签
        else if (i == (int)(this->tarCode_list.size() - 1))
        {
            if(table_p == symbol_table.funcname2index["main"])
                des << "j end\n";
            des << "\nend:";
            continue;
        }

        //函数起点
        if(nowCode.op[0] == 'P' || (nowCode.op[0] == 'F' && nowCode.op[1] != 'l'))
        {
            if(nowCode.op[0] == 'F')
            {
                table_p++;
                //main函数结束，跳转到end
                if(table_p == symbol_table.funcname2index["main"]+1)
                    des << "j end\n";
            }
            des << "\n" << nowCode.op << " \t";
            des << '\n';
            continue;
        }

        des << nowCode.op << " \t";

        if (nowCode.arg1 != DEFAULT_LOC && nowCode.op[0] != 'r' && nowCode.op[0] != 'J')
        {
            if (nowCode.arg1_p == CodeGenerator::ARG_LOCALVAR)
            {
//                auto& item = symbol_table.table_list.back()[nowCode.arg1];
                auto& item = symbol_table.table_list[table_p][nowCode.arg1];
                des << item.value;
            }
            else if (nowCode.arg1_p == CodeGenerator::ARG_GLOBALVAR)
            {
                auto& item = symbol_table.table_list.front()[nowCode.arg1];
                des << item.value;
            }
            else if (nowCode.arg1_p == CodeGenerator::ARG_REG)
                des << "$t" << nowCode.arg1;
            else if (nowCode.arg1_p == CodeGenerator::ARG_PREG)
                des << "$a" << nowCode.arg1;
            else if (nowCode.arg1_p == CodeGenerator::ARG_RReg)
                des << "$v" << nowCode.arg1;
            else if (nowCode.arg1_p == CodeGenerator::ARG_RAReg)
                des << "$ra";
            else if (nowCode.arg1_p == CodeGenerator::ARG_CALLFUNC)
                des << 'F' << nowCode.arg1;
//            des << nowCode.arg1;
            des << " ,\t";
        }


        if (nowCode.arg2 != DEFAULT_LOC)
        {
            if (nowCode.arg2_p == CodeGenerator::ARG_LOCALVAR)
            {
//                auto& item = symbol_table.table_list.back()[nowCode.arg2];
                auto& item = symbol_table.table_list[table_p][nowCode.arg2];
                //传参
                if(nowCode.op != "return" && nowCode.arg2 <= this->funcParamNum[table_p])
                {
                    des << "$a" << (this->funcParamNum[table_p] - nowCode.arg2);
                }
                else
                    des << item.value;
            }
            else if (nowCode.arg2_p == CodeGenerator::ARG_GLOBALVAR)
            {
                auto& item = symbol_table.table_list.front()[nowCode.arg2];
                des << item.value;
            }
            else if (nowCode.arg2_p == CodeGenerator::ARG_REG)
                des << "$t" << nowCode.arg2;
            else if (nowCode.arg2_p == CodeGenerator::ARG_RReg)
                des << "$v" << nowCode.arg2;
            else if (nowCode.arg2_p == CodeGenerator::ARG_RAReg)
                des << "$ra";
            else if (nowCode.op[0] == 'J')
            {
                des << "Flag" << nowCode.arg2;
//                des << "Flag" << this->jmpToNo[nowCode.arg2];
            }
            else
                des << nowCode.arg2;
        }

        des << '\n';
    }
    return State::OK;
}

State CodeGenerator::writeTarCodeToFile2(const char *des_path)
{
    ofstream des(des_path);
    if (!des.is_open())
        return State::ERROR;

    int table_p = 0;
    for(int i = 0; i < (int)(this->tarCode_list.size()); i++)
    {
        TarCode nowCode = this->tarCode_list[i];
        //程序开始，跳转到main函数
        if (i == 0)
        {
            des << ".test\n";
            //全局变量首地址
            des << "addi\t$k0,\t$zero,\t0x10010000\n";
            //局部变量首地址
            des << "addi\t$k1,\t$zero,\t0x10010100\n";
            //跳转到main函数
            des << "j F" << symbol_table.funcname2index["main"] << "\n";
            continue;
        }   //程序末尾，增加end标签
        else if (i == (int)(this->tarCode_list.size() - 1))
        {
            if(table_p == symbol_table.funcname2index["main"])
                des << "j end\n";
            des << "\nend:";
            continue;
        }

        if(nowCode.op == "jal")
            des << "add\t$k1,\t$k1,\t0x00000100\n";
        if(nowCode.op == "jr")
            des << "sub\t$k1,\t$k1,\t0x00000100\n";

        //函数起点
        if(nowCode.op[0] == 'P' || (nowCode.op[0] == 'F' && nowCode.op[1] != 'l'))
        {
            if(nowCode.op[0] == 'F')
            {
                table_p++;
                //main函数结束，跳转到end
                if(table_p == symbol_table.funcname2index["main"]+1)
                    des << "j end\n";
            }
            des << "\n" << nowCode.op << " \t";
            des << '\n';
            continue;
        }

        des << nowCode.op << " \t";

        if (nowCode.arg1 != DEFAULT_LOC && nowCode.op[0] != 'r' && nowCode.op[0] != 'J')
        {
            if (nowCode.arg1_p == CodeGenerator::ARG_LOCALVAR)
            {
                //传参
                if(nowCode.arg1 <= this->funcParamNum[table_p])
                {
                    des << "$a" << (this->funcParamNum[table_p] - nowCode.arg1);
                }
                else
                {
                    auto& item = symbol_table.table_list[table_p][nowCode.arg1];
                    des << item.value;
                }
            }
            else if (nowCode.arg1_p == CodeGenerator::ARG_GLOBALVAR)
            {
                auto& item = symbol_table.table_list.front()[nowCode.arg1];
                des << item.value;
            }
            else if (nowCode.arg1_p == CodeGenerator::ARG_REG)
            {
                if(table_p != symbol_table.funcname2index["main"])
                    des << "$s" << nowCode.arg1;
                else
                    des << "$t" << nowCode.arg1;
            }
            else if (nowCode.arg1_p == CodeGenerator::ARG_PREG)
                des << "$a" << nowCode.arg1;
            else if (nowCode.arg1_p == CodeGenerator::ARG_RReg)
                des << "$v" << nowCode.arg1;
            else if (nowCode.arg1_p == CodeGenerator::ARG_RAReg)
                des << "$ra";
            else if (nowCode.arg1_p == CodeGenerator::ARG_CALLFUNC)
                des << 'F' << nowCode.arg1;
//            des << nowCode.arg1;
            des << ",\t";
        }

        if (nowCode.arg1 != DEFAULT_LOC && nowCode.op[0] != 'r' && nowCode.op[0] != 'J')
        {
            if(nowCode.op == "addi")
            {
                des << "$zero,\t";
            }
            else if(nowCode.op == "add" || nowCode.op == "sub" || nowCode.op == "mul" || nowCode.op == "div")
            {
                if (nowCode.arg1_p == CodeGenerator::ARG_LOCALVAR)
                {
    //                auto& item = symbol_table.table_list.back()[nowCode.arg1];
                    auto& item = symbol_table.table_list[table_p][nowCode.arg1];
                    des << item.value;
                }
                else if (nowCode.arg1_p == CodeGenerator::ARG_GLOBALVAR)
                {
                    auto& item = symbol_table.table_list.front()[nowCode.arg1];
                    des << item.value;
                }
                else if (nowCode.arg1_p == CodeGenerator::ARG_REG)
                {
                    if(table_p != symbol_table.funcname2index["main"])
                        des << "$s" << nowCode.arg1;
                    else
                        des << "$t" << nowCode.arg1;
                }
                else if (nowCode.arg1_p == CodeGenerator::ARG_PREG)
                    des << "$a" << nowCode.arg1;
                else if (nowCode.arg1_p == CodeGenerator::ARG_RReg)
                    des << "$v" << nowCode.arg1;
                else if (nowCode.arg1_p == CodeGenerator::ARG_RAReg)
                    des << "$ra";
                else if (nowCode.arg1_p == CodeGenerator::ARG_CALLFUNC)
                    des << 'F' << nowCode.arg1;
                des << ",\t";
            }
        }


        if (nowCode.arg2 != DEFAULT_LOC)
        {
            if (nowCode.arg2_p == CodeGenerator::ARG_LOCALVAR)
            {
                if(nowCode.op == "sw" || nowCode.op == "lw")
                {
//                    des << 4*(nowCode.arg2-1) << "($k1)";
                    des << this->varAddrs[table_p][symbol_table.table_list[table_p][nowCode.arg2].value] << "($k1)";
                }
                else
                {
                    auto& item = symbol_table.table_list[table_p][nowCode.arg2];
                    //传参
                    if(nowCode.op != "return" && nowCode.arg2 <= this->funcParamNum[table_p])
                    {
                        des << "$a" << (this->funcParamNum[table_p] - nowCode.arg2);
                    }
                    else
                        des << item.value;
                }
            }
            else if (nowCode.arg2_p == CodeGenerator::ARG_GLOBALVAR)
            {
                if(nowCode.op == "sw" || nowCode.op == "lw")
                {
//                    des << 4*(nowCode.arg2-1) << "($k0)";
                    des << this->varAddrs[0][symbol_table.table_list[0][nowCode.arg2].value] << "($k0)";
                }
                else
                {
                    auto& item = symbol_table.table_list.front()[nowCode.arg2];
                    des << item.value;
                }
            }
            else if (nowCode.arg2_p == CodeGenerator::ARG_REG)
            {
                if(table_p != symbol_table.funcname2index["main"])
                    des << "$s" << nowCode.arg2;
                else
                    des << "$t" << nowCode.arg2;
            }
            else if (nowCode.arg2_p == CodeGenerator::ARG_RReg)
                des << "$v" << nowCode.arg2;
            else if (nowCode.arg2_p == CodeGenerator::ARG_RAReg)
                des << "$ra";
            else if (nowCode.op == "j" || nowCode.op == "bnez")
            {
                des << "Flag" << nowCode.arg2;
//                des << "Flag" << this->jmpToNo[nowCode.arg2];
            }
            else
                des << nowCode.arg2;
        }

        if (nowCode.op == "movz")
            des << ",\t$zero";
        if(nowCode.arg3 != -1)
        {
            if(nowCode.op[0] == 'b')
                des << ",\tFlag" << nowCode.arg3;
        }

        des << '\n';
    }
    return State::OK;
}

State CodeGenerator::initialReg(CodeBlock &codeBlock)
{
    if(codeBlock.vars.size() == 0)
        return State::ERROR;
    codeBlock.AVALUE = vector<vector<int>>(2);
    codeBlock.AVALUE[0] = vector<int>(codeBlock.vars[0].size(), -1);
    codeBlock.AVALUE[1] = vector<int>(codeBlock.vars[1].size(), -1);
    codeBlock.RVALUE = vector<vector<int>>(2);
    codeBlock.RVALUE[0] = vector<int>(CodeGenerator::REG_NUM, -1);
    codeBlock.RVALUE[1] = vector<int>(CodeGenerator::REG_NUM, -1);
    codeBlock.linkedP = vector<vector<int>>(2);
    for(int i = 0; i < (int)(codeBlock.linkedInfoG.size()); i++)
        codeBlock.linkedP[0].push_back(codeBlock.linkedInfoG[i].size()-1);
    for(int i = 0; i < (int)(codeBlock.linkedInfoL.size()); i++)
        codeBlock.linkedP[1].push_back(codeBlock.linkedInfoL[i].size()-1);
    return State::OK;
}

State CodeGenerator::updateLinkP(CodeBlock &codeBlock, int result, int arg1, int arg2, int result_p, int arg1_p, int arg2_p)
{
    //更新指针
    if(arg1 != DEFAULT_LOC)
    {
        if(arg1_p == CodeGenerator::ARG_GLOBALVAR)
            codeBlock.linkedP[0][codeBlock.mapForG[arg1]]--;
        else if(arg1_p == CodeGenerator::ARG_LOCALVAR)
            codeBlock.linkedP[1][codeBlock.mapForL[arg1]]--;
    }
    //参数2
    if(arg2 != DEFAULT_LOC)
    {
        if(arg2_p == CodeGenerator::ARG_GLOBALVAR)
            codeBlock.linkedP[0][codeBlock.mapForG[arg2]]--;
        else if(arg2_p == CodeGenerator::ARG_LOCALVAR)
            codeBlock.linkedP[1][codeBlock.mapForL[arg2]]--;
    }
    //结果
    if(result != DEFAULT_LOC)
    {
        if(result_p == CodeGenerator::ARG_GLOBALVAR)
            codeBlock.linkedP[0][codeBlock.mapForG[result]]--;
        else if(result_p == CodeGenerator::ARG_LOCALVAR)
            codeBlock.linkedP[1][codeBlock.mapForL[result]]--;
    }
    return State::OK;
}

State CodeGenerator::genStore(CodeBlock &codeBlock, int result, int arg1, int arg2, int result_p, int arg1_p, int arg2_p)
{
    //参数1
    if(arg1 != DEFAULT_LOC)
    {
        if(arg1_p == CodeGenerator::ARG_GLOBALVAR)
        {
            int argp = codeBlock.mapForG[arg1];
            if(codeBlock.linkedP[0][argp] == 0 && codeBlock.linkedInfoG[argp][0].isActive && codeBlock.AVALUE[0][argp] != -1)
                this->genTar("sw", codeBlock.AVALUE[0][argp], arg1, CodeGenerator::ARG_REG, CodeGenerator::ARG_GLOBALVAR);
        }
        else if(arg1_p == CodeGenerator::ARG_LOCALVAR)
        {
            int argp = codeBlock.mapForL[arg1];
            if(codeBlock.linkedP[1][argp] == 0 && codeBlock.linkedInfoL[argp][0].isActive && codeBlock.AVALUE[1][argp] != -1)
                this->genTar("sw", codeBlock.AVALUE[1][argp], arg1, CodeGenerator::ARG_REG, CodeGenerator::ARG_LOCALVAR);
        }
    }
    //参数2
    if(arg2 != DEFAULT_LOC)
    {
        if(arg2_p == CodeGenerator::ARG_GLOBALVAR)
        {
            int argp = codeBlock.mapForG[arg2];
            if(codeBlock.linkedP[0][argp] == 0 && codeBlock.linkedInfoG[argp][0].isActive && codeBlock.AVALUE[0][argp] != -1)
                this->genTar("sw", codeBlock.AVALUE[0][argp], arg2, CodeGenerator::ARG_REG, CodeGenerator::ARG_GLOBALVAR);
        }
        else if(arg2_p == CodeGenerator::ARG_LOCALVAR)
        {
            int argp = codeBlock.mapForL[arg2];
            if(codeBlock.linkedP[1][argp] == 0 && codeBlock.linkedInfoL[argp][0].isActive && codeBlock.AVALUE[1][argp] != -1)
                this->genTar("sw", codeBlock.AVALUE[1][argp], arg2, CodeGenerator::ARG_REG, CodeGenerator::ARG_LOCALVAR);
        }
    }
    //result参数
    if(result != DEFAULT_LOC)
    {
        if(result_p == CodeGenerator::ARG_GLOBALVAR)
        {
            int argp = codeBlock.mapForG[result];
            if(codeBlock.linkedP[0][argp] == 0 && codeBlock.linkedInfoG[argp][0].isActive && codeBlock.AVALUE[0][argp] != -1)
                this->genTar("sw", codeBlock.AVALUE[0][argp], result, CodeGenerator::ARG_REG, CodeGenerator::ARG_GLOBALVAR);
        }
        else if(result_p == CodeGenerator::ARG_LOCALVAR)
        {
            int argp = codeBlock.mapForL[result];
            if(codeBlock.linkedP[1][argp] == 0 && codeBlock.linkedInfoL[argp][0].isActive && codeBlock.AVALUE[1][argp] != -1)
                this->genTar("sw", codeBlock.AVALUE[1][argp], result, CodeGenerator::ARG_REG, CodeGenerator::ARG_LOCALVAR);
        }
    }
    return State::OK;
}

int CodeGenerator::getReg(CodeBlock &codeBlock, int result, int arg1, int arg2, int result_p, int arg1_p, int arg2_p, int tableRow)
{
    if(codeBlock.vars.size() == 0)
        return -1;
    //A = B op C

    //全局
    if(arg1_p == CodeGenerator::ARG_GLOBALVAR)
    {
        int reg_no = codeBlock.AVALUE[0][codeBlock.mapForG[arg1]];
        //B存在某个寄存器中
        if(reg_no != -1)
        {
            //A和B相同
            if(arg1 == result && arg1_p == result_p)
                return reg_no;
            //B之后非待用非活跃
            if(codeBlock.infoTable[tableRow].params[1].useLoc == 0 && codeBlock.infoTable[tableRow].params[1].isActive == false)
                return reg_no;
        }
    }   //局部
    else if(arg1_p == CodeGenerator::ARG_LOCALVAR)
    {
        int reg_no = codeBlock.AVALUE[1][codeBlock.mapForL[arg1]];
        //B存在某个寄存器中
        if(reg_no != -1)
        {
            //A和B相同
            if(arg1 == result && arg1_p == result_p)
                return reg_no;
            //B之后非待用非活跃
            if(codeBlock.infoTable[tableRow].params[1].useLoc == 0 && codeBlock.infoTable[tableRow].params[1].isActive == false)
                return reg_no;
        }
    }

    //寻找空闲寄存器
    for(int i = 0; i < CodeGenerator::REG_NUM; i++)
    {
        if(codeBlock.RVALUE[0][i] == -1 && codeBlock.RVALUE[1][i] == -1)
            return i;
    }
    //到这里还没return，只能抢占寄存器了
    //抢占非待用非活跃
    for(int i = 0; i < CodeGenerator::REG_NUM; i++)
    {
        if(codeBlock.RVALUE[0][i] != -1)
        {
            int var_p = codeBlock.mapForG[codeBlock.RVALUE[0][i]];
            InfoPair nowPair = codeBlock.linkedInfoG[var_p][codeBlock.linkedP[0][var_p]];
            if(nowPair.useLoc == 0 && nowPair.isActive == false)
            {
                this->genTar("ST", i, codeBlock.RVALUE[0][i], CodeGenerator::ARG_REG, CodeGenerator::ARG_GLOBALVAR);
                return i;
            }
        }
        if(codeBlock.RVALUE[1][i] != -1)
        {
            int var_p = codeBlock.mapForL[codeBlock.RVALUE[1][i]];
            InfoPair nowPair = codeBlock.linkedInfoL[var_p][codeBlock.linkedP[1][var_p]];
            if(nowPair.useLoc == 0 && nowPair.isActive == false)
            {
                this->genTar("ST", i, codeBlock.RVALUE[1][i], CodeGenerator::ARG_REG, CodeGenerator::ARG_LOCALVAR);
                return i;
            }
        }
    }

    //找不到合适的替换对象，替换掉第一个
    //全局
    for(int i = 0; i < (int)(codeBlock.AVALUE[0].size()); i++)
    {
        if(codeBlock.AVALUE[0][i] == 0)
            this->genTar("ST", 0, codeBlock.RVALUE[0][0], CodeGenerator::ARG_REG, CodeGenerator::ARG_GLOBALVAR);
    }
    for(int i = 0; i < (int)(codeBlock.AVALUE[1].size()); i++)
    {
        if(codeBlock.AVALUE[1][i] == 0)
            this->genTar("ST", 0, codeBlock.RVALUE[1][0], CodeGenerator::ARG_REG, CodeGenerator::ARG_LOCALVAR);
    }
    return 0;
}

State CodeGenerator::updateRegA(CodeBlock &codeBlock, int reg, int arg, int arg_p)
{
    if(arg_p == CodeGenerator::ARG_GLOBALVAR)
    {
        codeBlock.AVALUE[0][codeBlock.mapForG[arg]] = reg;
        codeBlock.RVALUE[0][reg] = arg;
    }
    else if(arg_p == CodeGenerator::ARG_LOCALVAR)
    {
        codeBlock.AVALUE[1][codeBlock.mapForL[arg]] = reg;
        codeBlock.RVALUE[1][reg] = arg;
    }
    return State::OK;
}

State CodeGenerator::updateReg(CodeBlock &codeBlock, int reg, int arg, int arg_p)
{
    if(arg_p == CodeGenerator::ARG_GLOBALVAR)
    {
        int var_p = codeBlock.mapForG[arg];
        InfoPair nowPair = codeBlock.linkedInfoG[var_p][codeBlock.linkedP[0][var_p]];
        if(nowPair.useLoc == 0 && nowPair.isActive == false)
        {
            codeBlock.AVALUE[0][var_p] = -1;
            codeBlock.RVALUE[0][reg] = -1;
        }
    }
    else if(arg_p == CodeGenerator::ARG_LOCALVAR)
    {
        int var_p = codeBlock.mapForL[arg];
        InfoPair nowPair = codeBlock.linkedInfoL[var_p][codeBlock.linkedP[1][var_p]];
        if(nowPair.useLoc == 0 && nowPair.isActive == false)
        {
            codeBlock.AVALUE[1][var_p] = -1;
            codeBlock.RVALUE[1][reg] = -1;
        }
    }
    return State::OK;
}

int CodeGenerator::getRegNo(CodeBlock &codeBlock, int arg, int arg_p)
{
    if(arg == DEFAULT_LOC)
        return -1;
    if(arg_p == CodeGenerator::ARG_GLOBALVAR)
        return codeBlock.AVALUE[0][codeBlock.mapForG[arg]];
    else if(arg_p == CodeGenerator::ARG_LOCALVAR)
        return codeBlock.AVALUE[1][codeBlock.mapForL[arg]];
    else
        return -1;
}

State CodeGenerator::genTarCodeBlock(CodeBlock &codeBlock)
{
    this->initialReg(codeBlock);
    for(int i = codeBlock.start; i <= codeBlock.end; i++)
    {
        if(this->jmpToNo.count(i) != 0)
            this->genTar("Flag"+to_string(this->jmpToNo[i])+":", -1, -1, -1, -1);
        Code now = this->code_list[i];
        this->updateLinkP(codeBlock, now.result, now.arg1, now.arg2, now.result_p, now.arg1_p, now.arg2_p);

        //A = B op C
        if(now.op[0] != 'j' && now.arg1 != DEFAULT_LOC && now.arg2 != DEFAULT_LOC && now.result != DEFAULT_LOC)
        {
            int reg_no = this->getReg(codeBlock, now.result, now.arg1, now.arg2, now.result_p, now.arg1_p, now.arg2_p, i-codeBlock.start);
            if(reg_no == -1)
                return State::ERROR;
            int regA, regB, regC;
            regB = this->getRegNo(codeBlock, now.arg1, now.arg1_p);
            regC = this->getRegNo(codeBlock, now.arg2, now.arg2_p);
            regA = this->getRegNo(codeBlock, now.result, now.result_p);
            //LD R, B
            if(regB != reg_no)
            {
                if(regB == -1)
                    this->genTar("LD", reg_no, now.arg1, CodeGenerator::ARG_REG, now.arg1_p);
                else
                    this->genTar("LD", reg_no, regB, CodeGenerator::ARG_REG, CodeGenerator::ARG_REG);
            }
            //OP R, C
            if(regC == -1)
                this->genTar(now.op, reg_no, now.arg2, CodeGenerator::ARG_REG, now.arg2_p);
            else
                this->genTar(now.op, reg_no, regC, CodeGenerator::ARG_REG, CodeGenerator::ARG_REG);
            //更新A、B和C状态
            if(regA != -1)
                this->updateReg(codeBlock, regA, now.result, now.result_p);
            if(regB != -1)
                this->updateReg(codeBlock, regB, now.arg1, now.arg1_p);
            if(regC != -1)
                this->updateReg(codeBlock, regC, now.arg2, now.arg2_p);
            //更新A的AVALUE和RVALUE
            this->updateRegA(codeBlock, reg_no, now.result, now.result_p);
            this->genStore(codeBlock, now.result, now.arg1, now.arg2, now.result_p, now.arg1_p, now.arg2_p);
            continue;
        }
        //赋值指令
        if(now.op == "=")
        {
            int regB = this->getRegNo(codeBlock, now.arg1, now.arg1_p);
            int regA = this->getRegNo(codeBlock, now.result, now.result_p);
            if(regA == -1)
            {
                int reg_no = this->getReg(codeBlock, now.result, now.arg1, now.arg2, now.result_p, now.arg1_p, now.arg2_p, i-codeBlock.start);
                if(reg_no == -1)
                    return State::ERROR;
                if(regB == -1)
                    this->genTar("LD", reg_no, now.arg1, CodeGenerator::ARG_REG, now.arg1_p);
                else if(regB != reg_no)
                    this->genTar("LD", reg_no, regB, CodeGenerator::ARG_REG, CodeGenerator::ARG_REG);
                //更新寄存器
                if(regA != -1)
                    this->updateReg(codeBlock, regA, now.result, now.result_p);
                if(regB != -1)
                    this->updateReg(codeBlock, regB, now.arg1, now.arg1_p);
                this->updateRegA(codeBlock, reg_no, now.result, now.result_p);
            }
            else
            {
                if(regB == -1)
                    this->genTar("LD", regA, now.arg1, CodeGenerator::ARG_REG, now.arg1_p);
                else
                    this->genTar("LD", regA, regB, CodeGenerator::ARG_REG, CodeGenerator::ARG_REG);
                //更新寄存器
                if(regA != -1)
                    this->updateReg(codeBlock, regA, now.result, now.result_p);
                if(regB != -1)
                    this->updateReg(codeBlock, regB, now.arg1, now.arg1_p);
            }
            this->genStore(codeBlock, now.result, now.arg1, now.arg2, now.result_p, now.arg1_p, now.arg2_p);
            continue;
        }
        //跳转指令
        if(now.op[0] == 'j')
        {
            this->genStore(codeBlock, now.result, now.arg1, now.arg2, now.result_p, now.arg1_p, now.arg2_p);
            now.op[0] = 'J';
            int regB, regC;
            regB = this->getRegNo(codeBlock, now.arg1, now.arg1_p);
            regC = this->getRegNo(codeBlock, now.arg2, now.arg2_p);
            //J dst
            if(now.op.length() == 1)
                this->genTar("J", now.arg1, this->jmpToNo[now.result], now.arg1_p, now.result_p);
            else if(now.op == "Jnz")   //Jopt A B dst
            {
                if(regB == -1 && now.arg1 != DEFAULT_LOC)
                    this->genTar("CMP", now.arg1, 0, now.arg1_p, CodeGenerator::ARG_INST);
                else
                    this->genTar("CMP", regB, 0, CodeGenerator::ARG_REG, CodeGenerator::ARG_INST);
                this->genTar(now.op, now.arg1, this->jmpToNo[now.result], now.arg1_p, now.result_p);
            }
            else
            {
                if(regB == -1 && now.arg1 != DEFAULT_LOC)
                {
                    if(regC == -1 && now.arg2 != DEFAULT_LOC)
                        this->genTar("CMP", now.arg1, now.arg2, now.arg1_p, now.arg2_p);
                    else
                        this->genTar("CMP", now.arg1, regC, now.arg1_p, CodeGenerator::ARG_REG);
                }
                else
                {
                    if(regC == -1 && now.arg2 != DEFAULT_LOC)
                        this->genTar("CMP", regB, now.arg2, CodeGenerator::ARG_REG, now.arg2_p);
                    else
                        this->genTar("CMP", regB, regC, CodeGenerator::ARG_REG, CodeGenerator::ARG_REG);
                }
//                this->genTar("CMP", now.arg1, now.arg1_p, now.arg2, now.arg2_p);
                this->genTar(now.op, now.arg1, this->jmpToNo[now.result], now.arg1_p, now.result_p);
            }

            continue;
        }
        //return
        if(now.op == "return")
        {
            this->genStore(codeBlock, now.result, now.arg1, now.arg2, now.result_p, now.arg1_p, now.arg2_p);
            this->genTar("LD", 0, now.result, CodeGenerator::ARG_RReg, now.result_p);
            if(codeBlock.tablePoin != symbol_table.funcname2index["main"])
                this->genTar("jr", now.arg1, now.result, now.arg1_p, CodeGenerator::ARG_RAReg);

            continue;
        }
        //param
        if(now.op == "param")
        {
            int regB = this->getRegNo(codeBlock, now.arg1, now.arg1_p);
            if (now.arg1_p == CodeGenerator::ARG_LOCALVAR)
            {
                auto& item = symbol_table.table_list[codeBlock.tablePoin][now.arg1];
                this->valueToReg[item.value] = this->valueToReg.size();
                if(regB != -1)
                    this->genTar("LD", this->valueToReg.size()-1, regB, CodeGenerator::ARG_PREG, CodeGenerator::ARG_REG);
                else
                    this->genTar("LD", this->valueToReg.size()-1, now.arg1, CodeGenerator::ARG_PREG, now.arg1_p);
            }
            else if (now.arg1_p == CodeGenerator::ARG_GLOBALVAR)
            {
                auto& item = symbol_table.table_list.front()[now.arg1];
                this->valueToReg[item.value] = this->valueToReg.size();
                if(regB != -1)
                    this->genTar("LD", this->valueToReg.size()-1, regB, CodeGenerator::ARG_PREG, CodeGenerator::ARG_REG);
                else
                    this->genTar("LD", this->valueToReg.size()-1, now.arg1, CodeGenerator::ARG_PREG, now.arg1_p);
            }

            this->genStore(codeBlock, now.result, now.arg1, now.arg2, now.result_p, now.arg1_p, now.arg2_p);
            continue;
        }
        //函数调用
        if(now.op == "call")
        {
            int regA = this->getRegNo(codeBlock, now.result, now.result_p);
            this->genTar("jal", now.arg1, -1, now.arg1_p, -1);
            int reg_no;
            if(regA == -1)
                reg_no = this->getReg(codeBlock, now.result, now.result, now.arg2, now.result_p, now.result_p, now.arg2_p, i-codeBlock.start);
            else
                reg_no = regA;
            this->genTar("LD", reg_no, 0, CodeGenerator::ARG_REG, CodeGenerator::ARG_RReg);
            this->genStore(codeBlock, now.result, now.arg1, now.arg2, now.result_p, now.arg1_p, now.arg2_p);
            this->updateRegA(codeBlock, reg_no, now.result, now.result_p);
            this->valueToReg.clear();
            continue;
        }
        //F
//        if(now.op[0] == 'F')
//        {
//            this->funcs.push_back(this->tarCode_list.size());
//            this->genTar(now.op, now.arg1, now.result, now.arg1_p, now.result_p);
//            this->genStore(codeBlock, now.result, now.arg1, now.arg2, now.result_p, now.arg1_p, now.arg2_p);
//            continue;
//        }
        //其他
        this->genTar(now.op, now.arg1, now.result, now.arg1_p, now.result_p);
        this->genStore(codeBlock, now.result, now.arg1, now.arg2, now.result_p, now.arg1_p, now.arg2_p);
    }

    return State::OK;
}

State CodeGenerator::getVarForJ(int &reg_no, int arg, int arg_p, CodeBlock &codeBlock, Code &now, int i)
{
//    reg_no = this->getReg(codeBlock, now.result, now.arg1, now.arg2, now.result_p, now.arg1_p, now.arg2_p, i-codeBlock.start);
    reg_no = this->getReg(codeBlock, arg, arg, arg, arg_p, arg_p, arg_p, i-codeBlock.start);
    if(arg_p == CodeGenerator::ARG_LOCALVAR)
    {
        auto& item = symbol_table.table_list[codeBlock.tablePoin][arg];
        //非常量
        if(!item.is_inst && arg > this->funcParamNum[codeBlock.tablePoin]) //变量在内存
        {
            this->genTar("lw", reg_no, arg, CodeGenerator::ARG_REG, arg_p);
            this->updateRegA(codeBlock, reg_no, arg, arg_p);
        }
        else
            return State::ERROR;
    }
    else    //全局变量需要lw
    {
        this->genTar("lw", reg_no, arg, CodeGenerator::ARG_REG, arg_p);
        this->updateRegA(codeBlock, reg_no, arg, arg_p);
    }
    return State::OK;
}

State CodeGenerator::getVarForBnez(int &reg_no, int arg, int arg_p, CodeBlock &codeBlock, Code &now, int i)
{
//    reg_no = this->getReg(codeBlock, now.result, now.arg1, now.arg2, now.result_p, now.arg1_p, now.arg2_p, i-codeBlock.start);
    reg_no = this->getReg(codeBlock, arg, arg, arg, arg_p, arg_p, arg_p, i-codeBlock.start);
    if(arg_p == CodeGenerator::ARG_LOCALVAR)
    {
        auto& item = symbol_table.table_list[codeBlock.tablePoin][arg];
        //非常量
        if(!item.is_inst && arg > this->funcParamNum[codeBlock.tablePoin]) //变量在内存
        {
            this->genTar("lw", reg_no, arg, CodeGenerator::ARG_REG, arg_p);
            this->updateRegA(codeBlock, reg_no, arg, arg_p);
        }
        else
        {
            this->genTar("addi", reg_no, arg, CodeGenerator::ARG_REG, arg_p);
            this->updateRegA(codeBlock, reg_no, arg, arg_p);
        }
    }
    else    //全局变量需要lw
    {
        this->genTar("lw", reg_no, arg, CodeGenerator::ARG_REG, arg_p);
        this->updateRegA(codeBlock, reg_no, arg, arg_p);
    }
    return State::OK;
}

State CodeGenerator::genTarCodeBlock2(CodeBlock &codeBlock)
{
    this->initialReg(codeBlock);
    for(int i = codeBlock.start; i <= codeBlock.end; i++)
    {
        if(this->jmpToNo.count(i) != 0)
            this->genTar("Flag"+to_string(this->jmpToNo[i])+":", -1, -1, -1, -1);
        Code now = this->code_list[i];
        this->updateLinkP(codeBlock, now.result, now.arg1, now.arg2, now.result_p, now.arg1_p, now.arg2_p);

        //A = B op C
        if(now.op[0] != 'j' && now.arg1 != DEFAULT_LOC && now.arg2 != DEFAULT_LOC && now.result != DEFAULT_LOC)
        {
            int reg_no = this->getReg(codeBlock, now.result, now.arg1, now.arg2, now.result_p, now.arg1_p, now.arg2_p, i-codeBlock.start);
            if(reg_no == -1)
                return State::ERROR;
            int regA, regB, regC;
            regB = this->getRegNo(codeBlock, now.arg1, now.arg1_p);
            regC = this->getRegNo(codeBlock, now.arg2, now.arg2_p);
            regA = this->getRegNo(codeBlock, now.result, now.result_p);
            //LD R, B
            if(regB != reg_no)
            {
                if(regB == -1)
                {
                    if(now.arg1_p == CodeGenerator::ARG_LOCALVAR)
                    {
                        auto& item = symbol_table.table_list[codeBlock.tablePoin][now.arg1];
                        //常量
                        if(item.is_inst)
                            this->genTar("addi", reg_no, now.arg1, CodeGenerator::ARG_REG, now.arg1_p);
                        else
                        {
                            //变量在参数中
                            if(now.arg1 <= this->funcParamNum[codeBlock.tablePoin])
                                this->genTar("movz", reg_no, now.arg1, CodeGenerator::ARG_REG, now.arg1_p);
                            else    //变量在内存
                                this->genTar("lw", reg_no, now.arg1, CodeGenerator::ARG_REG, now.arg1_p);
                        }
                    }
                    else
                        this->genTar("lw", reg_no, now.arg1, CodeGenerator::ARG_REG, now.arg1_p);
                }
                else
                    this->genTar("movz", reg_no, regB, CodeGenerator::ARG_REG, CodeGenerator::ARG_REG);
            }
            //OP R, C
            if(regC == -1)
            {
                //参数不在参数寄存器也不在普通寄存器，则为其分配一个
                if(now.arg2 > this->funcParamNum[codeBlock.tablePoin])
                {
                    //更新A、B和C状态
                    if(regA != -1)
                        this->updateReg(codeBlock, regA, now.result, now.result_p);
                    if(regB != -1)
                        this->updateReg(codeBlock, regB, now.arg1, now.arg1_p);
                    if(regC != -1)
                        this->updateReg(codeBlock, regC, now.arg2, now.arg2_p);
                    this->updateRegA(codeBlock, reg_no, now.result, now.result_p);
                    //分配寄存器存arg2
                    regC = this->getReg(codeBlock, now.arg2, now.arg2, now.arg2, now.arg2_p, now.arg2_p, now.arg2_p, i-codeBlock.start);
                    this->updateRegA(codeBlock, regC, now.arg2, now.arg2_p);
                    if(now.arg2_p == CodeGenerator::ARG_LOCALVAR)
                    {
                        auto& item = symbol_table.table_list[codeBlock.tablePoin][now.arg2];
                        if(item.is_inst)    //常量使用addi
                            this->genTar("addi", regC, now.arg2, CodeGenerator::ARG_REG, now.arg2_p);
                        else    //变量使用lw
                            this->genTar("lw", regC, now.arg2, CodeGenerator::ARG_REG, now.arg2_p);
                    }
                    else    //全局变量必为变量，使用lw
                        this->genTar("lw", regC, now.arg2, CodeGenerator::ARG_REG, now.arg2_p);
                    this->genTar(now.op, reg_no, regC, CodeGenerator::ARG_REG, CodeGenerator::ARG_REG);
                    //数组立刻存回内存
                    if(symbol_table.table_list[codeBlock.tablePoin][now.result].newtype == "arr")
                        this->genTar("sw", reg_no, now.result, CodeGenerator::ARG_REG, now.result_p);
                }
                else    //参数在参数寄存器
                {
                    this->genTar(now.op, reg_no, now.arg2, CodeGenerator::ARG_REG, now.arg2_p);
                    //数组立刻存回内存
                    if(symbol_table.table_list[codeBlock.tablePoin][now.result].newtype == "arr")
                        this->genTar("sw", reg_no, now.result, CodeGenerator::ARG_REG, now.result_p);
                }
            }
            else    //参数在普通寄存器中
            {
                this->genTar(now.op, reg_no, regC, CodeGenerator::ARG_REG, CodeGenerator::ARG_REG);
                //数组立刻存回内存
                if(symbol_table.table_list[codeBlock.tablePoin][now.result].newtype == "arr")
                    this->genTar("sw", reg_no, now.result, CodeGenerator::ARG_REG, now.result_p);
            }
            //更新A、B和C状态
            if(regA != -1)
                this->updateReg(codeBlock, regA, now.result, now.result_p);
            if(regB != -1)
                this->updateReg(codeBlock, regB, now.arg1, now.arg1_p);
            if(regC != -1)
                this->updateReg(codeBlock, regC, now.arg2, now.arg2_p);
            //更新A的AVALUE和RVALUE
            this->updateRegA(codeBlock, reg_no, now.result, now.result_p);
            this->genStore(codeBlock, now.result, now.arg1, now.arg2, now.result_p, now.arg1_p, now.arg2_p);
            continue;
        }
        //赋值指令
        if(now.op == "=")
        {
            int regB = this->getRegNo(codeBlock, now.arg1, now.arg1_p);
            int regA = this->getRegNo(codeBlock, now.result, now.result_p);
            if(regA == -1)
            {
                int reg_no = this->getReg(codeBlock, now.result, now.arg1, now.arg2, now.result_p, now.arg1_p, now.arg2_p, i-codeBlock.start);
                if(reg_no == -1)
                    return State::ERROR;
                if(regB == -1)
                {
                    if(now.arg1_p == CodeGenerator::ARG_LOCALVAR)
                    {
                        auto& item = symbol_table.table_list[codeBlock.tablePoin][now.arg1];
                        //常量
                        if(item.is_inst)
                        {
                            this->genTar("addi", reg_no, now.arg1, CodeGenerator::ARG_REG, now.arg1_p);
                            //数组立刻存回内存
                            if(symbol_table.table_list[codeBlock.tablePoin][now.result].newtype == "arr")
                                this->genTar("sw", reg_no, now.result, CodeGenerator::ARG_REG, now.result_p);
                        }
                        else
                        {
                            //变量在参数中
                            if(now.arg1 <= this->funcParamNum[codeBlock.tablePoin])
                            {
                                this->genTar("movz", reg_no, now.arg1, CodeGenerator::ARG_REG, now.arg1_p);
                                //数组立刻存回内存
                                if(symbol_table.table_list[codeBlock.tablePoin][now.result].newtype == "arr")
                                    this->genTar("sw", reg_no, now.result, CodeGenerator::ARG_REG, now.result_p);
                            }
                            else    //变量在内存
                            {
                                this->genTar("lw", reg_no, now.arg1, CodeGenerator::ARG_REG, now.arg1_p);
                                //数组立刻存回内存
                                if(symbol_table.table_list[codeBlock.tablePoin][now.result].newtype == "arr")
                                    this->genTar("sw", reg_no, now.result, CodeGenerator::ARG_REG, now.result_p);
                            }
                        }
                    }
                    else    //全局
                    {
                        this->genTar("lw", reg_no, now.arg1, CodeGenerator::ARG_REG, now.arg1_p);
                        //数组立刻存回内存
                        if(symbol_table.table_list[codeBlock.tablePoin][now.result].newtype == "arr")
                            this->genTar("sw", reg_no, now.result, CodeGenerator::ARG_REG, now.result_p);
                    }
                }
                else if(regB != reg_no)
                {
                    this->genTar("movz", reg_no, regB, CodeGenerator::ARG_REG, CodeGenerator::ARG_REG);
                    //数组立刻存回内存
                    if(symbol_table.table_list[codeBlock.tablePoin][now.result].newtype == "arr")
                        this->genTar("sw", reg_no, now.result, CodeGenerator::ARG_REG, now.result_p);
                }
                else    //目标和第一参数在一个寄存器中
                {
                    //数组立刻存回内存
                    if(symbol_table.table_list[codeBlock.tablePoin][now.result].newtype == "arr")
                        this->genTar("sw", reg_no, now.result, CodeGenerator::ARG_REG, now.result_p);
                }
                //更新寄存器
                if(regA != -1)
                    this->updateReg(codeBlock, regA, now.result, now.result_p);
                if(regB != -1)
                    this->updateReg(codeBlock, regB, now.arg1, now.arg1_p);
                this->updateRegA(codeBlock, reg_no, now.result, now.result_p);
            }
            else
            {
                if(regB == -1)
                {
                    if(now.arg1_p == CodeGenerator::ARG_LOCALVAR)
                    {
                        auto& item = symbol_table.table_list[codeBlock.tablePoin][now.arg1];
                        //常量
                        if(item.is_inst)
                        {
                            this->genTar("addi", regA, now.arg1, CodeGenerator::ARG_REG, now.arg1_p);
                            //数组立刻存回内存
                            if(symbol_table.table_list[codeBlock.tablePoin][now.result].newtype == "arr")
                                this->genTar("sw", regA, now.result, CodeGenerator::ARG_REG, now.result_p);
                        }
                        else
                        {
                            //变量在参数中
                            if(now.arg1 <= this->funcParamNum[codeBlock.tablePoin])
                            {
                                this->genTar("movz", regA, now.arg1, CodeGenerator::ARG_REG, now.arg1_p);
                                //数组立刻存回内存
                                if(symbol_table.table_list[codeBlock.tablePoin][now.result].newtype == "arr")
                                    this->genTar("sw", regA, now.result, CodeGenerator::ARG_REG, now.result_p);
                            }
                            else    //变量在内存
                            {
                                this->genTar("lw", regA, now.arg1, CodeGenerator::ARG_REG, now.arg1_p);
                                //数组立刻存回内存
                                if(symbol_table.table_list[codeBlock.tablePoin][now.result].newtype == "arr")
                                    this->genTar("sw", regA, now.result, CodeGenerator::ARG_REG, now.result_p);
                            }
                        }
                    }
                    else
                    {
                        this->genTar("lw", regA, now.arg1, CodeGenerator::ARG_REG, now.arg1_p);
                        //数组立刻存回内存
                        if(symbol_table.table_list[codeBlock.tablePoin][now.result].newtype == "arr")
                            this->genTar("sw", regA, now.result, CodeGenerator::ARG_REG, now.result_p);
                    }
                }
                else
                {
                    this->genTar("movz", regA, regB, CodeGenerator::ARG_REG, CodeGenerator::ARG_REG);
                    //数组立刻存回内存
                    if(symbol_table.table_list[codeBlock.tablePoin][now.result].newtype == "arr")
                        this->genTar("sw", regA, now.result, CodeGenerator::ARG_REG, now.result_p);
                }
                //更新寄存器
                if(regA != -1)
                    this->updateReg(codeBlock, regA, now.result, now.result_p);
                if(regB != -1)
                    this->updateReg(codeBlock, regB, now.arg1, now.arg1_p);
            }
            this->genStore(codeBlock, now.result, now.arg1, now.arg2, now.result_p, now.arg1_p, now.arg2_p);
            continue;
        }
        //跳转指令
        if(now.op[0] == 'j')
        {
            this->genStore(codeBlock, now.result, now.arg1, now.arg2, now.result_p, now.arg1_p, now.arg2_p);
            int regB, regC;
            regB = this->getRegNo(codeBlock, now.arg1, now.arg1_p);
            regC = this->getRegNo(codeBlock, now.arg2, now.arg2_p);
            //J dst
            if(now.op.length() == 1)
                this->genTar("j", now.arg1, this->jmpToNo[now.result], now.arg1_p, now.result_p);
            else if(now.op == "jnz")   //Jopt A B dst
            {
                //获取变量值到寄存器中
                State stat;
                if(regB == -1 && now.arg1 != DEFAULT_LOC)
                {
                    stat = this->getVarForBnez(regB, now.arg1, now.arg1_p, codeBlock, now, i);
                    if(stat == State::OK)
                        this->genTar("bnez", regB, this->jmpToNo[now.result], CodeGenerator::ARG_REG, now.result_p);
                    else    //值已存在寄存器中
                        this->genTar("bnez", now.arg1, this->jmpToNo[now.result], now.arg1_p, now.result_p);
                }
                else
                    this->genTar("bnez", regB, this->jmpToNo[now.result], CodeGenerator::ARG_REG, now.result_p);
            }
            else    //其他跳转语句
            {
                State stat1, stat2;
                //获取变量值到寄存器中
                if(regB == -1 && now.arg1 != DEFAULT_LOC)
                {
                    if(regC == -1 && now.arg2 != DEFAULT_LOC)   //获取两个值
                    {
                        stat1 = this->getVarForJ(regB, now.arg1, now.arg1_p, codeBlock, now, i);
                        stat2 = this->getVarForJ(regC, now.arg2, now.arg2_p, codeBlock, now, i);
                        if(stat1 == State::OK && stat2 == State::OK)
                            this->genTar(now.op, regB, regC, CodeGenerator::ARG_REG, CodeGenerator::ARG_REG, this->jmpToNo[now.result], now.result_p);
                        else if(stat1 != State::OK && stat2 == State::OK)
                            this->genTar(now.op, now.arg1, regC, now.arg1_p, CodeGenerator::ARG_REG, this->jmpToNo[now.result], now.result_p);
                        else if(stat1 == State::OK && stat2 != State::OK)
                            this->genTar(now.op, regB, now.arg2, CodeGenerator::ARG_REG, now.arg2_p, this->jmpToNo[now.result], now.result_p);
                        else
                            this->genTar(now.op, now.arg1, now.arg2, now.arg1_p, now.arg2_p, this->jmpToNo[now.result], now.result_p);
                        continue;
                    }
                    else    //获取一个值
                    {
                        stat1 = this->getVarForJ(regB, now.arg1, now.arg1_p, codeBlock, now, i);
                        if(stat1 == State::OK)
                            this->genTar(now.op, regB, regC, CodeGenerator::ARG_REG, CodeGenerator::ARG_REG, this->jmpToNo[now.result], now.result_p);
                        else
                            this->genTar(now.op, now.arg1, regC, now.arg1_p, CodeGenerator::ARG_REG, this->jmpToNo[now.result], now.result_p);
                        continue;
                    }
                }
                else if(regC == -1 && now.arg2 != DEFAULT_LOC)  //获取一个值
                {
                    stat2 = this->getVarForJ(regC, now.arg2, now.arg2_p, codeBlock, now, i);
                    if(stat2 == State::OK)
                        this->genTar(now.op, regB, regC, CodeGenerator::ARG_REG, CodeGenerator::ARG_REG, this->jmpToNo[now.result], now.result_p);
                    else
                        this->genTar(now.op, regB, now.arg2, CodeGenerator::ARG_REG, now.arg2_p, this->jmpToNo[now.result], now.result_p);
                    continue;
                }
                //均在寄存器中
                this->genTar(now.op, regB, regC, CodeGenerator::ARG_REG, CodeGenerator::ARG_REG, this->jmpToNo[now.result], now.result_p);
            }

            continue;
        }
        //return
        if(now.op == "return")
        {
            int regA = this->getRegNo(codeBlock, now.result, now.result_p);
            //main函数则返回值存回内存
            if(codeBlock.tablePoin == symbol_table.funcname2index["main"])
                this->genStore(codeBlock, now.result, now.arg1, now.arg2, now.result_p, now.arg1_p, now.arg2_p);
            if(regA != -1)
                this->genTar("movz", 0, regA, CodeGenerator::ARG_RReg, CodeGenerator::ARG_REG);
            else
                this->genTar("lw", 0, now.result, CodeGenerator::ARG_RReg, now.result_p);
            if(codeBlock.tablePoin != symbol_table.funcname2index["main"])
                this->genTar("jr", now.arg1, now.result, now.arg1_p, CodeGenerator::ARG_RAReg);

            continue;
        }
        //param
        if(now.op == "param")
        {
            int regB = this->getRegNo(codeBlock, now.arg1, now.arg1_p);
            if (now.arg1_p == CodeGenerator::ARG_LOCALVAR)
            {
                auto& item = symbol_table.table_list[codeBlock.tablePoin][now.arg1];
                this->valueToReg[item.value] = this->valueToReg.size();
                if(regB != -1)
                {
                    auto& item = symbol_table.table_list[codeBlock.tablePoin][now.arg1];
                    //常量
                    if(item.is_inst)
                        this->genTar("addi", this->valueToReg.size()-1, now.arg1, CodeGenerator::ARG_PREG, now.arg1_p);
                    else
                        this->genTar("movz", this->valueToReg.size()-1, regB, CodeGenerator::ARG_PREG, CodeGenerator::ARG_REG);
                }
                else
                    this->genTar("lw", this->valueToReg.size()-1, now.arg1, CodeGenerator::ARG_PREG, now.arg1_p);
            }
            else if (now.arg1_p == CodeGenerator::ARG_GLOBALVAR)
            {
                auto& item = symbol_table.table_list.front()[now.arg1];
                this->valueToReg[item.value] = this->valueToReg.size();
                if(regB != -1)
                    this->genTar("movz", this->valueToReg.size()-1, regB, CodeGenerator::ARG_PREG, CodeGenerator::ARG_REG);
                else
                     this->genTar("lw", this->valueToReg.size()-1, now.arg1, CodeGenerator::ARG_PREG, now.arg1_p);
            }

//            this->genStore(codeBlock, now.result, now.arg1, now.arg2, now.result_p, now.arg1_p, now.arg2_p);
            continue;
        }
        //函数调用
        if(now.op == "call")
        {
            int regA = this->getRegNo(codeBlock, now.result, now.result_p);
            this->genTar("jal", now.arg1, -1, now.arg1_p, -1);
            int reg_no;
            if(regA == -1)
                reg_no = this->getReg(codeBlock, now.result, now.result, now.arg2, now.result_p, now.result_p, now.arg2_p, i-codeBlock.start);
            else
                reg_no = regA;
            this->genTar("movz", reg_no, 0, CodeGenerator::ARG_REG, CodeGenerator::ARG_RReg);
            this->genStore(codeBlock, now.result, now.arg1, now.arg2, now.result_p, now.arg1_p, now.arg2_p);
            this->updateRegA(codeBlock, reg_no, now.result, now.result_p);
            this->valueToReg.clear();
            continue;
        }
        //其他
        this->genTar(now.op, now.arg1, now.result, now.arg1_p, now.result_p);
        this->genStore(codeBlock, now.result, now.arg1, now.arg2, now.result_p, now.arg1_p, now.arg2_p);
    }

    return State::OK;
}

State CodeGenerator::genTarCode()
{
    this->preOperate();
    if(this->codeblocks.size() == 0)
        return State::ERROR;
    for(int i = 0; i < (int)(this->codeblocks.size()); i++)
    {
        this->genTarCodeBlock(this->codeblocks[i]);
    }
    return State::OK;
}

State CodeGenerator::genTarCode2()
{
    this->preOperate();
    if(this->codeblocks.size() == 0)
        return State::ERROR;
    for(int i = 0; i < (int)(this->codeblocks.size()); i++)
    {
        this->genTarCodeBlock2(this->codeblocks[i]);
    }
    return State::OK;
}
