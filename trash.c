/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 17:48:47 by dwianni           #+#    #+#             */
/*   Updated: 2025/03/28 15:53:58 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef enum {
    TOKEN_INTEGER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_EOF,
    TOKEN_INVALID
} TokenType;

typedef struct {
    TokenType type;
    char *value;
} Token;

Token* new_token(TokenType type, char *value) {
    Token *token = malloc(sizeof(Token));
    token->type = type;
    token->value = value;
    return token;
}

void free_token(Token *token) {
    free(token->value);
    free(token);
}

Token* lexer(char *input) {
    int length = strlen(input);
    int i = 0;

    while (i < length) {
        if (isdigit(input[i])) {
            int start = i;
            while (i < length && isdigit(input[i])) i++;
            char *num = strndup(input + start, i - start);
            return new_token(TOKEN_INTEGER, num);
        } else if (input[i] == '+') {
            i++;
            return new_token(TOKEN_PLUS, strndup("+", 1));
        } else if (input[i] == '-') {
            i++;
            return new_token(TOKEN_MINUS, strndup("-", 1));
        } else if (input[i] == '*') {
            i++;
            return new_token(TOKEN_STAR, strndup("*", 1));
        } else if (input[i] == '/') {
            i++;
            return new_token(TOKEN_SLASH, strndup("/", 1));
        } else if (input[i] == '(') {
            i++;
            return new_token(TOKEN_LPAREN, strndup("(", 1));
        } else if (input[i] == ')') {
            i++;
            return new_token(TOKEN_RPAREN, strndup(")", 1));
        } else if (isspace(input[i])) {
            i++;
        } else {
            return new_token(TOKEN_INVALID, strndup(&input[i], 1));
        }
    }

    return new_token(TOKEN_EOF, NULL);
}

int main() {
    char *input = "12 + 34 * (56 - 78)";
    Token *token;
    while ((token = lexer(input))->type != TOKEN_EOF) {
        printf("Token: %d, Value: %s\n", token->type, token->value);
        free_token(token);
    }
    free_token(token);
    return 0;
}
*/

/*
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef enum {
    TOKEN_INTEGER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_EOF,
    TOKEN_INVALID
} TokenType;

typedef struct {
    TokenType type;
    char *value;
} Token;

Token* new_token(TokenType type, char *value) {
    Token *token = malloc(sizeof(Token));
    token->type = type;
    token->value = value;
    return token;
}

void free_token(Token *token) {
    free(token->value);
    free(token);
}

Token* lexer(char *input) {
    int length = strlen(input);
    int i = 0;

    while (i < length) {
        if (isdigit(input[i])) {
            int start = i;
            while (i < length && isdigit(input[i])) i++;
            char *num = strndup(input + start, i - start);
            return new_token(TOKEN_INTEGER, num);
        } else if (input[i] == '+') {
            i++;
            return new_token(TOKEN_PLUS, strndup("+", 1));
        } else if (input[i] == '-') {
            i++;
            return new_token(TOKEN_MINUS, strndup("-", 1));
        } else if (input[i] == '*') {
            i++;
            return new_token(TOKEN_STAR, strndup("*", 1));
        } else if (input[i] == '/') {
            i++;
            return new_token(TOKEN_SLASH, strndup("/", 1));
        } else if (input[i] == '(') {
            i++;
            return new_token(TOKEN_LPAREN, strndup("(", 1));
        } else if (input[i] == ')') {
            i++;
            return new_token(TOKEN_RPAREN, strndup(")", 1));
        } else if (isspace(input[i])) {
            i++;
        } else {
            return new_token(TOKEN_INVALID, strndup(&input[i], 1));
        }
    }

    return new_token(TOKEN_EOF, NULL);
}

typedef struct ASTNode {
    TokenType type;
    struct ASTNode *left;
    struct ASTNode *right;
    char *value;
} ASTNode;

ASTNode* new_ast_node(TokenType type, char *value) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = type;
    node->left = NULL;
    node->right = NULL;
    node->value = value;
    return node;
}

ASTNode* parse_expr(Token **tokens, int *index);
ASTNode* parse_term(Token **tokens, int *index);
ASTNode* parse_factor(Token **tokens, int *index);

ASTNode* parse_expr(Token **tokens, int *index) {
    ASTNode *left = parse_term(tokens, index);
    while (tokens[*index]->type == TOKEN_PLUS || tokens[*index]->type == TOKEN_MINUS) {
        Token *op = tokens[*index];
        (*index)++;
        ASTNode *right = parse_term(tokens, index);
        ASTNode *node = new_ast_node(op->type, op->value);
        node->left = left;
        node->right = right;
        left = node;
    }
    return left;
}

ASTNode* parse_term(Token **tokens, int *index) {
    ASTNode *left = parse_factor(tokens, index);
    while (tokens[*index]->type == TOKEN_STAR || tokens[*index]->type == TOKEN_SLASH) {
        Token *op = tokens[*index];
        (*index)++;
        ASTNode *right = parse_factor(tokens, index);
        ASTNode *node = new_ast_node(op->type, op->value);
        node->left = left;
        node->right = right;
        left = node;
    }
    return left;
}

ASTNode* parse_factor(Token **tokens, int *index) {
    if (tokens[*index]->type == TOKEN_INTEGER) {
        Token *num = tokens[*index];
        (*index)++;
        return new_ast_node(TOKEN_INTEGER, num->value);
    } else if (tokens[*index]->type == TOKEN_LPAREN) {
        (*index)++;
        ASTNode *node = parse_expr(tokens, index);
        if (tokens[*index]->type != TOKEN_RPAREN) {
            printf("Erreur de syntaxe : parenthèse fermante attendue\n");
            exit(1);
        }
        (*index)++;
        return node;
    }
    return NULL;
}

int main() {
    char *input = "12 + 34 * (56 - 78)";
    Token *tokens[] = {
        lexer("12"),
        lexer("+"),
        lexer("34"),
        lexer("*"),
        lexer("("),
        lexer("56"),
        lexer("-"),
        lexer("78"),
        lexer(")"),
        lexer("\0")
    };
    int index = 0;
    ASTNode *ast = parse_expr(tokens, &index);
    // Affichage ou traitement de l'AST ici
    return 0;
}
*/
/*
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    // Vérifier qu'un fichier a été passé en argument
    char	*file = "out1";

    // Ouvrir le fichier en lecture
    int fd = open(file, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Créer un processus enfant avec fork
    pid_t pid = fork();
    
    if (pid == -1) {
        perror("fork");
        close(fd);
        return 1;
    }

    if (pid == 0) {
        // Dans le processus enfant

        // Rediriger l'entrée standard vers le fichier
        if (dup2(fd, STDIN_FILENO) == -1) {
            perror("dup2");
            close(fd);
            return 1;
        }

        // Fermer le descripteur de fichier après duplication
        close(fd);

        // Préparer les arguments pour execve
        char *args[] = { "cat", NULL };

        // Exécuter la commande 'cat' avec execve
        if (execve("/bin/cat", args, NULL) == -1) {
            perror("execve");
            return 1;
        }
    } else {
        // Dans le processus parent

        // Attendre la fin du processus enfant
        wait(NULL);
    }

    return 0;
}

*/
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main() {
    int pipe_fd[2];  // Déclaration du pipe
    const char *str = "Hello, this is a string for the file descriptor!";
    
    // Créer un pipe
    if (pipe(pipe_fd) == -1) {
        perror("Erreur pipe");
        return 1;
    }

    // Écrire la chaîne dans le pipe
    write(pipe_fd[1], str, strlen(str));  // Écriture dans le pipe (file descriptor 1)
    
    // Fermer le côté d'écriture du pipe
    close(pipe_fd[1]);

    // Lire la chaîne depuis le pipe
    char buffer[1024];
    ssize_t bytes_read = read(pipe_fd[0], buffer, sizeof(buffer)-1);  // Lecture depuis le pipe (file descriptor 0)

    if (bytes_read == -1) {
        perror("Erreur de lecture");
        return 1;
    }

    // Null-terminer la chaîne lue
    buffer[bytes_read] = '\0';

    // Afficher la chaîne lue
    printf("Contenu du pipe : %s\n", buffer);

    // Fermer le côté de lecture du pipe
    close(pipe_fd[0]);

    return 0;
}

