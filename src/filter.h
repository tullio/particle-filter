#ifndef __FILTER
#define __FILTER
#include <iostream>
#include <vector>
#include <particles.h>
#include <MersenneTwister.h>
#include <ctime>
#include <cmath>
#include <cfloat>
using namespace std;

class Filter
{
  Particles<double> x, y;
  Particles<double>  v;
  vector<double> alpha;
  double w;
  MTRand mtrand;
  int number, dimension;
  Particles<double> (*state_func)(Particles<double> &p, Particles<double> &v);
  double (*robserve_func)(Particles<double> &p, Particle<double> &q);
  double (*robserve_jacobian_func)(Particles<double> &p, Particle<double> &q);
  double (*robserve_density_func)(double w);
public:
  Filter();
  Filter(double seed);
  ~Filter();
  bool setNumber(int n);
  bool setDimension(int d);
  bool createInitialParticles();
  bool create_system_noise(double mean, double dist);
  bool createInitialParticles(double d);
  int dump_predict_particles();
  Particles<double> get_particles();
  Particles<double> get_predict_particles();
  Particles<double> get_system_noise();
  bool set_state_func(Particles<double> (*func)(Particles<double> &p, Particles<double> &v));
  bool set_robserve_func(double (*func)(Particles<double> &p, Particle<double> &q));
  bool set_robserve_jacobian_func(double (*func)(Particles<double> &p, Particle<double> &q));
  bool set_robserve_density_func(double (*func)(double w));
  Filter & get_next_state();
  double get_observed_noise(int i);
  double get_robserved_density_value(double w);
  int dump_System_Noise();
  bool set_observed_data(Particles<double> &p);
  bool compute_likelihood();
  bool resampling();
};

#endif
