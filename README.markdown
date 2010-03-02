## YapR ##

YapR is a YAP module to enable the access to R-project facilities in the Prolog 
engine.

Current version only tested in windows.

## Example Usage ##

    ?- use_module(yapr).
    ?- r_predicate(sum, [[1,2,3]], X).
    X = 6.0 ?
    yes
    ?- r_predicate(sort, [[2,3,1]], X).
    X = [1.0, 2.0|3.0] ?
    yes
    ?- r_predicate('%*%', [[[1,2,3],[4,5,6],[7,8,9]],[[1,1],[1,1],[1,1]]], X).
    X = [[6.0|6.0],[15.0|15.0],[24.0|24.0]] ?
    yes
    ?- r_predicate(sqrt, [16], X).
    X = 4.0 ?
    yes
    ?- r_predicate(t, [[[1,1],[1,1],[1,1]]], X).
    X = [[1.0,1.0|1.0],[1.0,1.0|1.0]] ?
    yes
    ?- r_command('source("C:/sample.R")').
    yes
