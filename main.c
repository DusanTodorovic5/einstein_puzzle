#include "defs.h"

int main(int, char**) {
   concepts* m_concepts;
   load_file(&m_concepts, "test_file.txt");

   for (int i=0;i<m_concepts->number_of_groups;i++) {
      for (int j=0;j<m_concepts->number_of_concepts;j++) {
         printf("%s ", m_concepts->concepts[i][j]);
      }
      printf("\n");
   }

   printf("\n");

   node* tree = populate(m_concepts);
   print(tree, m_concepts, HORIZONTAL);
   printf("\n\nkraj\n\n");

   cleanup_concepts(m_concepts);
   free(m_concepts);
   
   cleanup_tree(tree);

   return 0;
}
