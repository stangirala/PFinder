 /*
 * Temp test file for quick testing.
 */

#include "utils.h"

#include <iostream>

using namespace std;

int main() {

  class point a, b, c;

  a.x = 2; a.y = 4;
  b.x = 1; b.y = 2;

  cout << "a - b : "; a.print (a - b);
  cout << "a + b : "; a.print (a + b);
  cout << "a - b : "; a.print (a - b);

  c = a - b;
  cout << "Stored value for a - b : ( " << c.x << ", " << c.y << ")" << endl << endl;


  cout << "Prod: " << a * b << endl;
  a==b?cout<<"eql yes\n\n":cout<<"eql no\n\n";


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
  /*point.x = 1;
  point.y = 1.5;

  inRect(rectangle, point)?cout<<"yes\n":cout<<"no\n";

  point.x = 15;
  point.y = 12;

  inRect(rectangle, point)?cout<<"yes\n":cout<<"no\n";


  point.x = 1;
  point.y = 0;

  inRect(rectangle, point)?cout<<"yes\n":cout<<"no\n";*/

  point.x = -1;
  point.y = 0;

  inRect(rectangle, point)?cout<<"yes\n":cout<<"no\n";

  point.x = -1;
  point.y = -1.5;

  inRect(rectangle, point)?cout<<"yes\n":cout<<"no\n";


  return 0;
}
