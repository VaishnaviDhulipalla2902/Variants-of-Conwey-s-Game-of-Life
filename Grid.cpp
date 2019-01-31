#include "Grid.h"

Grid::Grid(int x, int y){
    X = x;
    Y = y;
    gridcells = new GridCell*[x];
    for(int i = 0; i < x; i++)
        gridcells[i] = new GridCell[y];
}

Grid::~Grid(){
    for(int i = 0; i < X; i++)
        delete[] gridcells[i];
    // delete[] gridcells;

    X = 0;
    Y = 0;
}

Grid::Grid(const Grid& G){
    X = G.X;
    Y = G.Y;
    gridcells = new GridCell*[X];
    for(int i = 0; i < X; i++)
        gridcells[i] = new GridCell[Y];

    for(int i = 0; i < X; i++){
        for(int j = 0; j < Y; j++){
            gridcells[i][j] = G.gridcells[i][j];
        }
    }
        
}

Grid& Grid::operator=(const Grid& G){
    X = G.X;
    Y = G.Y;
    gridcells = new GridCell*[X];
    for(int i = 0; i < X; i++)
        gridcells[i] = new GridCell[Y];

    for(int i = 0; i < X; i++){
        for(int j = 0; j < Y; j++){
            gridcells[i][j] = G.gridcells[i][j];
        }
    }
    return (*this);
}

void Grid::set_state_of_cell(int x, int y, unsigned char state){
    gridcells[x][y].setState(state);
}

// GridCell** Grid::getGrid(){
//     return gridcells;
// }

// int Grid::get_rows(){
//     return X;
// }

// int Grid::get_columns(){
//     return Y;
// }

Grid::Grid(std::string filename){
    std::string token;
    std::ifstream grid_file (filename);
    if (grid_file.is_open()){
        grid_file >> token;
        int rows = stoi(token);
        grid_file >> token;
        int columns = stoi(token);
        grid_file >> token;
        int generation = stoi(token);
        if (generation != 0) return;
        else{
            X = rows;
            Y = columns;
            gridcells = new GridCell*[rows];
            for(int i = 0; i < rows; i++)
                gridcells[i] = new GridCell[columns];
            for(int i = 0; i < rows; i++){
                for(int j = 0; j < columns; j++){
                    grid_file >> token;
                    if(token == "+"){
                        gridcells[i][j].setState(1);
                    }
                    else if(token == "o"){
                        gridcells[i][j].setState(0);
                    }
                }
            }
            grid_file >> token;
            if((*this).check_validity()){
                if(token == "eof"){
                    (*this).update_neighborhood();
                }
                else{
                    X = 0;
                    return;
                }
            }
            else{
                return;
            }
        }
        grid_file.close();
    }
    else std::cout << "Offo....Unable to open the given file!!"; 
}

void Grid::generate_initial_state(){
    srand(time(0));
    int count = 0;

    for(int i = 0; i < X; i++){
        for(int j = 0; j < Y; j++){
            GridCell c(i,j);
            gridcells[i][j] = c;
            if(i != 0 && i != X-1 && j != 0 && j != Y-1){
                if(count <= L){
                    gridcells[i][j].setState(rand()%2);
                    if(gridcells[i][j].getState()) count++;
                }
            }
            else{
                gridcells[i][j].setState(0);
            }
            for(int k = 0; k < 8; k++){
                gridcells[i][j].setNeighborhood(0,k);
            }
        }
    }
}

void Grid::update_neighborhood(){
    for(int i = 0; i < X; i++){
        for(int j = 0; j < Y; j++){
            for(int k = 0; k < 8; k++){
                gridcells[i][j].setNeighborhood(0,k);
            }
            if(j+1 < Y) {
                if(gridcells[i][j+1].getState()) gridcells[i][j].setNeighborhood(1,0);
            }
            if(j-1 > -1) {
                if(gridcells[i][j-1].getState()) gridcells[i][j].setNeighborhood(1,4);
            }
            if(i+1 < X){
                if(gridcells[i+1][j].getState()) gridcells[i][j].setNeighborhood(1,6);
                if(j+1 < Y) {
                    if(gridcells[i+1][j+1].getState()) gridcells[i][j].setNeighborhood(1,7);
                }
                if(j-1 > -1) {
                    if(gridcells[i+1][j-1].getState()) gridcells[i][j].setNeighborhood(1,5);
                }
            }
            if(i-1 > -1){
                if(gridcells[i-1][j].getState()) gridcells[i][j].setNeighborhood(1,2);
                if(j+1 < Y) {
                    if(gridcells[i-1][j+1].getState()) gridcells[i][j].setNeighborhood(1,1);
                }
                if(j-1 > -1) {
                    if(gridcells[i-1][j-1].getState()) gridcells[i][j].setNeighborhood(1,3);
                }
            }
        }
    }

}

int Grid::generate_next_state(){
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

int Grid::count_live_neighbors(int x, int y){
    int count = 0;
    for(int i = 0; i < 8; i++){
        if(gridcells[x][y].getNeighbor(i)) count++;
    }
    return count;
}

void Grid::print_grid(){
    for(int i = 0; i < X; i++){
        for(int j = 0; j < Y; j++){
            if(gridcells[i][j].getState()){
                printf("+ ");
            }
            else{
                printf("o ");
            }
        }
        printf("\n");
    }
}

int Grid::sum_of_live_neighbors(){
    int total = 0;
    for(int i = 0; i < X; i++){
        for(int j = 0; j < Y; j++){
            total += count_live_neighbors(i,j);
        }
    }
    return total;
}

std::ostream& operator<<(std::ostream& os, Grid& G) {
  
    for (int i = 0; i < G.X; i++) {
        for (int j = 0; j < G.Y; j++) {
            if(G.gridcells[i][j].getState()){
                os << "+ " ;
            }
            else{
                os << "o " ;
            }
        }
        os << std::endl;
    }
    return os;
}

int Grid::check_validity(){
    if((X == 1 && Y == 3) || X == 0 || Y == 0) return 0;

    for(int i = 0; i < Y; i++){
        if(gridcells[0][i].getState()) return 0;
    }

    for(int i = 0; i < Y; i++){
        if(gridcells[X-1][i].getState()) return 0;
    }

    for(int i = 0; i < X; i++){
        if(gridcells[i][0].getState()) return 0;
    }

    for(int i = 0; i < X; i++){
        if(gridcells[i][Y-1].getState()) return 0;
    }

    return 1;
}
