#ifndef IO_LIB_H
#define IO_LIB_H

#include <string>
#include <regex>

void print(const std::string& output, const std::string& end_with = "\n");
void print_empty_line();

bool matches_regex(const std::string& target, const std::regex& regex);

std::string read_string();
std::string read_string_with_prompt(const std::string& prompt);
std::string read_regex_matching_string_with_prompt(const std::string& prompt, const std::regex& regex);

struct Separator {
  std::string value;

  static const Separator EMPTY;
};
Separator with(const std::string& value);

namespace iolib {
static const Separator with_space{ " " };
} // namespace iolib

template<typename ...TArgs>
std::string concat(const Separator& separator, const TArgs&... strings) {
  const std::string strings_array[] = { strings... };
  const auto* strings_array_final_element = std::end(strings_array) - 1;

  std::string output;  

  for (const auto* current = std::begin(strings_array); current < strings_array_final_element; ++current) {
    output += *current;
    output += separator.value;
  }
  output += *strings_array_final_element;

  return output;
}

#endif // IO_LIB_H