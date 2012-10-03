#ifndef __PARTICLES
#define __PARTICLES
#include <iostream>
#include <vector>
#include <particle.h>
using namespace std;

template<class C> class Particles
{
  vector<Particle<C> > p;
  int number;
public:
  Particles();
  Particles(int number);
  Particles(int number, int dimension);
  Particles(const Particles &f);
  Particles<C>&operator=(const Particles &f);
  Particles<C> &operator+=(Particles<C> a);
  Particles<C> operator+(Particles<C> &a);
  ~Particles();
  bool resize(int number, int dimension);
  bool resize(int number, int dimension, C a0);
  int size();
  Particle<C> &operator[](unsigned int i);
  Particle<C> operator[](unsigned int i) const;
  vector<Particle<C> > toVector();
  int dump_particles();
  string toString();
};


#endif
