; ModuleID = 'input.bc'
source_filename = "sample_input/loop.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@x = common global i32 0, align 4

; Function Attrs: nounwind uwtable
define i32 @f(i32 %arg) #0 {
bb:
  br label %bb4

bb4:                                              ; preds = %bb20, %bb
  %tmp1.0 = phi i32 [ 0, %bb ], [ %tmp22, %bb20 ]
  %tmp2.0 = phi i32 [ 0, %bb ], [ %tmp2.1, %bb20 ]
  %tmp7 = add nsw i32 %arg, 10
  %tmp8 = icmp slt i32 %tmp1.0, %tmp7
  br i1 %tmp8, label %bb9, label %bb23

bb9:                                              ; preds = %bb4
  %tmp11 = call i32 @extra(i32 %tmp1.0)
  br label %bb12

bb12:                                             ; preds = %bb16, %bb9
  %tmp2.1 = phi i32 [ %tmp2.0, %bb9 ], [ %tmp19, %bb16 ]
  %tmp15 = icmp slt i32 %tmp2.1, %arg
  br i1 %tmp15, label %bb16, label %bb20

bb16:                                             ; preds = %bb12
  %tmp19 = call i32 @extra2(i32 %tmp11, i32 %tmp2.1)
  br label %bb12

bb20:                                             ; preds = %bb12
  %tmp22 = call i32 @extra(i32 %tmp2.1)
  br label %bb4

bb23:                                             ; preds = %bb4
  ret i32 %tmp1.0
}

declare i32 @extra(i32) #1

declare i32 @extra2(i32, i32) #1

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.9.1 (tags/RELEASE_391/final)"}
