#include <iostream>
#include "classes.hpp"
#include "run.hpp"

int main (){
    int moves = runGame();
    std::cout << "You won in " << moves << " moves\n";
    return 0;
}
