; ModuleID = 'ex8.c'
source_filename = "ex8.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@z = common dso_local global i32* null, align 8, !dbg !0
@.str = private unnamed_addr constant [6 x i8] c"hello\00", align 1
@.str.1 = private unnamed_addr constant [13 x i8] c"%d %d %d %d\0A\00", align 1

; Function Attrs: noinline nounwind uwtable
define dso_local void @f(i32** %0, i32** %1) #0 !dbg !12 {
  %3 = alloca i32**, align 8
  %4 = alloca i32**, align 8
  %5 = alloca i32*, align 8
  store i32** %0, i32*** %3, align 8
  call void @llvm.dbg.declare(metadata i32*** %3, metadata !16, metadata !DIExpression()), !dbg !17
  store i32** %1, i32*** %4, align 8
  call void @llvm.dbg.declare(metadata i32*** %4, metadata !18, metadata !DIExpression()), !dbg !19
  %6 = load i32**, i32*** %4, align 8, !dbg !20
  %7 = load i32*, i32** %6, align 8, !dbg !21
  store i32* %7, i32** @z, align 8, !dbg !22
  call void @llvm.dbg.declare(metadata i32** %5, metadata !23, metadata !DIExpression()), !dbg !24
  %8 = load i32**, i32*** %3, align 8, !dbg !25
  %9 = load i32*, i32** %8, align 8, !dbg !26
  store i32* %9, i32** %5, align 8, !dbg !24
  %10 = load i32**, i32*** %4, align 8, !dbg !27
  %11 = load i32*, i32** %10, align 8, !dbg !28
  %12 = load i32**, i32*** %3, align 8, !dbg !29
  store i32* %11, i32** %12, align 8, !dbg !30
  %13 = load i32*, i32** %5, align 8, !dbg !31
  %14 = load i32**, i32*** %4, align 8, !dbg !32
  store i32* %13, i32** %14, align 8, !dbg !33
  ret void, !dbg !34
}

; Function Attrs: nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: noinline nounwind uwtable
define dso_local void @g() #0 !dbg !35 {
  %1 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str, i64 0, i64 0)), !dbg !38
  ret void, !dbg !39
}

declare dso_local i32 @printf(i8*, ...) #2

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main(i32 %0, i8** %1) #0 !dbg !40 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i8**, align 8
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  %8 = alloca i32*, align 8
  %9 = alloca i32*, align 8
  store i32 0, i32* %3, align 4
  store i32 %0, i32* %4, align 4
  call void @llvm.dbg.declare(metadata i32* %4, metadata !46, metadata !DIExpression()), !dbg !47
  store i8** %1, i8*** %5, align 8
  call void @llvm.dbg.declare(metadata i8*** %5, metadata !48, metadata !DIExpression()), !dbg !49
  call void @llvm.dbg.declare(metadata i32* %6, metadata !50, metadata !DIExpression()), !dbg !51
  store i32 4, i32* %6, align 4, !dbg !51
  call void @llvm.dbg.declare(metadata i32* %7, metadata !52, metadata !DIExpression()), !dbg !53
  store i32 5, i32* %7, align 4, !dbg !53
  call void @llvm.dbg.declare(metadata i32** %8, metadata !54, metadata !DIExpression()), !dbg !55
  store i32* %6, i32** %8, align 8, !dbg !55
  call void @llvm.dbg.declare(metadata i32** %9, metadata !56, metadata !DIExpression()), !dbg !57
  store i32* %7, i32** %9, align 8, !dbg !57
  %10 = load i32*, i32** %8, align 8, !dbg !58
  %11 = load i32, i32* %10, align 4, !dbg !59
  %12 = load i32*, i32** %9, align 8, !dbg !60
  %13 = load i32, i32* %12, align 4, !dbg !61
  %14 = load i32, i32* %6, align 4, !dbg !62
  %15 = load i32, i32* %7, align 4, !dbg !63
  %16 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.1, i64 0, i64 0), i32 %11, i32 %13, i32 %14, i32 %15), !dbg !64
  call void @f(i32** %8, i32** %9), !dbg !65
  %17 = load i32*, i32** %8, align 8, !dbg !66
  %18 = load i32, i32* %17, align 4, !dbg !67
  %19 = load i32*, i32** %9, align 8, !dbg !68
  %20 = load i32, i32* %19, align 4, !dbg !69
  %21 = load i32, i32* %6, align 4, !dbg !70
  %22 = load i32, i32* %7, align 4, !dbg !71
  %23 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.1, i64 0, i64 0), i32 %18, i32 %20, i32 %21, i32 %22), !dbg !72
  ret i32 1, !dbg !73
}

attributes #0 = { noinline nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone speculatable willreturn }
attributes #2 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!2}
!llvm.module.flags = !{!8, !9, !10}
!llvm.ident = !{!11}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(name: "z", scope: !2, file: !3, line: 3, type: !6, isLocal: false, isDefinition: true)
!2 = distinct !DICompileUnit(language: DW_LANG_C99, file: !3, producer: "clang version 10.0.0-4ubuntu1 ", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !4, globals: !5, splitDebugInlining: false, nameTableKind: None)
!3 = !DIFile(filename: "ex8.c", directory: "/home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/GPG_Impl/TestCases")
!4 = !{}
!5 = !{!0}
!6 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !7, size: 64)
!7 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!8 = !{i32 7, !"Dwarf Version", i32 4}
!9 = !{i32 2, !"Debug Info Version", i32 3}
!10 = !{i32 1, !"wchar_size", i32 4}
!11 = !{!"clang version 10.0.0-4ubuntu1 "}
!12 = distinct !DISubprogram(name: "f", scope: !3, file: !3, line: 5, type: !13, scopeLine: 5, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!13 = !DISubroutineType(types: !14)
!14 = !{null, !15, !15}
!15 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !6, size: 64)
!16 = !DILocalVariable(name: "x", arg: 1, scope: !12, file: !3, line: 5, type: !15)
!17 = !DILocation(line: 5, column: 14, scope: !12)
!18 = !DILocalVariable(name: "y", arg: 2, scope: !12, file: !3, line: 5, type: !15)
!19 = !DILocation(line: 5, column: 23, scope: !12)
!20 = !DILocation(line: 6, column: 10, scope: !12)
!21 = !DILocation(line: 6, column: 9, scope: !12)
!22 = !DILocation(line: 6, column: 7, scope: !12)
!23 = !DILocalVariable(name: "temp", scope: !12, file: !3, line: 7, type: !6)
!24 = !DILocation(line: 7, column: 10, scope: !12)
!25 = !DILocation(line: 7, column: 18, scope: !12)
!26 = !DILocation(line: 7, column: 17, scope: !12)
!27 = !DILocation(line: 8, column: 11, scope: !12)
!28 = !DILocation(line: 8, column: 10, scope: !12)
!29 = !DILocation(line: 8, column: 6, scope: !12)
!30 = !DILocation(line: 8, column: 8, scope: !12)
!31 = !DILocation(line: 9, column: 10, scope: !12)
!32 = !DILocation(line: 9, column: 6, scope: !12)
!33 = !DILocation(line: 9, column: 8, scope: !12)
!34 = !DILocation(line: 10, column: 1, scope: !12)
!35 = distinct !DISubprogram(name: "g", scope: !3, file: !3, line: 12, type: !36, scopeLine: 12, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!36 = !DISubroutineType(types: !37)
!37 = !{null}
!38 = !DILocation(line: 14, column: 1, scope: !35)
!39 = !DILocation(line: 15, column: 1, scope: !35)
!40 = distinct !DISubprogram(name: "main", scope: !3, file: !3, line: 18, type: !41, scopeLine: 18, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!41 = !DISubroutineType(types: !42)
!42 = !{!7, !7, !43}
!43 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !44, size: 64)
!44 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !45, size: 64)
!45 = !DIBasicType(name: "char", size: 8, encoding: DW_ATE_signed_char)
!46 = !DILocalVariable(name: "argc", arg: 1, scope: !40, file: !3, line: 18, type: !7)
!47 = !DILocation(line: 18, column: 14, scope: !40)
!48 = !DILocalVariable(name: "argv", arg: 2, scope: !40, file: !3, line: 18, type: !43)
!49 = !DILocation(line: 18, column: 26, scope: !40)
!50 = !DILocalVariable(name: "a", scope: !40, file: !3, line: 19, type: !7)
!51 = !DILocation(line: 19, column: 9, scope: !40)
!52 = !DILocalVariable(name: "b", scope: !40, file: !3, line: 20, type: !7)
!53 = !DILocation(line: 20, column: 9, scope: !40)
!54 = !DILocalVariable(name: "c", scope: !40, file: !3, line: 21, type: !6)
!55 = !DILocation(line: 21, column: 10, scope: !40)
!56 = !DILocalVariable(name: "d", scope: !40, file: !3, line: 22, type: !6)
!57 = !DILocation(line: 22, column: 10, scope: !40)
!58 = !DILocation(line: 23, column: 27, scope: !40)
!59 = !DILocation(line: 23, column: 26, scope: !40)
!60 = !DILocation(line: 23, column: 31, scope: !40)
!61 = !DILocation(line: 23, column: 30, scope: !40)
!62 = !DILocation(line: 23, column: 34, scope: !40)
!63 = !DILocation(line: 23, column: 37, scope: !40)
!64 = !DILocation(line: 23, column: 2, scope: !40)
!65 = !DILocation(line: 24, column: 2, scope: !40)
!66 = !DILocation(line: 25, column: 27, scope: !40)
!67 = !DILocation(line: 25, column: 26, scope: !40)
!68 = !DILocation(line: 25, column: 31, scope: !40)
!69 = !DILocation(line: 25, column: 30, scope: !40)
!70 = !DILocation(line: 25, column: 34, scope: !40)
!71 = !DILocation(line: 25, column: 36, scope: !40)
!72 = !DILocation(line: 25, column: 2, scope: !40)
!73 = !DILocation(line: 26, column: 2, scope: !40)
