/*
 * ©2022 The Regents of the University of California.  All rights reserved.
 */

#include <cstdlib>
#include <cstdio>
#include <vector>
#include <iostream> // std
#include <iomanip>  // setw
#include <fstream>  // fopen
#include <string>
#include <math.h>   // pow
#include <cstring>

#include "tsd.hpp"

/*
 * leak check (mac os x):
 *      leaks -atExit -- tsd
 *      leaks -atExit -- tsd | grep LEAK
 */
using namespace std;

int main(int argc, char** argv) {
    variables *vars = new variables();
    tsd *sonic = new tsd(argc, argv, vars);

    // input
    sonic->readInputParams("tsd.data");

    // discretization
    sonic->setMesh();

    // solve the continuity equations
    sonic->solveScheme();
    sonic->solvePhoPhu();
    sonic->solvePressureCoefs();
    sonic->solveGlobalCoefs();

    // restart file
    sonic->outputRestart("tsd.in");
    sonic->outputCpContour("tsd.cpcon");
    sonic->outputXiCp("tsd.cp");

    // print to screen (uncomment for prints, then rebuild)
    //sonic->printInput();
    sonic->printGlobalResults();

    delete sonic;
    delete vars;
}

