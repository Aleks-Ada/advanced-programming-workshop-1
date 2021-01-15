#include "wednesday-primers.h"

#include <iostream>
#include <string>
#include <regex>
#include <fstream>
#include <algorithm>

#include "io-lib.h"
#include "credentials-lib.h"
#include "random.h"

std::vector<std::string> read_file(const std::string& name) {
  std::vector<std::string> lines;

  std::ifstream file;
  file.open(name);

  for (std::string line; std::getline(file, line);) {
    lines.emplace_back(line);
  }

  return lines;
}

int calculate_column_padding(const std::string& title, const std::vector<std::string>& values) {
  const std::string& max_size_string = *std::max_element(values.begin(), values.end(),
                                                         [](const std::string& s1,
                                                            const std::string& s2) {
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

  std::transform(first_names.begin(), first_names.end(), output.begin(),
                 [](const std::string& string) {
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
  print(concat(column_separator, pad("Initial", initial_column_padding),
               pad("Last", last_column_padding), pad("Salary", salary_column_padding)));
  print(concat(column_separator, std::string(initial_column_padding, '-'),
               std::string(last_column_padding, '-'), std::string(salary_column_padding, '-')));
  for (int index = 0; index < lines.size(); ++index) {
    const std::string& initial = initials.at(index);
    const std::string& last_name = last_names.at(index);
    const std::string& salary = salaries.at(index);

    print(concat(column_separator, pad(initial, initial_column_padding),
                 pad(last_name, last_column_padding), pad(salary, salary_column_padding)));
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

  if (records.empty()) {
    const std::vector<std::string> lines = read_file("contact-records");
    for (const std::string& line : lines) {
      const std::vector<std::string> values = split_string(line, ',');
      ContactRecord record{values[0], values[1]};

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
  print(concat(iolib::with_space, "Searching", std::to_string(get_records().size() / 2), "records ..."));

  ContactRecord record;

  bool found = try_find_name(search_string, &record);
  if (!found) {
    found = try_find_phone(search_string, &record);
  }

  print_empty_line();
  if (found) {
    print("Contact details:");
    print(concat(iolib::no_separator, record.name, ", T: ", record.phone));
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
      credentials.insert(std::make_pair(values[0], User{values[0], values[1], values[2]}));
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

    std::transform(credentials.begin(), credentials.end(), lines.begin(),
                   [](const std::pair<std::string, User> pair) {
                     const User& user = pair.second;
                     return concat(with(","), user.username, user.password, user.name);
                   });

    save_file("credentials", lines);
  }

private:
  std::map<std::string, User> credentials;
};

std::string read_update_password_choice() {
  return read_regex_matching_string_with_prompt("Would you like to update your password with with"
                                                " a randomly generated one (Y/N)?",
                                                std::regex("^Y|N|y|n$"));
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
    print(concat(iolib::with_space, "Your new password is", random_password));
  } else {
    print("Okay, bye.");
  }
}