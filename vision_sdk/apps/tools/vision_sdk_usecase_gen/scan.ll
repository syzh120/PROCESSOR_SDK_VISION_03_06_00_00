%option noyywrap

%{

#include <cstdlib>
#include <sstream>
#include <cstring>
#include "vsdk-ctx.h"
#include "link.h"
#include "parse.tab.hh"
#include "options.h"
#include "error.h"

using namespace std;

void store_Token_Name(const char * tok_name);
void ignore_Token();
static char * token_name;

//int yylineno=1;

static bool show_tokens = false;
static ostream * tokens_fp = NULL;

#define YY_DECL int lexscan(yy::vsdk::semantic_type *yylval, \
    yy::vsdk::location_type *yylloc, vsdk_ctx &ctx)

# define YY_USER_ACTION  yylloc->columns (yyleng);

typedef yy::vsdk::token token;

%}

digit   [0-9]
letter  [a-z_A-Z_] 
dot     [.]
exp     [eE]
id      ({letter}|{digit})({letter}|{digit})*
%%

%{
     // start where previous token ended
     yylloc->step();
%}

[<>:{}();,-]    {
	                 store_Token_Name ("META CHAR");
	                 return yytext[0]; 
             	}
"[" 			{
	                 store_Token_Name ("META CHAR");
	                 return yytext[0]; 
             	}

"]"				{
	                 store_Token_Name ("META CHAR");
	                 return yytext[0]; 
             	}
[-/+*=]   		{
					store_Token_Name ("OPERATOR");
					return yytext[0];
		  		}


int	            {    
	                 store_Token_Name("INT");
	                 return token::INT; 
	            }

UseCase			{    
	                 store_Token_Name("USECASE");
	                 return token::USECASE; 
	            }
            
{id}  			{
	                 store_Token_Name("ID");
	                 yylval->sval = new std::string (yytext);
	                 return token::ID; 
	            }
\n           	{ 
	                 yylloc->lines(1); 
	                 yylineno++;
	                 ignore_Token();
             	}    

  /* skip over comments and white space */
";;".*  		|
[ \t]*"//".*	|
[ \t]			|
"/*"[^"*/"]*"*/"  	{  yylloc->step (); 
			           ignore_Token();
			        }	

.       { 
            stringstream ss;
            ss <<  "Illegal character `" << yytext << "' on line " << yylineno;
        }
%%

void init_Scanner ()
{
   show_tokens = cmd_options.show_Tokens();
   if (show_tokens)
        tokens_fp = cmd_options.tokens_File();
}

void store_Token_Name(const char * tok_name)
{     
    if (token_name) 
    	delete token_name;
    token_name = strdup (tok_name);
}

int yylex(yy::vsdk::semantic_type *yylval, 
    yy::vsdk::location_type *yylloc, vsdk_ctx &ctx)
{    
	 int token_code;

     token_code = lexscan(yylval, yylloc, ctx);

     if (show_tokens)
     {
          if (token_code)
          {
               string mesg = " Token name has not been set for the lexeme `" + string(yytext) +"'";
               CHECK_ERROR(token_name, mesg);
               *tokens_fp << "Line: " << yylineno << " Token name:" << token_name << "\ttoken code:" << token_code << "\tlexeme: `" << yytext << "'\n";
               delete token_name;
               token_name = NULL;
          }
    }
    return token_code;
}

void ignore_Token()
{
    if (show_tokens)
    {
       if (yytext[0] == '\n')
           *tokens_fp << "Line: "<< yylineno << " Ignored NEWLINE character\n";
       else
           *tokens_fp << "Line: "<< yylineno << " Ignored lexeme: '" << yytext << "'\n";
    }
}
