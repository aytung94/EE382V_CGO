; ModuleID = 'input.bc'
source_filename = "sample_input/branch1.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@A = common global [10 x i32] zeroinitializer, align 16

; Function Attrs: nounwind uwtable
define i32 @small(i32 %s) #0 {
entry:
  %add = add nsw i32 100, %s
  %mul = mul nsw i32 25, %s
  %cmp = icmp sgt i32 %add, %mul
  br i1 %cmp, label %if.then, label %if.else6

if.then:                                          ; preds = %entry
  %add1 = add nsw i32 %mul, 10
  %cmp2 = icmp sgt i32 %add, %add1
  br i1 %cmp2, label %if.then3, label %if.else

if.then3:                                         ; preds = %if.then
  %call = call i32 @extra(i32 %mul)
  br label %if.end

if.else:                                          ; preds = %if.then
  %add4 = add nsw i32 %mul, 10
  %call5 = call i32 @extra(i32 %add4)
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then3
  %b.0 = phi i32 [ %call, %if.then3 ], [ %call5, %if.else ]
  br label %if.end13

if.else6:                                         ; preds = %entry
  %cmp7 = icmp slt i32 %add, %mul
  br i1 %cmp7, label %if.then8, label %if.else10

if.then8:                                         ; preds = %if.else6
  %call9 = call i32 @extra(i32 %add)
  br label %if.end12

if.else10:                                        ; preds = %if.else6
  %call11 = call i32 @extra(i32 0)
  br label %if.end12

if.end12:                                         ; preds = %if.else10, %if.then8
  %b.1 = phi i32 [ %call9, %if.then8 ], [ %call11, %if.else10 ]
  br label %if.end13

if.end13:                                         ; preds = %if.end12, %if.end
  %b.2 = phi i32 [ %b.0, %if.end ], [ %b.1, %if.end12 ]
  ret i32 %b.2
}

declare i32 @extra(i32) #1

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.9.1 (tags/RELEASE_391/final)"}
