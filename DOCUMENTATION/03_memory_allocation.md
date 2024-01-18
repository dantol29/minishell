
### 3.      MEMORY ALLOCATION
```
9. malloc;       // Allocate memory dynamically.
10. free;       // Deallocate previously allocated memory.
```
_______________________________________________
### _MALLOC_
```
#include <stdlib.h>

void *malloc(size_t size);
```
 - Allocates size bytes and returns a pointer to the allocated memory
 
**Return Value:**
- Success: a pointer to the allocated memory
- Error: NULL
____________________________________
### _FREE_
```
#include <stdlib.h>

void free(void *ptr);
```
 - frees the memory space pointed to by ptr
 
**Return Value:**
- Success: void
- Error: void
