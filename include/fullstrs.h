/*  fullstrs - full strings */
/*
*   Method Prefixes:
*       *"q"    -   quick   (Quick access to execution result)
*       *"l"    -   long    (Long access to execution result)
*/

# ifndef BOTTOM_FULLSTRS
# define BOTTOM_FULLSTRS

int lbufferadder(char* buffer, int count, ...);
char* qlastchars(char* src, char delimiter);

# endif