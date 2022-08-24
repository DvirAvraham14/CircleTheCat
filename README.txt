OPP – ex4 “Circle the cat”
******************************************************************************
Dvir Avraham	‫*********‬	dviravr
******************************************************************************
Description:
In this exercise a programmable "Circle the cat" - Circle the Cat is a puzzle game where you draw circles around a cat in an attempt to trap it.
It's a player's turn in front of a computer. The player in his turn selects one tile he wants to block by clicking
Mouse on the desired circle. The computer in its turn moves the cat to try to escape obstacles, and to escape
From the board. If the cat reached one side of the board, the cat actually ran away from the board and won the game. If the player succeeded
******************************************************************************
Files:
Header files:
------ a prototype files --------
Animation.h
AnimationData.h
Board.h
Btn.h
Controller.h
Direction.h
macro.h
myCircle.h
Resources.h
theCat.h

CPP files:
Animation.cpp
AnimationData.cpp
Board.cpp
Btn.cpp
Controller.cpp
Direction.cpp
macro.cpp
myCircle.cpp
Resources.cpp
theCat.cpp

******************************************************************************
Main structure that use
------------------------------------
vector	- for save the map.
stack	- for undo moves.


Notable algorithms:
----------------------------
bfs -> To find the fastest path to exit the board
******************************************************************************
Known bug:
When we exit an odd line, the animation action in front of it at the top right will not work properly
******************************************************************************
Additional Comments
******************************************************************************
At the end of a phase,
In case you lose there is an option to create a new stage at the same level, or play the exact same stage.
When winning you can create a stage at the same random level or move on to the next stage.
The game levels are divided into three levels, easy medium and hard.
Easy - 14 blocked lengths.
Medium- 12 blocked lengths.
Hard- 10 blocked lengths.
You can change the degrees of the instincts in the macro.h file