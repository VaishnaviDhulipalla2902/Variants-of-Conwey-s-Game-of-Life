#include "Maze.h"

Maze::Maze(int x, int y):Mazectric(x,y){}

Maze::Maze(std::string filename):Mazectric(filename){}

Maze::~Maze(){}

int Maze::generate_next_state(){
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
                if(count < 1){
                    grid[i][j] = 0;
                }
                else if(count > 5){
                    grid[i][j] = 0;
                }
                else{
                    grid[i][j] = 1;
                }
            }
            else{
                if(count == 3){
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