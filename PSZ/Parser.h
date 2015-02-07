/*
 * Parser.h
 *
 *  Created on: Feb 3, 2015
 *      Author: Kevin-Lenovo
 */

#ifndef PARSER_H_
#define PARSER_H_

/**
 * Represents a statement type.
 */
typedef enum {
	ST_CAST,            // Cast statement.
	ST_PRINT,           // Print statement.
	ST_INPUT,           // Input statement.
	ST_ASSIGNMENT,      // Assignment statement.
	ST_DECLARATION,     // Declaration statement.
	ST_IFTHENELSE,      // If/then/else statement.
	ST_SWITCH,          // Switch statement.
	ST_BREAK,           // Break statement.
	ST_RETURN,          // Return statement.
	ST_LOOP,            // Loop statement.
	ST_DEALLOCATION,    // Deallocation statement.
	ST_FUNCDEF,         // Function definition statement.
	ST_EXPR,            // Expression statement.
	ST_ALTARRAYDEF,     // Function definition statement.
} StmtType;

/**
 * Stores statement data.
 */
typedef struct {
	StmtType type; /**< The type of statement in \a node. */
	void *stmt;    /**< The statement. */
} StmtNode;

/**
 * Stores a list of statements.
 */
typedef struct {
	unsigned int num; /**< The number of statements. */
	StmtNode **stmts; /**< The array of statements. */
} StmtNodeList;

/**
 * Represents an expression type.
 */
typedef enum {
	ET_CAST,       /**< Cast expression. */
	ET_CONSTANT,   /**< Constant expression. */
	ET_IDENTIFIER, /**< Identifier expression. */
	ET_FUNCCALL,   /**< Function call expression. */
	ET_OP,         /**< Operation expression. */
	ET_IMPVAR      /**< \ref impvar "Implicit variable". */
} ExprType;

/**
 * Stores an expression.
 */
typedef struct {
	ExprType type; /**< The type of expression in \a expr. */
	void *expr;    /**< The expression. */
} ExprNode;

/**
 * Stores a list of expressions.
 */
typedef struct {
	unsigned int num; /**< The number of expressions. */
	ExprNode **exprs; /**< The array of statements. */
} ExprNodeList;

/**
 * Represents an identifier type.
 */
typedef enum {
	IT_DIRECT,  /**< Direct identifier. */
	IT_INDIRECT /**< Indirect identifier. */
} IdentifierType;

/**
 * Stores an identifier.
 */
typedef struct identifiernode {
	IdentifierType type;         /**< The type of identifier in \a id. */
	void *id;                    /**< The identifier. */
	char *fname;                 /**< The original file name. */
	unsigned int line;           /**< The original line number. */
	struct identifiernode *slot; /**< The slot to access. */
} IdentifierNode;

/**
 * Stores a list of identifiers.
 */
typedef struct {
	unsigned int num;     /**< The number of identifiers. */
	IdentifierNode **ids; /**< The array of identifiers. */
} IdentifierNodeList;

/**
 * Stores a code block.
 */
typedef struct {
	StmtNodeList *stmts; /**< The list of statements in the block. */
} BlockNode;

/**
 * Stores a list of code blocks.
 */
typedef struct {
	unsigned int num;   /**< The number of code blocks. */
	BlockNode **blocks; /**< The array of code blocks. */
} BlockNodeList;

/**
 * Represents a constant type.
 */
typedef enum {
	CT_INTEGER, /**< Integer constant. */
	CT_FLOAT,   /**< Decimal constant. */
	CT_BOOLEAN, /**< Boolean constant. */
	CT_STRING,  /**< String constant. */
	CT_NIL,     /**< Nil constant. */
	CT_ARRAY    /**< Array constant. */
} ConstantType;

/**
 * Stores constant data.
 */
typedef union {
	long long i; /**< Integer data. */
	float f;     /**< Decimal data. */
	char *s;     /**< String data. */
} ConstantData;

/**
 * Stores a constant.
 */
typedef struct {
	ConstantType type; /**< The type of constant in \a data. */
	ConstantData data; /**< The constant. */
} ConstantNode;

/**
 * Stores a function definition statement.
 */
typedef struct {
	IdentifierNode *scope;    /**< The scope of the function. */
	IdentifierNode *name;     /**< The name of the function. */
	IdentifierNodeList *args; /**< The names of the function arguments. */
	BlockNode *body;          /**< The body of the function. */
} FuncDefStmtNode;

/**
 * Stores an alternate array definition statement.
 */
typedef struct {
	IdentifierNode *name;   /**< The name of the array. */
	BlockNode *body;        /**< The body of the array definition. */
	IdentifierNode *parent; /**< An optional inherited array. */
} AltArrayDefStmtNode;

/**
 * Stores the main code block of a program.
 *
 * \note This could be represented with just a BlockNode, but it seems
 * significant enough to merit its own structure.
 */
typedef struct {
	BlockNode *block; /**< The first block of code to execute. */
} MainNode;

/**
 * Stores a variable type.
 */
typedef struct {
	ConstantType type; /**< The type variable. */
} TypeNode;

/**
 * Stores a cast statement.  This statement changes the type of a variable.
 */
typedef struct {
	IdentifierNode *target; /**< The name of the variable to cast. */
	TypeNode *newtype;      /**< The type to cast \a target to. */
} CastStmtNode;

/**
 * Stores a print statement.  This statement prints a list of expressions with
 * an optional newline.
 */
typedef struct {
	ExprNodeList *args; /**< The expressions to print. */
	int nonl;           /**< Whether to print an ending newline. */
} PrintStmtNode;

/**
 * Stores an input statement.  This statement accepts input from the user and
 * stores it in a variable.
 */
typedef struct {
	IdentifierNode *target; /**< The variable to store the input in. */
} InputStmtNode;

/**
 * Stores an assignment statement.  This statement stores an evaluated
 * expression in a variable.
 */
typedef struct {
	IdentifierNode *target; /**< The variable to store \a expr in. */
	ExprNode *expr;         /**< The expression to store. */
} AssignmentStmtNode;

/**
 * Stores a declaration statement.  This statement creates a new variable in a
 * given scope and optionally initializes it to an expression.
 *
 * \note Either provide \a expr OR \a type.  If both are provided, the result is
 * undefined.
 */
typedef struct {
	IdentifierNode *scope;  /**< The scope to create the variable in. */
	IdentifierNode *target; /**< The name of the variable to create. */
	ExprNode *expr;         /**< An optional initialization expression. */
	TypeNode *type;         /**< An optional initialization type. */
	IdentifierNode *parent; /**< An optional inherited array. */
} DeclarationStmtNode;

/**
 * Stores an if/then/else statement.  This statement checks the value of the
 * \ref impvar "implicit variable" and executes the \c yes block if it can be
 * cast to true.  Else, the \c guards are evaluated and the corresponding code
 * in one of the \c blocks is executed.  Finally, if none of these things occur,
 * the \c no block is executed.
 */
typedef struct {
	BlockNode *yes;        /**< The code to execute if \c IT is true. */
	BlockNode *no;         /**< The code to execute if nothing else does. */
	ExprNodeList *guards;  /**< The guards for the \c blocks. */
	BlockNodeList *blocks; /**< The code to execute if a guard is true. */
} IfThenElseStmtNode;

/**
 * Stores a switch statement.  This statement compares the value of the \ref
 * impvar "implicit variable" to each of the \a guards and executes the
 * respective block of code in \a blocks if they match.  If no matches are
 * found, the optional default block of code, \a def, is executed.
 */
typedef struct {
	ExprNodeList *guards;  /**< The expressions to evaluate. */
	BlockNodeList *blocks; /**< The blocks of code to execute. */
	BlockNode *def;        /**< An optional default block of code. */
} SwitchStmtNode;

/**
 * Stores a return statement.  This statement signals that control should be
 * returned to the caller with a status value.
 */
typedef struct {
	ExprNode *value; /**< The value to return. */
} ReturnStmtNode;

/**
 * Stores a loop statement.  This statement repeatedly executes its \a body
 * while \a guard evaluates to true, executing \a update at the end of each
 * cycle.
 */
typedef struct {
	IdentifierNode *name; /**< The name of the loop. */
	IdentifierNode *var;  /**< The variable to be updated. */
	ExprNode *guard;      /**< The expression to determine continuation. */
	ExprNode *update;     /**< The expression to update \a var with. */
	BlockNode *body;      /**< The code to execute at each iteration. */
} LoopStmtNode;

/**
 * Stores a deallocation statement.  This statement releases the resources used
 * by a variable.
 */
typedef struct {
	IdentifierNode *target; /**< The variable to deallocate. */
} DeallocationStmtNode;

/**
 * Stores a cast expression.  This expression evaluates an expression and casts
 * its value to a particular type.
 */
typedef struct {
	ExprNode *target;  /**< The expression to cast. */
	TypeNode *newtype; /**< The type to cast \a target to. */
} CastExprNode;

/**
 * Stores a function call expression.  This expression calls a named function
 * and evaluates to the return value of that function.
 */
typedef struct {
	IdentifierNode *scope; /**< The scope to call the function in. */
	IdentifierNode *name;  /**< The name of the function to call. */
	ExprNodeList *args;    /**< The arguments to supply the function. */
} FuncCallExprNode;

/**
 * Represents the type of operation an OpExprNode performs.
 */
typedef enum {
	OP_ADD,  /**< Addition. */
	OP_SUB,  /**< Subtraction. */
	OP_MULT, /**< Multiplication. */
	OP_DIV,  /**< Division. */
	OP_MOD,  /**< Modulo. */
	OP_MAX,  /**< Maximum. */
	OP_MIN,  /**< Minimum. */

	OP_AND,  /**< Logical AND. */
	OP_OR,   /**< Logical OR. */
	OP_XOR,  /**< Logical XOR. */
	OP_NOT,  /**< Logical NOT. */

	OP_EQ,   /**< Equality. */
	OP_NEQ,  /**< Inequality. */

	OP_CAT   /**< String concatenation. */
} OpType;

/**
 * Stores an operation expression.  This expression applies an operator to its
 * arguments.
 */
typedef struct  {
	OpType type;        /**< The type of operation to perform. */
	ExprNodeList *args; /**< The arguments to perform the operation on. */
} OpExprNode;

class Parser {
public:
	Parser();
	virtual ~Parser();
};

#endif /* PARSER_H_ */
