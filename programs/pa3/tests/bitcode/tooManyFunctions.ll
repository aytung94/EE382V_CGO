; ModuleID = 'input.bc'
source_filename = "sample_input/tooManyFunctions.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind uwtable
define i32 @factor(i32 %n) #0 {
entry:
  %cmp = icmp eq i32 %n, 0
  br i1 %cmp, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  br label %return

if.else:                                          ; preds = %entry
  %sub = sub nsw i32 %n, 1
  %call = call i32 @factor(i32 %sub)
  %mul = mul nsw i32 %n, %call
  br label %return

return:                                           ; preds = %if.else, %if.then
  %retval.0 = phi i32 [ 1, %if.then ], [ %mul, %if.else ]
  ret i32 %retval.0
}

; Function Attrs: nounwind uwtable
define i32 @recursive1(i32 %a) #0 {
entry:
  %rem = srem i32 %a, 2
  %cmp = icmp eq i32 %rem, 0
  br i1 %cmp, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  %call = call i32 @recursive2(i32 %a)
  br label %return

if.else:                                          ; preds = %entry
  %sub = sub nsw i32 %a, 1
  %call1 = call i32 @recursive2(i32 %sub)
  %add = add nsw i32 %a, %call1
  br label %return

return:                                           ; preds = %if.else, %if.then
  %retval.0 = phi i32 [ %call, %if.then ], [ %add, %if.else ]
  ret i32 %retval.0
}

; Function Attrs: nounwind uwtable
define i32 @recursive2(i32 %a) #0 {
entry:
  %rem = srem i32 %a, 2
  %cmp = icmp ne i32 %rem, 0
  br i1 %cmp, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  %call = call i32 @recursive1(i32 %a)
  br label %return

if.else:                                          ; preds = %entry
  %sub = sub nsw i32 %a, 1
  %call1 = call i32 @recursive1(i32 %sub)
  %add = add nsw i32 %a, %call1
  br label %return

return:                                           ; preds = %if.else, %if.then
  %retval.0 = phi i32 [ %call, %if.then ], [ %add, %if.else ]
  ret i32 %retval.0
}

; Function Attrs: nounwind uwtable
define i32 @start(i32 (i32, i32)* %fp, i32 %a, i32 %b) #0 {
entry:
  %call = call i32 %fp(i32 %a, i32 %b)
  ret i32 %call
}

; Function Attrs: nounwind uwtable
define i32 @add(i32 %a, i32 %b) #0 {
entry:
  %add = add nsw i32 %a, %b
  ret i32 %add
}

; Function Attrs: nounwind uwtable
define i32 @sub(i32 %a, i32 %b) #0 {
entry:
  %sub = sub nsw i32 %a, %b
  ret i32 %sub
}

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
entry:
  %call = call i32 @factor(i32 10)
  %call1 = call i32 @recursive1(i32 15)
  %call2 = call i32 @start(i32 (i32, i32)* @add, i32 1, i32 2)
  ret i32 0
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.9.1 (tags/RELEASE_391/final)"}
