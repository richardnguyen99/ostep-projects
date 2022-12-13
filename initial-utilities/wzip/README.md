# wzip

In this directory, you should write the program `wzip.c` and compile it into
the binary `wzip` (e.g., `gcc -o wzip wzip.c -Wall -Werror`).

After doing so, you can run the tests from this directory by running the
`test-wzip.sh` script. If all goes well, you will see:

```sh
prompt> ./test-wzip.sh
test 1: passed
test 2: passed
test 3: passed
test 4: passed
test 5: passed
test 6: passed
prompt>
```

The `test-wzip.sh` script is just a wrapper for the `run-tests.sh` script in
the `tester` directory of this repository. This program has a few options; see
the relevant
[README](https://github.com/remzi-arpacidusseau/ostep-projects/blob/master/tester/README.md)
for details.

## Explanation

- Use `fwrite(3)` to write binary format to the stream, in this case, `stdout`. [^1]
- First parameter is a pointer, that's why `&(rleobj.l)` and `&(rleobj.c)` are used.
- This line

```c
fwrite((int *)(&(rleobj.l)), sizeof(int), 1, stdout);
```

tells that I want to write 4 bytes (`sizeof(int)`) of the first parameter (
`&(rleobj.l)`) to the standard output (`stdout`) one time (`1`). The typecast
is optional (depending on your compiler and how you want to read your code).

The reason why they require you to do so is because it will separate between the run-length part and the character part.

Let's say you have a simple input file like this:

```txt
333333333333333333333333333333333aaaaaaaaaaaa
```

After encoding without the binary format:

```txt
33312a
```

This is wrong. Because now, it looks like the run-length of the character `a` is `33312`, instead of `33` of `3` and `12` of `a`.

However, with binary format, those parts are separated:

```sh
❯ xxd -b output.z
00000000: 00100001 00000000 00000000 00000000 00110011 00001100  !...3.
00000006: 00000000 00000000 00000000 01100001                    ...a
```

Here, the first four bytes represent the run-length and the next one byte represents the character.

## Footnotes

[^1]: [`man 3p fwrite`](https://man7.org/linux/man-pages/man3/fwrite.3p.html)
