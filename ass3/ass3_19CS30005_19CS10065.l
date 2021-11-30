/*C includes and definitions*/
%{
	#define KEYWORD 301
	#define IDENTIFIER 302
	#define PUNCTUATOR 303
	#define WHITE_SPACE 304
	#define STRING_LITERAL 305

	#define INTEGER_CONSTANT 306
	#define FLOAT_CONSTANT 307
	#define CHAR_CONSTANT 308

	#define SINGLE_LINE_COMMENT_START 309
	#define SINGLE_LINE_COMMENT_BETWEEN 310
	#define SINGLE_LINE_COMMENT_END 311

	#define MULTI_LINE_COMMENT_START 312
	#define MULTI_LINE_COMMENT_BETWEEN 313
	#define MULTI_LINE_COMMENT_END 314
%}

/* regex */

%x SINGLE_LINE_COMMENT
%x MULTI_LINE_COMMENT

PUNCTUATOR "["|"]"|"("|")"|"{"|"}"|"."|"->"|"++"|"--"|"&"|"*"|"+"|"-"|"~"|"!"|"/"|"%"|"<<"|">>"|"<"|">"|"<="|">="|"=="|"!="|"^"|"|"|"&&"|"||"|"?"|":"|";"|"..."|"="|"*="|"/="|"%="|"+="|"-="|"<<="|">>="|"&="|"^="|"|="|","|"#"

ESCAPE_SEQUENCE "\\\'"|"\\\""|"\?"|"\\"|"\a"|"\b"|"\f"|"\n"|"\r"|"\t"|"\v"

KEYWORD "auto"|"enum"|"restrict"|"unsigned"|"break"|"extern"|"return"|"void"|"case"|"float"|"short"|"volatile"|"char"|"for"|"signed"|"while"|"const"|"goto"|"sizeof"|"_Bool"|"continue"|"if"|"static"|"_Complex"|"default"|"inline"|"struct"|"_Imaginary"|"do"|"int"|"switch"|"double"|"long"|"typedef"|"else"|"register"|"union"

IDENTIFIER [a-zA-Z_][a-zA-Z0-9_]*

DIGIT [0-9]
DIGIT_SEQUENCE [0-9]+
INTEGER_CONSTANT [1-9][0-9]*|[0]+
SIGN "+"|"-"
EXPONENT_PART ([Ee]([+-]?))({DIGIT_SEQUENCE})
FRACTIONAL_CONSTANT ({DIGIT_SEQUENCE}\.)|({DIGIT_SEQUENCE}?\.{DIGIT_SEQUENCE})
FLOAT_CONSTANT ({DIGIT_SEQUENCE}{EXPONENT_PART})|({FRACTIONAL_CONSTANT}{EXPONENT_PART}?)

S_CHAR [^\"\n\\]|{ESCAPE_SEQUENCE}
S_CHAR_SEQUENCE {S_CHAR}+
STRING_LITERAL \"({S_CHAR_SEQUENCE})?\"

C_CHAR [^\'\n\\]|{ESCAPE_SEQUENCE}
C_CHAR_SEQUENCE ({C_CHAR})+
CHAR_CONSTANT \'({C_CHAR_SEQUENCE})\'

ENUMERATION_CONSTANT {IDENTIFIER}
CONST {INTEGER_CONSTANT}|{CHAR_CONSTANT}|{FLOAT_CONSTANT}|{ENUMERATION_CONSTANT}

%%

"//" {BEGIN(SINGLE_LINE_COMMENT); return SINGLE_LINE_COMMENT_START;}
<SINGLE_LINE_COMMENT>"\n" {BEGIN(INITIAL); return SINGLE_LINE_COMMENT_END;}
<SINGLE_LINE_COMMENT>. {return SINGLE_LINE_COMMENT_BETWEEN;}

"/*" {BEGIN(MULTI_LINE_COMMENT); return MULTI_LINE_COMMENT_START;}
<MULTI_LINE_COMMENT>"*/" {BEGIN(INITIAL); return MULTI_LINE_COMMENT_END;}
<MULTI_LINE_COMMENT>. {return MULTI_LINE_COMMENT_BETWEEN;}
<MULTI_LINE_COMMENT>"\n" {return MULTI_LINE_COMMENT_BETWEEN;}

{KEYWORD} {return KEYWORD;}
{IDENTIFIER} {return IDENTIFIER;}
{PUNCTUATOR} {return PUNCTUATOR;}
{STRING_LITERAL} {return STRING_LITERAL;}
{INTEGER_CONSTANT} {return INTEGER_CONSTANT;}
{FLOAT_CONSTANT} {return FLOAT_CONSTANT;}
{CHAR_CONSTANT} {return CHAR_CONSTANT;}
{ESCAPE_SEQUENCE}|" " {}

%%