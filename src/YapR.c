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

double get_double(char * expression)
{
    SEXP e, tmp, val;
    int hadError;
    double result;
    ParseStatus status;

    PROTECT(tmp = mkString(expression));
    PROTECT(e = R_ParseVector(tmp, 1, &status, R_NilValue));
    val = R_tryEval(VECTOR_ELT(e, 0), R_GlobalEnv, &hadError);
    UNPROTECT(2);

    if (!hadError)
    {
        PROTECT(val);
        result = REAL(val)[0];
        UNPROTECT(1);
    }

    return result;
}
