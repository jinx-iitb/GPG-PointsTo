; ModuleID = 'ex7.cpp'
source_filename = "ex7.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: noinline nounwind uwtable
define dso_local void @_Z1fPi(i32* %0) #0 !dbg !7 {
  %2 = alloca i32*, align 8
  store i32* %0, i32** %2, align 8
  call void @llvm.dbg.declare(metadata i32** %2, metadata !12, metadata !DIExpression()), !dbg !13
  %3 = load i32*, i32** %2, align 8, !dbg !14
  store i32 5, i32* %3, align 4, !dbg !15
  ret void, !dbg !16
}

; Function Attrs: nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: noinline nounwind uwtable
define dso_local void @_Z1gRi(i32* dereferenceable(4) %0) #0 !dbg !17 {
  %2 = alloca i32*, align 8
  store i32* %0, i32** %2, align 8
  call void @llvm.dbg.declare(metadata i32** %2, metadata !21, metadata !DIExpression()), !dbg !22
  %3 = load i32*, i32** %2, align 8, !dbg !23
  store i32 5, i32* %3, align 4, !dbg !24
  ret void, !dbg !25
}

; Function Attrs: noinline norecurse nounwind uwtable
define dso_local i32 @main(i32 %0, i8** %1) #2 !dbg !26 {
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
  call void @llvm.dbg.declare(metadata i32* %4, metadata !32, metadata !DIExpression()), !dbg !33
  store i8** %1, i8*** %5, align 8
  call void @llvm.dbg.declare(metadata i8*** %5, metadata !34, metadata !DIExpression()), !dbg !35
  call void @llvm.dbg.declare(metadata i32* %6, metadata !36, metadata !DIExpression()), !dbg !37
  store i32 4, i32* %6, align 4, !dbg !37
  call void @llvm.dbg.declare(metadata i32* %7, metadata !38, metadata !DIExpression()), !dbg !39
  store i32 5, i32* %7, align 4, !dbg !39
  call void @llvm.dbg.declare(metadata i32** %8, metadata !40, metadata !DIExpression()), !dbg !41
  store i32* %6, i32** %8, align 8, !dbg !41
  call void @llvm.dbg.declare(metadata i32** %9, metadata !42, metadata !DIExpression()), !dbg !43
  store i32* %7, i32** %9, align 8, !dbg !43
  call void @llvm.dbg.declare(metadata i32*** %10, metadata !44, metadata !DIExpression()), !dbg !46
  store i32** %8, i32*** %10, align 8, !dbg !46
  %11 = load i32**, i32*** %10, align 8, !dbg !47
  %12 = load i32*, i32** %11, align 8, !dbg !48
  store i32* %12, i32** %8, align 8, !dbg !49
  %13 = load i32*, i32** %8, align 8, !dbg !50
  call void @_Z1fPi(i32* %13), !dbg !51
  call void @_Z1gRi(i32* dereferenceable(4) %6), !dbg !52
  ret i32 1, !dbg !53
}

attributes #0 = { noinline nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone speculatable willreturn }
attributes #2 = { noinline norecurse nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!3, !4, !5}
!llvm.ident = !{!6}

!0 = distinct !DICompileUnit(language: DW_LANG_C_plus_plus_14, file: !1, producer: "clang version 10.0.0-4ubuntu1 ", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !2, splitDebugInlining: false, nameTableKind: None)
!1 = !DIFile(filename: "ex7.cpp", directory: "/home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/GPG_Impl/TestCases")
!2 = !{}
!3 = !{i32 7, !"Dwarf Version", i32 4}
!4 = !{i32 2, !"Debug Info Version", i32 3}
!5 = !{i32 1, !"wchar_size", i32 4}
!6 = !{!"clang version 10.0.0-4ubuntu1 "}
!7 = distinct !DISubprogram(name: "f", linkageName: "_Z1fPi", scope: !1, file: !1, line: 3, type: !8, scopeLine: 3, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !2)
!8 = !DISubroutineType(types: !9)
!9 = !{null, !10}
!10 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !11, size: 64)
!11 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!12 = !DILocalVariable(name: "x", arg: 1, scope: !7, file: !1, line: 3, type: !10)
!13 = !DILocation(line: 3, column: 13, scope: !7)
!14 = !DILocation(line: 4, column: 6, scope: !7)
!15 = !DILocation(line: 4, column: 8, scope: !7)
!16 = !DILocation(line: 5, column: 1, scope: !7)
!17 = distinct !DISubprogram(name: "g", linkageName: "_Z1gRi", scope: !1, file: !1, line: 7, type: !18, scopeLine: 7, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !2)
!18 = !DISubroutineType(types: !19)
!19 = !{null, !20}
!20 = !DIDerivedType(tag: DW_TAG_reference_type, baseType: !11, size: 64)
!21 = !DILocalVariable(name: "x", arg: 1, scope: !17, file: !1, line: 7, type: !20)
!22 = !DILocation(line: 7, column: 13, scope: !17)
!23 = !DILocation(line: 8, column: 5, scope: !17)
!24 = !DILocation(line: 8, column: 7, scope: !17)
!25 = !DILocation(line: 9, column: 1, scope: !17)
!26 = distinct !DISubprogram(name: "main", scope: !1, file: !1, line: 11, type: !27, scopeLine: 11, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !2)
!27 = !DISubroutineType(types: !28)
!28 = !{!11, !11, !29}
!29 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !30, size: 64)
!30 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !31, size: 64)
!31 = !DIBasicType(name: "char", size: 8, encoding: DW_ATE_signed_char)
!32 = !DILocalVariable(name: "argc", arg: 1, scope: !26, file: !1, line: 11, type: !11)
!33 = !DILocation(line: 11, column: 14, scope: !26)
!34 = !DILocalVariable(name: "argv", arg: 2, scope: !26, file: !1, line: 11, type: !29)
!35 = !DILocation(line: 11, column: 26, scope: !26)
!36 = !DILocalVariable(name: "a", scope: !26, file: !1, line: 12, type: !11)
!37 = !DILocation(line: 12, column: 9, scope: !26)
!38 = !DILocalVariable(name: "b", scope: !26, file: !1, line: 13, type: !11)
!39 = !DILocation(line: 13, column: 9, scope: !26)
!40 = !DILocalVariable(name: "c", scope: !26, file: !1, line: 14, type: !10)
!41 = !DILocation(line: 14, column: 10, scope: !26)
!42 = !DILocalVariable(name: "d", scope: !26, file: !1, line: 15, type: !10)
!43 = !DILocation(line: 15, column: 10, scope: !26)
!44 = !DILocalVariable(name: "x", scope: !26, file: !1, line: 16, type: !45)
!45 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !10, size: 64)
!46 = !DILocation(line: 16, column: 11, scope: !26)
!47 = !DILocation(line: 17, column: 7, scope: !26)
!48 = !DILocation(line: 17, column: 6, scope: !26)
!49 = !DILocation(line: 17, column: 4, scope: !26)
!50 = !DILocation(line: 18, column: 4, scope: !26)
!51 = !DILocation(line: 18, column: 2, scope: !26)
!52 = !DILocation(line: 19, column: 2, scope: !26)
!53 = !DILocation(line: 20, column: 2, scope: !26)
