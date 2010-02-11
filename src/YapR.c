#include <YapR.h>

void init_R(int argc, char **argv)
{
    int defaultArgc = 1;
    char *defaultArgv[] = {"Rtest"};

    if (argc == 0 || argv == NULL) 
    {
	    argc = defaultArgc;
	    argv = defaultArgv;
    }
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

    init_R(0, NULL);

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

    end_R();
    return result;
}
