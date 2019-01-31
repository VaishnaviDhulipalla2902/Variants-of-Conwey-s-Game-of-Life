#include "HighLife.h"

HighLife::HighLife(int x, int y):Grid(x,y){}

HighLife::HighLife(std::string filename):Grid(filename){}

HighLife::~HighLife(){}

int HighLife::generate_next_state(){
    Grid proxy(*this);
    int** grid = new int*[X];
    for(int i = 0; i < X; i++)
        grid[i] = new int[Y];

    for(int i = 0; i < X; i++){
        for(int j = 0; j < Y; j++){
            grid[i][j] = 0;
        }
    }

    for(int i = 0; i < X; i++){
        for(int j = 0; j < Y; j++){
            int count = count_live_neighbors(i,j);  
            if(gridcells[i][j].getState()){                
                if(count < 2){
                    grid[i][j] = 0;
                }
                else if(count > 3){
                    grid[i][j] = 0;
                }
                else{
                    grid[i][j] = 1;
                }
            }
            else{
                if(count == 3 || count == 6){
                    grid[i][j] = 1;
                }
            }
        }
    }
    for(int i = 0; i < X; i++){
        for(int j = 0; j < Y; j++){
            if(grid[i][j]){
                proxy.set_state_of_cell(i,j,1);
            }
            else{
                proxy.set_state_of_cell(i,j,0);
            }
        }
    }
    int flag = proxy.check_validity();
    proxy.~Grid();
    if(flag == 0){
        return 2;        
    }
    else{
        for(int i = 0; i < X; i++){
            for(int j = 0; j < Y; j++){
                if(grid[i][j]){
                    gridcells[i][j].setState(1);
                }
                else{
                    gridcells[i][j].setState(0);
                }
            }
        }
        update_neighborhood();
    }
    return flag;
}