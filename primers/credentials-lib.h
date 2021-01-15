#ifndef CREDENTIALS_LIB_H
#define CREDENTIALS_LIB_H

#include "credentials-lib.h"

#include <string>
#include <map>

struct User {
  std::string username;
  std::string password;
  std::string name;
};

class CredentialStore {
public:
  virtual const std::map<std::string, User>& get() const = 0;
};

bool authenticates(const CredentialStore& credentials, const std::string& username, const std::string& password);

std::string get_name(const CredentialStore& credentials, const std::string& username);

std::string run_password_validator(const CredentialStore& credentials);

#endif // CREDENTIALS_LIB_H