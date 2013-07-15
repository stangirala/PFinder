 /*
 * Temp test file for quick testing.
 */

#include "utils.h"

#include <iostream>

using namespace std;

int main() {

  class point a, b, c, point;

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

  cout << "Rectangle is" << endl;
  point.print(rectangle.points[0]);
  point.print(rectangle.points[1]);
  point.print(rectangle.points[2]);
  point.print(rectangle.points[3]);
  cout << endl;


  cout << "inRect Tests" << endl;

  point.x = 1;
  point.y = 1.5;
  point.print(point);

  inRect(rectangle, point)?cout<<"yes\n\n":cout<<"no\n\n";

  point.x = 3;
  point.y = 3;
  point.print(point);

  inRect(rectangle, point)?cout<<"yes\n\n":cout<<"no\n\n";

  point.x = 15;
  point.y = 12;
  point.print(point);

  inRect(rectangle, point)?cout<<"yes\n\n":cout<<"no\n\n";


  point.x = 1;
  point.y = 0;
  point.print(point);

  inRect(rectangle, point)?cout<<"yes\n\n":cout<<"no\n\n";

  point.x = -1;
  point.y = 0;
  point.print(point);

  inRect(rectangle, point)?cout<<"yes\n\n":cout<<"no\n\n";

  point.x = -15;
  point.y = 0;
  point.print(point);

  inRect(rectangle, point)?cout<<"yes\n\n":cout<<"no\n\n";

  point.x = -1;
  point.y = -1.5;
  point.print(point);

  inRect(rectangle, point)?cout<<"yes\n\n":cout<<"no\n\n";


  return 0;
}
