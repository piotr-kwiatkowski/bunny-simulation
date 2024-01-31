C++ implementation of [this](http://www.cplusplus.com/forum/articles/12974) exercise as a starting point with some additional simple visual stuff.

---

# Bunny Simulation

Write a program that creates a linked list of bunny objects.

#### Each bunny object must have:

- Sex: male, female (random at creation, 50/50 chance)
- Color: white, brown, black, spotted
- Age: 0-10 (years old)
- Radioactive mutant vampire bunny: true/false (occurrence possibility: 2%)

## Main tasks:

1. ✅ At program initialization 5 bunnies must be created and given random colors
1. ✅ Each turn afterwards the bunnies age 1 year
1. ❓ So long as there is at least one male age 2 or older, for each female bunny in the list age 2 or older a new bunny is created each turn (i.e. if there was 1 adult male and 3 adult female bunnies, three new bunnies would be born each turn).
1. ✅ New bunnies born should be the same color as their mother
1. ✅ If a bunny becomes older than 10 years old, it dies
1. ✅ If a radioactive mutant vampire bunny is born then each turn it will change exactly one non radioactive bunny into a radioactive vampire bunny (if there are two radioactive mutant vampire bunnies two bunnies will be changed each turn and so on)
1. ✅ Radioactive vampire bunnies are excluded from regular breeding and do not count as adult bunnies
1. ✅ Radioactive vampire bunnies do not die until they reach age 50

#### Also:

- ❌ The program should print a list of all the bunnies in the colony each turn along with all the bunnies details, sorted by age
- ❌ The program should also output each turns events such as:
  _Bunny Thumper was born!_
  _Bunny Fufu was born!_
  _Radioactive Mutant Vampire Bunny Darth Maul was born!_
  _Bunny Julius Caesar died!_
- ❌ The program should write all screen output to a file
- ✅ When all the bunnies have died the program terminates
- ❌ If the bunny population exceeds 1000 a food shortage must occur killing exactly half of the bunnies (randomly chosen)

## Optional tasks:

★ Real time:
Modify the program to run in real time, with each turn lasting 2 seconds, and a one second pause between each announement.

★★ Rabbit cull:
Allow the user to hit the 'k' key to initiate a mass rabit cull! which causes half of all the rabits to be killed (randomly chosen).

★★★★ 80x80 grid:
Modify the program to place the rabbits in an 80x80 grid. Have the rabbits move one space each turn randomly. Mark juvenile males with m, adult males with M, juvenile females with f, adult females with F, and radioactive mutant vampire bunnies with X.
Modify the program so that radioactive mutant vampire bunnies only convert bunnies that end a turn on an adjacent square.
Modify the program so that new babies are born in an empty random adjacent square next to the mother bunny (if no empty square exists then the baby bunny isn't born).

★★★★★ playback:
Modify the program so that it saves each turn to a file and can play back at accelerated speed for all subsequent turns.

---

# _TODO list:_

- Ask for code review on [Code Review](http://codereview.stackexchange.com) & [4programmers](https://4programmers.net/Forum/C_i_C++)
- Read [this](http://www.cplusplus.com/forum/articles/28558) again so you remember not to create game in a console window, you idiot

---

### Useful links:

- [Other beginner excercises](http://www.cplusplus.com/forum/articles/12974) (cplusplus.com)
- [Implementation](http://www.cplusplus.com/forum/beginner/92473) (cplusplus.com)
- [Implementation review](http://codereview.stackexchange.com/questions/20407/linked-list-of-bunny-objects) (codereview.stackexchange.com)
- [Markdown Cheatsheet](https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet) & [Mastering Markdown](https://guides.github.com/features/mastering-markdown)
