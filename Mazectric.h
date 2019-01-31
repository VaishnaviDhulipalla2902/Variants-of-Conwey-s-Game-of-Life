#ifndef Mazectric_H_
#define Mazectric_H_

#include <iostream>
#include "Grid.h"

class Mazectric : public Grid{

    public:
        // Constructors //
        Mazectric();
        Mazectric(int x, int y);
        Mazectric(std::string filename);
        ~Mazectric();
        Mazectric(const Mazectric&);

        Mazectric& operator=(const Mazectric&);
        
        // Public functions //
        int generate_next_state();        
        
};

#endif