#include <cppcutter.h>
#include <particle.h>
#include <iostream>
using namespace std;
void test_particl(void);


void cut_setup()
{
  cout<<"setup"<<endl;
}
void cut_teardown()
{
}

int test_true()
{
  return(1);
}

void test_particl(void)
{
  Particle *a = new Particle();
  cppcut_assert_equal(0, 0);
  cut_assert(a!=NULL);
  cut_assert(test_true());
}
