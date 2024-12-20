#include <iostream>
#include <vector>

using namespace std;

const int RUN = 32;

vector<int> globe_vector(0);
pthread_mutex_t mut;

using partition = pair<int, int>;
typedef struct{
    int l;
    int m;
    int r;
}triple_partition;


void printArray(vector<int>& arr)
{
    for (int elem : arr)
        printf("%d ", elem);
    printf("\n");
}

void insertionSort(int left, int right)
{
    for (int i = left + 1; i <= right; i++) {
        int temp = globe_vector[i];
        int j = i - 1;
        while (j >= left && globe_vector[j] > temp) {
            globe_vector[j + 1] = globe_vector[j];
            j--;
        }
        globe_vector[j + 1] = temp;
    }
}
void* inS(void* part)
{
    int left = ((partition*)part)->first;
    int right = ((partition*)part)->second;
    insertionSort(left, right);
    pthread_exit(0);
    return 0;
}

void merge(int l, int m, int r)
{
    int len1 = m - l + 1, len2 = r - m;
    int left[len1], right[len2];
    for (int i = 0; i < len1; i++)
        left[i] = globe_vector[l + i];
    for (int i = 0; i < len2; i++)
        right[i] = globe_vector[m + 1 + i];

    int i = 0;
    int j = 0;
    int k = l;

    while (i < len1 && j < len2) {
        if (left[i] <= right[j]) {
            globe_vector[k] = left[i];
            i++;
        }
        else {
            globe_vector[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < len1) {
        globe_vector[k] = left[i];
        k++;
        i++;
    }

    while (j < len2) {
        globe_vector[k] = right[j];
        k++;
        j++;
    }
}
void* mr(void* part){
    int l = ((triple_partition*)part)->l;
    int m = ((triple_partition*)part)->m;
    int r = ((triple_partition*)part)->r;
    merge(l, m, r);
    pthread_exit(0);
    return 0;
}

void timSort(int thread_count)
{
    int n = globe_vector.size();
    pthread_t tid[thread_count];

    vector<partition> to_take(0);
    for (int i = 0; i < n; i += RUN){
        to_take.push_back(partition(i, min((i + RUN - 1), (n - 1))));
    }

    int n_parts = to_take.size();
    int ind = 0;
    while(n_parts > 0){
        for(int j = 0; j < min(n_parts, thread_count); ++j){
            pthread_create(&tid[j%thread_count], NULL, inS, &(to_take[ind%to_take.size()]));
            ++ind;
        }
        for(int k = 0; k < min(n_parts, thread_count); ++k){
            pthread_join(tid[k%thread_count], NULL);
        }
        n_parts-=thread_count;
    }

    vector<triple_partition> to_merge;
    for (int size = RUN; size < n; size = 2 * size) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1;
            int right = min((left + 2 * size - 1), (n - 1));
            if (mid < right){
                merge(left, mid, right);
            }
        }
    }
}


int main(int argc, char* argv[])
{
    if (argc != 2) {
        perror("\nНет потоков\n");
        exit(EXIT_FAILURE);
    }
    if(atoi(argv[1]) < 1 ){
        perror("\nОшибка, число от 1 до 4 введите\n");
        exit(EXIT_FAILURE);
    }
    const int thread_count = atoi(argv[1]);
    int tmp;
    printf("Напишите массив: ");
    while(scanf("%d", &tmp) > 0){
        globe_vector.push_back(tmp);
    }
    timSort(thread_count);
    printf("\nМассив после сортировки: ");
    printArray(globe_vector);\
    
    printf("\nРазмер массива %ld\n", globe_vector.size());
    return 0;
}

// g++ -o main main.cpp -lpthread
// ./main 4
// strace -o output.txt ./main