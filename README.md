# ForbiddenCombinations
Given M forbidden number combinations, prints the maximum subset of numbers, in which no forbidden combination is included.

Specifically, the program reads two integers N and M, where M is the amount of forbidden number combinations 
and N is the maximum number.
the i of the next M lines of input represent a forbidden number combination: a number k for the amount of numbers
followed by the k numbers of the combination.
outputs the maximum subset of numbers, in which no forbidden combination is included

written in C and OCaml. 

for C program:  
compile: gcc –std=c99 -Wall –Werror -O3 -o forbidden forbidden.c  
execute ./forbidden forbidden.txt

for OCaml program:  
compile: ocamlc -o dangerFinal forbiddenComb.ml   
execute: ./forbiddenComb "forbidden.txt"


forbidden.txt could be:

8 5   
2 1 2   
2 3 2   
1 7   
2 3 4   
3 5 6 4   
  
and the expected output: 1 3 5 6 8
