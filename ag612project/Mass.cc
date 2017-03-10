#include "Mass.h"
#include <stdio.h>
#include <string>
#include <vector>
using namespace std;

/*
Mass::Mass (double mass=1.0, double x=0, double y=0,
		 double vx=0, double vy=0)
{
  m_mass = mass;
  m_x = x;
  m_y = y;
  m_vx = vx;
  m_vy = vy;
}
*/

void Mass::set_position (double x, double y)
{
  m_x = x;
  m_y = y;
}

void Mass::set_velocity (double vx, double vy)
{
  m_vx = vx;
  m_vy = vy;
}


vector<double> Mass::get_position()
{
  vector<double> velocity (2);
  velocity[0] = m_x;
  velocity[1] = m_y;
  return velocity;
}


vector<double> Mass::get_velocity()
{
  vector<double> velocity (2);
  velocity[0] = m_vx;
  velocity[1] = m_vy;
  return velocity;
}

double Mass::get_energy()
{
  return 0.5 * m_mass * (m_vx*m_vx + m_vy*m_vy);
}

void Mass::set_mass (double mass)
{
  m_mass = mass;
}

