#ifndef _VERLET_CLASS_
#define _VERLET_CLASS_
#include <vector>

class Verlet_Int {
private:
  Mass* m_self_mass;
  double m_step_size;
  vector<Mass*> m_core_mass_list;
  vector<double> t_next_pos;
  vector<double> t_cur_pos;
  vector<double> t_prev_pos;
  vector<double> t_cur_vel;
  vector<double> t_next_vel;
  vector<double> t_force_vect;

public:
  Verlet_Int (Mass*,vector<Mass*>,double);
  void step();
  vector<double> calc_force();
  void simul_step(Verlet_Int*);
};

#endif
