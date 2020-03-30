// Created by Aidin Attar. 2019

// MassMean.h

#ifndef MassMean_h
#define MassMean_h

class Event;

class MassMean {

 public:

  MassMean( float min, float max ); // mass range
  ~MassMean();

  bool add( const Event& ev );      // add data from a new event
  void compute();                   // compute mean and rms

  int    nEvents(); // return number of accepted events
  double mMeanM(); // return mean mass
  double mRMS(); // return rms  mass

 private:

  double massMin;  // min mass
  double massMax; // max mass

  int nEvt; // number of accepted events
  double sum; // sum of masses
  double sqr; // sum of masses square

  double mean; // mean mass
  double rms; // rms  mass

};

#endif