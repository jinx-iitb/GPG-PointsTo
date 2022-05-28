; ModuleID = 'ex5.c'
source_filename = "ex5.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@p = common dso_local global i32** null, align 8, !dbg !0
@y = common dso_local global i32* null, align 8, !dbg !6

; Function Attrs: noinline nounwind uwtable
define dso_local void @f(i32** %0) #0 !dbg !15 {
  %2 = alloca i32**, align 8
  %3 = alloca i32*, align 8
  store i32** %0, i32*** %2, align 8
  call void @llvm.dbg.declare(metadata i32*** %2, metadata !18, metadata !DIExpression()), !dbg !19
  call void @llvm.dbg.declare(metadata i32** %3, metadata !20, metadata !DIExpression()), !dbg !21
  %4 = load i32**, i32*** %2, align 8, !dbg !22
  %5 = load i32*, i32** %4, align 8, !dbg !23
  store i32* %5, i32** %3, align 8, !dbg !21
  %6 = load i32*, i32** %3, align 8, !dbg !24
  %7 = load i32, i32* %6, align 4, !dbg !26
  %8 = icmp sgt i32 %7, 10, !dbg !27
  br i1 %8, label %9, label %13, !dbg !28

9:                                                ; preds = %1
  %10 = load i32**, i32*** %2, align 8, !dbg !29
  %11 = load i32*, i32** %10, align 8, !dbg !31
  %12 = load i32**, i32*** @p, align 8, !dbg !32
  store i32* %11, i32** %12, align 8, !dbg !33
  br label %16, !dbg !34

13:                                               ; preds = %1
  %14 = load i32*, i32** @y, align 8, !dbg !35
  %15 = load i32**, i32*** @p, align 8, !dbg !37
  store i32* %14, i32** %15, align 8, !dbg !38
  br label %16

16:                                               ; preds = %13, %9
  %17 = load i32*, i32** %3, align 8, !dbg !39
  store i32* %17, i32** @y, align 8, !dbg !40
  %18 = load i32*, i32** @y, align 8, !dbg !41
  %19 = load i32**, i32*** %2, align 8, !dbg !42
  store i32* %18, i32** %19, align 8, !dbg !43
  ret void, !dbg !44
}

; Function Attrs: nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main(i32 %0, i8** %1) #0 !dbg !45 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i8**, align 8
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  %8 = alloca i32*, align 8
  %9 = alloca i32*, align 8
  %10 = alloca i32**, align 8
  store i32 0, i32* %3, align 4
  store i32 %0, i32* %4, align 4
  call void @llvm.dbg.declare(metadata i32* %4, metadata !51, metadata !DIExpression()), !dbg !52
  store i8** %1, i8*** %5, align 8
  call void @llvm.dbg.declare(metadata i8*** %5, metadata !53, metadata !DIExpression()), !dbg !54
  call void @llvm.dbg.declare(metadata i32* %6, metadata !55, metadata !DIExpression()), !dbg !56
  store i32 4, i32* %6, align 4, !dbg !56
  call void @llvm.dbg.declare(metadata i32* %7, metadata !57, metadata !DIExpression()), !dbg !58
  store i32 5, i32* %7, align 4, !dbg !58
  call void @llvm.dbg.declare(metadata i32** %8, metadata !59, metadata !DIExpression()), !dbg !60
  store i32* %6, i32** %8, align 8, !dbg !60
  call void @llvm.dbg.declare(metadata i32** %9, metadata !61, metadata !DIExpression()), !dbg !62
  store i32* %7, i32** %9, align 8, !dbg !62
  call void @llvm.dbg.declare(metadata i32*** %10, metadata !63, metadata !DIExpression()), !dbg !64
  %11 = load i32, i32* %6, align 4, !dbg !65
  %12 = mul nsw i32 %11, 4, !dbg !67
  %13 = icmp eq i32 %12, 16, !dbg !68
  br i1 %13, label %14, label %15, !dbg !69

14:                                               ; preds = %2
  store i32** %8, i32*** %10, align 8, !dbg !70
  br label %16, !dbg !72

15:                                               ; preds = %2
  store i32** %9, i32*** %10, align 8, !dbg !73
  br label %16

16:                                               ; preds = %15, %14
  %17 = load i32**, i32*** %10, align 8, !dbg !75
  call void @f(i32** %17), !dbg !76
  %18 = load i32**, i32*** %10, align 8, !dbg !77
  %19 = load i32*, i32** %18, align 8, !dbg !78
  store i32* %19, i32** %8, align 8, !dbg !79
  ret i32 1, !dbg !80
}

attributes #0 = { noinline nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone speculatable willreturn }

!llvm.dbg.cu = !{!2}
!llvm.module.flags = !{!11, !12, !13}
!llvm.ident = !{!14}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(name: "p", scope: !2, file: !3, line: 3, type: !10, isLocal: false, isDefinition: true)
!2 = distinct !DICompileUnit(language: DW_LANG_C99, file: !3, producer: "clang version 10.0.0-4ubuntu1 ", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !4, globals: !5, splitDebugInlining: false, nameTableKind: None)
!3 = !DIFile(filename: "ex5.c", directory: "/home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/GPG_Impl/TestCases")
!4 = !{}
!5 = !{!0, !6}
!6 = !DIGlobalVariableExpression(var: !7, expr: !DIExpression())
!7 = distinct !DIGlobalVariable(name: "y", scope: !2, file: !3, line: 4, type: !8, isLocal: false, isDefinition: true)
!8 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !9, size: 64)
!9 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!10 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !8, size: 64)
!11 = !{i32 7, !"Dwarf Version", i32 4}
!12 = !{i32 2, !"Debug Info Version", i32 3}
!13 = !{i32 1, !"wchar_size", i32 4}
!14 = !{!"clang version 10.0.0-4ubuntu1 "}
!15 = distinct !DISubprogram(name: "f", scope: !3, file: !3, line: 6, type: !16, scopeLine: 6, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!16 = !DISubroutineType(types: !17)
!17 = !{null, !10}
!18 = !DILocalVariable(name: "x", arg: 1, scope: !15, file: !3, line: 6, type: !10)
!19 = !DILocation(line: 6, column: 14, scope: !15)
!20 = !DILocalVariable(name: "temp", scope: !15, file: !3, line: 7, type: !8)
!21 = !DILocation(line: 7, column: 10, scope: !15)
!22 = !DILocation(line: 7, column: 18, scope: !15)
!23 = !DILocation(line: 7, column: 17, scope: !15)
!24 = !DILocation(line: 8, column: 9, scope: !25)
!25 = distinct !DILexicalBlock(scope: !15, file: !3, line: 8, column: 8)
!26 = !DILocation(line: 8, column: 8, scope: !25)
!27 = !DILocation(line: 8, column: 14, scope: !25)
!28 = !DILocation(line: 8, column: 8, scope: !15)
!29 = !DILocation(line: 9, column: 15, scope: !30)
!30 = distinct !DILexicalBlock(scope: !25, file: !3, line: 8, column: 19)
!31 = !DILocation(line: 9, column: 14, scope: !30)
!32 = !DILocation(line: 9, column: 10, scope: !30)
!33 = !DILocation(line: 9, column: 12, scope: !30)
!34 = !DILocation(line: 10, column: 5, scope: !30)
!35 = !DILocation(line: 12, column: 14, scope: !36)
!36 = distinct !DILexicalBlock(scope: !25, file: !3, line: 10, column: 10)
!37 = !DILocation(line: 12, column: 10, scope: !36)
!38 = !DILocation(line: 12, column: 12, scope: !36)
!39 = !DILocation(line: 14, column: 9, scope: !15)
!40 = !DILocation(line: 14, column: 7, scope: !15)
!41 = !DILocation(line: 15, column: 10, scope: !15)
!42 = !DILocation(line: 15, column: 6, scope: !15)
!43 = !DILocation(line: 15, column: 8, scope: !15)
!44 = !DILocation(line: 18, column: 1, scope: !15)
!45 = distinct !DISubprogram(name: "main", scope: !3, file: !3, line: 20, type: !46, scopeLine: 20, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!46 = !DISubroutineType(types: !47)
!47 = !{!9, !9, !48}
!48 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !49, size: 64)
!49 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !50, size: 64)
!50 = !DIBasicType(name: "char", size: 8, encoding: DW_ATE_signed_char)
!51 = !DILocalVariable(name: "argc", arg: 1, scope: !45, file: !3, line: 20, type: !9)
!52 = !DILocation(line: 20, column: 14, scope: !45)
!53 = !DILocalVariable(name: "argv", arg: 2, scope: !45, file: !3, line: 20, type: !48)
!54 = !DILocation(line: 20, column: 26, scope: !45)
!55 = !DILocalVariable(name: "a", scope: !45, file: !3, line: 21, type: !9)
!56 = !DILocation(line: 21, column: 9, scope: !45)
!57 = !DILocalVariable(name: "b", scope: !45, file: !3, line: 22, type: !9)
!58 = !DILocation(line: 22, column: 9, scope: !45)
!59 = !DILocalVariable(name: "c", scope: !45, file: !3, line: 23, type: !8)
!60 = !DILocation(line: 23, column: 10, scope: !45)
!61 = !DILocalVariable(name: "d", scope: !45, file: !3, line: 24, type: !8)
!62 = !DILocation(line: 24, column: 10, scope: !45)
!63 = !DILocalVariable(name: "x", scope: !45, file: !3, line: 25, type: !10)
!64 = !DILocation(line: 25, column: 8, scope: !45)
!65 = !DILocation(line: 26, column: 5, scope: !66)
!66 = distinct !DILexicalBlock(scope: !45, file: !3, line: 26, column: 5)
!67 = !DILocation(line: 26, column: 6, scope: !66)
!68 = !DILocation(line: 26, column: 9, scope: !66)
!69 = !DILocation(line: 26, column: 5, scope: !45)
!70 = !DILocation(line: 27, column: 8, scope: !71)
!71 = distinct !DILexicalBlock(scope: !66, file: !3, line: 26, column: 16)
!72 = !DILocation(line: 28, column: 2, scope: !71)
!73 = !DILocation(line: 29, column: 8, scope: !74)
!74 = distinct !DILexicalBlock(scope: !66, file: !3, line: 28, column: 7)
!75 = !DILocation(line: 31, column: 4, scope: !45)
!76 = !DILocation(line: 31, column: 2, scope: !45)
!77 = !DILocation(line: 32, column: 7, scope: !45)
!78 = !DILocation(line: 32, column: 6, scope: !45)
!79 = !DILocation(line: 32, column: 4, scope: !45)
!80 = !DILocation(line: 33, column: 2, scope: !45)
