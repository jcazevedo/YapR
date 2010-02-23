module(YapR, init_r/0, float_val/2, int_val/2, list_val/2, r_predicate/3).

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
     conc(I, [44], L1)
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
     conc(X1, [44], X2),
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
    name(F, FN),
    conc(FN, [40], FC),
    build_args(Args, AL),
    conc(FC, AL, FF),
    conc(FF, [41], R).

get_result([H], H) :- !.
get_result(X, X).

r_predicate(F, Args, R) :-
    build_command(F, Args, C),
    list_val(C, L),
    get_result(L, R).

:- load_foreign_files(['YapR'], [], init_my_predicates).
:- init_r.
