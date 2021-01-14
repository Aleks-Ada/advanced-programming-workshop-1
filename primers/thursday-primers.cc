#include "thursday-primers.h"

#include <thread>
#include <chrono>

#include "io-lib.h"

void block_execution(const int seconds = 10) {
  std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

void run_primer_10() {
  block_execution();
}

void run_primer_11() {
  const std::string main_thread_id = std::to_string(std::this_thread::get_id());

  print(concat(iolib::with_space,
    "Main thread:",
    main_thread_id,
    "started"));
    
  print(concat(iolib::with_space,
    "Main thread:",
    main_thread_id,
    "ended"));
}

void run_primer_12() {

}