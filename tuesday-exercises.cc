#include <iostream>
#include <initializer_list>
#include <string>
#include <regex>
#include <cstdlib>

const std::regex ANY_REGEX = std::regex("^.*$");

void print(const std::string& output, const std::string& end_with = "\n") {
  std::cout << output << end_with;
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

bool matches_regex(const std::string& target, const std::regex& regex) {
  std::smatch match;
  return regex_match(target, regex);
}

std::string read_regex_matching_string_with_prompt(const std::string& prompt, const std::regex& regex) {
  std::string read_string = read_string_with_prompt(prompt);

  while (!matches_regex(read_string, regex)) {
    read_string = read_string_with_prompt(prompt);
  }

  return read_string;
}

struct Separator {
  static const Separator EMPTY;

  Separator(std::string value) : value(value) { }
  std::string value;
};
const Separator Separator::EMPTY("");

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

Separator with(std::string value) {
  return Separator(value);
}

std::string read_word() {
  return read_regex_matching_string_with_prompt("Please enter a word:", ANY_REGEX);
}

std::string reverse(const std::string& word) {
  std::string reverse;

  for (auto current = word.end(); current >= word.begin(); --current) {
    reverse += *current;
  }

  return reverse;
}

void reverse_word() {
  const std::string word = read_word();
  print(concat(with(" "),
    word,
    "spelt backwards is:",
    reverse(word)));
}

std::string to_lowercase(const std::string& word) {
  std::string lowercase;

  for (auto current = word.begin(); current < word.end(); ++current) {
    lowercase += std::tolower(*current);
  }

  return lowercase;
}

void convert_lower_case() {
  const std::string word = read_word();
  print(concat(with(" "),
    word,
    "converted to lower case is:",
    to_lowercase(word)));
}

bool is_palindrome(const std::string& word) {
  for (auto from_start = word.begin(),
            from_end = word.end() - 1;
       from_end > from_start;
       ++from_start, --from_end) {
    if ((*from_start) != (*from_end)) {
      return false;
    }
  }

  return true;
}

void palindrome_checker() {
  const std::string word = read_word();

  if (is_palindrome(to_lowercase(word))) {
    print(concat(Separator::EMPTY,
      "Yes, '",
      word,
      "' is a palindrome"));
  } else {
    print(concat(Separator::EMPTY,
      "Sorry, '",
      word,
      "' is not a palindrome"));
  }
}

int main() {
  reverse_word();
  convert_lower_case();
  palindrome_checker();

  return 0;
}