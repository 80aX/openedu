// Почти интерактивная хеш-таблица

// В данной задаче у Вас не будет проблем ни с вводом, ни с выводом. Просто 
// реализуйте быструю хеш-таблицу.

// В этой хеш-таблице будут храниться целые числа из диапазона [0; 10^15-1]. Требуется 
// поддерживать добавление числа x и проверку того, есть ли в таблице число x. 


#include <fstream>
#include <set>


class interactive_hash_table
{
    public:
        interactive_hash_table() {}
        
        ~interactive_hash_table() {}
        
        void processing() {
            std::ifstream fin("input.txt");
            std::ofstream fout("output.txt");
            
            long long n, x, a, b;
            fin >> n >> x >> a >> b;
            
            long long ac, bc, ad, bd;
            fin >> ac >> bc >> ad >> bd;
            
            for (int i = 0; i < n; ++i) {
                if (user_hash_table.find(x) != user_hash_table.end()) {
                    a = (a + ac) % 1000;
                    b = (b + bc) % 1000000000000000;
                } else {
                    user_hash_table.insert(x);
                    a = (a + ad) % 1000;
                    b = (b + bd) % 1000000000000000;
                }
                x = (x * a + b) % 1000000000000000;
            }
            
            fout << x << " " << a << " " << b << "\n";
        }
        
    private:
        std::set<long long> user_hash_table;
        std::set<long long>::iterator it;
};


int main()
{
    interactive_hash_table program;
    program.processing();
    
    return 0;
}
