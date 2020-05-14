#include <iostream>
#include <exception>
#include <math.h>
#include <chrono>
#include <functional>

double fib(unsigned int n)
{
    return n > 2 ? fib(n - 1) + fib(n - 2) : n;
}

double fac(unsigned int n)
{
    int result = 1;
    for (unsigned int i = n; i > 0; i--)
    {
        result *= i;
    }
    return result;
}

double pi(unsigned int precision) {
    double pi = 3;

    auto getDenominator = [](int step)
    {
        //step should start with 1
        const int base = step * 2;
        return base * (base + 1) * (base + 2);
    };

    for (unsigned int i = 1; i <= precision; i++) {
        if (i % 2 != 0) { //if odd
            pi += 4.0 / getDenominator(i);
        }
        else { //even
            pi -= 4.0 / getDenominator(i);
        }
    }

    return pi;
}

bool strings_are_equal(const char* a, const char* b) {
    std::string str_a(a);
    std::string str_b(b);
    return str_a.compare(b) == 0;
}

int main(int argc, char* argv[])
{
    using namespace std::chrono;

    std::function<double(unsigned int)> mathfunc;

    if (argc != 3)
    {
        std::cout << "Usage: MathFun functionName number";
        return 1;
    }
    try {

        if (strings_are_equal(argv[1], "fib")) {
            mathfunc = fib;
        }
        else if (strings_are_equal(argv[1], "fac"))
        {
            mathfunc = fac;
        }
        else if (strings_are_equal(argv[1], "pi"))
        {
            mathfunc = pi;
        }
        else {
            std::cout << "Please select one of the following functions: fib fac pi";
        }

        double userInput = atof(argv[2]);
        if (userInput != floor(userInput) || userInput < 0)
        {
            std::cout << "Use a positive whole number";
            return 1;
        }
        milliseconds startTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
        std::cout << mathfunc(static_cast<unsigned int>(userInput)) << std::endl;
        milliseconds endTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
        std::cout << "Duration: " << (endTime - startTime).count() << "ms";
    }
    catch (std::exception& e)
    {
        std::cout << e.what();
        return 1;
    }
}