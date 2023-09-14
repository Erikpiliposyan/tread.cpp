#include <iostream>
#include <thread>
#include <vector>

int factorial(int n) {
    if (n <= 1) return 1;
    int result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

int fibonacci(int n) {
    if (n <= 1) return n;
    int fib1 = 0, fib2 = 1, fib = 1;
    for (int i = 2; i <= n; ++i) {
        fib = fib1 + fib2;
        fib1 = fib2;
        fib2 = fib;
    }
    return fib;
}

void calculateAndDisplay(int n) {
    int fact = factorial(n);
    int fib = fibonacci(n);

    std::cout << "Number: " << n << " Factorial: " << fact << " Fibonacci: " << fib << std::endl;
}

int main() {
    int n;
    std::cout << "Enter the number of values to calculate (n): ";
    std::cin >> n;

    std::vector<std::thread> threads;

    for (int i = 1; i <= n; ++i) {
        threads.emplace_back(calculateAndDisplay, i);
    }
    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}
