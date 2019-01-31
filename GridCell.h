#ifndef GridCell_H_
#define GridCell_H_

#include <iostream>

class GridCell{

    public:
        // Constructors //
        GridCell();
        GridCell(int x1, int y1);
        // Destructor //
        ~GridCell();
        // Copy constructor //
        GridCell(const GridCell&);

        GridCell& operator=(const GridCell&);

        // Set functions //
        void setState(unsigned char s);
        void setNeighborhood(unsigned char s, int n);

        // Get functions //
        unsigned char getState(){
            return state;
        }
        unsigned char getNeighbor(int k){
            return neighborhood[k];
        }
        
    protected:
        // Data members //
        int x, y;
        unsigned char state;
        unsigned char neighborhood[8];
};

#endif