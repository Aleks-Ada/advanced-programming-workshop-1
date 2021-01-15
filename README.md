# Advanced Programming - Workshop 1
All primer-related code is located within the primers/ directory.

Each weekday's primers are located in their own source and header files.

In addition, I have made three helper libraries:
1. `io-lib.h/cc `contains shared console input/output operations
2. `credentials-lib.h/cc` contains shared code for authenticating users from a file or in-memory
3. `random.h/cc` contains a random number generator function

Furthermore, I have the data files for Wednesday's exercises in the top-level directory:
- `contact-records` stores a list of universities and their phone numbers
- `credentials` stores the users' login details
- `data-file-parser` stores people's salaries

The challenges done for Monday and Tuesday are located in the top-level directory, under the names
`monday-exercises.cc` and `tuesday-exercises.cc`. They can be compiled by changing the .replit file
to compile them instead of the primers.