// Created by Aidin Attar. 2019

// Event.cc

#include "Event.h"

unsigned int Max = 10;

Event::Event( int n, float x, float y, float z ):
 // initializations
 evNumber( n ),
 X( x ), Y( y ), Z( z ),
 nParticles( 0 ){

 // allocate array to contain energies: reserve space for max number
 particles.reserve( Max );

}


Event::~Event() {
}


void Event::add( float Px, float Py, float Pz, int q ) {

  // check for the number of particles, if maximum reached do nothing
  // and return
  if ( nParticles < Max ){

    // create the new particle and fill with data
    Particle* newPar = new Particle;
    newPar->Px = Px;
    newPar->Py = Py;
    newPar->Pz = Pz;
    newPar->q  = q;

    // store the new particle pointer in the array and increase counter
    particles.push_back( newPar );
    ++nParticles;
  }

  return;
}


// get event id.
int Event::eventNumber() const {
  return evNumber;
}


// get decay point coordinates
float Event::getX() const {
  return X;
}

float Event::getY() const {
  return Y;
}

float Event::getZ() const {
  return Z;
}


// get number of particles
int Event::numParticles () const {
  return nParticles;
}


// get particle
const Event:: part_ptr Event::particle( unsigned int i ) const {
  return particles[ i ];
}