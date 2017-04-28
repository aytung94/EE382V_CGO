; ModuleID = 'input.bc'
source_filename = "sample_input/problem44.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [4 x i8] c"%u\0A\00", align 1

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
entry:
  br label %for.cond

for.cond:                                         ; preds = %for.inc13, %entry
  %i.0 = phi i32 [ 1, %entry ], [ %inc14, %for.inc13 ]
  %min.0 = phi i32 [ -1, %entry ], [ %min.1, %for.inc13 ]
  %cmp = icmp ult i32 %i.0, 10000
  br i1 %cmp, label %for.body, label %for.end15

for.body:                                         ; preds = %for.cond
  br label %for.cond1

for.cond1:                                        ; preds = %for.inc, %for.body
  %j.0 = phi i32 [ %i.0, %for.body ], [ %inc, %for.inc ]
  %min.1 = phi i32 [ %min.0, %for.body ], [ %min.3, %for.inc ]
  %cmp2 = icmp ult i32 %j.0, 10000
  br i1 %cmp2, label %for.body3, label %for.end

for.body3:                                        ; preds = %for.cond1
  %call = call i32 @pentagonal(i32 %i.0)
  %call4 = call i32 @pentagonal(i32 %j.0)
  %add = add i32 %call, %call4
  %call5 = call i32 @is_pentagonal(i32 %add)
  %tobool = icmp ne i32 %call5, 0
  br i1 %tobool, label %land.lhs.true, label %if.end12

land.lhs.true:                                    ; preds = %for.body3
  %sub = sub i32 %call4, %call
  %call6 = call i32 @is_pentagonal(i32 %sub)
  %tobool7 = icmp ne i32 %call6, 0
  br i1 %tobool7, label %if.then, label %if.end12

if.then:                                          ; preds = %land.lhs.true
  %sub8 = sub i32 %call4, %call
  %cmp9 = icmp ult i32 %sub8, %min.1
  br i1 %cmp9, label %if.then10, label %if.end

if.then10:                                        ; preds = %if.then
  %sub11 = sub i32 %call4, %call
  br label %if.end

if.end:                                           ; preds = %if.then10, %if.then
  %min.2 = phi i32 [ %sub11, %if.then10 ], [ %min.1, %if.then ]
  br label %if.end12

if.end12:                                         ; preds = %if.end, %land.lhs.true, %for.body3
  %min.3 = phi i32 [ %min.2, %if.end ], [ %min.1, %land.lhs.true ], [ %min.1, %for.body3 ]
  br label %for.inc

for.inc:                                          ; preds = %if.end12
  %inc = add i32 %j.0, 1
  br label %for.cond1

for.end:                                          ; preds = %for.cond1
  br label %for.inc13

for.inc13:                                        ; preds = %for.end
  %inc14 = add i32 %i.0, 1
  br label %for.cond

for.end15:                                        ; preds = %for.cond
  %call16 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i32 %min.0)
  ret i32 0
}

; Function Attrs: inlinehint nounwind uwtable
define internal i32 @pentagonal(i32 %n) #1 {
entry:
  %mul = mul i32 3, %n
  %sub = sub i32 %mul, 1
  %mul1 = mul i32 %n, %sub
  %div = udiv i32 %mul1, 2
  ret i32 %div
}

; Function Attrs: inlinehint nounwind uwtable
define internal i32 @is_pentagonal(i32 %n) #1 {
entry:
  %mul = mul i32 24, %n
  %add = add i32 1, %mul
  %conv = uitofp i32 %add to double
  %call = call double @sqrt(double %conv) #4
  %conv1 = fptoui double %call to i32
  %mul2 = mul i32 %conv1, %conv1
  %mul3 = mul i32 24, %n
  %add4 = add i32 1, %mul3
  %cmp = icmp eq i32 %mul2, %add4
  br i1 %cmp, label %land.rhs, label %land.end

land.rhs:                                         ; preds = %entry
  %add6 = add i32 1, %conv1
  %rem = urem i32 %add6, 6
  %cmp7 = icmp eq i32 %rem, 0
  br label %land.end

land.end:                                         ; preds = %land.rhs, %entry
  %tmp5 = phi i1 [ false, %entry ], [ %cmp7, %land.rhs ]
  %land.ext = zext i1 %tmp5 to i32
  ret i32 %land.ext
}

declare i32 @printf(i8*, ...) #2

; Function Attrs: nounwind
declare double @sqrt(double) #3

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { inlinehint nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.9.1 (tags/RELEASE_391/final)"}
