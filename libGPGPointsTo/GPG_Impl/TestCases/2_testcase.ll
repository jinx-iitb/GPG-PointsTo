; ModuleID = '2_testcase.c'
source_filename = "2_testcase.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@n = common dso_local global i32 0, align 4
@p = common dso_local global i32* null, align 8
@b = common dso_local global i32 0, align 4
@q = common dso_local global i32* null, align 8
@.str = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.str.1 = private unnamed_addr constant [8 x i8] c"q = %d\0A\00", align 1

; Function Attrs: noinline nounwind uwtable
define dso_local void @f() #0 {
entry:
  store i32* @n, i32** @p, align 8
  store i32* @b, i32** @q, align 8
  store i32 22, i32* @n, align 4
  ret void
}

; Function Attrs: noinline nounwind uwtable
define dso_local void @g() #0 {
entry:
  store i32* @b, i32** @p, align 8
  store i32* @n, i32** @q, align 8
  store i32 67, i32* @n, align 4
  ret void
}

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main() #0 {
entry:
  %retval = alloca i32, align 4
  %d = alloca i32**, align 8
  %q = alloca i32, align 4
  store i32 0, i32* %retval, align 4
  store i32 10, i32* @b, align 4
  %call = call i32 (i8*, ...) @__isoc99_scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str, i64 0, i64 0), i32* @n)
  %0 = load i32, i32* @n, align 4
  %rem = srem i32 %0, 2
  %cmp = icmp eq i32 %rem, 0
  br i1 %cmp, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  call void @f()
  br label %if.end

if.else:                                          ; preds = %entry
  call void @g()
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %call1 = call i32 (i8*, ...) @__isoc99_scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str, i64 0, i64 0), i32* @n)
  %1 = load i32, i32* @n, align 4
  %rem2 = srem i32 %1, 2
  %cmp3 = icmp eq i32 %rem2, 0
  br i1 %cmp3, label %if.then4, label %if.else5

if.then4:                                         ; preds = %if.end
  store i32** @p, i32*** %d, align 8
  br label %if.end6

if.else5:                                         ; preds = %if.end
  store i32** @q, i32*** %d, align 8
  br label %if.end6

if.end6:                                          ; preds = %if.else5, %if.then4
  %2 = load i32*, i32** @p, align 8
  %3 = load i32, i32* %2, align 4
  %4 = load i32**, i32*** %d, align 8
  %5 = load i32*, i32** %4, align 8
  %6 = load i32, i32* %5, align 4
  %add = add nsw i32 %3, %6
  store i32 %add, i32* %q, align 4
  %7 = load i32, i32* %q, align 4
  %call7 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0), i32 %7)
  ret i32 0
}

declare dso_local i32 @__isoc99_scanf(i8*, ...) #1

declare dso_local i32 @printf(i8*, ...) #1

attributes #0 = { noinline nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 10.0.0-4ubuntu1 "}
