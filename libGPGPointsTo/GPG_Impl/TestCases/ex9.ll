; ModuleID = 'ex9.c'
source_filename = "ex9.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [6 x i8] c"%p %d\00", align 1

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @f(i32* %0) #0 !dbg !7 {
  %2 = alloca i32*, align 8
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  store i32* %0, i32** %2, align 8
  call void @llvm.dbg.declare(metadata i32** %2, metadata !12, metadata !DIExpression()), !dbg !13
  call void @llvm.dbg.declare(metadata i32* %3, metadata !14, metadata !DIExpression()), !dbg !15
  store i32 5, i32* %3, align 4, !dbg !15
  call void @llvm.dbg.declare(metadata i32* %4, metadata !16, metadata !DIExpression()), !dbg !17
  store i32 10, i32* %4, align 4, !dbg !17
  call void @llvm.dbg.declare(metadata i32* %5, metadata !18, metadata !DIExpression()), !dbg !19
  store i32 20, i32* %5, align 4, !dbg !19
  store i32* %3, i32** %2, align 8, !dbg !20
  %6 = load i32*, i32** %2, align 8, !dbg !21
  %7 = load i32, i32* %6, align 4, !dbg !23
  %8 = icmp sgt i32 %7, 10, !dbg !24
  br i1 %8, label %9, label %10, !dbg !25

9:                                                ; preds = %1
  store i32* %4, i32** %2, align 8, !dbg !26
  br label %11, !dbg !27

10:                                               ; preds = %1
  store i32* %5, i32** %2, align 8, !dbg !28
  br label %11

11:                                               ; preds = %10, %9
  %12 = load i32*, i32** %2, align 8, !dbg !29
  %13 = load i32, i32* %12, align 4, !dbg !30
  ret i32 %13, !dbg !31
}

; Function Attrs: nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main() #0 !dbg !32 {
  %1 = alloca i32, align 4
  %2 = alloca i32*, align 8
  %3 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  call void @llvm.dbg.declare(metadata i32** %2, metadata !35, metadata !DIExpression()), !dbg !36
  call void @llvm.dbg.declare(metadata i32* %3, metadata !37, metadata !DIExpression()), !dbg !38
  store i32 5, i32* %3, align 4, !dbg !38
  store i32* %3, i32** %2, align 8, !dbg !39
  %4 = load i32*, i32** %2, align 8, !dbg !40
  store i32 6, i32* %4, align 4, !dbg !41
  %5 = load i32*, i32** %2, align 8, !dbg !42
  %6 = load i32*, i32** %2, align 8, !dbg !43
  %7 = load i32, i32* %6, align 4, !dbg !44
  %8 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str, i64 0, i64 0), i32* %5, i32 %7), !dbg !45
  %9 = load i32*, i32** %2, align 8, !dbg !46
  %10 = call i32 @f(i32* %9), !dbg !47
  ret i32 1, !dbg !48
}

declare dso_local i32 @printf(i8*, ...) #2

attributes #0 = { noinline nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone speculatable willreturn }
attributes #2 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!3, !4, !5}
!llvm.ident = !{!6}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 10.0.0-4ubuntu1 ", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !2, splitDebugInlining: false, nameTableKind: None)
!1 = !DIFile(filename: "ex9.c", directory: "/home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/GPG_Impl/TestCases")
!2 = !{}
!3 = !{i32 7, !"Dwarf Version", i32 4}
!4 = !{i32 2, !"Debug Info Version", i32 3}
!5 = !{i32 1, !"wchar_size", i32 4}
!6 = !{!"clang version 10.0.0-4ubuntu1 "}
!7 = distinct !DISubprogram(name: "f", scope: !1, file: !1, line: 3, type: !8, scopeLine: 3, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !2)
!8 = !DISubroutineType(types: !9)
!9 = !{!10, !11}
!10 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!11 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !10, size: 64)
!12 = !DILocalVariable(name: "x", arg: 1, scope: !7, file: !1, line: 3, type: !11)
!13 = !DILocation(line: 3, column: 12, scope: !7)
!14 = !DILocalVariable(name: "a", scope: !7, file: !1, line: 4, type: !10)
!15 = !DILocation(line: 4, column: 9, scope: !7)
!16 = !DILocalVariable(name: "b", scope: !7, file: !1, line: 5, type: !10)
!17 = !DILocation(line: 5, column: 9, scope: !7)
!18 = !DILocalVariable(name: "c", scope: !7, file: !1, line: 6, type: !10)
!19 = !DILocation(line: 6, column: 9, scope: !7)
!20 = !DILocation(line: 7, column: 7, scope: !7)
!21 = !DILocation(line: 8, column: 9, scope: !22)
!22 = distinct !DILexicalBlock(scope: !7, file: !1, line: 8, column: 8)
!23 = !DILocation(line: 8, column: 8, scope: !22)
!24 = !DILocation(line: 8, column: 11, scope: !22)
!25 = !DILocation(line: 8, column: 8, scope: !7)
!26 = !DILocation(line: 9, column: 11, scope: !22)
!27 = !DILocation(line: 9, column: 9, scope: !22)
!28 = !DILocation(line: 11, column: 11, scope: !22)
!29 = !DILocation(line: 12, column: 13, scope: !7)
!30 = !DILocation(line: 12, column: 12, scope: !7)
!31 = !DILocation(line: 12, column: 5, scope: !7)
!32 = distinct !DISubprogram(name: "main", scope: !1, file: !1, line: 15, type: !33, scopeLine: 15, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !2)
!33 = !DISubroutineType(types: !34)
!34 = !{!10}
!35 = !DILocalVariable(name: "p", scope: !32, file: !1, line: 16, type: !11)
!36 = !DILocation(line: 16, column: 10, scope: !32)
!37 = !DILocalVariable(name: "x", scope: !32, file: !1, line: 17, type: !10)
!38 = !DILocation(line: 17, column: 9, scope: !32)
!39 = !DILocation(line: 18, column: 7, scope: !32)
!40 = !DILocation(line: 19, column: 6, scope: !32)
!41 = !DILocation(line: 19, column: 8, scope: !32)
!42 = !DILocation(line: 20, column: 21, scope: !32)
!43 = !DILocation(line: 20, column: 25, scope: !32)
!44 = !DILocation(line: 20, column: 24, scope: !32)
!45 = !DILocation(line: 20, column: 5, scope: !32)
!46 = !DILocation(line: 21, column: 7, scope: !32)
!47 = !DILocation(line: 21, column: 5, scope: !32)
!48 = !DILocation(line: 22, column: 5, scope: !32)
