#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
//#include <pngwriter.h>
using namespace std;

#include "Point.hh"
#include "Polygon.hh"


// ************************************************************************************

void error (int n){
  if (n==1) cout << "error: unrecognized command" << endl;
  else if (n==2) cout << "error: polygon not defined yet" << endl;
  else if (n==3) cout << "error: wrong format" << endl;
  else if (n==4) cout << "error: command with wrong number or type of arguments" << endl;
}

void pols_comment (istringstream& iss){
  string comment;
  iss >> comment;
  cout << "#" << endl;
}

void pols_def (map<string,Polygon>& pols, istringstream& iss){
  string name,letra;
  iss >> name;
  double x;
  vector<Point> v(0);
  vector<double> r(0);
  while( iss>>x ) r.push_back(x);
  int n = r.size();
  if (n%2==0){
    for(int i=1; i<n; i+=2){
      Point p = Point(r[i-1],r[i]);
      v.push_back(p);
    }
    pols[name] = Polygon(v);
    cout << "ok" << endl;
  } else error(4);
}

void pols_print (map<string,Polygon>& pols, istringstream& iss){
  string name;
  iss >> name;
  if (pols.count(name)){
    cout << name;
    int n = pols[name].get_vector().size();
    if (n==0) cout << " is empty" << endl;
    else {
      for (int i=0; i<n; i++) cout << " " << pols[name].get_vector()[i].get_x() << " " << pols[name].get_vector()[i].get_y();
      cout << endl;
    }
  } else error (2);
}

void pols_intersection (map<string,Polygon>& pols, istringstream& iss){
  string name;
  vector<string> names(0);
  while ( iss>>name ) names.push_back(name);
  bool exists = true;
  for(auto nom : names) if (not pols.count(nom)) exists = false;
  if (exists){
    int n = names.size();
    if (n==2) pols[names[0]] = pols[names[0]].intersection(pols[names[1]]);
    else pols[names[0]] = pols[names[1]].intersection(pols[names[2]]);
    cout << "ok" << endl;
  } else error(2);
}

void pols_union (map<string,Polygon>& pols, istringstream& iss){
  string name;
  vector<string> names(0);
  while ( iss>>name ) names.push_back(name);
  bool exists = true;
  for (auto nom : names) if (not pols.count(nom)) exists = false;
  if (exists){
    int n = names.size();
    cout << n << endl;
    if (n==2) pols[names[0]] = pols[names[0]].convex_union(pols[names[1]]);
    else pols[names[0]] = pols[names[1]].convex_union(pols[names[2]]);
    cout << "ok" << endl;
  } else error(2);
}

void pols_bbox (map<string,Polygon>& pols, istringstream& iss){
  string name, name1;
  vector<string> names(0);
  iss >> name1;            /** Name of the bounding box */
  while ( iss >> name ) names.push_back(name);
  bool exists = true;
  for (auto nom : names) if (not pols.count(nom)) exists = false;
  if (exists){
    int n = names.size();
    vector<Point> points(0);
    for (int i=0; i<n; i++){
      int m = pols[names[i]].get_vector().size();
      for (int j=0; j<m; j++){
        points.push_back(pols[names[i]].get_vector()[j]);
      }
    }
    Polygon aux = Polygon(points);    /** Auxiliar polygon that contains all the points. */
    pols[name1] = aux.bounding_box();
    cout << "ok" << endl;
  } else error(2);
}

void pols_polygon_inside (map<string,Polygon>& pols, istringstream& iss){
  string name1, name2;
    /** First we input the name of the polygon that may contain the second polygon */
  iss >> name1 >> name2;
  if (pols.count(name1) and pols.count(name2)){
    if (pols[name1].empty()) cout << name1 << " is empty, so it cannot contain another polygon" << endl;
    else if (pols[name2].empty()) cout << name2 << " is empty, so it cannot be contained" << endl;
    else{
      if (pols[name1].polygon_inside(pols[name2])) cout << "yes" << endl;
      else cout << "no" << endl;
    }
  } else error(2);
}

void pols_point_inside (map<string,Polygon>& pols, map<string, Point> points, istringstream& iss){
  string name1, aux = "aux";
  double x;
  vector<double> r(0);
  /** First we input the name of the polygon and then the name of the point */
  iss >> name1;
  while( iss>>x ) r.push_back(x);
  if (pols.count(name1)){
    if ( r.size()==2 ){
      if (pols[name1].empty())cout << name1 << " is empty, so it cannot contain a point" << endl;
      else{
        points[aux] = Point(r[0],r[1]);
        if (pols[name1].point_inside(points[aux])) cout << "yes" << endl;
        else cout<< "no" << endl;
      }
    } else error(4);
  } else error(2);
}

void pols_vertices (map<string,Polygon>& pols, istringstream& iss){
  string name;
  iss >> name;
  if (pols.count(name)) cout << pols[name].number_vertices() << endl;
  else error(2);
}

void pols_edges (map<string,Polygon>& pols, istringstream& iss){
  string name;
  iss >> name;
  if (pols.count(name)) cout << pols[name].number_edges() << endl;
  else error(2);
}

void pols_perimeter (map<string,Polygon>& pols, istringstream& iss){
  string name;
  iss >> name;
  if (pols.count(name)) cout << pols[name].lenght_perimeter() << endl;
  else error(2);
}

void pols_area (map<string,Polygon>& pols, istringstream& iss){
  string name;
  iss >> name;
  if (pols.count(name)){
    if (pols[name].area()!=0) cout << pols[name].area() << endl;
    else cout << name << " is empty" << endl;
  } else error(2);
}

void pols_regular (map<string,Polygon>& pols, istringstream& iss){
  string name;
  iss >> name;
  if (pols.count(name)){
    if (pols[name].regular()) cout << "yes" << endl;
    else cout << "no" << endl;
  } else error(2);
}

void pols_centroid (map<string,Polygon>& pols, istringstream& iss){
  string name;
  iss >> name;
  if (pols.count(name)) cout << pols[name].centroid().get_x() << " " << pols[name].centroid().get_y() << endl;
  else error(2);
}

void pols_empty (map<string,Polygon>& pols, istringstream& iss){
  string name;
  iss >> name;
  if (pols.count(name)){
    if (pols[name].empty()) cout << "yes" << endl;
    else cout << "no" << endl;
  } else error(2);
}

void pols_monogon (map<string,Polygon>& pols, istringstream& iss){
  string name;
  iss >> name;
  if (pols.count(name)){
    if (pols[name].monogon()) cout << "yes" << endl;
    else cout << "no" << endl;
  } else error(2);
}

void pols_digon (map<string,Polygon>& pols, istringstream& iss){
  string name;
  iss >> name;
  if (pols.count(name)){
    if (pols[name].digon()) cout << "yes" << endl;
    else cout << "no" << endl;
  } else error(2);
}

void pols_give_colors (map<string,Polygon>& pols, istringstream& iss){
  string name;
  iss >> name;
  if (pols.count(name)){
    pols[name].give_colors();
  } else error(2);
}

void pols_save (map<string,Polygon>& pols, istringstream& iss){
  string name, polygon;
  iss >> name;

  ofstream file;
  file.open (name);
  while ( iss>>polygon ){
    if (pols.count(polygon)){
      file << polygon;
      for ( auto p : pols[polygon].get_vector() ){
        file << " " << p.get_x() << " " << p.get_y();
      } file << endl;
    } else error(2);
  }
  file.close();
  cout << "ok" << endl;
}

void pols_load (map<string,Polygon>& pols, istringstream& iss){
  string name, linia, polygon;
  iss >> name;
  ifstream myfile (name);
  while( getline(myfile,linia) ){
    istringstream oss(linia);
    oss >> polygon;
    double x, y;
    vector<Point>v(0);
    while( oss>>x>>y ){
      Point aux = Point(x,y);
      v.push_back(aux);
    } pols[polygon] = Polygon(v);
  } cout << "ok" << endl;
}

void pols_list (map<string,Polygon>& pols){
  if (pols.empty()) cout << "There are no polygons" << endl;
  else {
    for ( auto x : pols ){
      cout << x.first << " ";
    } cout << endl;
  }
}

void pols_setcol(map<string,Polygon>& pols, istringstream& iss){
  string name;
  iss >> name;
  if (pols.count(name)){
    double r, g, b;
    iss >> r >> g >> b;
    if (r<=1 and r>=0 and g<=1 and g>=0 and b<=1 and b>=0){
      pols[name].set_color(r,g,b);
      cout << "ok" << endl;
    } else error(3);
  } else error(2);
}

void pols_draw (map<string,Polygon>& pols, istringstream& iss){
  /**string file, name;
  iss >> file;
  pngwriter png (500, 500, 1.0, file.c_str());
  vector <string> names(0);
  vector <Point> all_points(0);
  while ( iss>>name ) names.push_back(name);
  bool exists = true;
  for (auto nom : names) if (not pols.count(nom)) exists = false;
  if (exists){
      for (auto nom : names){
          int n = pols[nom].get_vector().size();
          for (int i=0; i<n; i++) all_points.push_back(pols[nom].get_vector()[i]);
      }
      Polygon aux = Polygon(all_points);
      aux = aux.bounding_box();
      for (auto nom : names) pols[nom].draw(png,aux);
      cout << "ok" << endl;
  } else error(2);*/
  cout << "ok" << endl;
}

/** ************************************************************************************ */
/** ************************************************************************************ */


int main(){
  cout.setf (ios::fixed);
  cout.precision (3);
  map<string, Point> points;
  map<string, Polygon> pols;

  string action, linia;
  while (getline(cin,linia)){
    istringstream iss(linia);
    iss >> action;
         if (action == "#")                 pols_comment(iss);
    else if (action == "polygon")           pols_def(pols,iss);
    else if (action == "print")             pols_print(pols,iss);
    else if (action == "intersection")      pols_intersection(pols,iss);
    else if (action == "union")             pols_union(pols,iss);
    else if (action == "bbox")              pols_bbox(pols,iss);
    else if (action == "inside")            pols_polygon_inside(pols,iss);
    else if (action == "point_inside")      pols_point_inside(pols,points,iss);
    else if (action == "vertices")          pols_vertices(pols,iss);
    else if (action == "edges")             pols_edges(pols,iss);
    else if (action == "perimeter")         pols_perimeter(pols,iss);
    else if (action == "area")              pols_area(pols,iss);
    else if (action == "regular")           pols_regular(pols,iss);
    else if (action == "centroid")          pols_centroid(pols,iss);
    else if (action == "empty")             pols_empty(pols,iss);
    else if (action == "monogon")           pols_monogon(pols,iss);
    else if (action == "digon")             pols_digon(pols,iss);
    else if (action == "give_colors")       pols_give_colors(pols,iss);
    else if (action == "save")              pols_save(pols,iss);
    else if (action == "load")              pols_load(pols,iss);
    else if (action == "list")              pols_list(pols);
    else if (action == "setcol")            pols_setcol(pols,iss);
  //  else if (action == "draw")              pols_draw(pols,iss);

    else error(1);
  }
}
