
#include <iostream>
#include <cmath>

int main() {
    size_t input;
    std::cin >> input;

    /* looking for the size of the biggest complete square inside grid
     * it is actually the largest power of 2 of an odd number  */
    size_t size = sqrtf(input);

    if (!(size % 2)) {
        size -= 1;
    }

    // now get the position of the input on the incomplete external square

    auto pos = input - size * size;

    // now taking size of the outer square
    size++;

    // problem is symetric thus the distance to center is the same for edge elements rotated of PI/2
    // this mean that the position can be reduced to the side [0..size-1]
    pos %= size;

    // as the center of the square is the origin of coordinates, and as the
    // edge is symetric (distance from top is the same as distance from bottom), we can reduce the values once more:
    if (pos > size / 2)
        pos -= size / 2;
    else
        pos = size / 2 - pos; 

    // now distance is just of the coordinates of the point:
    // it is on the outer square thus one coordinate is size / 2, the other one is the position on the edge
    std::cout << pos + size / 2 << std::endl;
}
