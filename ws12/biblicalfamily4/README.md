This directory contains code demonstrating using shared_ptr 
for implementing object relationships.

This is the fourth step, showing the  use of shared_ptr in 
combination with weak_ptr and enable_shared_from_this for
cyclic relationships. This mechanism allows cyclic object
relationships that can be released automatically with the 
drawback that one direction is "weak" requiring one to first 
check the pointer validity after converting it to a shared_ptr.

NB: there are three more versions demonstrating modifications
when cyclic relationships, e.g., between parents and children 
in a family, are represented.