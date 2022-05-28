; ModuleID = 'tc2.ll'
source_filename = "tc2.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@a = common dso_local global i32 0, align 4, !dbg !0
@x = common dso_local global i32* null, align 8, !dbg !6
@y = common dso_local global i32* null, align 8, !dbg !10
@p = common dso_local global i32** null, align 8, !dbg !12
@b = common dso_local global i32 0, align 4, !dbg !17
@q = common dso_local global i32** null, align 8, !dbg !15
@c = common dso_local global i32 0, align 4, !dbg !19

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main() #0 !dbg !25 {
bb:
  store i32* @a, i32** @x, align 8, !dbg !28
  %tmp1 = load i32, i32* @a, align 4, !dbg !29
  %tmp2 = icmp sgt i32 %tmp1, 5, !dbg !31
  br i1 %tmp2, label %bb3, label %bb6, !dbg !32

bb3:                                              ; preds = %bb
  %tmp4 = load i32*, i32** @y, align 8, !dbg !33
  %tmp5 = load i32**, i32*** @p, align 8, !dbg !35
  store i32* %tmp4, i32** %tmp5, align 8, !dbg !36
  br label %bb6, !dbg !37

bb6:                                              ; preds = %bb3, %bb
  store i32* @b, i32** @x, align 8, !dbg !38
  ret i32 0, !dbg !39
}

attributes #0 = { noinline nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!2}
!llvm.module.flags = !{!21, !22, !23}
!llvm.ident = !{!24}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(name: "a", scope: !2, file: !3, line: 2, type: !9, isLocal: false, isDefinition: true)
!2 = distinct !DICompileUnit(language: DW_LANG_C99, file: !3, producer: "clang version 10.0.0-4ubuntu1 ", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !4, globals: !5, splitDebugInlining: false, nameTableKind: None)
!3 = !DIFile(filename: "tc2.c", directory: "/home/jinx/IITB/MTP/mehul_mtp/libGPGPointsTo/GPG_Impl/TestCases")
!4 = !{}
!5 = !{!6, !10, !12, !15, !0, !17, !19}
!6 = !DIGlobalVariableExpression(var: !7, expr: !DIExpression())
!7 = distinct !DIGlobalVariable(name: "x", scope: !2, file: !3, line: 2, type: !8, isLocal: false, isDefinition: true)
!8 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !9, size: 64)
!9 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!10 = !DIGlobalVariableExpression(var: !11, expr: !DIExpression())
!11 = distinct !DIGlobalVariable(name: "y", scope: !2, file: !3, line: 2, type: !8, isLocal: false, isDefinition: true)
!12 = !DIGlobalVariableExpression(var: !13, expr: !DIExpression())
!13 = distinct !DIGlobalVariable(name: "p", scope: !2, file: !3, line: 2, type: !14, isLocal: false, isDefinition: true)
!14 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !8, size: 64)
!15 = !DIGlobalVariableExpression(var: !16, expr: !DIExpression())
!16 = distinct !DIGlobalVariable(name: "q", scope: !2, file: !3, line: 2, type: !14, isLocal: false, isDefinition: true)
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
!28 = !DILocation(line: 5, column: 7, scope: !25)
!29 = !DILocation(line: 6, column: 9, scope: !30)
!30 = distinct !DILexicalBlock(scope: !25, file: !3, line: 6, column: 9)
!31 = !DILocation(line: 6, column: 11, scope: !30)
!32 = !DILocation(line: 6, column: 9, scope: !25)
!33 = !DILocation(line: 8, column: 14, scope: !34)
!34 = distinct !DILexicalBlock(scope: !30, file: !3, line: 7, column: 5)
!35 = !DILocation(line: 8, column: 10, scope: !34)
!36 = !DILocation(line: 8, column: 12, scope: !34)
!37 = !DILocation(line: 9, column: 5, scope: !34)
!38 = !DILocation(line: 10, column: 7, scope: !25)
!39 = !DILocation(line: 11, column: 1, scope: !25)
