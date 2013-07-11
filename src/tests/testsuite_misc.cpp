 /*
 * Temp test file for quick testing.
 */

#include "utils.h"

#include <iostream>

using namespace std;

int main() {

  class point a, b;

  a.x = 2; a.y = 4;
  b.x = 1; b.y = 2;

  a.print (a - b);
  a.print (a + b);
  cout << "Prod: " << a * b << endl;
  a==b?cout<<"eql yes\n":cout<<"eql no\n";


  struct rectangle rectangle;
  rectangle.points[3].x = 0;
  rectangle.points[3].y = 0;
  rectangle.points[2].x = 0;
  rectangle.points[2].y = 2;
  rectangle.points[1].x = 3;
  rectangle.points[1].y = 2;
  rectangle.points[0].x = 0;
  rectangle.points[0].y = 3;

  class point point;
  point.x = 1;
  point.y = 1;

  inRect(rectangle, point)?cout<<"rect yes\n":cout<<"rect no\n";


  return 0;
}
