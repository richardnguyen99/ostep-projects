# wcat

In this directory, you should write the program `wcat.c` and compile it into
the binary `wcat` (e.g., `gcc -o wcat wcat.c -Wall -Werror`).

After doing so, you can run the tests from this directory by running the
`test-wcat.sh` script. If all goes well, you will see:

```sh
prompt> ./test-wcat.sh
test 1: passed
test 2: passed
test 3: passed
test 4: passed
test 5: passed
test 6: passed
test 7: passed
prompt>
```

The `test-wcat.sh` script is just a wrapper for the `run-tests.sh` script in
the `tester` directory of this repository. This program has a few options; see
the relevant
[README](https://github.com/remzi-arpacidusseau/ostep-projects/blob/master/tester/README.md)
for details.

## Explanation

- Use `argc` and `argv` from `int main(int argc, const char* argv[])` to read
user input passed to the the program `wcat`. [^command_line_arguments_in_c]
- Use `fopen(3)` from the C standard libraries to open files from user input
strings. [^man_3_fopen]
- Use `fgets(3)` from the C standard libraries to read strings from file
pointers opened by `fopen(3)`. [^man_3_fgets]

## Footnotes

[^command_line_arguments_in_c]: [C Command Line Arguments](https://www.tutorialspoint.com/cprogramming/c_command_line_arguments.htm).

[^man_3_fopen]: [`fopen(3)` — Linux manual page](https://man7.org/linux/man-pages/man3/fopen.3.html)

[^man_3_fgets]: [`fgets(3)` — Linux manual page](https://man7.org/linux/man-pages/man3/fgets.3.html)