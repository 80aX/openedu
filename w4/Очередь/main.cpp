// Очередь

// Реализуйте работу очереди. Для каждой операции изъятия элемента выведите 
// ее результат.

// На вход программе подаются строки, содержащие команды. Каждая строка содержит 
// одну команду. Команда — это либо «+ N», либо «−». Команда «+ N» означает 
// добавление в очередь числа N, по модулю не превышающего 10^9. Команда «−» 
// означает изъятие элемента из очереди. Гарантируется, что размер очереди 
// в процессе выполнения команд не превысит 10^6 элементов.

// Формат входного файла
// В первой строке содержится M (1<=M<=10^6) — число команд. В последующих строках 
// содержатся команды, по одной в каждой строке.

// Формат выходного файла
// Выведите числа, которые удаляются из очереди с помощью команды «−», 
// по одному в каждой строке. Числа нужно выводить в том порядке, в котором 
// они были извлечены из очереди. Гарантируется, что извлечения из пустой 
// очереди не производится.


#include <fstream>


class queue_node
{
    private:
        int value;
        queue_node *next;
        queue_node *prev;
    
    public:
        queue_node() {
            value = 0;
            next = 0;
            prev = 0;
        }
        
        ~queue_node() {}
        
        queue_node(int v, queue_node *p) {
            value = v;
            prev = p;
            next = 0;
        }
        
        int get_value() {
            return value;
        }
        
        queue_node * get_next() {
            return next;
        }
        
        queue_node * get_prev() {
            return prev;
        }
        
        void set_next(queue_node *n) {
            next = n;
        }
        
        void set_prev(queue_node *p) {
            prev = p;
        }
};


class queue
{
    private:
        queue_node *first;
        queue_node *last;
    
    public:
        queue() {
            first = 0;
            last = 0;
        }
        
        ~queue() {
            queue_node *temp;
            
            while (last != 0) {
                temp = last;
                last = last -> get_prev();
                delete temp;
            }
        }
        
        void push(int value) {
            queue_node *new_node = new queue_node(value, last);
            
            if (first == 0)
                first = new_node;
            else
                last -> set_next(new_node);
            
            last = new_node;
        }
        
        int pop() {
            int value = first -> get_value();
            
            queue_node *temp = first;
            first = first -> get_next();
            
            if (first != 0)
                first -> set_prev(0);
            else
                last = last -> get_prev();
            
            delete temp;
            return value;
        }
        
        void processing() {
            std::ifstream fin("input.txt");
            std::ofstream fout("output.txt");
            
            int n, value;
            char operation;
            
            fin >> n;
            
            for (int i = 0; i < n; ++i) {
                fin >> operation;
                
                if (operation == '+') {
                    fin >> value;
                    push(value);
                } else {
                    fout << pop() << '\n';
                }
            }
        }
};


int main()
{
    queue test;
    test.processing();
    
    return 0;
}
