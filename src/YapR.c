#include <YapR.h>

void init_R()
{
    int argc = 2;
	char * argv[] = {"R", "--silent"};

    Rf_initEmbeddedR(argc, argv);
}

void end_R()
{
    Rf_endEmbeddedR(0);
    R_dot_Last();
    R_RunExitFinalizers();
    R_gc();
}

SEXP process_expression(char * expression)
{
    SEXP e, tmp, val;
    int hadError;
    ParseStatus status;

    PROTECT(tmp = mkString(expression));
    PROTECT(e = R_ParseVector(tmp, 1, &status, R_NilValue));
    val = R_tryEval(VECTOR_ELT(e, 0), R_GlobalEnv, &hadError);
    UNPROTECT(2);

    if (!hadError)
        return val;
    return NULL;
}
