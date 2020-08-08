CMAKE_MINIMUM_REQUIRED(VERSION 3.12.1 FATAL_ERROR)



set(SRCS
    Channel.cc
    Epoll.cc
    EventLoop.cc
    EventLoopThread.cc
    EventLoopThreadPool.cc
    HttpData.cc
    Main.cc
    Server.cc
    #ThreadPool.cpp
    Timer.cc
    Util.cc
)
include_directories(${PROJECT_SOURCE_DIR}/base)


add_executable(h_webserver ${SRCS})
target_link_libraries(h_webserver libserver_base)


add_subdirectory(base)
add_subdirectory(tests)
