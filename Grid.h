#ifndef Grid_H_
#define Grid_H_

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "GridCell.h"

class Grid{

    public:
        // Constructor //
        Grid(int x, int y);
        // Construct using a file //     
        Grid(std::string filename);
        // Destructor //
        ~Grid();
        // Copy constructor //
        Grid(const Grid&);

        Grid& operator=(const Grid&);

        // Friend function //
        friend std::ostream& operator<< (std::ostream &, Grid &) ;

        // Set function //
        void set_state_of_cell(int x, int y, unsigned char state);

        // Get functions //
        GridCell** getGrid(){
            return gridcells;
        }
        int get_rows(){
            return X;
        }
        int get_columns(){
            return Y;
        }

        // Public Funcions //
        void generate_initial_state();
        void update_neighborhood();
        int generate_next_state();
        int count_live_neighbors(int x, int y);
        void print_grid();
        int sum_of_live_neighbors();
        int check_validity();

    protected:
        // Data members //
        int X, Y, L;
        GridCell ** gridcells;

};

#endif