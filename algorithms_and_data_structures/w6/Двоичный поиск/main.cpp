// Двоичный поиск

// Дан массив из n элементов, упорядоченный в порядке неубывания, и m запросов: 
// найти первое и последнее вхождение некоторого числа в массив. Требуется 
// ответить на эти запросы.

// Формат входного файла
// В первой строке входного файла содержится одно число n — размер массива (1<=n<=10^5). 
// Во второй строке находятся n чисел в порядке неубывания — элементы массива. 
// В третьей строке находится число m — число запросов (1<=m<=10^5). В следующей строке 
// находятся m чисел — запросы. Элементы массива и запросы являются целыми 
// числами, неотрицательны и не превышают 10^9.

// Формат выходного файла
// Для каждого запроса выведите в отдельной строке номер (индекс) первого и 
// последнего вхождения этого числа в массив. Ecли числа в массиве нет, 
// выведите два раза -1.


#include <fstream>


int second_pos_searching(int *a, int l_index, int n, int x)
{
    int l = l_index;
    int r = n;
    
    while (l < r - 1) {
        int m = (l + r) / 2;
        
        (a[m] > x) ? r = m : l = m;
    }
    
    return l;
}


void binary_search(int *a, int n, int x, std::ofstream &fout)
{
    int l = -1;
    int r = n;
    
    while (r > l + 1) {
        int m = (l + r) / 2;
        
        (a[m] < x) ? l = m : r = m;
    }
    
    if (r < n && a[r] == x) {
        int r2 = r;
        
        if (r < n - 1 && a[r + 1] == x)
            r2 = second_pos_searching(a, l, n, x);
        
        fout << r + 1 << " " << r2 + 1 << "\n";
    } else
        fout << "-1 -1\n";
}


int main()
{
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");
    
    int n;
    fin >> n;
    int *a = new int [n + 1];
    
    for (int i = 0; i < n; ++i)
        fin >> a[i];
    
    int m, req;
    fin >> m;
    
    for (int i = 0; i < m; ++i) {
        fin >> req;
        binary_search(a, n, req, fout);
    }
    
    delete [] a;
    
    return 0;
}
