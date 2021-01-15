#include "friday-primers.h"

#include <utility>

#include "io-lib.h"

class Circle {
private:
  static constexpr float PI = 3.14159f;
  int x;

public:
  Circle() {
    x = 10;
  }

  explicit Circle(const int x) : x(x) {
  }

  ~Circle() {
    print("Done");
  }

  float area(const float r) const {
    return PI * r * r;
  }

  int X() const {
    return x;
  }

  void X(int x) {
    this->x = x;
  }

  int y = 20;
};

void run_primer_13() {
  Circle myCircle1;
  print(concat(iolib::with_space, "Area:", std::to_string(myCircle1.area(27))));
  myCircle1.X(37);
  print(concat(iolib::with_space, "X:", std::to_string(myCircle1.X())));
  print(concat(iolib::with_space, "Area:", std::to_string(myCircle1.area(37))));
  print_empty_line();
}

class PhoneBook {
private:
  static constexpr int max_entry_count = 5;
  std::string entries[max_entry_count];
  int count;

public:
  PhoneBook() : count(0) {
  }

  bool add_entry(const std::string& entry) {
    if (count == max_entry_count) {
      return false;
    }

    entries[count] = entry;
    ++count;

    return true;
  }

  const std::string* list_entries() const {
    return entries;
  }

  int count_entries() const {
    return count;
  }
};

std::string read_phone_directory_choice() {
  return read_regex_matching_string_with_prompt("Please select an option (or 0 to finish):",
                                                std::regex("^0|1|2$"));
}

void run_primer_14() {
  PhoneBook phone_book;

  while (true) {
    print("Phone Directory (version 2)");
    print("1. Add an Entry");
    print("2. List All Entries");

    const std::string choice = read_phone_directory_choice();

    if (choice == "1") {
      if (phone_book.count_entries() == 5) {
        print("Reached maximum record quantity (5). Can't add any more records.");
      } else {
        const std::string& record_to_add = read_string_with_prompt("Enter a record to add:");
        phone_book.add_entry(record_to_add);
      }
    } else if (choice == "2") {
      print(concat(iolib::no_separator, "All Entries (Available: ",
                   std::to_string(phone_book.count_entries()), ")"));
      const std::string* entries = phone_book.list_entries();

      for (int index = 0; index < phone_book.count_entries(); ++index) {
        print(concat(iolib::no_separator, std::to_string(index + 1), ". ", *(entries + index)));
      }
    } else {
      break;
    }
  }
}

class Car {
private:
  std::string colour;
  std::string make;
  bool is_engine_on;
  bool is_locked;

public:
  Car(std::string colour, std::string make, const bool is_engine_on, const bool is_locked) : colour(
      std::move(colour)), make(std::move(make)), is_engine_on(is_engine_on), is_locked(is_locked) {
  }

  const std::string& get_colour() const {
    return colour;
  }

  const std::string& get_make() const {
    return make;
  }

  void set_colour(const std::string& colour) {
    this->colour = colour;
  }

  void set_make(const std::string& make) {
    this->make = make;
  }

  void engine_off() {
    if (is_engine_on) {
      print("Turning the engine off");
      is_engine_on = false;
    } else {
      print("Sorry, the engine is already off");
    }
  }

  void engine_on() {
    if (is_engine_on) {
      print("Sorry, the engine is already on");
    } else {
      print("Turning the engine on");
      is_engine_on = true;
    }
  }

  void locked(const bool state) {
    if (state) {
      if (is_locked) {
        print("Sorry, the car is already locked");
      } else {
        print("Locking the car");
        is_locked = true;
      }
    } else {
      if (is_locked) {
        print("Unlocking the car");
        is_locked = false;
      } else {
        print("Sorry, the car is already unlocked");
      }
    }
  }

  void status() {
    print(concat(iolib::no_separator, "Car Status: ", "Colour: ", colour, ", Make: ", make,
                 ", Engine: ", is_engine_on ? "On" : "Off", is_locked ? ", Locked" : ", Unlocked"));
  }
};

std::string read_car_action_choice() {
  return read_regex_matching_string_with_prompt("Please select an option (or 0 to finish):",
                                                std::regex("^0|1|2|3|4$"));
}

void run_primer_15() {
  Car car("Black", "Agera RS", true, true);

  while (true) {
    car.status();
    print("1. Turn Engine On");
    print("2. Turn Engine Off");
    print("3. Lock Car");
    print("4. Unlock Car");

    const std::string option = read_car_action_choice();

    if (option == "1") {
      car.engine_on();
    } else if (option == "2") {
      car.engine_off();
    } else if (option == "3") {
      car.locked(true);
    } else if (option == "4") {
      car.locked(false);
    } else {
      break;
    }

    print_empty_line();
  }
}