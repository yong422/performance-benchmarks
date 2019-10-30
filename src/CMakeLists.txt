

INCLUDE_DIRECTORIES ( ./ )
SET ( SRCS
      localtime_benchmark.cpp
      cctz_benchmark.cpp
      localtime_safe_benchmark.cpp
      main.cpp
)

ADD_EXECUTABLE ( ${BIN_NAME} ${SRCS} )

TARGET_LINK_LIBRARIES ( ${BIN_NAME} 
                        CONAN_PKG::cctz
                        CONAN_PKG::google-benchmark
                        ${CMAKE_THREAD_LIBS_INIT} )
