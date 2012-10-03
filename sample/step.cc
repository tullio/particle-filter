#include <MersenneTwister.h>
#include <filter.h>
Particles<double> func1(Particles<double> &p, Particles<double> &v)
{
  for(int i=0;i<p.size();++i)
  {
    for(int j=0;j<p[i].size();++j)
    {
//cout<< p[i][j]<<"+"<<v[i][j]<<endl;
      p[i][j]= p[i][j]+v[i][j];
    }
  }
//  cout<<"state function"<<endl;
  return(p);
}
double func2(Particles<double> &p, Particle<double> &q)
{

//  cout<<"robserve function"<<endl;
//  cout<<"noise="<<(p[0][0]-q[0])<<endl;
//  return(p[0][0]-q[0]);
  double err = 0.0, n=0.0;
  for(int i=0;i<p.size();++i)
  {
    for(int j=0;j<p[i].size();++j)
    {
       err += p[i][j] - q[j];
       n += 1.0;
    }
  }
  return(err/n);
}
double func3(Particles<double> &p, Particle<double> &q)
{
//  cout<<"robserve jacobian function"<<endl;
  return(1.0);
}
double func4(double w)
{
//  cout<<"robserve density function"<<endl;
  double rho = 1.51;
  double r = (1.0/sqrt(2.0*M_PI*rho*rho)*exp(-w*w/(2.0*rho*rho)));
  return(r);
}

int main()
{
  Filter track;
  MTRand mtrand;
#define NUM 1000
  mtrand.seed(time(NULL));
  track.setNumber(NUM);
  track.setDimension(1);
  track.set_state_func(&func1);
  track.set_robserve_func(&func2);
  track.set_robserve_jacobian_func(&func3);
  track.set_robserve_density_func(&func4);
  track.createInitialParticles();
  double t;
  Particles<double> x(NUM,1), y(NUM,1);
  for(int i=0;i<100;++i)
  {
    track.create_system_noise(0.0, 1.0);
    track.get_next_state(); // predict
    x = track.get_particles();
    double xp_=0.0;
    for(int j=0;j<x.size();++j)
    {
      xp_ += x[j][0];
    }
//cout<<xp_/x.size()<<endl;

    t = i<25?1:i<50?0:i<75?-1:1;
    for(int j=0;j<x.size();++j)
    {
      y[j][0] = t + (mtrand.rand()-0.5)*8.0;
    }
    double y_=0.0;
    for(int j=0;j<x.size();++j)
    {
      y_ += y[j][0];
    }
//cout<<"observed="<<y_/x.size()<<endl;
//cout<<y_/x.size()<<endl;

//cout<<y[0][0]<<endl;
    track.set_observed_data(y);
    track.compute_likelihood();
    x = track.get_particles();
    for(int j=0;j<x.size();++j)
    {
//      cout<<"["<<j<<"]"<<x[j][0]<<endl;
    }
    track.resampling();
//cout<<"--resampled--"<<endl;
    x = track.get_particles();
    for(int j=0;j<x.size();++j)
    {
//      cout<<"["<<j<<"]"<<x[j][0]<<endl;
    }
//cout<<endl;
//cout<<endl;

    double x_=0.0;
    for(int j=0;j<x.size();++j)
    {
      x_ += x[j][0];
    }
cout<<x_/x.size()<<endl;
  }
}