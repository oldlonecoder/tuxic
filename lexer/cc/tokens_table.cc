//
// Created by oldlonecoder on 24-01-27.
//



#include <tuxic/lexer/tokens_table.h>

namespace tux
{
/*!
 * @brief This is the default complete tokens reference of the Scrat Language.
 * @return
 */
[[maybe_unused]] size_t token_table::set_reference_table()
{
    if(!ref_table.empty())
    {
        log::warning() << log::code::notempty << log::fn::func;
    }
    ref_table = lex_token::list{
        {
            .prim   = lex::type::Binary,
            .sem    = lex::type::Operator|lex::type::Binary,
            .m      = lex::mnemonic::LeftShift,
            .name   = {"LeftShift"},
            .d      = lex::operand::Shift,
            .token_location    = { .begin = lex::lexem::LeftShift },
            .flags  = { .V = 1 }
        },
        {
            .prim = lex::type::Keyword,
            .sem = lex::type::Keyword|lex::type::Number|lex::type::Const,
            .m     = lex::mnemonic::Null,
            .name  = "Null",
            .d     = lex::operand::Identifier,
            .token_location   = { .begin = lex::lexem::Null },
            .flags = { .V = 1 }
        },
        {
            .prim  = lex::type::Prefix,
            .sem = lex::type::Unary|lex::type::Prefix|lex::type::Operator,
            .m     = lex::mnemonic::UnShadow,
            .name  = "Unshadow",
            .d     = lex::operand::Scope,
            .token_location   = { .begin = lex::lexem::Unshadow },
            .flags = { .V = 1 }
        },
        {
            .prim = lex::type::OpenPair,
            .sem = lex::type::Binary|lex::type::Operator|lex::type::OpenPair|lex::type::Punc,
            .m     = lex::mnemonic::OpenAbsOp, // |< x+1 >|;
            //                               ~~
            //                               ^
            .name  = "OpenAbsOp",
            .d     = lex::operand::Parenthese,
            .token_location   = {.begin = lex::lexem::AbsBegin },
            .flags = { .V = 1 }
        },
        {
            .prim = lex::type::ClosePair,
            .sem = lex::type::Binary|lex::type::Operator|lex::type::OpenPair|lex::type::Punc,
            .m     = lex::mnemonic::CloseAbsOp, // |< x+1 >|;
            //                                       ~~
            //                                       ^
            .name  = "CloseAbsOp",
            .d     = lex::operand::Parenthese,
            .token_location   = {.begin = lex::lexem::AbsEnd },
            .flags = { .V = 1 }
        },
        {
            .prim = lex::type::Binary,
            .sem = lex::type::Binary|lex::type::Operator,
            .m     = lex::mnemonic::Radical,
            .name  = "Radical",
            .d     = lex::operand::Exponent,
            .token_location   = {.begin = lex::lexem::Radical },
            .flags = { .V = 1 }
        },
        {
            .prim = lex::type::Binary,
            .sem = lex::type::Binary|lex::type::Operator,
            .m     = lex::mnemonic::Exponent,
            .name    = "Exponent",
            .d     = lex::operand::Exponent,
            .token_location   = {.begin = lex::lexem::Exponent },
            .flags = { .V = 1 }
        },
        {
            .prim = lex::type::Binary,
            .sem = lex::type::Binary|lex::type::Operator,
            .m     = lex::mnemonic::RightShift,
            .name  = "RightShift",
            .d     = lex::operand::Shift,
            .token_location   = {.begin = lex::lexem::RightShift },
            .flags = { .V = 1 }
        },
        {
            .prim = lex::type::Binary,
            .sem = lex::type::Binary|lex::type::Operator,
            .m     = lex::mnemonic::BinaryXor,
            .name  = "BinaryXor",
            .d     = lex::operand::Bits,
            .token_location   = {.begin = lex::lexem::Xor },
            .flags = { .V = 1 }
        },
        {
            .prim = lex::type::Prefix,
            .sem = lex::type::Prefix|lex::type::Operator|lex::type::Unary,
            .m     = lex::mnemonic::Deref,
            .name  = "Deref",
            .d     = lex::operand::Deref,
            .token_location   = {.begin = lex::lexem::Deref },
            .flags = { .V = 1 }
        },
        {
            .prim = lex::type::Prefix,
            .sem = lex::type::Unary|lex::type::Prefix|lex::type::Operator,
            .m     = lex::mnemonic::Deref,
            .name  = "DerefUtf",
            .d     = lex::operand::Bits,
            .token_location   = {.begin = "➪" },
            .flags = { .V = 1 }
        },
        {
            .prim = lex::type::Unary,
            .sem = lex::type::Unary|lex::type::Prefix|lex::type::Operator,
            .m     = lex::mnemonic::Decr,
            .name  = "Decr",
            .d     = lex::operand::Unary,
            .token_location   = {.begin = lex::lexem::Decr },
            .flags = { .V = 1 }
        },
        {
            .prim  = lex::type::Unary,
            .sem = lex::type::Unary|lex::type::Prefix|lex::type::Operator,
            .m     = lex::mnemonic::Incr,
            .name  = "Incr",
            .d     = lex::operand::Unary,
            .token_location   = {.begin = lex::lexem::Incr },
            .flags = { .V = 1 }
        },
        {
            .prim  = lex::type::Assign,
            .sem   = lex::type::Keyword|lex::type::Operator|lex::type::Binary|lex::type::Assign,
            .m     = lex::mnemonic::AssignAdd,
            .name  = "AssignAdd",
            .d     = lex::operand::Assign,
            .token_location   = {.begin = lex::lexem::AssignAdd},
            .flags = {.V=1}
        },
        {
            .prim   = lex::type::Assign,
            .sem    = lex::type::Keyword|lex::type::Operator|lex::type::Binary|lex::type::Assign,
            .m      = lex::mnemonic::AssignMul,
            .name  = "AssignMul",
            .d      = lex::operand::Assign,
            .token_location    = {.begin = lex::lexem::AssignMul},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::Assign,
            .sem    = lex::type::Keyword|lex::type::Operator|lex::type::Binary|lex::type::Assign,
            .m      = lex::mnemonic::AssignDiv,
            .name  = "AssignDiv",
            .d      = lex::operand::Assign,
            .token_location    = {.begin = lex::lexem::AssignDiv},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::Assign,
            .sem    = lex::type::Keyword|lex::type::Operator|lex::type::Binary|lex::type::Assign,
            .m      = lex::mnemonic::AssignMod,
            .name  = "AssignMod",
            .d      = lex::operand::Assign,
            .token_location    = {.begin = lex::lexem::AssignMod},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::Assign,
            .sem    = lex::type::Keyword|lex::type::Operator|lex::type::Binary|lex::type::Assign,
            .m      = lex::mnemonic::AssignOr,
            .name  = "AssignOr",
            .d      = lex::operand::Assign,
            .token_location    = {.begin = lex::lexem::AssignOr},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::Assign,
            .sem    = lex::type::Keyword|lex::type::Operator|lex::type::Binary|lex::type::Assign,
            .m      = lex::mnemonic::AssignXor,
            .name  = "AssignXor",
            .d      = lex::operand::Assign,
            .token_location    = {.begin = lex::lexem::AssignXor},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::Assign,
            .sem    = lex::type::Keyword|lex::type::Operator|lex::type::Binary|lex::type::Assign,
            .m      = lex::mnemonic::AssignC1,
            .name  = "AssignC1",
            .d      = lex::operand::Assign,
            .token_location    = {.begin = lex::lexem::AssignC1},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::Assign,
            .sem    = lex::type::Keyword|lex::type::Operator|lex::type::Binary|lex::type::Assign,
            .m      = lex::mnemonic::AssignLeftShift,
            .name  = "AssignLeftShift",
            .d      = lex::operand::Assign,
            .token_location    = {.begin = lex::lexem::AssignLShift},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::Assign,
            .sem    = lex::type::Keyword|lex::type::Operator|lex::type::Binary|lex::type::Assign,
            .m      = lex::mnemonic::AssignRightShift,
            .name  = "AssignRightShift",
            .d      = lex::operand::Assign,
            .token_location    = {.begin = lex::lexem::AssignRShift},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::Binary,
            .sem    = lex::type::Operator|lex::type::Binary|lex::type::Bool,
            .m      = lex::mnemonic::GreaterEq,
            .name  = "GreaterEq",
            .d      = lex::operand::Equality,
            .token_location    = {.begin = lex::lexem::GreaterEqual},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::Binary,
            .sem    = lex::type::Operator|lex::type::Binary|lex::type::Bool,
            .m      = lex::mnemonic::Equal,
            .name  = "Equal",
            .d      = lex::operand::Equality,
            .token_location    = {.begin = lex::lexem::Equal},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::Binary,
            .sem    = lex::type::Operator|lex::type::Binary|lex::type::Bool,
            .m      = lex::mnemonic::NotEqual,
            .name  = "NotEqual",
            .d      = lex::operand::Equality,
            .token_location    = {.begin = lex::lexem::NotEqual},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::Binary,
            .sem    = lex::type::Operator|lex::type::Binary|lex::type::Bool,
            .m      = lex::mnemonic::NotEqual,
            .name  = "NotEqualAlt",
            .d      = lex::operand::Equality,
            .token_location    = {.begin = "<>"},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::Binary,
            .sem    = lex::type::Operator|lex::type::Binary,
            .m      = lex::mnemonic::Add,
            .name  = "Addition",
            .d      = lex::operand::Addition,
            .token_location    = {.begin = lex::lexem::Addition},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::Binary,
            .sem    = lex::type::Operator|lex::type::Binary,
            .m      = lex::mnemonic::Sub,
            .name  = "Subtract",
            .d      = lex::operand::Addition,
            .token_location    = {.begin = lex::lexem::Sub},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::Binary,
            .sem    = lex::type::Operator|lex::type::Binary,
            .m      = lex::mnemonic::Mul,
            .name  = "Multiply",
            .d      = lex::operand::Product,
            .token_location    = {.begin = lex::lexem::Multiply},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::LineComment,
            .sem    = lex::type::LineComment|lex::type::Operator,
            .m      = lex::mnemonic::CommentCpp,
            .name  = "CommentCpp",
            .d      = lex::operand::Noop_,
            .token_location    = {.begin = lex::lexem::CommentCpp},
            .flags  = {.V = 0}
        },
        {
            .prim   = lex::type::Binary,
            .sem    = lex::type::Operator|lex::type::Binary,
            .m      = lex::mnemonic::Modulo,
            .name  = "Modulo",
            .d      = lex::operand::Product,
            .token_location    = {.begin = lex::lexem::Modulo},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::Binary,
            .sem    = lex::type::Operator|lex::type::Binary|lex::type::Bool,
            .m      = lex::mnemonic::LessThan,
            .name  = "LessThan",
            .d      = lex::operand::Equality,
            .token_location    = {.begin = lex::lexem::LessThan},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::Binary,
            .sem    = lex::type::Operator|lex::type::Binary|lex::type::Bool,
            .m      = lex::mnemonic::GreaterThan,
            .name  = "GreaterThan",
            .d      = lex::operand::Equality,
            .token_location    = {.begin = lex::lexem::GreaterThan},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::Binary,
            .sem    = lex::type::Keyword|lex::type::Operator|lex::type::Binary|lex::type::Assign,
            .m      = lex::mnemonic::Assign,
            .name  = "Assign",
            .d      = lex::operand::Assign,
            .token_location    = {.begin = lex::lexem::Assign},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::Binary,
            .sem    = lex::type::Operator|lex::type::Binary,
            .m      = lex::mnemonic::BinaryAnd,
            .name  = "BinaryAnd",
            .d      = lex::operand::Bits,
            .token_location    = {.begin = lex::lexem::BinaryAnd},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::Binary,
            .sem    = lex::type::Operator|lex::type::Binary,
            .m      = lex::mnemonic::BinaryOr,
            .name  = "BinaryOr",
            .d      = lex::operand::Bits,
            .token_location    = {.begin = lex::lexem::BinaryOr},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::Prefix,
            .sem    = lex::type::Unary|lex::type::Operator|lex::type::Prefix,
            .m      = lex::mnemonic::C2, // Tow's complement
            .name  = "TwoComplement",
            .d      = lex::operand::Prefix,
            .token_location    = {.begin = lex::lexem::C2},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::Prefix,
            .sem    = lex::type::Unary|lex::type::Operator|lex::type::Prefix,
            .m      = lex::mnemonic::C1, // Tow's complement
            .name  = "OneComplement",
            .d      = lex::operand::Prefix,
            .token_location    = {.begin = lex::lexem::C1},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::Unary,
            .sem    = lex::type::Unary|lex::type::Operator|lex::type::Prefix,
            .m      = lex::mnemonic::BinaryNot, // Tow's complement
            .name  = "BinaryNot",
            .d      = lex::operand::Prefix,
            .token_location    = {.begin = lex::lexem::Not},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::Binary,
            .sem    = lex::type::Operator|lex::type::Binary|lex::type::Bool,
            .m      = lex::mnemonic::LogicalAnd, // Tow's complement
            .name  = "LogicalAnd",
            .d      = lex::operand::Bool_and,
            .token_location    = {.begin = lex::lexem::BoolAnd},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::Binary,
            .sem    = lex::type::Operator|lex::type::Binary|lex::type::Bool,
            .m      = lex::mnemonic::LogicalOr, // Tow's complement
            .name  = "LogicalOr",
            .d      = lex::operand::Bool_or,
            .token_location    = {.begin = lex::lexem::BoolOr},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::OpenPair,
            .sem    = lex::type::Operator|lex::type::Punc|lex::type::OpenPair,
            .m      = lex::mnemonic::OpenPar, // Tow's complement
            .name  = "OpenPar",
            .d      = lex::operand::Parenthese,
            .token_location    = {.begin = lex::lexem::OpenPar},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::ClosePair,
            .sem    = lex::type::Operator|lex::type::Punc|lex::type::ClosePair,
            .m      = lex::mnemonic::ClosePar, // Tow's complement
            .name  = "ClosePar",
            .d      = lex::operand::Parenthese,
            .token_location    = {.begin = lex::lexem::ClosePar},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::OpenPair,
            .sem    = lex::type::Operator|lex::type::Punc|lex::type::OpenPair,
            .m      = lex::mnemonic::OpenIndex, // Tow's complement
            .name  = "OpenIndex",
            .d      = lex::operand::Parenthese,
            .token_location    = {.begin = lex::lexem::OpenIndex},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::ClosePair,
            .sem    = lex::type::Operator|lex::type::Punc|lex::type::ClosePair,
            .m      = lex::mnemonic::CloseIndex, // Tow's complement
            .name  = "CloseIndex",
            .d      = lex::operand::Parenthese,
            .token_location    = {.begin = lex::lexem::CloseIndex},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::OpenPair,
            .sem    = lex::type::Operator|lex::type::Punc|lex::type::OpenPair,
            .m      = lex::mnemonic::OpenBrace, // Tow's complement
            .name  = "OpenBrace",
            .d      = lex::operand::Parenthese,
            .token_location    = {.begin = lex::lexem::BraceBegin},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::ClosePair,
            .sem    = lex::type::Operator|lex::type::Punc|lex::type::ClosePair,
            .m      = lex::mnemonic::CloseBrace, // Tow's complement
            .name  = "CloseBrace",
            .d      = lex::operand::Parenthese,
            .token_location    = {.begin = lex::lexem::BraceEnd},
            .flags  = {.V = 1}
        },
        {
            .prim   = lex::type::BlocComment,
            .sem    = lex::type::BlocComment|lex::type::Operator,
            .m      = lex::mnemonic::BeginComment, // Tow's complement
            .name  = "BeginBlocComment",
            .d      = lex::operand::Noop_,
            .token_location    = {.begin = lex::lexem::CommentBegin},
            .flags  = {.V = 0}
        },
        {
            .prim   = lex::type::BlocComment,
            .sem    = lex::type::BlocComment|lex::type::Operator,
            .m      = lex::mnemonic::EndComment, // Tow's complement
            .name  = "EndBlocComment",
            .d      = lex::operand::Noop_,
            .token_location    = {.begin = lex::lexem::CommentEnd},
            .flags  = {.V = 0}
        },
        {
            .prim = lex::type::Binary,
            .sem = lex::type::Operator|lex::type::Binary,
            .m = lex::mnemonic::Div,
            .name  = "Division",
            .d = lex::operand::Product,
            .token_location = {.begin = lex::lexem::Division},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Punc,
            .sem = lex::type::Operator|lex::type::Binary|lex::type::Punc,
            .m = lex::mnemonic::Comma,
            .name  = "Comma",
            .d = lex::operand::Comma,
            .token_location = {.begin = lex::lexem::Comma},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Punc,
            .sem = lex::type::Operator|lex::type::Binary|lex::type::Punc,
            .m = lex::mnemonic::Scope,
            .name  = "Scope",
            .d = lex::operand::Scope,
            .token_location = {.begin = lex::lexem::Scope},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Punc,
            .sem = lex::type::Punc,
            .m = lex::mnemonic::Semicolon,
            .name  = "SemiColon",
            .d = lex::operand::Noop_,
            .token_location = {.begin = lex::lexem::Semicolon},
            .flags{.V=0}
        },
        {
            .prim = lex::type::Punc,
            .sem = lex::type::Operator|lex::type::Binary|lex::type::Punc,
            .m = lex::mnemonic::Colon,
            .name  = "Colon",
            .d = lex::operand::Noop_,
            .token_location = {.begin = lex::lexem::Colon},
            .flags{.V=0}
        },
        {
            .prim = lex::type::Binary,
            .sem = lex::type::Operator|lex::type::Binary|lex::type::Punc,
            .m = lex::mnemonic::Range,
            .name  = "Range",
            .d = lex::operand::Scope,
            .token_location = {.begin = lex::lexem::Range},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Postfix,
            .sem = lex::type::Unary|lex::type::Postfix|lex::type::Operator,
            .m = lex::mnemonic::Factorial,
            .name  = "Factorial",
            .d = lex::operand::Unary,
            .token_location = {.begin = lex::lexem::Factorial},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Prefix,
            .sem = lex::type::Sign|lex::type::Unary|lex::type::Prefix|lex::type::Operator,
            .m = lex::mnemonic::Positive,
            .name  = "Positive",
            .d = lex::operand::Unary,
            .token_location = {.begin = lex::lexem::Positive},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Prefix,
            .sem = lex::type::Sign|lex::type::Unary|lex::type::Prefix|lex::type::Operator,
            .m = lex::mnemonic::Negative,
            .name  = "Negative",
            .d = lex::operand::Unary,
            .token_location = {.begin = lex::lexem::Negative},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Text,
            .sem = lex::type::Text|lex::type::Leaf|lex::type::Operator,
            .m = lex::mnemonic::SQuote,
            .name  = "SingleQuote",
            .d = lex::operand::Identifier,
            .token_location = {.begin = lex::lexem::Squote},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Text,
            .sem = lex::type::Text|lex::type::Leaf|lex::type::Operator,
            .m = lex::mnemonic::DQuote,
            .name  = "DoubleQuote",
            .d = lex::operand::Identifier,
            .token_location = {.begin = lex::lexem::Dquote},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Keyword,
            .sem = lex::type::Keyword|lex::type::Operator|lex::type::Binary,
            .m = lex::mnemonic::Ternary,
            .name  = "Ternary",
            .d = lex::operand::Unary,
            .token_location = {.begin = lex::lexem::Ternary},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Prefix,
            .sem = lex::type::Unary|lex::type::Prefix|lex::type::Operator,
            .m = lex::mnemonic::Hash,
            .name  = "Hash",
            .d = lex::operand::Unary,
            .token_location = {.begin = lex::lexem::Hash},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Prefix,
            .sem = lex::type::Unary|lex::type::Prefix|lex::type::Operator,
            .m = lex::mnemonic::Eos,
            .name  = "EosMark",
            .d = lex::operand::Unary,
            .token_location = {.begin = lex::lexem::Eos},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Punc,
            .sem = lex::type::Punc|lex::type::Operator,
            .m = lex::mnemonic::Dot,
            .name  = "Dot",
            .d = lex::operand::Scope,
            .token_location = {.begin = lex::lexem::Dot},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Keyword,
            .sem = lex::type::Keyword,
            .m = lex::mnemonic::Return,
            .name  = "Return",
            .d = lex::operand::Identifier,
            .token_location = {.begin = lex::lexem::Return},
            .flags{.V=0}
        },
        {
            .prim = lex::type::Keyword,
            .sem = lex::type::Keyword,
            .m = lex::mnemonic::If,
            .name  = "If",
            .d = lex::operand::Identifier,
            .token_location = {.begin = lex::lexem::If},
            .flags{.V=0}
        },
        {
            .prim = lex::type::Number,
            .sem = lex::type::Number|lex::type::Leaf|lex::type::Float|lex::type::Keyword|lex::type::Const,
            .m = lex::mnemonic::Pi,
            .name  = "Pi",
            .d = lex::operand::Identifier,
            .token_location = {.begin = lex::lexem::Pi},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Number,
            .sem = lex::type::Number|lex::type::Leaf|lex::type::Float|lex::type::Keyword|lex::type::Const,
            .m = lex::mnemonic::Pi,
            .name  = "PiUtf",
            .d = lex::operand::Identifier,
            .token_location = {.begin = "π"},
            .flags{.V=1,.U=1}
        },
        {
            .prim = lex::type::Prefix,
            .sem = lex::type::Number|lex::type::Unary|lex::type::Keyword|lex::type::Prefix|lex::type::Operator,
            .m = lex::mnemonic::Number,
            .name  = "Number",
            .d = lex::operand::Identifier,
            .token_location = {.begin = lex::lexem::Number},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Prefix,
            .sem = lex::type::U8|lex::type::Keyword|lex::type::Prefix|lex::type::Operator,
            .m = lex::mnemonic::U8,
            .name  = "U8",
            .d = lex::operand::Identifier,
            .token_location = {.begin = lex::lexem::U8},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Prefix,
            .sem = lex::type::U16|lex::type::Unary|lex::type::Keyword|lex::type::Prefix|lex::type::Operator,
            .m = lex::mnemonic::U16,
            .name  = "U16",
            .d = lex::operand::Identifier,
            .token_location = {.begin = lex::lexem::U16},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Prefix,
            .sem = lex::type::U32|lex::type::Unary|lex::type::Keyword|lex::type::Prefix|lex::type::Operator,
            .m = lex::mnemonic::U32,
            .name  = "U32",
            .d = lex::operand::Identifier,
            .token_location = {.begin = lex::lexem::U32},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Prefix,
            .sem = lex::type::U64|lex::type::Unary|lex::type::Keyword|lex::type::Prefix|lex::type::Operator,
            .m = lex::mnemonic::U64,
            .name  = "U64",
            .d = lex::operand::Identifier,
            .token_location = {.begin = lex::lexem::U64},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Prefix,
            .sem = lex::type::I8|lex::type::Unary|lex::type::Keyword|lex::type::Prefix|lex::type::Operator,
            .m = lex::mnemonic::I8,
            .name  = "I8",
            .d = lex::operand::Identifier,
            .token_location = {.begin = lex::lexem::I8},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Prefix,
            .sem = lex::type::I16|lex::type::Unary|lex::type::Keyword|lex::type::Prefix|lex::type::Operator                ,
            .m = lex::mnemonic::I16,
            .name  = "I16",
            .d = lex::operand::Identifier, .token_location = {.begin = lex::lexem::I16},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Prefix,
            .sem = lex::type::I32|lex::type::Unary|lex::type::Keyword|lex::type::Prefix|lex::type::Operator                ,
            .m = lex::mnemonic::I32,
            .name  = "I32",
            .d = lex::operand::Identifier,
            .token_location = {.begin = lex::lexem::I32},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Prefix,
            .sem = lex::type::I64|lex::type::Unary|lex::type::Keyword|lex::type::Prefix|lex::type::Operator,
            .m = lex::mnemonic::I64,
            .name  = "I64",
            .d = lex::operand::Identifier,
            .token_location = {.begin = lex::lexem::I64},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Prefix,
            .sem = lex::type::Float|lex::type::Unary|lex::type::Keyword|lex::type::Prefix|lex::type::Operator ,
            .m = lex::mnemonic::Float,
            .name  = "Float",
            .d = lex::operand::Identifier,
            .token_location = {.begin = lex::lexem::Float},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Prefix,
            .sem = lex::type::Text|lex::type::Unary|lex::type::Keyword|lex::type::Prefix|lex::type::Operator,
            .m = lex::mnemonic::String,
            .name  = "String",
            .d = lex::operand::Identifier,
            .token_location = {.begin = lex::lexem::String},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Keyword,
            .sem = lex::type::Keyword,
            .m = lex::mnemonic::Then,
            .name  = "Then",
            .d = lex::operand::Identifier,
            .token_location = {.begin = lex::lexem::Then},
            .flags{.V=0}
        },
        {
            .prim = lex::type::Keyword,
            .sem = lex::type::Keyword,
            .m = lex::mnemonic::Else,
            .name  = "Else",
            .d = lex::operand::Identifier,
            .token_location = {.begin = lex::lexem::Else},
            .flags{.V=0}
        },
        {
            .prim = lex::type::Keyword,
            .sem = lex::type::Keyword|lex::type::Const,
            .m = lex::mnemonic::Const,
            .name  = "Const",
            .d = lex::operand::Identifier,
            .token_location = {.begin = lex::lexem::Const},
            .flags{.V=0}
        },
        {
            .prim = lex::type::Keyword,
            .sem = lex::type::Keyword,
            .m = lex::mnemonic::Include,
            .name  = "Include",
            .d = lex::operand::Identifier,
            .token_location = {.begin = lex::lexem::Include},
            .flags{.V=0}
        },
        {
            .prim = lex::type::Keyword,
            .sem = lex::type::Keyword,
            .m = lex::mnemonic::Amu,
            .name  = "Amu",
            .d = lex::operand::Identifier,
            .token_location = {.begin = lex::lexem::Amu},
            .flags{.V=0}
        },
        {
            .prim = lex::type::Prefix,
            .sem = lex::type::Unary|lex::type::Prefix|lex::type::Operator,
            .m = lex::mnemonic::At,
            .name  = "At",
            .d = lex::operand::Unary,
            .token_location = {.begin = lex::lexem::At},.flags{.V=1}
        },
        {
            .prim = lex::type::Prefix,
            .sem = lex::type::Unary|lex::type::Prefix|lex::type::Operator,
            .m = lex::mnemonic::Prime,
            .name  = "Prime",
            .d = lex::operand::Unary,
            .token_location = {.begin = lex::lexem::Prime},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Keyword,
            .sem = lex::type::Keyword,
            .m = lex::mnemonic::Do,
            .name  = "Do",
            .d = lex::operand::Noop_,
            .token_location = {.begin = lex::lexem::Do},
            .flags{.V=0}
        },
        {
            .prim = lex::type::Keyword,
            .sem = lex::type::Keyword,
            .m = lex::mnemonic::While,
            .name  = "While",
            .d = lex::operand::Noop_,
            .token_location = {.begin = lex::lexem::While},
            .flags{.V=0}
        },
        {
            .prim = lex::type::Keyword,
            .sem = lex::type::Keyword,
            .m = lex::mnemonic::For,
            .name  = "For",
            .d = lex::operand::Noop_,
            .token_location = {.begin = lex::lexem::For},
            .flags{.V=0}
        },
        {
            .prim = lex::type::Keyword,
            .sem = lex::type::Keyword,
            .m = lex::mnemonic::Until,
            .name  = "Until",
            .d = lex::operand::Noop_,
            .token_location = {.begin = lex::lexem::Until},
            .flags{.V=0}
        },
        {
            .prim = lex::type::Keyword,
            .sem = lex::type::Keyword,
            .m = lex::mnemonic::Repeat,
            .name  = "Repeat",
            .d = lex::operand::Noop_,
            .token_location = {.begin = lex::lexem::Repeat},
            .flags{.V=0}
        },
        {
            .prim = lex::type::Keyword,
            .sem = lex::type::Keyword,
            .m = lex::mnemonic::Switch,
            .name  = "Switch",
            .d = lex::operand::Noop_,
            .token_location = {.begin = lex::lexem::Switch},
            .flags{.V=0}
        },
        {
            .prim = lex::type::Keyword,
            .sem = lex::type::Keyword,
            .m = lex::mnemonic::Case,
            .name  = "Case",
            .d = lex::operand::Noop_,
            .token_location = {.begin = lex::lexem::Case},
            .flags{.V=0}
        },
        {
            .prim = lex::type::Keyword,
            .sem = lex::type::Keyword,
            .m = lex::mnemonic::Type,
            .name  = "Type",
            .d = lex::operand::Noop_,
            .token_location = {.begin = lex::lexem::Type},
            .flags{.V=0}
        },
        {
            .prim = lex::type::Prefix,
            .sem = lex::type::Unary|lex::type::Prefix|lex::type::Leaf|lex::type::Keyword|lex::type::Operator|lex::type::Hex,
            .m = lex::mnemonic::LowHex,
            .name  = "LowHex",
            .d = lex::operand::Noop_,
            .token_location = {.begin = lex::lexem::LowHex},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Prefix,
            .sem = lex::type::Unary|lex::type::Prefix|lex::type::Leaf|lex::type::Keyword|lex::type::Operator|lex::type::Hex,
            .m = lex::mnemonic::UpHex,
            .name  = "UpHex",
            .d = lex::operand::Noop_,
            .token_location = {.begin = lex::lexem::UpHex},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Prefix,
            .sem = lex::type::Unary|lex::type::Prefix|lex::type::Operator,
            .m = lex::mnemonic::Cosinus,
            .name  = "Cosinus",
            .d = lex::operand::Unary,
            .token_location = {.begin = lex::lexem::Cosinus},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Prefix,
            .sem = lex::type::Keyword|lex::type::Unary|lex::type::Prefix|lex::type::Operator,
            .m = lex::mnemonic::ArcCosinus,
            .name  = "ArcCosinus",
            .d = lex::operand::Unary,
            .token_location = {.begin = lex::lexem::ArcCosinus},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Prefix,
            .sem = lex::type::Keyword|lex::type::Unary|lex::type::Prefix|lex::type::Operator,
            .m = lex::mnemonic::Tangent,
            .name  = "Tangent",
            .d = lex::operand::Unary,
            .token_location = {.begin = lex::lexem::Tangent},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Prefix,
            .sem = lex::type::Keyword|lex::type::Unary|lex::type::Prefix|lex::type::Operator,
            .m = lex::mnemonic::ArcTangent,
            .name  = "ArcTangent",
            .d = lex::operand::Unary,
            .token_location = {.begin = lex::lexem::ArcTangent},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Prefix,
            .sem = lex::type::Keyword|lex::type::Unary|lex::type::Prefix|lex::type::Operator,
            .m = lex::mnemonic::Sinus,
            .name  = "Sinus",
            .d = lex::operand::Unary,
            .token_location = {.begin = lex::lexem::Sinus},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Prefix,
            .sem = lex::type::Keyword|lex::type::Unary|lex::type::Prefix|lex::type::Operator,
            .m = lex::mnemonic::ArcSinus,
            .name  = "ArcSinus",
            .d = lex::operand::Unary,
            .token_location = {.begin = lex::lexem::ArcSinus},
            .flags{.V=1}
        },
        {
            .prim = lex::type::Keyword,
            .sem = lex::type::Keyword,
            .m = lex::mnemonic::Object,
            .name  = "Object",
            .d = lex::operand::Identifier,
            .token_location = {.begin = lex::lexem::Object},
            .flags{.V=0}
        },
        {
            .prim = lex::type::Keyword,
            .sem = lex::type::Keyword,
            .m = lex::mnemonic::Static,
            .name  = "Static",
            .d = lex::operand::Identifier,
            .token_location = {.begin = lex::lexem::Static},
            .flags{.V=0}
        },
        {
            .prim = lex::type::Keyword,
            .sem = lex::type::Keyword,
            .m = lex::mnemonic::This,
            .name  = "This",
            .d = lex::operand::Identifier,
            .token_location = {.begin = lex::lexem::This},
            .flags{.V=1}
        }
    };

    return ref_table.size();
}




// size_t ArithmeticLexemes::DeclareTable()
// {
//     return token_table::DeclareTable();
// }


token_table::~token_table()
{
    ref_table.clear(); //oops!!!!!!

}

lex_token token_table::scan(const char* C)
{
    //log::Debug() << " :" << *C;
    if(ref_table.empty())
    {
        log::warning() << " tokens reference table is empty";
        return {};
    }

    int unicode = 0;
    if (!*C)
        return {};

    for (auto token : ref_table)
    {
        //log::Debug() << "Token Ref loop:'" << Color::Yellow << token.name << Color::Reset << ": (" << Color::HotPink4 << token.token_location.begin << Color::Reset << "<=>" << Color::Lime << *C << Color::Reset << "):";
        std::string_view::iterator crs = C;
        std::string_view::iterator rtxt = token.token_location.begin;
        unicode = 0; // oops...
        //std::size_t sz = std::strlen(rtxt);

        if(*crs != *rtxt) {
            //log::Debug() << *crs << " != " << *rtxt;
            continue;
        }
        //log::Debug() << *crs << " <==> " << *rtxt;
        while ((rtxt && crs) && (*crs && *rtxt) && (*crs == *rtxt))
        {
            if (*crs < 0)
                ++unicode; ///< @note oui/ yes; Soon/Bientôt je supporte quelques symboles UTF-8 (pi, xor,...)

            ++crs;
            ++rtxt;
            //log::Debug() << *crs << " <==> " << ( rtxt ?  *rtxt : ' ');
        }
        if (!rtxt || (*rtxt == 0))
        {
            if (*crs && !isspace(*crs))
            {
                if ((isalnum(*crs) || (*crs == '_')) && !token.has_type(lex::type::Operator|lex::type::Punc|lex::type::Keyword))
                    continue;
            }

            token.token_location.begin = C;
            token.token_location.end = --crs;
            token.token_location.length = (token.token_location.end - token.token_location.begin)+1;
            return token;
        }
    }

    log::debug() << " No match.";
    return {};
}

token_table &token_table::operator<<(lex_token &NewToken)
{
    prod_table.emplace_back(NewToken);
    return *this;
}

void token_table::dump_reference_table() const
{
    log::debug() << " Dump the Tokens Reference Table:\n";

    for(auto const& token : ref_table)
        log::out() << token.details();
}



lex_token const &token_table::get(std::string_view mnemonic_name)
{
    if(ref_table.empty())
        throw log::exception() [ log::error() << " Tokens Reference Table is empty!"];

    for(auto const& Token : ref_table)
        if(Token.name == mnemonic_name) return Token;

    throw log::exception() [ log::error() << " Tokens identified by '" << color::yellow << mnemonic_name << color::reset << "' Is not in this table."];
}

void token_table::dump_production_table()
{
    log::debug() << " Dump the Tokens Product Table:" << log::fn::endl;

    for(auto const& token : prod_table)
        log::out() << token.details();
}

lex_token const &token_table::get(lex::mnemonic::T M)
{
    for(auto const& token : ref_table)
    {
        if(token.m == M) return token;
    }
    throw log::exception()[ log::error()  << " Tokens identified by Enumerator " << color::yellow << static_cast<int>(M) << color::reset << " Is not in this table."];
}


}
