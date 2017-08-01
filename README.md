Graduation
==========
C++ implementation of [this](http://www.cplusplus.com/forum/articles/12974/) excercise.

Write a program that creates a linked list of bunny objects.

---

#### Each bunny object must have:
- Sex: male, female (random at creation 50/50)
- Color: white, brown, black, spotted
- Age: 0-10 (years old)
- Radioactive mutant vampire bunny: true/false (occurrence possibility: 2%)

---

## Main tasks:
1. At program initialization 5 bunnies must be created and given random colors.
1. Each turn afterwards the bunnies age 1 year.
1. So long as there is at least one male age 2 or older, for each female bunny in the list age 2 or older a new bunny is created each turn (i.e. if there was 1 adult male and 3 adult female bunnies, three new bunnies would be born each turn).
1. New bunnies born should be the same color as their mother.
1. If a bunny becomes older than 10 years old, it dies.
1. If a radioactive mutant vampire bunny is born then each turn it will change exactly one non radioactive bunny into a radioactive vampire bunny (if there are two radioactive mutant vampire bunnies two bunnies will be changed each turn and so on)
1. Radioactive vampire bunnies are excluded from regular breeding and do not count as adult bunnies.
1. Radioactive vampire bunnies do not die until they reach age 50.

---

#### Also:
- The program should print a list of all the bunnies in the colony each turn along with all the bunnies details, sorted by age.
- The program should also output each turns events such as:
 "Bunny Thumper was born!
 Bunny Fufu was born!
 Radioactive Mutant Vampire Bunny Darth Maul was born!
 Bunny Julius Caesar died!"
- The program should write all screen output to a file.
- When all the bunnies have died the program terminates.
- If the bunny population exceeds 1000 a food shortage must occur killing exactly half of the bunnies (randomly chosen)

---

## Optional tasks:
★ Modify the program to run in real time, with each turn lasting 2 seconds, and a one second pause between each announement.

★★ Allow the user to hit the 'k' key to initiate a mass rabit cull! which causes half of all the rabits to be killed (randomly chosen).

★★★★ Modify the program to place the rabits in an 80x80 grid. Have the rabits move one space each turn randomly. Mark juvenile males with m, adult males w/ M, juvenile females w/ f, adult femails w/ F, radioactive mutant vampire bunnies with X.
Modify the program so that radioactive mutant vampire bunnies only convert bunnies that end a turn on an adjacent square.
Modify the program so that new babies are born in an empty random adjacent square next to the mother bunny. (if no empty square exits then the baby bunny isn't born)

★★★★★ Modify the program so that it saves each turn to a file and can play back at accelearted speed all subsequent turns.

---

#### Project requires: (crossed out if already done)
~~variables, data types and numerical operators~~, ~~basic input/output~~, ~~logic (if statements, switch statements)~~, ~~loops (for, while, do-while)~~, ~~arrays~~, ~~pseudo random number generation~~, ~~strings & string functions~~, ~~functions~~, ~~structures/classes~~, enumerated data, ~~file input/output~~, ~~pointers~~, ~~sorting~~, ~~linked lists~~, advanced classes (?)

---

# **2017 Update:**
### *TODO:*
- [x] ~~Play around with already written code / check current project state, store notes in *.txt* file~~ **DONE: 13-03-2017**
- [ ] Analyse project again, prepare UML diagrams
- [x] ~~Main tasks:~~
  - [x] ~~Main task #1~~ **DONE: 2017-03-13**
  - [x] ~~Main task #2~~ **DONE: 2017-07-26**
  - [x] ~~Main task #3~~ **DONE: 2017-07-27**
  - [X] ~~Main task #4~~ **DONE: 2017-07-26**
  - [X] ~~Main task #5~~ **DONE: 2017-07-26**
  - [x] ~~Main task #6~~ **DONE: 2017-08-01**
  - [x] ~~Main task #7~~ **DONE: 2017-07-27**
  - [x] ~~Main task #8~~ **DONE: 2017-07-27**
- [ ] Separate logics
- [ ] Ask for code review on [Code Review](http://codereview.stackexchange.com/) & [4programmers](https://4programmers.net/Forum/C_i_C++/) & [wykop](http://wykop.pl/tag/cpp/)
- [ ] Optional tasks:  
  - [ ] Optional task #1 (real-time)
  - [ ] Optional task #2 (rabbit cull)
  - [ ] Optional task #3 (80x80 grid)
  - [ ] Optional task #4 (saving & playback)
- [ ] Ask for code review on [Code Review](http://codereview.stackexchange.com/) & [4programmers](https://4programmers.net/Forum/C_i_C++/) & [wykop](http://wykop.pl/tag/cpp/)
- [ ] Create C++11/C++14 version (if not already)
- [ ] Ask for code review on [Code Review](http://codereview.stackexchange.com/) & [4programmers](https://4programmers.net/Forum/C_i_C++/) & [wykop](http://wykop.pl/tag/cpp/)
- [ ] Die

---

### Useful links:
* [Other beginner excercises (including this one)](http://www.cplusplus.com/forum/articles/12974/) (cplusplus.com)
* [Implementation](http://www.cplusplus.com/forum/beginner/92473/) (cplusplus.com)
* [Implementation review](http://codereview.stackexchange.com/questions/20407/linked-list-of-bunny-objects) (codereview.stackexchange.com)
* [Markdown Cheatsheet](https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet) & [Mastering Markdown](https://guides.github.com/features/mastering-markdown/)
