// Стэк

// Реализуйте работу стека. Для каждой операции изъятия элемента выведите ее 
// результат.

// На вход программе подаются строки, содержащие команды. Каждая строка содержит 
// одну команду. Команда — это либо "+ N", либо "−". Команда "+ N" означает 
// добавление в стек числа N, по модулю не превышающего 10^9. Команда "−" означает 
// изъятие элемента из стека. Гарантируется, что не происходит извлечения из 
// пустого стека. Гарантируется, что размер стека в процессе выполнения команд 
// не превысит 10^6 элементов.

// Формат входного файла
// В первой строке входного файла содержится M (1<=M<=10^6) — число команд. Каждая 
// последующая строка исходного файла содержит ровно одну команду.

// Формат выходного файла
// Выведите числа, которые удаляются из стека с помощью команды "−", по одному в 
// каждой строке. Числа нужно выводить в том порядке, в котором они были извлечены 
// из стека. Гарантируется, что изъятий из пустого стека не производится.


#include <fstream>


class stack_node
{
    private:
        int value;
        stack_node *next;
    
    public:
        stack_node() {
            value = 0;
            next = 0;
        }
        
        ~stack_node() {}
        
        stack_node(int v, stack_node *n) {
            value = v;
            next = n;
        }
        
        int get_value() {
            return value;
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
            stack_node *temp;
            
            while(first) {
                temp = first -> get_next();
                delete first;
                first = temp;
            }
        }
        
        void push(int value) {
            stack_node *new_node = new stack_node(value, first);
            first = new_node;
        }
        
        int pop() {
            int value = first -> get_value();
            stack_node *temp = first;
            first = first -> get_next();
            delete temp;
            
            return value;
        }
};


int main()
{
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");
    
    int n, value;
    char operation;
    
    fin >> n;
    stack test;
    
    for (int i = 0; i < n; ++i) {
        fin >> operation;
        
        if (operation == '+') {
            fin >> value;
            test.push(value);
        } else {
            fout << test.pop() << '\n';
        }
    }
    
    return 0;
}
