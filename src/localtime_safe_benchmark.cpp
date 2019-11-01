#include <time.h>
#include <ctime>
#include <string.h>
#include <benchmark/benchmark.h>

#include "common_test_function.h"

void localtime_safe(time_t time, long timezone, struct tm *tm_time)
{
    const char Days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    uint32_t n32_Pass4year;
    uint32_t n32_hpery;

    time=time + (timezone * 60 * 60);

    if(time < 0)
    {
        time = 0;
    }
    tm_time->tm_sec=(int)(time % 60);
    time /= 60;
    tm_time->tm_min=(int)(time % 60);
    time /= 60;
    n32_Pass4year=((unsigned int)time / (1461L * 24L));
    tm_time->tm_year=(n32_Pass4year << 2)+70;
    time %= 1461L * 24L;
    for (;;)
    {
        n32_hpery = 365 * 24;
        if ((tm_time->tm_year & 3) == 0)
        {
            n32_hpery += 24;
        }
        if (time < n32_hpery)
        {
            break;
        }
        tm_time->tm_year++;
        time -= n32_hpery;
    }
    tm_time->tm_hour=(int)(time % 24);
    time /= 24;
    time++;
    if ((tm_time->tm_year & 3) == 0)
    {
        if (time > 60)
        {
            time--;
        }
        else
        {
            if (time == 60)
            {
                tm_time->tm_mon = 1;
                tm_time->tm_mday = 29;
                return ;
            }
        }
    }
    for (tm_time->tm_mon = 0; Days[tm_time->tm_mon] < time;tm_time->tm_mon++)
    {
        time -= Days[tm_time->tm_mon];
    }

    tm_time->tm_mday = (int)(time);
    return;
}

static void BenchmarkLocaltimeSafe(benchmark::State& state) {
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
    localtime_safe(time_value, 9, &tmvariable);
    //memcpy(&tmvariable, localtime(&time_value), sizeof(tmvariable));;
  }
  if (state.thread_index == 0) {
    // Teardown code here.
  }
  exit_signal.set_value();
  th.join();
}


BENCHMARK(BenchmarkLocaltimeSafe)->Iterations(10000)->Threads(1000);


