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
#line 14 "config.y" /* yacc.c:339  */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* Avoid warnings for undeclared items */

extern	char	*yytext;
#include ".yyleng"
extern	int	yylex(void);



/********************************************************************************/
/*										*/
/*			Start of Definitions					*/
/*										*/
/********************************************************************************/

#define	NIL	(struct dev_ent *)0x00

#define	CONFC	 "conf.c"		/* Name of .c output			*/
#define CONFH	 "conf.h"		/* Name of .h output			*/
#define	CONFHREF "<conf.h>"		/* How conf.h referenced		*/
#define	INFILE	 "Configuration"	/* Name of input file			*/
#define	MAXNAME  16			/* Max length of names			*/

#define	NDEVS		250		/* Max devices				*/
#define	NTYPES		250		/* Max device types			*/

int	linectr = 1;

FILE	*confc;
FILE	*confh;

int	brkcount = 0;			/* Count of %% separators till now in	*/
					/*  the input file			*/
char	*doing = "device type declarations";

struct	dev_ent	{			/* Entry for a device or device type	*/
	char	name[MAXNAME];		/* device name (unused in a type)	*/
	char	tname[MAXNAME];		/* Type name				*/
	char	ison[MAXNAME];		/* Name is "on" XXX			*/
	int	tindex;			/* Index in dtypes (unused in a type)	*/
	int	csr;			/* Control Status Register addr		*/
	int	irq;			/* interrupt request			*/
	char	intr[MAXNAME];		/* interrupt function name		*/
	char	init[MAXNAME];		/* init function name			*/
	char	open[MAXNAME];		/* open function name			*/
	char	close[MAXNAME];		/* close function name			*/
	char	read[MAXNAME];		/* read function name			*/
	char	write[MAXNAME];		/* write function name			*/
	char	control[MAXNAME];	/* control function name		*/
	char	seek[MAXNAME];		/* seek function name			*/
	char	getc[MAXNAME];		/* getc function name			*/
	char	putc[MAXNAME];		/* putc function name			*/
	int	minor;			/* In a device, the minor device	*/
					/*  assigned to the device 0,1,...	*/
					/*  in a type, the next minor number	*/
					/*  to assign				*/
};
struct	dev_ent		dtypes[NTYPES];/* Table of all device types		*/
int	ntypes	= 0;			/* Number of device types found		*/

struct	dev_ent		devs[NDEVS];	/* Table of all devices			*/
int	ndevs = 0;			/* Number of devices found		*/

char *devstab[] = {
	"/* Device table entry */",
	"struct\tdentry\t{",
	"\tint32   dvnum;",
	"\tint32   dvminor;",
	"\tchar    *dvname;",
	"\tdevcall (*dvinit) (struct dentry *);",
	"\tdevcall (*dvopen) (struct dentry *, char *, char *);",
	"\tdevcall (*dvclose)(struct dentry *);",
	"\tdevcall (*dvread) (struct dentry *, void *, uint32);",
	"\tdevcall (*dvwrite)(struct dentry *, void *, uint32);",
	"\tdevcall (*dvseek) (struct dentry *, int32);",
	"\tdevcall (*dvgetc) (struct dentry *);",
	"\tdevcall (*dvputc) (struct dentry *, char);",
	"\tdevcall (*dvcntl) (struct dentry *, int32, int32, int32);",
	"\tvoid    *dvcsr;",
	"\tvoid    (*dvintr)(void);",
	"\tbyte    dvirq;",
	"};\n",
	"extern	struct	dentry	devtab[]; /* one entry per device */",
	NULL
};

char	saveattrid[MAXNAME];		/* Holds the IDENT from an attribute	*/

/********************************************************************************/
/*										*/
/*			       Function prototypes				*/
/*										*/
/********************************************************************************/

void	addattr(int, int);
int	addton(char *);
int	config_atoi(char *, int);
void	devisid(char *);
void	devonid(char *);
void	getattrid(char *);
void	newdev(char *);
int	newtype(char *);
void	yyerror(char *);



#line 178 "y.tab.c" /* yacc.c:339  */

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
    DEFBRK = 258,
    IFBRK = 259,
    COLON = 260,
    OCTAL = 261,
    INTEGER = 262,
    IDENT = 263,
    CSR = 264,
    IRQ = 265,
    INTR = 266,
    INIT = 267,
    OPEN = 268,
    CLOSE = 269,
    READ = 270,
    WRITE = 271,
    SEEK = 272,
    CONTROL = 273,
    IS = 274,
    ON = 275,
    GETC = 276,
    PUTC = 277
  };
#endif
/* Tokens.  */
#define DEFBRK 258
#define IFBRK 259
#define COLON 260
#define OCTAL 261
#define INTEGER 262
#define IDENT 263
#define CSR 264
#define IRQ 265
#define INTR 266
#define INIT 267
#define OPEN 268
#define CLOSE 269
#define READ 270
#define WRITE 271
#define SEEK 272
#define CONTROL 273
#define IS 274
#define ON 275
#define GETC 276
#define PUTC 277

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);



/* Copy the second part of user declarations.  */

#line 270 "y.tab.c" /* yacc.c:358  */

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   39

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  23
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  20
/* YYNRULES -- Number of rules.  */
#define YYNRULES  35
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  58

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   277

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
      15,    16,    17,    18,    19,    20,    21,    22
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,   133,   133,   142,   143,   146,   149,   152,   153,   156,
     159,   162,   163,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   180,   183,   193,   194,   197,
     200,   203,   206,   209,   212,   215
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "DEFBRK", "IFBRK", "COLON", "OCTAL",
  "INTEGER", "IDENT", "CSR", "IRQ", "INTR", "INIT", "OPEN", "CLOSE",
  "READ", "WRITE", "SEEK", "CONTROL", "IS", "ON", "GETC", "PUTC",
  "$accept", "configuration", "devtypes", "devtype", "tname", "dev_tlist",
  "theader", "tonid", "attr_list", "attr", "id", "number", "devices",
  "device", "dheader", "dname", "devis", "devisid", "devon", "devonid", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277
};
# endif

#define YYPACT_NINF -14

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-14)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -14,    10,    22,   -14,   -14,   -14,   -14,     6,    16,     8,
     -14,   -14,   -14,    12,    18,     8,   -14,    -9,    19,    13,
     -14,   -14,   -14,    -9,    25,    25,    26,    26,    26,    26,
      26,    26,    26,    26,    26,    26,   -14,   -14,   -14,    27,
     -14,    -9,   -14,   -14,   -14,   -14,   -14,   -14,   -14,   -14,
     -14,   -14,   -14,   -14,   -14,   -14,   -14,   -14
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     1,    27,     6,     4,     0,     2,     0,
      31,    28,    11,     0,     0,     5,    11,    29,     0,     0,
      10,     9,    11,     7,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    12,    33,    32,     0,
      30,     8,    26,    13,    14,    25,    15,    18,    16,    17,
      21,    22,    23,    24,    19,    20,    35,    34
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -14,   -14,   -14,   -14,   -14,   -14,    21,   -14,     7,   -14,
     -13,    14,   -14,   -14,   -14,   -14,   -14,   -14,   -14,   -14
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,     6,     7,    15,    16,    21,    17,    36,
      46,    43,     8,    11,    12,    13,    19,    38,    40,    57
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
       3,     9,    34,    35,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    23,    10,     4,    20,    37,    14,    41,
       5,    18,    42,    39,    45,    56,    22,     0,     0,    44
};

static const yytype_int8 yycheck[] =
{
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
       0,     5,    21,    22,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    16,     8,     3,     8,     8,    20,    22,
       8,    19,     7,    20,     8,     8,    15,    -1,    -1,    25
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    24,    25,     0,     3,     8,    26,    27,    35,     5,
       8,    36,    37,    38,    20,    28,    29,    31,    19,    39,
       8,    30,    29,    31,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    21,    22,    32,     8,    40,    20,
      41,    31,     7,    34,    34,     8,    33,    33,    33,    33,
      33,    33,    33,    33,    33,    33,     8,    42
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    23,    24,    25,    25,    26,    27,    28,    28,    29,
      30,    31,    31,    32,    32,    32,    32,    32,    32,    32,
      32,    32,    32,    32,    32,    33,    34,    35,    35,    36,
      37,    38,    39,    40,    41,    42
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     0,     2,     3,     1,     2,     3,     2,
       1,     0,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     1,     1,     0,     2,     2,
       3,     1,     2,     1,     2,     1
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
        case 3:
#line 142 "config.y" /* yacc.c:1646  */
    { doing = "device definitions"; }
#line 1375 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 149 "config.y" /* yacc.c:1646  */
    { (yyval) = newtype(yytext); }
#line 1381 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 156 "config.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 1387 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 159 "config.y" /* yacc.c:1646  */
    { (yyval) = addton(yytext); }
#line 1393 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 166 "config.y" /* yacc.c:1646  */
    { addattr(CSR,    (yyvsp[0]));	}
#line 1399 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 167 "config.y" /* yacc.c:1646  */
    { addattr(IRQ,    (yyvsp[0]));	}
#line 1405 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 168 "config.y" /* yacc.c:1646  */
    { addattr(INTR,    0);	}
#line 1411 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 169 "config.y" /* yacc.c:1646  */
    { addattr(OPEN,    0);	}
#line 1417 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 170 "config.y" /* yacc.c:1646  */
    { addattr(CLOSE,   0);	}
#line 1423 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 171 "config.y" /* yacc.c:1646  */
    { addattr(INIT,    0);	}
#line 1429 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 172 "config.y" /* yacc.c:1646  */
    { addattr(GETC,    0);	}
#line 1435 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 173 "config.y" /* yacc.c:1646  */
    { addattr(PUTC,    0);	}
#line 1441 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 174 "config.y" /* yacc.c:1646  */
    { addattr(READ,    0);	}
#line 1447 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 175 "config.y" /* yacc.c:1646  */
    { addattr(WRITE,   0);	}
#line 1453 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 176 "config.y" /* yacc.c:1646  */
    { addattr(SEEK,    0);	}
#line 1459 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 177 "config.y" /* yacc.c:1646  */
    { addattr(CONTROL, 0);	}
#line 1465 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 180 "config.y" /* yacc.c:1646  */
    { (yyval) = 0; getattrid(yytext); }
#line 1471 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 183 "config.y" /* yacc.c:1646  */
    { (yyval) = config_atoi(yytext, yyleng); }
#line 1477 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 193 "config.y" /* yacc.c:1646  */
    { doing = "interface types"; }
#line 1483 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 203 "config.y" /* yacc.c:1646  */
    { newdev(yytext); }
#line 1489 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 209 "config.y" /* yacc.c:1646  */
    { devisid(yytext); }
#line 1495 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 215 "config.y" /* yacc.c:1646  */
    { devonid(yytext); }
#line 1501 "y.tab.c" /* yacc.c:1646  */
    break;


#line 1505 "y.tab.c" /* yacc.c:1646  */
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
#line 218 "config.y" /* yacc.c:1906  */


#include "lex.yy.c"


/************************************************************************/
/*									*/
/* main  -  main program: parse arguments, invoke the parser, and	*/
/*		write the conf.h and conf.c files			*/
/*									*/
/************************************************************************/


int main(int argc, char **argv) {
	int n, i, j, l, fcount;
	struct dev_ent *s;
	int   verbose = 0;
	char *p;
	int  c;

	if ( argc > 1 && (strncmp("-v", argv[1], 2) == 0) ) {
		argc--;
		argv++;
		verbose++;
	}

	if ( argc > 4 ) {
		fprintf(stderr, "use: config [-v] [input_file] [conf.c] [conf.h]\n");
		exit(1);
	}

	if (verbose) { printf("Opening input file...\n"); }

	if (argc >= 2) {
		if (freopen(argv[1], "r", stdin) == NULL) {
			fprintf(stderr, "Can't open %s\n", argv[1]);
			exit(1);
		}
	}
	else {	/* try to open Configuration file */
		if (freopen(INFILE, "r", stdin) == NULL) {
			fprintf(stderr, "Can't open %s\n", INFILE);
			exit(1);
		}
	}

	/****************************************************************/
	/*								*/
	/*		Parse the Configuration file			*/
	/*								*/
	/****************************************************************/


	if (verbose) { printf("Parsing configuration specs...\n"); }

	if ( (n = yyparse()) != 0 ) { exit(n); }

	/* Open conf.h and conf.c for writing */

	if (verbose) { printf("Opening output files...\n"); }

	if (argc >= 3) {
		if ( (confc = fopen(argv[2],"w") ) == NULL) {
			fprintf(stderr, "Can't write on %s\n", argv[2]);
			exit(1);
		}
	}
	else { 	/* try to open conf.c file */
		if ( (confc = fopen(CONFC,"w") ) == NULL) {
			fprintf(stderr, "Can't write on %s\n", CONFC);
			exit(1);
		}
	}

	if (argc >= 4) {
		if ( (confh = fopen(argv[3],"w") ) == NULL) {
			fprintf(stderr, "Can't write on %s\n", argv[3]);
			exit(1);
		}
	}
	else { 	/* try to open conf.h file */
		if ( (confh = fopen(CONFH,"w") ) == NULL) {
			fprintf(stderr, "Can't write on %s\n", CONFH);
			exit(1);
		}
	}

	/****************************************************************/
	/*								*/
	/*			produce conf.h				*/
	/*								*/
	/****************************************************************/


	fprintf(confh, "/* conf.h (GENERATED FILE; DO NOT EDIT) */\n\n");

	if (verbose) { printf("Writing output...\n"); }

	fprintf(confh, "/* Device switch table declarations */\n\n");

	for (i = 0; (p = devstab[i]) != NULL; i++) {
		fprintf(confh, "%s\n", p);
	}

	fprintf(confh, "\n");

	/* write device declarations and definitions */

	fprintf(confh, "/* Device name definitions */\n\n");
	for (i = 0; i<ndevs; i++) {
		s = &devs[i];
		fprintf(confh, "#define %-20s%2d\t/* type %-8s */\n",
			s->name, i, s->tname);
	}
	fprintf(confh, "\n");

	/* write count of device types */

	fprintf(confh, "/* Control block sizes */\n\n");
	for (i = 0; i < ntypes;  i++) {
		s = &dtypes[i];
		if (s->minor > 0) {
			fprintf(confh, "#define\tN%s\t%d\n",
				s->tname, s->minor);
		}
	}

	fprintf(confh, "\n");

	if (ndevs > 0) { fprintf(confh, "#define NDEVS %d\n", ndevs); }

	/* Copy definitions to output */

	if (brkcount >= 4 && verbose) {
		printf("Copying definitions to %s...\n", CONFH);
	}

	if (brkcount >= 2) {
		while ( (c = input()) > 0) {	/* lex input function	*/
			putc(c, confh);
		}
	}
	fclose(confh);


	/****************************************************************/
	/*								*/
	/*			produce conf.c				*/
	/*								*/
	/****************************************************************/


	fprintf(confc, "/* conf.c (GENERATED FILE; DO NOT EDIT) */\n\n");
	fprintf(confc, "#include <xinu.h>\n\n");
	fprintf(confc, "\n");

	fprintf(confc, "extern\tdevcall\tioerr(void);\n");
	fprintf(confc, "extern\tdevcall\tionull(void);\n\n");

	/* produce devtab (giant I/O switch table) */
	fprintf(confc, "/* Device independent I/O switch */\n\n");
	if (ndevs > 0)
	{
		fprintf(confc, "struct	dentry	devtab[NDEVS] =\n{\n");
		fprintf(confc, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n",
			"/**",
			" * Format of entries is:",
			" * dev-number, minor-number, dev-name,",
			" * init, open, close,",
			" * read, write, seek,",
			" * getc, putc, control,",
			" * dev-csr-address, intr-handler, irq",
			" */");
	}

	for (i=0; i<ndevs; i++) {
		s = &devs[i];
		fprintf(confc, "/* %s is %s */\n", s->name, s->tname);
		fprintf(confc, "\t{ %d, %d, \"%s\",\n", i, s->minor, s->name);
		fprintf(confc, "\t  (void *)%s, (void *)%s, (void *)%s,\n",
			s->init, s->open, s->close);
		fprintf(confc, "\t  (void *)%s, (void *)%s, (void *)%s,\n",
			s->read, s->write, s->seek);
		fprintf(confc, "\t  (void *)%s, (void *)%s, (void *)%s,\n",
			s->getc, s->putc, s->control);
		fprintf(confc, "\t  (void *)0x%x, (void *)%s, %d }",
			s->csr, s->intr, s->irq);
		if (i< ndevs-1) {
			fprintf(confc, ",\n\n");
		} else {
			fprintf(confc, "\n};");
		}
	}

	/* we must guarantee conf.c written later than conf.h for make */
	fprintf(confc, "\n");
	fclose(confc);

	/* finish up and write report for user if requested */
	if (verbose) {
		printf("Configuration complete. Number of devs=%d:\n", ndevs);
		for (i=0; i<ndevs; i++) {
			s = &devs[i];
			printf("Device %s (on %s)\n", s->name, s->ison);
			printf("    csr=0x%04x, irq=0x%04x, minor=%d\n",
				s->csr, s->irq, s->minor);
		}
	}
}

/************************************************************************/
/*									*/
/* addattr - add a new attribute spec to current type/device description*/
/*		tok: token type (attribute type)			*/
/*		val: symbol number of value				*/
/*									*/
/************************************************************************/

void	addattr(int tok, int val) {
	struct dev_ent *s;
	char *c;

	if (brkcount == 0) {
		/* Doing types */
		s = &dtypes[ntypes-1];
	} else {
		/* Doing devices */
		s = &devs[ndevs-1];
	}

	switch (tok) {
	case CSR:	s->csr = val;			break;
	case IRQ:	s->irq = val;			break;
	case INTR:	strcpy(s->intr, saveattrid);	break;
	case READ:	strcpy(s->read, saveattrid);	break;
	case WRITE:	strcpy(s->write,saveattrid);	break;
	case GETC:	strcpy(s->getc, saveattrid);	break;
	case PUTC:	strcpy(s->putc, saveattrid);	break;
	case OPEN:	strcpy(s->open, saveattrid);	break;
	case CLOSE:	strcpy(s->close,saveattrid);	break;
	case INIT:	strcpy(s->init, saveattrid);	break;
	case SEEK:	strcpy(s->seek, saveattrid);	break;
	case CONTROL:	strcpy(s->control,saveattrid);	break;
	default:	fprintf(stderr, "Internal error 1\n");
	}
}


/************************************************************************/
/*									*/
/* addton -- add an "on XXX" to the current type			*/
/*									*/
/************************************************************************/

int	addton(char *tonid) {
	int	currtype;		/* The current type		*/

	if (strlen(tonid) >= MAXNAME) {
		fprintf(stderr,"string %s is too long on line %d\n",
				tonid, linectr);
		exit(1);
	}
	currtype = ntypes - 1;
	strcpy(dtypes[currtype].ison, tonid);

	return currtype;
}


/************************************************************************/
/*									*/
/* config_atoi - convert an ascii string of text to an integer,		*/
/*			honoring octal, decimal, and hex		*/
/*									*/
/************************************************************************/

int	config_atoi(char *p, int len) {
	int base, rv;

	if (*p == '0')
	{
		++p;
		--len;
		if (*p == 'x' || *p == 'X')
		{
			++p; --len; /* skip 'x' */
			base = 16;
		}
		else
		{
			base = 8;
		}
	}
	else
	{
		base = 10;
	}

	rv = 0;
	for (; len > 0; ++p, --len)
	{
		rv *= base;
		if      (isdigit(*p)) { rv += *p - '0'; }
		else if (isupper(*p)) { rv += *p - 'A' + 10; }
		else                  { rv += *p - 'a' + 10; }
	}

	return rv;
}

/************************************************************************/
/*									*/
/* devisid -- add an "is XXX" to the current device			*/
/*									*/
/************************************************************************/

void	devisid(char *tname) {
	int	currdev;		/* The current device		*/
	int	i;

	if (strlen(tname) >= MAXNAME) {
		fprintf(stderr,"string %s is too long on line %d\n",
				tname, linectr);
		exit(1);
	}
	/* Verify the type exists */

	for (i=0; i<ntypes; i++) {
		if (strcmp(tname, dtypes[i].tname) == 0) {
			break;
		}
	}
	if (i >= ntypes) {
		fprintf(stderr, "Illegal type name %s on line %d\n",
				tname, linectr);
		exit(1);
	}
	currdev = ndevs - 1;
	strcpy(devs[currdev].tname, tname);

	return;
}


/************************************************************************/
/*									*/
/* devonid -- add an "on XXX" to the current device, lookup the type,	*/
/*		and copy attributes into the device from the type	*/
/*									*/
/************************************************************************/

void	devonid(char *onname) {
	int	currdev;		/* The current device		*/
	int	i;
	struct	dev_ent	*dptr;		/* Pointer to current device	*/
	struct	dev_ent	*tptr;		/* Pointer to a type		*/
	char	tmp[MAXNAME];		/* Holds the device name during	*/
					/*   copy			*/

	if (strlen(onname) >= MAXNAME) {
		fprintf(stderr,"string %s is too long on line %d\n",
				onname, linectr);
		exit(1);
	}
	if (ndevs <=0) {
		fprintf(stderr,"Internal error 3\n");
		exit(1);
	}
	currdev = ndevs - 1;
	dptr = &devs[currdev];

	strcpy(dptr->ison, onname);

	/* Lookup the device type */

	for (i=0; i<ntypes; i++) {
		tptr = &dtypes[i];
		if ( (strcmp(dptr->tname,tptr->tname) == 0 ) &&
		     (strcmp(dptr->ison, tptr->ison)  == 0 )  ){

			/* The specified type matches the ith entry, so	*/
			/*  set all attributes equal to the ones in the	*/
			/*  type definition.				*/

			strcpy(tmp, dptr->name);
			bcopy (tptr, dptr, sizeof(struct dev_ent));
			/* Increment the minor device number for the	*/
			/*  next time the type is used			*/
			tptr->minor++;
			strcpy(dptr->name, tmp);
			return;
		}
	}

	fprintf(stderr, "Ileagal device specification on line %d\n", linectr);
	exit(1);
}


/************************************************************************/
/*									*/
/* getattrid -- pick up and save the attribute string from an id	*/
/*									*/
/************************************************************************/

void	getattrid(char *str) {

	if (strlen(str) >= MAXNAME) {
		fprintf(stderr,"atribute string %s is too long on line %d\n",
				str, linectr);
		exit(1);
	}
	strcpy(saveattrid, str);
	return;
}


/************************************************************************/
/*									*/
/* newdev -- allocate an entry in devs, initialize, and fill in the name*/
/*									*/
/************************************************************************/

void	newdev(char *name) {

	struct	dev_ent	*dptr;		/* Ptr. to an entry in devs	*/
	int	i;

	if (ndevs >= NDEVS) {
		fprintf(stderr,"Too many devices on line %d", linectr);
		exit(1);
	}
	if (strlen(name) >= MAXNAME) {
		fprintf(stderr,"Device name %s is too long on line %d\n",
				name, linectr);
		exit(1);
	}

	/* Verify that the device name is unique */

	for (i=0; i<ndevs; i++) {
		if (strcmp(name, devs[i].name) == 0) {
			fprintf(stderr, "Duplicate device name %s on line %d\n",
				name, linectr);
			exit(1);
		}
	}

	dptr = &devs[ndevs];

	/* Initialize fields in the entry */

	bzero((void *)dptr, sizeof(struct dev_ent));
	strcpy(dptr->name,	 name);
	ndevs++;
	return;
}


/************************************************************************/
/*									*/
/* newtype -- allocate an entry in the type array and fill in the name	*/
/*									*/
/************************************************************************/

int	newtype(char *name) {

	struct	dev_ent	*dptr;		/* Ptr. to an entry in dtypes	*/
	int	i;			/* Index into the type table	*/

	if (ntypes >= NTYPES) {
		fprintf(stderr,"Too many types on line %d", linectr);
		exit(1);
	}
	if (strlen(name) >= MAXNAME) {
		fprintf(stderr,"Type name %s is too long on line %d\n",
				name, linectr);
		exit(1);
	}

	/* Verify that the type name is unique */

	for (i=0; i<ntypes; i++) {
		if (strcmp(name, dtypes[i].tname) == 0) {
			fprintf(stderr, "Duplicate type name %s on line %d\n",
				name, linectr);
			exit(1);
		}
	}

	dptr = &dtypes[ntypes];

	/* Initialize fields in the entry */

	bzero((void *)dptr, sizeof(struct dev_ent));
	strcpy(dptr->tname,	 name);
	strncpy(dptr->intr,	"ioerr", 5);
	strncpy(dptr->init,	"ioerr", 5);
	strncpy(dptr->open,	"ioerr", 5);
	strncpy(dptr->close,	"ioerr", 5);
	strncpy(dptr->read,	"ioerr", 5);
	strncpy(dptr->write,	"ioerr", 5);
	strncpy(dptr->control,	"ioerr", 5);
	strncpy(dptr->seek,	"ioerr", 5);
	strncpy(dptr->getc,	"ioerr", 5);
	strncpy(dptr->putc,	"ioerr", 5);

	return ntypes++;
}


/************************************************************************/
/*									*/
/* yyerror - print an error message with the line number		*/
/*									*/
/************************************************************************/

void yyerror(char *s) {

	fprintf(stderr, "Syntax error in %s on line %d\n", doing, linectr);
}
