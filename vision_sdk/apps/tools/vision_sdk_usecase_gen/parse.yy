%skeleton "lalr1.cc"
%language "C++"
%defines
%locations

%define parser_class_name "vsdk"
 
%{
	
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "vsdk-ctx.h"
#include "link.h"
#include "usecase.h"

using namespace std;

class Link;
extern Usecase mainObj;

%}

%parse-param { vsdk_ctx &ctx }
%lex-param   { vsdk_ctx &ctx }

%union 
{
    int ival;
    std::string *sval;
    vector<Link*> *lnk;
};

/* declare tokens */
%token <ival> I_NUM
%token <sval> ID
%token INT USECASE

%left '*' '/'
%left '+' '-'

%type <lnk> Connection

%{
	/* Grammar 
	 * start:
			List_Declarations
		;

		List_Declarations :
			Declaration
		|
			Declaration List_Declarations
		;

		Declaration :
			UseCaseName
		|
			Connection
		;

		UseCaseName :
			UseCase ':' ID
		;

		Connection : 
			ID
		|
			ID '-''>' Connection
		;
		 */
			
  extern int yylex(yy::vsdk::semantic_type *yylval,
       yy::vsdk::location_type* yylloc,
       vsdk_ctx &ctx);

  extern int yylineno;
%}

%initial-action {
 // Filename for locations here
 @$.begin.filename = @$.end.filename = new std::string("stdin");
}
%%

start:
	List_Declarations
;

List_Declarations :
	Declaration
|
	Declaration List_Declarations
;

Declaration :
	UseCaseName
|
	Connection
	{
		mainObj.setNewConn($1);
	}
;

UseCaseName :
	USECASE ':' ID
	{
		mainObj.setFileName(*$3);
	}
;

Connection : 
		ID
		{
			$$ = new vector<Link*>;
			Link* obj = mainObj.createObject(*$1);
			$$->push_back(obj);
		}
|
		ID '(' ID ')'
		{
			$$ = new vector<Link*>;
			Link* obj = mainObj.createObject(*$1);
			obj->setProcType(*$3);
			$$->push_back(obj);
		}
|

		ID '-''>' Connection
		{
			Link* obj = mainObj.createObject(*$1);
			$4->push_back(obj);
			$$ = $4;
		}
|
		ID '(' ID ')' '-''>' Connection
		{
			Link* obj = mainObj.createObject(*$1);
			obj->setProcType(*$3);
			$7->push_back(obj);
			$$ = $7;
		}
;
