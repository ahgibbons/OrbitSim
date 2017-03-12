#include <stdio.h>
#include <stdlib.h>

struct mass {
  double m;
  double r0[2];
  double r[2];
  double v[2];

  
};

void initMass(struct mass* m, double r0, double v0, double dt) {
  double rx;
  double ry;

  m->m = 1;
  m->r0[0] = r0;
  m->r0[1] = 0;
  m->v[0] = 0;
  m->v[1] = v0;

  rx = (m->r0[0]) + dt*(m->v[0]);
  ry = (m->r0[1]) + dt*(m->v[1]);

  m->r[0] = rx;
  m->r[1] = ry;

}

void runOrbit(final_time,total_steps) {
  double dt;
  struct mass m1;
  struct mass m2;
  double xs[total_steps];
  double r0;
  double r1;
  double r_new;
  double a;
  double ys[total_steps];
  double ts[total_steps];
  double t;

  dt = final_time / total_steps;
  t = 0;
  initMass(&m1,10,0.316,dt);
  initMass(&m2,0,0,dt);
  
  for (int i=0;i<total_steps;i++) {
    ts[i] = t;
    t += dt;
    
    r1 = m1.r[0];
    r0 = m1.r0[0];
    a = gravAcc;
    r_new = verletStep(r0,r1,a,dt);
    
    
}

  double gravAcc()

double verletStep(double x0, double x1, double a, double dt) {
  return (2*x1 - x0 + (dt*dt*a));
}

int main(int argc, char *argv[]) {
  // args: [Final time] [Total steps] 
  
  double final_time;
  int total_steps;
  

  if (argc!=3) {
    printf("Incorrect number of arguments.\n");
    return 0;
  }

  final_time = atof(argv[1]);
  total_steps = atoi(argv[2]);

  

  printf("Final time is %f\n", final_time);
  printf("Total steps is %d\n",total_steps);

  runOrbit(final_time,total_steps);
  
  return 0;
}

