# performance benchmarks

## Description

monitoring 에서 사용하는 기능의 테스트를 위한 공통의 성능 벤치 마크

## build


```bash
$ mkdir -p build
$ cmake ../
$ make run 

[ 20%] Building CXX object src/CMakeFiles/perf-benchmarks.dir/localtime_benchmark.cpp.o
[ 40%] Building CXX object src/CMakeFiles/perf-benchmarks.dir/cctz_benchmark.cpp.o
[ 60%] Building CXX object src/CMakeFiles/perf-benchmarks.dir/localtime_safe_benchmark.cpp.o
[ 80%] Building CXX object src/CMakeFiles/perf-benchmarks.dir/main.cpp.o
[100%] Linking CXX executable perf-benchmarks
[100%] Built target perf-benchmarks
2019-11-01 09:13:58
Running src/perf-benchmarks
Run on (2 X 2400 MHz CPU s)
CPU Caches:
  L1 Data 32K (x2)
  L1 Instruction 32K (x2)
  L2 Unified 4096K (x2)
-----------------------------------------------------------------------------------------------
Benchmark                                                        Time           CPU Iterations
-----------------------------------------------------------------------------------------------
BenchmarkLocaltime/iterations:10000/threads:500               1624 ns       2101 ns    5000000
BenchmarkLocaltime_r/iterations:10000/threads:500             1094 ns       2652 ns    5000000
BenchmarkLocaltime_rSetTZ/iterations:10000/threads:500        1106 ns       2708 ns    5000000
BenchmarkCctzLocalTimeZone/iterations:10000/threads:500        899 ns       2529 ns    5000000
BenchmarkCctzLoadTimeZone/iterations:10000/threads:500         911 ns       2343 ns    5000000
BenchmarkLocaltimeSafe/iterations:10000/threads:1000             0 ns        106 ns   10000000

```
