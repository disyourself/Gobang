# Gobang
Rough game on windows implented by Easyx library.

## step to test
````
mkdir build && cd build
cmake .. -G "Unix Makefiles"
./bin/gobang.exe
````


## Todo & known Bugs

1. The algorithem to calculate the position weight of AI. 
   Located in ./src/AI.cpp :  void AI::calculateScore(){...}  
<br>

2. The algoritem to check win conditions in the direction of backslash "\\" & forwar slash "/".
   located in ./src/chess.cpp : bool Chess::checkWin (){...}
<br>

3. Only input 'q' on terminal could exit game. 