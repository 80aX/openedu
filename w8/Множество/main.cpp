// Множество

// Реализуйте множество с операциями «добавление ключа», «удаление ключа», 
// «проверка существования ключа».


#include <set>
#include <fstream>


class custom_set
{
    public:
        custom_set() {}
        
        ~custom_set() {}
        
        long long hash(long long x) {
            long long p = 1000000000000000000; // (10^18)
            
            return x % p;
        }
        
        void insert(long long x) {
            long long key = hash(x);
            
            if (user_set.find(key) == user_set.end())
                user_set.insert(key);
        }
        
        
        char search(long long x) {
            long long key = hash(x);
            
            if (user_set.find(key) != user_set.end())
                return 'Y';
            else
                return 'N';
        }
        
        void remove(long long x) {
            long long key = hash(x);
            
            if (user_set.find(key) != user_set.end())
                user_set.erase(key);
        }
        
        void processing() {
            std::ifstream fin("input.txt");
            std::ofstream fout("output.txt");
            
            int n;
            fin >> n;
            
            for (int i = 0; i < n; ++i) {
                char operation;
                long long value;
                fin >> operation >> value;
                
                if (operation == 'A')
                    insert(value);
                else if (operation == 'D')
                    remove(value);
                else
                    fout << search(value) << "\n";
            }
        }
        
    private:
        std::set<long long> user_set;
};



int main()
{
    custom_set test;
    test.processing();
    
    return 0;
}
