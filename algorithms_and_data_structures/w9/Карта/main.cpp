// Карта

// Выведите одно число x — число способов вычеркнуть из текста все буквы 
// кроме трех так, чтобы оставшееся слово одинаково читалось слева направо 
// и справа налево.


#include <fstream>
#include <string>


long long map_decoding(std::string &str)
{
    long long result = 0;
    int str_length = str.length();
    int i, j, space_counter;
    
    for (i = 0; i < str_length - 1; ++i)
    {
        space_counter = 0;
        for (j = i + 1; j < str_length; ++j)
        {
            if (str[i] != ' ' && str[i] == str[j])
                result += j - i - 1 - space_counter;
            else if (str[j] == ' ')
                space_counter++;
        }
    }
    
    return result;
}


int main()
{
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    std::string x;
    std::getline(fin, x);

    fout << map_decoding(x) << "\n";

    return 0;
}
