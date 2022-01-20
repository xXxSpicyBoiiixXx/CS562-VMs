# Notes Lab01: Preliminaries for Project 1

We followed the instruction but instead of having the linker be 

ld65 -t sim6502 -o test test.o lib/sim6502.lib 

We replaced test with test1 as there is already a test directory. 

From here we can now excute out simulator. 

For some reason we can't cross compile the fib.c file? I'm not exactly sure why. 

1/10/2022
Tried to do both recursive and non-recursive types for cross compliation. The following out comes came to be. 

1) For our recursive fib file, we had issues compiling the file and I have dumped the error output in a directory as a text based file. 
2) For our non-recursive fib file, we have that it will work until N = 25, where we get a negative output. It does compile but I think it maybe due to the integer being out of the range of ~65,00


### 01/18/2020

Taking a closer look it seems that the 6502 processor might not be able to take large amount of fib. For instance:

This is the C output below: 

0
1
1
2
3
5
8
13
21
34
55
89
144
233
377
610
987
1597
2584
4181
6765
10946
17711
28657
46368

For our simulated 6502 processor we get the same value except the last one which turns to be -19168. 

Now moving to a smaller represetnation e.g. N = 10 we will get the same values. 

Moving on to the assembly representation. 




