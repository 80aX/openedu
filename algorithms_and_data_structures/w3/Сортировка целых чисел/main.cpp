// Сортировка целых чисел

// В этой задаче Вам нужно будет отсортировать много неотрицательных целых чисел.

// Вам даны два массива, A и B, содержащие соответственно n и m элементов. Числа, 
// которые нужно будет отсортировать, имеют вид Ai * Bi, где 1<=i<=n и 1<=j<=m. 
// Иными словами, каждый элемент первого массива нужно умножить на каждый элемент 
// второго массива.

// Пусть из этих чисел получится отсортированная последовательность C длиной n*m. 
// Выведите сумму каждого десятого элемента этой последовательности (то есть, 
// C1+C11+C21+...).

// Формат входного файла
// В первой строке содержатся числа n и m (1<=N,m<=6000) — размеры массивов. 
// Во второй строке cодержится n чисел — элементы массива A. Аналогично, в третьей 
// строке содержится m чисел — элементы массива B. Элементы массива неотрицательны 
// и не превосходят 40000.

// Формат выходного файла
// Выведите одно число — сумму каждого десятого элемента последовательности, 
// полученной сортировкой попарных произведенй элементов массивов A и B.


#include <fstream>


void merge(long long *a, int l, int m, int r)
{
    int i, j, k;
    int lsize = m - l, rsize = r - m;
    long long *left_array = new long long [lsize];
    long long *right_array = new long long [rsize];
    
    for (i = 0; i < lsize; ++i)
        left_array[i] = a[l + i];
    for (j = 0; j < rsize; ++j)
        right_array[j] = a[m + j];
    
    i = 0, j = 0, k = l;
    
    while (i < lsize && j < rsize) {
        if (left_array[i] <= right_array[j])
            a[k++] = left_array[i++];
        else
            a[k++] = right_array[j++];
    }
    
    while (i < lsize)
        a[k++] = left_array[i++];
    while (j < rsize)
        a[k++] = right_array[j++];
    
    delete [] left_array;
    delete [] right_array;
}


void mergesort(long long *a, int l, int r, int sub)
{
    for (int i = sub * 2; i <= r; i += sub) {
        merge(a, l, i - sub, i);
    }
}


void countsort(int *a, int n, int k)
{
    int i;
    int *b = new int [n + 1];
    int *c = new int [k + 1];
    
    for (i = 0; i <= k; ++i)
        c[i] = 0;
    for (i = 1; i <= n; ++i)
        c[a[i]]++;
    for (i = 1; i <= k; ++i)
        c[i] += c[i - 1];
    for (i = n; i > 0; --i) {
        b[c[a[i]]] = a[i];
        c[a[i]]--;
    }
    for (i = 1; i <= n; ++i)
        a[i] = b[i];
    
    delete [] b;
    delete [] c;
}


int main()
{
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");
    
    int n, m, i, j, k, max_value;
    fin >> n >> m;
    int max_length = (m > n) ? m : n;
    int min_length = (m < n) ? m : n;
    
    int *a = new int [n + 1];
    int *b = new int [m + 1];
    long long *c = new long long [n * m];
    
    for (i = 1, max_value = 0; i <= n; ++i) {
        fin >> a[i];
        if (a[i] > max_value)
            max_value = a[i];
    }
    
    countsort(a, n, max_value);
    
    for (j = 1, max_value = 0; j <= m; ++j) {
        fin >> b[j];
        if (b[j] > max_value)
            max_value = b[j];
    }
    
    countsort(b, m, max_value);
    
    int *temp;
    if (m < n) {
        temp = a;
        a = b;
        b = temp;
    }
    
    for (k = 0; k < n * m;) {
        for (i = 1; i <= min_length; ++i) {
            for (j = 1; j <= max_length; ++j) {
                c[k] = a[i] * b[j];
                k++;
            }
        }
    }
    
    if (min_length > 1)
        mergesort(c, 0, n * m, max_length);
    
    long long result = 0;
    for (i = 0; i < n * m; i += 10)
        result += c[i];
    
    fout << result << '\n';
    
    delete [] a;
    delete [] b;
    delete [] c;
    
    return 0;
}
