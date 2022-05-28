; ModuleID = 'ex4.c'
source_filename = "ex4.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [10 x i8] c"%p %p %d\0A\00", align 1

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main(i32 %0, i8** %1) #0 !dbg !7 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i8**, align 8
  %6 = alloca i32, align 4
  %7 = alloca i32*, align 8
  %8 = alloca i32**, align 8
  store i32 0, i32* %3, align 4
  store i32 %0, i32* %4, align 4
  call void @llvm.dbg.declare(metadata i32* %4, metadata !14, metadata !DIExpression()), !dbg !15
  store i8** %1, i8*** %5, align 8
  call void @llvm.dbg.declare(metadata i8*** %5, metadata !16, metadata !DIExpression()), !dbg !17
  call void @llvm.dbg.declare(metadata i32* %6, metadata !18, metadata !DIExpression()), !dbg !19
  store i32 4, i32* %6, align 4, !dbg !19
  call void @llvm.dbg.declare(metadata i32** %7, metadata !20, metadata !DIExpression()), !dbg !22
  store i32* %6, i32** %7, align 8, !dbg !22
  call void @llvm.dbg.declare(metadata i32*** %8, metadata !23, metadata !DIExpression()), !dbg !25
  store i32** %7, i32*** %8, align 8, !dbg !25
  %9 = load i32**, i32*** %8, align 8, !dbg !26
  %10 = load i32**, i32*** %8, align 8, !dbg !27
  %11 = load i32*, i32** %10, align 8, !dbg !28
  %12 = load i32**, i32*** %8, align 8, !dbg !29
  %13 = load i32*, i32** %12, align 8, !dbg !30
  %14 = load i32, i32* %13, align 4, !dbg !31
  %15 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str, i64 0, i64 0), i32** %9, i32* %11, i32 %14), !dbg !32
  ret i32 1, !dbg !33
}

; Function Attrs: nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare dso_local i32 @printf(i8*, ...) #2

attributes #0 = { noinline nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone speculatable willreturn }
attributes #2 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!3, !4, !5}
!llvm.ident = !{!6}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 10.0.0-4ubuntu1 ", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !2, splitDebugInlining: false, nameTableKind: None)
!1 = !DIFile(filename: "ex4.c", directory: "/home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/GPG_Impl/TestCases")
!2 = !{}
!3 = !{i32 7, !"Dwarf Version", i32 4}
!4 = !{i32 2, !"Debug Info Version", i32 3}
!5 = !{i32 1, !"wchar_size", i32 4}
!6 = !{!"clang version 10.0.0-4ubuntu1 "}
!7 = distinct !DISubprogram(name: "main", scope: !1, file: !1, line: 4, type: !8, scopeLine: 4, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !2)
!8 = !DISubroutineType(types: !9)
!9 = !{!10, !10, !11}
!10 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!11 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !12, size: 64)
!12 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !13, size: 64)
!13 = !DIBasicType(name: "char", size: 8, encoding: DW_ATE_signed_char)
!14 = !DILocalVariable(name: "argc", arg: 1, scope: !7, file: !1, line: 4, type: !10)
!15 = !DILocation(line: 4, column: 14, scope: !7)
!16 = !DILocalVariable(name: "argv", arg: 2, scope: !7, file: !1, line: 4, type: !11)
!17 = !DILocation(line: 4, column: 26, scope: !7)
!18 = !DILocalVariable(name: "a", scope: !7, file: !1, line: 5, type: !10)
!19 = !DILocation(line: 5, column: 9, scope: !7)
!20 = !DILocalVariable(name: "b", scope: !7, file: !1, line: 6, type: !21)
!21 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !10, size: 64)
!22 = !DILocation(line: 6, column: 10, scope: !7)
!23 = !DILocalVariable(name: "c", scope: !7, file: !1, line: 7, type: !24)
!24 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !21, size: 64)
!25 = !DILocation(line: 7, column: 11, scope: !7)
!26 = !DILocation(line: 8, column: 23, scope: !7)
!27 = !DILocation(line: 8, column: 27, scope: !7)
!28 = !DILocation(line: 8, column: 26, scope: !7)
!29 = !DILocation(line: 8, column: 32, scope: !7)
!30 = !DILocation(line: 8, column: 31, scope: !7)
!31 = !DILocation(line: 8, column: 30, scope: !7)
!32 = !DILocation(line: 8, column: 2, scope: !7)
!33 = !DILocation(line: 9, column: 2, scope: !7)
