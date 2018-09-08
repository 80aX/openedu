// Прошитый ассоциативный массив

// Реализуйте прошитый ассоциативный массив.
// Выведите последовательно результат выполнения всех операций get, prev, next. 
// Следуйте формату выходного файла из примера.


#include <fstream>
#include <cstring>


class array_node
{
    public:
        array_node() {
            key = 0;
            next = 0;
            prev = 0;
        }
        
        ~array_node() {}
        
        array_node(long long k, char *v, array_node *n, array_node *p) {
            key = k;
            strcpy(value, v);
            next = n;
            prev = p;
        }
        
        long long get_key() {
            return key;
        }
        
        char *get_value() {
            return value;
        }
        
        array_node *get_next() {
            return next;
        }
        
        array_node *get_prev() {
            return prev;
        }
        
        void set_key(long long k) {
            key = k;
        }
        
        void set_value(char *v) {
            strcpy(value, v);
        }
        
        void set_next(array_node *n) {
            next = n;
        }
        
        void set_prev(array_node *p) {
            prev = p;
        }
        
    private:
        long long key;
        char value[20];
        array_node *next;
        array_node *prev;
};


class associative_array
{
    public:
        associative_array() {
            first = 0;
            last = 0;
            temp = 0;
            pow_calc();

            none[0] = '<';
            none[1] = 'n';
            none[2] = 'o';
            none[3] = 'n';
            none[4] = 'e';
            none[5] = '>';
        }
        
        ~associative_array() {
            while (first != 0) {
                temp = first;
                first = first -> get_next();
                delete temp;
            }
        }
        
        void pow_calc() {
            int t = 127;
            
            pow_array[0] = 1;
            for (int i = 1; i < 21; ++i)
                pow_array[i] = pow_array[i - 1] * t;
            
            
            // for (int i = 0; i < 21; ++i)
                // std::cout << p_pow[i] << " ";
            // std::cout << "\n";
        }
        
        long long hash(char *x) {
            long long h = 0;
            
            for (int i = 0; x[i] != '\0'; ++i)
                h += x[i] * pow_array[i];
            
            return h;
        }
        
        char *get(char *x) {
            
            // std::cout << "get\n";
            
            long long key = hash(x);
            
            temp = first;
            while (temp != 0 && temp -> get_key() != key)
                temp = temp -> get_next();
            
            if (temp != 0)
                return temp -> get_value();
            else
                return none;
        }
        
        char *prev(char *x) {
            
            // std::cout << "prev\n";
            
            long long key = hash(x);
            
            temp = first;
            while (temp != 0 && temp -> get_key() != key)
                temp = temp -> get_next();
            
            if (temp != 0) {
                array_node *prev = temp -> get_prev();
            
                if (prev != 0)
                    return prev -> get_value();
            }
            return none;
        }
        
        char *next(char *x) {
            
            // std::cout << "next\n";
            
            long long key = hash(x);
            
            temp = first;
            while (temp != 0 && temp -> get_key() != key)
                temp = temp -> get_next();
            
            if (temp != 0) {
                array_node *next = temp -> get_next();
            
                if (next != 0)
                    return next -> get_value();
            }
            return none;
        }
        
        void put(char *x, char *y) {
            
            // std::cout << "put\n";
            
            long long key = hash(x);
            
            if (first == 0) {
                array_node *new_node = new array_node(key, y, 0, 0);
                first = new_node;
                last = new_node;
                return;
            }
            
            temp = first;
            while (temp != 0 && temp -> get_key() != key)
                temp = temp -> get_next();
            
            if (temp != 0) {
                temp -> set_value(y);
            } else {
                array_node *new_node = new array_node(key, y, 0, last);
                last -> set_next(new_node);
                last = new_node;
            }
        }
        
        void remove(char *x) {
            
            // std::cout << "remove\n";
            
            long long key = hash(x);
            
            temp = first;
            while (temp != 0 && temp -> get_key() != key)
                temp = temp -> get_next();
            
            if (temp != 0) {
                array_node *next = temp -> get_next();
                array_node *prev = temp -> get_prev();
                
                if (next == 0 && prev == 0) {
                    first = 0;
                    last = 0;
                } else if (next == 0) {
                    prev -> set_next(0);
                    last = prev;
                } else if (prev == 0) {
                    next -> set_prev(0);
                    first = next;
                } else {
                    next -> set_prev(prev);
                    prev -> set_next(next);
                }
                delete temp;
            }
        }
        
        void processing() {
            std::ifstream fin("input.txt");
            std::ofstream fout("output.txt");
            
            int n;
            fin >> n;
            
            for (int i = 0; i < n; ++i) {
                char procedure[6], x[20], y[20];
                fin >> procedure >> x;
                
                if (!std::strcmp(procedure, "get")) {
                    fout << get(x) << "\n";
                } else if (!std::strcmp(procedure, "prev")) {
                    fout << prev(x) << "\n";
                } else if (!std::strcmp(procedure, "next")) {
                    fout << next(x) << "\n";
                } else if (!std::strcmp(procedure, "delete")) {
                    remove(x);
                } else {
                    fin >> y;
                    put(x, y);
                }
                
                // temp = first;
                // while (temp != 0) {
                    // std::cout << temp -> get_key() << " " << temp -> get_value() << " ";
                    // temp = temp -> get_next();
                // }
                // std::cout << "\n";
            }
        }
        
    private:
        array_node *first;
        array_node *last;
        array_node *temp;
        char none[6];
        unsigned long long pow_array[21];
};


int main()
{
    associative_array program;
    program.processing();
    
    return 0;
}
