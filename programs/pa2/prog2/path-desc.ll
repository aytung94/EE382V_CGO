%6%21inner loop!
Successors = %8
-; <label> %8 visiting!
Successors = %12
-; <label> %12 visiting!
Successors = %15
-; <label> %15 visiting!
Successors = %17
-; <label> %17 visiting!
Successors = %20
-; <label> %20 visiting!
Successors = %21
-; <label> %21 visiting!
Successors = %6
-Successor is header!


calculating paths
1


calculating paths
path graph size = 1
1


calculating paths
path graph size = 1
1


calculating paths
path graph size = 1
1

Successors = %._crit_edge
-; <label> %._crit_edge visiting!
Successors = %17
-Visited!


calculating paths
path graph size = 1
1


calculating paths
path graph size = 1
1path graph size = 2
2

Successors = %18
-; <label> %18 visiting!
Successors = %20
-Visited!


calculating paths
path graph size = 1
1


calculating paths
path graph size = 1
2path graph size = 2
3

Successors = %23
-Successor not in loop!


calculating paths
path graph size = 1
3

; <label> %21, paths = 1, exiting block
; <label> %20, paths = 1
; <label> %17, paths = 1
; <label> %15, paths = 1
; <label> %._crit_edge, paths = 1
; <label> %12, paths = 2
; <label> %18, paths = 1
; <label> %8, paths = 3
; <label> %6, paths = 3, exiting block

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


Loop at depth 1 containing: %6<header><exiting>,%8,%18,%12,%._crit_edge,%15,%17,%20,%21<latch>


%8->%18: edge value = 2
2%12->%._crit_edge: edge value = 1
1