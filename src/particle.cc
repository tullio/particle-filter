/**
 this class repsesents one particle.
*/
#include <particle.h>


template<class C> Particle<C>::Particle()
{
  dimension = -1;
}
template<class C> Particle<C>::Particle(int dimension)
{
  resize(dimension);
}
template<class C> Particle<C>::~Particle()
{
}

// Copy constructor
template<class C> Particle<C>::Particle(const Particle &f)
{
  p = f.p;
  dimension = f.dimension;
}
template<class C> Particle<C>& Particle<C>::operator=(const Particle &f)
{
  if(this != &f)
  {
    if(dimension<0)
    {
      dimension = f.dimension;
      resize(dimension);
    }
    p = f.p;
  }
  return(*this);
}
template<class C> Particle<C>& Particle<C>::operator=(vector<C> &f)
{
  p = f;
  return(*this);
}
template<class C> Particle<C> &Particle<C>::operator+=(Particle<C> a)
{
  for(int i=0;i<size();++i)
  {
    p[i] += a[i];
  }
  return(*this);
}
template<class C> Particle<C> Particle<C>::operator+(Particle<C> &a)
{
  Particle<C> c = *this;
  return(c+=a);
}
template<class C> C &Particle<C>::operator[](unsigned int i)
{
  return(p[i]);
}
template<class C> C Particle<C>::operator[](unsigned int i) const
{
  return(p[i]);
}
template<class C> int Particle<C>::resize(int n)
{
  p.resize(n);
  this->dimension = n;
  return(0);
}
template<class C> int Particle<C>::resize(int n, C a0)
{
  p.resize(n, a0);
  this->dimension = n;
  return(0);
}
template<class C> int Particle<C>::size()
{
  return(dimension);
}
template<class C> vector<C> Particle<C>::toVector()
{
  return(p);
}
template<class C> string Particle<C>::toString()
{
  ostringstream s;
  s<<"(";
//  for(vector<C>::iterator i=p.begin();
//      i!=p.end();++i)
  for(unsigned int i=0;i<p.size();++i)
  {
//    if(i!=p.begin()) s<<",";
    if(i!=0) s<<",";
//    s<<dec<<*i;
    s<<fixed<<p[i];
  }
  s<<")";
  return(s.str());
}
template<class C> int Particle<C>::dump()
{
  cout<<toString()<<endl;
  return(0);
}

template class Particle<int>;
template class Particle<double>;
