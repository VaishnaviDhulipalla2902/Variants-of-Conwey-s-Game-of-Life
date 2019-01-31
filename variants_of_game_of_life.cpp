#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "GridCell.h"
#include "Grid.h"
#include "HighLife.h"
#include "Mazectric.h"
#include "Maze.h"

using namespace std;

int main(int argc, char **argv){
    ofstream output("output.txt");
    string filename; 
    int gen, temp, type; 
    filename = argv[1];
    gen = atoi(argv[2]);
    type = atoi(argv[3]);
    temp = gen;
    if(type == 1){
        HighLife h(filename);
        int flag = h.check_validity();
        while(flag == 1 && temp--){
            cout << h << endl;
            flag = h.generate_next_state();
        }
        if(output.is_open()){
            if(flag == 1 || flag == 2){
                output << h.get_rows() << " ";
                output << h.get_columns() << " ";
                output << gen-temp-1 << endl;
                output << h;
                output << "eof" << endl;
            }
            else{
                output << "0 0 0" << endl;
                output << "eof" << endl;
            }
            output.close();
        }
    }
    else if (type == 2){
        Mazectric h(filename);
        int flag = h.check_validity();
        while(flag == 1 && temp--){
            cout << h << endl;
            flag = h.generate_next_state();
        }
        if(output.is_open()){
            if(flag == 1 || flag == 2){
                output << h.get_rows() << " ";
                output << h.get_columns() << " ";
                output << gen-temp-1 << endl;
                output << h;
                output << "eof" << endl;
            }
            else{
                output << "0 0 0" << endl;
                output << "eof" << endl;
            }
            output.close();
        }
    }
    else if (type == 3){
        Maze h(filename);
        int flag = h.check_validity();
        while(flag == 1 && temp--){
            cout << h << endl;
            flag = h.generate_next_state();
        }
        if(output.is_open()){
            if(flag == 1 || flag == 2){
                output << h.get_rows() << " ";
                output << h.get_columns() << " ";
                output << gen-temp-1 << endl;
                output << h;
                output << "eof" << endl;
            }
            else{
                output << "0 0 0" << endl;
                output << "eof" << endl;
            }
            output.close();
        }
    }
    else cout << "Offo...Unable to open the given file!!";
    return 0;
}