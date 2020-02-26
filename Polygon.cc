#include "Polygon.hh"
#include <cmath>
#include <algorithm>
#include <vector>
#include <iostream>
#include <vector>
#include <algorithm>
//#include <pngwriter.h>
using namespace std;

/** OPERATIONS WITHIN THE CONVEX HULL */

/** Returns the slope of the rect between two points */
double slope (const Point& a, const Point& b){
  return (b.get_y() - a.get_y()) / (b.get_x() - a.get_x());
}

struct Comparador {
  Point ll;
  bool operator() (const Point& p1, const Point& p2) const {
    if (ll.get_x() == p1.get_x() and ll.get_x() == p2.get_x()) return p1.get_y() < p2.get_y();
    if (ll.get_x() == p1.get_x()) return true;
    if (ll.get_x() == p2.get_x()) return false;
    if (slope(ll,p1) == slope(ll,p2)) return p1.get_x() < p2.get_x();
    else return slope(ll,p1) > slope(ll,p2);
  }
};

/** Changes the first Point of the vector v with the left lower-point */
/** Criteria: first we choose the leftest point,  and if some coindice, we choose the one in the bottom. */
void get_LL( vector<Point>& v, int n ){
  int a = 0;
  for (int i=1; i<n; i++){
    if ( v[i].get_x() < v[a].get_x() ) a = i;
    else if ( v[i].get_x() == v[a].get_x() and v[i].get_y() < v[a].get_y()) a = i;
  } if (a!=0) swap (v[0],v[a]);
}

/** This function sorts the vector and puts in the first place the LL point */
vector<Point> changevector ( vector<Point>& v, int n ){
  get_LL(v,n); /** Start with the left-lower point */
  vector<Point> s = {v[0]};
  Comparador comp;
  comp.ll = v[0];
  sort ( v.begin()+1, v.end(), comp );
  /** We check that there are no repeated points */
  for (int i=1; i<n; i++) if(v[i-1]!=v[i]) s.push_back(v[i]);
  return s;
}

/** Determines whether point c is clockwise or counterclockwise in relation with a and b */
/** True: counterclockwise */
bool leftof (const Point& a, const Point& b, const Point& c){
  return (b.get_x() - a.get_x())*(c.get_y() - a.get_y()) >= (b.get_y() - a.get_y())*(c.get_x() - a.get_x());
}

/** Given a set of points, we can calculate the smallest convex polygon that contains the set. */
vector <Point> convex_hull ( const vector<Point>& v ){
  int m = v.size();
  if (m<2) return v;         /** vectors with 0 or 1 element */
  vector<Point> copia = v;
  vector <Point> s = changevector(copia,m);
  int n = s.size();
  if (n<4){
    if ( n==3 and leftof(s[0],s[1],s[2]) ){    /** vectors that form a line with 3 elements*/
      swap(s[1],s[2]); s.pop_back();
    } return s;
  }
  vector <Point> aux(0);
  aux.push_back(s[0]); aux.push_back(s[1]); aux.push_back(s[2]);
  if ( leftof(aux[0],aux[1],aux[2]) ){    /** vectors that form a line with 3 elements*/
    swap(aux[1],aux[2]); aux.pop_back();
  }
  int t = aux.size();
  for ( int i=3; i<n; i++ ){
    /** We remove points from the aux as long as the angle formed by */
    /** aux[i+1], aux[i+2] and v[i] is a left turn (is counterclockwise). */
    while( t>1 and leftof(aux[t-2],aux[t-1],s[i]) ){
      aux.pop_back(); --t;
    }
    aux.push_back(s[i]); t++;  /** We add the next point to the vector */
  }
  return aux;
}

/** CONSTRUCTOR */
/** In the same Constructor we have the convex_hull operation */
Polygon::Polygon ( const vector<Point>& v_, const double& R_col, const double& G_col, const double& B_col )
: v(convex_hull(v_)),
  _R (R_col),
  _G (G_col),
  _B (B_col)
{   }
Polygon::Polygon () {}

// OPERATIONS //

/** Given two points, returns the line equation */
/** The line equation is of the from: Y = m*X + n */
/** In this fuction we compute m and n */
void line_equation ( const Point& p1, const Point& p2, double& m, double& n){
  m = (p2.get_y() - p1.get_y()) / (p2.get_x() - p1.get_x());
  n = p1.get_y() - p1.get_x()*m;
}

/** Returns whether a point is inside the two segments */
bool inside ( const Point& p1, const Point& p2, const Point& q1, const Point& q2, const Point& aux ){
  double px_left = min(p1.get_x(), p2.get_x());
  double px_right = max(p1.get_x(), p2.get_x());
  double py_lower = min(p1.get_y(), p2.get_y());
  double py_higher = max(p1.get_y(), p2.get_y());

  double qx_left = min(q1.get_x(), q2.get_x());
  double qx_right = max(q1.get_x(), q2.get_x());
  double qy_lower = min(q1.get_y(), q2.get_y());
  double qy_higher = max(q1.get_y(), q2.get_y());
  if ( px_left <= aux.get_x() and px_right >= aux.get_x() and py_lower <= aux.get_y() and py_higher >= aux.get_y() and qx_left <= aux.get_x() and qx_right >= aux.get_x() and qy_lower <= aux.get_y() and qy_higher >= aux.get_y() ) return true;
  return false;
}

void vector_intersection (const Point& p1, const Point& p2, const Point& q1, const Point& q2, vector<Point>& inter){
  double m1, n1, m2, n2, x_coor, y_coor;
  bool parallel = false;
  if (p1.get_x() == p2.get_x() and q1.get_x() == q2.get_x() and p1.get_x() != q1.get_x()){
    parallel = true;        /** The lines are parallels in the Y axis */
  }
  else if (p1.get_y() == p2.get_y() and q1.get_y() == q2.get_y() and p1.get_y() != q2.get_y()){
    parallel = true;        /** The lines are parallels in the X axis */
  }
  else if (p1.get_x() == p2.get_x()){   /** the segment of A is parallel to the Y axis */
    line_equation(q1,q2,m2,n2);
    x_coor = p1.get_x();
    y_coor = m2*x_coor+n2;

  } else if (q1.get_x() == q2.get_x()){   /** the segment of B is parallel to the Y axis */
    line_equation(p1,p2,m1,n1);
    x_coor = q1.get_x();
    y_coor = m1*x_coor+n1;

  } else {
    /** We compute the line equations of each pair of vertices of both polygons */
    line_equation(p1,p2,m1,n1); line_equation(q1,q2,m2,n2);
    if (m1 == m2) parallel = true;     /** first, we check that they are not parallel */
    else {
      x_coor = (n2 - n1)/(m1 - m2);
      y_coor = m1*x_coor+n1;
    }
  }
  if (not parallel){
    /** We check that the coordinates X and Y are inside the segments of the points */
    Point aux = Point(x_coor, y_coor);
    if ( inside(p1,p2,q1,q2,aux) ){
      inter.push_back(aux);
    }
  }
}

/** The intersection of two convex polygons is a convex polygon, as shown in the figure. */
Polygon Polygon::intersection ( const Polygon& P ) {
  vector<Point> inter(0);
  int a = v.size();
  int b = P.v.size();
  /** Points from polygon A(this) inside polygon B(P) */
  for ( auto p : v ) if (P.point_inside(p)) inter.push_back(p);
  /** Points from polygon B(P) inside polygon A(this) */
  for ( auto p : P.v ) if (point_inside(p)) inter.push_back(p);
  /** Points from the intersection of the edges */
  for (int i=1; i<a; i++){
    for (int j=1; j<b; j++){
      Point p1 = v[i-1];
      Point p2 = v[i];
      Point q1 = P.v[j-1];
      Point q2 = P.v[j];
      vector_intersection(p1,p2,q1,q2,inter);
    }
    Point p1 = v[i-1];
    Point p2 = v[i];
    Point q1 = P.v[b-1];
    Point q2 = P.v[0];
    vector_intersection(p1,p2,q1,q2,inter);
  }
  for (int j=1; j<b; j++){
    Point p1 = v[a-1];
    Point p2 = v[0];
    Point q1 = P.v[j-1];
    Point q2 = P.v[j];
    vector_intersection(p1,p2,q1,q2,inter);
  }
  Polygon Intersection = convex_hull(inter);
  return Intersection;
}

/** Given two convex polygons, the convex union is the smallest convex polygon that contains both polygons. */
Polygon Polygon::convex_union ( const Polygon& r ){
  vector<Point> unionn;
  unionn = this->v;
  int n = r.v.size();
  for (int i=0; i<n; i++) unionn.push_back(r.v[i]);
  Polygon Union = convex_hull (unionn);
  return Union;
}

/** Bounding box: Given a set of convex polygons, find the smallest bounding box that encloses all polygons. */
Polygon Polygon::bounding_box (){
  vector<Point> bb(4);
  double lx=0;
  double rx=0;
  double uy=0;
  double ly=0;
  /** We have to find the vertices of the bounding box. */
  for(Point p : v){
    if ( p.get_x() < lx ) lx = p.get_x();
    else if ( p.get_x() > rx ) rx = p.get_x();
    if ( p.get_y() < ly ) ly = p.get_y();
    else if ( p.get_y() > uy ) uy = p.get_y();
  }
  bb[0] = Point( lx, ly);
  bb[1] = Point( rx, ly);
  bb[2] = Point( rx, uy);
  bb[3] = Point( lx, uy);

  Polygon box = Polygon(bb);
  return box;
}

/**Returns whether a convex polygon is inside another convex polygon. */
/** We have to see whether all points of polygon p belong to the polygon(this) */
bool Polygon::polygon_inside ( const Polygon& p) const{
  int n = p.number_vertices();
  for (int i=0; i<n; i++){
    if ( not point_inside(p.v[i]) ) return false;
  }
  return true;
}

/** Returns whether point c is counterclockwise respect points a and b */
bool counterclockwise ( const Point& a, const Point& b, const Point& c ){
  return (b.get_x() - a.get_x())*(c.get_y() - a.get_y()) > (b.get_y() - a.get_y())*(c.get_x() - a.get_x());
}

bool inside2 ( const Point& a, const Point& b, const Point& c ){
  double x_left = min(a.get_x(), b.get_x());
  double x_right = max(a.get_x(), b.get_x());
  double y_lower = min(a.get_y(), b.get_y());
  double y_higher = max(a.get_y(), b.get_y());

  if (a.get_x() == b.get_x()) return (c.get_x() == a.get_x() and y_lower <= c.get_y() and y_higher >= c.get_y());
  else {
    double m,n;
    line_equation(a,b,m,n);
    return ( c.get_y() == c.get_x()*m+n and x_left <= c.get_x() and x_right >= c.get_x() and y_lower <= c.get_y() and y_higher >= c.get_y() );
  }
}

/** Returns whether a point is inside a convex polygon. */
bool Polygon::point_inside ( const Point& p ) const {
  int n = number_vertices();
  if (n==1) return v[0] == p;
  if (n==2) return inside2(v[0],v[1],p);
  for (int i=1; i<n; i++){
    if (counterclockwise(v[i-1],v[i],p)) return false;
  }
  if (counterclockwise(v[n-1],v[0],p)) return false;
  return true;
}

/** Changes the color of the polygon */
void Polygon::set_color( const double& R_col, const double& G_col, const double& B_col ){
  _R = R_col; _G = G_col; _B = B_col;
}

// INFORMATION ABOUT POLYGONS //

/** Returns the vector v */
vector<Point> Polygon::get_vector() const {
  return v;
}

/** Returns the number of vertices. */
int Polygon::number_vertices () const {
  return v.size();
}

/** Returns the number of edges. */
int Polygon::number_edges () const {
  return v.size();
}

/** Returns the lenght of the perimeter. */
double Polygon::lenght_perimeter () const {
  double lenght = 0;
  int n = v.size();
  for (int i = 1; i<n; ++i) lenght += v[i-1].distance (v[i]);

  if (n>2) return lenght + v[0].distance(v[n-1]);
  else return lenght;
}

/** Returns the area of the Polygon. */
double Polygon::area () const {
  int n = v.size();
  if ( n<3 ) return 0;
  double area = 0;
  for (int i=1; i<n; i++){     /** We compute the area with the determinants of matrix. */
    area += v[i-1].get_x()*v[i].get_y() - v[i-1].get_y()*v[i].get_x();
  }
  area += v[n-1].get_x()*v[0].get_y() - v[n-1].get_y()*v[0].get_x();
  return abs(area/2);
}

/** Returns whether a polygon is regular. */
bool Polygon::regular () const {
  int n = v.size();
  for (int i=2; i<n; i++) if ( v[i-2].distance(v[i-1]) != v[i-1].distance(v[i]) ) return false;
  return true;
}

/** Returns the coordinates of the centroid */
Point Polygon::centroid () const {
  int n = v.size();
  Point c = Point(0,0);
  for (int i=0; i<n; i++) c = Point( c.get_x() + v[i].get_x() , c.get_y() + v[i].get_y() );
  c = Point( c.get_x()/n, c.get_y()/n );
  return c;
}

/** Returns whether a polygon is empty */
bool Polygon::empty () const {
  return v.size() == 0;
}

/** Returns wheter a polygon has one vertex */
bool Polygon::monogon () const {
  return v.size() == 1;
}

/** Returns whether a polygon has two vertex */
bool Polygon::digon () const {
  return v.size() == 2;
}

/** Returns the colors of the polygon */
void Polygon::give_colors () const{
  cout << "color red: " << _R << endl;
  cout << "color gren: " << _G << endl;
  cout << "color blue: " << _B << endl;
}

/** Rescales each coordinate of the points, adapting it to the mesure of the png (500x500) */
/** To do so, we use the bounding box */
/**
Point rescale (const Point& p, const Polygon& bbox){
    Point ll = bbox.get_vector()[0];
    Point ur = bbox.get_vector()[2];   // These are the boundaries of the draw
    Point q = p;
    q -= ll;
    double x = 495 / (ur.get_x() - ll.get_x());
    double y = 495 / (ur.get_y() - ll.get_y());
    q *= min(x,y);
    return q + Point(2,2);   // We want the draw to start in the Point (2,2)
}
*/

/** Draws a given set of polygons */
/** The limit is the bounding box of the set of polygons we want to draw */
/**
void Polygon::draw(pngwriter& png, const Polygon& bbox) const{
    int n  = v.size();

    for (int i=0; i<n; i++){
        int j = (i == n-1 ? 0 : i+1);
        Point p = rescale(v[i],bbox);
        Point q = rescale(v[j],bbox);
        png.line(p.get_x(), p.get_y(), q.get_x(), q.get_y(), _R, _G, _B);
        png.filledcircle(p.get_x(), p.get_y(), 2, _R, _G, _B);
    }
    png.close();
}
*/
