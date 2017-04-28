; ModuleID = 'input.bc'
source_filename = "sample_input/goto.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.user = type { i32, %struct.user* }

@u = common global %struct.user zeroinitializer, align 8
@lu = common global %struct.user* null, align 8

; Function Attrs: nounwind uwtable
define %struct.user* @go2(i32 %id) #0 {
entry:
  br label %while.cond

while.cond:                                       ; preds = %if.end, %entry
  %p.0 = phi %struct.user* [ @u, %entry ], [ %tmp5, %if.end ]
  %tobool = icmp ne %struct.user* %p.0, null
  br i1 %tobool, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  %id1 = getelementptr inbounds %struct.user, %struct.user* %p.0, i32 0, i32 0
  %tmp2 = load i32, i32* %id1, align 8
  %cmp = icmp eq i32 %tmp2, %id
  br i1 %cmp, label %if.then, label %if.else

if.then:                                          ; preds = %while.body
  br label %end

if.else:                                          ; preds = %while.body
  %next = getelementptr inbounds %struct.user, %struct.user* %p.0, i32 0, i32 1
  %tmp5 = load %struct.user*, %struct.user** %next, align 8
  br label %if.end

if.end:                                           ; preds = %if.else
  br label %while.cond

while.end:                                        ; preds = %while.cond
  store i32 %id, i32* getelementptr inbounds (%struct.user, %struct.user* @u, i32 0, i32 0), align 8
  br label %end

end:                                              ; preds = %while.end, %if.then
  store %struct.user* %p.0, %struct.user** @lu, align 8
  ret %struct.user* %p.0
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.9.1 (tags/RELEASE_391/final)"}
