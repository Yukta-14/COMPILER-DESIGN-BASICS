# INTERNSHIP TASK - 03

# COMPILER-DESIGN-BASICS

COMPANY: CODTECH IT SOLUTIONS

 NAME: YUKTA ANAND

 INTERN ID: CT04DN1416

 DOMAIN: C PROGRAMMING

 DURATION: 4 WEEKS

 MENTOR: NEELA SANTOSH

#  📘 Theory of the Program and Lexical Analyzer Explanation


# 🔍 What is Lexical Analysis?

Lexical analysis is the first phase of a compiler, responsible for reading source code and converting it into a sequence of tokens.
A token is a group of characters representing a meaningful element such as:

a) Keywords (int, return)

b) Identifiers (main, a)

c) Operators (=, ++)

d) Separators (;, (), {})

e) Literals (5, 3.14, etc.)

# ✅ Theory of the Program

This C program implements a simple lexical analyzer, designed to:

1. Read a source file (e.g., a .c file)

2. Parse the content

3. Identify and classify tokens

4. Display each token along with its type

# 🧠 How It Works – Step-by-Step

1. Reading the Input File :-
   
read_file_contents() reads the entire content of a file into a dynamically allocated buffer.
     
     c
       char *code = read_file_contents(argv[1]);
       
2. Tokenization via lexical_analyze() :-
   
This function loops through each character of the source code and uses logic to classify different elements.

2.1 Whitespace Handling

    c
        if (isspace(*p)) {
            p++;
            continue;
       }
Skips spaces, newlines, and tabs.

2.2 Operator Detection

    c
       int op_len = operator_length(p);
       
-> Uses the operator_length() helper to match multi-character operators first (like ++, ==).

-> If matched, prints as Operator.

2.3 Keyword or Identifier

    c
      if (is_identifier_start(*p)) {

-> Starts with letter or _.

-> Reads until non-alphanumeric character.

-> Uses is_keyword() to decide:-

 i) If it matches a reserved word → Keyword
 
 ii) Else → Identifier

2.4 Literals (Numbers)

    c
       if (isdigit(*p)) {
       
-> Collects digits (and optionally a decimal point).

-> Marks as Literal.

2.5 Unknown Characters

-> If none of the above matches, it's marked as Unknown.

3. Token Output :-

All tokens are printed in a table-like format:

    text
         Token           Type
         =====================
         int             Keyword
         main            Identifier
          ...
          
# 🛠️ What Is a Simple Lexical Analyzer Tool?

A Lexical Analyzer Tool (or lexer) is a utility or program that:

-> Scans source code linearly

-> Identifies meaningful units (tokens)

-> Acts as the input stage for compilers or interpreters

This tool does not check syntax or semantics — just breaks the source into tokens.

# ✨ Key Features of This Tool :-

-> Handles common C language keywords and operators

-> Categorizes:

    Keywords

    Identifiers

    Operators

    Literals

-> Ignores or flags unknown symbols

-> Works from input files, making it useful for small-scale compiler design experiments

# 📌 Limitations :-

-> No handling of comments (// or /* */)

-> No string literals or character constants

-> No preprocessor directives (#include)

-> Limited to C language subset

-> No error recovery or diagnostics

# 📚 Applications :-

-> Teaching compiler design

-> Building early-stage compilers

-> Code analysis tools

-> Static analysis or syntax highlighting backends

# ✅ Summary
This program demonstrates the core concept of lexical analysis — extracting tokens from source code — using plain C.
It shows how a simple lexer works without relying on external libraries or lexer generators like Lex or Flex.


# OUTPUT

![Image](https://github.com/user-attachments/assets/7be26340-d58e-47c2-93c0-d68256a8b7cf)

# simple_lexical_analyzer tool

![Image](https://github.com/user-attachments/assets/81aac50c-164a-4628-9518-e3fbbe8eddce)

# analyzer preview

![Image](https://github.com/user-attachments/assets/35b5db37-0232-49b4-aa28-a6ea8e8588af)
