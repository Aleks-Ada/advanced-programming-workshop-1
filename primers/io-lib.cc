#include "io-lib.h"

#include <iostream>

void print(const std::string_view output, const std::string_view end_with) {
  std::cout << output << end_with;
}

void print_empty_line() {
  print("");
}

bool matches_regex(const std::string& target, const std::regex& regex) {
  std::smatch match;
  return regex_match(target, regex);
}

std::string read_string() {
  std::string input;
  std::getline(std::cin, input);
  return input;
}

std::string read_string_with_prompt(const std::string& prompt) {
  print(prompt, " ");
  return read_string();
}

std::string read_regex_matching_string_with_prompt(const std::string& prompt, const std::regex& regex) {
  std::string read_string = read_string_with_prompt(prompt);

  while (!matches_regex(read_string, regex)) {
    read_string = read_string_with_prompt(prompt);
  }

  return read_string;
}

Separator with(const std::string& value) {
  return Separator{ value };
}