#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

std::mutex mtx; 

void random(std::vector<unsigned int>& R) {
	srand(time(0));
	for (int i = 0; i < R.size(); i++)
	{
		R[i] = rand() % 15;
	}
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

int main() {
    const int num_threads = 20;
    std::vector<unsigned int> r(num_threads);
    random(r);

    std::vector<std::thread> threads;

    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back([i, &r]() {
            int res = fibo(r[i]);
            mtx.lock();
            std::cout << "Thread " << i << ": Fibonacci(" << r[i] << ") = " << res << std::endl;
            mtx.unlock();
        });
    }

    for (auto& thread : threads) {
        thread.join();
    }
    return 0;
}
