#include "tuesday-primers.h"

#include <iostream>
#include <string>
#include <regex>

#include "io-lib.h"
#include "credentials-lib.h"

const std::regex SIMPLE_SENTENCE_REGEX = std::regex("^[.,&!?\\()\\/';:A-Za-z -]+$");
const std::regex NUMBER_REGEX = std::regex("\\d+");
const std::regex NUMERIC_REGEX = std::regex("\\d");
const std::regex ALPHABETIC_REGEX = std::regex("[A-Za-z]");

void insert(std::map<std::string, User>& map, const User& user) {
  map.insert(std::make_pair(user.username, user));
}

const std::map<std::string, User>& read_credentials() {
  static std::map<std::string, User> credentials;

  if (credentials.empty()) {
    insert(credentials, User{ "mike@ada.ac", "AdaRocks", "Mike" });
  }

  return credentials;
}

class InMemoryCredentialStore : public CredentialStore {
public:
  const std::map<std::string, User>& get() const override {
    return read_credentials();
  }
};

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
  print(concat(iolib::no_separator,
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

  print(concat(iolib::with_space,
               "There are",
               std::to_string(size_of_names),
               "employees:"));
  print_names(names, size_of_names);
  print_empty_line();

  const std::string name_to_remove = read_name_to_remove();

  print_empty_line();
  print(concat(iolib::with_space,
               "There are",
               std::to_string(size_of_names - 1),
               "employees:"));
  print_names_excluding(names, size_of_names, name_to_remove);
}
