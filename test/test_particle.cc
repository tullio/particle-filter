#include <cppcutter.h>
#include <particle.h>
#include <iostream>

using namespace std;

namespace test_particle
{

  void cut_setup()
  {
  }
  void cut_teardown()
  {
  }

  void test_construction(void)
  {
    Particle<int> a(5);
    for(int i=1;i<=5;++i) a[i-1]=i;
    cut_assert_equal_int(5,a.size());
    cut_assert_equal_string("(1,2,3,4,5)",a.toString().c_str());

    Particle<int> c(5);
    cut_assert_equal_string("(0,0,0,0,0)",c.toString().c_str());
    for(int i=1;i<5;++i) cut_assert_equal_int(i, a[i-1]);
  }
  void test_toVector(void)
  {
    Particle<int> a(5);
    for(int i=1;i<=5;++i) a[i-1]=i;

    vector<int> p = a.toVector();
    cppcut_assert_equal(5, (int)p.size());
    for(int i=1;i<=5;++i) cut_assert_equal_int(i, p.at(i-1));
  }
  void test_plus_equal(void)
  {
    Particle<int> a(5), b(5);
    for(int i=1;i<=5;++i)
    {
      a[i-1]=i; // 1, 2, 3, 4, 5
      b[i-1]=2-i; // 1, 0, -1, -2, -3
    }
    a += b;
    for(int i=0;i<4;++i) cut_assert_equal_int(2, a[i]);

  }
  void test_plus(void)
  {
    Particle<int> a(5), b(5);
    for(int i=1;i<=5;++i)
    {
      a[i-1]=i; // 1, 2, 3, 4, 5
      b[i-1]=2-i; // 1, 0, -1, -2, -3
    }
    Particle<int> c = a + b;
    for(int i=0;i<4;++i) cut_assert_equal_int(2, c[i]);

  }
  void test_copyConstructor(void)
  {
    Particle<int> a(5);
    for(int i=1;i<=5;++i) a[i-1]=i;

    Particle<int> b;
    b = a;
    for(int i=1;i<=5;++i) cut_assert_equal_int(i, b[i-1]);
  }
  void test_MersennneTwister(void)
  {
    MTRand r;
    cout<<r.randInt()<<endl;
  }
  void test_dumping(void)
  {
    Particle<int> a(5);
    cut_assert_equal_string("(0,0,0,0,0)",a.toString().c_str());
  }
}
