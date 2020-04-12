#include "parser.h"




int prefixMatch(char* x, char* y, int sz){
	for(int i = 0; i < sz; i++){
		if(x[i] != y[i]) return 0;
	}
	return 1;
}


void skipUntil(ParserState* ps, char c){
	int cont = 1;
	while(cont){
		if(ps->text[ps->head] != c){
			ps->head++;
		}else{
			cont = 0;
		}
		if(ps->head == ps->size) cont = 0;
	}
}


int parseComment(ParserState* ps){
	int headstart = ps->head;
	if      (prefixMatch(&ps->text[ps->head], "//", 2)){
		// Parse line comment
		skipUntil(ps, '\n');
		ps->tokens[ps->tkct].text = &ps->text[headstart];
		ps->tokens[ps->tkct].size = headstart - ps->head;
		ps->tokens[ps->tkct].type = TK_LCOM;
		// TODO: Add checks for array overflow
		ps->tkct++;
		return 1;
	}else if(prefixMatch(&ps->text[ps->head], "/*", 2)){
		// Parse multiline comment
		int cont = 1;
		while(cont){
			skipUntil(ps, '*');
			if      (ps->head >= ps->size){
				cont = 0;
			}else if(ps->text[ps->head+1] == '/'){
				cont = 0;
				ps->head++;
			}
		}
		ps->tokens[ps->tkct].text = &ps->text[headstart];
		ps->tokens[ps->tkct].size = headstart - ps->head;
		ps->tokens[ps->tkct].type = TK_MCOM;
		// TODO: Add checks for array overflow
		ps->tkct++;
		return 1;
	}
	return 0;
}


void skipWhitespace(ParserState* ps){
	int cont = 1;
	while(cont){
		if(ps->head >= ps->size){
			cont = 0;
		}else if((ps->text[ps->head] == ' ' ) ||
				 (ps->text[ps->head] == '\n') ||
				 (ps->text[ps->head] == '\t')){
			ps->head++;
		}else{
			cont = 0;
		} 
	}
	// insert whitespace token
}

/*
int parseWord(ParserState* ps){
	int cont = 1;
	while(cont){
		char c = ps->text[ps->head];
		if(((c >= 'a') && (c <= 'z')) ||
		   ((c >= 'A') && (c <= 'Z')) ||
		   ((c >= '0') && (c <= '9')) ||
		    (c == '_')){
			cont = 0;
		}
	}

}


int parse(char* text, int size, ParserState* ps){

}*/







