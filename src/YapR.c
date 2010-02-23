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

static SEXP process_expression(char * expression)
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

double get_double(char * expression)
{
    double result;
    SEXP val = process_expression(expression);

    if (val != NULL)
    {
        PROTECT(val);
        result = REAL(val)[0];
        UNPROTECT(1);
    }

    return result;
}

int get_int(char * expression)
{
    int result;
    SEXP val = process_expression(expression);

    if (val != NULL)
    {
        if (isInteger(val))
        {
            PROTECT(val);
            result = INTEGER(val)[0];
            UNPROTECT(1);
        }
        else
        {
            PROTECT(val);
            result = (int) REAL(val)[0];
            UNPROTECT(1);
        }
    }

    return result;
}

list get_list(char * expression)
{
    list l;
    int i;
    SEXP val = process_expression(expression);
    l.size = LENGTH(val);

    SEXP dims = getAttrib(val, R_DimSymbol);
    if (dims == R_NilValue)
    {
        l.nDims = 1;
        l.dims[0] = l.size;
    }
    else
    {
        l.nDims = LENGTH(dims);
        for (i = 0; i < l.nDims; i++)
        {
            PROTECT(dims);
            l.dims[i] = INTEGER(dims)[i];
            UNPROTECT(1);
        }
    }

    for (i = 0; i < l.size; i++)
    {
        if (isInteger(val))
        {
            PROTECT(val);
            strcpy(l.values[i].type, "int");
            l.values[i].int_val = INTEGER(val)[i];
            UNPROTECT(1);
        }
        else if (isReal(val))
        {
            PROTECT(val);
            strcpy(l.values[i].type, "double");
            l.values[i].double_val = REAL(val)[i];
            UNPROTECT(1);
        }
    }

    return l;
}
