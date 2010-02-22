## YapR ##

YapR is a YAP module to enable the access to R-project facilities in the Prolog 
engine.

Current version only tested in windows and only supports int and double values.

## Example Usage ##

    ?- use_module(yapr).
    ?- r_predicate(sum, [[1, 2, 3]], X).
    X = 6.0 ?
    yes
    ?- r_predicate(sort, [[2, 3, 1]], X).
    X = [1.0, 2.0|3.0] ?
    yes
    ?- float_val("2 + 3.5", X).
    X = 5.5 ?
    yes
    ?- float_val("sqrt(16)", X).
    X = 4.0 ?
    yes
    ?- int_val("{a = 2; b = 3; a + b}", X).
    X = 5 ?
    yes
