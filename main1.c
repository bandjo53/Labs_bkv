#include <stdio.h>
#include <ctype.h>

// Функция для проверки гласных букв
int isvowel(int c) {
    switch(tolower(c)) {
        case 'a': 
        case 'e':
        case 'i': 
        case 'o': 
        case 'u':
        case 'y': return 1;
    }
    return 0;
}

// Функция для проверки согласных букв
int isconsonant(int c) {
    return isalpha(c) && !isvowel(c);
}

int main() {
    FILE *F;
    char filename[100];
    int c;
    int total = 0, lines = 0, digits = 0, punct = 0, spaces = 0;
    int letters = 0, lower = 0, upper = 0, vowels = 0, consonants = 0;
    
    // Ввод имени файла с клавиатуры
    printf("Enter filename: ");
    scanf("%s", filename);
    
    // Открытие файла с проверкой
    F = fopen(filename, "r");
    if (F == NULL) {
        printf("Error: Cannot open file %s\n", filename);
        return 1;
    }
    
    // Чтение файла посимвольно
    while ((c = fgetc(F)) != EOF) {
        total++;
        
        if (c == '\n') lines++;
        if (isdigit(c)) digits++;
        if (ispunct(c)) punct++;
        if (isspace(c)) spaces++;
        if (isalpha(c)) {
            letters++;
            if (islower(c)) lower++;
            if (isupper(c)) upper++;
            if (isvowel(c)) vowels++;
            if (isconsonant(c)) consonants++;
        }
    }
    
    // Вывод результатов
    printf("File analysis results:\n");
    printf("Total characters: %d\n", total);
    printf("Lines: %d\n", lines);
    printf("Digits: %d\n", digits);
    printf("Punctuation marks: %d\n", punct);
    printf("Whitespace characters: %d\n", spaces);
    printf("Letters: %d\n", letters);
    printf("  Lowercase: %d\n", lower);
    printf("  Uppercase: %d\n", upper);
    printf("  Vowels: %d\n", vowels);
    printf("  Consonants: %d\n", consonants);
    
    fclose(F);
    return 0;
}