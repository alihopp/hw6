#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

void runge(double* k, const double a, const double b, const double c, double x, double y, double z)
{
  k[0]= a*(y-x);
  k[1]= x*(b-z)-y;
  k[2]= x*y-c*z;
}

// main function
int main()
{
  // defining variables and intial condition
  const double t_init=0.0, t_end=100.0;
  const double dt=0.05;

  const int N=((t_end-t_init)/dt)+1;
  
  const double a=10, b=28, c=8/3;
  double x=1, y=1, z=1;

  double k1[3], k2[3], k3[3], k4[3];


  // printing all values (x,y,z) in the file "Lorentz_model"
  ofstream out("Lorentz_model:dt=0.05.txt");

  out << t_init << "\t" << x << "\t" << y << "\t" << z << endl;


  // implementation of 4th order Runge scheme with saving in file
  for(int i=1; i<N; i++)
    {
      runge(k1,a,b,c,x,y,z);
      runge(k2,a,b,c,x+(dt/2)*k1[0],y+(dt/2)*k1[1],z+(dt/2)*k1[2]);
      runge(k3,a,b,c,x+(dt/2)*k2[0],y+(dt/2)*k2[1],z+(dt/2)*k2[2]);
      runge(k4,a,b,c,x+dt*k3[0],y+dt*k3[1],z+dt*k3[2]);

      x+= (dt/6)*(k1[0]+ 2*k2[0]+ 2*k3[0]+ k4[0]);
      y+= (dt/6)*(k1[1]+ 2*k2[1]+ 2*k3[1]+ k4[1]);
      z+= (dt/6)*(k1[2]+ 2*k2[2]+ 2*k3[2]+ k4[2]);

      out << i*dt << "\t" << x << "\t" << y << "\t" << z << endl;
    }

  out.close();
  return 0;
}
