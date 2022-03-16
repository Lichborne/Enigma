# Enigma
Enigma Machine developed according to the task set out by Imperial College London. The formulation of this task is found in the spec* pdf file.

### Usage:

The correct usage is in the following format

  ./enigma plugboard-file reflector-file (<rotor-file>)* rotor-positions
  
  e.g:
  
  ./enigma plugboards/I.pb reflectors/I.rf rotors/I.rot rotors/I.pos
 
 The files are found in the folders named after the component to which they relate. They must be both well-formed and compatible. If the need arises, please consult the spec* pdf file.
 
  ### Notes
  
  The repository includes the compiled program. Developed under g++ (Ubuntu 9.4.0-1ubuntu1~20.04) 9.4.0. Suggested platforms are Linux (wsl is perfect as well) or MacOs. May not run on cygwin.
  
  ### Possible improvements
  
  It would be a good idea to replace self-managed parsing based on expectatios formulated on the basis of existing files and the exercise with one that handles edge cases better (i.e. using existing library functions such as >>).
  
  Cable class is slightly extraneous; it is not a useful abstraction, only a conceptually convenient one; should be replaced by direct operations.
