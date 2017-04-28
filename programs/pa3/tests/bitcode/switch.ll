; ModuleID = 'input.bc'
source_filename = "sample_input/switch.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind uwtable
define i32 @sw(i32 %a) #0 {
entry:
  switch i32 %a, label %sw.default [
    i32 0, label %sw.bb
    i32 1, label %sw.bb1
    i32 2, label %sw.bb2
    i32 3, label %sw.bb3
  ]

sw.bb:                                            ; preds = %entry
  br label %return

sw.bb1:                                           ; preds = %entry
  %add = add nsw i32 undef, 1
  br label %sw.bb2

sw.bb2:                                           ; preds = %entry, %sw.bb1
  %b.0 = phi i32 [ undef, %entry ], [ %add, %sw.bb1 ]
  %mul = mul nsw i32 %b.0, 2
  br label %sw.epilog

sw.bb3:                                           ; preds = %entry
  %call = call i32 @f(i32 undef)
  br label %sw.epilog

sw.default:                                       ; preds = %entry
  br label %return

sw.epilog:                                        ; preds = %sw.bb3, %sw.bb2
  %b.1 = phi i32 [ %call, %sw.bb3 ], [ %mul, %sw.bb2 ]
  br label %return

return:                                           ; preds = %sw.epilog, %sw.default, %sw.bb
  %retval.0 = phi i32 [ 0, %sw.default ], [ %b.1, %sw.epilog ], [ 1, %sw.bb ]
  ret i32 %retval.0
}

declare i32 @f(i32) #1

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.9.1 (tags/RELEASE_391/final)"}
