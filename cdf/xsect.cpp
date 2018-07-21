#include <iostream>
#include <fstream>

using namespace std;

extern "C" {
  //void zduini_();
  //void zduevt_(int* iwant);
  void fileini_();
  void integrate_();

  extern struct {
    int ipar[20];
    double lpar[20];
  } datapar_;

  extern struct {
    double s1,s2,s3,s4;
  } result_;

}

int main() {

  fileini_();

  // Beam parameters
  datapar_.ipar[4] = 9;
  datapar_.lpar[2] = 3500.;

  // Outgoing leptons kinematics
  datapar_.lpar[4] = 2.5; // eta cut
  datapar_.lpar[5] = 0.; // energy cut
  datapar_.lpar[6] = 0.; // pt cut
  //datapar_.lpar[8] = 1.e6; // invm cut
  //integrate_();

  ofstream cs("tmp/xsec_lpair_doubleinelastic_7tev_v2.dat");
  //ofstream cs("tmp/xsec_lpair_doubleinelastic_8tev_noetacut.dat");
  //ofstream cs("tmp/xsec_lpair_elastic_vs_cm_energy.dat");

  for (int i=0; i<=100; i++) {
    datapar_.lpar[6] = 0.+i*0.5;
    //datapar_.lpar[2] = (i+1)*(14000/50);
    integrate_();

    //cs << datapar_.lpar[2] << "\t" << result_.s1 << "\t" << result_.s2 << endl;
    //std::cout << "sqrt(s) = " << datapar_.lpar[2] << " GeV : xsec = " << result_.s1 << ", error = " << result_.s2 << std::endl;

    cs << datapar_.lpar[6] << "\t" << result_.s1 << "\t" << result_.s2 << endl;
    std::cout << "Pt > " << datapar_.lpar[6] << " GeV : xsec = " << result_.s1 << ", error = " << result_.s2 << std::endl;  
  }

  return 0;
}
