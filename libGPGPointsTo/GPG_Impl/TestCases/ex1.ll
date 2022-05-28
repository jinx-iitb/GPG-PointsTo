; ModuleID = 'ex1.c'
source_filename = "ex1.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: noinline nounwind uwtable
define dso_local void @f(i32** %x, i32** %y) #0 !dbg !7 {
entry:
  %x.addr = alloca i32**, align 8
  %y.addr = alloca i32**, align 8
  %temp = alloca i32*, align 8
  store i32** %x, i32*** %x.addr, align 8
  call void @llvm.dbg.declare(metadata i32*** %x.addr, metadata !13, metadata !DIExpression()), !dbg !14
  store i32** %y, i32*** %y.addr, align 8
  call void @llvm.dbg.declare(metadata i32*** %y.addr, metadata !15, metadata !DIExpression()), !dbg !16
  call void @llvm.dbg.declare(metadata i32** %temp, metadata !17, metadata !DIExpression()), !dbg !18
  %0 = load i32**, i32*** %x.addr, align 8, !dbg !19
  %1 = load i32*, i32** %0, align 8, !dbg !20
  store i32* %1, i32** %temp, align 8, !dbg !18
  %2 = load i32**, i32*** %y.addr, align 8, !dbg !21
  %3 = load i32*, i32** %2, align 8, !dbg !22
  %4 = load i32**, i32*** %x.addr, align 8, !dbg !23
  store i32* %3, i32** %4, align 8, !dbg !24
  %5 = load i32*, i32** %temp, align 8, !dbg !25
  %6 = load i32**, i32*** %y.addr, align 8, !dbg !26
  store i32* %5, i32** %6, align 8, !dbg !27
  ret void, !dbg !28
}

; Function Attrs: nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main(i32 %argc, i8** %argv) #0 !dbg !29 {
entry:
  %retval = alloca i32, align 4
  %argc.addr = alloca i32, align 4
  %argv.addr = alloca i8**, align 8
  %a = alloca i32, align 4
  %b = alloca i32, align 4
  %c = alloca i32*, align 8
  %d = alloca i32*, align 8
  store i32 0, i32* %retval, align 4
  store i32 %argc, i32* %argc.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %argc.addr, metadata !35, metadata !DIExpression()), !dbg !36
  store i8** %argv, i8*** %argv.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %argv.addr, metadata !37, metadata !DIExpression()), !dbg !38
  call void @llvm.dbg.declare(metadata i32* %a, metadata !39, metadata !DIExpression()), !dbg !40
  store i32 4, i32* %a, align 4, !dbg !40
  call void @llvm.dbg.declare(metadata i32* %b, metadata !41, metadata !DIExpression()), !dbg !42
  store i32 5, i32* %b, align 4, !dbg !42
  call void @llvm.dbg.declare(metadata i32** %c, metadata !43, metadata !DIExpression()), !dbg !44
  store i32* %a, i32** %c, align 8, !dbg !44
  call void @llvm.dbg.declare(metadata i32** %d, metadata !45, metadata !DIExpression()), !dbg !46
  call void @f(i32** %c, i32** %d), !dbg !47
  %0 = load i32*, i32** %c, align 8, !dbg !48
  store i32* %0, i32** %d, align 8, !dbg !49
  ret i32 1, !dbg !50
}

attributes #0 = { noinline nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone speculatable willreturn }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!3, !4, !5}
!llvm.ident = !{!6}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 10.0.0-4ubuntu1 ", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !2, splitDebugInlining: false, nameTableKind: None)
!1 = !DIFile(filename: "ex1.c", directory: "/home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/GPG_Impl/TestCases")
!2 = !{}
!3 = !{i32 7, !"Dwarf Version", i32 4}
!4 = !{i32 2, !"Debug Info Version", i32 3}
!5 = !{i32 1, !"wchar_size", i32 4}
!6 = !{!"clang version 10.0.0-4ubuntu1 "}
!7 = distinct !DISubprogram(name: "f", scope: !1, file: !1, line: 3, type: !8, scopeLine: 3, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !2)
!8 = !DISubroutineType(types: !9)
!9 = !{null, !10, !10}
!10 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !11, size: 64)
!11 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !12, size: 64)
!12 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!13 = !DILocalVariable(name: "x", arg: 1, scope: !7, file: !1, line: 3, type: !10)
!14 = !DILocation(line: 3, column: 14, scope: !7)
!15 = !DILocalVariable(name: "y", arg: 2, scope: !7, file: !1, line: 3, type: !10)
!16 = !DILocation(line: 3, column: 23, scope: !7)
!17 = !DILocalVariable(name: "temp", scope: !7, file: !1, line: 4, type: !11)
!18 = !DILocation(line: 4, column: 10, scope: !7)
!19 = !DILocation(line: 4, column: 18, scope: !7)
!20 = !DILocation(line: 4, column: 17, scope: !7)
!21 = !DILocation(line: 5, column: 11, scope: !7)
!22 = !DILocation(line: 5, column: 10, scope: !7)
!23 = !DILocation(line: 5, column: 6, scope: !7)
!24 = !DILocation(line: 5, column: 8, scope: !7)
!25 = !DILocation(line: 6, column: 10, scope: !7)
!26 = !DILocation(line: 6, column: 6, scope: !7)
!27 = !DILocation(line: 6, column: 8, scope: !7)
!28 = !DILocation(line: 7, column: 1, scope: !7)
!29 = distinct !DISubprogram(name: "main", scope: !1, file: !1, line: 10, type: !30, scopeLine: 10, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !2)
!30 = !DISubroutineType(types: !31)
!31 = !{!12, !12, !32}
!32 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !33, size: 64)
!33 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !34, size: 64)
!34 = !DIBasicType(name: "char", size: 8, encoding: DW_ATE_signed_char)
!35 = !DILocalVariable(name: "argc", arg: 1, scope: !29, file: !1, line: 10, type: !12)
!36 = !DILocation(line: 10, column: 14, scope: !29)
!37 = !DILocalVariable(name: "argv", arg: 2, scope: !29, file: !1, line: 10, type: !32)
!38 = !DILocation(line: 10, column: 26, scope: !29)
!39 = !DILocalVariable(name: "a", scope: !29, file: !1, line: 11, type: !12)
!40 = !DILocation(line: 11, column: 9, scope: !29)
!41 = !DILocalVariable(name: "b", scope: !29, file: !1, line: 12, type: !12)
!42 = !DILocation(line: 12, column: 9, scope: !29)
!43 = !DILocalVariable(name: "c", scope: !29, file: !1, line: 13, type: !11)
!44 = !DILocation(line: 13, column: 10, scope: !29)
!45 = !DILocalVariable(name: "d", scope: !29, file: !1, line: 14, type: !11)
!46 = !DILocation(line: 14, column: 10, scope: !29)
!47 = !DILocation(line: 17, column: 2, scope: !29)
!48 = !DILocation(line: 19, column: 6, scope: !29)
!49 = !DILocation(line: 19, column: 4, scope: !29)
!50 = !DILocation(line: 21, column: 2, scope: !29)
