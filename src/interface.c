#include <YAP/YAPInterface.h>
#include <YAP/c_interface.h>
#include <YapR.h>
#include <string.h>

static int float_val(void)
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

static YAP_Term get_term(list_cell cell)
{
    if (strncmp(cell.type, "int", 3) == 0)
        return YAP_MkIntTerm(cell.int_val);
    else if (strncmp(cell.type, "double", 6) == 0)
        return YAP_MkFloatTerm(cell.double_val);
    return YAP_MkIntTerm(0);
}

static YAP_Term build_list(list l, int current_pos)
{
    if (l.nDims > 1)
    {
        YAP_Term curr_term = YAP_MkAtomTerm(YAP_LookupAtom("[]"));
        int cDims = l.dims[0], i, j, k, inc = cDims;

        for (i = cDims - 1; i >= 0; i--)
        {
            list newL;
            newL.nDims = l.nDims - 1;
            newL.size = l.size / cDims;
            k = 0;

            for (j = 1; j < l.nDims; j++)
                newL.dims[j - 1] = l.dims[j];
            for (j = i; j < l.size; j += inc)
                newL.values[k++] = l.values[j];

            curr_term = YAP_MkPairTerm(build_list(newL, 0), curr_term);
        }

        return curr_term;
    }
    else
    {
        YAP_Term curr_term = get_term(l.values[current_pos]);
        if (current_pos == l.size - 1)
            return curr_term;
        else
            return YAP_MkPairTerm(curr_term, build_list(l, current_pos + 1));
    }
}

static int list_val(void)
{
    YAP_Term in = YAP_ARG1;
    YAP_Term out = YAP_ARG2;
    char buffer[256];

    YAP_StringToBuffer(in, buffer, BUFSIZE);
    YAP_Term res = build_list(get_list(buffer), 0);

    return YAP_Unify(out, res);
}

static int send_r_command(void)
{
    YAP_Term in = YAP_ARG1;
    char buffer[256];

    YAP_StringToBuffer(in, buffer, BUFSIZE);
    send_command(buffer);

    return 1;
}

static int init_r(void)
{
    init_R();

    return 1;
}

void init_my_predicates()
{
    YAP_UserCPredicate("float_val", float_val, 2);
    YAP_UserCPredicate("int_val", int_val, 2);
    YAP_UserCPredicate("list_val", list_val, 2);
    YAP_UserCPredicate("init_r", init_r, 0);
    YAP_UserCPredicate("send_r_command", send_r_command, 1);
}
