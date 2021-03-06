#ifndef IO_LIB_H
#define IO_LIB_H

#include <string>
#include <string_view>
#include <regex>

void print(std::string_view output, std::string_view end_with = "\n");
void print_empty_line();

bool matches_regex(const std::string& target, const std::regex& regex);

std::string read_string();
std::string read_string_with_prompt(const std::string& prompt);
std::string read_regex_matching_string_with_prompt(const std::string& prompt, const std::regex& regex);

struct Separator {
  std::string value;
};
Separator with(const std::string& value);

namespace iolib {
inline const Separator no_separator{ "" };
inline const Separator with_space{ " " };
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