; ModuleID = '2_testcase.ll'
source_filename = "2_testcase.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@n = common dso_local global i32 0, align 4, !dbg !0
@p = common dso_local global i32* null, align 8, !dbg !6
@b = common dso_local global i32 0, align 4, !dbg !12
@q = common dso_local global i32* null, align 8, !dbg !10
@.str = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.str.1 = private unnamed_addr constant [8 x i8] c"q = %d\0A\00", align 1

; Function Attrs: noinline nounwind uwtable
define dso_local void @f() #0 !dbg !18 {
entry:
  store i32* @n, i32** @p, align 8, !dbg !21
  store i32* @b, i32** @q, align 8, !dbg !22
  store i32 22, i32* @n, align 4, !dbg !23
  ret void, !dbg !24
}

; Function Attrs: noinline nounwind uwtable
define dso_local void @g() #0 !dbg !25 {
entry:
  store i32* @b, i32** @p, align 8, !dbg !26
  store i32* @n, i32** @q, align 8, !dbg !27
  store i32 67, i32* @n, align 4, !dbg !28
  ret void, !dbg !29
}

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main() #0 !dbg !30 {
entry:
  store i32 10, i32* @b, align 4, !dbg !33
  %call = call i32 (i8*, ...) @__isoc99_scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str, i64 0, i64 0), i32* @n), !dbg !34
  %tmp = load i32, i32* @n, align 4, !dbg !35
  %rem = srem i32 %tmp, 2, !dbg !37
  %cmp = icmp eq i32 %rem, 0, !dbg !38
  br i1 %cmp, label %if.then, label %if.else, !dbg !39

if.then:                                          ; preds = %entry
  call void @f(), !dbg !40
  br label %if.end, !dbg !42

if.else:                                          ; preds = %entry
  call void @g(), !dbg !43
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %call1 = call i32 (i8*, ...) @__isoc99_scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str, i64 0, i64 0), i32* @n), !dbg !45
  %tmp1 = load i32, i32* @n, align 4, !dbg !46
  %rem2 = srem i32 %tmp1, 2, !dbg !48
  %cmp3 = icmp eq i32 %rem2, 0, !dbg !49
  br i1 %cmp3, label %if.then4, label %if.else5, !dbg !50

if.then4:                                         ; preds = %if.end
  call void @llvm.dbg.value(metadata i32** @p, metadata !51, metadata !DIExpression()), !dbg !53
  br label %if.end6, !dbg !54

if.else5:                                         ; preds = %if.end
  call void @llvm.dbg.value(metadata i32** @q, metadata !51, metadata !DIExpression()), !dbg !53
  br label %if.end6

if.end6:                                          ; preds = %if.else5, %if.then4
  %d.0 = phi i32** [ @p, %if.then4 ], [ @q, %if.else5 ], !dbg !55
  call void @llvm.dbg.value(metadata i32** %d.0, metadata !51, metadata !DIExpression()), !dbg !53
  %tmp2 = load i32*, i32** @p, align 8, !dbg !56
  %tmp3 = load i32, i32* %tmp2, align 4, !dbg !57
  %tmp5 = load i32*, i32** %d.0, align 8, !dbg !58
  %tmp6 = load i32, i32* %tmp5, align 4, !dbg !59
  %add = add nsw i32 %tmp3, %tmp6, !dbg !60
  call void @llvm.dbg.value(metadata i32 %add, metadata !61, metadata !DIExpression()), !dbg !53
  %call7 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0), i32 %add), !dbg !62
  ret i32 0, !dbg !63
}

; Function Attrs: nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare dso_local i32 @__isoc99_scanf(i8*, ...) #2

declare dso_local i32 @printf(i8*, ...) #2

; Function Attrs: nounwind readnone speculatable willreturn
declare void @llvm.dbg.value(metadata, metadata, metadata) #1

attributes #0 = { noinline nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone speculatable willreturn }
attributes #2 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!2}
!llvm.module.flags = !{!14, !15, !16}
!llvm.ident = !{!17}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(name: "n", scope: !2, file: !3, line: 4, type: !9, isLocal: false, isDefinition: true)
!2 = distinct !DICompileUnit(language: DW_LANG_C99, file: !3, producer: "clang version 10.0.0-4ubuntu1 ", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !4, globals: !5, splitDebugInlining: false, nameTableKind: None)
!3 = !DIFile(filename: "2_testcase.c", directory: "/home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/GPG_Impl/TestCases")
!4 = !{}
!5 = !{!6, !10, !0, !12}
!6 = !DIGlobalVariableExpression(var: !7, expr: !DIExpression())
!7 = distinct !DIGlobalVariable(name: "p", scope: !2, file: !3, line: 4, type: !8, isLocal: false, isDefinition: true)
!8 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !9, size: 64)
!9 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!10 = !DIGlobalVariableExpression(var: !11, expr: !DIExpression())
!11 = distinct !DIGlobalVariable(name: "q", scope: !2, file: !3, line: 4, type: !8, isLocal: false, isDefinition: true)
!12 = !DIGlobalVariableExpression(var: !13, expr: !DIExpression())
!13 = distinct !DIGlobalVariable(name: "b", scope: !2, file: !3, line: 4, type: !9, isLocal: false, isDefinition: true)
!14 = !{i32 7, !"Dwarf Version", i32 4}
!15 = !{i32 2, !"Debug Info Version", i32 3}
!16 = !{i32 1, !"wchar_size", i32 4}
!17 = !{!"clang version 10.0.0-4ubuntu1 "}
!18 = distinct !DISubprogram(name: "f", scope: !3, file: !3, line: 6, type: !19, scopeLine: 7, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!19 = !DISubroutineType(types: !20)
!20 = !{null}
!21 = !DILocation(line: 8, column: 4, scope: !18)
!22 = !DILocation(line: 9, column: 4, scope: !18)
!23 = !DILocation(line: 10, column: 4, scope: !18)
!24 = !DILocation(line: 11, column: 1, scope: !18)
!25 = distinct !DISubprogram(name: "g", scope: !3, file: !3, line: 13, type: !19, scopeLine: 14, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!26 = !DILocation(line: 15, column: 4, scope: !25)
!27 = !DILocation(line: 16, column: 4, scope: !25)
!28 = !DILocation(line: 17, column: 4, scope: !25)
!29 = !DILocation(line: 18, column: 1, scope: !25)
!30 = distinct !DISubprogram(name: "main", scope: !3, file: !3, line: 20, type: !31, scopeLine: 21, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!31 = !DISubroutineType(types: !32)
!32 = !{!9}
!33 = !DILocation(line: 22, column: 4, scope: !30)
!34 = !DILocation(line: 26, column: 2, scope: !30)
!35 = !DILocation(line: 28, column: 6, scope: !36)
!36 = distinct !DILexicalBlock(scope: !30, file: !3, line: 28, column: 6)
!37 = !DILocation(line: 28, column: 8, scope: !36)
!38 = !DILocation(line: 28, column: 12, scope: !36)
!39 = !DILocation(line: 28, column: 6, scope: !30)
!40 = !DILocation(line: 30, column: 3, scope: !41)
!41 = distinct !DILexicalBlock(scope: !36, file: !3, line: 29, column: 2)
!42 = !DILocation(line: 31, column: 2, scope: !41)
!43 = !DILocation(line: 34, column: 3, scope: !44)
!44 = distinct !DILexicalBlock(scope: !36, file: !3, line: 33, column: 2)
!45 = !DILocation(line: 37, column: 2, scope: !30)
!46 = !DILocation(line: 39, column: 6, scope: !47)
!47 = distinct !DILexicalBlock(scope: !30, file: !3, line: 39, column: 6)
!48 = !DILocation(line: 39, column: 8, scope: !47)
!49 = !DILocation(line: 39, column: 12, scope: !47)
!50 = !DILocation(line: 39, column: 6, scope: !30)
!51 = !DILocalVariable(name: "d", scope: !30, file: !3, line: 24, type: !52)
!52 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !8, size: 64)
!53 = !DILocation(line: 0, scope: !30)
!54 = !DILocation(line: 40, column: 3, scope: !47)
!55 = !DILocation(line: 0, scope: !47)
!56 = !DILocation(line: 45, column: 11, scope: !30)
!57 = !DILocation(line: 45, column: 10, scope: !30)
!58 = !DILocation(line: 45, column: 16, scope: !30)
!59 = !DILocation(line: 45, column: 15, scope: !30)
!60 = !DILocation(line: 45, column: 13, scope: !30)
!61 = !DILocalVariable(name: "q", scope: !30, file: !3, line: 45, type: !9)
!62 = !DILocation(line: 47, column: 2, scope: !30)
!63 = !DILocation(line: 49, column: 2, scope: !30)
