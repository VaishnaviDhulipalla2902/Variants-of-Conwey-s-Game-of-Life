#include "GridCell.h"

GridCell::GridCell(){
    x = 0;
    y = 0;
    state = 0;
    for(int i = 0; i < 8; i++){
        neighborhood[i] = 0;
    }
}

GridCell::GridCell(int x1, int y1){
    x = x1;
    y = y1;
}

GridCell::~GridCell(){
    x = 0;
    y = 0;
    state = 0;
    for(int i = 0; i < 8; i++){
        neighborhood[i] = 0;
    }

}

GridCell::GridCell(const GridCell& G){
    x = G.x;
    y = G.y;
    state = G.state;
    for(int i = 0; i < 8; i++){
        neighborhood[i] = G.neighborhood[i];
    }    
}

GridCell& GridCell::operator=(const GridCell& G){
    x = G.x;
    y = G.y;
    state = G.state;
    for(int i = 0; i < 8; i++){
        neighborhood[i] = G.neighborhood[i];
    } 
    return (*this);
}

void GridCell::setState(unsigned char s){
    state = s;
}

void GridCell::setNeighborhood(unsigned char s, int n){
    neighborhood[n] = s;
}

// unsigned char GridCell::getState(){
//     return state;
// }

// unsigned char GridCell::getNeighbor(int k){
//     return neighborhood[k];
// }

