==========  MathCMD - a Command Prompt-like calculator  ==========

Copyright© 2017 Haja Florin-Gabriel, Liceul Teoretic "Ion Luca" Vatra Dornei

This represents my own work for the computer science certificate.
These hundreds of lines of code are done my own pleasure of coding, so
PLEASE DO NOT DISRESPECT them and turn them into something jokeful!
I thought initally about an SQL-like command prompt, but my knowledge
in networking are poor, so I decided to go with something easier, such
as a number processing command processor.

Its idea consists of a 'while' loop with a STOP variable which is always 0
until we write the 'exit' command, when the STOP becomes 1 and the 
program stops. The command names are passed through a trie (a tree whose edges
represent a letter in the Latin alphabet) where the function codes are stored.
In case it exists, the function code is checked and the right function is called.
Then it checks its parameters by parsing the string (char array) which is read
from stdin (with cin.getline() command). In case they are in the correct order
the command is successfully executed, else it prints an error message.

Commands list (case-sensitive):

1. define [variable_name] [value]
  
   It declares a variable and attributes a floating-point value (double).
   
2. print [expression]
 
   It prints the typed expression on the console. Undeclared variables give an
   error.
   
3. undefine [variable_name]

   The opposite of the 'define' command. It sets its value to 0, it undeclares
   the variable.
 
4. exit

   Closes the program, after deleting the trie of the function names.
