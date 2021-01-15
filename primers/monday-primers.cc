#include "monday-primers.h"

#include <string>
#include <regex>

#include "io-lib.h"
#include "random.h"

const std::regex SIMPLE_SENTENCE_REGEX = std::regex("^[.,&!?\\()\\/';:A-Za-z -]+$");
const std::regex NUMBER_REGEX = std::regex("\\d+");
const std::regex NUMERIC_REGEX = std::regex("\\d");
const std::regex ALPHABETIC_REGEX = std::regex("[A-Za-z]");

std::string read_quote() {
  return read_regex_matching_string_with_prompt("What is the quote?", SIMPLE_SENTENCE_REGEX);
}

std::string read_author() {
  return read_regex_matching_string_with_prompt("Who said it?", SIMPLE_SENTENCE_REGEX);
}

void practice_exercise_1() {
  const std::string quote = read_quote();
  const std::string author = read_author();

  print_empty_line();
  print(concat(with(" "), author, "says:", concat(iolib::no_separator, "\"", quote, "\"")));
}

void run_primer_1() {
  practice_exercise_1();
}

std::string read_difficulty_level() {
  const std::regex DIFFICULTY_LEVEL_REGEX = std::regex("^1|2|3$");
  return read_regex_matching_string_with_prompt("Please pick a difficulty level (1, 2, or 3):", DIFFICULTY_LEVEL_REGEX);
}

std::string read_guess(const std::string& prompt) {
  return read_string_with_prompt(prompt);
}

std::string read_play_again() {
  const std::regex PLAY_AGAIN_REGEX = std::regex("^Y|N|y|n$");
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
    print(concat(with(" "),
      "Great, I have randomly picked a number in the range 1 -",
      std::to_string(range_high)));

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
    if (total_guesses == 1) {
      print("Wow, you are a mind reader!");
    } else if (total_guesses < 4) {
      print("Well done, most impressive!");
    } else if (total_guesses < 7) {
      print("Good, but I am sure you can do better!");
    } else {
      print("Better luck next time!");
    }
    print(concat(with(" "),
      "The number was",
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
    "(or 0 to finish):"), std::regex("^\\d+$"));
}

std::string read_cost(const std::string& item_string) {
  return read_regex_matching_string_with_prompt(concat(with(" "),
    "Please enter item",
    item_string,
    "cost:"), std::regex("^\\d+.\\d{2}$"));
}

int char_to_int(const char c) {
  return c - '0';
}

std::string pence_to_pound_string(const int pence) {
  const int pounds = static_cast<int>(pence / 100);
  const int remainder_pence = pence % 100;

  std::string remainder_pence_string = std::to_string(remainder_pence);

  if (remainder_pence_string.size() == 1) {
    remainder_pence_string = "0" + remainder_pence_string;
  }

  return concat(iolib::no_separator,
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
  print(concat(iolib::no_separator, "Subtotal: £", pence_to_pound_string(total_cost_pence)));
  print(concat(iolib::no_separator, "Shopping Tax: £", pence_to_pound_string(shopping_tax)));
  print_empty_line();
  print(concat(iolib::no_separator, "Total: £",
               pence_to_pound_string(total_cost_pence + shopping_tax)));
}