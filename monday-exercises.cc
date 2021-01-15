#include <iostream>
#include <initializer_list>
#include <string>
#include <regex>
#include <cstdlib>

const std::regex ANY_REGEX = std::regex("^.*$");
const std::regex SIMPLE_SENTENCE_REGEX = std::regex("^[.,&!?\()\\/';:A-Za-z -]+$");
const std::regex TEMPERATURE_REGEX = std::regex("^\\d+.*\\d+$");
const std::regex C_OR_F_REGEX = std::regex("^C|F|c|f$");
const std::regex NUMBER_REGEX = std::regex("\\d+");

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

std::string read_quote() {
  return read_regex_matching_string_with_prompt("What is the quote?", SIMPLE_SENTENCE_REGEX);
}

std::string read_author() {
  return read_regex_matching_string_with_prompt("Who said it?", SIMPLE_SENTENCE_REGEX);
}

void print_empty_line() {
  print("");
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

void practice_exercise_1() {
  const std::string quote = read_quote();
  const std::string author = read_author();

  print_empty_line();
  print(concat(with(" "), author, "says:", concat(Separator::EMPTY, "\"", quote, "\"")));
}

std::string read_starting_temperature() {
  return read_regex_matching_string_with_prompt("Please enter the starting temperature:", TEMPERATURE_REGEX);
}

std::string read_temperature_conversion_choice() {
  return read_regex_matching_string_with_prompt("Your choice:", C_OR_F_REGEX);
}

float fahrenheit_to_centigrade(const float fahrenheit) {
  return (fahrenheit - 32.0f) * (5.0f / 9.0f);
}

float centigrade_to_fahrenheit(const float centigrade) {
  return (centigrade * (9.0f / 5.0f)) + 32.0f;
}

void practice_exercise_2() {
  const std::string starting_temperature = read_starting_temperature();

  print("Press 'C' to convert from Fahrenheit to Centigrade.");
  print("Press 'F' to convert from Centigrade to Fahrenheit.");

  print_empty_line();
  const std::string choice = read_temperature_conversion_choice();

  if (choice == "C") {
    print(concat(with(" "),
      starting_temperature,
      "degrees Fahrenheit is",
      std::to_string(fahrenheit_to_centigrade(std::stof(starting_temperature)))));
  } else {
    print(concat(with(" "),
      starting_temperature,
      "degrees Centigrade is",
      std::to_string(centigrade_to_fahrenheit(std::stof(starting_temperature)))));
  }
}

int main() {
  practice_exercise_1();
  practice_exercise_2();

  return 0;
}