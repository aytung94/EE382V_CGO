; ModuleID = 'input.bc'
source_filename = "sample_input/small.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@A = common global [10 x i32] zeroinitializer, align 16
@g = common global i32 0, align 4

; Function Attrs: nounwind uwtable
define i32 @small(i32 %arg) #0 {
bb:
  %tmp15 = mul nsw i32 %arg, %arg
  %tmp17 = sdiv i32 %tmp15, 2
  %tmp19 = icmp sgt i32 %arg, 0
  br i1 %tmp19, label %bb20, label %bb27

bb20:                                             ; preds = %bb
  %tmp23 = add nsw i32 %tmp15, %tmp17
  %tmp26 = add nsw i32 %tmp23, %arg
  br label %bb27

bb27:                                             ; preds = %bb20, %bb
  %tmp1.0 = phi i32 [ %tmp26, %bb20 ], [ %tmp15, %bb ]
  ret i32 %tmp1.0
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.9.1 (tags/RELEASE_391/final)"}
