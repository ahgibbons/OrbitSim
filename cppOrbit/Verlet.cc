#include <vector>
#include <math.h>
#include <iostream>
#include "Mass.h"
#include "Verlet.h"
using namespace std;

static double G = 1;

void copy_vector(vector<double> source, vector<double> dest)
{
  int length = source.size();
  for (int i=0;i<length;i++) {
    dest[i] = source[i];
      }
}

Verlet_Int::Verlet_Int(Mass* self_mass, vector<Mass*> core_mass_list,
		       double step_size)
{
  m_step_size = step_size;
  m_self_mass = self_mass;
  m_core_mass_list = core_mass_list;
  vector<double> first_approx (2);
  // Perform an Euler Step to get r1
  for (int i=0;i<2;i++) {
    first_approx[i] = (m_self_mass -> get_velocity())[i] * m_step_size + 
      (m_self_mass -> get_position())[i];
  }
  t_prev_pos = m_self_mass -> get_position();
  m_self_mass -> set_position(first_approx[0],first_approx[1]);

  t_next_pos = * (new vector<double> (2));
  t_cur_pos  = * (new vector<double> (2));
  t_cur_vel = * (new vector<double> (2));
  t_next_vel = * (new vector<double> (2));
  t_force_vect = * (new vector<double> (2));
  
}

vector<double> Verlet_Int::calc_force()
{
  vector<double> total_force (2);
  double force;
  int length = m_core_mass_list.size();
  Mass mass;
  vector<double> disp_vect (2);
  vector<double> mass_vect (2);
  double dist_sq;
  for (int i=0;i<length;i++) {
    mass = *(m_core_mass_list[i]);
    for (int j=0;j<2;j++) {
      disp_vect[j] = (m_self_mass -> get_position())[j] - 
	mass.get_position()[j];
    }
    dist_sq = disp_vect[0]*disp_vect[0] + 
      disp_vect[1]*disp_vect[1];;

    
    for (int j=0;j<2;j++) {
      force = -G*disp_vect[j]*mass.get_mass()*
	pow(dist_sq, -(3.0/2.0));
      total_force[j] += force;
    }
  }
  return total_force;
}

void Verlet_Int::step()
{
  t_cur_pos = m_self_mass -> get_position();
  t_force_vect = calc_force();

  for (int i=0;i<2;i++) {
    //update position
    t_next_pos[i] = 2*t_cur_pos[i] - t_prev_pos[i] +
      (t_force_vect[i]*m_step_size*m_step_size);

    //update velocity
    t_next_vel[i] = (t_next_pos[i] - t_prev_pos[i]) / (2*m_step_size);
  }

  m_self_mass -> set_position(t_next_pos[0], t_next_pos[1]);
  m_self_mass -> set_velocity(t_next_vel[0], t_next_vel[1]);

  t_prev_pos[0] = t_cur_pos[0];
  t_prev_pos[1] = t_cur_pos[1];
  
}

// Perform Integration step on two masses at the same time
void Verlet_Int::simul_step(Verlet_Int* other_int) 
{
  t_cur_pos = m_self_mass -> get_position();
  t_force_vect = calc_force();

  for (int i=0;i<2;i++) {
    //update position
    t_next_pos[i] = 2*t_cur_pos[i] - t_prev_pos[i] +
      (t_force_vect[i]*m_step_size*m_step_size);

    //update velocity
    t_next_vel[i] = (t_next_pos[i] - t_prev_pos[i]) / (2*m_step_size);
  }

  // Call other integrator before values are updated
  other_int -> step();

  m_self_mass -> set_position(t_next_pos[0], t_next_pos[1]);
  m_self_mass -> set_velocity(t_next_vel[0], t_next_vel[1]);

  t_prev_pos[0] = t_cur_pos[0];
  t_prev_pos[1] = t_cur_pos[1];
}
