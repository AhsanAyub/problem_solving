## Indexing Words

### Input
 * The file consists of a number of lines, separated by line breaks. 
 * Each line contains "words" made up of lower case alphabetical characters separated by white space.
 * We can assume that the file is small enough to fit in working memory.

### Output
 * TFor each word w in the input, there is an entry of the form w
 num1 num2 ... <carriage_return>
 such that num1, num2,... are the line numbers in the input on which
 w occurs. If w occurs more than once on a given line, the line number
 should only occur once.

```
For example, if the input is:

the quick brown fox jumps over
the lazy
lazy lazy
dog

then the output will be: 

brown 1
dog 4
fox 1
jumps 1
lazy 2 3
over 1
quick 1
the 1 2
```

### Compilation

Each solution file has the compilation process in its first two lines.