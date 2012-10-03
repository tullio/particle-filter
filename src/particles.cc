#include <particles.h>

template<class C> Particles<C>::Particles()
{
}
template<class C> Particles<C>::Particles(int number)
{
  p.resize(number);
  this->number = number;
}
template<class C> Particles<C>::Particles(int number, int dimension)
{
  resize(number, dimension);
}
// Copy constructor
template<class C> Particles<C>::Particles(const Particles &f)
{
  number = f.number;
  p.resize(number);
  for(unsigned int i=0;i<p.size();++i)
  {
    p[i] = f[i];
  }
}
// Copy substitution
template<class C> Particles<C>& Particles<C>::operator=(const Particles &f)
{
  if(this != &f)
  {
    number = f.number;
    p.resize(number);
    for(unsigned int i=0;i<p.size();++i)
    {
      p[i] = f[i];
    }
  }
  return(*this);
}
template<class C> Particles<C> &Particles<C>::operator+=(Particles<C> a)
{
  for(int i=0;i<size();++i)
  {
    p[i] += a[i];
  }
  return(*this);
}
template<class C> Particles<C> Particles<C>::operator+(Particles<C> &a)
{
  Particles<C> c = *this;
  return(c+=a);
}

template<class C> Particles<C>::~Particles()
{
}
template<class C> bool Particles<C>::resize(int number, int dimension)
{
  p.resize(number);
  this->number = number;
  typedef Particle<C> ParticleC;
//  for(vector<ParticleC>::iterator i= p.begin();
//    i!=p.end();++i)
  for(unsigned int i=0;i<p.size();++i)
  {
//    i->resize(dimension);
    p[i].resize(dimension);
  }
  return(true);
}
template<class C> bool Particles<C>::resize(int number, int dimension, C a0)
{
  p.resize(number);
  this->number = number;
  typedef Particle<C> ParticleC;
//  for(vector<ParticleC>::iterator i= p.begin();
//    i!=p.end();++i)
  for(unsigned int i=0;i<p.size();++i)
  {
//    i->resize(dimension);
    p[i].resize(dimension, a0);
  }
  return(true);
}
template<class C> int Particles<C>::size()
{
  return(number);
}
template<class C> Particle<C> &Particles<C>::operator[](unsigned int i)
{
  return(p.at(i));
}
template<class C> Particle<C> Particles<C>::operator[](unsigned int i) const
{
  return(p.at(i));
}
template<class C> vector<Particle<C> > Particles<C>::toVector()
{
  return(p);
}
template<class C> int Particles<C>::dump_particles()
{
//  for(vector<Particle<C> >::iterator i=p.begin();
//      i!=p.end();++i)
  for(unsigned int i=0;i<p.size();++i)
  {
//    i->dump();
    p[i].dump();
  }
  return(0);
}
template<class C> string Particles<C>::toString()
{
  ostringstream s;
  for(unsigned int i=0;i<p.size();++i)
  {
    s<<p[i].toString();
  }
  return(s.str());
}

template class Particles<int>;
template class Particles<double>;
