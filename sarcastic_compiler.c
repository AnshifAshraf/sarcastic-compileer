#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024

int contains(const char *line, const char *word) {
    return strstr(line, word) != NULL;
}

void print_sarcasm(const char *line) {
    if (contains(line, "expected ';'")) {
        printf("SARCASM: Missing a semicolon? Bold move.\n");
    } 
    else if (contains(line, "undeclared")) {
        printf("SARCASM: That variable hasn't been declared. Maybe it's imaginary.\n");
    } 
    else if (contains(line, "No such file or directory")) {
        printf("SARCASM: The file is missing. Perhaps it ran away?\n");
    } 
    else if (contains(line, "expected expression")) {
        printf("SARCASM: Expected an expression, got a dramatic pause instead.\n");
    } 
    else if (contains(line, "redefinition")) {
        printf("SARCASM: Redefinition detected - cloning isn't always legal.\n");
    } 
    else if (contains(line, "conflicting types")) {
        printf("SARCASM: Conflicting types - your variable is having an identity crisis.\n");
    } 
    else if (contains(line, "expected declaration or statement at end of input")) {
        printf("SARCASM: You just stopped writing code mid-sentence. Cliffhanger!\n");
    } 
    else {
        printf("RAW: %s", line);
    }
}

int main() {
    char filename[256];
    char cmd[512];
    char line[MAX_LINE];

    printf("Enter C file name to compile: ");
    scanf("%255s", filename);

    snprintf(cmd, sizeof(cmd), "gcc %s -o temp_out 2> temp_errors.txt", filename);
    system(cmd);

    FILE *errFile = fopen("temp_errors.txt", "r");
    if (!errFile) {
        perror("Error opening temp_errors.txt");
        return 1;
    }

    int hasError = 0;
    while (fgets(line, sizeof(line), errFile)) {
        hasError = 1;
        print_sarcasm(line);
    }

    fclose(errFile);

    if (!hasError) {
        printf("? Compilation successful. No sarcasm needed!\n");
    }

    remove("temp_errors.txt");
    remove("temp_out");

    return 0;
}
