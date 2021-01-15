#include "io-lib.h"
#include "monday-primers.h"
#include "tuesday-primers.h"
#include "wednesday-primers.h"
#include "thursday-primers.h"
#include "friday-primers.h"

#define BEGIN_PRIMERS_SWITCH(choice) switch (choice) {
#define MAP_PRIMER(index) case index: run_primer_##index(); break;
#define MAP_EXIT(index, message) case index: print(message); return false;
#define MAP_DEFAULT(message) default: \
  print(message); \
  break;
#define END_PRIMERS_SWITCH }

std::string read_primer_choice() {
  return read_regex_matching_string_with_prompt("Please enter option to run primer (e.g. 1 for Primer 01): ",
                                                std::regex("^\\d+$"));
}

bool run_primers() {
  print_empty_line();
  print("Advanced Programming - Primers Portfolio Menu:");
  print("Monday (Basic Programming Primers)");
  print("\t1. Primer 01");
  print("\t2. Primer 02");
  print("\t3. Primer 03");
  print_empty_line();
  print("Tuesday (Data Types, Manipulation & Structures)");
  print("\t4. Primer 04");
  print("\t5. Primer 05");
  print("\t6. Primer 06");
  print_empty_line();
  print("Wednesday (IO Streams, File & Error Handling)");
  print("\t7. Primer 07");
  print("\t8. Primer 08");
  print("\t9. Primer 09");
  print_empty_line();
  print("Thursday (Multi-Threading & Concurrency)");
  print("\t10. Primer 10");
  print("\t11. Primer 11");
  print("\t12. Primer 12");
  print_empty_line();
  print("Friday (Classes and Objects)");
  print("\t13. Primer 13");
  print("\t14. Primer 14");
  print("\t15. Primer 15");
  print_empty_line();
  print("\t0. Quit");
  print_empty_line();

  const std::string choice_string = read_primer_choice();
  const int choice = std::stoi(choice_string);

  BEGIN_PRIMERS_SWITCH(choice)
    MAP_EXIT(0, "Exiting")
    MAP_PRIMER(1)
    MAP_PRIMER(2)
    MAP_PRIMER(3)
    MAP_PRIMER(4)
    MAP_PRIMER(5)
    MAP_PRIMER(6)
    MAP_PRIMER(7)
    MAP_PRIMER(8)
    MAP_PRIMER(9)
    MAP_PRIMER(10)
    MAP_PRIMER(11)
    MAP_PRIMER(12)
    MAP_PRIMER(13)
    MAP_PRIMER(14)
    MAP_PRIMER(15)
    MAP_DEFAULT(concat(iolib::no_separator, "'", std::to_string(choice),
                       "' is an invalid option - please try again."))
  END_PRIMERS_SWITCH

  return true;
}

int main() {
  while (run_primers()) { }

  return 0;
}