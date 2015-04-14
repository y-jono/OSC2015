#include<thread>
#include<chrono>
#include<mutex>

int main(void) {
  std::mutex mtx_a;
  std::mutex mtx_b;

  std::thread th_a([&mtx_a,&mtx_b]{
    std::lock_guard<std::mutex> lock_a(mtx_a);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::lock_guard<std::mutex> lock_b(mtx_b);
  });
  std::thread th_b([&mtx_a,&mtx_b]{
    std::lock_guard<std::mutex> lock_b(mtx_b);
    std::lock_guard<std::mutex> lock_a(mtx_a);
  });

  th_a.join();
  th_b.join();
  return 0;
}


