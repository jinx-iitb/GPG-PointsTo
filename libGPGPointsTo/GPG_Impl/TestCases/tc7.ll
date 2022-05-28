; ModuleID = 'tc7.c'
source_filename = "tc7.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@a = common dso_local global i32 0, align 4, !dbg !0
@x = common dso_local global i32* null, align 8, !dbg !15
@b = common dso_local global i32 0, align 4, !dbg !21
@y = common dso_local global i32* null, align 8, !dbg !17
@c = common dso_local global i32 0, align 4, !dbg !23
@p = common dso_local global i32** null, align 8, !dbg !6
@z = common dso_local global i32* null, align 8, !dbg !19
@q = common dso_local global i32** null, align 8, !dbg !11
@r = common dso_local global i32** null, align 8, !dbg !13

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main() #0 !dbg !29 {
  %1 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  store i32* @a, i32** @x, align 8, !dbg !32
  %2 = load i32, i32* @a, align 4, !dbg !33
  %3 = icmp sgt i32 %2, 10, !dbg !35
  br i1 %3, label %4, label %9, !dbg !36

4:                                                ; preds = %0
  store i32* @b, i32** @y, align 8, !dbg !37
  %5 = load i32, i32* @c, align 4, !dbg !39
  %6 = icmp slt i32 %5, 10, !dbg !41
  br i1 %6, label %7, label %8, !dbg !42

7:                                                ; preds = %4
  store i32** @x, i32*** @p, align 8, !dbg !43
  br label %8, !dbg !45

8:                                                ; preds = %7, %4
  br label %14, !dbg !46

9:                                                ; preds = %0
  store i32* @c, i32** @z, align 8, !dbg !47
  %10 = load i32, i32* @b, align 4, !dbg !49
  %11 = icmp slt i32 %10, 10, !dbg !51
  br i1 %11, label %12, label %13, !dbg !52

12:                                               ; preds = %9
  store i32** @y, i32*** @q, align 8, !dbg !53
  br label %13, !dbg !55

13:                                               ; preds = %12, %9
  br label %14

14:                                               ; preds = %13, %8
  %15 = load i32*, i32** @x, align 8, !dbg !56
  store i32* %15, i32** @z, align 8, !dbg !57
  %16 = load i32*, i32** @y, align 8, !dbg !58
  %17 = load i32**, i32*** @r, align 8, !dbg !59
  store i32* %16, i32** %17, align 8, !dbg !60
  ret i32 0, !dbg !61
}

attributes #0 = { noinline nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!2}
!llvm.module.flags = !{!25, !26, !27}
!llvm.ident = !{!28}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(name: "a", scope: !2, file: !3, line: 2, type: !10, isLocal: false, isDefinition: true)
!2 = distinct !DICompileUnit(language: DW_LANG_C99, file: !3, producer: "clang version 10.0.0-4ubuntu1 ", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !4, globals: !5, splitDebugInlining: false, nameTableKind: None)
!3 = !DIFile(filename: "tc7.c", directory: "/home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/GPG_Impl/TestCases")
!4 = !{}
!5 = !{!6, !11, !13, !15, !17, !19, !0, !21, !23}
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
!16 = distinct !DIGlobalVariable(name: "x", scope: !2, file: !3, line: 2, type: !9, isLocal: false, isDefinition: true)
!17 = !DIGlobalVariableExpression(var: !18, expr: !DIExpression())
!18 = distinct !DIGlobalVariable(name: "y", scope: !2, file: !3, line: 2, type: !9, isLocal: false, isDefinition: true)
!19 = !DIGlobalVariableExpression(var: !20, expr: !DIExpression())
!20 = distinct !DIGlobalVariable(name: "z", scope: !2, file: !3, line: 2, type: !9, isLocal: false, isDefinition: true)
!21 = !DIGlobalVariableExpression(var: !22, expr: !DIExpression())
!22 = distinct !DIGlobalVariable(name: "b", scope: !2, file: !3, line: 2, type: !10, isLocal: false, isDefinition: true)
!23 = !DIGlobalVariableExpression(var: !24, expr: !DIExpression())
!24 = distinct !DIGlobalVariable(name: "c", scope: !2, file: !3, line: 2, type: !10, isLocal: false, isDefinition: true)
!25 = !{i32 7, !"Dwarf Version", i32 4}
!26 = !{i32 2, !"Debug Info Version", i32 3}
!27 = !{i32 1, !"wchar_size", i32 4}
!28 = !{!"clang version 10.0.0-4ubuntu1 "}
!29 = distinct !DISubprogram(name: "main", scope: !3, file: !3, line: 3, type: !30, scopeLine: 3, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!30 = !DISubroutineType(types: !31)
!31 = !{!10}
!32 = !DILocation(line: 4, column: 7, scope: !29)
!33 = !DILocation(line: 5, column: 8, scope: !34)
!34 = distinct !DILexicalBlock(scope: !29, file: !3, line: 5, column: 8)
!35 = !DILocation(line: 5, column: 10, scope: !34)
!36 = !DILocation(line: 5, column: 8, scope: !29)
!37 = !DILocation(line: 6, column: 11, scope: !38)
!38 = distinct !DILexicalBlock(scope: !34, file: !3, line: 5, column: 15)
!39 = !DILocation(line: 7, column: 12, scope: !40)
!40 = distinct !DILexicalBlock(scope: !38, file: !3, line: 7, column: 12)
!41 = !DILocation(line: 7, column: 14, scope: !40)
!42 = !DILocation(line: 7, column: 12, scope: !38)
!43 = !DILocation(line: 8, column: 15, scope: !44)
!44 = distinct !DILexicalBlock(scope: !40, file: !3, line: 7, column: 19)
!45 = !DILocation(line: 9, column: 9, scope: !44)
!46 = !DILocation(line: 10, column: 5, scope: !38)
!47 = !DILocation(line: 12, column: 11, scope: !48)
!48 = distinct !DILexicalBlock(scope: !34, file: !3, line: 11, column: 9)
!49 = !DILocation(line: 13, column: 12, scope: !50)
!50 = distinct !DILexicalBlock(scope: !48, file: !3, line: 13, column: 12)
!51 = !DILocation(line: 13, column: 14, scope: !50)
!52 = !DILocation(line: 13, column: 12, scope: !48)
!53 = !DILocation(line: 14, column: 15, scope: !54)
!54 = distinct !DILexicalBlock(scope: !50, file: !3, line: 13, column: 19)
!55 = !DILocation(line: 15, column: 9, scope: !54)
!56 = !DILocation(line: 17, column: 9, scope: !29)
!57 = !DILocation(line: 17, column: 7, scope: !29)
!58 = !DILocation(line: 18, column: 10, scope: !29)
!59 = !DILocation(line: 18, column: 6, scope: !29)
!60 = !DILocation(line: 18, column: 8, scope: !29)
!61 = !DILocation(line: 19, column: 5, scope: !29)
