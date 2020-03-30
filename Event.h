// Created by Aidin Attar. 2019

// Event.h

#ifndef Event_h
#define Event_h

#include <vector>

class Event {

 public:

  Event( int n, float x, float y, float z ); // create an event with number "n"
                                             // and coordinates x, y, z
  ~Event();

  // composite object Particle to hold all information for each particle
  // ( x,y,z momentum components and electric charge )
  struct Particle {

    int q; // charge
    float Px; float Py; float Pz; // momentum components
  
  };
  typedef const Particle* part_ptr;

  // add a particle to the event
  void add( float Px, float Py, float Pz, int q );

  // get event id.
  int eventNumber() const;
  // get decay point coordinates
  float getX() const;
  float getY() const;
  float getZ() const;
  // get number of particles
  int numParticles() const;
  // get particle
  const part_ptr particle( unsigned int i ) const;

 private:

  // event-specific informations:
  int evNumber; // event id
  float X; float Y; float Z;  // decay point
  unsigned int nParticles;   // number of particles
  std::vector <part_ptr> particles; 

};

#endif