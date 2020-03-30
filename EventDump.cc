#include "EventDump.h"
#include "Event.h"
#include "AnalysisFactory.h"

#include <iostream>
#include <math.h>
#include <stdio.h>

using namespace std;

// concrete factory to create an EventDump analyzer
class EventDumpFactory: public AnalysisFactory::AbsFactory {
 public:
  // assign "dump" as name for this analyzer and factory
  EventDumpFactory(): AnalysisFactory::AbsFactory( "dump" ) {}
  // create an EventDump when builder is run
  virtual AnalysisSteering* create( const AnalysisInfo* info ) {
    return new EventDump( info );
  }
};
// create a global EventDumpFactory, so that it is created and registered 
// before main execution start:
// when the AnalysisFactory::create function is run,
// an EventDumpFactory will be available with name "dump".
static EventDumpFactory ed;

EventDump::EventDump( const AnalysisInfo* info ):
 AnalysisSteering( info ) {
}


EventDump::~EventDump() {
}


// function to be called at execution start
void EventDump::beginJob() {
  return;
}


// function to be called at execution end
void EventDump::endJob() {
  return;
}


// function to be called for each event
void EventDump::process( const Event& ev ) {

    // write event number, 3 decay point coordinates and number
    // of particles
    std::cout << ev.eventNumber() << std::endl
              << ev.getX() << ' '
              << ev.getY() << ' '
              << ev.getZ() << std::endl
              << ev.numParticles() << std::endl;

    // write charge and 3 momentum components for every particle
    for( int i = 0; i < ev.numParticles(); ++i)
        std::cout << ev.particle( i )->q  << ' '
                  << ev.particle( i )->Px << ' '
                  << ev.particle( i )->Py << ' '
                  << ev.particle( i )->Pz << std::endl;

    return;
}

