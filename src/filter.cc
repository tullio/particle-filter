#include <filter.h>

Filter::Filter()
{
  number = -1;
  dimension = -1;
  state_func = NULL;
  mtrand.seed(time(NULL));
}
Filter::Filter(double seed)
{
  number = -1;
  dimension = -1;
  state_func = NULL;
  mtrand.seed(seed);
}
Filter::~Filter()
{
}

bool Filter::setNumber(int n)
{
  number = n;
  alpha.resize(n);
  return(true);
}
bool Filter::setDimension(int d)
{
  dimension = d;
  return(true);
}
bool Filter::createInitialParticles()
{
  if(number<0||dimension<0) return(false);
  x.resize(number, dimension);
  v.resize(number, dimension);
  return(true);
}
bool Filter::createInitialParticles(double d)
{
  if(number<0||dimension<0) return(false);
  x.resize(number, dimension, d);
  v.resize(number, dimension);
  return(true);
}
bool Filter::create_system_noise(double mean, double dist)
{
  for(int i=0;i<v.size();++i)
  {
    for(int j=0;j<v[i].size();++j)
    {
      v[i][j] = mtrand.randNorm(mean, dist);
    }
  }
  return(true);
}
int Filter::dump_predict_particles()
{
  x.dump_particles();
  return(0);
}
int Filter::dump_System_Noise()
{
  v.dump_particles();
  return(0);
}
Particles<double> Filter::get_predict_particles()
{
  return(x);
}
Particles<double> Filter::get_system_noise()
{
  return(v);
}
bool Filter::set_state_func(Particles<double> (*func)(Particles<double> &p, Particles<double> &v))
{
  state_func = func;
  return(true);
}
bool Filter::set_robserve_func(double (*func)(Particles<double> &p, Particle<double> &q))
{
  robserve_func = func;
  return(true);
}
bool Filter::set_robserve_jacobian_func(double (*func)(Particles<double> &p, Particle<double> &q))
{
  robserve_jacobian_func = func;
  return(true);
}
bool Filter::set_robserve_density_func(double (*func)(double w))
{
  robserve_density_func = func;
  return(true);
}
Filter & Filter::get_next_state()
{
  (*state_func)(x, v);
  return(*this);
}
double Filter::get_observed_noise(int i)
{
  return((*robserve_func)(y, x[i]));
}
double Filter::get_robserved_density_value(double w)
{
  return((*robserve_density_func)(w));
}

bool Filter::set_observed_data(Particles<double> &p)
{
  y = p;
  return(true);
}
bool Filter::compute_likelihood()
{
  for(unsigned int i=0;i<alpha.size();++i)
  {
//cout<<"y="<<y[0].toString()<<" x="<<x[i].toString()<<endl;
//cout<<"alpha="<<(*robserve_density_func)((*robserve_func)(y, x[i]))
//             <<"*"<<(*robserve_jacobian_func)(y, x[i])<<endl;
    alpha[i] = (*robserve_density_func)((*robserve_func)(y, x[i]))
                *(*robserve_jacobian_func)(y, x[i]);
  }
  return(true);
}
Particles<double> Filter::get_particles()
{
  return(x);
}
bool Filter::resampling()
{
  double alphasum = 0.0;
  int k=0;
  for(vector<double>::iterator i=alpha.begin();i!=alpha.end();++i)
  {
//cout<<"alpha["<<k<<"]="<<(*i)<<endl;
    ++k;
    alphasum += (*i);
  }
//cout<<"alpha sum="<<alphasum<<endl;
  if(alphasum*alphasum<DBL_EPSILON)
    cout<<"Regularize Constant is too small="<<alphasum<<endl;
  double m = (double)x.size();
  Particles<double> f(number, dimension);
  vector<double> psuma(x.size() + 1);
  psuma[0] = 0.0;
  for(int i=1;i<x.size();++i)
  {
    int l;
    psuma[i]=0.0;
    for(l=0;l<i;++l)
    {
      psuma[i]+=alpha[l];
    }
  }
  psuma[x.size()-1] = psuma[x.size()-2]+alpha[x.size()-1];
  for(int j=0;j<x.size();++j)
  {
    double u = ((j+1)-0.5)/m;
//cout<<"u="<<u<<endl;
    int sample_i = -1;
//    for(int i=1;i<((int)m-2);++i)
    for(int i=1;i<=x.size();++i)
    {
      double a1=0.0, a2=0.0;
      a1 = psuma[i-1];
      a2 = psuma[i];
//cout<<a1<<"<"<<u*alphasum<<"<="<<a2<<"?"<<endl;
//cout<<a1/alphasum<<"<"<<u<<"<="<<a2/alphasum<<"?"<<endl;
//cout<<(u<=a2/alphasum)<<"?"<<endl;
//cout<<(a1/alphasum<u)<<endl;
      if((a1/alphasum<u) && (a2/alphasum>=u))
      {
        sample_i = i - 1;
        break;
      }
    }
//cout<<"sample="<<(sample_i+0)<<endl;
    if(sample_i>=0)
    {
      f[j] = x[sample_i+0];
    }
  }
  x = f;
  return(true);
}