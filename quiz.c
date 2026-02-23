// dfa_tokens.c
#include <stdio.h>
#include <string.h>
#include <ctype.h>

static void rstrip_newline(char *s) {
    size_t n = strlen(s);
    while (n > 0 && (s[n-1] == '\n' || s[n-1] == '\r')) {
        s[n-1] = '\0';
        n--;
    }
}

static void trim_spaces(char *s) {
    // trim izquierda
    char *start = s;
    while (*start && isspace((unsigned char)*start)) start++;

    // mover al inicio
    if (start != s) memmove(s, start, strlen(start) + 1);

    // trim derecha
    size_t n = strlen(s);
    while (n > 0 && isspace((unsigned char)s[n-1])) {
        s[n-1] = '\0';
        n--;
    }
}

static int is_plus(const char *s) {
    return strcmp(s, "+") == 0;
}

static int is_increment(const char *s) {
    return strcmp(s, "++") == 0;
}

static int is_integer_1digit(const char *s) {
    return (strlen(s) == 1 && isdigit((unsigned char)s[0]));
}

static int is_id(const char *s) {
    // [A-Za-z]([a-z][0-9])*
    size_t len = strlen(s);
    if (len == 0) return 0;

    size_t i = 0;

    if (!isalpha((unsigned char)s[i])) return 0;
    i++;

    while (i < len) {
        if (!(s[i] >= 'a' && s[i] <= 'z')) return 0;
        i++;
        if (i >= len) return 0;
        if (!isdigit((unsigned char)s[i])) return 0;
        i++;
    }

    return 1;
}

static int accepts_token(const char *s) {
    // Orden: "++" primero
    if (is_increment(s)) return 1;
    else if (is_plus(s)) return 1;
    else if (is_integer_1digit(s)) return 1;
    else if (is_id(s)) return 1;
    else return 0;
}

int main(void) {
    FILE *f = fopen("archivo.txt", "r");
    if (!f) {
        perror("Error abriendo archivo.txt");
        return 1;
    }

    char line[1024];

    while (fgets(line, sizeof(line), f)) {
        char raw[1024];
        strncpy(raw, line, sizeof(raw));
        raw[sizeof(raw)-1] = '\0';

        rstrip_newline(line);
        // guardamos una versión original sin \n para imprimirla
        char original[1024];
        strncpy(original, line, sizeof(original));
        original[sizeof(original)-1] = '\0';

        trim_spaces(line);

        if (line[0] == '\0') {
            printf("\"%s\" NO ACEPTA\n", original);
            continue;
        }

        if (accepts_token(line)) {
            printf("\"%s\" ACEPTA\n", original);
        } else {
            printf("\"%s\" NO ACEPTA\n", original);
        }
    }

    fclose(f);
    return 0;
}