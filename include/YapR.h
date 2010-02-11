#include <Rembedded.h>
#include <R.h>
#include <Rinternals.h>
#include <R_ext/Parse.h>

void init_R(int argc, char ** argv);
void end_R();
double get_double(char * expression);
