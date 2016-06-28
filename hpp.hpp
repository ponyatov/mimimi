#ifndef _H_HPP
#define _H_HPP

#include <iostream>
//#include <sstream>
#include <cstdlib>
#include <vector>
#include <map>
using namespace std;

struct Sym {
	string val;
	Sym(string);
	vector<Sym*> nest; void push(Sym*);
	virtual string dump(int=0); virtual string head(); string pad(int);
	virtual Sym* eval();
	virtual Sym* div(Sym*);
};

struct Error: Sym { Error(string); };

struct Vector: Sym { Vector(); string head(); };

struct Op: Sym { Op(string); string head(); Sym*eval(); };

struct Dep: Sym { Dep(Sym*,Sym*,Sym*); string head(); };

extern int yylex();
extern int yylineno;
extern char* yytext;
#define TOC(C,X) { yylval.o = new C(yytext); return X; }
extern int yyparse();
extern void yyerror(string);
#include "ypp.tab.hpp"

#endif // _H_HPP
