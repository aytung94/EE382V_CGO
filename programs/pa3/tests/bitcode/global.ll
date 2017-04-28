; ModuleID = 'input.bc'
source_filename = "sample_input/global.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@A = common global [10 x i32] zeroinitializer, align 16
@g = common global i32 0, align 4

; Function Attrs: nounwind uwtable
define i32 @small(i32 %s) #0 {
entry:
  %tmp = load i32, i32* getelementptr inbounds ([10 x i32], [10 x i32]* @A, i64 0, i64 0), align 16
  %tmp1 = load i32, i32* @g, align 4
  %cmp = icmp sgt i32 %tmp, %tmp1
  br i1 %cmp, label %if.then, label %if.end

if.then:                                          ; preds = %entry
  store i32 %tmp1, i32* getelementptr inbounds ([10 x i32], [10 x i32]* @A, i64 0, i64 0), align 16
  store i32 %tmp, i32* @g, align 4
  br label %if.end

if.end:                                           ; preds = %if.then, %entry
  ret i32 %tmp
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.9.1 (tags/RELEASE_391/final)"}
