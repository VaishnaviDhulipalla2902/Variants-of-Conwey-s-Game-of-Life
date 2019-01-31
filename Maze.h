#ifndef Maze_H_
#define Maze_H_

#include <iostream>
#include "Mazectric.h"

class Maze : public Mazectric{

    public:
        // Constructors //
        Maze();
        Maze(int x, int y);
        Maze(std::string filename);
        ~Maze();
        Maze(const Maze&);

        Maze& operator=(const Maze&);
        
        // Public functions //
        int generate_next_state();        
        
};

#endif