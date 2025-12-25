#include <iostream>
#include <Array.hpp>

#define MAX_VAL 750
int main(int, char**)
{
    Array<int> numbers(MAX_VAL);
    std::cout << "Size of the numbers array is: " << numbers.size() << "\n";
    int* mirror = new int[MAX_VAL];
    srand(time(NULL));
    for (int i = 0; i < MAX_VAL; i++)
    {
        const int value = rand();
        numbers[i] = value;
        mirror[i] = value;
    }
    try
    {
        std::cout << "Value of numbers[-10]:\t" << numbers[-10] << "\n";
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    std::cout << "Value of numbers[10]:\t" << numbers[10] << "\n";
    std::cout << "Value of mirror[10]:\t" << mirror[10] << "\n";
    //SCOPE
    {
        Array<int> tmp = numbers;
        std::cout << "Size of the tmp array is: " << tmp.size()
                  << ". Value of tmp[10]: " << tmp[10] << "\n";
        Array<int> test(tmp);
        std::cout << "Size of the test array is: " << test.size()
                  << ". Value of test[10]: " << test[10] << "\n";
    }
    for (int i = 0; i < MAX_VAL; i++)
    {
        if (mirror[i] != numbers[i])
        {
            std::cerr << "didn't save the same value!!" << std::endl;
            return 1;
        }
    }
    try
    {
        numbers[-2] = 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    try
    {
        numbers[MAX_VAL] = 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    for (int i = 0; i < MAX_VAL; i++)
    {
        numbers[i] = rand();
    }
    delete [] mirror;//
    return 0;
}