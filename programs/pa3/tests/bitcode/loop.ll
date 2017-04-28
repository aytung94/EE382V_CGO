; ModuleID = 'input.bc'
source_filename = "sample_input/loop.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@x = common global i32 0, align 4

; Function Attrs: nounwind uwtable
define i32 @f(i32 %s) #0 {
entry:
  br label %while.cond

while.cond:                                       ; preds = %while.end, %entry
  %i.0 = phi i32 [ 0, %entry ], [ %call5, %while.end ]
  %j.0 = phi i32 [ 0, %entry ], [ %j.1, %while.end ]
  %add = add nsw i32 %s, 10
  %cmp = icmp slt i32 %i.0, %add
  br i1 %cmp, label %while.body, label %while.end6

while.body:                                       ; preds = %while.cond
  %call = call i32 @extra(i32 %i.0)
  br label %while.cond1

while.cond1:                                      ; preds = %while.body3, %while.body
  %j.1 = phi i32 [ %j.0, %while.body ], [ %call4, %while.body3 ]
  %cmp2 = icmp slt i32 %j.1, %s
  br i1 %cmp2, label %while.body3, label %while.end

while.body3:                                      ; preds = %while.cond1
  %call4 = call i32 @extra2(i32 %call, i32 %j.1)
  br label %while.cond1

while.end:                                        ; preds = %while.cond1
  %call5 = call i32 @extra(i32 %j.1)
  br label %while.cond

while.end6:                                       ; preds = %while.cond
  ret i32 %i.0
}

declare i32 @extra(i32) #1

declare i32 @extra2(i32, i32) #1

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.9.1 (tags/RELEASE_391/final)"}
