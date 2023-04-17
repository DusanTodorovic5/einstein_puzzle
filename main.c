#include "defs.h"

int main(int, char**) {
   concepts* m_concepts;
   load_from_file("test_file.txt", &m_concepts);

   return 0;
}
