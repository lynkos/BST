# README
Sorts all words in an input file (or from standard input) and prints the sorted words to an output file (or standard output). Command line arguments:

```
bstsort [-c] [-o output_file_name] [input_file_name]
```

If -c is present, the program needs to compare the strings in upper case.  Otherwise, the case stays as read in. If the output_file_name is given with the -o option, the program will output the sorted words to the given output file; otherwise, the output shall be the standard output. Similarly, if the input_file_name is given, the program will read from the input file; otherwise, the input will be from the standard input.
