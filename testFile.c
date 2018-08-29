// I need to remember to delete this, I am just testing stuff

#include "da.h"

int main(void)
{
  DA *someDa = newDA();
  insertDA(someDa, 0, (void*)7);
  displayDA(someDa, stdout);
  insertDA(someDa, 2, (void*)15);
  displayDA(someDa, stdout);
  return 0;
}
