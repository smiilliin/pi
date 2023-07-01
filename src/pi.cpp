#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <gmpxx.h>
#include <unistd.h>

using namespace std;

const size_t n = 1200; //The number of digits in the integer and fractional parts
const int threadCount = 4; //The number of threads
const size_t size = 40000000; //The number of operations to be performed by one thread

mpz_class base;
mutex resultLock;
mpz_class result;

void calculate(size_t start, size_t end) {
  mpz_class result;
  
  for (size_t a = 0; a < end; a++) {
    size_t i = start + a;

    if (i % 2 == 0) {
      result += base / (2 * i + 1);
    }
    else {
      result -= base / (2 * i + 1);
    }
  }
  resultLock.lock();
  ::result += result;
  resultLock.unlock();
}

int main() {
  mpz_ui_pow_ui(base.get_mpz_t(), 10, n);
  base *= 4;

  vector<thread> threads;
  for (size_t i = 0; i < threadCount; i++) {
    threads.emplace_back(calculate, i * size, (i + 1) * size - 1);
  }
  for (auto& t : threads) {
    t.join();
  }

  auto resultString = result.get_str();

  for (size_t i = 0; i < resultString.length(); i++) {
    cout << resultString[i] << flush;
    if (i == 0) cout << "." << flush;
    this_thread::sleep_for(chrono::milliseconds(50));
  }
  cout << endl;

  return 0;
}