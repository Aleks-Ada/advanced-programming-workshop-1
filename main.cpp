#include <iostream>
#include <initializer_list>
#include <string>
#include <regex>
#include <cstdlib>

const std::regex ANY_REGEX = std::regex("^.*$");
const std::regex SIMPLE_SENTENCE_REGEX = std::regex("^[.,&!?\()\\/';:A-Za-z -]+$");
const std::regex TEMPERATURE_REGEX = std::regex("^\\d+.*\\d+$");
const std::regex C_OR_F_REGEX = std::regex("^C|F|c|f$");
const std::regex DIFFICULTY_LEVEL_REGEX = std::regex("^1|2|3$");
const std::regex PLAY_AGAIN_REGEX = std::regex("^Y|N$");
const std::regex ANY_LENGTH_NUMBER_REGEX = std::regex("^\\d+$");
const std::regex COST_REGEX = std::regex("^\\d+.\\d{2}$");
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

void run_primer_1() {
  practice_exercise_1();
}

std::string read_difficulty_level() {
  return read_regex_matching_string_with_prompt("Please pick a difficulty level (1, 2, or 3):", DIFFICULTY_LEVEL_REGEX);
}

int pick_random_number(const int low, const int high) {
  return (rand() % high) + low;
}

std::string read_guess(const std::string& prompt) {
  return read_regex_matching_string_with_prompt(prompt, ANY_REGEX);
}

std::string read_play_again() {
  return read_regex_matching_string_with_prompt("Do you want to play again (Y/N)?", PLAY_AGAIN_REGEX);
}

void run_primer_2() {
  print("Let's play 'Guess the Number'");

  while (true) {  
    const std::string difficulty = read_difficulty_level();

    int range_high;

    if (difficulty == "1") {
      range_high = 10;
    } else if (difficulty == "2") {
      range_high = 100;
    } else {
      range_high = 1000;
    }

    print_empty_line();
    print(concat(with(" "), "Great, I have randomly picked a number in the range 1 -", std::to_string(range_high)));

    int target_random_number = pick_random_number(1, range_high);
    int total_guesses = 0;
    std::string guess;
    int guess_int;

    while (true) {
      if (total_guesses == 0) {
        guess = read_guess("What's your guess?");
      } else if (!matches_regex(guess, NUMBER_REGEX)) {
        guess = read_guess("Please enter a positive numeric guess:");
      } else {
        guess_int = std::stoi(guess);

        if (guess_int == target_random_number) {
          break;
        } else if (guess_int < target_random_number) {
          guess = read_guess("Too low, guess again:");
        } else {
          guess = read_guess("Too high, guess again:");
        }
      }

      ++total_guesses;
    }

    print_empty_line();
    print(concat(with(" "),
      "Well done, the number was",
      std::to_string(target_random_number),
      "- you got it in",
      std::to_string(total_guesses),
      "guesses"));

    const std::string play_again = read_play_again();

    if (play_again == "N") {
      print("No problem, see you later.");
      break;
    }
  }
}

std::string read_quantity(const std::string& item_string) {
  return read_regex_matching_string_with_prompt(concat(with(" "),
    "Please enter a quantity for item",
    item_string,
    "(or 0 to finish):"),
    ANY_LENGTH_NUMBER_REGEX);
}

std::string read_cost(const std::string& item_string) {
  return read_regex_matching_string_with_prompt(concat(with(" "),
    "Please enter item",
    item_string,
    "cost:"),
    COST_REGEX);
}

int char_to_int(const char c) {
  return c - '0';
}

std::string pence_to_pound_string(const int pence) {
  const int pounds = static_cast<int>(pence / 100);
  const int remainder_pence = pence % 100;

  std::string remainder_pence_string = std::to_string(remainder_pence);

  if (remainder_pence_string.size() == 1) {
    remainder_pence_string += "0";
  }

  return concat(Separator::EMPTY,
    std::to_string(pounds),
    ".",
    remainder_pence_string);
}

void run_primer_3() {
  constexpr static float shopping_tax_percentage = 5.5f;
  int total_cost_pence = 0;

  for (int item = 1; ; ++item) {
    const std::string item_string = std::to_string(item);
    const std::string quantity = read_quantity(item_string);

    if (quantity == "0") {
      break;
    }

    const std::string cost = read_cost(item_string);

    const int digit0 = char_to_int(cost[0]);
    const int digit1 = char_to_int(cost[2]);
    const int digit2 = char_to_int(cost[3]);
    const int quantity_int = std::stoi(quantity);

    total_cost_pence += ((digit0 * 100) + (digit1 * 10) + (digit2)) * quantity_int;
  }

  const int shopping_tax = static_cast<int>((total_cost_pence / 100.0f) * shopping_tax_percentage);

  print("Thank you.");
  print_empty_line();
  print(concat(Separator::EMPTY, "Subtotal: £", pence_to_pound_string(total_cost_pence)));
  print(concat(Separator::EMPTY, "Shopping Tax: £", pence_to_pound_string(shopping_tax)));
  print_empty_line();
  print(concat(Separator::EMPTY, "Total: £", pence_to_pound_string(total_cost_pence + shopping_tax)));
}

int main() {
  // run_primer_1();
  // run_primer_2();
  // run_primer_3();
  practice_exercise_2();

  return 0;
}