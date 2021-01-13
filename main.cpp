#include <iostream>
#include <initializer_list>
#include <string>
#include <regex>
#include <cstdlib>
#include <fstream>
#include <algorithm>

const std::regex ANY_REGEX = std::regex("^.*$");
const std::regex SIMPLE_SENTENCE_REGEX = std::regex("^[.,&!?\()\\/';:A-Za-z -]+$");
const std::regex TEMPERATURE_REGEX = std::regex("^\\d+.*\\d+$");
const std::regex C_OR_F_REGEX = std::regex("^C|F|c|f$");
const std::regex DIFFICULTY_LEVEL_REGEX = std::regex("^1|2|3$");
const std::regex PLAY_AGAIN_REGEX = std::regex("^Y|N$");
const std::regex ANY_LENGTH_NUMBER_REGEX = std::regex("^\\d+$");
const std::regex COST_REGEX = std::regex("^\\d+.\\d{2}$");
const std::regex NUMBER_REGEX = std::regex("\\d+");
const std::regex NUMERIC_REGEX = std::regex("\\d");
const std::regex ALPHABETIC_REGEX = std::regex("[A-Za-z]");
const std::regex YES_NO_REGEX = std::regex("^Y|N|y|n$");

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
  return low + (std::rand() % (high - low + 1));
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

std::string read_username() {
  return read_string_with_prompt("Username:");
}

std::string read_password() {
  return read_string_with_prompt("Password:");
}

struct User {
  User(const std::string& username, const std::string& password, const std::string& name) : username(username), password(password), name(name) {}
  std::string username;
  std::string password;
  std::string name;
};

void insert(std::map<std::string, User>& map, const User& user) {
  map.insert(std::make_pair(user.username, user));
}

const std::map<std::string, User>& read_credentials() {
  static std::map<std::string, User> credentials;

  if (credentials.size() == 0) {
    insert(credentials, User{ "mike@ada.ac", "AdaRocks", "Mike" });
  }

  return credentials;
}

class CredentialStore {
public:
  virtual const std::map<std::string, User>& get() const = 0;
};

bool authenticates(const CredentialStore& credentials, const std::string& username, const std::string& password) {
  auto user_search = credentials.get().find(username);

  if (user_search == credentials.get().end()) {
    return false;
  }

  return user_search->second.password == password;
}

std::string get_name(const CredentialStore& credentials, const std::string& username) {
  return credentials.get().find(username)->second.name;
}

class InMemoryCredentialStore : public CredentialStore {
public:
  const std::map<std::string, User>& get() const override {
    return read_credentials();
  }
};

std::string run_password_validator(const CredentialStore& credentials) {
  const std::string username = read_username();
  const std::string password = read_password();

  print_empty_line();

  if (authenticates(credentials, username, password)) {
    print(concat(with(" "),
      "Welcome",
      get_name(credentials, username)));
  } else {
    print("Failed to authenticate");
  }

  return username;
}

void run_primer_4() {
  run_password_validator(InMemoryCredentialStore());
}

enum PasswordStrength {
  Weak,
  Moderate,
  Strong,
  VeryStrong
};

PasswordStrength test_strength(const std::string& password) {
  int numeric = 0;
  int alphabetic = 0;
  int special = 0;

  for (const char c : password) {
    std::string string(1, c);

    if (matches_regex(string, NUMERIC_REGEX)) {
      ++numeric;
    } else if (matches_regex(string, ALPHABETIC_REGEX)) {
      ++alphabetic;
    } else {
      ++special;
    }
  }

  if (password.size() >= 8 &&
      numeric >= 2 &&
      alphabetic >= 4 &&
      special >= 1) {
    return VeryStrong;
  } else if (password.size() >= 8 &&
             numeric >= 2 &&
             alphabetic >= 4) {
    return Strong;
  } else if ((numeric > 0 && alphabetic == 0 && special == 0) ||
    (alphabetic > 0 && numeric == 0 && special == 0)) {
    return Weak;
  } else {
    return Moderate;
  }
}

#define START_ENUM_SWITCH(value) switch (value) {
#define MAP(value, name) case value: return "" #name "";
#define END_ENUM_SWITCH }

std::string strength_to_string(const PasswordStrength strength) {
  START_ENUM_SWITCH(strength)
    MAP(Weak, weak)
    MAP(Moderate, moderate)
    MAP(Strong, strong)
    MAP(VeryStrong, very strong)
  END_ENUM_SWITCH
}

void print_password_security(const std::string& password) {
  print(concat(Separator::EMPTY,
    "The password '",
    password,
    "' is ",
    strength_to_string(test_strength(password))));
}

void run_primer_5() {
  print_password_security("12345678");
  print_password_security("AB235");
  print_password_security("Password2021");
  print_password_security("Password2021!");
}

void print_names(const std::string* names, const int size) {
  for (int index = 0; index < size; ++index) {
    print(*(names + index));
  }
}

std::string read_name_to_remove() {
  return read_string_with_prompt("Enter an employee name to remove:");
}

void print_names_excluding(const std::string* names, const int size, const std::string& excluding) {
  for (int index = 0; index < size; ++index) {
    const std::string& name = *(names + index);

    if (name != excluding) {
      print(name);
    }
  }
}

void run_primer_6() {
  static constexpr int size_of_names = 5;
  const std::string names[size_of_names] = {
    "John Smith",
    "Jaelynn Stuart",
    "Kaley Barajas",
    "Walter Collier",
    "Cale Myers"
  };

  print(concat(with(" "),
    "There are",
    std::to_string(size_of_names),
    "employees:"));
  print_names(names, size_of_names);
  print_empty_line();

  const std::string name_to_remove = read_name_to_remove();

  print_empty_line();
  print(concat(with(" "),
    "There are",
    std::to_string(size_of_names - 1),
    "employees:"));
  print_names_excluding(names, size_of_names, name_to_remove);
}

std::vector<std::string> read_file(const std::string& name) {
  std::vector<std::string> lines;

  std::ifstream file;
  file.open(name);

  for (std::string line; std::getline(file, line); ) {
    lines.emplace_back(line);
  }

  return lines;
}

int calculate_column_padding(const std::string& title, const std::vector<std::string>& values) {
  const std::string& max_size_string = *std::max_element(values.begin(), values.end(), [](const std::string& s1, const std::string& s2) {
    return s1.size() < s2.size();
  });

  if (max_size_string.size() > title.size()) {
    return max_size_string.size() + 1;
  }

  return title.size() + 1;
}

std::string pad(const std::string& string, const int padding) {
  std::string padded;

  std::copy(string.begin(), string.end(), std::back_inserter(padded));

  padded += std::string(padding - string.size(), ' ');

  return padded;
}

std::vector<std::string> split_string(const std::string& string, const char token) {
  std::vector<std::string> split;
  std::string current;

  for (const char c : string) {
    if (c == token) {
      split.push_back(current);
      current.clear();
    } else {
      current += c;
    }
  }
  split.emplace_back(current);

  return split;
}

std::vector<std::string> get_data_index(const std::vector<std::string>& data, const int index) {
  std::vector<std::string> output(data.size());

  std::transform(data.begin(), data.end(), output.begin(), [index](const std::string& string) {
    return split_string(string, ',').at(index);
  });

  return output;
}

std::vector<std::string> get_initials(const std::vector<std::string>& data) {
  const std::vector<std::string> first_names = get_data_index(data, 0);
  std::vector<std::string> output(first_names.size());

  std::transform(first_names.begin(), first_names.end(), output.begin(), [](const std::string& string) {
    return std::string(1, string[0]) + ".";
  });

  return output;
}

std::vector<std::string> get_last_names(const std::vector<std::string>& data) {
  return get_data_index(data, 1);
}

std::vector<std::string> get_salaries(const std::vector<std::string>& data) {
  const std::vector<std::string> salaries = get_data_index(data, 2);
  std::vector<std::string> output(salaries.size());

  std::transform(salaries.begin(), salaries.end(), output.begin(), [](const std::string& string) {
    return "£" + string;
  });

  return output;
}

void run_primer_7() {
  const std::vector<std::string> lines = read_file("data-file-parser");

  const std::vector<std::string> initials = get_initials(lines);
  const std::vector<std::string> last_names = get_last_names(lines);
  const std::vector<std::string> salaries = get_salaries(lines);

  const int initial_column_padding = calculate_column_padding("Initial", initials);
  const int last_column_padding = calculate_column_padding("Last", last_names);
  const int salary_column_padding = calculate_column_padding("Salary", salaries);

  const Separator column_separator = with("    ");
  print(concat(column_separator,
    pad("Initial", initial_column_padding),
    pad("Last", last_column_padding),
    pad("Salary", salary_column_padding)));
  print(concat(column_separator,
    std::string(initial_column_padding, '-'),
    std::string(last_column_padding, '-'),
    std::string(salary_column_padding, '-')));
  for (int index = 0; index < lines.size(); ++index) {
    const std::string& initial = initials.at(index);
    const std::string& last_name = last_names.at(index);
    const std::string& salary = salaries.at(index);

    print(concat(column_separator,
      pad(initial, initial_column_padding),
      pad(last_name, last_column_padding),
      pad(salary, salary_column_padding)));
  }
}

struct ContactRecord {
  std::string name;
  std::string phone;
};

std::string read_search_string() {
  return read_string_with_prompt("Please enter a name or number to search:");
}

const std::map<std::string, ContactRecord>& get_records() {
  static std::map<std::string, ContactRecord> records;

  if (records.size() == 0) {
    const std::vector<std::string> lines = read_file("contact-records");
    for (const std::string& line : lines) {
      const std::vector<std::string> values = split_string(line, ',');
      ContactRecord record{ values[0], values[1] };

      records.insert(std::make_pair(record.name, record));
      records.insert(std::make_pair(record.phone, record));
    }
  }

  return records;
}

bool try_find_value(const std::string& search_string, ContactRecord* record) {
  auto search = get_records().find(search_string);

  if (search != get_records().end()) {
    *record = search->second;
    return true;
  }

  return false;
}

bool try_find_name(const std::string& search_string, ContactRecord* record) {
  return try_find_value(search_string, record);
}

bool try_find_phone(const std::string& search_string, ContactRecord* record) {
  return try_find_value(search_string, record);
}

void run_primer_8() {
  const std::string search_string = read_search_string();
  print(concat(with(" "),
    "Searching",
    std::to_string(get_records().size() / 2),
    "records ..."));

  ContactRecord record;

  bool found = try_find_name(search_string, &record);
  if (!found) {
    found = try_find_phone(search_string, &record);
  }

  print_empty_line();
  if (found) {    
    print("Contact details:");
    print(concat(Separator::EMPTY,
      record.name,
      ", T: ",
      record.phone));
  } else {
    print("Sorry, no contact details found");
  }
}

void save_file(const std::string& name, const std::vector<std::string>& lines) {
  std::ofstream output(name, std::ios::out);

  for (const std::string& line : lines) {
    output << line << std::endl;
  }
}

class FileCredentialStore : public CredentialStore {
public:
  FileCredentialStore() {
    const std::vector<std::string> lines = read_file("credentials");
    for (const std::string& line : lines) {
      const std::vector<std::string> values = split_string(line, ',');
      credentials.insert(std::make_pair(values[0], User{ values[0], values[1], values[2] }));
    }
  }

  const std::map<std::string, User>& get() const override {
    return credentials;
  }

  void update(const std::string& username, const std::string& new_password) {
    std::string& password = credentials.find(username)->second.password;

    password.clear();
    password += new_password;

    std::vector<std::string> lines(credentials.size());

    std::transform(credentials.begin(), credentials.end(), lines.begin(), [](const std::pair<std::string, User> pair) {
      const User& user = pair.second;
      return concat(with(","), user.username, user.password, user.name);
    });

    save_file("credentials", lines);
  }

private:
  std::map<std::string, User> credentials;
};

std::string read_update_password_choice() {
  return read_regex_matching_string_with_prompt("Would you like to update your passwith with a randomly generated one (Y/N)?", YES_NO_REGEX);
}

std::string generate_random_password() {
  static constexpr int length = 10;

  std::string password;

  for (int index = 0; index < length; ++index) {
    password += static_cast<char>(pick_random_number(33, 126));
  }

  return password;
}

void run_primer_9() {
  FileCredentialStore fileCredentialStore = FileCredentialStore();

  const std::string username = run_password_validator(fileCredentialStore);
  const std::string update_password = read_update_password_choice();

  if (update_password == "Y") {
    const std::string random_password = generate_random_password();
    fileCredentialStore.update(username, random_password);
    print(concat(with(" "),
      "Your new password is",
      random_password));
  } else {
    print("Okay, bye.");
  }
}

int main() {
  // run_primer_1();
  // run_primer_2();
  // run_primer_3();
  // run_primer_4();
  // run_primer_5();
  // run_primer_6();
  // run_primer_7();
  // run_primer_8();
  run_primer_9();

  return 0;
}