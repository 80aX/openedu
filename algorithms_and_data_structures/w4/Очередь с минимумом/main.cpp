// Очередь с минимумом

// Реализуйте работу очереди. В дополнение к стандартным операциям очереди, 
// необходимо также отвечать на запрос о минимальном элементе из тех, которые 
// сейчас находится в очереди. Для каждой операции запроса минимального элемента 
// выведите ее результат.

// На вход программе подаются строки, содержащие команды. Каждая строка содержит
// одну команду. Команда — это либо «+ N», либо «−», либо «?». Команда «+ N» означает 
// добавление в очередь числа N, по модулю не превышающего 10^9. Команда «−» означает 
// изъятие элемента из очереди. Команда «?» означает запрос на поиск минимального 
// элемента в очереди.

// Формат входного файла
// В первой строке содержится M (1<=M<=10^6) — число команд. В последующих строках 
// содержатся команды, по одной в каждой строке.

// Формат выходного файла
// Для каждой операции поиска минимума в очереди выведите её результат. Результаты 
// должны быть выведены в том порядке, в котором эти операции встречаются во входном 
// файле. Гарантируется, что операций извлечения или поиска минимума для пустой очереди 
// не производится.


#include <fstream>


class stack_node
{
    private:
        stack_node *next;
        long long value;
        long long min;
    
    public:
        stack_node() {
            next = 0;
            value = 0;
            min = 0;
        }
        
        stack_node(stack_node *n, long long v, long long m) {
            next = n;
            value = v;
            min = m;
        }
        
        ~stack_node() {};
        
        long long get_value() {
            return value;
        }
        
        long long get_min() {
            return min;
        }
        
        void set_min(long long m) {
            min = m;
        }
        
        stack_node * get_next() {
            return next;
        }
};


class stack
{
    private:
        stack_node *first;
        
    public:
        stack() {
            first = 0;
        }
        
        ~stack() {
            while (first != 0) {
                stack_node *temp = first -> get_next();
                delete first;
                first = temp;
            }
        }
        
        void push(long long value) {
            stack_node *new_node;
            
            if (first == 0)
                new_node = new stack_node(first, value, value);
            else {
                int current_min = first -> get_min();
                if (current_min < value)
                    new_node = new stack_node(first, value, current_min);
                else
                    new_node = new stack_node(first, value, value);
            }
            
            first = new_node;
        }
        
        long long pop() {
            long long value = first -> get_value();
            stack_node *temp = first;
            first = first -> get_next();
            delete temp;
            
            return value;
        }
        
        stack_node *get_first() {
            return first;
        }
        
        long long stack_min() {
            return first -> get_min();
        }
};


int main()
{
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");
    
    int m;
    fin >> m;
    
    stack s1, s2;
    char input;
    long long value;
    
    for (int i = 0; i < m; ++i) {
        fin >> input;
        
        if (input == '+') {
            fin >> value;
            s1.push(value);
        } else if (input == '-') {
            if (s2.get_first() == 0) {
                while (s1.get_first() != 0) {
                    s2.push(s1.pop());
                }
            }
            s2.pop();
        } else {
            long long current_min;
            
            if (s1.get_first() == 0 || s2.get_first() == 0)
                current_min = s1.get_first() == 0 ? s2.stack_min() : s1.stack_min();
            else
                current_min = s1.stack_min() < s2.stack_min() ? s1.stack_min() : s2.stack_min();
            
            fout << current_min << '\n';
        }
    }
    
    return 0;
}
