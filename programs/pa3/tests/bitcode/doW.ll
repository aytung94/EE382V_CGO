; ModuleID = 'input.bc'
source_filename = "sample_input/doW.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@A = common global [10 x i32] zeroinitializer, align 16

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
entry:
  %B = alloca [10 x i32], align 16
  br label %do.body

do.body:                                          ; preds = %do.cond, %entry
  %i.0 = phi i32 [ 9, %entry ], [ %sub, %do.cond ]
  %sum.0 = phi i32 [ undef, %entry ], [ %add7, %do.cond ]
  %idxprom = sext i32 %i.0 to i64
  %arrayidx = getelementptr inbounds [10 x i32], [10 x i32]* @A, i64 0, i64 %idxprom
  %tmp1 = load i32, i32* %arrayidx, align 4
  %cmp = icmp slt i32 %tmp1, 0
  br i1 %cmp, label %if.then, label %if.else

if.then:                                          ; preds = %do.body
  %idxprom1 = sext i32 %i.0 to i64
  %arrayidx2 = getelementptr inbounds [10 x i32], [10 x i32]* %B, i64 0, i64 %idxprom1
  %tmp3 = load i32, i32* %arrayidx2, align 4
  %add = add nsw i32 %tmp3, 1
  %idxprom3 = sext i32 %i.0 to i64
  %arrayidx4 = getelementptr inbounds [10 x i32], [10 x i32]* @A, i64 0, i64 %idxprom3
  store i32 %add, i32* %arrayidx4, align 4
  br label %if.end

if.else:                                          ; preds = %do.body
  store i32 1, i32* getelementptr inbounds ([10 x i32], [10 x i32]* @A, i64 0, i64 0), align 16
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %idxprom5 = sext i32 %i.0 to i64
  %arrayidx6 = getelementptr inbounds [10 x i32], [10 x i32]* %B, i64 0, i64 %idxprom5
  %tmp6 = load i32, i32* %arrayidx6, align 4
  %add7 = add nsw i32 %sum.0, %tmp6
  %sub = sub nsw i32 %i.0, 1
  br label %do.cond

do.cond:                                          ; preds = %if.end
  %cmp8 = icmp sge i32 %sub, 0
  br i1 %cmp8, label %do.body, label %do.end

do.end:                                           ; preds = %do.cond
  %tmp10 = load i32, i32* getelementptr inbounds ([10 x i32], [10 x i32]* @A, i64 0, i64 3), align 4
  ret i32 %tmp10
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.9.1 (tags/RELEASE_391/final)"}
