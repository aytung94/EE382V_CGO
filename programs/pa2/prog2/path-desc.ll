%24%40inner loop!
Successors = %26
-; <label> %26 visiting!
Successors = %28
-; <label> %28 visiting!
Successors = %38
-; <label> %38 visiting!
Successors = %40
-; <label> %40 visiting!
Successors = %24
-Successor is header!


calculating paths



calculating paths
path graph size = 1
1


calculating paths
path graph size = 1
1

Successors = %30
-; <label> %30 visiting!
Successors = %33
-; <label> %33 visiting!
Successors = %37
-; <label> %37 visiting!
Successors = %38
-Visited!


calculating paths
path graph size = 1
1


calculating paths
path graph size = 1
1

Successors = %35
-; <label> %35 visiting!
Successors = %37
-Visited!


calculating paths
path graph size = 1
1


calculating paths
path graph size = 1
1path graph size = 2
2


calculating paths
path graph size = 1
1path graph size = 2
3

Successors = %42
-Successor not in loop!


calculating paths
path graph size = 1
3

; <label> %40, paths = 1, exiting block
; <label> %38, paths = 1
; <label> %28, paths = 1
; <label> %37, paths = 1
; <label> %33, paths = 1
; <label> %35, paths = 1
; <label> %30, paths = 2
; <label> %26, paths = 3
; <label> %24, paths = 4, exiting block

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


Loop at depth 1 containing: %24<header><exiting>,%26,%30,%35,%33,%37,%28,%38,%40<latch>
Loop at depth 1 containing: %6<header><exiting>,%8,%18,%12,%._crit_edge,%15,%17,%20,%21<latch>


%24->%Exit: edge value = 3
3%26->%30: edge value = 1
1%30->%35: edge value = 1
1%6%21inner loop!
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
; <label> %6, paths = 4, exiting block

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


Loop at depth 1 containing: %24<header><exiting>,%26,%30,%35,%33,%37,%28,%38,%40<latch>
Loop at depth 1 containing: %6<header><exiting>,%8,%18,%12,%._crit_edge,%15,%17,%20,%21<latch>


%6->%Exit: edge value = 3
3%8->%18: edge value = 2
2%12->%._crit_edge: edge value = 1
1