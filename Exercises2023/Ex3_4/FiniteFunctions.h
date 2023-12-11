#include <string>
#include <vector>
#include "gnuplot-iostream.h"

#pragma once //Replacement for IFNDEF

class FiniteFunction{

public:
  FiniteFunction(); //Empty constructor
  FiniteFunction(double range_min, double range_max, std::string outfile); //Variable constructor
  ~FiniteFunction(); //Destructor
  double rangeMin(); //Low end of the range the function is defined within
  double rangeMax(); //High end of the range the function is defined within
  double integral(int Ndiv = 1000); 
  std::vector< std::pair<double,double> > scanFunction(int Nscan = 1000); //Scan over function to plot it (slight hack needed to plot function in gnuplot)
  void setRangeMin(double RMin); 
  void setRangeMax(double RMax);
  void setOutfile(std::string outfile);
  void plotFunction(); //Plot the function using scanFunction
  
  std::vector<double> metropolis(int length, float width); //use the metropolis algorithm to sample a distribution function
  //Plot the supplied data points (either provided data or points sampled from function) as a histogram using NBins
  void plotData(std::vector<double> &points, int NBins, bool isdata=true); //NB! use isdata flag to pick between data and sampled distributions
  virtual void printInfo(); //Dump parameter info about the current function (Overridable)
  virtual double callFunction(double x); //Call the function with value x (Overridable)

  //Protected members can be accessed by child classes but not users
protected:
  double m_RMin; //Low end of the range the function is defined within
  double m_RMax; //High end of the range the function is defined within
  double m_Integral; //value of the integral within boundaries
  int m_IntDiv = 0; //Number of division for performing integral
  std::string m_FunctionName; //The name of the function
  std::string m_OutData; //Output filename for data
  std::string m_OutPng; //Output filename for plot
  std::vector< std::pair<double,double> > m_data; //input data points to plot
  std::vector< std::pair<double,double> > m_samples; //Holder for randomly sampled data 
  std::vector< std::pair<double,double> > m_function_scan; //holder for data from scanFunction (slight hack needed to plot function in gnuplot)
  bool m_plotfunction = false; //Flag to determine whether to plot function
  bool m_plotdatapoints = false; //Flag to determine whether to plot input data
  bool m_plotsamplepoints = false; //Flag to determine whether to plot sampled data 
  double integrate(int Ndiv); //numerically integrate a function
  std::vector< std::pair<double, double> > makeHist(std::vector<double> &points, int Nbins); //Helper function to turn data points into histogram with Nbins
  void checkPath(std::string outstring); //Helper function to ensure data and png paths are correct
  void generatePlot(Gnuplot &gp); 
  
private:
  double invxsquared(double x); //The default functional form
};


//the class for the normal distribution has FiniteFunction as a base class
//the callFunction() function is overriden. Custom, function relevant paremeters, are added as well 
class NormalDistributionFunction : public FiniteFunction{

public:
  NormalDistributionFunction(); //empty constructor
  NormalDistributionFunction(double range_min, double range_max, double mu, double sigma, std::string outfile); //variable constructor
  ~NormalDistributionFunction();
  double callFunction(double x); //call the function associated to the class
  double getMu(); //get the mu parameter
  double getSigma(); //get the sigma parameter
  void setMu(double mu); //set the mu parameter
  void setSigma(double sigma); //set the sigma parameter
  void printInfo(); //print some info of the function

private:

  double pm_sigma; //sigma parameter
  double pm_mu; //mu parameter
  double normalDistribution(double x); //function that gives bach the normal distribution

};

//the class for the Cauchy Lorentz distribution has FiniteFunction as a base class
//the callFunction() function is overriden. Custom, function relevant paremeters, are added as well 
class CauchyLorentzFunction : public FiniteFunction{

public:
  CauchyLorentzFunction(); //tmpty constructor
  CauchyLorentzFunction(double range_min, double range_max, double x0, double gamma, std::string outfile); //variable constructor
  ~CauchyLorentzFunction(); 
  double callFunction(double x); //calls the function associated to the class
  double getX0(); //get the x0 parameter
  double getGamma(); //get the gamma parameter
  void setX0(double x0); //set the x0 parameter
  void setGamma(double gamma); //set the gamma parameter
  void printInfo(); //print some infos of the function

private:

  double pm_x0; //private x0 parameter
  double pm_gamma; //private gamma parameter
  double CauchyLorentzDistributionFunction(double x); //function used to evaluate the Cauchy Lorentz distribution

};

//the class for the negative crystal ball distribution has FiniteFunction as a base class
//the callFunction() function is overriden. Custom, function relevant paremeters, are added as well 
class NegativeCrystalBallDistribution : public FiniteFunction{

public:
  NegativeCrystalBallDistribution(); //empty constructor
  NegativeCrystalBallDistribution(double range_min, double range_max, double x0, double n, double alpha, double sigma, std::string outfile); // variable constructor
  ~NegativeCrystalBallDistribution();
  double callFunction(double x); //call the function associated with this class
  double getX0(); //get the x0 parameter
  double getN(); //get the n parameter
  double getAlpha(); //get the alpha parameter
  double getSigma(); //get the sigma parameter
  void setX0(double x0); //set the x0 parameter
  void setN(double n); //set the n parameter
  void setAlpha(double alpha); //set the alpha parameter
  void setSigma(double sigma); //set the sigma parameter
  void printInfo(); //print some info about the function

private:

  double pm_x0;
  double pm_n;
  double pm_alpha;
  double pm_sigma;
  double NegativeCrystalBallDistributionFunction(double x);

};