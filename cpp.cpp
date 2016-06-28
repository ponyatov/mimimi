#include "hpp.hpp"
#define YYERR "\n\n"<<yylineno<<":"<<msg<<"["<<yytext<<"]\n\n"
void yyerror(string msg) { cout<<YYERR; cerr<<YYERR; exit(-1); }
int main() { return yyparse(); }

Sym::Sym(string V) { val=V; }
void Sym::push(Sym*o) { nest.push_back(o); }

string Sym::head() { return "<"+val+">"; }
string Sym::pad(int n) { string S; for (int i=0;i<n;i++) S+='\t'; return S; }
string Sym::dump(int depth) { string S = "\n"+pad(depth)+head();
	for (auto it=nest.begin(),e=nest.end();it!=e;it++)
		S += (*it)->dump(depth+1);
	return S; }

Sym* Sym::eval() {
	for (auto it=nest.begin(),e=nest.end();it!=e;it++)
		(*it) = (*it)->eval();
	return this; }

Sym* Sym::div(Sym*o) {
	if (val==".") return new Sym(val+"/"+o->val);
	return new Error(val+"/"+o->val);
}

Error::Error(string V):Sym(V) { yyerror(V); }

Vector::Vector():Sym("[]"){}
string Vector::head() { return val; }

Op::Op(string V):Sym(V){}
string Op::head() { return val; }
Sym* Op::eval() {
	if (val=="~") return nest[0]; else Sym::eval();
	if (val=="/") return nest[0]->div(nest[1]);
	return this;
}

Dep::Dep(Sym*A,Sym*B,Sym*C):Sym("dep") { push(A); push(B); push(C); }
string Dep::head() { return ":"; }
