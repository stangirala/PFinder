 /*
 * Temp test file for quick testing.
 */

#include "utils.h"
#include "utils.cpp"

#include <iostream>
#include <Eigen/Dense>
#include <cv.h>

using namespace std;
using namespace Eigen;
using namespace cv;

int main() {

  int i, j;
  class point a, b, c, point;

  /*a.x = 2; a.y = 4;
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

  inRect(rectangle, point)?cout<<"yes\n\n":cout<<"no\n\n";*/


  /*Matrix<float, Dynamic, Dynamic> areamat;
  Matrix<float, 1, 4> rect;
  rect << 0.0, 0.0, 2.0, 3.0;

  cout << "Rect" << rect << endl;

  cout << endl << "alignedRectInt Test" << endl;
  alignedRectInt(rect, rect, areamat);
  cout << "Rows " << areamat.rows() << " Cols " << areamat.cols() << endl;
  cout << "Areamat" << endl << areamat << endl;*/

  /*Matrix<double, Dynamic, Dynamic> areamat;
  Matrix<double, 2, 4> rect;
  rect << 308.498687744141, 301.4560546875, 106.437408447266, 240.276611328125,
       810.169372558594, 329.236206054688, 106.490905761719, 253.474853515625;

  cout << "Rect" << rect << endl;

  cout << endl << "alignedRectInt Test" << endl;
  alignedRectInt(rect, rect, areamat);
  cout << "Rows " << areamat.rows() << " Cols " << areamat.cols() << endl;
  cout << "Areamat" << endl << areamat << endl;*/

  class cvMatAt t("/home/vtangira/Downloads/20120920_the-police-ghost-in-the-machine_33.jpg");
  cout << t.At(20, 21, 2) << endl;

  return 0;
}
