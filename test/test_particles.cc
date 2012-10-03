#include <cppcutter.h>
#include <particles.h>
#include <iostream>
using namespace std;

namespace test_particles
{
  void cut_setup()
  {
  }
  void cut_teardown()
  {
  }

  void test_construction(void)
  {
    Particles<int> a(3);
    Particle<int> dummy(5);
    for(int j=1;j<=3;++j)
    {
      for(int i=1;i<=5;++i)
      {
        dummy[i-1]=j*10+i;
      }
      a[j-1] = dummy;
    }
    for(int j=1;j<=3;++j)
    {
      for(int i=1;i<=5;++i)
      {
        cppcut_assert_equal(j*10+i, a[j-1][i-1]);
      }
    }

    Particles<int> b(3,2); // (number, dimension)
    for(int i=0;i<3;++i)
      cut_assert_equal_string("(0,0)", b[i].toString().c_str());
  }
  void test_copyConstructor(void)
  {
    Particles<int> a(3);
    Particle<int> dummy(5);
    for(int j=1;j<=3;++j)
    {
      for(int i=1;i<=5;++i)
      {
        dummy[i-1]=j*10+i;
      }
      a[j-1] = dummy;
    }
    Particles<int> b;
    b = a;
    for(int j=1;j<=3;++j)
    {
      for(int i=1;i<=5;++i)
      {
        cppcut_assert_equal(j*10+i, b[j-1][i-1]);
      }
    }
  }
  void test_plus_equal(void)
  {
    Particles<int> a(3), b(3);
    Particle<int> dummy(5);
    for(int j=1;j<=3;++j)
    {
      for(int i=1;i<=5;++i)
      {
        dummy[i-1]=j*10+i; // 11, 12, 13, 14, 15, 21, 22, ... 55
      }
      a[j-1] = dummy;
      for(int i=1;i<=5;++i)
      {
        dummy[i-1]=j*20+i; // 21, 22, 23, 24, 25, 31, 32, ... 65
      }
      b[j-1] = dummy;
    }
    b += a;
    for(int j=1;j<=3;++j)
    {
      for(int i=1;i<=5;++i)
      {
        cppcut_assert_equal(j*30+2*i, b[j-1][i-1]);
      }
    }
  }
  void test_plus(void)
  {
    Particles<int> a(3), b(3);
    Particle<int> dummy(5);
    for(int j=1;j<=3;++j)
    {
      for(int i=1;i<=5;++i)
      {
        dummy[i-1]=j*10+i; // 11, 12, 13, 14, 15, 21, 22, ... 55
      }
      a[j-1] = dummy;
      for(int i=1;i<=5;++i)
      {
        dummy[i-1]=j*20+i; // 21, 22, 23, 24, 25, 31, 32, ... 65
      }
      b[j-1] = dummy;
    }
    Particles<int> c = a+b;
    for(int j=1;j<=3;++j)
    {
      for(int i=1;i<=5;++i)
      {
        cppcut_assert_equal(j*30+2*i, c[j-1][i-1]);
      }
    }

  }
  void test_manipulate(void)
  {
    Particles<int> b(3,2);
    Particle<int> c(2);
    c[0]=1; c[1]=2;
    cut_assert_equal_string("(1,2)", c.toString().c_str());
    b[0] = c;
    cut_assert_equal_string("(1,2)", b[0].toString().c_str());
    int n=10;
    for(int i=0;i<3;++i)
    {
      for(int j=0;j<2;++j)
      {
        b[i][j] = n++;
      }
    }
    cut_assert_equal_string("(10,11)", b[0].toString().c_str());
    cut_assert_equal_string("(12,13)", b[1].toString().c_str());
    cut_assert_equal_string("(14,15)", b[2].toString().c_str());
//    cppcut_assert_equal(0,b.dump_particles());
  }
  void test_dumping(void)
  {
    Particles<int> a(3,2);
    cppcut_assert_equal(0,a.dump_particles());
  }

}
