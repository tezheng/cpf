
// Generated from C:/Projects/cpf/Tools/idl\IDLParser.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"




class  IDLParser : public antlr4::Parser {
public:
  enum {
    Windows = 1, Darwin = 2, IMPORT = 3, STRUCT = 4, DEFAULT = 5, UNION = 6, 
    CALLBACK = 7, INTERFACE = 8, ENUM = 9, FLAGS = 10, MODULE = 11, FROM = 12, 
    AS = 13, In = 14, Out = 15, COLON = 16, SEMICOLON = 17, STAR = 18, SLASH = 19, 
    DOT = 20, COMMA = 21, EQUALS = 22, QUOTE = 23, SQUOTE = 24, LBRACE = 25, 
    RBRACE = 26, LPAREN = 27, RPAREN = 28, LBRACKET = 29, RBRACKET = 30, 
    LT = 31, GT = 32, PLUS = 33, MINUS = 34, LSHIFT = 35, RSHIFT = 36, PIPE = 37, 
    Const = 38, Void = 39, RESULT = 40, SUCCESS = 41, FAILURE = 42, CLASS_ID = 43, 
    STRING = 44, U8 = 45, S8 = 46, U16 = 47, S16 = 48, U32 = 49, S32 = 50, 
    U64 = 51, S64 = 52, F32 = 53, F64 = 54, IDENT = 55, DECIMAL_LIT = 56, 
    HEX_LIT = 57, BIN_LIT = 58, OCT_LIT = 59, STRING_LIT = 60, CHAR_LIT = 61, 
    FLOAT_LIT = 62, WHITE_SPACE = 63, BLOCK_COMMENT = 64, LINE_COMMENT = 65
  };

  enum {
    RuleMain = 0, RuleGlobal_statements = 1, RuleGlobal_statement = 2, RuleEmpty_stmt = 3, 
    RuleModule_stmt = 4, RuleError_code_stmt = 5, RuleSuccess_stmt = 6, 
    RuleFailure_stmt = 7, RuleImport_from_stmt = 8, RuleImport_stmt = 9, 
    RuleStruct_stmt = 10, RuleStruct_decl = 11, RuleStruct_fwd = 12, RuleUnion_stmt = 13, 
    RuleUnion_decl = 14, RuleUnion_fwd = 15, RuleStruct_block = 16, RuleStruct_item = 17, 
    RuleOs_specific = 18, RuleOs_tag = 19, RuleInterface_stmt = 20, RuleInterface_fwd = 21, 
    RuleInterface_decl = 22, RuleInterface_super = 23, RuleInterface_block = 24, 
    RuleInterface_item = 25, RuleFunction_decl = 26, RuleFunction_param_list = 27, 
    RuleFunction_param = 28, RuleParam_dir_qualifier = 29, RuleCallback_decl = 30, 
    RuleConst_def = 31, RuleConst_integral_def = 32, RuleConst_float_def = 33, 
    RuleConst_string_def = 34, RuleConst_class_id_def = 35, RuleEnum_fwd = 36, 
    RuleEnum_def = 37, RuleFlags_fwd = 38, RuleFlags_def = 39, RuleEnum_type = 40, 
    RuleEnum_elements = 41, RuleEnum_item = 42, RuleEnum_expr = 43, RuleExpr_add_sub = 44, 
    RuleExpr_mul_div = 45, RuleExpr_shift = 46, RuleExpr_logical = 47, RuleExpr_value = 48, 
    RuleAny_literal = 49, RuleNumeric_lit = 50, RuleInteger_lit = 51, RuleFloat_lit = 52, 
    RuleString_lit = 53, RuleChar_lit = 54, RuleQualified_ident = 55, RuleQualified_part = 56, 
    RuleQualified_separator = 57, RuleAll_or_ident = 58, RuleMember_decl = 59, 
    RuleMember_init = 60, RuleMember_init_value = 61, RuleInit_as_type = 62, 
    RuleType_decl = 63, RuleType_modifier = 64, RulePointer_type = 65, RulePointer_decl = 66, 
    RuleAny_type = 67, RuleUtility_type = 68, RuleIntegral_type = 69, RuleFloat_type = 70, 
    RuleTemplate_type = 71, RuleTemplate_params = 72, RuleTemplate_param = 73
  };

  IDLParser(antlr4::TokenStream *input);
  ~IDLParser();

  virtual std::string getGrammarFileName() const override;
  virtual const antlr4::atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;


  class MainContext;
  class Global_statementsContext;
  class Global_statementContext;
  class Empty_stmtContext;
  class Module_stmtContext;
  class Error_code_stmtContext;
  class Success_stmtContext;
  class Failure_stmtContext;
  class Import_from_stmtContext;
  class Import_stmtContext;
  class Struct_stmtContext;
  class Struct_declContext;
  class Struct_fwdContext;
  class Union_stmtContext;
  class Union_declContext;
  class Union_fwdContext;
  class Struct_blockContext;
  class Struct_itemContext;
  class Os_specificContext;
  class Os_tagContext;
  class Interface_stmtContext;
  class Interface_fwdContext;
  class Interface_declContext;
  class Interface_superContext;
  class Interface_blockContext;
  class Interface_itemContext;
  class Function_declContext;
  class Function_param_listContext;
  class Function_paramContext;
  class Param_dir_qualifierContext;
  class Callback_declContext;
  class Const_defContext;
  class Const_integral_defContext;
  class Const_float_defContext;
  class Const_string_defContext;
  class Const_class_id_defContext;
  class Enum_fwdContext;
  class Enum_defContext;
  class Flags_fwdContext;
  class Flags_defContext;
  class Enum_typeContext;
  class Enum_elementsContext;
  class Enum_itemContext;
  class Enum_exprContext;
  class Expr_add_subContext;
  class Expr_mul_divContext;
  class Expr_shiftContext;
  class Expr_logicalContext;
  class Expr_valueContext;
  class Any_literalContext;
  class Numeric_litContext;
  class Integer_litContext;
  class Float_litContext;
  class String_litContext;
  class Char_litContext;
  class Qualified_identContext;
  class Qualified_partContext;
  class Qualified_separatorContext;
  class All_or_identContext;
  class Member_declContext;
  class Member_initContext;
  class Member_init_valueContext;
  class Init_as_typeContext;
  class Type_declContext;
  class Type_modifierContext;
  class Pointer_typeContext;
  class Pointer_declContext;
  class Any_typeContext;
  class Utility_typeContext;
  class Integral_typeContext;
  class Float_typeContext;
  class Template_typeContext;
  class Template_paramsContext;
  class Template_paramContext; 

  class  MainContext : public antlr4::ParserRuleContext {
  public:
    MainContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    Global_statementsContext *global_statements();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MainContext* main();

  class  Global_statementsContext : public antlr4::ParserRuleContext {
  public:
    Global_statementsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Global_statementContext *> global_statement();
    Global_statementContext* global_statement(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Global_statementsContext* global_statements();

  class  Global_statementContext : public antlr4::ParserRuleContext {
  public:
    Global_statementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Import_stmtContext *import_stmt();
    Struct_stmtContext *struct_stmt();
    Union_stmtContext *union_stmt();
    Interface_stmtContext *interface_stmt();
    Callback_declContext *callback_decl();
    Const_defContext *const_def();
    Enum_defContext *enum_def();
    Flags_fwdContext *flags_fwd();
    Flags_defContext *flags_def();
    Enum_fwdContext *enum_fwd();
    Module_stmtContext *module_stmt();
    Error_code_stmtContext *error_code_stmt();
    Empty_stmtContext *empty_stmt();
    Import_from_stmtContext *import_from_stmt();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Global_statementContext* global_statement();

  class  Empty_stmtContext : public antlr4::ParserRuleContext {
  public:
    Empty_stmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Empty_stmtContext* empty_stmt();

  class  Module_stmtContext : public antlr4::ParserRuleContext {
  public:
    Module_stmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *MODULE();
    Qualified_identContext *qualified_ident();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Module_stmtContext* module_stmt();

  class  Error_code_stmtContext : public antlr4::ParserRuleContext {
  public:
    Error_code_stmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Success_stmtContext *success_stmt();
    Failure_stmtContext *failure_stmt();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Error_code_stmtContext* error_code_stmt();

  class  Success_stmtContext : public antlr4::ParserRuleContext {
  public:
    Success_stmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SUCCESS();
    antlr4::tree::TerminalNode *IDENT();
    antlr4::tree::TerminalNode *LPAREN();
    std::vector<antlr4::tree::TerminalNode *> STRING_LIT();
    antlr4::tree::TerminalNode* STRING_LIT(size_t i);
    antlr4::tree::TerminalNode *COMMA();
    antlr4::tree::TerminalNode *RPAREN();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Success_stmtContext* success_stmt();

  class  Failure_stmtContext : public antlr4::ParserRuleContext {
  public:
    Failure_stmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FAILURE();
    antlr4::tree::TerminalNode *IDENT();
    antlr4::tree::TerminalNode *LPAREN();
    std::vector<antlr4::tree::TerminalNode *> STRING_LIT();
    antlr4::tree::TerminalNode* STRING_LIT(size_t i);
    antlr4::tree::TerminalNode *COMMA();
    antlr4::tree::TerminalNode *RPAREN();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Failure_stmtContext* failure_stmt();

  class  Import_from_stmtContext : public antlr4::ParserRuleContext {
  public:
    Import_from_stmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IMPORT();
    All_or_identContext *all_or_ident();
    antlr4::tree::TerminalNode *FROM();
    Qualified_identContext *qualified_ident();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Import_from_stmtContext* import_from_stmt();

  class  Import_stmtContext : public antlr4::ParserRuleContext {
  public:
    Import_stmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IMPORT();
    antlr4::tree::TerminalNode *IDENT();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Import_stmtContext* import_stmt();

  class  Struct_stmtContext : public antlr4::ParserRuleContext {
  public:
    Struct_stmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Struct_declContext *struct_decl();
    Struct_fwdContext *struct_fwd();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Struct_stmtContext* struct_stmt();

  class  Struct_declContext : public antlr4::ParserRuleContext {
  public:
    Struct_declContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STRUCT();
    antlr4::tree::TerminalNode *IDENT();
    Struct_blockContext *struct_block();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Struct_declContext* struct_decl();

  class  Struct_fwdContext : public antlr4::ParserRuleContext {
  public:
    Struct_fwdContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STRUCT();
    Qualified_identContext *qualified_ident();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Struct_fwdContext* struct_fwd();

  class  Union_stmtContext : public antlr4::ParserRuleContext {
  public:
    Union_stmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Union_declContext *union_decl();
    Union_fwdContext *union_fwd();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Union_stmtContext* union_stmt();

  class  Union_declContext : public antlr4::ParserRuleContext {
  public:
    Union_declContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *UNION();
    antlr4::tree::TerminalNode *IDENT();
    Struct_blockContext *struct_block();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Union_declContext* union_decl();

  class  Union_fwdContext : public antlr4::ParserRuleContext {
  public:
    Union_fwdContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *UNION();
    Qualified_identContext *qualified_ident();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Union_fwdContext* union_fwd();

  class  Struct_blockContext : public antlr4::ParserRuleContext {
  public:
    Struct_blockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<Struct_itemContext *> struct_item();
    Struct_itemContext* struct_item(size_t i);
    std::vector<Os_specificContext *> os_specific();
    Os_specificContext* os_specific(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Struct_blockContext* struct_block();

  class  Struct_itemContext : public antlr4::ParserRuleContext {
  public:
    Struct_itemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Member_declContext *member_decl();
    Const_defContext *const_def();
    Enum_defContext *enum_def();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Struct_itemContext* struct_item();

  class  Os_specificContext : public antlr4::ParserRuleContext {
  public:
    Os_specificContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Os_tagContext *os_tag();
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<Struct_itemContext *> struct_item();
    Struct_itemContext* struct_item(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Os_specificContext* os_specific();

  class  Os_tagContext : public antlr4::ParserRuleContext {
  public:
    Os_tagContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Windows();
    antlr4::tree::TerminalNode *Darwin();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Os_tagContext* os_tag();

  class  Interface_stmtContext : public antlr4::ParserRuleContext {
  public:
    Interface_stmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Interface_declContext *interface_decl();
    Interface_fwdContext *interface_fwd();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Interface_stmtContext* interface_stmt();

  class  Interface_fwdContext : public antlr4::ParserRuleContext {
  public:
    Interface_fwdContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INTERFACE();
    Qualified_identContext *qualified_ident();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Interface_fwdContext* interface_fwd();

  class  Interface_declContext : public antlr4::ParserRuleContext {
  public:
    Interface_declContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INTERFACE();
    antlr4::tree::TerminalNode *IDENT();
    Interface_blockContext *interface_block();
    Interface_superContext *interface_super();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Interface_declContext* interface_decl();

  class  Interface_superContext : public antlr4::ParserRuleContext {
  public:
    Interface_superContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *COLON();
    Qualified_identContext *qualified_ident();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Interface_superContext* interface_super();

  class  Interface_blockContext : public antlr4::ParserRuleContext {
  public:
    Interface_blockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<Interface_itemContext *> interface_item();
    Interface_itemContext* interface_item(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Interface_blockContext* interface_block();

  class  Interface_itemContext : public antlr4::ParserRuleContext {
  public:
    Interface_itemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Function_declContext *function_decl();
    Const_defContext *const_def();
    Enum_defContext *enum_def();
    Callback_declContext *callback_decl();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Interface_itemContext* interface_item();

  class  Function_declContext : public antlr4::ParserRuleContext {
  public:
    Function_declContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Type_declContext *type_decl();
    antlr4::tree::TerminalNode *IDENT();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    antlr4::tree::TerminalNode *SEMICOLON();
    Function_param_listContext *function_param_list();
    antlr4::tree::TerminalNode *Const();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Function_declContext* function_decl();

  class  Function_param_listContext : public antlr4::ParserRuleContext {
  public:
    Function_param_listContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Function_paramContext *> function_param();
    Function_paramContext* function_param(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Function_param_listContext* function_param_list();

  class  Function_paramContext : public antlr4::ParserRuleContext {
  public:
    Function_paramContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Type_declContext *type_decl();
    antlr4::tree::TerminalNode *IDENT();
    Param_dir_qualifierContext *param_dir_qualifier();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Function_paramContext* function_param();

  class  Param_dir_qualifierContext : public antlr4::ParserRuleContext {
  public:
    Param_dir_qualifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACKET();
    antlr4::tree::TerminalNode *In();
    antlr4::tree::TerminalNode *RBRACKET();
    antlr4::tree::TerminalNode *Out();
    antlr4::tree::TerminalNode *COMMA();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Param_dir_qualifierContext* param_dir_qualifier();

  class  Callback_declContext : public antlr4::ParserRuleContext {
  public:
    Callback_declContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CALLBACK();
    antlr4::tree::TerminalNode *IDENT();
    antlr4::tree::TerminalNode *EQUALS();
    Type_declContext *type_decl();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    antlr4::tree::TerminalNode *SEMICOLON();
    Function_param_listContext *function_param_list();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Callback_declContext* callback_decl();

  class  Const_defContext : public antlr4::ParserRuleContext {
  public:
    Const_defContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Const_integral_defContext *const_integral_def();
    Const_float_defContext *const_float_def();
    Const_string_defContext *const_string_def();
    Const_class_id_defContext *const_class_id_def();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Const_defContext* const_def();

  class  Const_integral_defContext : public antlr4::ParserRuleContext {
  public:
    Const_integral_defContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Const();
    Integral_typeContext *integral_type();
    antlr4::tree::TerminalNode *IDENT();
    antlr4::tree::TerminalNode *EQUALS();
    Integer_litContext *integer_lit();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Const_integral_defContext* const_integral_def();

  class  Const_float_defContext : public antlr4::ParserRuleContext {
  public:
    Const_float_defContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Const();
    Float_typeContext *float_type();
    antlr4::tree::TerminalNode *IDENT();
    antlr4::tree::TerminalNode *EQUALS();
    Float_litContext *float_lit();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Const_float_defContext* const_float_def();

  class  Const_string_defContext : public antlr4::ParserRuleContext {
  public:
    Const_string_defContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Const();
    antlr4::tree::TerminalNode *STRING();
    antlr4::tree::TerminalNode *IDENT();
    antlr4::tree::TerminalNode *EQUALS();
    String_litContext *string_lit();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Const_string_defContext* const_string_def();

  class  Const_class_id_defContext : public antlr4::ParserRuleContext {
  public:
    Const_class_id_defContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Const();
    antlr4::tree::TerminalNode *CLASS_ID();
    antlr4::tree::TerminalNode *IDENT();
    antlr4::tree::TerminalNode *LPAREN();
    String_litContext *string_lit();
    antlr4::tree::TerminalNode *RPAREN();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Const_class_id_defContext* const_class_id_def();

  class  Enum_fwdContext : public antlr4::ParserRuleContext {
  public:
    Enum_fwdContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ENUM();
    antlr4::tree::TerminalNode *IDENT();
    antlr4::tree::TerminalNode *SEMICOLON();
    Enum_typeContext *enum_type();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Enum_fwdContext* enum_fwd();

  class  Enum_defContext : public antlr4::ParserRuleContext {
  public:
    Enum_defContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ENUM();
    antlr4::tree::TerminalNode *IDENT();
    antlr4::tree::TerminalNode *LBRACE();
    Enum_elementsContext *enum_elements();
    antlr4::tree::TerminalNode *RBRACE();
    Enum_typeContext *enum_type();
    antlr4::tree::TerminalNode *COMMA();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Enum_defContext* enum_def();

  class  Flags_fwdContext : public antlr4::ParserRuleContext {
  public:
    Flags_fwdContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FLAGS();
    antlr4::tree::TerminalNode *IDENT();
    antlr4::tree::TerminalNode *SEMICOLON();
    Enum_typeContext *enum_type();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Flags_fwdContext* flags_fwd();

  class  Flags_defContext : public antlr4::ParserRuleContext {
  public:
    Flags_defContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FLAGS();
    antlr4::tree::TerminalNode *IDENT();
    antlr4::tree::TerminalNode *LBRACE();
    Enum_elementsContext *enum_elements();
    antlr4::tree::TerminalNode *RBRACE();
    Enum_typeContext *enum_type();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Flags_defContext* flags_def();

  class  Enum_typeContext : public antlr4::ParserRuleContext {
  public:
    Enum_typeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *COLON();
    Integral_typeContext *integral_type();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Enum_typeContext* enum_type();

  class  Enum_elementsContext : public antlr4::ParserRuleContext {
  public:
    Enum_elementsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Enum_itemContext *> enum_item();
    Enum_itemContext* enum_item(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Enum_elementsContext* enum_elements();

  class  Enum_itemContext : public antlr4::ParserRuleContext {
  public:
    Enum_itemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENT();
    antlr4::tree::TerminalNode *EQUALS();
    Enum_exprContext *enum_expr();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Enum_itemContext* enum_item();

  class  Enum_exprContext : public antlr4::ParserRuleContext {
  public:
    Enum_exprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Expr_add_subContext *expr_add_sub();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Enum_exprContext* enum_expr();

  class  Expr_add_subContext : public antlr4::ParserRuleContext {
  public:
    Expr_add_subContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Expr_mul_divContext *expr_mul_div();
    Expr_add_subContext *expr_add_sub();
    antlr4::tree::TerminalNode *PLUS();
    antlr4::tree::TerminalNode *MINUS();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Expr_add_subContext* expr_add_sub();
  Expr_add_subContext* expr_add_sub(int precedence);
  class  Expr_mul_divContext : public antlr4::ParserRuleContext {
  public:
    Expr_mul_divContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Expr_shiftContext *expr_shift();
    Expr_mul_divContext *expr_mul_div();
    antlr4::tree::TerminalNode *STAR();
    antlr4::tree::TerminalNode *SLASH();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Expr_mul_divContext* expr_mul_div();
  Expr_mul_divContext* expr_mul_div(int precedence);
  class  Expr_shiftContext : public antlr4::ParserRuleContext {
  public:
    Expr_shiftContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Expr_logicalContext *expr_logical();
    Expr_shiftContext *expr_shift();
    antlr4::tree::TerminalNode *LSHIFT();
    antlr4::tree::TerminalNode *RSHIFT();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Expr_shiftContext* expr_shift();
  Expr_shiftContext* expr_shift(int precedence);
  class  Expr_logicalContext : public antlr4::ParserRuleContext {
  public:
    Expr_logicalContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Expr_valueContext *expr_value();
    Expr_logicalContext *expr_logical();
    antlr4::tree::TerminalNode *PIPE();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Expr_logicalContext* expr_logical();
  Expr_logicalContext* expr_logical(int precedence);
  class  Expr_valueContext : public antlr4::ParserRuleContext {
  public:
    Expr_valueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Integer_litContext *integer_lit();
    Qualified_identContext *qualified_ident();
    antlr4::tree::TerminalNode *LPAREN();
    Enum_exprContext *enum_expr();
    antlr4::tree::TerminalNode *RPAREN();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Expr_valueContext* expr_value();

  class  Any_literalContext : public antlr4::ParserRuleContext {
  public:
    Any_literalContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Numeric_litContext *numeric_lit();
    String_litContext *string_lit();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Any_literalContext* any_literal();

  class  Numeric_litContext : public antlr4::ParserRuleContext {
  public:
    Numeric_litContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Integer_litContext *integer_lit();
    Float_litContext *float_lit();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Numeric_litContext* numeric_lit();

  class  Integer_litContext : public antlr4::ParserRuleContext {
  public:
    Integer_litContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DECIMAL_LIT();
    antlr4::tree::TerminalNode *HEX_LIT();
    antlr4::tree::TerminalNode *OCT_LIT();
    antlr4::tree::TerminalNode *BIN_LIT();
    Char_litContext *char_lit();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Integer_litContext* integer_lit();

  class  Float_litContext : public antlr4::ParserRuleContext {
  public:
    Float_litContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FLOAT_LIT();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Float_litContext* float_lit();

  class  String_litContext : public antlr4::ParserRuleContext {
  public:
    String_litContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STRING_LIT();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  String_litContext* string_lit();

  class  Char_litContext : public antlr4::ParserRuleContext {
  public:
    Char_litContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CHAR_LIT();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Char_litContext* char_lit();

  class  Qualified_identContext : public antlr4::ParserRuleContext {
  public:
    Qualified_identContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENT();
    Qualified_separatorContext *qualified_separator();
    std::vector<Qualified_partContext *> qualified_part();
    Qualified_partContext* qualified_part(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Qualified_identContext* qualified_ident();

  class  Qualified_partContext : public antlr4::ParserRuleContext {
  public:
    Qualified_partContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Qualified_separatorContext *qualified_separator();
    antlr4::tree::TerminalNode *IDENT();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Qualified_partContext* qualified_part();

  class  Qualified_separatorContext : public antlr4::ParserRuleContext {
  public:
    Qualified_separatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> COLON();
    antlr4::tree::TerminalNode* COLON(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Qualified_separatorContext* qualified_separator();

  class  All_or_identContext : public antlr4::ParserRuleContext {
  public:
    All_or_identContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENT();
    antlr4::tree::TerminalNode *STAR();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  All_or_identContext* all_or_ident();

  class  Member_declContext : public antlr4::ParserRuleContext {
  public:
    Member_declContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Type_declContext *type_decl();
    antlr4::tree::TerminalNode *IDENT();
    antlr4::tree::TerminalNode *SEMICOLON();
    antlr4::tree::TerminalNode *LBRACKET();
    antlr4::tree::TerminalNode *RBRACKET();
    Member_initContext *member_init();
    Integer_litContext *integer_lit();
    Qualified_identContext *qualified_ident();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Member_declContext* member_decl();

  class  Member_initContext : public antlr4::ParserRuleContext {
  public:
    Member_initContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EQUALS();
    std::vector<Member_init_valueContext *> member_init_value();
    Member_init_valueContext* member_init_value(size_t i);
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Member_initContext* member_init();

  class  Member_init_valueContext : public antlr4::ParserRuleContext {
  public:
    Member_init_valueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DEFAULT();
    Qualified_identContext *qualified_ident();
    Integer_litContext *integer_lit();
    Init_as_typeContext *init_as_type();
    Float_litContext *float_lit();
    String_litContext *string_lit();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Member_init_valueContext* member_init_value();

  class  Init_as_typeContext : public antlr4::ParserRuleContext {
  public:
    Init_as_typeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *AS();
    Integral_typeContext *integral_type();
    Float_typeContext *float_type();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Init_as_typeContext* init_as_type();

  class  Type_declContext : public antlr4::ParserRuleContext {
  public:
    Type_declContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Any_typeContext *any_type();
    Type_modifierContext *type_modifier();
    Pointer_typeContext *pointer_type();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Type_declContext* type_decl();

  class  Type_modifierContext : public antlr4::ParserRuleContext {
  public:
    Type_modifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Const();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Type_modifierContext* type_modifier();

  class  Pointer_typeContext : public antlr4::ParserRuleContext {
  public:
    Pointer_typeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Pointer_declContext *> pointer_decl();
    Pointer_declContext* pointer_decl(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Pointer_typeContext* pointer_type();

  class  Pointer_declContext : public antlr4::ParserRuleContext {
  public:
    Pointer_declContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STAR();
    antlr4::tree::TerminalNode *Const();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Pointer_declContext* pointer_decl();

  class  Any_typeContext : public antlr4::ParserRuleContext {
  public:
    Any_typeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Integral_typeContext *integral_type();
    Float_typeContext *float_type();
    Utility_typeContext *utility_type();
    Qualified_identContext *qualified_ident();
    Template_typeContext *template_type();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Any_typeContext* any_type();

  class  Utility_typeContext : public antlr4::ParserRuleContext {
  public:
    Utility_typeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Void();
    antlr4::tree::TerminalNode *RESULT();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Utility_typeContext* utility_type();

  class  Integral_typeContext : public antlr4::ParserRuleContext {
  public:
    Integral_typeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *U8();
    antlr4::tree::TerminalNode *S8();
    antlr4::tree::TerminalNode *U16();
    antlr4::tree::TerminalNode *S16();
    antlr4::tree::TerminalNode *U32();
    antlr4::tree::TerminalNode *S32();
    antlr4::tree::TerminalNode *U64();
    antlr4::tree::TerminalNode *S64();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Integral_typeContext* integral_type();

  class  Float_typeContext : public antlr4::ParserRuleContext {
  public:
    Float_typeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *F32();
    antlr4::tree::TerminalNode *F64();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Float_typeContext* float_type();

  class  Template_typeContext : public antlr4::ParserRuleContext {
  public:
    Template_typeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Qualified_identContext *qualified_ident();
    antlr4::tree::TerminalNode *LT();
    Template_paramsContext *template_params();
    antlr4::tree::TerminalNode *GT();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Template_typeContext* template_type();

  class  Template_paramsContext : public antlr4::ParserRuleContext {
  public:
    Template_paramsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Template_paramContext *template_param();
    std::vector<Template_paramsContext *> template_params();
    Template_paramsContext* template_params(size_t i);
    antlr4::tree::TerminalNode *COMMA();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Template_paramsContext* template_params();
  Template_paramsContext* template_params(int precedence);
  class  Template_paramContext : public antlr4::ParserRuleContext {
  public:
    Template_paramContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Any_typeContext *any_type();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Template_paramContext* template_param();


  virtual bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;
  bool expr_add_subSempred(Expr_add_subContext *_localctx, size_t predicateIndex);
  bool expr_mul_divSempred(Expr_mul_divContext *_localctx, size_t predicateIndex);
  bool expr_shiftSempred(Expr_shiftContext *_localctx, size_t predicateIndex);
  bool expr_logicalSempred(Expr_logicalContext *_localctx, size_t predicateIndex);
  bool template_paramsSempred(Template_paramsContext *_localctx, size_t predicateIndex);

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

