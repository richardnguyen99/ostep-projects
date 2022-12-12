# wgrep

In this directory, you should write the program `wgrep.c` and compile it into
the binary `wgrep` (e.g., `gcc -o wgrep wgrep.c -Wall -Werror`).

After doing so, you can run the tests from this directory by running the
`test-wgrep.sh` script. If all goes well, you will see:

```sh
prompt> ./test-wgrep.sh
test 1: passed
test 2: passed
test 3: passed
test 4: passed
test 5: passed
test 6: passed
test 7: passed
prompt>
```

The `test-wgrep.sh` script is just a wrapper for the `run-tests.sh` script in
the `tester` directory of this repository. This program has a few options; see
the relevant
[README](https://github.com/remzi-arpacidusseau/ostep-projects/blob/master/tester/README.md)
for details.

## Explanation

- Lines can be substantially long, therefore `getline(3)` is used to read lines
from file streams. [^1]
- Since `getline(3)` will dynamically allocated a string to fit a line,
deallocation should be used, i.e, `free(3)`. [^2]
- To find if a line contains the pattern, a naive string-searching algorithm is
used. However, the time complexity is $O(nm)$ with $n$ as the length of string and $m$ as the length of the patter, which is  the worst compared to others. [^3]

## Footnotes 

[^1]: [man 3 getline](https://man7.org/linux/man-pages/man3/getline.3.html)
[^2]: [man 3 free](https://man7.org/linux/man-pages/man3/free.3.html)
[^3]: [String searching algorithms](https://en.wikipedia.org/wiki/String-searching_algorithm)
