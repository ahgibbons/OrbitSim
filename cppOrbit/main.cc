#include <iostream>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Mass.h"
#include "Verlet.h"
#define PI 3.141592653589793
using namespace std;


/* 
Writes mass data from mass_list to outfile. rel_pos and rel_vel define frame
in which coordinates are output (so Position (0,0,0), velocity (0,0,0) 
represents the origin) 
*/
void output_data(FILE* outfile, vector<Mass> mass_list, double time,
		 vector<double> rel_pos, vector<double> rel_vel)
{
  /* 
     For Gnuplot:
     col time: 1
     col x_i: 2 + 5*i
     col y_i: 3 + 5*i
     col vx_i: 4 + 5*i
     col vy_i: 5 + 5*i
     col E_i: 6 + 5*i
  */

  int length = mass_list.size();
  fprintf(outfile, "%.3f\t", time);
  for (int i=0;i<length;i++) {
    double x = mass_list[i].get_x() - rel_pos[0];
    double y = mass_list[i].get_y() - rel_pos[1];
    double vx = mass_list[i].get_vx() - rel_vel[0];
    double vy = mass_list[i].get_vy() - rel_vel[1];
    double E = mass_list[i].get_energy();
    fprintf(outfile, "%.3f\t%.3f\t%.3f\t%.3f\t%.3f\t",
	    x, y, vx, vy, E);
  }
  fprintf(outfile, "\n");
}

/*
Creates a ring of test masses surrounding cmass. The masses are evenly
distributed around the ring
*/
vector<Mass> create_ring(double radius, int number, double cmass, double G=1)
{
  vector<Mass> ring_list (number);
  double theta;
  double omega;
  for (int i=0;i<number;i++) {
    
    theta = (2 * PI * i) / number;
    omega = pow(G*cmass / (radius*radius*radius), 0.5);
    double mass = 1.0;
    double x_pos = radius * cos(theta);
    double y_pos = radius * sin(theta);
    double x_vel = -1*radius * omega * sin(theta);
    double y_vel = radius * omega * cos(theta);
    Mass test_mass;
    test_mass.set_position(x_pos,y_pos);
    test_mass.set_velocity(x_vel,y_vel);
    test_mass.set_mass(mass);
    ring_list[i] = test_mass;
  }
  
  return ring_list;
}

/*
Creates multiple rings of test masses according to
the initial conditions of the problem.
*/
vector<Mass> setup_rings()
{
  vector<Mass> ring1_list;
  vector<Mass> ring2_list;
  vector<Mass> ring3_list;
  vector<Mass> ring4_list;
  vector<Mass> ring5_list;
  vector<Mass> ring6_list;
  vector<Mass> ring7_list;
  vector<Mass> output_list;
 
  ring1_list = create_ring(2,12,1);
  ring2_list = create_ring(3,18,1);
  ring3_list = create_ring(4,24,1);
  ring4_list = create_ring(5,30,1);
  ring5_list = create_ring(6,36,1);
  //ring6_list = create_ring(7,42,1); // These lines will add more masses
  //ring7_list = create_ring(8,48,1);

  output_list.insert(output_list.end(), ring1_list.begin(),ring1_list.end());
  output_list.insert(output_list.end(), ring2_list.begin(),ring2_list.end());
  output_list.insert(output_list.end(), ring3_list.begin(),ring3_list.end());
  output_list.insert(output_list.end(), ring4_list.begin(),ring4_list.end());
  output_list.insert(output_list.end(), ring5_list.begin(),ring5_list.end());
  output_list.insert(output_list.end(), ring6_list.begin(),ring6_list.end());
  output_list.insert(output_list.end(), ring7_list.begin(),ring7_list.end());

  return output_list;
}

// Used for testing. Standard constant accerlation distance formula
double uvast_dist(double x0, double ux, double acc, double t)
{
  return x0 + ux*t + 0.5*acc*t*t;
}

int main(int argc, char* argv[])
{
  /*  Command Line
      ./main [final time] [dt] [step size] [galaxframe]
  */

  vector<Mass> mass_list;
  vector<Verlet_Int> verlet_list;
  vector<Mass> core_mass_list;
  vector<Mass*> core_mass_ptr_list;
  double time=0;
  double final_time;
  double dt;
  int step;
  bool galaxframe;
  
  // retrieve commandline arguments
  if (argc >1) {final_time = atoi(argv[1]);}
  else {final_time = 20;}
  if (argc>2) {dt = atof(argv[2]);}
  else {dt = 0.001;}
  if (argc >3) {step = atoi(argv[3]);}
  else {step = 10;}
  if (argc>4) {int i_galaxframe = atoi(argv[4]);
    galaxframe = (i_galaxframe == 1);}
  else {galaxframe = false;}

  int num_steps = (int) (final_time - time) / dt;

  // Setup galaxy centre masses
  Mass galaxy;
  galaxy.set_position(0,0);
  galaxy.set_velocity(0,0);
  galaxy.set_mass(1);
  core_mass_list.push_back(galaxy);
  Mass galaxy2;

  galaxy2.set_position(-36,-27);
  galaxy2.set_velocity(2.0/15.0,4.0/15.0);
  galaxy2.set_mass(1);
  core_mass_list.push_back(galaxy2);

  int length = core_mass_list.size();
  for (int i=0;i<length;i++) {
    core_mass_ptr_list.push_back(&core_mass_list[i]);
  }

  //Setup test masses
  mass_list = setup_rings();

  /*
    COMMENTED OUT. Used for debugging of single test mass
  Mass test_mass;
  test_mass.set_position(1,0);
  test_mass.set_velocity(0,-1);
  test_mass.set_mass(1);
  mass_list.push_back(test_mass);
  */


  cout << "Number of test masses:  " << mass_list.size() << endl;

  // Create Verlet Integrator for each test mass
  for (int i=0;i<mass_list.size();i++) {
    Verlet_Int verlet(&(mass_list[i]),core_mass_ptr_list, dt);
    verlet_list.push_back(verlet);
  }

  
  // Create Verlet Integrator for the Galactic Masses
  vector<Mass*> gal1_list (1);
  vector<Mass*> gal2_list (1);
  gal1_list[0] = &core_mass_list[0];
  gal2_list[0] = &core_mass_list[1];
  Verlet_Int gal_int_1(&core_mass_list[0], gal2_list, dt);
  Verlet_Int gal_int_2(&core_mass_list[1], gal1_list, dt);
  


  FILE * t_mass_file;
  FILE * c_mass_file;
  t_mass_file = fopen("tmass.txt", "w");
  c_mass_file = fopen("cmass.txt", "w");

  // Run Simulation
  vector<double> frame_centre (2,0);
  vector<double> frame_vel (2,0);
  int mass_num = verlet_list.size();
  for (int i=0;i<num_steps;i++) {
    for (int j=0;j<mass_num;j++) {
      verlet_list[j].step();
    }
    gal_int_1.simul_step(&gal_int_2);
    if (i%step == 0) {
      if (galaxframe) {
	frame_centre = core_mass_list[0].get_position();
	frame_vel = core_mass_list[0].get_velocity();
      }
      output_data(t_mass_file, mass_list,i*dt,
		  frame_centre,frame_vel);
      output_data(c_mass_file,core_mass_list, i*dt,
		  frame_centre,frame_vel);
      
    }
  }
  
  // Output program information to commandline
  cout << "Galaxy Centre Frame: ";
  if (galaxframe) { cout << "True" << endl;}
  else {cout << "False" << endl;}
  cout << "Simulation time:  " << final_time << endl;
  cout << "Time Step:  " << dt << endl;
  cout << "Output Step:  " << step << endl;
  cout << "Lines Output:  " << final_time / (dt * step) << endl;
  cout << "Done"  << endl;
  fclose(t_mass_file);
  fclose(c_mass_file);
    
}
