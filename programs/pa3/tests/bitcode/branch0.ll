; ModuleID = 'input.bc'
source_filename = "sample_input/branch0.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@A = common global [1000 x i32] zeroinitializer, align 16

; Function Attrs: nounwind uwtable
define i32 @small(i32 %s) #0 {
entry:
  %add = add nsw i32 100, %s
  %mul = mul nsw i32 25, %s
  %cmp = icmp sgt i32 %add, %mul
  br i1 %cmp, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  %idxprom = sext i32 %add to i64
  %arrayidx = getelementptr inbounds [1000 x i32], [1000 x i32]* @A, i64 0, i64 %idxprom
  store i32 0, i32* %arrayidx, align 4
  call void @error(i32 %add)
  %call = call i32 @extra(i32 %mul)
  %idxprom1 = sext i32 %mul to i64
  %arrayidx2 = getelementptr inbounds [1000 x i32], [1000 x i32]* @A, i64 0, i64 %idxprom1
  %tmp8 = load i32, i32* %arrayidx2, align 4
  %add3 = add nsw i32 %call, %tmp8
  br label %if.end

if.else:                                          ; preds = %entry
  %call4 = call i32 @extra(i32 %add)
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %c.0 = phi i32 [ %add3, %if.then ], [ %call4, %if.else ]
  ret i32 %c.0
}

declare void @error(i32) #1

declare i32 @extra(i32) #1

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.9.1 (tags/RELEASE_391/final)"}
