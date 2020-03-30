// Created by Aidin Attar. 2019

// MassMean.cc

#include "MassMean.h"
#include "Event.h"

#include <cmath>

double mass( const Event& ev );

MassMean::MassMean( float min, float max ):
 // initializations
  massMin( min ),
  massMax( max ),
  nEvt( 0 ),
  sum( 0 ), sqr( 0 ),
  mean( 0 ), rms( 0 ){
}


MassMean::~MassMean() {
}


// add data from a new event
bool MassMean::add( const Event& ev ) {
  double Mass = mass( ev );

  // check for mass being in range
  if ( Mass < massMin || Mass > massMax ) 
    return false;

  // update number of events and sums
  ++nEvt;
  sum += Mass;
  sqr += Mass * Mass;

  return true;

}


// compute mean and rms
void MassMean::compute() {
  double v;

  mean =   sum * 1.0 / nEvt;
  v    = ( sqr * 1.0 / nEvt ) - ( mean * mean );
  rms  = ( v > 0 ? sqrt ( v ) : 0.0 );
}


// return number of selected events
int MassMean::nEvents(){
  return nEvt;
}


// return mean
double MassMean::mMeanM(){
  return mean;
}

// return rms
double MassMean::mRMS(){
  return rms;
}