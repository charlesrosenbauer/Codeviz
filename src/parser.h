#ifndef __PARSER_HEADER__
#define __PARSER_HEADER__


#include "stdint.h"


typedef enum{
	TK_WORD, TK_KWRD, TK_LCOM, TK_MCOM, TK_INT, TK_FLT, TK_QSTR, TK_ASTR, TK_SPACE
}TokenType;


typedef struct{
	char*      text;
	int        size;
	TokenType  type;
}Token;


typedef struct{
	char*      text;
	int        size, head;
	Token*     tokens;
	int        tkct, tkmax;
}ParserState;







#endif
