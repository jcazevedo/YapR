#include <YAP/YAPInterface.h>
#include <YAP/c_interface.h>
#include <YapR.h>

#define BUFSIZE 256

static int double_val(void)
{
    YAP_Term in = YAP_ARG1;
    YAP_Term out = YAP_ARG2;
    char buffer[256];

    YAP_StringToBuffer(in, buffer, BUFSIZE);
    YAP_Term res = YAP_MkFloatTerm(get_double(buffer));

    return YAP_Unify(out, res);
}

static int int_val(void)
{
    YAP_Term in = YAP_ARG1;
    YAP_Term out = YAP_ARG2;
    char buffer[256];

    YAP_StringToBuffer(in, buffer, BUFSIZE);
    YAP_Term res = YAP_MkIntTerm(get_int(buffer));

    return YAP_Unify(out, res);
}

static int init_r(void)
{
    init_R();

    return 1;
}

void init_my_predicates()
{
    YAP_UserCPredicate("double_val", double_val, 2);
    YAP_UserCPredicate("int_val", int_val, 2);
    YAP_UserCPredicate("init_r", init_r, 0);
}
