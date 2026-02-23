#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKEN 256

int afd(char *token) {
    int len = strlen(token);
    int estado = 0;
    int i;

    if (len == 0) return 0;

    // --- Incremento: ++ ---
    if (strcmp(token, "++") == 0) return 4;

    // --- Suma: + ---
    if (strcmp(token, "+") == 0) return 2;

    // --- AFD Entero: [0-9]+ ---
    estado = 0;
    for (i = 0; i < len; i++) {
        if (estado == 0) {
            if (isdigit(token[i])) estado = 1;
            else { estado = -1; break; }
        } else if (estado == 1) {
            if (isdigit(token[i])) estado = 1;
            else { estado = -1; break; }
        }
    }
    if (estado == 1) return 3;

    // --- AFD Id: [A-Za-z]([a-z]|[0-9])* ---
    estado = 0;
    for (i = 0; i < len; i++) {
        if (estado == 0) {
            if (isalpha(token[i])) estado = 1;
            else { estado = -1; break; }
        } else if (estado == 1) {
            if (islower(token[i]) || isdigit(token[i])) estado = 1;
            else { estado = -1; break; }
        }
    }
    if (estado == 1) return 1;

    return 0;
}

int main(int argc, char *argv[]) {
    FILE *archivo;
    char linea[MAX_TOKEN];
    int numLinea = 1;
    int resultado;
    char *nombres[] = {"NO ACEPTA", "Id", "Suma", "Entero", "Incremento"};

    if (argc < 2) {
        printf("Uso: ./afd <archivo.txt>\n");
        return 1;
    }

    archivo = fopen(argv[1], "r");

    if (archivo == NULL) {
        printf("ERROR: No se pudo abrir '%s'\n", argv[1]);
        return 1;
    }

    while (fgets(linea, MAX_TOKEN, archivo) != NULL) {
        int len = strlen(linea);
        if (len > 0 && linea[len - 1] == '\n')
            linea[len - 1] = '\0';

        resultado = afd(linea);

        if (resultado == 0) {
            printf("NO ACEPTA: '%s'\n", linea);
        } else {
            printf("ACEPTA: '%s' -> %s\n", linea, nombres[resultado]);
        }

        numLinea++;
    }

fclose(archivo);
return 0;
}