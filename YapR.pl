module(YapR, init_r/0, float_val/2, int_val/2, list_val/2, r_predicate/3).

conc([], L, L).
conc([X|L1], L2, [X|L3]) :-
    conc(L1, L2, L3).

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

build_arglist(L, R) :-
    build_args(L, SL),
    conc([99,40], SL, R1),
    conc(R1, [41], R).

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
