// README

All source code files in this project adhere to the GNU coding standards.

To Build from command line:
--------------------------
1. cd to the directory where you want the project clone to reside
2. git clone https://github.com/jpm5830/lm962_C.git (will create dir lm962_C under current directory)
3. cd lm962_C
4. cmake -S . -B .
5. make

TODO:

1. Use better RNG or different seed value
2. Make N_ACTIVE_PAYLINES a global variable
3. Add detailed documentation