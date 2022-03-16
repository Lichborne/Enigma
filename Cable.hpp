#ifndef CABLE_H
#define CABLE_H

//Class to represent a single cable or wire connecting 2 letters
class Cable {
    private: 
        int Node_1 = 0;
        int Node_2 = 0;

    public:
        // Getters
        int get_Node_1();
        int get_Node_2();

        // Default Constructor
        Cable(); 

        // Constructor
        Cable(int node_1, int node_2);
    
        // To see of a particular cable has a connection to a given 
        // letter-number. True if yes, false if no.
        bool Cable_connected(int letter_num);

        // Swap the input value with the one it connects to
        int Cable_swap(int letter_num);
};
#endif