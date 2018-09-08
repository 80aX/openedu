// Сортировка пугалом

// «Сортировка пугалом» — это давно забытая народная потешка, которую восстановили 
// по летописям специалисты платформы «Открытое образование» специально для этого курса.

// Участнику под верхнюю одежду продевают деревянную палку, так что у него оказываются
// растопырены руки, как у огородного пугала. Перед ним ставятся  матрёшек в ряд. 
// Из-за палки единственное, что он может сделать — это взять в руки две матрешки 
// на расстоянии k друг от друга (то есть i-ую и (i+k)-ую), развернуться и поставить их 
// обратно в ряд, таким образом поменяв их местами.

// Задача участника — расположить матрёшки по неубыванию размера. Может ли он это 
// сделать?

// Формат входного файла
// В первой строчке содержатся числа n и k(1<=n,k<=10^5) — число матрёшек и размах рук.

// Во второй строчке содержится  целых чисел, которые по модулю не 
// превосходят 10^9 — размеры матрёшек.

// Формат выходного файла
// Выведите «YES», если возможно отсортировать матрёшки по неубыванию размера, 
// и «NO» в противном случае.


#include <fstream>


int checkorder(int *a, int n)
{
    for (int i = 1; i < n; ++i) {
        if (a[i] < a[i - 1])
            return 1;
    }
    
    return 0;
}


int split(int *a, int l, int r, int k)
{
    int x = a[l];
    int l_index = l, r_index = r, buff;
    
    while (l_index <= r_index) {
        while (a[l_index] < x)
            l_index += k;
        while (a[r_index] > x)
            r_index -= k;
            
        if (l_index <= r_index) {
            buff = a[l_index];
            a[l_index] = a[r_index];
            a[r_index] = buff;
            l_index += k;
            r_index -= k;
        }
    }
    
    return l_index;
}


void quicksort(int *a, int l, int r, int k)
{
    if (l == r)
        return;
    
    int m = split(a, l, r, k);
    
    quicksort(a, l, m - k, k);
    quicksort(a, m, r, k);
}


void pugalosort(int *a, int n, int k)
{
    if (k >= n)
        return;
    
    int r = ((int)(n - 1) / k) * k;
    
    for (int i = 0; i < k; ++i) {
        quicksort(a, i, r, k);
        r++;
        
        if (r > n - 1)
            r -= k;
    }
}


int main()
{
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");
    
    int n, k;
    fin >> n >> k;
    int *a = new int [n];
    
    for (int i = 0; i < n; ++i)
        fin >> a[i];
    
    pugalosort(a, n, k);
    
    if (checkorder(a, n))
        fout << "NO" << '\n';
    else
        fout << "YES" << '\n';
    
    delete [] a;
    
    return 0;
}
