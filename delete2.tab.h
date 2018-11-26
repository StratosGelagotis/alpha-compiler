/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_DELETE2_TAB_H_INCLUDED
# define YY_YY_DELETE2_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IF = 258,
    INTEGER = 259,
    ELSE = 260,
    WHILE = 261,
    REAL = 262,
    STRING = 263,
    FOR = 264,
    FUNCTION = 265,
    RETURN = 266,
    BREAK = 267,
    CONTINUE = 268,
    AND = 269,
    NOT = 270,
    OR = 271,
    LOCAL = 272,
    TRUE = 273,
    FALSE = 274,
    NIL = 275,
    COMMA = 276,
    COLON = 277,
    DOUBLE_POINT = 278,
    DOUBLE_ANWKATW = 279,
    ID = 280,
    LEFT_BRACKET = 281,
    RIGHT_BRACKET = 282,
    RIGHT_SQUERE_BRACKET = 283,
    LEFT_SQUERE_BRACKET = 284,
    SEMICOLON = 285,
    ASGN = 286,
    EQUAL = 287,
    NEQUAL = 288,
    GT = 289,
    GE = 290,
    LT = 291,
    LE = 292,
    PLUS = 293,
    MINUS = 294,
    MUL = 295,
    DIV = 296,
    MODULO = 297,
    PLUSPLUS = 298,
    MINUSMINUS = 299,
    UMINUS = 300,
    POINT = 301,
    LEFT_PARENTHESIS = 302,
    RIGHT_PARENTHESIS = 303
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 31 "delete2.y" /* yacc.c:1909  */

struct  forStruct * forprefix2;
//struct breakStruct * breakstmt;
//struct continueStruct *	continuestmt;
struct stmtStruct  *Stmt2;
string* stringValue;
int intValue;
double realValue;
struct expr* exprNode;
struct callsuffix* callsuf;
struct SymbolTableEntry* SymbolTableEntry;

#line 116 "delete2.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_DELETE2_TAB_H_INCLUDED  */
