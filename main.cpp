#include<iostream>
#include<fstream>
#include<string>
#include<cctype>
#include<cstdlib>
#include<iomanip>
#include<algorithm>
#include<vector>
#include"Enigma.hpp"
#include"Errors.hpp"

// SEE COMMENTS ON OVERALL DESIGN CHOICES BELOW MAIN FUNCTION

// NOTE:
// Header files typically comment on what does what,
// .cpp files comment on why and how it does that,
// if and when it seems necessary.

int main(int argc, char** argv) {
    try {

        // Create the enigma machine.
        Enigma machine = Enigma(argc, argv);

        // Use the machine until end of input or exit for some error.
        machine.Use_Machine();

    // Catch throw if any
    } catch (int error) {
          return error;
    }
    // return No Error if none found.
    return NO_ERROR;
}

// COMMENTS ON DESIGN CHOICES: 


// IO AND ERROR NAMESPACES:

// The most pressing question: why the IO and Error namespaces? 
// Mainly, there would have been a lot of duplicate code between 
// classes if I had done everything separately; this way, there is
// very little of that. Secondly, this way, all that is left in classes are
// the functions that describe how they work, so it is much easier to read
// and understand what the components do, and how. As to why they are name-
// spaces; they could have been simple modules, but I thought this was a 
// slightly more appropriate given their use (originally, I made them classes,
// but that seemed to be a little strange as they only contain functions). 
// As you can see, I also decided against any 'using' directives, opting 
// instead to be explicit in what I am using and when.

// ON VECTORS:

// Why vectors for everything? Three reasons. Firstly, vectors have methods pre-
// defined that make several things simpler and more elegant to implement and 
// also to interpret. Secondly, Plugboards and Reflectors become essentially 
// the same thing, so code that would have had to be written twice only 
// slightly differently now has to be written only once. Moreover, this way, by 
// changing only the constants and the console readin function's character 
// constraints, we can have components that use up to the entire set of ASCII
// characters with correct functionality. I think that is worth the tradeoff
// of having to allocate slightly more memory to objects.


// ERROR HANDLING:

// Originally, I was passing an int error by reference to all subfunctions
// and exiting on the event that it is modified. This was tedious and very
// ugly, so I opted instead for throw and catch; which we haven't learnt yet,
// but is quite universally used so I though I would do so as well.


// MEMORY:

// There appears to be absolutely no need for dynamic memory allocation in my
// implementation of this exercise. Also, since we return to main no matter 
// what, everything gets appropriately deconstructed one by one. Ownership
// structure is very clear:Enigma (Plugboard(Cables), Reflector(Cables), Rotors)

// Notice that I have both a constructor I define and a default constructor for 
// all classes. Since I do define another constructor, this is needed in order
// to have a default Rotor object if at any point one is needed, for any 
// reason, (even if simply as a stand-in). Notice, however, that there are 
// never any  setters; objects can only modify themselves through the operations
// needed to make the enigma machine work; so default, empty objects will always
// remain so.

// The default destructors the compiler generates should be adequate for all of
// the classes (compiler knows how to destruct std::vector and ints whcih is
// all I use), and if I defined my own destructor, move/copy constructorsand 
// assignments could no longer be deduced by the compiler, so I would have to 
// do those as well

// ON NAMING: 
        // Classes: their members and menthods are all capitalized snake case
            // in order to clearly separate namsepaces and classes in code.

        // Namespaces: namspace capitalized snake case, member functions
            // normal snake case, too separate clearly from classes. 
                // No 'using' directives, always specified explicitly.
