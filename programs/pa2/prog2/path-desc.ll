Loop at depth 1 containing: %6<header><exiting>,%8,%14,%12,%16,%17<latch>

USING GETBLOCKS

---------- DEBUG PRINT FOR LOOP 1 ----------
INNER LOOP FOUND

Header: %6
Latch: %17

Print Paths:
; <label> %17, paths = 1, exiting block
; <label> %16, paths = 1
; <label> %12, paths = 1
; <label> %14, paths = 1
; <label> %8, paths = 2
; <label> %6, paths = 3, exiting block

Print Edge Values:
%6->%Exit: edge value = 2
%6->%8: edge value = 0
%8->%14: edge value = 1
%8->%12: edge value = 0
%14->%16: edge value = 0
%12->%16: edge value = 0
%16->%17: edge value = 0
%17->%Exit: edge value = 0

Print Instrumentation Locations
%6->%Exit: edge value = 2
%6->%8: edge value = 0
-inserting instruction at successor beginning
%8->%14: edge value = 1
-inserting instruction at successor beginning
%8->%12: edge value = 0
-inserting instruction at successor beginning
%14->%16: edge value = 0
-inserting instruction at predecessor terminator for
%12->%16: edge value = 0
-inserting instruction at predecessor terminator for
%16->%17: edge value = 0
-inserting instruction at successor beginning
%17->%Exit: edge value = 0
 I AM LATCH
(2)1       0       ->Exit
(1)1       1       ->->->->->Exit
(0)1       2       ->->->->->Exit
--------------------------------------------

