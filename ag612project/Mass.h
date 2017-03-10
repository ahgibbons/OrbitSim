#ifndef _MASS_CLASS_
#define _MASS_CLASS_

#include <vector>
#include <string>
using namespace std;

class Mass {
private:
  double m_mass;
  double m_x,m_y;
  double m_vx,m_vy;
public:
  //Mass (double,double,double,double,double);
  void set_position(double,double);
  void set_velocity(double,double);
  vector<double> get_position();
  vector<double> get_velocity();
  //std::string print();
  double get_x() {return m_x;}
  double get_y() {return m_y;}
  double get_vx() {return m_vx;}
  double get_vy() {return m_vy;}
  double get_mass() {return m_mass;}
  double get_energy();
  void set_mass(double);
};


#endif
