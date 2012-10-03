#include <cppcutter.h>
#include <particle.h>
#include <iostream>
#include <filter.h>
using namespace std;

#define NUM_PARTICLE 100
#define SYS_DIST 5.0
#define OBS_DIST 0.01

Particles<double> func1(Particles<double> &p, Particles<double> &v)
{
  for(int i=0;i<p.size();++i)
  {
    for(int j=0;j<p[i].size();++j)
    {
      p[i][j]= p[i][j]+v[i][j];
    }
  }
//  cout<<"state function"<<endl;
  return(p);
}
double func2(Particles<double> &p, Particle<double> &q)
{
  double diff = 0.0;
  for(int i=0;i<p.size();++i)
  {
    Particle<double> x = p[i];
    double d = 0.0;
    for(int j=0;j<x.size();++j)
    {
      d += (x[j]-q[j])*(x[j]-q[j]);
    }
    diff += sqrt(d);
  }

//  cout<<"robserve function"<<endl;
//  return(p[0][0]-q[0]);
  return(diff/p.size());
}
double func3(Particles<double> &p, Particle<double> &q)
{
//  cout<<"robserve jacobian function"<<endl;
  return(1.0);
}
double func4(double w)
{
//  cout<<"robserve density function"<<endl;
  return(1.0/sqrt(2.0*M_PI*OBS_DIST*OBS_DIST)*exp(-w*w/(2.0*OBS_DIST*OBS_DIST)));
}

Particles<double> sin_system_func(Particles<double> &p, Particles<double> &v)
{
  for(int i=0;i<p.size();++i)
  {
    for(int j=0;j<p[i].size();++j)
    {
      p[i][j]= p[i][j]+v[i][j];
    }
  }
//  cout<<"state function"<<endl;
  return(p);
}
double sin_reversed_observed_func(Particles<double> &p, Particle<double> &q)
{
  double diff = 0.0;
  for(int i=0;i<p.size();++i)
  {
    Particle<double> x = p[i];
    double d = 0.0;
    for(int j=0;j<x.size();++j)
    {
      d += (x[j]-q[j])*(x[j]-q[j]);
    }
    diff += sqrt(d);
  }

//  cout<<"robserve function"<<endl;
//  return(p[0][0]-q[0]);
  return(diff/p.size());
}
double sin_reversed_jacobian_func(Particles<double> &p, Particle<double> &q)
{
//  cout<<"robserve jacobian function"<<endl;
  return(1.0);
}
double sin_reversed_observed_density_func(double w)
{
//  cout<<"robserve density function"<<endl;
  return(1.0/sqrt(2.0*M_PI*OBS_DIST*OBS_DIST)*exp(-w*w/(2.0*OBS_DIST*OBS_DIST)));
}

namespace test_filter
{
  void cut_setup()
  {
  }
  void cut_teardown()
  {
  }

  void test_construction(void)
  {
    // Constructor
    Filter a(0.0);
    a.setNumber(NUM_PARTICLE);
    a.setDimension(3);
    a.createInitialParticles();
    for(int i=0;i<NUM_PARTICLE;++i)
    {
      for(int j=0;j<3;++j)
      {
        // initial values should be zero
        cut_assert_equal_double(0.0, 0.1, a.get_particles().toVector().at(i).toVector().at(j));
      }
    }
//    a.dump_predict_particles();
  }
  void test_manipulation(void)
  {
    Filter a(0.0);
    a.setNumber(NUM_PARTICLE);
    a.setDimension(3);
    a.set_state_func(&func1);
    a.set_robserve_func(&func2);
    a.set_robserve_jacobian_func(&func3);
    a.set_robserve_density_func(func4);

    a.createInitialParticles();
    a.create_system_noise(0.0, 1.0);

    // initial value
    for(int i=0;i<NUM_PARTICLE;++i)
    {
      for(int j=0;j<3;++j)
      {
        // initial values should be zero
        cut_assert_equal_double(0.0, 0.1, a.get_particles()[i][j]);
      }
    }
    for(int i=0;i<NUM_PARTICLE;++i)
    {
      for(int j=0;j<3;++j)
      {
        // initial values should be near zero
        cut_assert_equal_double(0.0, 10.0, a.get_system_noise()[i][j]);
      }
    }

    Particles<double> noise(a.get_system_noise());
    Particles<double> prediction(a.get_predict_particles());

    a.get_next_state();
    Particles<double> predict =  prediction + noise;
    // initial value+system noise
    cut_assert_equal_string(predict.toString().c_str(),a.get_predict_particles().toString().c_str());
//cout<<"predict1:"<<predict.toString()<<endl;
    Particles<double> y(NUM_PARTICLE,3);
    Particle<double> x(3);
    x[0]=0.1; x[1]=-1.1; x[2]=1.5;

    // no noise. tracking point should be (0.1, -1.1, 1.5)
    for(int i=0;i<y.size();++i)
    {
      y[i] = x;
    }
//cout<<"observed1:"<<y.toString()<<endl;
    a.set_observed_data(y);
    double diff;
    diff = x[0]-predict[0][0];
    cut_assert_equal_double(0.0, 2.0, diff);
    cut_assert_equal_double(1.0,1.0 ,a.get_robserved_density_value(diff));
    a.compute_likelihood();
    a.resampling();
//cout<<"resampled1:"<<a.get_predict_particles().toString()<<endl;
    for(int j=0;j<a.get_predict_particles().size();++j)
    {
      for(int i=0;i<x.size();++i)
      {
        cut_assert_equal_double(x[i],10.0, a.get_predict_particles()[j][i]);
      }
    }

    // step 2

    a.create_system_noise(0.0, 1.0);
    a.get_next_state();
//cout<<"predict2:"<<a.get_predict_particles().toString()<<endl;
    for(int j=0;j<a.get_predict_particles().size();++j)
    {
      for(int i=0;i<x.size();++i)
      {
        cut_assert_equal_double(x[i],10.0, a.get_predict_particles()[j][i]);
      }
    }
    x[0]=0.2; x[1]=-1.0; x[2]=1.5;
    for(int i=0;i<y.size();++i)
    {
      y[i] = x;
    }
//cout<<"observed2:"<<y.toString()<<endl;
    a.set_observed_data(y);
    cut_assert_equal_double(x[0],10.0,a.get_observed_noise(0));
    a.set_robserve_density_func(func4);
    diff = x[0]-predict[0][0];
    cut_assert_equal_double(1.0,1.0,a.get_robserved_density_value(diff));
    a.compute_likelihood();
    a.resampling();
//cout<<"resampled2:"<<a.get_predict_particles().toString()<<endl;
    for(int j=0;j<a.get_predict_particles().size();++j)
    {
      for(int i=0;i<x.size();++i)
      {
        cut_assert_equal_double(x[i],10.0, a.get_predict_particles()[j][i]);
      }
    }

  }
  void test_sin_curve(void)
  {
    double t = 0.0;
    Filter a(0.0);
    const unsigned int num_particle = 100;
    a.setNumber(num_particle);
    a.setDimension(1);
    a.set_state_func(&sin_system_func);
    a.set_robserve_func(&sin_reversed_observed_func);
    a.set_robserve_jacobian_func(&sin_reversed_jacobian_func);
    a.set_robserve_density_func(&sin_reversed_observed_density_func);

    a.createInitialParticles();
      // initial value
    for(unsigned int i=0;i<num_particle;++i)
    {
      // initial values should be zero[currently]
      cut_assert_equal_double(0.0, 0.1, a.get_particles()[i][0]);
    }
    for(unsigned l=0;l<100;++l)
    {
      a.create_system_noise(0.0, 1.0);

      for(unsigned int i=0;i<num_particle;++i)
      {
        // initial values should be near zero
        cut_assert_equal_double(0.0, 10.0, a.get_system_noise()[i][0]);
      }

      Particles<double> noise(a.get_system_noise());
      Particles<double> prediction(a.get_predict_particles());

      a.get_next_state();
      Particles<double> predict =  prediction + noise;
      // initial value+system noise(random walk)
      cut_assert_equal_string(predict.toString().c_str(),a.get_predict_particles().toString().c_str());
//cout<<"predict1:"<<predict.toString()<<endl;
      Particles<double> y(num_particle,1);
      Particle<double> x(1);
      for(unsigned int i=0;i<num_particle;++i)
      {
        y[i][0]=sin(t);
      }
    }
  }
}
int main()
{
  test_filter::test_construction();
  return(0);
}
