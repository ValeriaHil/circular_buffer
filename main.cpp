#include <iostream>
#include "circular_buffer.h"

int main() {
    circ_buff<int> buff;
    for (int i = 1; i <= 4; i++) {
        buff.push_back(i);
    }
    for(int i = 5; i <= 100; i++) {
        buff.push_front(i);

        buff.erase(buff.end() - 2);
    }

    for (auto x : buff) {
        std::cout << x << std::endl;
    }

    return 0;
}