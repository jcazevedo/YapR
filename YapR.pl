module(YapR, init_r/0, float_val/2, int_val/2).

:- load_foreign_files(['YapR'], [], init_my_predicates).
:- init_r.
