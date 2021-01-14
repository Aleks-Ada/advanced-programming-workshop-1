#include "thursday-primers.h"

#include <chrono>
#include <thread>
#include <string>
#include <sstream>
#include <iostream>

#include "io-lib.h"

void block_execution(const int seconds = 10) {
  std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

void run_primer_10() {
  block_execution();
}

std::string thread_id_to_string(const std::thread::id id) {
  std::ostringstream ss;
  ss << id;
  return ss.str();
}

std::string current_thread_id() {
  return thread_id_to_string(std::this_thread::get_id());
}

void thread_function(const int id, const int sleep) {
  print(concat(Separator::EMPTY,
    "Thread ",
    std::to_string(id),
    ": ",
    current_thread_id(),
    " started"));
  block_execution(sleep);
  print(concat(Separator::EMPTY,
    "Thread ",
    std::to_string(id),
    ": ",
    current_thread_id(),
    " ended"));
}

void run_primer_11() {
  print(concat(iolib::with_space,
    "Main thread:",
    current_thread_id(),
    "started"));
  std::thread thread1(&thread_function, 1, 5);
  std::thread thread2(&thread_function, 2, 10);
  thread1.join();
  thread2.join();
  print(concat(iolib::with_space,
    "Main thread:",
    current_thread_id(),
    "ended"));
  // Explanation:
  // 0. The main thread prints it's started message
  // 1. Thread 1 is created, which causes the thread_function
  //    to immediately begin execution on a separate thread.
  // 2. This causes thread 1 to print its ID almost immediately.
  // 3. Thread 2 is created, which causes a new instance of the
  //    thread_function to immediately begin execution on a
  //    separate thread.
  // 4. This causes thread 2 to print its ID almost immediately.
  // 5. There is no guarantee which order the threads print their
  //    IDs in, or whether thread 2 starts before thread 1 prints
  //    it's ID, since there are 3 threads in play here. This all
  //    depends on the C++ standard library implementation of
  //    std::thread and the operating system scheduler.
  // 6. Thread 1 is joined, which means the execution block is
  //    awaited (for the remainder of the 5 seconds).
  // 7. Thread 1 prints it's exit message.
  // 8. Thread 2 is joined, which means the execution block is
  //    awaited (for the remainder of the 10 seconds).
  // 9. Thread 1 prints it's exit message.
  // 10. The main thread prints it's exit message.
}

std::thread thread1;
std::thread thread2;

void run_primer_12() {
  print(concat(iolib::with_space,
    "Main thread:",
    current_thread_id(),
    "started"));
  thread1 = std::thread(&thread_function, 1, 5);
  thread2 = std::thread(&thread_function, 2, 10);
  thread1.detach();
  thread2.detach();
  print(concat(iolib::with_space,
    "Main thread:",
    current_thread_id(),
    "ended"));
  // Explanation:
  // 0. The main thread prints it's started message
  // 1. Thread 1 is created, which causes the thread_function
  //    to immediately begin execution on a separate thread.
  // 2. This causes thread 1 to print its ID almost immediately.
  // 3. Thread 2 is created, which causes a new instance of the
  //    thread_function to immediately begin execution on a
  //    separate thread.
  // 4. This causes thread 2 to print its ID almost immediately.
  // 5. There is no guarantee which order the threads print their
  //    IDs in, or whether thread 2 starts before thread 1 prints
  //    it's ID, since there are 3 threads in play here. This all
  //    depends on the C++ standard library implementation of
  //    std::thread and the operating system scheduler.
  // 6. Thread 1 is detached, which means that it's execution is
  //    now independent of the main thread's execution.
  // 7. Thread 2 is detached, which means that it's execution is
  //    now independent of the main thread's execution.
  // 8. The main thread prints it's exit message.
  // 9. Thread 1 and 2 may or may not have printed their exit
  //    messages - this entirely depends on whether they had
  //    time to do so whilst the main thread was running.
  // 10. The main thread of the program exits, which causes
  //     the operating system to release all resources used
  //     by the program, including any threads, which means
  //     threads 1 and 2 are stopped regardless of whether
  //     they printed their exit messages or not.
}