#include <stdio.h>
#include <ctype.h>  // для функции tolower

// множество гласных
#define GLASN (1u<<('a'-'a') | 1u<<('e'-'a') | 1u<<('i'-'a') | 1u<<('o'-'a') | 1u<<('u'-'a') | 1u<<('y'-'a'))

// функция порождения множества из заданной буквы
unsigned int char_to_set(char c) {
    c = tolower(c); // преобразуем в нижний регистр
    if (c < 'a' || c > 'z') {
        // если это не буква -- возвращаем пустое множество
        return 0;
    } else {
        return 1u << (c - 'a');
    }
}

int main() {
    int c;
    char last_char = '\0'; // переменная для последнего символа

    // чтение литер, пока не встретится '\n'
    while ((c = getchar()) != '\n') {  // для EOF заменить '\n' на 'EOF'
        if (isalpha(c)) {  // проверяем, является ли символ буквой
            last_char = c; // сохраняем последнюю букву
        }
    }

    // если последняя буква есть, проверяем её
    if (last_char != '\0') {
        unsigned int last_char_set = char_to_set(last_char); // множество из последней буквы
        if (last_char_set & GLASN) { // пересекаем с множеством гласных
            printf("YES");
        } else {
            printf("NO");
        }
    } else {
        printf("NO"); // если не было букв
    }

    return 0;
}
