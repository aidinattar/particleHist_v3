// Created by Aidin Attar. 2019

// Utilities.h

#include <cmath>

#ifndef Utilities_h
#define Utilities_h

struct Utilities {

    static inline double restMass ( float Px, float Py, float Pz,
                                    double en ){
                      
        double Ptot = sqrt ( pow ( Px, 2 ) +
                             pow ( Py, 2 ) +
                             pow ( Pz, 2 ) );

        return sqrt ( pow ( en,   2 ) -
                      pow ( Ptot, 2) );

    }

    static inline double energy   ( float Px, float Py, float Pz,
                                    double invMass){

        double Ptot = sqrt ( pow ( Px, 2 ) +
                             pow ( Py, 2 ) +
                             pow ( Pz, 2 ) );

        return sqrt ( pow ( invMass, 2 ) +
                      pow ( Ptot,    2 ) );

    }

};

#endif