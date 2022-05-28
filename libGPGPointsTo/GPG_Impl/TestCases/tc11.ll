; ModuleID = 'tc11.c'
source_filename = "tc11.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@x = common dso_local global i32* null, align 8, !dbg !0
@p = common dso_local global i32** null, align 8, !dbg !6
@a = common dso_local global i32 0, align 4, !dbg !19
@q = common dso_local global i32** null, align 8, !dbg !11
@y = common dso_local global i32* null, align 8, !dbg !15
@r = common dso_local global i32** null, align 8, !dbg !13
@z = common dso_local global i32* null, align 8, !dbg !17
@b = common dso_local global i32 0, align 4, !dbg !21
@c = common dso_local global i32 0, align 4, !dbg !23

; Function Attrs: noinline nounwind uwtable
define dso_local void @f(i32** %0, i32** %1) #0 !dbg !29 {
  %3 = alloca i32**, align 8
  %4 = alloca i32**, align 8
  %5 = alloca i32*, align 8
  store i32** %0, i32*** %3, align 8
  call void @llvm.dbg.declare(metadata i32*** %3, metadata !32, metadata !DIExpression()), !dbg !33
  store i32** %1, i32*** %4, align 8
  call void @llvm.dbg.declare(metadata i32*** %4, metadata !34, metadata !DIExpression()), !dbg !35
  call void @llvm.dbg.declare(metadata i32** %5, metadata !36, metadata !DIExpression()), !dbg !37
  %6 = load i32**, i32*** %3, align 8, !dbg !38
  %7 = bitcast i32** %6 to i32*, !dbg !38
  store i32* %7, i32** %5, align 8, !dbg !37
  %8 = load i32**, i32*** %4, align 8, !dbg !39
  %9 = bitcast i32** %8 to i32*, !dbg !39
  %10 = load i32**, i32*** %3, align 8, !dbg !40
  store i32* %9, i32** %10, align 8, !dbg !41
  %11 = load i32*, i32** %5, align 8, !dbg !42
  %12 = load i32**, i32*** %4, align 8, !dbg !43
  store i32* %11, i32** %12, align 8, !dbg !44
  ret void, !dbg !45
}

; Function Attrs: nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main() #0 !dbg !46 {
  %1 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  store i32** @x, i32*** @p, align 8, !dbg !49
  %2 = load i32**, i32*** @q, align 8, !dbg !50
  store i32* @a, i32** %2, align 8, !dbg !51
  store i32** @y, i32*** @r, align 8, !dbg !52
  call void @f(i32** @x, i32** @y), !dbg !53
  store i32* @a, i32** @x, align 8, !dbg !54
  ret i32 0, !dbg !55
}

attributes #0 = { noinline nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone speculatable willreturn }

!llvm.dbg.cu = !{!2}
!llvm.module.flags = !{!25, !26, !27}
!llvm.ident = !{!28}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(name: "x", scope: !2, file: !3, line: 2, type: !9, isLocal: false, isDefinition: true)
!2 = distinct !DICompileUnit(language: DW_LANG_C99, file: !3, producer: "clang version 10.0.0-4ubuntu1 ", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !4, globals: !5, splitDebugInlining: false, nameTableKind: None)
!3 = !DIFile(filename: "tc11.c", directory: "/home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/GPG_Impl/TestCases")
!4 = !{}
!5 = !{!6, !11, !13, !0, !15, !17, !19, !21, !23}
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
!20 = distinct !DIGlobalVariable(name: "a", scope: !2, file: !3, line: 2, type: !10, isLocal: false, isDefinition: true)
!21 = !DIGlobalVariableExpression(var: !22, expr: !DIExpression())
!22 = distinct !DIGlobalVariable(name: "b", scope: !2, file: !3, line: 2, type: !10, isLocal: false, isDefinition: true)
!23 = !DIGlobalVariableExpression(var: !24, expr: !DIExpression())
!24 = distinct !DIGlobalVariable(name: "c", scope: !2, file: !3, line: 2, type: !10, isLocal: false, isDefinition: true)
!25 = !{i32 7, !"Dwarf Version", i32 4}
!26 = !{i32 2, !"Debug Info Version", i32 3}
!27 = !{i32 1, !"wchar_size", i32 4}
!28 = !{!"clang version 10.0.0-4ubuntu1 "}
!29 = distinct !DISubprogram(name: "f", scope: !3, file: !3, line: 4, type: !30, scopeLine: 4, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!30 = !DISubroutineType(types: !31)
!31 = !{null, !8, !8}
!32 = !DILocalVariable(name: "xx", arg: 1, scope: !29, file: !3, line: 4, type: !8)
!33 = !DILocation(line: 4, column: 14, scope: !29)
!34 = !DILocalVariable(name: "yy", arg: 2, scope: !29, file: !3, line: 4, type: !8)
!35 = !DILocation(line: 4, column: 23, scope: !29)
!36 = !DILocalVariable(name: "temp", scope: !29, file: !3, line: 5, type: !9)
!37 = !DILocation(line: 5, column: 10, scope: !29)
!38 = !DILocation(line: 5, column: 17, scope: !29)
!39 = !DILocation(line: 6, column: 11, scope: !29)
!40 = !DILocation(line: 6, column: 6, scope: !29)
!41 = !DILocation(line: 6, column: 9, scope: !29)
!42 = !DILocation(line: 7, column: 11, scope: !29)
!43 = !DILocation(line: 7, column: 6, scope: !29)
!44 = !DILocation(line: 7, column: 9, scope: !29)
!45 = !DILocation(line: 8, column: 1, scope: !29)
!46 = distinct !DISubprogram(name: "main", scope: !3, file: !3, line: 10, type: !47, scopeLine: 10, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!47 = !DISubroutineType(types: !48)
!48 = !{!10}
!49 = !DILocation(line: 11, column: 7, scope: !46)
!50 = !DILocation(line: 12, column: 6, scope: !46)
!51 = !DILocation(line: 12, column: 8, scope: !46)
!52 = !DILocation(line: 13, column: 7, scope: !46)
!53 = !DILocation(line: 14, column: 5, scope: !46)
!54 = !DILocation(line: 15, column: 7, scope: !46)
!55 = !DILocation(line: 16, column: 5, scope: !46)
