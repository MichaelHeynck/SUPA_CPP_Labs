#include <iostream>
#include <string>
#include <vector>
#include "FiniteFunctions.h"
#include <filesystem> //To check extensions in a nice way
#include <math.h>
#include <random>

#include "gnuplot-iostream.h" //Needed to produce plots (not part of the course) 

using std::filesystem::path;


//Empty constructor
FiniteFunction::FiniteFunction(){
  m_RMin = -5.0;
  m_RMax = 5.0;
  this->checkPath("DefaultFunction");
  m_Integral = NULL;
}

//initialised constructor
FiniteFunction::FiniteFunction(double range_min, double range_max, std::string outfile){
  m_RMin = range_min;
  m_RMax = range_max;
  m_Integral = NULL;
  this->checkPath(outfile); //Use provided string to name output files
}

//Plots are called in the destructor
//SUPACPP note: They syntax of the plotting code is not part of the course
FiniteFunction::~FiniteFunction(){
  Gnuplot gp; //Set up gnuplot object
  this->generatePlot(gp); //Generate the plot and save it to a png using "outfile" for naming 
}

NormalDistributionFunction::NormalDistributionFunction() : FiniteFunction(){
  pm_mu=0;
  pm_sigma=1;
  this->checkPath("NormalDistributionFunction");
};

NormalDistributionFunction::NormalDistributionFunction(double range_min, double range_max, double mu, double sigma, std::string outfile) : FiniteFunction(range_min, range_max, outfile){  
  if(sigma<=0){
    pm_sigma=1;
    std::cout<<"sigma has to be larger than 0, set it to 1."<<std::endl;
  }
  else{
    pm_sigma=sigma;
  }
  pm_mu=mu;
  
};

NormalDistributionFunction::~NormalDistributionFunction(){
  Gnuplot gp; //Set up gnuplot object
  this->generatePlot(gp); //Generate the plot and save it to a png using "outfile" for naming 
}

CauchyLorentzFunction::CauchyLorentzFunction() : FiniteFunction(){
  pm_x0=0;
  pm_gamma=1;
  this->checkPath("CauchyLorentzFunction");
};

CauchyLorentzFunction::CauchyLorentzFunction(double range_min, double range_max, double x0, double gamma, std::string outfile) : FiniteFunction(range_min, range_max, outfile){  
  if(gamma<=0){
    pm_gamma=1;
    std::cout<<"gamma has to be larger than zero, set it to 1."<<std::endl;
  }
  else{
    pm_gamma=gamma;
  }
  pm_x0=x0;
};

CauchyLorentzFunction::~CauchyLorentzFunction(){
  Gnuplot gp; //Set up gnuplot object
  this->generatePlot(gp); //Generate the plot and save it to a png using "outfile" for naming 
}

NegativeCrystalBallDistribution::NegativeCrystalBallDistribution() : FiniteFunction(){
  pm_x0=0;
  pm_n=2;
  pm_alpha=1;
  pm_sigma=1;
  this->checkPath("NegativeCrystalBallDistribution");
};

NegativeCrystalBallDistribution::NegativeCrystalBallDistribution(double range_min, double range_max, double x0, double n, double alpha, double sigma, std::string outfile) : FiniteFunction(range_min, range_max, outfile){  
  if(n<=1){
    pm_n=2;
    std::cout<<"n has to be larger than 1, set it to 2."<<std::endl;
  }
  else{
    pm_n=n;
  }

  if(alpha<0){
    pm_alpha=1;
    std::cout<<"alpha has to be larger than 0, set it to 1."<<std::endl;
  }
  else{
    pm_alpha=alpha;
  }

  if(sigma<0){
    pm_sigma=1;
    std::cout<<"sigma has to be larger than 0, set it to 1."<<std::endl;
  }
  else{
    pm_sigma=sigma;
  }

  pm_x0=x0;
};

NegativeCrystalBallDistribution::~NegativeCrystalBallDistribution(){
  Gnuplot gp; //Set up gnuplot object
  this->generatePlot(gp); //Generate the plot and save it to a png using "outfile" for naming 
}

/*
###################
//Setters
###################
*/ 
void FiniteFunction::setRangeMin(double RMin) {m_RMin = RMin;};
void FiniteFunction::setRangeMax(double RMax) {m_RMax = RMax;};
void FiniteFunction::setOutfile(std::string Outfile) {this->checkPath(Outfile);};

void NormalDistributionFunction::setMu(double mu) {pm_mu = mu;};
void NormalDistributionFunction::setSigma(double sigma){
  if(sigma<=0){
    pm_sigma=1;
    std::cout<<"sigma has to be larger than 0, set it to 1."<<std::endl;
  } 
  else{
    pm_sigma = sigma;
  }
};

void CauchyLorentzFunction::setX0(double x0) {pm_x0 = x0;};
void CauchyLorentzFunction::setGamma(double gamma){
  if(gamma<=0){
    pm_gamma=1;
    std::cout<<"gamma has to be larger than 0, set it to 1."<<std::endl;
  } 
  else{
    pm_gamma = gamma;
  }
};

void NegativeCrystalBallDistribution::setX0(double x0) {pm_x0 = x0;};
void NegativeCrystalBallDistribution::setN(double n){
  if(n<=1){
    pm_n=2;
    std::cout<<"n has to be larger than 1, set it to 2."<<std::endl;
  } 
  else{
    pm_n = n;
  }
};
void NegativeCrystalBallDistribution::setAlpha(double alpha){
  if(alpha<=0){
    pm_alpha=1;
    std::cout<<"alpha has to be larger than 0, set it to 1."<<std::endl;
  } 
  else{
    pm_alpha = alpha;
  }
};
void NegativeCrystalBallDistribution::setSigma(double sigma){
  if(sigma<=0){
    pm_sigma=1;
    std::cout<<"sigma has to be larger than 0, set it to 1."<<std::endl;
  } 
  else{
    pm_sigma = sigma;
  }
};

/*
###################
//Getters
###################s
*/ 
double FiniteFunction::rangeMin() {return m_RMin;};
double FiniteFunction::rangeMax() {return m_RMax;};

double NormalDistributionFunction::getMu() {return pm_mu;};
double NormalDistributionFunction::getSigma() {return pm_sigma;};

double NegativeCrystalBallDistribution::getX0() {return pm_x0;};
double NegativeCrystalBallDistribution::getN() {return pm_n;};
double NegativeCrystalBallDistribution::getAlpha() {return pm_alpha;};
double NegativeCrystalBallDistribution::getSigma() {return pm_sigma;};

/*
###################
//Function eval
###################
*/ 
double FiniteFunction::invxsquared(double x) {return 1/(1+x*x);};
double FiniteFunction::callFunction(double x) {return this->invxsquared(x);}; //(overridable)


double NormalDistributionFunction::normalDistribution(double x){
 return ( 1/(pm_sigma*std::sqrt(2*M_PI)) )*std::exp(-0.5*(x-pm_mu)*(x-pm_mu)/(pm_sigma*pm_sigma));
};

double NormalDistributionFunction::callFunction(double x){
  return this->normalDistribution(x);
};

double CauchyLorentzFunction::CauchyLorentzDistributionFunction(double x){
 return 1/( M_PI*pm_gamma*(1+((x-pm_x0)/pm_gamma)*((x-pm_x0)/pm_gamma)) );
};

double CauchyLorentzFunction::callFunction(double x){
  return this->CauchyLorentzDistributionFunction(x);
};

double NegativeCrystalBallDistribution::NegativeCrystalBallDistributionFunction(double x){
  
  double exp1, A, B, C, D, N;
  
  exp1=(x-pm_x0)/pm_sigma;

  C=pm_n/pm_alpha*(1/(pm_n-1))*std::exp(-pm_alpha*pm_alpha/2);
  D=sqrt(M_PI/2)*(1+std::erf(pm_alpha/std::sqrt(2)));
  N=1/(pm_sigma*(C+D)); 

  if(exp1>-pm_alpha){
     return N*std::exp(-exp1*exp1/2);
  }
  else{
    A=pow((pm_n/pm_alpha), pm_n)*exp(-pm_alpha*pm_alpha/2);
    B=pm_n/pm_alpha-pm_alpha;
    return N*A*std::pow(B-exp1, -pm_n);
  }
};

double NegativeCrystalBallDistribution::callFunction(double x){
  return this->NegativeCrystalBallDistributionFunction(x);
};
/*
###################
Integration by hand (output needed to normalise function when plotting)
###################
*/ 
// Integrate a function using the trapezoidal sum
double FiniteFunction::integrate(int Ndiv){ //private
  double step = (m_RMax - m_RMin)/(double)Ndiv;
  double x = m_RMin;
  double integralResult=0;


  for (int i = 0; i < Ndiv; i++){
    integralResult+=( (this->callFunction(x)+this->callFunction(x+step))*step/2 );
    x += step;
  } 
  return integralResult;
}
double FiniteFunction::integral(int Ndiv) { //public
  if (Ndiv <= 0){
    std::cout << "Invalid number of divisions for integral, setting Ndiv to 1000" <<std::endl;
    Ndiv = 1000;
  }
  if (m_Integral == NULL || Ndiv != m_IntDiv){
    m_IntDiv = Ndiv;
    m_Integral = this->integrate(Ndiv);
    return m_Integral;
  }
  else return m_Integral; //Don't bother re-calculating integral if Ndiv is the same as the last call
}


std::vector<double> FiniteFunction::metropolis(int length, float width=1){

  std::vector<double> vector;
  float seed, y, A, T, f_tmp;

  std::random_device rd;
  std::mt19937 mtEngine{rd()};
  std::uniform_real_distribution<float> uniformPDF{m_RMin, m_RMax};
  std::uniform_real_distribution<float> uniformPDF_0to1{0,1};

  seed=uniformPDF(mtEngine);

  for(int i=0; i<length; i++){
    std::normal_distribution<float> gaussianPDF{seed, width};

    y=gaussianPDF(mtEngine);
    f_tmp=this->callFunction(y)/this->callFunction(seed);
    if(f_tmp<=1){
      A=f_tmp;
    }
    else{
      A=1;
    }
    T=uniformPDF_0to1(mtEngine);
    if(T<A){
      vector.push_back(y);
      seed=y;
    }
    else{
      vector.push_back(seed);
    }
  }
  	
  return vector;
}


/*
###################
//Helper functions 
###################
*/
// Generate paths from user defined stem
void FiniteFunction::checkPath(std::string outfile){
 path fp = outfile;
 m_FunctionName = fp.stem(); 
 m_OutData = m_FunctionName+".data";
 m_OutPng = m_FunctionName+".png";
}

//Print (overridable)
void FiniteFunction::printInfo(){
  std::cout << "--------------------"<< std::endl;
  std::cout << "rangeMin: " << m_RMin << std::endl;
  std::cout << "rangeMax: " << m_RMax << std::endl;
  std::cout << "integral: " << m_Integral << ", calculated using " << m_IntDiv << " divisions" << std::endl;
  std::cout << "function: " << m_FunctionName << std::endl;
  std::cout << "--------------------"<< std::endl;
}

void NormalDistributionFunction::printInfo(){
  std::cout << "--------------------"<< std::endl;
  std::cout << "rangeMin: " << m_RMin << std::endl;
  std::cout << "rangeMax: " << m_RMax << std::endl;
  std::cout << "mu: " << pm_mu << std::endl;
  std::cout << "sigma: " << pm_sigma << std::endl;
  std::cout << "integral: " << m_Integral << ", calculated using " << m_IntDiv << " divisions" << std::endl;
  std::cout << "function: " << m_FunctionName << std::endl;
  std::cout << "--------------------"<< std::endl;
}

void CauchyLorentzFunction::printInfo(){
  std::cout << "--------------------"<< std::endl;
  std::cout << "rangeMin: " << m_RMin << std::endl;
  std::cout << "rangeMax: " << m_RMax << std::endl;
  std::cout << "x0: " << pm_x0 << std::endl;
  std::cout << "gamma: " << pm_gamma << std::endl;
  std::cout << "integral: " << m_Integral << ", calculated using " << m_IntDiv << " divisions" << std::endl;
  std::cout << "function: " << m_FunctionName << std::endl;
  std::cout << "--------------------"<< std::endl;
}

void NegativeCrystalBallDistribution::printInfo(){
  std::cout << "--------------------"<< std::endl;
  std::cout << "rangeMin: " << m_RMin << std::endl;
  std::cout << "rangeMax: " << m_RMax << std::endl;
  std::cout << "x0: " << pm_x0 << std::endl;
  std::cout << "n: " << pm_n << std::endl;
  std::cout << "alpha: " << pm_alpha << std::endl;
  std::cout << "sigma: " << pm_sigma << std::endl;
  std::cout << "integral: " << m_Integral << ", calculated using " << m_IntDiv << " divisions" << std::endl;
  std::cout << "function: " << m_FunctionName << std::endl;
  std::cout << "--------------------"<< std::endl;
}

/*
###################
//Plotting
###################
*/

//Hack because gnuplot-io can't read in custom functions, just scan over function and connect points with a line... 
void FiniteFunction::plotFunction(){
  m_function_scan = this->scanFunction(10000);
  m_plotfunction = true;
}

//Transform data points into a format gnuplot can use (histogram) and set flag to enable drawing of data to output plot
//set isdata to true (default) to plot data points in black, set to false to plot sample points in blue
void FiniteFunction::plotData(std::vector<double> &points, int Nbins, bool isdata){
  if (isdata){
    m_data = this->makeHist(points,Nbins);
    m_plotdatapoints = true;
  }
  else{
    m_samples = this->makeHist(points,Nbins);
    m_plotsamplepoints = true;
  }
}


/*
  #######################################################################################################
  ## SUPACPP Note:
  ## The three helper functions below are needed to get the correct format for plotting with gnuplot
  ## In theory you shouldn't have to touch them
  ## However it might be helpful to read through them and understand what they are doing
  #######################################################################################################
 */

//Scan over range of function using range/Nscan steps (just a hack so we can plot the function)
std::vector< std::pair<double,double> > FiniteFunction::scanFunction(int Nscan){
  std::vector< std::pair<double,double> > function_scan;
  double step = (m_RMax - m_RMin)/(double)Nscan;
  double x = m_RMin;
  //We use the integral to normalise the function points
  if (m_Integral == NULL) {
    std::cout << "Integral not set, doing it now" << std::endl;
    this->integral(Nscan);
    std::cout << "integral: " << m_Integral << ", calculated using " << Nscan << " divisions" << std::endl;
  }
  //For each scan point push back the x and y values 
  for (int i = 0; i < Nscan; i++){
    function_scan.push_back( std::make_pair(x,this->callFunction(x)/m_Integral));
    x += step;
  }
  return function_scan;
}

//Function to make histogram out of sampled x-values - use for input data and sampling
std::vector< std::pair<double,double> > FiniteFunction::makeHist(std::vector<double> &points, int Nbins){

  std::vector< std::pair<double,double> > histdata; //Plottable output shape: (midpoint,frequency)
  std::vector<int> bins(Nbins,0); //vector of Nbins ints with default value 0 
  int norm = 0;
  for (double point : points){
    //Get bin index (starting from 0) the point falls into using point value, range, and Nbins
    int bindex = static_cast<int>(floor((point-m_RMin)/((m_RMax-m_RMin)/(double)Nbins)));
    if (bindex<0 || bindex>Nbins-1){
      continue;
    }
    bins[bindex]++; //weight of 1 for each data point
    norm++; //Total number of data points
  }
  double binwidth = (m_RMax-m_RMin)/(double)Nbins;
  for (int i=0; i<Nbins; i++){
    double midpoint = m_RMin + i*binwidth + binwidth/2; //Just put markers at the midpoint rather than drawing bars
    double normdata = bins[i]/((double)norm*binwidth); //Normalise with N = 1/(Ndata*binwidth)
    histdata.push_back(std::make_pair(midpoint,normdata));
  }
  return histdata;
}

//Function which handles generating the gnuplot output, called in destructor
//If an m_plot... flag is set, the we must have filled the related data vector
//SUPACPP note: They syntax of the plotting code is not part of the course
void FiniteFunction::generatePlot(Gnuplot &gp){

  if (m_plotfunction==true && m_plotdatapoints==true && m_plotsamplepoints==true){
    gp << "set terminal pngcairo\n";
    gp << "set output 'Outputs/png/"<<m_FunctionName<<".png'\n"; 
    gp << "set xrange ["<<m_RMin<<":"<<m_RMax<<"]\n";
    gp << "set style line 1 lt 1 lw 2 pi 1 ps 0\n";
    gp << "plot '-' with linespoints ls 1 title '"<<m_FunctionName<<"', '-' with points ps 2 lc rgb 'blue' title 'sampled data', '-' with points ps 1 lc rgb 'black' pt 7 title 'data'\n";
    gp.send1d(m_function_scan);
    gp.send1d(m_samples);
    gp.send1d(m_data);
  }
  else if (m_plotfunction==true && m_plotdatapoints==true){
    gp << "set terminal pngcairo\n";
    gp << "set output 'Outputs/png/"<<m_FunctionName<<".png'\n"; 
    gp << "set xrange ["<<m_RMin<<":"<<m_RMax<<"]\n";
    gp << "set style line 1 lt 1 lw 2 pi 1 ps 0\n";
    gp << "plot '-' with linespoints ls 1 title '"<<m_FunctionName<<"', '-' with points ps 1 lc rgb 'black' pt 7 title 'data'\n";
    gp.send1d(m_data);
    gp.send1d(m_function_scan);
  }
  else if (m_plotfunction==true && m_plotsamplepoints==true){
    gp << "set terminal pngcairo\n";
    gp << "set output 'Outputs/png/"<<m_FunctionName<<".png'\n"; 
    gp << "set xrange ["<<m_RMin<<":"<<m_RMax<<"]\n";
    gp << "set style line 1 lt 1 lw 2 pi 1 ps 0\n";
    gp << "plot '-' with linespoints ls 1 title '"<<m_FunctionName<<"', '-' with points ps 2 lc rgb 'blue' title 'sampled data'\n";
    gp.send1d(m_function_scan);
    gp.send1d(m_samples);
  }
  else if (m_plotfunction==true){
    gp << "set terminal pngcairo\n";
    gp << "set output 'Outputs/png/"<<m_FunctionName<<".png'\n"; 
    gp << "set xrange ["<<m_RMin<<":"<<m_RMax<<"]\n";
    gp << "set style line 1 lt 1 lw 2 pi 1 ps 0\n";
    gp << "plot '-' with linespoints ls 1 title 'function'\n";
    gp.send1d(m_function_scan);
  }

  else if (m_plotdatapoints == true){
    gp << "set terminal pngcairo\n";
    gp << "set output 'Outputs/png/"<<m_FunctionName<<".png'\n"; 
    gp << "set xrange ["<<m_RMin<<":"<<m_RMax<<"]\n";
    gp << "plot '-' with points ps 1 lc rgb 'black' pt 7 title 'data'\n";
    gp.send1d(m_data);
  }

  else if (m_plotsamplepoints == true){
    gp << "set terminal pngcairo\n";
    gp << "set output 'Outputs/png/"<<m_FunctionName<<".png'\n"; 
    gp << "set xrange ["<<m_RMin<<":"<<m_RMax<<"]\n";
    gp << "plot '-' with points ps 2 lc rgb 'blue' title 'sampled data'\n";
    gp.send1d(m_samples);
  }
}
