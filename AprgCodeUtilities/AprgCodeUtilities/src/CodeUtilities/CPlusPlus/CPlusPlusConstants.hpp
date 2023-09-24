#pragma once

#define KEYWORD_OPERATORS \
    "typeid", "const_cast", "dynamic_cast", "reinterpret_cast", "static_cast", "sizeof", "new", "delete", "throw"

#define THREE_CHAR_OPERATORS "->*", "<<=", ">>="

#define TWO_CHAR_OPERATORS                                                        \
    "::", "++", "--", "->", ".*", "<<", ">>", "<=", ">=", "==", "!=", "&&", "||", \
        "+=", "-=", "*=", "/=", "%=", "&=", "^=", "|="

// should backslash be really included?
#define ONE_CHAR_OPERATORS                                                                                             \
    "(", ")", "[", "]", "{", "}", ";", ".", "+", "-", "!", "~", "*", "&", "/", "%", "<", ">", "^", "|", "?", ":", "=", \
        ",", "\\"

#define CPLUSPLUS_KEYWORDS                                                                                             \
    "alignas", "alignof", "and", "and_eq", "asm", "auto", "bitand", "bitor", "bool", "break", "case", "catch", "char", \
        "char16_t", "char32_t", "class", "compl", "const", "constexpr", "const_cast", "continue", "decltype",          \
        "default", "delete", "do", "double", "dynamic_cast", "else", "enum", "explicit", "export", "extern", "false",  \
        "float", "for", "friend", "goto", "if", "inline", "int", "long", "mutable", "namespace", "new", "noexcept",    \
        "not", "not_eq", "nullptr", "operator", "or", "or_eq", "private", "protected", "public", "register",           \
        "reinterpret_cast", "return", "short", "signed", "sizeof", "static", "static_assert", "static_cast", "struct", \
        "switch", "template", "this", "thread_local", "throw", "true", "try", "typedef", "typeid", "typename",         \
        "union", "unsigned", "using", "virtual", "void", "volatile", "wchar_t", "while", "xor", "xor_eq"

#define PRIMITIVE_TYPES                                                                                              \
    "bool", "char", "char16_t", "char32_t", "double", "float", "int", "long", "short", "signed", "unsigned", "void", \
        "wchar_t", "int8_t", "int16_t", "int32_t", "int64_t", "int_fast8_t", "int_fast16_t", "int_fast32_t",         \
        "int_fast64_t", "int_least8_t", "int_least16_t", "int_least32_t", "int_least64_t", "intmax_t", "intptr_t",   \
        "uint8_t", "uint16_t", "uint32_t", "uint64_t", "uint_fast8_t", "uint_fast16_t", "uint_fast32_t",             \
        "uint_fast64_t", "uint_least8_t", "uint_least16_t", "uint_least32_t", "uint_least64_t", "uintmax_t",         \
        "uintptr_t", "size_t"
