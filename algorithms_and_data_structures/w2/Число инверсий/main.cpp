// Число инверсий

// Инверсией в последовательности чисел A называется такая ситуация, когда i<j, а Ai>Aj.

// Дан массив целых чисел. Ваша задача — подсчитать число инверсий в нем.

// Подсказка: чтобы сделать это быстрее, можно воспользоваться модификацией 
// сортировки слиянием.

// Формат входного файла
// В первой строке входного файла содержится число n(1<=n<=10^5) — число элементов в массиве. 
// Во второй строке находятся  целых чисел, по модулю не превосходящих 10^9.

// Формат выходного файла
// В выходной файл надо вывести число инверсий в массиве.


#include <fstream>


int merge(int *a, int l, int m, int r)
{
    int i, j, k, inv;
    int lsize = m - l + 1, rsize = r - m;
    int *left_array = new int [lsize];
    int *right_array = new int [rsize];
    
    for (i = 0; i < lsize; ++i)
        left_array[i] = a[l + i];
    for (j = 0; j < rsize; ++j)
        right_array[j] = a[m + 1 + j];
    
    i = 0, j = 0, k = l, inv = 0;
    
    while (i < lsize && j < rsize) {
        if (left_array[i] <= right_array[j])
            a[k++] = left_array[i++];
        else {
            a[k++] = right_array[j++];
            inv += lsize - i + 2;
        }
    }
    
    while (i < lsize)
        a[k++] = left_array[i++];
    while (j < rsize)
        a[k++] = right_array[j++];
    
    delete left_array;
    delete right_array;
    
    return inv;
}


int mergesort(int *a, int l, int r, std::ofstream &fout)
{
    if (l >= r)
        return 0;
    
    int m = (r + l) / 2, inv = 0;
    
    mergesort(a, l, m, fout);
    mergesort(a, m + 1, r, fout);
    
    return merge(a, l, m, r);
}


int main()
{
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");
    
    int n, result = 0;
    fin >> n;
    int *array = new int [n];
    
    for (int i = 0; i < n; ++i)
        fin >> array[i];
    
    fout << mergesort(array, 0, n - 1, fout) << '\n';
    
    delete [] array;
    
    return 0;
}
