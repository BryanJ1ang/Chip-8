#include "memory.h"
#include "registers.h"

#include <iostream>
#include <stack>

class Chip_8 {

    public:
        Memory memory;
        Registers registers;
        std::stack<uint8_t> stack;


};