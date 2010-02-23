#include <Rembedded.h>
#include <R.h>
#include <Rinternals.h>
#include <R_ext/Parse.h>

#define BUFSIZE 256

typedef struct
{
    char    type[10];
    int     int_val;
    double  double_val;
    char    char_val[BUFSIZE];
} list_cell;

typedef struct
{
    int         size;
    int         nDims;
    int         dims[BUFSIZE];
    list_cell   values[BUFSIZE];
} list;

void    init_R();
void    end_R();
double  get_double(char * expression);
int     get_int(char * expression);
list    get_list(char * expression);
