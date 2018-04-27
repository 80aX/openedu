// Скобочная последовательность

// Последовательность , состоящую из символов из множества «(», «)», «[» и «]», 
// назовем правильной скобочной последовательностью, если выполняется одно из 
// следующих утверждений:

// A — пустая последовательность;
// первый символ последовательности A — это «(», и в этой последовательности 
// существует такой символ «)», что последовательность можно представить как A=(B)C, 
// где B и C — правильные скобочные последовательности;
// первый символ последовательности A — это «[», и в этой последовательности 
// существует такой символ «]», что последовательность можно представить как A=[B]C, 
// где B и C — правильные скобочные последовательности.

// Формат входного файла
// Первая строка входного файла содержит число N (1<=N<=500) - число скобочных 
// последовательностей, которые необходимо проверить. Каждая из следующих N 
// строк содержит скобочную последовательность длиной от 1 до 10^4 включительно. 
// В каждой из последовательностей присутствуют только скобки указанных выше видов.

// Формат выходного файла
// Для каждой строки входного файла выведите в выходной файл «YES», если 
// соответствующая последовательность является правильной скобочной 
// последовательностью, или «NO», если не является.


#include <fstream>
#include <string>


class stack_node
{
    private:
        char sym;
        stack_node *next;
    
    public:
        stack_node() {
            sym = '\0';
            next = 0;
        }
        
        ~stack_node() {}
        
        stack_node(char s, stack_node *n) {
            sym = s;
            next = n;
        }
        
        char get_value() {
            return sym;
        }
        
        stack_node * get_next() {
            return next;
        }
};


class stack
{
    private:
        bool flag;
        stack_node *first;
    
    public:
        stack() {}
        
        ~stack() {
            stack_node *temp;
            
            while(first != 0) {
                temp = first -> get_next();
                delete first;
                first = temp;
            }
        }
        
        void push(char sym) {
            stack_node *new_node;
            new_node = new stack_node(sym, first);
            first = new_node;
        }
        
        void pop() {
            stack_node *temp;
            temp = first;
            first = temp -> get_next();
            delete temp;
        }
        
        void processing() {
            std::ifstream fin("input.txt");
            std::ofstream fout("output.txt");
            
            int n, symbol, i, j;
            std::string str;
            
            fin >> n;
            std::getline(fin, str);
            for (i = 0; i < n; ++i) {
                
                flag = true;
                this -> ~stack();
                
                std::getline(fin, str);
                for (j = 0; j < str.length(); ++j) {
                    
                    if (str[j] == '(' || str[j] == '[') {
                        push(str[j]);
                    } else if (first != 0 && (int)(first -> get_value() + str[j]) % 132 > 1) {
                        pop();
                    } else {
                        flag = false;
                        break;
                    }
                }
                
                if (flag && first == 0)
                    fout << "YES" << '\n';
                else
                    fout << "NO" << '\n';
            }
        }
};


int main()
{
    stack test;
    test.processing();
    
    return 0;
}
