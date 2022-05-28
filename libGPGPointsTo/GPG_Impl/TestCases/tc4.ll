; ModuleID = 'tc4.c'
source_filename = "tc4.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@x = common dso_local global i32* null, align 8, !dbg !0
@p = common dso_local global i32** null, align 8, !dbg !6
@a = common dso_local global i32 0, align 4, !dbg !21
@w = common dso_local global i32* null, align 8, !dbg !19
@b = common dso_local global i32 0, align 4, !dbg !23
@y = common dso_local global i32* null, align 8, !dbg !15
@q = common dso_local global i32** null, align 8, !dbg !11
@r = common dso_local global i32** null, align 8, !dbg !13
@z = common dso_local global i32* null, align 8, !dbg !17
@c = common dso_local global i32 0, align 4, !dbg !25

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main() #0 !dbg !31 {
  %1 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  store i32** @x, i32*** @p, align 8, !dbg !34
  store i32* @a, i32** @w, align 8, !dbg !35
  br label %2, !dbg !36

2:                                                ; preds = %5, %0
  %3 = load i32, i32* @a, align 4, !dbg !37
  %4 = icmp sgt i32 %3, 0, !dbg !38
  br i1 %4, label %5, label %6, !dbg !36

5:                                                ; preds = %2
  store i32* @b, i32** @x, align 8, !dbg !39
  br label %2, !dbg !36, !llvm.loop !41

6:                                                ; preds = %2
  %7 = load i32*, i32** @x, align 8, !dbg !43
  %8 = load i32**, i32*** @p, align 8, !dbg !44
  store i32* %7, i32** %8, align 8, !dbg !45
  store i32* @b, i32** @y, align 8, !dbg !46
  ret i32 0, !dbg !47
}

attributes #0 = { noinline nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!2}
!llvm.module.flags = !{!27, !28, !29}
!llvm.ident = !{!30}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(name: "x", scope: !2, file: !3, line: 2, type: !9, isLocal: false, isDefinition: true)
!2 = distinct !DICompileUnit(language: DW_LANG_C99, file: !3, producer: "clang version 10.0.0-4ubuntu1 ", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !4, globals: !5, splitDebugInlining: false, nameTableKind: None)
!3 = !DIFile(filename: "tc4.c", directory: "/home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/GPG_Impl/TestCases")
!4 = !{}
!5 = !{!6, !11, !13, !0, !15, !17, !19, !21, !23, !25}
!6 = !DIGlobalVariableExpression(var: !7, expr: !DIExpression())
!7 = distinct !DIGlobalVariable(name: "p", scope: !2, file: !3, line: 2, type: !8, isLocal: false, isDefinition: true)
!8 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !9, size: 64)
!9 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !10, size: 64)
!10 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!11 = !DIGlobalVariableExpression(var: !12, expr: !DIExpression())
!12 = distinct !DIGlobalVariable(name: "q", scope: !2, file: !3, line: 2, type: !8, isLocal: false, isDefinition: true)
!13 = !DIGlobalVariableExpression(var: !14, expr: !DIExpression())
!14 = distinct !DIGlobalVariable(name: "r", scope: !2, file: !3, line: 2, type: !8, isLocal: false, isDefinition: true)
!15 = !DIGlobalVariableExpression(var: !16, expr: !DIExpression())
!16 = distinct !DIGlobalVariable(name: "y", scope: !2, file: !3, line: 2, type: !9, isLocal: false, isDefinition: true)
!17 = !DIGlobalVariableExpression(var: !18, expr: !DIExpression())
!18 = distinct !DIGlobalVariable(name: "z", scope: !2, file: !3, line: 2, type: !9, isLocal: false, isDefinition: true)
!19 = !DIGlobalVariableExpression(var: !20, expr: !DIExpression())
!20 = distinct !DIGlobalVariable(name: "w", scope: !2, file: !3, line: 2, type: !9, isLocal: false, isDefinition: true)
!21 = !DIGlobalVariableExpression(var: !22, expr: !DIExpression())
!22 = distinct !DIGlobalVariable(name: "a", scope: !2, file: !3, line: 2, type: !10, isLocal: false, isDefinition: true)
!23 = !DIGlobalVariableExpression(var: !24, expr: !DIExpression())
!24 = distinct !DIGlobalVariable(name: "b", scope: !2, file: !3, line: 2, type: !10, isLocal: false, isDefinition: true)
!25 = !DIGlobalVariableExpression(var: !26, expr: !DIExpression())
!26 = distinct !DIGlobalVariable(name: "c", scope: !2, file: !3, line: 2, type: !10, isLocal: false, isDefinition: true)
!27 = !{i32 7, !"Dwarf Version", i32 4}
!28 = !{i32 2, !"Debug Info Version", i32 3}
!29 = !{i32 1, !"wchar_size", i32 4}
!30 = !{!"clang version 10.0.0-4ubuntu1 "}
!31 = distinct !DISubprogram(name: "main", scope: !3, file: !3, line: 3, type: !32, scopeLine: 3, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!32 = !DISubroutineType(types: !33)
!33 = !{!10}
!34 = !DILocation(line: 4, column: 7, scope: !31)
!35 = !DILocation(line: 5, column: 7, scope: !31)
!36 = !DILocation(line: 6, column: 5, scope: !31)
!37 = !DILocation(line: 6, column: 11, scope: !31)
!38 = !DILocation(line: 6, column: 13, scope: !31)
!39 = !DILocation(line: 7, column: 11, scope: !40)
!40 = distinct !DILexicalBlock(scope: !31, file: !3, line: 6, column: 17)
!41 = distinct !{!41, !36, !42}
!42 = !DILocation(line: 8, column: 5, scope: !31)
!43 = !DILocation(line: 9, column: 10, scope: !31)
!44 = !DILocation(line: 9, column: 6, scope: !31)
!45 = !DILocation(line: 9, column: 8, scope: !31)
!46 = !DILocation(line: 10, column: 7, scope: !31)
!47 = !DILocation(line: 11, column: 5, scope: !31)
