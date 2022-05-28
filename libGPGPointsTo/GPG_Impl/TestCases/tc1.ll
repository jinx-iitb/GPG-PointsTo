; ModuleID = 'tc1.c'
source_filename = "tc1.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@a = common dso_local global i32 0, align 4, !dbg !0
@x = common dso_local global i32* null, align 8, !dbg !6
@b = common dso_local global i32 0, align 4, !dbg !19
@c = common dso_local global i32 0, align 4, !dbg !21
@y = common dso_local global i32* null, align 8, !dbg !10
@w = common dso_local global i32* null, align 8, !dbg !12
@p = common dso_local global i32** null, align 8, !dbg !14
@q = common dso_local global i32** null, align 8, !dbg !17

; Function Attrs: noinline nounwind uwtable
define dso_local void @f() #0 !dbg !27 {
  store i32* @a, i32** @x, align 8, !dbg !30
  %1 = load i32, i32* @a, align 4, !dbg !31
  switch i32 %1, label %6 [
    i32 1, label %2
    i32 2, label %3
    i32 3, label %4
    i32 5, label %5
  ], !dbg !32

2:                                                ; preds = %0
  store i32* @b, i32** @x, align 8, !dbg !33
  br label %7, !dbg !35

3:                                                ; preds = %0
  store i32* @c, i32** @x, align 8, !dbg !36
  br label %7, !dbg !37

4:                                                ; preds = %0
  store i32* @a, i32** @y, align 8, !dbg !38
  br label %7, !dbg !39

5:                                                ; preds = %0
  br label %7, !dbg !40

6:                                                ; preds = %0
  store i32* @b, i32** @y, align 8, !dbg !41
  br label %7, !dbg !42

7:                                                ; preds = %6, %5, %4, %3, %2
  %8 = load i32*, i32** @w, align 8, !dbg !43
  %9 = load i32**, i32*** @p, align 8, !dbg !44
  store i32* %8, i32** %9, align 8, !dbg !45
  ret void, !dbg !46
}

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main() #0 !dbg !47 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  store i32** @y, i32*** @p, align 8, !dbg !50
  store i32* @c, i32** @w, align 8, !dbg !51
  call void @f(), !dbg !52
  call void @llvm.dbg.declare(metadata i32* %2, metadata !53, metadata !DIExpression()), !dbg !54
  %3 = load i32*, i32** @x, align 8, !dbg !55
  %4 = load i32, i32* %3, align 4, !dbg !56
  store i32 %4, i32* %2, align 4, !dbg !54
  ret i32 0, !dbg !57
}

; Function Attrs: nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

attributes #0 = { noinline nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone speculatable willreturn }

!llvm.dbg.cu = !{!2}
!llvm.module.flags = !{!23, !24, !25}
!llvm.ident = !{!26}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(name: "a", scope: !2, file: !3, line: 2, type: !9, isLocal: false, isDefinition: true)
!2 = distinct !DICompileUnit(language: DW_LANG_C99, file: !3, producer: "clang version 10.0.0-4ubuntu1 ", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !4, globals: !5, splitDebugInlining: false, nameTableKind: None)
!3 = !DIFile(filename: "tc1.c", directory: "/home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/GPG_Impl/TestCases")
!4 = !{}
!5 = !{!6, !10, !12, !14, !17, !0, !19, !21}
!6 = !DIGlobalVariableExpression(var: !7, expr: !DIExpression())
!7 = distinct !DIGlobalVariable(name: "x", scope: !2, file: !3, line: 2, type: !8, isLocal: false, isDefinition: true)
!8 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !9, size: 64)
!9 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!10 = !DIGlobalVariableExpression(var: !11, expr: !DIExpression())
!11 = distinct !DIGlobalVariable(name: "y", scope: !2, file: !3, line: 2, type: !8, isLocal: false, isDefinition: true)
!12 = !DIGlobalVariableExpression(var: !13, expr: !DIExpression())
!13 = distinct !DIGlobalVariable(name: "w", scope: !2, file: !3, line: 2, type: !8, isLocal: false, isDefinition: true)
!14 = !DIGlobalVariableExpression(var: !15, expr: !DIExpression())
!15 = distinct !DIGlobalVariable(name: "p", scope: !2, file: !3, line: 2, type: !16, isLocal: false, isDefinition: true)
!16 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !8, size: 64)
!17 = !DIGlobalVariableExpression(var: !18, expr: !DIExpression())
!18 = distinct !DIGlobalVariable(name: "q", scope: !2, file: !3, line: 2, type: !16, isLocal: false, isDefinition: true)
!19 = !DIGlobalVariableExpression(var: !20, expr: !DIExpression())
!20 = distinct !DIGlobalVariable(name: "b", scope: !2, file: !3, line: 2, type: !9, isLocal: false, isDefinition: true)
!21 = !DIGlobalVariableExpression(var: !22, expr: !DIExpression())
!22 = distinct !DIGlobalVariable(name: "c", scope: !2, file: !3, line: 2, type: !9, isLocal: false, isDefinition: true)
!23 = !{i32 7, !"Dwarf Version", i32 4}
!24 = !{i32 2, !"Debug Info Version", i32 3}
!25 = !{i32 1, !"wchar_size", i32 4}
!26 = !{!"clang version 10.0.0-4ubuntu1 "}
!27 = distinct !DISubprogram(name: "f", scope: !3, file: !3, line: 3, type: !28, scopeLine: 3, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!28 = !DISubroutineType(types: !29)
!29 = !{null}
!30 = !DILocation(line: 4, column: 4, scope: !27)
!31 = !DILocation(line: 5, column: 9, scope: !27)
!32 = !DILocation(line: 5, column: 2, scope: !27)
!33 = !DILocation(line: 7, column: 6, scope: !34)
!34 = distinct !DILexicalBlock(scope: !27, file: !3, line: 5, column: 11)
!35 = !DILocation(line: 8, column: 4, scope: !34)
!36 = !DILocation(line: 10, column: 6, scope: !34)
!37 = !DILocation(line: 11, column: 4, scope: !34)
!38 = !DILocation(line: 13, column: 6, scope: !34)
!39 = !DILocation(line: 14, column: 4, scope: !34)
!40 = !DILocation(line: 16, column: 4, scope: !34)
!41 = !DILocation(line: 18, column: 6, scope: !34)
!42 = !DILocation(line: 19, column: 4, scope: !34)
!43 = !DILocation(line: 21, column: 7, scope: !27)
!44 = !DILocation(line: 21, column: 3, scope: !27)
!45 = !DILocation(line: 21, column: 5, scope: !27)
!46 = !DILocation(line: 23, column: 1, scope: !27)
!47 = distinct !DISubprogram(name: "main", scope: !3, file: !3, line: 24, type: !48, scopeLine: 24, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!48 = !DISubroutineType(types: !49)
!49 = !{!9}
!50 = !DILocation(line: 25, column: 4, scope: !47)
!51 = !DILocation(line: 26, column: 4, scope: !47)
!52 = !DILocation(line: 28, column: 2, scope: !47)
!53 = !DILocalVariable(name: "aa", scope: !47, file: !3, line: 29, type: !9)
!54 = !DILocation(line: 29, column: 6, scope: !47)
!55 = !DILocation(line: 29, column: 11, scope: !47)
!56 = !DILocation(line: 29, column: 10, scope: !47)
!57 = !DILocation(line: 30, column: 2, scope: !47)
