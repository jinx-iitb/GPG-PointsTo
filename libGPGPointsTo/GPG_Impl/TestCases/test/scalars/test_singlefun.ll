; ModuleID = './GPG_Impl/TestCases/test/scalars/test_singlefun.ll'
source_filename = "test_singlefun.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@a = common dso_local global i32 0, align 4, !dbg !0
@b = common dso_local global i32 0, align 4, !dbg !6
@c = common dso_local global i32 0, align 4, !dbg !9

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main() #0 !dbg !15 {
bb:
  store i32 20, i32* @a, align 4, !dbg !18
  %tmp = load i32, i32* @a, align 4, !dbg !19
  store i32 %tmp, i32* @b, align 4, !dbg !20
  %tmp1 = load i32, i32* @b, align 4, !dbg !21
  store i32 %tmp1, i32* @c, align 4, !dbg !22
  ret i32 0, !dbg !23
}

attributes #0 = { noinline nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!2}
!llvm.module.flags = !{!11, !12, !13}
!llvm.ident = !{!14}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(name: "a", scope: !2, file: !3, line: 2, type: !8, isLocal: false, isDefinition: true)
!2 = distinct !DICompileUnit(language: DW_LANG_C99, file: !3, producer: "clang version 10.0.0-4ubuntu1 ", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !4, globals: !5, splitDebugInlining: false, nameTableKind: None)
!3 = !DIFile(filename: "test_singlefun.c", directory: "/home/mehul/Desktop/MTP_Venkatesh_Source_code/test/scalars")
!4 = !{}
!5 = !{!0, !6, !9}
!6 = !DIGlobalVariableExpression(var: !7, expr: !DIExpression())
!7 = distinct !DIGlobalVariable(name: "b", scope: !2, file: !3, line: 2, type: !8, isLocal: false, isDefinition: true)
!8 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!9 = !DIGlobalVariableExpression(var: !10, expr: !DIExpression())
!10 = distinct !DIGlobalVariable(name: "c", scope: !2, file: !3, line: 2, type: !8, isLocal: false, isDefinition: true)
!11 = !{i32 7, !"Dwarf Version", i32 4}
!12 = !{i32 2, !"Debug Info Version", i32 3}
!13 = !{i32 1, !"wchar_size", i32 4}
!14 = !{!"clang version 10.0.0-4ubuntu1 "}
!15 = distinct !DISubprogram(name: "main", scope: !3, file: !3, line: 4, type: !16, scopeLine: 4, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!16 = !DISubroutineType(types: !17)
!17 = !{!8}
!18 = !DILocation(line: 6, column: 3, scope: !15)
!19 = !DILocation(line: 8, column: 4, scope: !15)
!20 = !DILocation(line: 8, column: 3, scope: !15)
!21 = !DILocation(line: 10, column: 4, scope: !15)
!22 = !DILocation(line: 10, column: 3, scope: !15)
!23 = !DILocation(line: 13, column: 1, scope: !15)
