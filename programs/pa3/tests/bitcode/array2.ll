; ModuleID = 'input.bc'
source_filename = "sample_input/array2.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@A = common global [10 x i32] zeroinitializer, align 16

; Function Attrs: nounwind uwtable
define i32 @sas(i32 %a, i32 %b) #0 {
entry:
  %B = alloca [10 x i32], align 16
  %cmp = icmp sgt i32 %a, %b
  br i1 %cmp, label %cond.true, label %cond.false

cond.true:                                        ; preds = %entry
  br label %cond.end

cond.false:                                       ; preds = %entry
  br label %cond.end

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i32 [ %a, %cond.true ], [ %b, %cond.false ]
  %idxprom = sext i32 %cond to i64
  %arrayidx = getelementptr inbounds [10 x i32], [10 x i32]* @A, i64 0, i64 %idxprom
  %tmp5 = load i32, i32* %arrayidx, align 4
  %idxprom1 = sext i32 %cond to i64
  %arrayidx2 = getelementptr inbounds [10 x i32], [10 x i32]* %B, i64 0, i64 %idxprom1
  store i32 %tmp5, i32* %arrayidx2, align 4
  %idxprom3 = sext i32 %cond to i64
  %arrayidx4 = getelementptr inbounds [10 x i32], [10 x i32]* @A, i64 0, i64 %idxprom3
  store i32 0, i32* %arrayidx4, align 4
  %idxprom5 = sext i32 %cond to i64
  %arrayidx6 = getelementptr inbounds [10 x i32], [10 x i32]* @A, i64 0, i64 %idxprom5
  %tmp9 = load i32, i32* %arrayidx6, align 4
  ret i32 %tmp9
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.9.1 (tags/RELEASE_391/final)"}
