// Наивный поиск подстроки в строке

// В первой строке выведите число вхождений строки p в строку t. 
// Во второй строке выведите в возрастающем порядке номера символов 
// строки t, с которых начинаются вхождения p. Символы нумеруются с единицы.


#include <fstream>
#include <string>


void tfind(std::string &p, std::string &t)
{
    std::ofstream fout("output.txt");
    
    int t_length = t.length(), p_length = p.length();
    int i, j, inst = 0;
    int pos[10000];
    bool equiv = true;
    
    for (i = 0; i <= t_length - p_length; ++i) {
        for (j = 0; j < p_length; ++j) {
            if (t[i + j] != p[j]) {
                equiv = false;
                break;
            }
        }
        if (equiv == true) {
            pos[inst] = i + 1;
            inst++;
        } else {
            equiv = true;
        }
    }
    
    fout << inst << "\n";
    
    for (i = 0; i < inst; ++i)
        fout << pos[i] << " ";
    fout << "\n";
}


int main()
{
    std::ifstream fin("input.txt");
    
    std::string p, t;
    fin >> p;
    fin >> t;
    
    tfind(p, t);
    
    return 0;
}
