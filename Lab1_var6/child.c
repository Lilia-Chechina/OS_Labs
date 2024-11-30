#include <stdio.h>
#include <unistd.h>  // для read(), write(), dup2()
#include <sys/types.h>  // для работы с файловыми дескрипторами
#include <fcntl.h>   // для работы с файловыми дескрипторами
#include <string.h>  // для strtok(у-ль на саму строку[массив char], разделитель const)
#define buf_size 100  // длина буфера для хранения данных

// Этот файл реализует вычисления и вывод результатов для дочернего процесса.
int main() {
    char buffer[buf_size]; // буфер для накопления символов строки
    int result = 0;
    int count = 0;
    // Считываем из входного потока символ за символом
    while (read(STDIN_FILENO, buffer + count, 1) > 0) {  // read из <unistd.h>
    // buffer + count вычисляет адрес элемента в массиве buffer, соответствующий текущему индексу count 
    // если read указывает > 0, то выдаёт n прочитанных байтов
    // когда read возвращает 0, это значит, что файл или ввод закончился => по нашей логике программы прога завершится
        // Если встречен символ новой строки или конец файла
        if (buffer[count] == '\n' || buffer[count] == EOF) {
            buffer[count] = '\0';  // Завершаем строку нулевым символом
            
            int number;
            /* переменная number, которая будет использоваться для хранения каждого числа, 
            преобразованного из токена. Каждый раз, когда токен будет успешно преобразован в 
            целое число, это число будет добавлено к переменной result*/
            char *token = strtok(buffer, " ");
            /*В результате первого вызова strtok() будет возвращен указатель на первый токен (первое число) 
            в строке. Если строка buffer содержит "12 34 56", то token будет указывать на "12"*/
            while (token != NULL) {
                // Преобразуем строку в число с помощью sscanf
                if (sscanf(token, "%d", &number) == 1) { // если sscanf=1, то прочитано успешно и код внутри выполн
                    result += number; // Добавляем число к результату
                }
                // Переходим к следующему числу в строке
                token = strtok(NULL, " ");
            }

            // Пишем результат в стандартный вывод
            write(STDOUT_FILENO, &result, sizeof(result));

            // Сбрасываем все переменные для обработки следующей строки
            result = 0;
            count = 0;
        } else {
            count++;
        }
    }
    return 0;
}
