Loop at depth 1 containing: %24<header><exiting>,%26,%30,%35,%33,%37,%28,%38,%40<latch>
Loop at depth 1 containing: %6<header><exiting>,%8,%18,%12,%._crit_edge,%15,%17,%20,%21<latch>


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
%26->%30: edge value = 1
%30->%35: edge value = 1
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
%8->%18: edge value = 2
%12->%._crit_edge: edge value = 1
--------------------------------------------

