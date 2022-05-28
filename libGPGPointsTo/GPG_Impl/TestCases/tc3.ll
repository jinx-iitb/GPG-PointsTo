; ModuleID = 'tc3.c'
source_filename = "tc3.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@a = common dso_local global i32 0, align 4, !dbg !0
@y = common dso_local global i32* null, align 8, !dbg !14
@b = common dso_local global float 0.000000e+00, align 4, !dbg !22
@z = common dso_local global float* null, align 8, !dbg !16
@x = common dso_local global i32** null, align 8, !dbg !12
@c = common dso_local global float 0.000000e+00, align 4, !dbg !24
@w = common dso_local global float* null, align 8, !dbg !20
@u = common dso_local global i32*** null, align 8, !dbg !6

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main() #0 !dbg !30 {
  %1 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  store i32* @a, i32** @y, align 8, !dbg !33
  %2 = load i32, i32* @a, align 4, !dbg !34
  %3 = icmp sgt i32 %2, 2, !dbg !36
  br i1 %3, label %4, label %5, !dbg !37

4:                                                ; preds = %0
  store float* @b, float** @z, align 8, !dbg !38
  br label %7, !dbg !40

5:                                                ; preds = %0
  %6 = load i32**, i32*** @x, align 8, !dbg !41
  store i32* @a, i32** %6, align 8, !dbg !43
  br label %7

7:                                                ; preds = %5, %4
  store float* @c, float** @w, align 8, !dbg !44
  store i32*** @x, i32**** @u, align 8, !dbg !45
  ret i32 0, !dbg !46
}

attributes #0 = { noinline nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!2}
!llvm.module.flags = !{!26, !27, !28}
!llvm.ident = !{!29}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(name: "a", scope: !2, file: !3, line: 2, type: !11, isLocal: false, isDefinition: true)
!2 = distinct !DICompileUnit(language: DW_LANG_C99, file: !3, producer: "clang version 10.0.0-4ubuntu1 ", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !4, globals: !5, splitDebugInlining: false, nameTableKind: None)
!3 = !DIFile(filename: "tc3.c", directory: "/home/jinx/IITB/MTP/mehul_mtp/libGPGPointsTo/GPG_Impl/TestCases")
!4 = !{}
!5 = !{!6, !12, !14, !0, !16, !20, !22, !24}
!6 = !DIGlobalVariableExpression(var: !7, expr: !DIExpression())
!7 = distinct !DIGlobalVariable(name: "u", scope: !2, file: !3, line: 2, type: !8, isLocal: false, isDefinition: true)
!8 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !9, size: 64)
!9 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !10, size: 64)
!10 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !11, size: 64)
!11 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!12 = !DIGlobalVariableExpression(var: !13, expr: !DIExpression())
!13 = distinct !DIGlobalVariable(name: "x", scope: !2, file: !3, line: 2, type: !9, isLocal: false, isDefinition: true)
!14 = !DIGlobalVariableExpression(var: !15, expr: !DIExpression())
!15 = distinct !DIGlobalVariable(name: "y", scope: !2, file: !3, line: 2, type: !10, isLocal: false, isDefinition: true)
!16 = !DIGlobalVariableExpression(var: !17, expr: !DIExpression())
!17 = distinct !DIGlobalVariable(name: "z", scope: !2, file: !3, line: 3, type: !18, isLocal: false, isDefinition: true)
!18 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !19, size: 64)
!19 = !DIBasicType(name: "float", size: 32, encoding: DW_ATE_float)
!20 = !DIGlobalVariableExpression(var: !21, expr: !DIExpression())
!21 = distinct !DIGlobalVariable(name: "w", scope: !2, file: !3, line: 3, type: !18, isLocal: false, isDefinition: true)
!22 = !DIGlobalVariableExpression(var: !23, expr: !DIExpression())
!23 = distinct !DIGlobalVariable(name: "b", scope: !2, file: !3, line: 3, type: !19, isLocal: false, isDefinition: true)
!24 = !DIGlobalVariableExpression(var: !25, expr: !DIExpression())
!25 = distinct !DIGlobalVariable(name: "c", scope: !2, file: !3, line: 3, type: !19, isLocal: false, isDefinition: true)
!26 = !{i32 7, !"Dwarf Version", i32 4}
!27 = !{i32 2, !"Debug Info Version", i32 3}
!28 = !{i32 1, !"wchar_size", i32 4}
!29 = !{!"clang version 10.0.0-4ubuntu1 "}
!30 = distinct !DISubprogram(name: "main", scope: !3, file: !3, line: 4, type: !31, scopeLine: 5, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!31 = !DISubroutineType(types: !32)
!32 = !{!11}
!33 = !DILocation(line: 6, column: 7, scope: !30)
!34 = !DILocation(line: 7, column: 8, scope: !35)
!35 = distinct !DILexicalBlock(scope: !30, file: !3, line: 7, column: 8)
!36 = !DILocation(line: 7, column: 10, scope: !35)
!37 = !DILocation(line: 7, column: 8, scope: !30)
!38 = !DILocation(line: 9, column: 11, scope: !39)
!39 = distinct !DILexicalBlock(scope: !35, file: !3, line: 8, column: 5)
!40 = !DILocation(line: 10, column: 5, scope: !39)
!41 = !DILocation(line: 13, column: 10, scope: !42)
!42 = distinct !DILexicalBlock(scope: !35, file: !3, line: 12, column: 5)
!43 = !DILocation(line: 13, column: 12, scope: !42)
!44 = !DILocation(line: 15, column: 7, scope: !30)
!45 = !DILocation(line: 16, column: 7, scope: !30)
!46 = !DILocation(line: 17, column: 5, scope: !30)
