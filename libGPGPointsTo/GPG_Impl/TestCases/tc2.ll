; ModuleID = 'tc2.c'
source_filename = "tc2.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@x = common dso_local global i32* null, align 8, !dbg !0
@a = common dso_local global i32 0, align 4, !dbg !15
@y = common dso_local global i32* null, align 8, !dbg !6
@p = common dso_local global i32** null, align 8, !dbg !10
@b = common dso_local global i32 0, align 4, !dbg !17
@q = common dso_local global i32** null, align 8, !dbg !13
@c = common dso_local global i32 0, align 4, !dbg !19

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main() #0 !dbg !25 {
  %1 = alloca i32, align 4
  %2 = alloca i32*, align 8
  store i32 0, i32* %1, align 4
  call void @llvm.dbg.declare(metadata i32** %2, metadata !28, metadata !DIExpression()), !dbg !29
  %3 = load i32*, i32** @x, align 8, !dbg !30
  store i32* %3, i32** %2, align 8, !dbg !29
  store i32* @a, i32** @x, align 8, !dbg !31
  %4 = load i32, i32* @a, align 4, !dbg !32
  %5 = icmp sgt i32 %4, 5, !dbg !34
  br i1 %5, label %6, label %9, !dbg !35

6:                                                ; preds = %0
  %7 = load i32*, i32** @y, align 8, !dbg !36
  %8 = load i32**, i32*** @p, align 8, !dbg !38
  store i32* %7, i32** %8, align 8, !dbg !39
  br label %9, !dbg !40

9:                                                ; preds = %6, %0
  store i32* @b, i32** @x, align 8, !dbg !41
  %10 = load i32*, i32** %2, align 8, !dbg !42
  store i32* %10, i32** @y, align 8, !dbg !43
  %11 = load i32, i32* %1, align 4, !dbg !44
  ret i32 %11, !dbg !44
}

; Function Attrs: nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

attributes #0 = { noinline nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone speculatable willreturn }

!llvm.dbg.cu = !{!2}
!llvm.module.flags = !{!21, !22, !23}
!llvm.ident = !{!24}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(name: "x", scope: !2, file: !3, line: 2, type: !8, isLocal: false, isDefinition: true)
!2 = distinct !DICompileUnit(language: DW_LANG_C99, file: !3, producer: "clang version 10.0.0-4ubuntu1 ", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !4, globals: !5, splitDebugInlining: false, nameTableKind: None)
!3 = !DIFile(filename: "tc2.c", directory: "/home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/GPG_Impl/TestCases")
!4 = !{}
!5 = !{!0, !6, !10, !13, !15, !17, !19}
!6 = !DIGlobalVariableExpression(var: !7, expr: !DIExpression())
!7 = distinct !DIGlobalVariable(name: "y", scope: !2, file: !3, line: 2, type: !8, isLocal: false, isDefinition: true)
!8 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !9, size: 64)
!9 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!10 = !DIGlobalVariableExpression(var: !11, expr: !DIExpression())
!11 = distinct !DIGlobalVariable(name: "p", scope: !2, file: !3, line: 2, type: !12, isLocal: false, isDefinition: true)
!12 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !8, size: 64)
!13 = !DIGlobalVariableExpression(var: !14, expr: !DIExpression())
!14 = distinct !DIGlobalVariable(name: "q", scope: !2, file: !3, line: 2, type: !12, isLocal: false, isDefinition: true)
!15 = !DIGlobalVariableExpression(var: !16, expr: !DIExpression())
!16 = distinct !DIGlobalVariable(name: "a", scope: !2, file: !3, line: 2, type: !9, isLocal: false, isDefinition: true)
!17 = !DIGlobalVariableExpression(var: !18, expr: !DIExpression())
!18 = distinct !DIGlobalVariable(name: "b", scope: !2, file: !3, line: 2, type: !9, isLocal: false, isDefinition: true)
!19 = !DIGlobalVariableExpression(var: !20, expr: !DIExpression())
!20 = distinct !DIGlobalVariable(name: "c", scope: !2, file: !3, line: 2, type: !9, isLocal: false, isDefinition: true)
!21 = !{i32 7, !"Dwarf Version", i32 4}
!22 = !{i32 2, !"Debug Info Version", i32 3}
!23 = !{i32 1, !"wchar_size", i32 4}
!24 = !{!"clang version 10.0.0-4ubuntu1 "}
!25 = distinct !DISubprogram(name: "main", scope: !3, file: !3, line: 3, type: !26, scopeLine: 4, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!26 = !DISubroutineType(types: !27)
!27 = !{!9}
!28 = !DILocalVariable(name: "temp", scope: !25, file: !3, line: 5, type: !8)
!29 = !DILocation(line: 5, column: 10, scope: !25)
!30 = !DILocation(line: 5, column: 17, scope: !25)
!31 = !DILocation(line: 6, column: 7, scope: !25)
!32 = !DILocation(line: 7, column: 9, scope: !33)
!33 = distinct !DILexicalBlock(scope: !25, file: !3, line: 7, column: 9)
!34 = !DILocation(line: 7, column: 11, scope: !33)
!35 = !DILocation(line: 7, column: 9, scope: !25)
!36 = !DILocation(line: 9, column: 14, scope: !37)
!37 = distinct !DILexicalBlock(scope: !33, file: !3, line: 8, column: 5)
!38 = !DILocation(line: 9, column: 10, scope: !37)
!39 = !DILocation(line: 9, column: 12, scope: !37)
!40 = !DILocation(line: 10, column: 5, scope: !37)
!41 = !DILocation(line: 11, column: 7, scope: !25)
!42 = !DILocation(line: 12, column: 9, scope: !25)
!43 = !DILocation(line: 12, column: 7, scope: !25)
!44 = !DILocation(line: 13, column: 1, scope: !25)
