; ModuleID = 'input.bc'
source_filename = "sample_input/branch.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@A = common global [10 x i32] zeroinitializer, align 16

; Function Attrs: nounwind uwtable
define i32 @small(i32 %s) #0 {
entry:
  %add = add nsw i32 100, %s
  %mul = mul nsw i32 25, %s
  store i32 1, i32* getelementptr inbounds ([10 x i32], [10 x i32]* @A, i64 0, i64 0), align 16
  %cmp = icmp sgt i32 %add, %mul
  br i1 %cmp, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  %call = call i32 @extra(i32 %mul)
  br label %if.end6

if.else:                                          ; preds = %entry
  %cmp1 = icmp slt i32 %add, %mul
  br i1 %cmp1, label %if.then2, label %if.else4

if.then2:                                         ; preds = %if.else
  %call3 = call i32 @extra(i32 %add)
  br label %if.end

if.else4:                                         ; preds = %if.else
  %call5 = call i32 @extra(i32 0)
  br label %if.end

if.end:                                           ; preds = %if.else4, %if.then2
  %b.0 = phi i32 [ %call3, %if.then2 ], [ %call5, %if.else4 ]
  br label %if.end6

if.end6:                                          ; preds = %if.end, %if.then
  %b.1 = phi i32 [ %call, %if.then ], [ %b.0, %if.end ]
  %cmp7 = icmp sgt i32 %add, %b.1
  br i1 %cmp7, label %if.then8, label %if.else17

if.then8:                                         ; preds = %if.end6
  %add9 = add nsw i32 %b.1, 10
  %cmp10 = icmp sgt i32 %add, %add9
  br i1 %cmp10, label %if.then11, label %if.else13

if.then11:                                        ; preds = %if.then8
  %call12 = call i32 @extra(i32 %b.1)
  br label %if.end16

if.else13:                                        ; preds = %if.then8
  %add14 = add nsw i32 %b.1, 10
  %call15 = call i32 @extra(i32 %add14)
  br label %if.end16

if.end16:                                         ; preds = %if.else13, %if.then11
  %b.2 = phi i32 [ %call12, %if.then11 ], [ %call15, %if.else13 ]
  br label %if.end24

if.else17:                                        ; preds = %if.end6
  %cmp18 = icmp slt i32 %add, %b.1
  br i1 %cmp18, label %if.then19, label %if.else21

if.then19:                                        ; preds = %if.else17
  %call20 = call i32 @extra(i32 %add)
  br label %if.end23

if.else21:                                        ; preds = %if.else17
  %call22 = call i32 @extra(i32 0)
  br label %if.end23

if.end23:                                         ; preds = %if.else21, %if.then19
  %b.3 = phi i32 [ %call20, %if.then19 ], [ %call22, %if.else21 ]
  br label %if.end24

if.end24:                                         ; preds = %if.end23, %if.end16
  %b.4 = phi i32 [ %b.2, %if.end16 ], [ %b.3, %if.end23 ]
  ret i32 %b.4
}

declare i32 @extra(i32) #1

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.9.1 (tags/RELEASE_391/final)"}
