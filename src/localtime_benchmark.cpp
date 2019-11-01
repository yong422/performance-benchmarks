#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <ctime>
#include <mutex>
#include <benchmark/benchmark.h>

#include "common_test_function.h"

static void BenchmarkLocaltime(benchmark::State& state) {
  std::promise<void> exit_signal;
  std::future<void>  future_obj = exit_signal.get_future();
  std::thread th(localtime_thread_lambda, std::move(future_obj));

  if (state.thread_index == 0) {
    // Setup code here.
  }
  for(auto _ : state) {
    char buffer[256] = {0, };
    time_t time_value = static_cast<time_t>(std::time(nullptr));
    std::tm tmvariable;
    memcpy(&tmvariable, localtime(&time_value), sizeof(tmvariable));;
  }
  if (state.thread_index == 0) {
    // Teardown code here.
  }
  exit_signal.set_value();
  th.join();

}

static void BenchmarkLocaltime_r(benchmark::State& state) {
  std::promise<void> exit_signal;
  std::future<void>  future_obj = exit_signal.get_future();
  std::thread th(localtime_thread_lambda, std::move(future_obj));

  for (auto _ : state) {
    char buffer[256] = {0, };
    time_t time_value = static_cast<time_t>(std::time(nullptr));
    std::tm tmvariable;
    localtime_r(&time_value, &tmvariable);
  }
  exit_signal.set_value();
  th.join();
}


std::mutex set_tz_mutex;
static void BenchmarkLocaltime_rSetTZ(benchmark::State& state) {
  std::promise<void> exit_signal;
  std::future<void>  future_obj = exit_signal.get_future();
  std::thread th(localtime_thread_lambda, std::move(future_obj));

  set_tz_mutex.lock();
  {
    std::string tz = "TZ=Asia/Seoul";
    putenv(const_cast<char*>(tz.c_str()));
  }
  set_tz_mutex.unlock();

  for (auto _ : state) {
    char buffer[256] = {0, };
    time_t time_value = static_cast<time_t>(std::time(nullptr));
    std::tm tmvariable;
    localtime_r(&time_value, &tmvariable);
  }
  exit_signal.set_value();
  th.join();
}

// 	thread test
//	반복횟수, thread 생성 개수를 설정.
BENCHMARK(BenchmarkLocaltime)->Iterations(10000)->Threads(500);
BENCHMARK(BenchmarkLocaltime_r)->Iterations(10000)->Threads(500);
BENCHMARK(BenchmarkLocaltime_rSetTZ)->Iterations(10000)->Threads(500);

