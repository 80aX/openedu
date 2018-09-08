// Очередь с приоритетами

// Реализуйте очередь с приоритетами. Ваша очередь должна поддерживать 
// следующие операции: добавить элемент, извлечь минимальный элемент, 
// уменьшить элемент, добавленный во время одной из операций.

// Формат входного файла
// В первой строке входного файла содержится число n(1<=n<=10^6) - число 
// операций с очередью.

// Следующие  строк содержат описание операций с очередью, по одному 
// описанию в строке. Операции могут быть следующими:

// A x — требуется добавить элемент  в очередь.
// X — требуется удалить из очереди минимальный элемент и вывести его 
// в выходной файл. Если очередь пуста, в выходной файл требуется 
// вывести звездочку «∗».
// D x y — требуется заменить значение элемента, добавленного в очередь 
// операцией A в строке входного файла номер x+1, на y. Гарантируется, что 
// в строке x+1 действительно находится операция A, что этот элемент не 
// был ранее удален операцией X, и что y меньше, чем предыдущее значение 
// этого элемента.
// В очередь помещаются и извлекаются только целые числа, не превышающие 
// по модулю 10^9.

// Формат выходного файла
// Выведите последовательно результат выполнения всех операций X, по одному 
// в каждой строке выходного файла. Если перед очередной операцией X очередь 
// пуста, выведите вместо числа звездочку «∗».


#include <fstream>
#include <climits>
#include <vector>


class priority_queue
{
    private:
        std::vector<std::pair<int, int> > a;
        int heap_size;
    
    public:
        priority_queue() {
            heap_size = 0;
        }
        
        ~priority_queue() {}
        
        int parent(int i) {
            return (i - 1) / 2;
        }
        
        int left_child(int i) {
            return 2 * i + 1;
        }
        
        int right_child(int i) {
            return 2 * i + 2;
        }
        
        void min_heapify(int i) {
            int lowest = i;
            int l = left_child(i);
            int r = right_child(i);
            
            if (l < heap_size && a[l].first < a[lowest].first)
                lowest = l;
            if (r < heap_size && a[r].first < a[lowest].first)
                lowest = r;
            
            if (lowest != i) {
                std::swap(a[i], a[lowest]);
                min_heapify(lowest);
            }
        }
        
        // void build_min_heap() {
            // heap_size = a.size();
            
            // for (int i = (heap_size - 2) / 2; i >= 0; --i) {
                // min_heapify(i);
            // }
        // }
        
        void decrease_key(int i, int key) {
            // if (key > a[i].first)
                // return;
            
            a[i].first = key;
            while (i > 0 && a[i].first < a[parent(i)].first) {
                std::swap(a[i], a[parent(i)]);
                i = parent(i);
            }
        }
        
        void index_searching(int x, int key) {
            int i = 0;
            
            while (a[i].second != x)
                i++;
            
            decrease_key(i, key);
        }
        
        void insert(int key, int n_line) {
            heap_size += 1;
            a.push_back(std::make_pair(INT_MAX, n_line));
            decrease_key(heap_size - 1, key);
        }
        
        void extract_min() {
            
            if (heap_size < 1) {
                fout << "*\n";
                return;
            }
            
            int current_min = a[0].first;
            a[0] = a[heap_size - 1];
            heap_size -= 1;
            a.pop_back();
            min_heapify(0);
            
            fout << current_min << "\n";
        }
        
        void processing() {
            std::ifstream fin("input.txt");
            std::ofstream fout("output.txt");
            
            int n, x, y;
            io >> n;
            char procedure;
            
            for (int i = 0; i < n; ++i) {
                io >> procedure;
                
                if (procedure == 'A') {
                    fin >> x;
                    insert(x, i + 1);
                } else if (procedure == 'X') {
                    extract_min();
                } else {
                    fin >> x >> y;
                    index_searching(x, y);
                }
            }
        }
};


int main()
{
    priority_queue test;
    test.processing();
    
    return 0;
}
