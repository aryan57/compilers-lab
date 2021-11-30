/*
*   Group - 9
*   Assignment-3, Compilers Lab
*   Aryan Agarwal, 19CS30005
*   Vinit Raj, 19CS10065
*/

#include <stdio.h>

int main()
{
	int token;
	while (token = yylex())
	{
		switch (token)
		{
		case KEYWORD:
			printf("<KEYWORD, %d, %s>\n", token, yytext);
			break;
		case IDENTIFIER:
			printf("<IDENTIFIER, %d, %s>\n", token, yytext);
			break;
		case PUNCTUATOR:
			printf("<PUNCTUATOR, %d, %s>\n", token, yytext);
			break;
		case STRING_LITERAL:
			printf("<STRING_LITERAL, %d, %s>\n", token, yytext);
			break;
		case INTEGER_CONSTANT:
			printf("<INTEGER_CONSTANT, %d, %s>\n", token, yytext);
			break;
		case FLOAT_CONSTANT:
			printf("<FLOAT_CONSTANT, %d, %s>\n", token, yytext);
			break;
		case CHAR_CONSTANT:
			printf("<CHARACTER_CONSTANT, %d, %s>\n", token, yytext);
			break;
		case MULTI_LINE_COMMENT_START:
			printf("<MULTI_LINE_COMMENT_START, %d, %s>\n", token, yytext);
			break;
		case MULTI_LINE_COMMENT_END:
			printf("<MULTI_LINE_COMMENT_END, %d, %s>\n", token, yytext);
			break;
		case MULTI_LINE_COMMENT_BETWEEN:
			printf("%s", yytext);
			break;
		case SINGLE_LINE_COMMENT_START:
			printf("<SINGLE_LINE_COMMENT_START, %d, %s>\n", token, yytext);
			break;
		case SINGLE_LINE_COMMENT_END:
			printf("<SINGLE_LINE_COMMENT_END, %d, %s>\n", token, yytext);
			break;
		case SINGLE_LINE_COMMENT_BETWEEN:
			printf("%s", yytext);
			break;
		default:
			break;
		}
	}
	return 0;
}
