Loop at depth 1 containing: %24<header><exiting>,%26,%30,%35,%33,%37,%28,%38,%40<latch>
Loop at depth 1 containing: %6<header><exiting>,%8,%18,%12,%._crit_edge,%15,%17,%20,%21<latch>

USING GETBLOCKS

---------- DEBUG PRINT FOR LOOP 1 ----------
INNER LOOP FOUND

Header: %24
Latch: %40

Print Paths:
; <label> %40, paths = 1, exiting block
; <label> %38, paths = 1
; <label> %28, paths = 1
; <label> %37, paths = 1
; <label> %33, paths = 1
; <label> %35, paths = 1
; <label> %30, paths = 2
; <label> %26, paths = 3
; <label> %24, paths = 4, exiting block

Print Edge Values:
%24->%Exit: edge value = 3
%24->%26: edge value = 0
%26->%30: edge value = 1
%26->%28: edge value = 0
%30->%35: edge value = 1
%30->%33: edge value = 0
%35->%37: edge value = 0
%33->%37: edge value = 0
%37->%38: edge value = 0
%28->%38: edge value = 0
%38->%40: edge value = 0
%40->%Exit: edge value = 0

Print Instrumentation Locations
%24->%Exit: edge value = 3
%24->%26: edge value = 0
-inserting instruction at successor beginning
%26->%30: edge value = 1
-inserting instruction at successor beginning
%26->%28: edge value = 0
-inserting instruction at successor beginning
%30->%35: edge value = 1
-inserting instruction at successor beginning
%30->%33: edge value = 0
-inserting instruction at successor beginning
%35->%37: edge value = 0
-inserting instruction at predecessor terminator for
%33->%37: edge value = 0
-inserting instruction at predecessor terminator for
%37->%38: edge value = 0
-inserting instruction at predecessor terminator for
%28->%38: edge value = 0
-inserting instruction at predecessor terminator for
%38->%40: edge value = 0
-inserting instruction at successor beginning
%40->%Exit: edge value = 0
 I AM LATCH
(3)1       0       ->Exit
(2)1       1       ->->->->->->->Exit
(1)1       2       ->->->->->->->Exit
(0)1       3       ->->->->->Exit
--------------------------------------------


---------- DEBUG PRINT FOR LOOP 2 ----------
INNER LOOP FOUND

Header: %6
Latch: %21

Print Paths:
; <label> %21, paths = 1, exiting block
; <label> %20, paths = 1
; <label> %17, paths = 1
; <label> %15, paths = 1
; <label> %._crit_edge, paths = 1
; <label> %12, paths = 2
; <label> %18, paths = 1
; <label> %8, paths = 3
; <label> %6, paths = 4, exiting block

Print Edge Values:
%6->%Exit: edge value = 3
%6->%8: edge value = 0
%8->%18: edge value = 2
%8->%12: edge value = 0
%18->%20: edge value = 0
%12->%._crit_edge: edge value = 1
%12->%15: edge value = 0
%._crit_edge->%17: edge value = 0
%15->%17: edge value = 0
%17->%20: edge value = 0
%20->%21: edge value = 0
%21->%Exit: edge value = 0

Print Instrumentation Locations
%6->%Exit: edge value = 3
%6->%8: edge value = 0
-inserting instruction at successor beginning
%8->%18: edge value = 2
-inserting instruction at successor beginning
%8->%12: edge value = 0
-inserting instruction at successor beginning
%18->%20: edge value = 0
-inserting instruction at predecessor terminator for
%12->%._crit_edge: edge value = 1
-inserting instruction at successor beginning
%12->%15: edge value = 0
-inserting instruction at successor beginning
%._crit_edge->%17: edge value = 0
-inserting instruction at predecessor terminator for
%15->%17: edge value = 0
-inserting instruction at predecessor terminator for
%17->%20: edge value = 0
-inserting instruction at predecessor terminator for
%20->%21: edge value = 0
-inserting instruction at successor beginning
%21->%Exit: edge value = 0
 I AM LATCH
(3)2       0       ->Exit
(2)2       1       ->->->->->Exit
(1)2       2       ->->->._crit_edge->->->->Exit
(0)2       3       ->->->->->->->Exit
--------------------------------------------

