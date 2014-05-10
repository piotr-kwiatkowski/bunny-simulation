Bunny-Simulation
================

AKA Graduation


Requires:
- variables, data types, and numerical operators
- basic input/output
- logic (if statements, switch statements)
- loops (for, while, do-while)
- arrays
- pseudo random number generation
- strings & string functions
- functions
- structures/classes
- enumerated data
- file input/output
- pointers
- sorting
- linked lists
- advanced classes

Write a program that creates a linked list of bunny objects.
Each bunny object must have:
- Sex: Male, Female (random at creation 50/50)
- ??? Color: white, brown, black, spotted
- Age : 0-10 (years old)
- radioactive_mutant_vampire_bunny: true/false (decided at time of bunny creation 2% chance of true)

At program initialization 5 bunnies must be created and given random colors.
Each turn afterwards the bunnies age 1 year.
So long as there is at least one male age 2 or older,
for each female bunny in the list age 2 or older a new bunny is created each turn.
(i.e. if there was 1 adult male and 3 adult female bunnies, three new bunnies would be born each turn)
??? New bunnies born should be the same color as their mother.
If a bunny becomes older than 10 years old, it dies.
If a radioactive mutant vampire bunny is born
then each turn it will change exactly one non radioactive bunny into a radioactive vampire bunny.
(if there are two radioactive mutant vampire bunnies two bunnies will be changed each turn and so on...)
Radioactive vampire bunnies are excluded from regular breeding and do not count as adult bunnies.
Radioactive vampire bunnies do not die until they reach age 50.

The program should print a list of all the bunnies in the colony each turn
along w/ all the bunnies details, sorted by age.
The program should also output each turns events such as
"Bunny Thumper was born!
Bunny Fufu was born!
Radioactive Mutant Vampire Bunny Darth Maul was born!
Bunny Julius Caesar died!
The program should write all screen output to a file.
When all the bunnies have died the program terminates.
If the bunny population exceeds 1000 a food shortage must occur
killing exactly half of the bunnies (randomly chosen)
