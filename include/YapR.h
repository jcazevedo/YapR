#include <Rembedded.h>
#include <R.h>
#include <Rinternals.h>
#include <R_ext/Parse.h>

void init_R();
void end_R();
SEXP process_expression(char * expression);
