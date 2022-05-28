; ModuleID = './GPG_Impl/TestCases/test/twofun.ll'
source_filename = "twofun.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@z = common dso_local global i32* null, align 8, !dbg !0
@p = common dso_local global i32** null, align 8, !dbg !6
@x = common dso_local global i32* null, align 8, !dbg !13
@a = common dso_local global i32 0, align 4, !dbg !17
@y = common dso_local global i32* null, align 8, !dbg !15
@b = common dso_local global i32 0, align 4, !dbg !19
@q = common dso_local global i32** null, align 8, !dbg !11

; Function Attrs: noinline nounwind uwtable
define dso_local void @f() #0 !dbg !25 {
bb:
  %tmp = load i32*, i32** @z, align 8, !dbg !28
  %tmp1 = load i32**, i32*** @p, align 8, !dbg !29
  store i32* %tmp, i32** %tmp1, align 8, !dbg !30
  ret void, !dbg !31
}

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main() #0 !dbg !32 {
bb:
  store i32** @x, i32*** @p, align 8, !dbg !35
  store i32* @a, i32** @z, align 8, !dbg !36
  call void @f(), !dbg !37
  %tmp = load i32**, i32*** @p, align 8, !dbg !38
  %tmp1 = load i32*, i32** %tmp, align 8, !dbg !39
  store i32 20, i32* %tmp1, align 4, !dbg !40
  store i32** @y, i32*** @p, align 8, !dbg !41
  store i32* @b, i32** @z, align 8, !dbg !42
  call void @f(), !dbg !43
  %tmp2 = load i32**, i32*** @p, align 8, !dbg !44
  %tmp3 = load i32*, i32** %tmp2, align 8, !dbg !45
  store i32 30, i32* %tmp3, align 4, !dbg !46
  ret i32 0, !dbg !47
}

attributes #0 = { noinline nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!2}
!llvm.module.flags = !{!21, !22, !23}
!llvm.ident = !{!24}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(name: "z", scope: !2, file: !3, line: 3, type: !9, isLocal: false, isDefinition: true)
!2 = distinct !DICompileUnit(language: DW_LANG_C99, file: !3, producer: "clang version 10.0.0-4ubuntu1 ", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !4, globals: !5, splitDebugInlining: false, nameTableKind: None)
!3 = !DIFile(filename: "twofun.c", directory: "/home/mehul/Desktop/MTP_Venkatesh_Source_code/test")
!4 = !{}
!5 = !{!6, !11, !13, !15, !0, !17, !19}
!6 = !DIGlobalVariableExpression(var: !7, expr: !DIExpression())
!7 = distinct !DIGlobalVariable(name: "p", scope: !2, file: !3, line: 2, type: !8, isLocal: false, isDefinition: true)
!8 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !9, size: 64)
!9 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !10, size: 64)
!10 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!11 = !DIGlobalVariableExpression(var: !12, expr: !DIExpression())
!12 = distinct !DIGlobalVariable(name: "q", scope: !2, file: !3, line: 2, type: !8, isLocal: false, isDefinition: true)
!13 = !DIGlobalVariableExpression(var: !14, expr: !DIExpression())
!14 = distinct !DIGlobalVariable(name: "x", scope: !2, file: !3, line: 3, type: !9, isLocal: false, isDefinition: true)
!15 = !DIGlobalVariableExpression(var: !16, expr: !DIExpression())
!16 = distinct !DIGlobalVariable(name: "y", scope: !2, file: !3, line: 3, type: !9, isLocal: false, isDefinition: true)
!17 = !DIGlobalVariableExpression(var: !18, expr: !DIExpression())
!18 = distinct !DIGlobalVariable(name: "a", scope: !2, file: !3, line: 4, type: !10, isLocal: false, isDefinition: true)
!19 = !DIGlobalVariableExpression(var: !20, expr: !DIExpression())
!20 = distinct !DIGlobalVariable(name: "b", scope: !2, file: !3, line: 4, type: !10, isLocal: false, isDefinition: true)
!21 = !{i32 7, !"Dwarf Version", i32 4}
!22 = !{i32 2, !"Debug Info Version", i32 3}
!23 = !{i32 1, !"wchar_size", i32 4}
!24 = !{!"clang version 10.0.0-4ubuntu1 "}
!25 = distinct !DISubprogram(name: "f", scope: !3, file: !3, line: 6, type: !26, scopeLine: 6, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!26 = !DISubroutineType(types: !27)
!27 = !{null}
!28 = !DILocation(line: 8, column: 5, scope: !25)
!29 = !DILocation(line: 8, column: 3, scope: !25)
!30 = !DILocation(line: 8, column: 4, scope: !25)
!31 = !DILocation(line: 9, column: 1, scope: !25)
!32 = distinct !DISubprogram(name: "main", scope: !3, file: !3, line: 11, type: !33, scopeLine: 11, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!33 = !DISubroutineType(types: !34)
!34 = !{!10}
!35 = !DILocation(line: 13, column: 4, scope: !32)
!36 = !DILocation(line: 14, column: 4, scope: !32)
!37 = !DILocation(line: 16, column: 3, scope: !32)
!38 = !DILocation(line: 18, column: 5, scope: !32)
!39 = !DILocation(line: 18, column: 4, scope: !32)
!40 = !DILocation(line: 18, column: 6, scope: !32)
!41 = !DILocation(line: 20, column: 4, scope: !32)
!42 = !DILocation(line: 21, column: 4, scope: !32)
!43 = !DILocation(line: 23, column: 3, scope: !32)
!44 = !DILocation(line: 25, column: 5, scope: !32)
!45 = !DILocation(line: 25, column: 4, scope: !32)
!46 = !DILocation(line: 25, column: 6, scope: !32)
!47 = !DILocation(line: 28, column: 1, scope: !32)
