#include"Cable.hpp"

//===========================================================================

int Cable::get_Node_1() {
    return Node_1;
}
//===========================================================================

int Cable::get_Node_2() {
    return Node_2;
}

//===========================================================================

// See comments in main.cpp for why this is good to have
Cable::Cable() {}

//===========================================================================

Cable::Cable(int node_1, int node_2) {
    Node_1 = node_1;
    Node_2 = node_2;
}

//===========================================================================

// Not absolutely necessary (Cable_swap would be enough on its own), but 
// provides easy break condition to cut short loop for checking whether a 
// plugboard has cables connected to a letter.
bool Cable::Cable_connected(int letter_num) {

    if (Cable::get_Node_1() == letter_num)
        return 1;

    if (Cable::get_Node_2() == letter_num)
        return 1;
        
    return 0; 
}

//===========================================================================

int Cable::Cable_swap(int letter_num) {

    if (Cable::get_Node_1() == letter_num)
        return Cable::get_Node_2();

    if (Cable::get_Node_2() == letter_num)
        return Cable::get_Node_1();
    
    return letter_num;
}

//===========================================================================

