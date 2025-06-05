#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// List of keywords for C language (common subset)
const char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue",
    "default", "do", "double", "else", "enum", "extern",
    "float", "for", "goto", "if", "int", "long",
    "register", "return", "short", "signed", "sizeof",
    "static", "struct", "switch", "typedef", "union",
    "unsigned", "void", "volatile", "while", NULL
};

// List of operators (common subset)
const char *operators[] = {
    "+", "-", "*", "/", "%",    // arithmetic
    "++", "--",
    "==", "!=", "<", "<=", ">", ">=", // relational
    "=", "+=", "-=", "*=", "/=", "%=", // assignment
    "&&", "||", "!",           // logical
    "&", "|", "^", "~",        // bitwise
    "<<", ">>",
    "?", ":", ".", ",", ";",   // misc
    "->",
    "(", ")", "{", "}", "[", "]",
    NULL
};

int is_keyword(const char *str) {
    for (int i = 0; keywords[i] != NULL; i++) {
        if (strcmp(str, keywords[i]) == 0) return 1;
    }
    return 0;
}

int is_operator(const char *str) {
    for (int i = 0; operators[i] != NULL; i++) {
        if (strcmp(str, operators[i]) == 0) return 1;
    }
    return 0;
}

int is_identifier_start(char c) {
    return (isalpha(c) || c == '_');
}

int is_identifier_char(char c) {
    return (isalnum(c) || c == '_');
}

// Function to read the entire input file contents
char* read_file_contents(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Error: Could not open file %s\n", filename);
        return NULL;
    }
    fseek(fp, 0, SEEK_END);
    long length = ftell(fp);
    rewind(fp);

    char *buffer = (char*) malloc(length + 1);
    if (!buffer) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        fclose(fp);
        return NULL;
    }

    fread(buffer, 1, length, fp);
    buffer[length] = '\0';

    fclose(fp);
    return buffer;
}

// Attempt to extract operator tokens (some are multi-character)
int operator_length(const char *s) {
    // Check all operators against the start of s and return the length of matching operator

    // We'll check from longest operator lengths (3 chars max here for ">>", "<<" and "->")
    static const char *op_list[] = {
        "++", "--", "==", "!=", "<=", ">=", "+=", "-=", "*=", "/=", "%=",
        "&&", "||", "<<", ">>", "->",
        "+", "-", "*", "/", "%", "<", ">", "=", "!", "&", "|", "^", "~",
        "?", ":", ".", ",", ";", "(", ")", "{", "}", "[", "]",
        NULL
    };

    for (int i = 0; op_list[i] != NULL; i++) {
        size_t len = strlen(op_list[i]);
        if (strncmp(s, op_list[i], len) == 0) {
            return (int)len;
        }
    }
    return 0;
}
 
void lexical_analyze(const char *code) {
    const char *p = code;
    char token[256];
    int token_len = 0;

    printf("Token\t\tType\n");
    printf("=====================\n");

    while (*p != '\0') {
        // Skip whitespace
        if (isspace(*p)) {
            p++;
            continue;
        }

        // Check for operator
        int op_len = operator_length(p);
        if (op_len > 0) {
            // Extract operator token
            strncpy(token, p, op_len);
            token[op_len] = '\0';
            printf("%-15s Operator\n", token);
            p += op_len;
            continue;
        }

        // Check for identifier or keyword
        if (is_identifier_start(*p)) {
            token_len = 0;
            while (is_identifier_char(*p)) {
                if (token_len < 255) {
                    token[token_len++] = *p;
                }
                p++;
            }
            token[token_len] = '\0';

            if (is_keyword(token)) {
                printf("%-15s Keyword\n", token);
            } else {
                printf("%-15s Identifier\n", token);
            }
            continue;
        }

        // Check for numeric literals - treat as unknown/ignore tokens here
        if (isdigit(*p)) {
            token_len = 0;
            while (isdigit(*p) || *p == '.') {
                if (token_len < 255) {
                    token[token_len++] = *p;
                }
                p++;
            }
            token[token_len] = '\0';
            // We do not categorize numeric literals as requested; just skip or print as unknown
            printf("%-15s Literal\n", token);
            continue;
        }

        // If none matched, print as unknown and advance
        printf("%-15c Unknown\n", *p);
        p++;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    char *code = read_file_contents(argv[1]);
    if (!code) return 1;

    printf("Lexical Analysis of file: %s\n\n", argv[1]);
    lexical_analyze(code);

    free(code);
    return 0;
}

/*
Sample output (for input file containing: 

int main() {
  int a = 5;
  a++;
  if (a >= 5) {
    return a;
  }
}

would be:

Lexical Analysis of file: input.c

Token           Type
=====================
int             Keyword
main            Identifier
(               Operator
)               Operator
{               Operator
int             Keyword
a               Identifier
=               Operator
5               Literal
;               Operator
a               Identifier
++              Operator
;               Operator
if              Keyword
(               Operator
a               Identifier
>=              Operator
5               Literal
)               Operator
{               Operator
return          Keyword
a               Identifier
;               Operator
}               Operator
}               Operator

*/


