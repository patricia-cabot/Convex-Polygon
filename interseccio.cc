#include <iostream>
#include <vector>
#include <algorithm>
#include "Polygon_hh"
using namespace std;

void line_equation ( const Point& p1, const Point& p2, double& m, double& n){
  m = (p2.get_y() - p1.get_y()) / (p2.get_x() - p1.get_x());
  n = p1.get_y() - p1.get_x()*m;
}

double maximum (const double a, const double b, const double c, const double d){
  double m = max(a,b);
  m = max(m,c);
  m = max(m,d);
  return m;
}

double minimum (const double a, const double b, const double c, const double d){
  double m = min(a,b);
  m = min(m,c);
  m = min(m,d);
  return m;
}

Point interseccio (const Point& p1, const Point& p2, const Point& q1, const Point& q2){
  Point inter = Point(1000,1000);
  double m1, n1, m2, n2, x_coor, y_coor;
  if (p2.get_x() == p1.get_x() and q2.get_x() == q1.get_x()){   /** Both are parallels in the Y axis */
    return inter;
  } else if (p2.get_x() == p1.get_x()){   /** the first is parallel to the Y axis */
    line_equation(q1,q2,m2,n2);
    print(2,m2,n2);
    x_coor = p1.get_x();
    y_coor = m2*x_coor+n2;

  } else if (q2.get_x() == q1.get_x()){   /** the second is parallel to the Y axis */
    line_equation(p1,p2,m1,n1);
    print(1,m1,n1);
    x_coor = q1.get_x();
    y_coor = m1*x_coor+n1;

  } else {
    /** First we compute the line equations of each pair of vertices of both polygons */
    line_equation(p1,p2,m1,n1); line_equation(q1,q2,m2,n2);
    print(1,m1,n1); print(2,m2,n2);
    x_coor = (n2 - n1)/(m1 - m2);
    y_coor = m1*x_coor+n1;

  }
    /** We check that the coordinates X and Y are inside the segments of the points */
    double xl = minimum( p1.get_x(), p2.get_x(), q1.get_x(), q2.get_x() );
    double yl = minimum( p1.get_y(), p2.get_y(), q1.get_y(), q2.get_y() );
    double xr = maximum( p1.get_x(), p2.get_x(), q1.get_x(), q2.get_x() );
    double yu = maximum( p1.get_y(), p2.get_y(), q1.get_y(), q2.get_y() );
    if ( xl<=x_coor and x_coor<=xr and yl<=y_coor and y_coor<=yu ) inter = Point(x_coor, y_coor);
    return inter;
}

int main(){
  double x,y;
  cin>>x>>y;Point a = Point(x,y);
  cin>>x>>y; Point b = Point(x,y);
  cin>>x>>y; Point c = Point(x,y);
  cin>>x>>y; Point d = Point(x,y);
  Point inter = interseccio(a,b,c,d);
  if (inter.get_x()==1000 and inter.get_y()==1000) cout << "no intersection" << endl;
  else cout << "Inter: " << inter.get_x() << " , " << inter.get_y() << endl;
}
