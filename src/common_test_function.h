#include <future>
#include <thread>

//  multi thread 기반에서 LogFile 함수내의 localtime 호출시
//  외부의 localtime 호출로 인한 throughput 저하현상을 확인하기 위한 람다함수
auto localtime_thread_lambda = [](std::future<void> future_obj) -> void {
  while (future_obj.wait_for(std::chrono::milliseconds(100)) == std::future_status::timeout) {
    time_t timeval;
    localtime(&timeval);
  }
};

