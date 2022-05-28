; ModuleID = 'ex6.c'
source_filename = "ex6.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@k = dso_local global i32 5, align 4, !dbg !0
@.str = private unnamed_addr constant [3 x i8] c"%p\00", align 1
@o = common dso_local global i32 0, align 4, !dbg !6

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main(i32 %0, i8** %1) #0 !dbg !13 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i8**, align 8
  %6 = alloca i32*, align 8
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  %9 = alloca i32*, align 8
  %10 = alloca i32*, align 8
  %11 = alloca i32**, align 8
  store i32 0, i32* %3, align 4
  store i32 %0, i32* %4, align 4
  call void @llvm.dbg.declare(metadata i32* %4, metadata !19, metadata !DIExpression()), !dbg !20
  store i8** %1, i8*** %5, align 8
  call void @llvm.dbg.declare(metadata i8*** %5, metadata !21, metadata !DIExpression()), !dbg !22
  call void @llvm.dbg.declare(metadata i32** %6, metadata !23, metadata !DIExpression()), !dbg !25
  store i32* @k, i32** %6, align 8, !dbg !25
  %12 = load i32*, i32** %6, align 8, !dbg !26
  %13 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str, i64 0, i64 0), i32* %12), !dbg !27
  call void @llvm.dbg.declare(metadata i32* %7, metadata !28, metadata !DIExpression()), !dbg !29
  store i32 4, i32* %7, align 4, !dbg !29
  call void @llvm.dbg.declare(metadata i32* %8, metadata !30, metadata !DIExpression()), !dbg !31
  %14 = load i32*, i32** %6, align 8, !dbg !32
  %15 = load i32, i32* %14, align 4, !dbg !33
  store i32 %15, i32* %8, align 4, !dbg !31
  call void @llvm.dbg.declare(metadata i32** %9, metadata !34, metadata !DIExpression()), !dbg !35
  store i32* %7, i32** %9, align 8, !dbg !35
  call void @llvm.dbg.declare(metadata i32** %10, metadata !36, metadata !DIExpression()), !dbg !37
  store i32* %8, i32** %10, align 8, !dbg !37
  call void @llvm.dbg.declare(metadata i32*** %11, metadata !38, metadata !DIExpression()), !dbg !40
  %16 = load i32, i32* %7, align 4, !dbg !41
  %17 = mul nsw i32 %16, 4, !dbg !43
  %18 = icmp eq i32 %17, 16, !dbg !44
  br i1 %18, label %19, label %20, !dbg !45

19:                                               ; preds = %2
  store i32** %9, i32*** %11, align 8, !dbg !46
  br label %21, !dbg !48

20:                                               ; preds = %2
  store i32** %10, i32*** %11, align 8, !dbg !49
  br label %21

21:                                               ; preds = %20, %19
  %22 = load i32**, i32*** %11, align 8, !dbg !51
  %23 = load i32*, i32** %22, align 8, !dbg !52
  store i32* %23, i32** %9, align 8, !dbg !53
  %24 = load i32, i32* @k, align 4, !dbg !54
  ret i32 %24, !dbg !55
}

; Function Attrs: nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare dso_local i32 @printf(i8*, ...) #2

attributes #0 = { noinline nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone speculatable willreturn }
attributes #2 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!2}
!llvm.module.flags = !{!9, !10, !11}
!llvm.ident = !{!12}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(name: "k", scope: !2, file: !3, line: 3, type: !8, isLocal: false, isDefinition: true)
!2 = distinct !DICompileUnit(language: DW_LANG_C99, file: !3, producer: "clang version 10.0.0-4ubuntu1 ", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !4, globals: !5, splitDebugInlining: false, nameTableKind: None)
!3 = !DIFile(filename: "ex6.c", directory: "/home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/GPG_Impl/TestCases")
!4 = !{}
!5 = !{!0, !6}
!6 = !DIGlobalVariableExpression(var: !7, expr: !DIExpression())
!7 = distinct !DIGlobalVariable(name: "o", scope: !2, file: !3, line: 4, type: !8, isLocal: false, isDefinition: true)
!8 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!9 = !{i32 7, !"Dwarf Version", i32 4}
!10 = !{i32 2, !"Debug Info Version", i32 3}
!11 = !{i32 1, !"wchar_size", i32 4}
!12 = !{!"clang version 10.0.0-4ubuntu1 "}
!13 = distinct !DISubprogram(name: "main", scope: !3, file: !3, line: 6, type: !14, scopeLine: 6, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!14 = !DISubroutineType(types: !15)
!15 = !{!8, !8, !16}
!16 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !17, size: 64)
!17 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !18, size: 64)
!18 = !DIBasicType(name: "char", size: 8, encoding: DW_ATE_signed_char)
!19 = !DILocalVariable(name: "argc", arg: 1, scope: !13, file: !3, line: 6, type: !8)
!20 = !DILocation(line: 6, column: 14, scope: !13)
!21 = !DILocalVariable(name: "argv", arg: 2, scope: !13, file: !3, line: 6, type: !16)
!22 = !DILocation(line: 6, column: 26, scope: !13)
!23 = !DILocalVariable(name: "l", scope: !13, file: !3, line: 7, type: !24)
!24 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !8, size: 64)
!25 = !DILocation(line: 7, column: 10, scope: !13)
!26 = !DILocation(line: 8, column: 18, scope: !13)
!27 = !DILocation(line: 8, column: 5, scope: !13)
!28 = !DILocalVariable(name: "a", scope: !13, file: !3, line: 9, type: !8)
!29 = !DILocation(line: 9, column: 9, scope: !13)
!30 = !DILocalVariable(name: "b", scope: !13, file: !3, line: 10, type: !8)
!31 = !DILocation(line: 10, column: 9, scope: !13)
!32 = !DILocation(line: 10, column: 14, scope: !13)
!33 = !DILocation(line: 10, column: 13, scope: !13)
!34 = !DILocalVariable(name: "c", scope: !13, file: !3, line: 11, type: !24)
!35 = !DILocation(line: 11, column: 10, scope: !13)
!36 = !DILocalVariable(name: "d", scope: !13, file: !3, line: 12, type: !24)
!37 = !DILocation(line: 12, column: 10, scope: !13)
!38 = !DILocalVariable(name: "x", scope: !13, file: !3, line: 13, type: !39)
!39 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !24, size: 64)
!40 = !DILocation(line: 13, column: 8, scope: !13)
!41 = !DILocation(line: 14, column: 5, scope: !42)
!42 = distinct !DILexicalBlock(scope: !13, file: !3, line: 14, column: 5)
!43 = !DILocation(line: 14, column: 6, scope: !42)
!44 = !DILocation(line: 14, column: 9, scope: !42)
!45 = !DILocation(line: 14, column: 5, scope: !13)
!46 = !DILocation(line: 15, column: 8, scope: !47)
!47 = distinct !DILexicalBlock(scope: !42, file: !3, line: 14, column: 16)
!48 = !DILocation(line: 16, column: 2, scope: !47)
!49 = !DILocation(line: 17, column: 8, scope: !50)
!50 = distinct !DILexicalBlock(scope: !42, file: !3, line: 16, column: 7)
!51 = !DILocation(line: 19, column: 7, scope: !13)
!52 = !DILocation(line: 19, column: 6, scope: !13)
!53 = !DILocation(line: 19, column: 4, scope: !13)
!54 = !DILocation(line: 20, column: 9, scope: !13)
!55 = !DILocation(line: 20, column: 2, scope: !13)
