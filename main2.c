#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

typedef struct word {
    int count;
    char *w;
} WORD;

WORD *words[100000];
int totalw = 0;

char *getword(FILE *F);
int cmpword_alpha(const void *a, const void *b);
int cmpword_quant(const void *a, const void *b);

int main(int argc, char *argv[])
{
    FILE *IN, *OUT1, *OUT2;
    char *pword;
    int i, found;
    
    if (argc < 2)
    {
        printf("Need files\n");
        return 1;
    }
    
    for (i = 1; i < argc; i++)
    {
        char filepath[256];
        snprintf(filepath, sizeof(filepath), "texts/%s", argv[i]);
        
        IN = fopen(filepath, "r");
        if (IN == NULL) {
            printf("Cannot open file: %s\n", filepath);
            continue;
        }
        
        while ((pword = getword(IN)) != NULL)
        {
            found = 0;
            for (int j = 0; j < totalw; j++) {
                if (strcmp(words[j]->w, pword) == 0) {
                    words[j]->count++;
                    found = 1;
                    break;
                }
            }
            
            if (!found && totalw < 100000) {
                words[totalw] = (WORD*)malloc(sizeof(WORD));
                words[totalw]->w = (char*)malloc(strlen(pword) + 1);
                strcpy(words[totalw]->w, pword);
                words[totalw]->count = 1;
                totalw++;
            }
            
            free(pword);
        }
        fclose(IN);
    }
    
    OUT1 = fopen("alphabetical.txt", "w");
    OUT2 = fopen("frequency.txt", "w");
    
    qsort(words, totalw, sizeof(WORD*), cmpword_alpha);
    for (i = 0; i < totalw; i++) {
        fprintf(OUT1, "%s: %d\n", words[i]->w, words[i]->count);
    }
    
    qsort(words, totalw, sizeof(WORD*), cmpword_quant);
    for (i = 0; i < totalw; i++) {
        fprintf(OUT2, "%s: %d\n", words[i]->w, words[i]->count);
    }
    
    fclose(OUT1);
    fclose(OUT2);
    
    for (i = 0; i < totalw; i++) {
        free(words[i]->w);
        free(words[i]);
    }
    
    return 0;
}

char *getword(FILE *F)
{
    static char buffer[256];
    int c, index = 0;
    
    while ((c = fgetc(F)) != EOF && !isalpha(c));
    if (c == EOF) return NULL;
    
    do {
        if (index < 255) {
            buffer[index++] = tolower(c);
        }
        c = fgetc(F);
    } while (c != EOF && (isalpha(c) || isdigit(c)));
    
    buffer[index] = '\0';
    
    if (strlen(buffer) == 0) return NULL;
    
    char *result = (char*)malloc(strlen(buffer) + 1);
    strcpy(result, buffer);
    return result;
}

int cmpword_alpha(const void *a, const void *b)
{
    WORD *wa = *(WORD**)a;
    WORD *wb = *(WORD**)b;
    return strcmp(wa->w, wb->w);
}

int cmpword_quant(const void *a, const void *b)
{
    WORD *wa = *(WORD**)a;
    WORD *wb = *(WORD**)b;
    return wb->count - wa->count;
}