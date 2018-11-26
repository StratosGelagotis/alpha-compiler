/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "delete2.y" /* yacc.c:339  */

//#include "header.hpp"
#include "phase4.hpp"
extern	unsigned programVarOffset  ;
extern unsigned functionLocalOffset ;
extern unsigned formalArgOffset  ;
extern void generate_UMINUS(quad* q);

extern list<expr*> exprList;
extern list<pair*> pairList;
extern stack<int> functionLocalStack;

extern unsigned scopeSpaceCounter ;

extern stack<int> OffsetStack;

extern int yylineno;
extern FILE* yyin;
int yylex();
int yyerror(string yaccProvidedMessage);
int yyinput();
extern char* yytext;
int scope=0;
int scope2=scope;
bool bes;
int loopcounter;

#line 94 "delete2.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "delete2.tab.h".  */
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
#line 31 "delete2.y" /* yacc.c:355  */

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

#line 196 "delete2.tab.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_DELETE2_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 211 "delete2.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   457

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  51
/* YYNRULES -- Number of rules.  */
#define YYNRULES  109
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  194

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   303

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   128,   128,   128,   165,   168,   171,   175,   177,   180,
     183,   187,   197,   208,   209,   210,   213,   217,   224,   231,
     238,   245,   252,   262,   272,   282,   292,   302,   312,   319,
     326,   331,   336,   343,   350,   366,   385,   401,   419,   422,
     450,   453,   456,   459,   464,   469,   510,   567,   579,   584,
     587,   593,   596,   604,   607,   615,   622,   625,   630,   638,
     646,   650,   650,   657,   661,   664,   677,   691,   691,   698,
     699,   702,   710,   710,   745,   754,   786,   792,   796,   805,
     810,   823,   824,   836,   839,   843,   849,   855,   862,   862,
     903,   906,   906,   944,   947,   956,   961,   966,   999,  1002,
    1006,  1010,  1014,  1020,  1035,  1041,  1046,  1055,  1071,  1076
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IF", "INTEGER", "ELSE", "WHILE", "REAL",
  "STRING", "FOR", "FUNCTION", "RETURN", "BREAK", "CONTINUE", "AND", "NOT",
  "OR", "LOCAL", "TRUE", "FALSE", "NIL", "COMMA", "COLON", "DOUBLE_POINT",
  "DOUBLE_ANWKATW", "ID", "LEFT_BRACKET", "RIGHT_BRACKET",
  "RIGHT_SQUERE_BRACKET", "LEFT_SQUERE_BRACKET", "SEMICOLON", "ASGN",
  "EQUAL", "NEQUAL", "GT", "GE", "LT", "LE", "PLUS", "MINUS", "MUL", "DIV",
  "MODULO", "PLUSPLUS", "MINUSMINUS", "UMINUS", "POINT",
  "LEFT_PARENTHESIS", "RIGHT_PARENTHESIS", "$accept", "stmts", "$@1",
  "program", "stmt", "expr", "term", "assignexpr", "primary", "lvalue",
  "member", "call", "callsuffix", "normcall", "methodcall", "elist", "$@2",
  "_elist_", "objectdef", "indexed", "$@3", "_indexed_", "indexedelem",
  "block", "$@4", "fid", "funcargs", "funcbody", "funcprefix",
  "jafterfunc", "funcdef", "const", "number", "idlist", "$@5", "_idlist_",
  "$@6", "ifprefix", "elseprefix", "ifstmt", "loopstart", "loopend",
  "loopstmt", "whilestart", "whilecond", "whilestmt", "N", "M",
  "forprefix", "forstmt", "returnstmt", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303
};
# endif

#define YYPACT_NINF -165

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-165)))

#define YYTABLE_NINF -68

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-68)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -165,    21,    28,   105,  -165,   -12,  -165,  -165,  -165,  -165,
      -3,     7,    18,    22,   146,    30,  -165,  -165,  -165,    33,
    -165,  -165,    17,  -165,   146,    -7,    -7,   146,  -165,   249,
    -165,  -165,  -165,    50,  -165,    10,  -165,  -165,    51,  -165,
    -165,  -165,   105,  -165,    29,  -165,  -165,  -165,  -165,   146,
      47,  -165,   262,  -165,  -165,  -165,  -165,  -165,  -165,    52,
     146,    54,    58,  -165,  -165,   -17,    10,   -17,   162,    37,
     146,   146,  -165,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   146,    53,   146,   146,  -165,  -165,    61,
      39,  -165,  -165,  -165,   146,    63,    39,    65,    44,    87,
     146,  -165,    39,   191,    68,  -165,    73,  -165,   291,  -165,
     146,    74,    56,  -165,    55,   179,   208,   415,   415,   375,
     375,   375,   375,   -33,   -33,  -165,  -165,  -165,    72,   306,
     404,  -165,    57,   321,  -165,    62,  -165,  -165,    90,    95,
    -165,   105,   220,   105,  -165,    78,  -165,  -165,  -165,   146,
    -165,   350,    58,  -165,    55,    39,    39,  -165,  -165,  -165,
    -165,  -165,    79,  -165,  -165,  -165,  -165,  -165,  -165,   146,
     291,   146,    74,    80,    84,   112,  -165,  -165,  -165,   363,
    -165,   392,  -165,  -165,  -165,   111,  -165,  -165,  -165,  -165,
    -165,  -165,   112,  -165
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     2,     0,    79,     1,     0,    86,   101,    87,    82,
       0,     0,     0,     0,     0,     0,    84,    85,    83,     0,
      45,    72,    61,    15,     0,     0,     0,    79,     3,     0,
      30,    16,    38,    40,    48,    41,    42,    13,     0,    14,
      44,    81,    79,     7,     0,     8,   104,     9,    10,     0,
      61,   108,     0,    11,    12,    33,    46,    47,     4,     0,
       0,     0,     0,    32,    79,    34,     0,    36,     0,     0,
       0,     0,     6,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    35,    37,     0,
      61,    54,    56,    57,     0,     0,    61,    74,     0,    96,
       0,    98,    61,     0,     0,   109,     2,    65,    64,    66,
       0,    70,     0,    31,    43,    28,    29,    26,    27,    22,
      23,    24,    25,    17,    18,    19,    20,    21,     0,     0,
      39,    49,     0,     0,    51,     0,    75,    78,    90,     0,
      95,    79,     0,    79,   103,     0,    94,   105,    73,     0,
      62,     0,     0,    68,     0,    61,    61,    50,    58,    52,
      53,    88,     0,    77,    80,    97,   102,    99,   104,     0,
      64,     0,    70,     0,     0,    93,    76,   100,    98,     0,
      63,     0,    69,    55,    59,     0,    89,   104,   106,    71,
      91,   107,    93,    92
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -165,    81,  -165,  -165,   -40,   -11,  -165,  -165,  -165,    -6,
    -165,     8,  -165,  -165,  -165,   -49,  -165,   -30,  -165,  -165,
    -165,   -35,   -10,     2,  -165,  -165,  -165,  -165,  -165,  -165,
     -22,  -165,  -165,  -165,  -165,   -47,  -165,  -165,  -165,  -165,
    -165,  -165,   -32,  -165,  -165,  -165,  -164,  -165,  -165,  -165,
    -165
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     3,     2,    28,    29,    30,    31,    32,    33,
      34,    35,    91,    92,    93,    59,    60,   150,    36,    61,
      62,   153,   111,    37,    58,   137,   139,   164,    98,    38,
      39,    40,    41,   162,   175,   186,   192,    42,   141,    43,
     143,   177,   144,    44,   101,    45,   102,   169,    46,    47,
      48
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      52,   104,    99,    55,   178,    69,    84,    81,    82,    83,
      15,     6,    85,    63,     8,     9,    68,    19,    20,    65,
      67,    -5,    14,   191,    15,    16,    17,    18,     4,    89,
      90,    19,    20,    66,    66,    49,    22,    51,   103,    94,
      64,   132,   112,   -67,    50,   -60,    24,   135,    53,   108,
      25,    26,    54,   145,    27,    56,    95,    96,    57,   115,
     116,    97,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,    84,   129,   130,   100,   -60,   128,    85,
     107,    86,   109,   133,   110,   114,   131,   -60,   134,   142,
     136,   138,   140,    87,    88,   152,    89,    90,   147,   151,
     148,   165,   155,   167,   154,   158,   173,   174,     5,     6,
     160,     7,     8,     9,    10,   161,    11,    12,    13,   156,
      14,    21,    15,    16,    17,    18,   168,   176,   183,    19,
      20,    21,   184,   185,    22,    23,   190,   182,   170,   106,
     180,   163,   172,     0,    24,   193,   187,     0,    25,    26,
       6,     0,    27,     8,     9,     0,     0,     0,   179,     0,
     181,    14,     0,    15,    16,    17,    18,     0,     0,     0,
      19,    20,     0,     0,     0,    22,    70,     0,    71,     0,
       0,     0,     0,     0,     0,    24,     0,     0,     0,    25,
      26,     0,     0,    27,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    70,     0,    71,     0,     0,
     113,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    70,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    70,     0,    71,     0,     0,   146,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,     0,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    70,     0,    71,     0,     0,   166,     0,
       0,     0,     0,     0,     0,     0,    70,     0,    71,    72,
       0,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,   105,     0,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    70,     0,    71,     0,     0,
       0,     0,   149,     0,     0,     0,     0,     0,     0,     0,
      70,     0,    71,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,   157,    70,     0,    71,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,   159,
       0,     0,     0,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    70,     0,    71,     0,     0,     0,
       0,     0,   171,     0,     0,     0,     0,    70,     0,    71,
       0,     0,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,   188,     0,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    70,     0,    71,   -68,
     -68,   -68,   -68,    79,    80,    81,    82,    83,    70,   189,
      71,     0,     0,     0,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,     0,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,   -68,   -68,    75,
      76,    77,    78,    79,    80,    81,    82,    83
};

static const yytype_int16 yycheck[] =
{
      11,    50,    42,    14,   168,    27,    23,    40,    41,    42,
      17,     4,    29,    24,     7,     8,    27,    24,    25,    25,
      26,     0,    15,   187,    17,    18,    19,    20,     0,    46,
      47,    24,    25,    25,    26,    47,    29,    30,    49,    29,
      47,    90,    64,    26,    47,    28,    39,    96,    30,    60,
      43,    44,    30,   102,    47,    25,    46,    47,    25,    70,
      71,    10,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    23,    85,    86,    47,    30,    25,    29,
      28,    31,    28,    94,    26,    48,    25,    48,    25,   100,
      25,    47,     5,    43,    44,    21,    46,    47,    30,   110,
      27,   141,    47,   143,    48,    48,   155,   156,     3,     4,
      48,     6,     7,     8,     9,    25,    11,    12,    13,    47,
      15,    26,    17,    18,    19,    20,    48,    48,    48,    24,
      25,    26,    48,    21,    29,    30,    25,   172,   149,    58,
     170,   139,   152,    -1,    39,   192,   178,    -1,    43,    44,
       4,    -1,    47,     7,     8,    -1,    -1,    -1,   169,    -1,
     171,    15,    -1,    17,    18,    19,    20,    -1,    -1,    -1,
      24,    25,    -1,    -1,    -1,    29,    14,    -1,    16,    -1,
      -1,    -1,    -1,    -1,    -1,    39,    -1,    -1,    -1,    43,
      44,    -1,    -1,    47,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    14,    -1,    16,    -1,    -1,
      48,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    14,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    14,    -1,    16,    -1,    -1,    48,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    -1,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    14,    -1,    16,    -1,    -1,    48,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    14,    -1,    16,    30,
      -1,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    30,    -1,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    14,    -1,    16,    -1,    -1,
      -1,    -1,    21,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      14,    -1,    16,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    28,    14,    -1,    16,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    28,
      -1,    -1,    -1,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    14,    -1,    16,    -1,    -1,    -1,
      -1,    -1,    22,    -1,    -1,    -1,    -1,    14,    -1,    16,
      -1,    -1,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    30,    -1,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    14,    -1,    16,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    14,    27,
      16,    -1,    -1,    -1,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    -1,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    50,    52,    51,     0,     3,     4,     6,     7,     8,
       9,    11,    12,    13,    15,    17,    18,    19,    20,    24,
      25,    26,    29,    30,    39,    43,    44,    47,    53,    54,
      55,    56,    57,    58,    59,    60,    67,    72,    78,    79,
      80,    81,    86,    88,    92,    94,    97,    98,    99,    47,
      47,    30,    54,    30,    30,    54,    25,    25,    73,    64,
      65,    68,    69,    54,    47,    58,    60,    58,    54,    79,
      14,    16,    30,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    23,    29,    31,    43,    44,    46,
      47,    61,    62,    63,    29,    46,    47,    10,    77,    53,
      47,    93,    95,    54,    64,    30,    50,    28,    54,    28,
      26,    71,    79,    48,    48,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    25,    54,
      54,    25,    64,    54,    25,    64,    25,    74,    47,    75,
       5,    87,    54,    89,    91,    64,    48,    30,    27,    21,
      66,    54,    21,    70,    48,    47,    47,    28,    48,    28,
      48,    25,    82,    72,    76,    53,    48,    53,    48,    96,
      54,    22,    71,    64,    64,    83,    48,    90,    95,    54,
      66,    54,    70,    48,    48,    21,    84,    91,    30,    27,
      25,    95,    85,    84
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    49,    51,    50,    50,    52,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    55,    55,    55,    55,    55,    55,    55,    55,    56,
      57,    57,    57,    57,    57,    58,    58,    58,    58,    59,
      59,    59,    59,    60,    60,    60,    61,    61,    62,    63,
      64,    65,    64,    66,    66,    67,    67,    69,    68,    70,
      70,    71,    73,    72,    74,    74,    75,    76,    77,    78,
      79,    80,    80,    80,    80,    80,    81,    81,    83,    82,
      82,    85,    84,    84,    86,    87,    88,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,    99
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     3,     0,     1,     2,     1,     1,     1,
       1,     2,     2,     1,     1,     1,     1,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       1,     3,     2,     2,     2,     2,     2,     2,     1,     3,
       1,     1,     1,     3,     1,     1,     2,     2,     1,     3,
       4,     3,     4,     4,     2,     6,     1,     1,     3,     5,
       0,     0,     3,     3,     0,     3,     3,     0,     3,     3,
       0,     5,     0,     4,     0,     1,     3,     1,     2,     0,
       4,     1,     1,     1,     1,     1,     1,     1,     0,     3,
       0,     0,     4,     0,     4,     1,     2,     4,     0,     0,
       3,     1,     3,     3,     0,     0,     7,     7,     2,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 128 "delete2.y" /* yacc.c:1646  */
    {  if((yyvsp[0].Stmt2)==NULL) (yyvsp[0].Stmt2) = new stmtStruct();  }
#line 1486 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 128 "delete2.y" /* yacc.c:1646  */
    {

/*		$1 = new stmtStruct();
		$1->b=new breakStruct();
		$1->c= new continueStruct();*/

		(yyval.Stmt2) = new stmtStruct();

		if((yyvsp[-2].Stmt2)!=NULL ){
		
			for(auto it = (yyvsp[-2].Stmt2)->breakList.begin();it!=(yyvsp[-2].Stmt2)->breakList.end();it++){
				cout<<*it<<endl;
				(yyval.Stmt2)->breakList.push_front(*it);
			}
			for(auto it = (yyvsp[-2].Stmt2)->continueList.begin();it!=(yyvsp[-2].Stmt2)->continueList.end();it++){
				cout<<*it<<endl;
				(yyval.Stmt2)->continueList.push_front(*it);
			}
}

if((yyvsp[0].Stmt2)!=NULL ){

		for(auto it = (yyvsp[0].Stmt2)->breakList.begin();it!=(yyvsp[0].Stmt2)->breakList.end();++it){
			cout<<*it<<endl;
			(yyval.Stmt2)->breakList.push_front(*it);
		}
		for(auto it = (yyvsp[0].Stmt2)->continueList.begin();it!=(yyvsp[0].Stmt2)->continueList.end();it++){
			cout<<*it<<endl;
			(yyval.Stmt2)->continueList.push_front(*it);
		}
}
	/*	for(auto it = $2->continueList.begin();it!=$2->continueList.end();it++){
		cout<<*it<<endl;
			$$->continueList.push_front(*it);
		}*/

	cout<<"apo stmts se stmts stmt \n";}
#line 1528 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 165 "delete2.y" /* yacc.c:1646  */
    {(yyval.Stmt2)=NULL;cout<<"apo stmts se tpt \n";}
#line 1534 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 168 "delete2.y" /* yacc.c:1646  */
    {}
#line 1540 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 171 "delete2.y" /* yacc.c:1646  */
    {
	(yyval.Stmt2)=NULL;
	cout<<"apo statement se Semicolon \n";
}
#line 1549 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 175 "delete2.y" /* yacc.c:1646  */
    {cout<<"apo statement phga se Ifstmt \n";
	(yyval.Stmt2)=(yyvsp[0].Stmt2);}
#line 1556 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 177 "delete2.y" /* yacc.c:1646  */
    {cout<<"apo statement phga se Whilestmt \n";
	(yyval.Stmt2)=NULL;
	}
#line 1564 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 180 "delete2.y" /* yacc.c:1646  */
    {cout<<"apo statement phga se Forstmt \n";
	(yyval.Stmt2)=(yyvsp[0].Stmt2);;
	}
#line 1572 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 183 "delete2.y" /* yacc.c:1646  */
    {cout<<"apo statement phga se Returnstmt \n";
					if(scope==0) yyerror("Return statement at scope 0");
					(yyval.Stmt2)=NULL;
					}
#line 1581 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 187 "delete2.y" /* yacc.c:1646  */
    {cout<<"apo statement phga se Breaksemicolostmt \n";
					if(loopcounter==0) yyerror("Break statement at scope 0");

					(yyvsp[-1].Stmt2)=new stmtStruct();

					(yyvsp[-1].Stmt2)->breakList.push_front(currQuad);

		emit(jump,(expr*)0,(expr*)0,(expr*)0,-21,yylineno);
		(yyval.Stmt2)=(yyvsp[-1].Stmt2);
	}
#line 1596 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 197 "delete2.y" /* yacc.c:1646  */
    {cout<<"apo statement phga se Continuesemicolostmt \n";
					if(loopcounter==0) yyerror("Continue statement at scope 0");

					(yyvsp[-1].Stmt2)=new stmtStruct();

					(yyvsp[-1].Stmt2)->continueList.push_front(currQuad);

		emit(jump,(expr*)0,(expr*)0,(expr*)0,-21,yylineno);
		(yyval.Stmt2)=(yyvsp[-1].Stmt2);
	}
#line 1611 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 208 "delete2.y" /* yacc.c:1646  */
    {(yyval.Stmt2)=(yyvsp[0].Stmt2);cout<<"apo statement phga se Block \n";}
#line 1617 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 209 "delete2.y" /* yacc.c:1646  */
    {(yyval.Stmt2)=NULL;cout<<"apo statement phga se Funcdef \n";}
#line 1623 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 210 "delete2.y" /* yacc.c:1646  */
    {(yyval.Stmt2)=NULL;cout<<"apo statement phga se Semicolon \n";}
#line 1629 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 213 "delete2.y" /* yacc.c:1646  */
    {cout<<"apo expr se assignexpr \n";
	(yyval.exprNode)=(yyvsp[0].exprNode);
}
#line 1637 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 217 "delete2.y" /* yacc.c:1646  */
    {cout<<"apo expr phga se Plus expr"<<endl;
					expr* ex1=(expr*)(yyvsp[-2].exprNode);
					expr* ex2=(expr*)(yyvsp[0].exprNode);
					(yyval.exprNode)=newexpr(arithexpr_e);
					(yyval.exprNode)->sym=newtemp();
					emit(add,ex1,ex2,(yyval.exprNode),-21,yylineno);
}
#line 1649 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 224 "delete2.y" /* yacc.c:1646  */
    {cout<<"apo expr phga se Minus expr"<<endl;
					expr* ex1=(expr*)(yyvsp[-2].exprNode);
					expr* ex2=(expr*)(yyvsp[0].exprNode);
					(yyval.exprNode)=newexpr(arithexpr_e);
					(yyval.exprNode)->sym=newtemp();
					emit(sub,ex1,ex2,(yyval.exprNode),-21,yylineno);
					}
#line 1661 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 231 "delete2.y" /* yacc.c:1646  */
    {cout<<"apo expr phga se Mul expr"<<endl;
					expr* ex1=(expr*)(yyvsp[-2].exprNode);
					expr* ex2=(expr*)(yyvsp[0].exprNode);
					(yyval.exprNode)=newexpr(arithexpr_e);
					(yyval.exprNode)->sym=newtemp();
					emit(mul,ex1,ex2,(yyval.exprNode),-21,yylineno);
}
#line 1673 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 238 "delete2.y" /* yacc.c:1646  */
    {cout<<"apo expr phga se Div expr"<<endl;
					expr* ex1=(expr*)(yyvsp[-2].exprNode);
					expr* ex2=(expr*)(yyvsp[0].exprNode);
					(yyval.exprNode)=newexpr(arithexpr_e);
					(yyval.exprNode)->sym=newtemp();
					emit(div1,ex1,ex2,(yyval.exprNode),-21,yylineno);//ELEGXOS !=0 PARANOMASTHS
}
#line 1685 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 245 "delete2.y" /* yacc.c:1646  */
    {cout<<"apo expr phga se Modulo expr"<<endl;
					expr* ex1=(expr*)(yyvsp[-2].exprNode);
					expr* ex2=(expr*)(yyvsp[0].exprNode);
					(yyval.exprNode)=newexpr(arithexpr_e);
					(yyval.exprNode)->sym=newtemp();
					emit(mod,ex1,ex2,(yyval.exprNode),-21,yylineno);  //ELEGXOS !=0 PARANOMASTHS
}
#line 1697 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 252 "delete2.y" /* yacc.c:1646  */
    {cout<<"apo expr phga se GT expr"<<endl;
					expr* ex1=(expr*)(yyvsp[-2].exprNode);
					expr* ex2=(expr*)(yyvsp[0].exprNode);
					(yyval.exprNode)=newexpr(boolexpr_e);
					(yyval.exprNode)->sym=newtemp();
					emit(if_greater,ex1,ex2,(expr*)0,currQuad+3,yylineno);
					emit(assign,newexpr_constbool(0),(expr*)0,(yyval.exprNode),-21,yylineno);
					emit(jump,(expr*)0,(expr*)0,(expr*)0,currQuad+2,yylineno);
					emit(assign,newexpr_constbool(1),(expr*)0,(yyval.exprNode),-21,yylineno);
				}
#line 1712 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 262 "delete2.y" /* yacc.c:1646  */
    {cout<<"apo expr phga se GE expr"<<endl;
					expr* ex1=(expr*)(yyvsp[-2].exprNode);
					expr* ex2=(expr*)(yyvsp[0].exprNode);
					(yyval.exprNode)=newexpr(boolexpr_e);
					(yyval.exprNode)->sym=newtemp();
					emit(if_greatereq,ex1,ex2,(expr*)0,currQuad+3,yylineno);
					emit(assign,newexpr_constbool(0),(expr*)0,(yyval.exprNode),-21,yylineno);
					emit(jump,(expr*)0,(expr*)0,(expr*)0,currQuad+2,yylineno);
					emit(assign,newexpr_constbool(1),(expr*)0,(yyval.exprNode),-21,yylineno);
				}
#line 1727 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 272 "delete2.y" /* yacc.c:1646  */
    {cout<<"apo expr phga se LE expr"<<endl;
					expr* ex1=(expr*)(yyvsp[-2].exprNode);
					expr* ex2=(expr*)(yyvsp[0].exprNode);
					(yyval.exprNode)=newexpr(boolexpr_e);
					(yyval.exprNode)->sym=newtemp();
					emit(if_less,ex1,ex2,(expr*)0,currQuad+3,yylineno);
					emit(assign,newexpr_constbool(0),(expr*)0,(yyval.exprNode),-21,yylineno);
					emit(jump,(expr*)0,(expr*)0,(expr*)0,currQuad+2,yylineno);
					emit(assign,newexpr_constbool(1),(expr*)0,(yyval.exprNode),-21,yylineno);
				}
#line 1742 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 282 "delete2.y" /* yacc.c:1646  */
    {cout<<"apo expr phga se LE expr"<<endl;
					expr* ex1=(expr*)(yyvsp[-2].exprNode);
					expr* ex2=(expr*)(yyvsp[0].exprNode);
					(yyval.exprNode)=newexpr(boolexpr_e);
					(yyval.exprNode)->sym=newtemp();
					emit(if_lesseq,ex1,ex2,(expr*)0,currQuad+3,yylineno);
					emit(assign,newexpr_constbool(0),(expr*)0,(yyval.exprNode),-21,yylineno);
					emit(jump,(expr*)0,(expr*)0,(expr*)0,currQuad+2,yylineno);
					emit(assign,newexpr_constbool(1),(expr*)0,(yyval.exprNode),-21,yylineno);
				}
#line 1757 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 292 "delete2.y" /* yacc.c:1646  */
    {cout<<"apo expr phga se Equal expr"<<endl;
					expr* ex1=(expr*)(yyvsp[-2].exprNode);
					expr* ex2=(expr*)(yyvsp[0].exprNode);
					(yyval.exprNode)=newexpr(boolexpr_e);
					(yyval.exprNode)->sym=newtemp();
					emit(if_eq,ex1,ex2,(expr*)0,currQuad+3,yylineno);
					emit(assign,newexpr_constbool(0),(expr*)0,(yyval.exprNode),-21,yylineno);
					emit(jump,(expr*)0,(expr*)0,(expr*)0,currQuad+2,yylineno);
					emit(assign,newexpr_constbool(1),(expr*)0,(yyval.exprNode),-21,yylineno);
				}
#line 1772 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 302 "delete2.y" /* yacc.c:1646  */
    {cout<<"apo expr phga se Nequal expr"<<endl;
					expr* ex1=(expr*)(yyvsp[-2].exprNode);
					expr* ex2=(expr*)(yyvsp[0].exprNode);
					(yyval.exprNode)=newexpr(boolexpr_e);
					(yyval.exprNode)->sym=newtemp();
					emit(if_noteq,ex1,ex2,(expr*)0,currQuad+3,yylineno);
					emit(assign,newexpr_constbool(0),(expr*)0,(yyval.exprNode),-21,yylineno);
					emit(jump,(expr*)0,(expr*)0,(expr*)0,currQuad+2,yylineno);
					emit(assign,newexpr_constbool(1),(expr*)0,(yyval.exprNode),-21,yylineno);
				}
#line 1787 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 312 "delete2.y" /* yacc.c:1646  */
    {cout<<"apo expr phga se And expr"<<endl;
					expr* ex1=(expr*)(yyvsp[-2].exprNode);
					expr* ex2=(expr*)(yyvsp[0].exprNode);
					(yyval.exprNode)=newexpr(boolexpr_e);
					(yyval.exprNode)->sym=newtemp();
					emit(and1,ex1,ex2,(yyval.exprNode),-21,yylineno);
				}
#line 1799 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 319 "delete2.y" /* yacc.c:1646  */
    {cout<<"apo expr phga se Or expr"<<endl;
					expr* ex1=(expr*)(yyvsp[-2].exprNode);
					expr* ex2=(expr*)(yyvsp[0].exprNode);
					(yyval.exprNode)=newexpr(boolexpr_e);
					(yyval.exprNode)->sym=newtemp();
					emit(or1,ex1,ex2,(yyval.exprNode),-21,yylineno);
				}
#line 1811 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 326 "delete2.y" /* yacc.c:1646  */
    {cout<<"apo expr phga se term "<<endl;
	(yyval.exprNode)=(yyvsp[0].exprNode);
}
#line 1819 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 331 "delete2.y" /* yacc.c:1646  */
    {
							(yyval.exprNode)=(yyvsp[-1].exprNode);
							cout<<"apo term se ( expr ) \n";
			}
#line 1828 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 336 "delete2.y" /* yacc.c:1646  */
    {cout<<"apo term phga se Uminus"<<endl;
							expr* ex=(expr*) (yyvsp[0].exprNode);
							checkuminus(ex);
							(yyval.exprNode)=newexpr(arithexpr_e);
							(yyval.exprNode)->sym=newtemp();
							emit(uminus,ex,(expr*)0,(yyval.exprNode),-21,yylineno);
						}
#line 1840 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 343 "delete2.y" /* yacc.c:1646  */
    {cout<<"apo term phga se Not expr"<<endl;
							expr* ex=(expr*) (yyvsp[0].exprNode);
							checkuminus(ex);
							(yyval.exprNode)=newexpr(arithexpr_e);
							(yyval.exprNode)->sym=newtemp();
							emit(not1,ex,(expr*)0,(yyval.exprNode),-21,yylineno);
						}
#line 1852 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 350 "delete2.y" /* yacc.c:1646  */
    {cout<<"apo term phga se PlusPlus lvalue"<<endl;
							if (((expr *)(yyvsp[0].exprNode))->type==programfunc_e || ((expr *)(yyvsp[0].exprNode))->type==libraryfunc_e){
								string lola="ERROR: USING ILEGAL OPERATOR -> ";lola+="++";lola+=" <- on function -> ";lola+=*yylval.stringValue;lola+=" <-";
								yyerror(lola);
							}
							if((yyvsp[0].exprNode)->type == tableitem_e){
								(yyval.exprNode) = emit_iftableitem((yyvsp[0].exprNode));
								emit(add,(yyval.exprNode),newexpr_constnum(1),(yyval.exprNode),-21,yylineno);
								emit(tablesetelem,(yyvsp[0].exprNode),(yyvsp[0].exprNode)->index,(yyval.exprNode),-21,yylineno);
							}else{
								emit(add,(yyvsp[0].exprNode),newexpr_constnum(1),(yyvsp[0].exprNode),-21,yylineno);
								(yyval.exprNode) = newexpr(arithexpr_e);
								(yyval.exprNode)->sym = newtemp();
								emit(assign,(yyvsp[0].exprNode),(expr*)0,(yyval.exprNode),-21,yylineno);
							}
}
#line 1873 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 366 "delete2.y" /* yacc.c:1646  */
    {cout<<"apo term phga se lvalue PlusPlus"<<endl;
							if (((expr *)(yyvsp[-1].exprNode))->type==programfunc_e || ((expr *)(yyvsp[-1].exprNode))->type==libraryfunc_e){
								string lola="ERROR: USING ILEGAL OPERATOR -> ";lola+="++";lola+=" <- on function -> ";lola+=*yylval.stringValue;lola+=" <-";
								yyerror(lola);
							}
							(yyval.exprNode) = newexpr(var_e);
							(yyval.exprNode)->sym = newtemp();

							if((yyvsp[-1].exprNode)->type == tableitem_e){
								expr* value = emit_iftableitem((yyvsp[-1].exprNode));
								emit(assign,value,(expr*)0,(yyval.exprNode),-21,yylineno);
								emit(add,value,newexpr_constnum(1),value,-21,yylineno);
								emit(tablesetelem,(yyvsp[-1].exprNode),(yyvsp[-1].exprNode)->index,value,-21,yylineno);
							}else{
								emit(assign,(yyvsp[-1].exprNode),(expr*)0,(yyval.exprNode),-21,yylineno);
								emit(add,(yyvsp[-1].exprNode),newexpr_constnum(1),(yyvsp[-1].exprNode),-21,yylineno);
							}

}
#line 1897 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 385 "delete2.y" /* yacc.c:1646  */
    {cout<<"apo term phga se MinusMinus lvalue"<<endl;
							if (((expr *)(yyvsp[0].exprNode))->type==programfunc_e || ((expr *)(yyvsp[0].exprNode))->type==libraryfunc_e ){
								string lola="ERROR: USING ILEGAL OPERATOR -> ";lola+="--";lola+=" <- on function -> ";lola+=*yylval.stringValue;lola+=" <-";
								yyerror(lola);
							}
							if((yyvsp[0].exprNode)->type == tableitem_e){
								(yyval.exprNode) = emit_iftableitem((yyvsp[0].exprNode));
								emit(sub,(yyval.exprNode),newexpr_constnum(1),(yyval.exprNode),-21,yylineno);
								emit(tablesetelem,(yyvsp[0].exprNode),(yyvsp[0].exprNode)->index,(yyval.exprNode),-21,yylineno);
							}else{
								emit(sub,(yyvsp[0].exprNode),newexpr_constnum(1),(yyvsp[0].exprNode),-21,yylineno);
								(yyval.exprNode) = newexpr(arithexpr_e);
								(yyval.exprNode)->sym = newtemp();
								emit(assign,(yyvsp[0].exprNode),(expr*)0,(yyval.exprNode),-21,yylineno);
							}
}
#line 1918 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 401 "delete2.y" /* yacc.c:1646  */
    {cout<<"apo term phga se lvalue MinusMinus"<<endl;
								if (((expr *)(yyvsp[-1].exprNode))->type==programfunc_e || ((expr *)(yyvsp[-1].exprNode))->type==libraryfunc_e ){
								string lola="ERROR: USING ILEGAL OPERATOR -> ";lola+="--";lola+=" <- on function -> ";lola+=*yylval.stringValue;lola+=" <-";
								yyerror(lola);
							}
							(yyval.exprNode) = newexpr(var_e);
							(yyval.exprNode)->sym = newtemp();

							if((yyvsp[-1].exprNode)->type == tableitem_e){
								expr* value = emit_iftableitem((yyvsp[-1].exprNode));
								emit(assign,value,(expr*)0,(yyval.exprNode),-21,yylineno);
								emit(sub,value,newexpr_constnum(1),value,-21,yylineno);
								emit(tablesetelem,(yyvsp[-1].exprNode),(yyvsp[-1].exprNode) ->index,value,-21,yylineno);
							}else{
								emit(assign,(yyvsp[-1].exprNode),(expr*)0,(yyval.exprNode),-21,yylineno);
								emit(sub,(yyvsp[-1].exprNode),newexpr_constnum(1),(yyvsp[-1].exprNode),-21,yylineno);
							}
}
#line 1941 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 419 "delete2.y" /* yacc.c:1646  */
    {(yyval.exprNode)=(yyvsp[0].exprNode);cout<<"apo term phga se primary "<<endl;}
#line 1947 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 422 "delete2.y" /* yacc.c:1646  */
    {
			cout<<"apo assignedexpr se lvalue ASGN expr \n";

	if ( ((expr* )(yyvsp[-2].exprNode))->type == programfunc_e ){
	string lola = "ERROR: Trying to use Userfun: ->"+*yylval.stringValue+"<- as lvalue";
			yyerror(lola);
	}
	if ( ((expr*)(yyvsp[-2].exprNode))->type == libraryfunc_e ){
	string lola = "ERROR: Trying to use libraryfunc_s: ->"+((SymbolTableEntry*)(yyvsp[-2].exprNode))->value.funcVal->name+"<- as lvalue";
			yyerror(lola);
	}
	if ( (yyvsp[-2].exprNode)->type == tableitem_e)
		{
			emit(tablesetelem,(yyvsp[-2].exprNode),(yyvsp[-2].exprNode)->index,(yyvsp[0].exprNode),-21,yylineno);
			
			(yyval.exprNode)=emit_iftableitem((yyvsp[-2].exprNode));
			(yyval.exprNode)->type = assignexpr_e;
		}
	else{
			emit(assign,(yyvsp[0].exprNode),(expr*)0,(yyvsp[-2].exprNode),-21,yylineno);

			(yyval.exprNode)=newexpr(assignexpr_e);
			(yyval.exprNode)->sym = newtemp();
			emit(assign,(yyvsp[-2].exprNode),(expr*)0,(yyval.exprNode),-21,yylineno);
		}
}
#line 1978 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 450 "delete2.y" /* yacc.c:1646  */
    {
	(yyval.exprNode)=emit_iftableitem((yyvsp[0].exprNode));
	cout<<"apo primary se lvalue \n";}
#line 1986 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 453 "delete2.y" /* yacc.c:1646  */
    {cout<<"apo primary phga se call "<<endl;
	(yyval.exprNode)=(yyvsp[0].exprNode);
}
#line 1994 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 456 "delete2.y" /* yacc.c:1646  */
    {cout<<"apo primary phga se objectdef"<<endl;
	(yyval.exprNode)=(yyvsp[0].exprNode);
}
#line 2002 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 459 "delete2.y" /* yacc.c:1646  */
    {cout<<"apo primary phga se left par funcdef right parenth "<<endl;
	(yyval.exprNode)=newexpr(programfunc_e);
	(yyval.exprNode)->sym=(yyvsp[-1].SymbolTableEntry);

}
#line 2012 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 464 "delete2.y" /* yacc.c:1646  */
    {cout<<"apo primary phga se const "<<endl;

}
#line 2020 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 469 "delete2.y" /* yacc.c:1646  */
    {

	//resetFunctionLocalOffset();					//------------------------
				cout<<"apo lvalue se ID \n";
		SymbolTableEntry *t = lookup_all(*yylval.stringValue,(symbol_t)666);
		if(t == NULL){
			/*if(scope != 0){
				t=insert_var(*yylval.stringValue,var_s);
				t->offset=currScopeOffset();
				t->scopespace=currScopeSpace();
				inCurrScopeOffset();
			}else{
				t=insert_var(*yylval.stringValue,var_s);
				t->offset=currScopeOffset();
				t->scopespace=currScopeSpace();
				inCurrScopeOffset();
			}	*/
				t=insert_var(*yylval.stringValue,var_s);

					if(t->value.varVal->scope==0){
					t->scopespace=programvar;
					t->offset=programVarOffset;
					programVarOffset++;
					(yyval.exprNode) = (expr *)lvalue_expr(t);
				}
				else{
					t->offset=currScopeOffset();
					t->scopespace=currScopeSpace();
					inCurrScopeOffset();
					(yyval.exprNode) = (expr *)lvalue_expr(t);
				}
		}
		else{	//make ccout<<"to scope edw einai : "<<scope<<endl;
			if(t->type==var_s && !checkVisibility(t) )
				yyerror("ERROR: Accesing variable: -> " + *yylval.stringValue +"<- but is not visible");
			else if( checkVisibility(t) ){
					(yyval.exprNode) = (expr *)lvalue_expr(t);
			}
		}
}
#line 2065 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 510 "delete2.y" /* yacc.c:1646  */
    {
			cout<<"apo lvalue se Local Id \n";
	SymbolTableEntry *t = lookup_scope(0,*yylval.stringValue,libraryfunc_s);

	if( t!=NULL ){
		if(scope!=0 ){
			string lola = "ERROR: Trying to shadow libraryfunc_s";
			lola+=" -> ";lola+=*yylval.stringValue;lola+=" <- ";
			yyerror(lola);
			}
			(yyval.exprNode) = (expr *)lvalue_expr(t);
	}
	else  {
		if((t= lookup_scope(scope,*yylval.stringValue,(symbol_t)666))==NULL){
		/*	if(scope != 0){
				t=insert_var(*yylval.stringValue,var_s);

				t->offset=currScopeOffset();
				t->scopespace=currScopeSpace();
				inCurrScopeOffset();
			}else{
				t=insert_var(*yylval.stringValue,var_s);
				t->offset=currScopeOffset();
				t->scopespace=currScopeSpace();
				inCurrScopeOffset();
			}*/
			t=insert_var(*yylval.stringValue,var_s);

				if(t->value.varVal->scope==0){
					t->scopespace=programvar;
					t->offset=programVarOffset;
					programVarOffset++;
					(yyval.exprNode) = (expr *)lvalue_expr(t);
				}
				else{
					t->offset=currScopeOffset();
					t->scopespace=currScopeSpace();
					inCurrScopeOffset();
					(yyval.exprNode) = (expr *)lvalue_expr(t);
				}
		}
			else{
				/*	if(t->type==programfunc_s){
					string lola="ERROR: Trying to shadow programfunc_s fucntion";
					lola+=" -> ";
					lola+=*yylval.stringValue;
					lola+=" <- ";
						yyerror(lola);
					}
					else if( t-> type == var_s){
						string lola="ERROR: Trying to shadow local var ";
						lola+="-> "; lola+=*yylval.stringValue; lola+=" <-";
						yyerror(lola);
					}	*/
			}		(yyval.exprNode) = (expr *)lvalue_expr(t);
	}
}
#line 2127 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 567 "delete2.y" /* yacc.c:1646  */
    {
			cout<<"apo lvalue se Double_anw katw \n";
	SymbolTableEntry *t = lookup_scope(0,*yylval.stringValue,(symbol_t)666);
			if(t==NULL){
				string lola="ERROR: No var_s var/func found with this name ->";
				lola+=*yylval.stringValue; lola+="<- ";
				yyerror(lola);
			}
	if(t!=NULL)
		(yyval.exprNode) = (expr *)lvalue_expr(t);

}
#line 2144 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 579 "delete2.y" /* yacc.c:1646  */
    {cout<<"apo DOUBLE_ANWKATW se member \n";
	(yyval.exprNode)=(yyvsp[0].exprNode);
}
#line 2152 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 584 "delete2.y" /* yacc.c:1646  */
    {	cout<<"apo member phga se lvalue Point Id"<<endl;
	(yyval.exprNode)=member_item((yyvsp[-2].exprNode),(yyvsp[0].stringValue));
}
#line 2160 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 587 "delete2.y" /* yacc.c:1646  */
    {cout<<"apo member phga se lvalue left [ expr ]"<<endl;
	(yyvsp[-3].exprNode)=emit_iftableitem((yyvsp[-3].exprNode));
	(yyval.exprNode)=newexpr(tableitem_e);
	(yyval.exprNode)->sym=(yyvsp[-3].exprNode)->sym;
	(yyval.exprNode)->index=(yyvsp[-1].exprNode);
}
#line 2171 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 593 "delete2.y" /* yacc.c:1646  */
    {cout<<"apo member phga se point id"<<endl;
	(yyval.exprNode)=member_item((yyvsp[-2].exprNode),(yyvsp[0].stringValue));
}
#line 2179 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 596 "delete2.y" /* yacc.c:1646  */
    {cout<<"apo member phga se call [ expr ] "<<endl;
	(yyvsp[-3].exprNode)=emit_iftableitem((yyvsp[-3].exprNode));
	(yyval.exprNode)=newexpr(tableitem_e);
	(yyval.exprNode)->sym=(yyvsp[-3].exprNode)->sym;
	(yyval.exprNode)->index=(yyvsp[-1].exprNode);
}
#line 2190 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 604 "delete2.y" /* yacc.c:1646  */
    {cout<<"apo call se call ( elist ) "<<endl;
	(yyval.exprNode)=make_call((yyvsp[-3].exprNode));
}
#line 2198 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 607 "delete2.y" /* yacc.c:1646  */
    {cout<<"apo call lvalue callsuffix "<<endl;
	if((yyvsp[0].callsuf)->method){
		expr* self=(yyvsp[-1].exprNode);
		(yyvsp[-1].exprNode)=emit_iftableitem(member_item(self,(yyvsp[0].callsuf)->name));
		exprList.push_front(self);
	}
	(yyval.exprNode)=make_call((yyvsp[-1].exprNode));
}
#line 2211 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 615 "delete2.y" /* yacc.c:1646  */
    {cout<<"apo call ( funcdef ) ( elist )"<<endl;
	expr* func=newexpr(programfunc_e);
	func->sym=(yyvsp[-4].SymbolTableEntry);
	(yyval.exprNode)=make_call(func);
}
#line 2221 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 622 "delete2.y" /* yacc.c:1646  */
    {cout<<"apo callsuffix se normcall "<<endl;
	(yyval.callsuf)=(yyvsp[0].callsuf);
}
#line 2229 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 625 "delete2.y" /* yacc.c:1646  */
    {cout<<"apo callsuffix se methodcamll "<<endl;
	(yyval.callsuf)=(yyvsp[0].callsuf);
}
#line 2237 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 630 "delete2.y" /* yacc.c:1646  */
    {cout<<"apo normcall se ( elist ) "<<endl;
	(yyval.callsuf)=new callsuffix();
	//$$.elist=$2;
	(yyval.callsuf)->method=false;
	(yyval.callsuf)->name=NULL;
}
#line 2248 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 638 "delete2.y" /* yacc.c:1646  */
    {cout<<"apo methodcall se doublepoint id ( elist ) "<<endl;
		(yyval.callsuf)=new callsuffix();
		//$$.elist=$4;
		(yyval.callsuf)->method=true;
		(yyval.callsuf)->name=(yyvsp[-3].stringValue);
}
#line 2259 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 646 "delete2.y" /* yacc.c:1646  */
    {cout<<"Mpika ELIST\n";
	exprList.clear();
	//$$=exprList.front();
  }
#line 2268 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 650 "delete2.y" /* yacc.c:1646  */
    {exprList.clear();}
#line 2274 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 650 "delete2.y" /* yacc.c:1646  */
    {cout<<"apo elist se expr elist \n";
	expr* ex=(expr*)(yyvsp[-1].exprNode);
	exprList.push_front(ex);

}
#line 2284 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 657 "delete2.y" /* yacc.c:1646  */
    {
	expr* ex=(expr*)(yyvsp[-1].exprNode);
	exprList.push_front(ex);
}
#line 2293 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 661 "delete2.y" /* yacc.c:1646  */
    {}
#line 2299 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 664 "delete2.y" /* yacc.c:1646  */
    {cout<<"apo objectdef se [elist] \n";
	expr *t=newexpr(newtable_e);
	t->sym=newtemp();
	emit(tablecreate,(expr*)0,(expr*)0,t,-21,yylineno);
	int i=0;
	if(!exprList.empty()){
	for(expr* e: exprList)
		emit(tablesetelem,t,newexpr_constnum(i++),e,-21,yylineno);
	}
	exprList.clear();
	(yyval.exprNode)=t;
}
#line 2316 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 677 "delete2.y" /* yacc.c:1646  */
    {cout<<"apo object def se [indexed] \n";

	expr* t=newexpr(newtable_e);
	t->sym=newtemp();
	emit(tablecreate,(expr*)0,(expr*)0,t,-21,yylineno);
	if(!pairList.empty()){
		pairList.reverse();
		for(pair* p: pairList){	emit(tablesetelem,t,p->key,p->value,-21,yylineno);
		}
	}
	(yyval.exprNode)=t;
}
#line 2333 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 691 "delete2.y" /* yacc.c:1646  */
    {
	pairList.clear();
}
#line 2341 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 693 "delete2.y" /* yacc.c:1646  */
    {cout<<"apo indexed se indexedele_indexed_ \n ";

}
#line 2349 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 698 "delete2.y" /* yacc.c:1646  */
    {}
#line 2355 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 699 "delete2.y" /* yacc.c:1646  */
    {}
#line 2361 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 703 "delete2.y" /* yacc.c:1646  */
    {
	pair* p=new pair();
	p->key=(expr*)(yyvsp[-3].exprNode);
	p->value=(expr*)(yyvsp[-1].exprNode);
	pairList.push_front(p);
}
#line 2372 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 710 "delete2.y" /* yacc.c:1646  */
    {
		//enterScopeSpace();
		if(currScopeSpace()==formalarg){
			bes=false;
			enterScopeSpace();
		}
		//cout<<"-----------------------------------------------------to scopeSpaceCounter =  "<<scopeSpaceCounter<<endl;
		if( scopeSpaceCounter % 2 != 0 &&  scopeSpaceCounter  != 1){
			OffsetStack.push(functionLocalOffset);
				cout<<"-----------------------------------------------------STOIBAS SIZE =  "<<OffsetStack.size()<<endl;
	}
	resetFunctionLocalOffset();

	if(scopeSpaceCounter % 2 == 0 && scopeSpaceCounter!=1)
	enterScopeSpace();

	scope++;
}
#line 2395 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 728 "delete2.y" /* yacc.c:1646  */
    {hide(scope);

		if(!OffsetStack.empty() &&  currScopeSpace()==functionlocal ){
				functionLocalOffset=OffsetStack.top();
				OffsetStack.pop();
				cout<<"-----------------------------------------------------STOIBAS SIZE =  "<<OffsetStack.size()<<endl;
		}

		if(scopeSpaceCounter  != 1){
			exitScopeSpace();
			exitScopeSpace();
		}
		scope--;
		(yyval.Stmt2)=(yyvsp[-1].Stmt2);
	}
#line 2415 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 745 "delete2.y" /* yacc.c:1646  */
    {	cout<<"Bika fid \n";
		string out="_AutoGenFunc_";
		out+=std::to_string(scope);
		out+="_";
		out+=std::to_string(yylineno);
		SymbolTableEntry* entry=insert_fun(out,programfunc_s);
		enterScopeSpace();										//------------------------
		(yyval.SymbolTableEntry)=(SymbolTableEntry*)entry;
}
#line 2429 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 754 "delete2.y" /* yacc.c:1646  */
    {	cout<<"Bika fid me name \n";
		SymbolTableEntry* t=lookup_scope(0,*yylval.stringValue,libraryfunc_s);
		if(t!=NULL){
			string lola0="ERROR: Trying to shadow the Library function ->"+*yylval.stringValue+"<- ";
			//$$=(SymbolTableEntry*)t;
			yyerror(lola0);
		}else{
			t= lookup_scope(scope,*yylval.stringValue,(symbol_t)666);
			if(t==NULL  ){
				SymbolTableEntry* entry=insert_fun(*yylval.stringValue,programfunc_s);

				enterScopeSpace();

				(yyval.SymbolTableEntry)=(SymbolTableEntry*)entry;
			}else{
				if(  t->type==programfunc_s && t->isActive==true   )	{
					string lola0 ="ERROR:(redefinition) The function ->" +*yylval.stringValue+"<- alreay exists at scope: "+ std::to_string(scope);
					yyerror(lola0);
			}	else if
					( (t->type==var_s || t->type==var_s) && t->isActive==true )	{
						string lola="ERROR:(redefinition) The variable ->" +*yylval.stringValue+"<- alreay exists at scope: "+ std::to_string(scope);
						yyerror(lola);
					}
				else if (t->type==2 ){
					string msg="ERROR:(redefinition) The var_s variable ->" +*yylval.stringValue+"<- alreay exists at scope: "+ std::to_string(scope);
					yyerror(msg);
				}
			}
		}
}
#line 2464 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 786 "delete2.y" /* yacc.c:1646  */
    {
	cout<<" KAINOURGIO 1\n";
	//enterScopeSpace();
	//resetFunctionLocalOffset();
}
#line 2474 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 792 "delete2.y" /* yacc.c:1646  */
    {cout<<" KAINOURGIO 2\n";
	//exitScopeSpace();
	}
#line 2482 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 796 "delete2.y" /* yacc.c:1646  */
    {cout<<" KAINOURGIO 3\n";
	(yyval.SymbolTableEntry)=(yyvsp[0].SymbolTableEntry);
	(yyval.SymbolTableEntry)->iaddress=currQuad;

	emit(funcstart,(expr*)0,(expr*)0,lvalue_expr((yyval.SymbolTableEntry)),-21,yylineno);
	functionLocalStack.push(currScopeOffset());
	//enterScopeSpace();
	//resetFormalArgsOffset();
	}
#line 2496 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 805 "delete2.y" /* yacc.c:1646  */
    {
	(yyval.intValue)=currQuad;
	emit(jump,(expr*)0,(expr*)0,(expr*)0,-21,yylineno);
}
#line 2505 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 810 "delete2.y" /* yacc.c:1646  */
    {cout<<" KAINOURGIO 4\n";
	//exitScopeSpace();
	(yyvsp[-2].SymbolTableEntry)->totalLocals=functionLocalOffset;
	//functionLocalOffset=functionLocalStack.top();
	//functionLocalStack.pop();
	//functionLocalOffset = OffsetStack.top();
	//OffsetStack.pop();
	(yyval.SymbolTableEntry)=(yyvsp[-2].SymbolTableEntry);
	emit(funcend,(expr*)0,(expr*)0,lvalue_expr((yyvsp[-2].SymbolTableEntry)),-21,yylineno);
	patchLabel((yyvsp[-3].intValue),currQuad);
	}
#line 2521 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 823 "delete2.y" /* yacc.c:1646  */
    {(yyval.exprNode)=(yyvsp[0].exprNode);}
#line 2527 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 824 "delete2.y" /* yacc.c:1646  */
    {
	//string tmp(*(string*)$1);
	//string *tmp=new string($1->c_str());
	(yyval.exprNode)=newexpr(conststring_e);

	string* a=new string((yyvsp[0].stringValue)->c_str());
	(yyval.exprNode)->strConst=*a;

	//string* tmp;
	//strcpy(tmp,$1);
	//$$=newexpr_conststring(tmp);
}
#line 2544 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 836 "delete2.y" /* yacc.c:1646  */
    {
	(yyval.exprNode)=newexpr(nil_e);
}
#line 2552 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 839 "delete2.y" /* yacc.c:1646  */
    {
	(yyval.exprNode)=newexpr(constbool_e);
	(yyval.exprNode)->boolConst=TRUE;
}
#line 2561 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 843 "delete2.y" /* yacc.c:1646  */
    {
	(yyval.exprNode)=newexpr(constbool_e);
	(yyval.exprNode)->boolConst=FALSE;
}
#line 2570 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 849 "delete2.y" /* yacc.c:1646  */
    {cout<<"apo number se Interger \n";
	int k=(int)(yyvsp[0].intValue);
	(yyval.exprNode)=newexpr(constnum_e);
	(yyval.exprNode)->numConst=k;
	//cout<<":TO K EINAI : "<<k<<endl;
}
#line 2581 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 855 "delete2.y" /* yacc.c:1646  */
    {cout<<"apo number se Real \n";
	double k=(double)(yyvsp[0].realValue);
	(yyval.exprNode)=newexpr(constnum_e);
	(yyval.exprNode)->numConst=k;
}
#line 2591 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 862 "delete2.y" /* yacc.c:1646  */
    {
	//resetFormalArgsOffset();
	int scope2 =scope; scope2++;
	SymbolTableEntry* t=lookup_scope(scope2,*yylval.stringValue,(symbol_t)666);

	if(t!=NULL && t->type== libraryfunc_s){
		cout<<"LIBBBBBB FUNCCCCCCCCCCCC";
	}
	if(t!=NULL){
		string lola = "ERROR: Bre8ike local var ->";
		lola+=*yylval.stringValue; lola+="<- pou dhlwnete arg se function idiou scope: ";lola+=std::to_string(scope);
		yyerror(lola);
	}
	if(t==NULL){
		if(!containsLib(*yylval.stringValue)){
		scope++;

		SymbolTableEntry * tmp = insert_var(*yylval.stringValue, var_s);

		tmp->scopespace=currScopeSpace();
		//cout<<"TO CURR OFFSET EINAI "<<currScopeOffset()<<endl;
		tmp->offset=currScopeOffset();
		//resetFormalArgsOffset();

		SymbolTableEntry* func=lookupFunc(scope-1);

			if(func ==NULL)cout<<"einai null auto pou brhka \n";

				if(func!=NULL){
					insertArguments(func->value.funcVal,tmp->value.varVal);
					//printFunc(func->value.funcVal);
				}
		scope--;
		}else{	string lola= "ERROR: libraryfunc_s ->"; lola+=*yylval.stringValue; lola+="<- As Argumnent ";
		yyerror(lola);}

		//enterScopeSpace();//------------------------S
		bes=true;
	}

}
#line 2637 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 902 "delete2.y" /* yacc.c:1646  */
    {}
#line 2643 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 903 "delete2.y" /* yacc.c:1646  */
    {}
#line 2649 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 906 "delete2.y" /* yacc.c:1646  */
    {
		scope++;
		SymbolTableEntry * tmp = lookup_scope(scope,*yylval.stringValue,(symbol_t)666);
		SymbolTableEntry* entry;
		string msg;
		if(tmp != NULL){
		msg ="ERROR: bre8ikan arguments me idio onoma ->"+*yylval.stringValue+"<-";
		yyerror(msg);
		}else{
			if(containsLib(*yylval.stringValue)){
			msg= "ERROR: libraryfunc_s ->" + *yylval.stringValue + "<- As Argumnent ";
			yyerror(msg);
			}else{
				if(scopeSpaceCounter % 2 != 0)
					enterScopeSpace();

				entry=insert_var(*yylval.stringValue,var_s);

				inCurrScopeOffset();

				entry->scopespace=currScopeSpace();
				entry->offset=currScopeOffset();

				SymbolTableEntry* func=lookupFunc(scope-1);

				//exitScopeSpace();//------------------------

				if(func != NULL){
				insertArguments(func->value.funcVal,entry->value.varVal);
				//printFunc(func->value.funcVal);
				}
			}
		}
		scope--;
	//enterScopeSpace();//------------------------
	bes=true;

}
#line 2692 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 943 "delete2.y" /* yacc.c:1646  */
    {}
#line 2698 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 944 "delete2.y" /* yacc.c:1646  */
    {}
#line 2704 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 947 "delete2.y" /* yacc.c:1646  */
    {

		emit(if_eq , (yyvsp[-1].exprNode) , newexpr_constbool(1),(expr*)0, currQuad+2,yylineno);

		(yyval.intValue) = currQuad;

		emit(jump, (expr*)0, (expr*)0, (expr*)0,-21,yylineno);
}
#line 2717 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 956 "delete2.y" /* yacc.c:1646  */
    {
	(yyval.intValue) = currQuad;
	emit(jump, (expr*)0, (expr*)0, (expr*)0,-21,yylineno);
}
#line 2726 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 961 "delete2.y" /* yacc.c:1646  */
    {cout<<"apo ifstmt se ( expr ) stmt \n";
	patchLabel((yyvsp[-1].intValue),currQuad);
	(yyval.Stmt2)=(yyvsp[0].Stmt2);
}
#line 2735 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 966 "delete2.y" /* yacc.c:1646  */
    {cout<<"apo ifstmt se if ( expr ) stmt Else stmt \n";
	patchLabel((yyvsp[-3].intValue),(yyvsp[-1].intValue)+1);
	patchLabel((yyvsp[-1].intValue),currQuad);

	(yyval.Stmt2) = new stmtStruct();

		if((yyvsp[-2].Stmt2)!=NULL  ){

			for(auto it = (yyvsp[-2].Stmt2)->breakList.begin();it!=(yyvsp[-2].Stmt2)->breakList.end();it++){
				cout<<*it<<endl;
				(yyval.Stmt2)->breakList.push_front(*it);
			}
			for(auto it = (yyvsp[-2].Stmt2)->continueList.begin();it!=(yyvsp[-2].Stmt2)->continueList.end();it++){
				cout<<*it<<endl;
				(yyval.Stmt2)->continueList.push_front(*it);
			}
}

if((yyvsp[0].Stmt2)!=NULL ){

		for(auto it = (yyvsp[0].Stmt2)->breakList.begin();it!=(yyvsp[0].Stmt2)->breakList.end();++it){
			cout<<*it<<endl;
			(yyval.Stmt2)->breakList.push_front(*it);
		}
		for(auto it = (yyvsp[0].Stmt2)->continueList.begin();it!=(yyvsp[0].Stmt2)->continueList.end();it++){
			cout<<*it<<endl;
			(yyval.Stmt2)->continueList.push_front(*it);
		}
}

}
#line 2771 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 999 "delete2.y" /* yacc.c:1646  */
    {++loopcounter;
}
#line 2778 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 1002 "delete2.y" /* yacc.c:1646  */
    {
	--loopcounter;
}
#line 2786 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 1006 "delete2.y" /* yacc.c:1646  */
    {
	(yyval.Stmt2) = (yyvsp[-1].Stmt2);
}
#line 2794 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 1010 "delete2.y" /* yacc.c:1646  */
    {	cout<<" WHILESTART SE WHILE "<<endl;
	(yyval.intValue) = currQuad;
}
#line 2802 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 1014 "delete2.y" /* yacc.c:1646  */
    {cout<<"apo whilestmt while ( expr ) stmt \n";
	emit(if_eq,(yyvsp[-1].exprNode),newexpr_constbool(1),(expr*)0,currQuad+2,yylineno);
	(yyval.intValue) = currQuad;
	emit(jump,(expr*)0,(expr*)0,(expr*)0,-21,yylineno);
}
#line 2812 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 1020 "delete2.y" /* yacc.c:1646  */
    {	cout<<" whilestart whilecond loopstmt "<<endl;
	emit(jump, (expr*)0,(expr*)0,(expr*)0,(yyvsp[-2].intValue),yylineno);
	patchLabel((yyvsp[-1].intValue),currQuad);
	//patchLabel( ,currQuad);
	//patchLabel( ,$1);

	for(auto it = (yyvsp[0].Stmt2)->breakList.begin();it!=(yyvsp[0].Stmt2)->breakList.end();it++ ){
		patchLabel(*it, currQuad);		
	}
	for(auto it = (yyvsp[0].Stmt2)->continueList.begin();it!=(yyvsp[0].Stmt2)->continueList.end();it++){
		patchLabel(*it , (yyvsp[-2].intValue));
	}
}
#line 2830 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 1035 "delete2.y" /* yacc.c:1646  */
    {	cout<<" Se N "<<endl;
	(yyval.intValue) = currQuad;
	emit(jump,(expr*)0,(expr*)0,(expr*)0,-21,yylineno);
}
#line 2839 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 1041 "delete2.y" /* yacc.c:1646  */
    {cout<<" Se M "<<endl;
	(yyval.intValue) = currQuad;
}
#line 2847 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 1046 "delete2.y" /* yacc.c:1646  */
    {
	cout<<"APO forprefix SE \n";
	(yyval.forprefix2) = new forStruct();
	(yyval.forprefix2)->test=(yyvsp[-2].intValue);
	(yyval.forprefix2)->enter = currQuad;
	emit(if_eq,(yyvsp[-1].exprNode),newexpr_constbool(1),(expr*)0,-21,yylineno);
}
#line 2859 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 1055 "delete2.y" /* yacc.c:1646  */
    {cout<<"apo forstmt se for ( elist semicolon expr Semicolon elist) stmt \n";
	patchLabel((yyvsp[-6].forprefix2)->enter,(yyvsp[-2].intValue)+1);
	patchLabel((yyvsp[-5].intValue),currQuad);
	patchLabel((yyvsp[-2].intValue),(yyvsp[-6].forprefix2)->test);
	patchLabel((yyvsp[0].intValue),(yyvsp[-5].intValue)+1);

	for(auto it = (yyvsp[-1].Stmt2)->breakList.begin();it!=(yyvsp[-1].Stmt2)->breakList.end();it++){
			patchLabel(*it,currQuad);
	}
	for(auto it = (yyvsp[-1].Stmt2)->continueList.begin();it!=(yyvsp[-1].Stmt2)->continueList.end();it++){
			patchLabel(*it,(yyvsp[-5].intValue)+1);
	}
	(yyval.Stmt2)=(yyvsp[-1].Stmt2);
}
#line 2878 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 1071 "delete2.y" /* yacc.c:1646  */
    {cout<<"apo returnstmt se Return Semicolon \n";
	if(currScopeSpace()!=functionlocal){
		yyerror("Return statement out of function");}
	emit(ret,(expr*)0,(expr*)0,(expr*)0,-21,yylineno);
	}
#line 2888 "delete2.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 1076 "delete2.y" /* yacc.c:1646  */
    {cout<<"apo returnstmt se Return expr Semicolon \n";
	if(currScopeSpace()!=functionlocal){
		yyerror("Return statement out of function");}
	emit(ret,(yyvsp[-1].exprNode),(expr*)0,(expr*)0,-21,yylineno);
	}
#line 2898 "delete2.tab.c" /* yacc.c:1646  */
    break;


#line 2902 "delete2.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 1083 "delete2.y" /* yacc.c:1906  */

int yyerror(string  yaccProvidedMessage){
//cout<<"error sto line "<<yylineno<<" before token "<<yytext<<endl;
cout<<endl<<yaccProvidedMessage<<" at line "<<yylineno<<" before token: ->"<<yytext<<"<-    <---ERROR "<<endl<<endl;
//exit(-1);
}
	void pray_start(){
		scopeTable =  vector<SymbolTableEntry*>();

		for(int i=0;i<1500;i++){
			scopeTable.push_back(NULL);
		}
		table = create();
	insert_fun("print" ,libraryfunc_s );
	insert_fun("input" ,libraryfunc_s );
	insert_fun("tableindices" ,libraryfunc_s );
	insert_fun("tablelength" ,libraryfunc_s );
	insert_fun("tablecopy" ,libraryfunc_s );
	insert_fun("totalarguments" ,libraryfunc_s );
	insert_fun("argument" ,libraryfunc_s );
	insert_fun("typeof" ,libraryfunc_s );
	insert_fun("strtonum" ,libraryfunc_s);
	insert_fun("sqrt" ,libraryfunc_s );
	insert_fun("cos" ,libraryfunc_s );
	insert_fun("sin" ,libraryfunc_s );
}

void print_table(){
		cout<<"-------------------------||--------------------------------- \n";
		for(auto it = scopeTable.begin();it!=scopeTable.end();it++ ){
		if(*it!=NULL)
				for(; *it!=NULL; (*it)=(*it)->nextscope )	{
				cout<<"Is Active: "<<(*it)->isActive<<" || ";

				if((*it)->type==1)
					cout<<"Scope: "<<(*it)->value.funcVal->scope<<" || ";
				else
					cout<<"Scope: "<<(*it)->value.varVal->scope<<" || ";

				if((*it)->type ==1 ||(*it)->type ==2 ){
				cout<<"Name: "<<(*it)->value.funcVal->name<<" || ";
				cout<<"Line: "<<(*it)->value.funcVal->line<<" || ";
				}
					else{
				cout<<"Name: "<<(*it)->value.varVal->name<<" || ";
				cout<<"Line: "<<(*it)->value.varVal->line<<" || ";
				cout<<"SCOPESPACE: "<<(*it)->scopespace<<" || ";
				if( (*it)->type!=1 && (*it)->type!=2)
					cout<<"OFFSET: "<<(*it)->offset<<" || ";
				}
				switch( (*it)->type){
				case libraryfunc_s:
					cout<<"Type: "<<"libraryfunc_s"<<endl;
					break;
				case var_s:
					cout<<"Type: "<<"var_s"<<endl;
					break;
			/*	case var_s:
					cout<<"Type: "<<"LOCAL"<<endl;
					break;*/
				case programfunc_s:
					cout<<"Type: "<<"programfunc_s || ";
						if( (*it)->value.funcVal->headArgument ==NULL )
								cout<<"No args";
						if( (*it)->value.funcVal->headArgument !=NULL ){
							Variable* tmp= (*it)->value.funcVal->headArgument;
							cout<<"Arguments: ";
							for(;tmp!=NULL;tmp=tmp->nextArgument){
									if(tmp->nextArgument!= NULL)
										cout<<tmp->name<<" , ";
									else
										cout<<tmp->name;
							}
					}
						cout<<endl;
					break;
				//case var_s:
				//cout<<"Type: "<<"var_s "<<endl;
				//break;
				}
			}
		}
	}

int main(int argc, char **argv ){
if(argc>1){
	if(!(yyin = fopen(argv[1],"r") )){
		fprintf(stderr , "Cannot read file %s ",argv[1]);
		return 1;
	}
}
else
yyin =  stdin;
pray_start();
yyparse();
printQuads();
print_table();
generate();
patch_incomplete_jumps();
printInstructions();
WriteBinary();
cout<<"TELOSSSS TO STIBA SIZE EINAI : "<< OffsetStack.size()<<endl;
return 0;
}
