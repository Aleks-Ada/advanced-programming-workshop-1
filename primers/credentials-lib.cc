#include "credentials-lib.h"

#include "io-lib.h"

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

std::string read_username() {
  return read_string_with_prompt("Username:");
}

std::string read_password() {
  return read_string_with_prompt("Password:");
}

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