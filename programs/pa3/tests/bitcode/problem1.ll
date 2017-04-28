; ModuleID = 'input.bc'
source_filename = "sample_input/problem1.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
entry:
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %entry
  %s15.0 = phi i32 [ 0, %entry ], [ %s15.1, %for.inc ]
  %s5.0 = phi i32 [ 0, %entry ], [ %s5.1, %for.inc ]
  %s3.0 = phi i32 [ 0, %entry ], [ %s3.1, %for.inc ]
  %i.0 = phi i32 [ 0, %entry ], [ %inc, %for.inc ]
  %cmp = icmp slt i32 %i.0, 1000
  br i1 %cmp, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %rem = srem i32 %i.0, 3
  %cmp1 = icmp eq i32 %rem, 0
  br i1 %cmp1, label %if.then, label %if.end

if.then:                                          ; preds = %for.body
  %add = add nsw i32 %s3.0, %i.0
  br label %if.end

if.end:                                           ; preds = %if.then, %for.body
  %s3.1 = phi i32 [ %add, %if.then ], [ %s3.0, %for.body ]
  %rem2 = srem i32 %i.0, 5
  %cmp3 = icmp eq i32 %rem2, 0
  br i1 %cmp3, label %if.then4, label %if.end6

if.then4:                                         ; preds = %if.end
  %add5 = add nsw i32 %s5.0, %i.0
  br label %if.end6

if.end6:                                          ; preds = %if.then4, %if.end
  %s5.1 = phi i32 [ %add5, %if.then4 ], [ %s5.0, %if.end ]
  %rem7 = srem i32 %i.0, 15
  %cmp8 = icmp eq i32 %rem7, 0
  br i1 %cmp8, label %if.then9, label %if.end11

if.then9:                                         ; preds = %if.end6
  %add10 = add nsw i32 %s15.0, %i.0
  br label %if.end11

if.end11:                                         ; preds = %if.then9, %if.end6
  %s15.1 = phi i32 [ %add10, %if.then9 ], [ %s15.0, %if.end6 ]
  br label %for.inc

for.inc:                                          ; preds = %if.end11
  %inc = add nsw i32 %i.0, 1
  br label %for.cond

for.end:                                          ; preds = %for.cond
  %add12 = add nsw i32 %s3.0, %s5.0
  %sub = sub nsw i32 %add12, %s15.0
  %call = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i32 %sub)
  ret i32 0
}

declare i32 @printf(i8*, ...) #1

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.9.1 (tags/RELEASE_391/final)"}
