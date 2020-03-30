#include "ParticleMass.h"

#include "Event.h"
#include "MassMean.h"
#include "AnalysisInfo.h"
#include "AnalysisFactory.h"

#include "TH1F.h"
#include "TFile.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>


float massMinK0 = 0.495;
float massMaxK0 = 0.500;
float massMinL0 = 1.115;
float massMaxL0 = 1.116;

// arbitrary bin number
int nBinD = 128;

double mass ( const Event& ev );

// concrete factory to create an ParticleMass analyzer
class ParticleMassFactory: public AnalysisFactory::AbsFactory {
 public:
  // assign "plot" as name for this analyzer and factory
  ParticleMassFactory(): AnalysisFactory::AbsFactory( "plot" ) {}
  // create an ParticleMass when builder is run
  virtual AnalysisSteering* create( const AnalysisInfo* info ) {
    return new ParticleMass( info );
  }
};
// create a global ParticleMassFactory, so that it is created and registered 
// before main execution start:
// when the AnalysisFactory::create function is run,
// an ParticleMassFactory will be available with name "plot".
static ParticleMassFactory er;

ParticleMass::ParticleMass( const AnalysisInfo* info ):
 AnalysisSteering( info ) {
}


ParticleMass::~ParticleMass() {
}


// function to be called at execution start
void ParticleMass::beginJob() {

  // create mass distributions for different particles
  pList.reserve( 10 );
  pCreate( "K0" , massMinK0, massMaxK0 );
  pCreate( "L0" , massMinL0, massMaxL0 );

  return;

}


// function to be called at execution end
void ParticleMass::endJob() {
  // save current working area
  TDirectory* currentDir = gDirectory;
  // open histogram file
  TFile* file = new TFile( aInfo->value( "plot" ).c_str(), "RECREATE" );

  // loop over elements
  int n = pList.size();
  int i;
  for ( i = 0; i < n; ++i ) {
    // get mass informations
    MassMean* pMean = pList[i]->pMean;
    TH1F*     hMean = pList[i]->hMean;
    // compute results
    pMean->compute();
    // get mean and rms mass
    double mean = pMean->mMeanM();
    double rms  = pMean->mRMS  ();

    // print results
    std::cout << pMean->nEvents() << ' ' 
              << mean             << ' ' 
              << rms              << std::endl;
    
    // print number of events
//    std::cout << pMean->nEvents() << std::endl;
    // save distribution
    hMean->Write();
  }

  // close file
  file->Close();
  delete file;
  // restore working area
  currentDir->cd();

  return;

}


// function to be called for each event
void ParticleMass::process( const Event& ev ) {
  // loop over mass distributions and pass event to each of them
  unsigned int n = pList.size();
  unsigned int i;
//  int iBinD;
  
  for ( i = 0; i < n; ++i ){
    // get mass informations
    MassMean* pMean = pList[i]->pMean;
    TH1F*     hMean = pList[i]->hMean;

    if( pMean->add( ev ) == true )
      // set center values in the graph
      // by using SetBinContent, bin count starts from 1
      hMean->Fill( mass( ev ) );
  }
  return;
}


void ParticleMass::pCreate( const std::string& name, float min, float max ) {

  // create mass distribution for events with mass in given range

  // create name for TH1F object
  const char* hName = name.c_str();

  // create TH1F and statistic objects and store their pointers
  Particle* pm = new Particle;
  pm-> name = name;
  pm->pMean = new MassMean( min, max );
  pm->hMean = new TH1F( hName, hName, nBinD, min, max );
  pList.push_back( pm );

  return;

}