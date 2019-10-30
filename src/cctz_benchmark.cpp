
#include <cctz/time_zone.h>
#include <cctz/civil_time.h>
#include <benchmark/benchmark.h>

#include "common_test_function.h"

static void BenchmarkCctzLocalTimeZone(benchmark::State& state)
{
  std::promise<void> exit_signal;
  std::future<void>  future_obj = exit_signal.get_future();
  std::thread th(localtime_thread_lambda, std::move(future_obj));
  for (auto _ : state) {
    cctz::time_zone local_timezone = cctz::local_time_zone();
    const auto now = std::chrono::system_clock::now();
    const cctz::civil_second cs = cctz::convert(now, local_timezone);
    std::string result_datetime = cctz::format("Now : %Y-%m-%d %H:%M:%S %z\n", now, local_timezone);  
  }
  exit_signal.set_value();
  th.join();
}

static void BenchmarkCctzLoadTimeZone(benchmark::State& state)
{
  std::promise<void> exit_signal;
  std::future<void>  future_obj = exit_signal.get_future();
  std::thread th(localtime_thread_lambda, std::move(future_obj));
  for (auto _ : state) {
    cctz::time_zone local_timezone;
	cctz::load_time_zone("Asia/Seoul", &local_timezone);
    const auto now = std::chrono::system_clock::now();
    const cctz::civil_second cs = cctz::convert(now, local_timezone);
    std::string result_datetime = cctz::format("Now : %Y-%m-%d %H:%M:%S %z\n", now, local_timezone);  
  }
  exit_signal.set_value();
  th.join();
}

BENCHMARK(BenchmarkCctzLocalTimeZone)->Iterations(10000)->Threads(500);
BENCHMARK(BenchmarkCctzLoadTimeZone)->Iterations(10000)->Threads(500);
