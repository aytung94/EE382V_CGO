; ModuleID = 'input.bc'
source_filename = "tests/sample_input/tooManyFunctions.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind uwtable
define i32 @factor(i32 %arg) #0 {
bb:
  %tmp3 = icmp eq i32 %arg, 0
  br i1 %tmp3, label %bb4, label %bb5

bb4:                                              ; preds = %bb
  br label %bb11

bb5:                                              ; preds = %bb
  %tmp8 = sub nsw i32 %arg, 1
  %tmp9 = call i32 @factor(i32 %tmp8)
  %tmp10 = mul nsw i32 %arg, %tmp9
  br label %bb11

bb11:                                             ; preds = %bb5, %bb4
  %tmp.0 = phi i32 [ 1, %bb4 ], [ %tmp10, %bb5 ]
  ret i32 %tmp.0
}

; Function Attrs: nounwind uwtable
define i32 @recursive1(i32 %arg) #0 {
bb:
  %tmp3 = srem i32 %arg, 2
  %tmp4 = icmp eq i32 %tmp3, 0
  br i1 %tmp4, label %bb5, label %bb8

bb5:                                              ; preds = %bb
  %tmp7 = call i32 @recursive2(i32 %arg)
  br label %bb14

bb8:                                              ; preds = %bb
  %tmp11 = sub nsw i32 %arg, 1
  %tmp12 = call i32 @recursive2(i32 %tmp11)
  %tmp13 = add nsw i32 %arg, %tmp12
  br label %bb14

bb14:                                             ; preds = %bb8, %bb5
  %tmp.0 = phi i32 [ %tmp7, %bb5 ], [ %tmp13, %bb8 ]
  ret i32 %tmp.0
}

; Function Attrs: nounwind uwtable
define i32 @recursive2(i32 %arg) #0 {
bb:
  %tmp3 = srem i32 %arg, 2
  %tmp4 = icmp ne i32 %tmp3, 0
  br i1 %tmp4, label %bb5, label %bb8

bb5:                                              ; preds = %bb
  %tmp7 = call i32 @recursive1(i32 %arg)
  br label %bb14

bb8:                                              ; preds = %bb
  %tmp11 = sub nsw i32 %arg, 1
  %tmp12 = call i32 @recursive1(i32 %tmp11)
  %tmp13 = add nsw i32 %arg, %tmp12
  br label %bb14

bb14:                                             ; preds = %bb8, %bb5
  %tmp.0 = phi i32 [ %tmp7, %bb5 ], [ %tmp13, %bb8 ]
  ret i32 %tmp.0
}

; Function Attrs: nounwind uwtable
define i32 @start(i32 (i32, i32)* %arg, i32 %arg1, i32 %arg2) #0 {
bb:
  %tmp8 = call i32 %arg(i32 %arg1, i32 %arg2)
  ret i32 %tmp8
}

; Function Attrs: nounwind uwtable
define i32 @add(i32 %arg, i32 %arg1) #0 {
bb:
  %tmp5 = add nsw i32 %arg, %arg1
  ret i32 %tmp5
}

; Function Attrs: nounwind uwtable
define i32 @sub(i32 %arg, i32 %arg1) #0 {
bb:
  %tmp5 = sub nsw i32 %arg, %arg1
  ret i32 %tmp5
}

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
bb:
  %tmp2 = call i32 @factor(i32 10)
  %tmp3 = call i32 @recursive1(i32 15)
  %tmp5 = call i32 @start(i32 (i32, i32)* @add, i32 1, i32 2)
  ret i32 0
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.9.1 (tags/RELEASE_391/final)"}
