module(YapR, init_r/0, float_val/2, int_val/2, list_val/2, r_predicate/3, 
             r_command/1).

binary('-').
binary('+').
binary('/').
binary('*').
binary('^').
binary('%x%').
binary('%%').
binary('%/%').
binary('%*%').
binary('%o%').
binary('%x%').
binary('%in%').
binary('$').

conc([], L, L).
conc([X|L1], L2, [X|L3]) :-
    conc(L1, L2, L3).

flatten([], []).
flatten(X, [X]) :- 
    atomic(X).
flatten([X|Y], Z) :- 
    flatten(X, X1),
    flatten(Y, Y1),
    conc(X1, Y1, Z).

build_args([], []) :- !.
build_args([H|T], L) :-
    (atomic(H), !, 
     name(H, I)
     ;
     build_arglist(H, I)),
    build_args(T, R),
    (T \== [], !,
     name(',', Comma),
     conc(I, Comma, L1)
     ;
     L1 = I),
    conc(L1, R, L).

get_dimargs(A, []) :-
    atomic(A), !.
get_dimargs([H|T], X) :-
    get_dimargs(H, X1),
    length([H|T], LH),
    name(LH, NLH),
    (X1 \== [], !,
     name(',', Comma),
     conc(X1, Comma, X2),
     conc(X2, NLH, X)
     ;
     X = NLH).

build_arglist(L, R) :-
    flatten(L, L), !,
    build_args(L, SL),
    name('c(', Prefix),
    conc(Prefix, SL, R1),
    name(')', Suffix),
    conc(R1, Suffix, R).
build_arglist(L, R) :-
    flatten(L, LF),
    build_args(LF, SL),
    name('array(c(', Prefix),
    conc(Prefix, SL, R1),
    name(')', Suffix),
    get_dimargs(L, Dims),
    conc(R1, Suffix, R2),
    name(',c(', DimPrefix),
    conc(R2, DimPrefix, R3),
    conc(R3, Dims, R4),
    conc(R4, Suffix, R5),
    conc(R5, Suffix, R).

build_command(F, Args, R) :-
    binary(F), !,
    name(F, FN),
    length(Args, 2),
    [O1, O2] = Args,
    build_args([O1], A1),
    build_args([O2], A2),
    conc(A1, FN, R1),
    conc(R1, A2, R).
build_command(F, Args, R) :-
    name(F, FN),
    name('(', Prefix),
    conc(FN, Prefix, FC),
    build_args(Args, AL),
    conc(FC, AL, FF),
    name(')', Suffix),
    conc(FF, Suffix, R).

get_result([H], H) :- !.
get_result(X, X).

r_predicate(F, Args, R) :-
    build_command(F, Args, C),
    list_val(C, L),
    get_result(L, R).

r_command(C) :-
    name(C, CL),
    send_r_command(CL).

:- load_foreign_files(['YapR'], [], init_my_predicates).
:- init_r.
