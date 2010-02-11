#include <YAP/YAPInterface.h>
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

void init_my_predicates()
{
    YAP_UserCPredicate("double_val", double_val, 2);
}
