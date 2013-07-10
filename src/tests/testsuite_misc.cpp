 /*
 * Temp test file for quick testing.
 */

#include "utils.h"

int main() {

  class point a, b;

  a.x = 0; a.y = 0;
  b.x = 1; b.y = 2;

  a.print (a - b);
  a.print (a + b);

  return 0;
}
