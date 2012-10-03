#ifndef __PARTICLE
#define __PARTICLE
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <MersenneTwister.h>
using namespace std;

template<class C> class Particle
{
  vector<C> p;
  int dimension;
public:
  Particle();
  Particle(int dimension);
  ~Particle();
  Particle(const Particle &f);
  Particle& operator=(const Particle &f);
  int resize(int n);
  int resize(int n, C a0);
  int size();
  vector<C> toVector();
  string toString();
  int dump();
  Particle& operator=(vector<C> &f);
  Particle<C> &operator+=(Particle<C> a);
  Particle<C> operator+(Particle<C> &a);
  C &operator[](unsigned int i);
  C operator[](unsigned int i) const;
};


#endif
