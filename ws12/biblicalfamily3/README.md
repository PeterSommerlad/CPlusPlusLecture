This directory contains code demonstrating using shared_ptr 
for implementing object relationships.

This is the third step, showing the suboptimal use of shared_ptr for
cyclic relationships. Specific code needs to be called to break the 
cycles when one want to get rid of an object.

NB: there are three more versions demonstrating modifications
when cyclic relationships, e.g., between parents and children 
in a family, are represented.