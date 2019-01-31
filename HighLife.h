#ifndef HighLife_H_
#define HighLife_H_

#include <iostream>
#include "Grid.h"

class HighLife : public Grid{

    public:
        // Constructors //
        HighLife();
        HighLife(int x, int y);
        HighLife(std::string filename);
        ~HighLife();        
        HighLife(const HighLife&);

        HighLife& operator=(const HighLife&);
        
        // Public functions //
        int generate_next_state();        
   
};

#endif