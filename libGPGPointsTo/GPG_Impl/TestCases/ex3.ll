; ModuleID = 'ex3.c'
source_filename = "ex3.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%struct.abc = type { i32*, i32* }

@b = common dso_local global i32* null, align 8, !dbg !0
@.str = private unnamed_addr constant [6 x i8] c"%p %d\00", align 1
@a = common dso_local global i32* null, align 8, !dbg !6
@c = common dso_local global i32* null, align 8, !dbg !10

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @f(%struct.abc* %0) #0 !dbg !16 {
  %2 = alloca %struct.abc*, align 8
  %3 = alloca i32*, align 8
  store %struct.abc* %0, %struct.abc** %2, align 8
  call void @llvm.dbg.declare(metadata %struct.abc** %2, metadata !24, metadata !DIExpression()), !dbg !25
  call void @llvm.dbg.declare(metadata i32** %3, metadata !26, metadata !DIExpression()), !dbg !27
  %4 = load %struct.abc*, %struct.abc** %2, align 8, !dbg !28
  %5 = getelementptr inbounds %struct.abc, %struct.abc* %4, i32 0, i32 0, !dbg !29
  %6 = load i32*, i32** %5, align 8, !dbg !29
  store i32* %6, i32** %3, align 8, !dbg !27
  %7 = load i32*, i32** @b, align 8, !dbg !30
  %8 = load %struct.abc*, %struct.abc** %2, align 8, !dbg !31
  %9 = getelementptr inbounds %struct.abc, %struct.abc* %8, i32 0, i32 0, !dbg !32
  store i32* %7, i32** %9, align 8, !dbg !33
  %10 = load i32*, i32** %3, align 8, !dbg !34
  %11 = load %struct.abc*, %struct.abc** %2, align 8, !dbg !35
  %12 = getelementptr inbounds %struct.abc, %struct.abc* %11, i32 0, i32 1, !dbg !36
  store i32* %10, i32** %12, align 8, !dbg !37
  ret i32 0, !dbg !38
}

; Function Attrs: nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main() #0 !dbg !39 {
  %1 = alloca i32, align 4
  %2 = alloca i32*, align 8
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca %struct.abc, align 8
  store i32 0, i32* %1, align 4
  call void @llvm.dbg.declare(metadata i32** %2, metadata !42, metadata !DIExpression()), !dbg !43
  call void @llvm.dbg.declare(metadata i32* %3, metadata !44, metadata !DIExpression()), !dbg !45
  store i32 5, i32* %3, align 4, !dbg !45
  call void @llvm.dbg.declare(metadata i32* %4, metadata !46, metadata !DIExpression()), !dbg !47
  store i32 6, i32* %4, align 4, !dbg !47
  call void @llvm.dbg.declare(metadata %struct.abc* %5, metadata !48, metadata !DIExpression()), !dbg !49
  %6 = getelementptr inbounds %struct.abc, %struct.abc* %5, i32 0, i32 0, !dbg !50
  store i32* %3, i32** %6, align 8, !dbg !51
  %7 = getelementptr inbounds %struct.abc, %struct.abc* %5, i32 0, i32 1, !dbg !52
  store i32* %4, i32** %7, align 8, !dbg !53
  %8 = call i32 @f(%struct.abc* %5), !dbg !54
  store i32* %3, i32** %2, align 8, !dbg !55
  %9 = load i32*, i32** %2, align 8, !dbg !56
  store i32 6, i32* %9, align 4, !dbg !57
  %10 = load i32*, i32** %2, align 8, !dbg !58
  %11 = load i32*, i32** %2, align 8, !dbg !59
  %12 = load i32, i32* %11, align 4, !dbg !60
  %13 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str, i64 0, i64 0), i32* %10, i32 %12), !dbg !61
  ret i32 1, !dbg !62
}

declare dso_local i32 @printf(i8*, ...) #2

attributes #0 = { noinline nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone speculatable willreturn }
attributes #2 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!2}
!llvm.module.flags = !{!12, !13, !14}
!llvm.ident = !{!15}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(name: "b", scope: !2, file: !3, line: 3, type: !8, isLocal: false, isDefinition: true)
!2 = distinct !DICompileUnit(language: DW_LANG_C99, file: !3, producer: "clang version 10.0.0-4ubuntu1 ", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !4, globals: !5, splitDebugInlining: false, nameTableKind: None)
!3 = !DIFile(filename: "ex3.c", directory: "/home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/GPG_Impl/TestCases")
!4 = !{}
!5 = !{!6, !0, !10}
!6 = !DIGlobalVariableExpression(var: !7, expr: !DIExpression())
!7 = distinct !DIGlobalVariable(name: "a", scope: !2, file: !3, line: 3, type: !8, isLocal: false, isDefinition: true)
!8 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !9, size: 64)
!9 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!10 = !DIGlobalVariableExpression(var: !11, expr: !DIExpression())
!11 = distinct !DIGlobalVariable(name: "c", scope: !2, file: !3, line: 3, type: !8, isLocal: false, isDefinition: true)
!12 = !{i32 7, !"Dwarf Version", i32 4}
!13 = !{i32 2, !"Debug Info Version", i32 3}
!14 = !{i32 1, !"wchar_size", i32 4}
!15 = !{!"clang version 10.0.0-4ubuntu1 "}
!16 = distinct !DISubprogram(name: "f", scope: !3, file: !3, line: 10, type: !17, scopeLine: 10, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!17 = !DISubroutineType(types: !18)
!18 = !{!9, !19}
!19 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !20, size: 64)
!20 = distinct !DICompositeType(tag: DW_TAG_structure_type, name: "abc", file: !3, line: 5, size: 128, elements: !21)
!21 = !{!22, !23}
!22 = !DIDerivedType(tag: DW_TAG_member, name: "d", scope: !20, file: !3, line: 6, baseType: !8, size: 64)
!23 = !DIDerivedType(tag: DW_TAG_member, name: "e", scope: !20, file: !3, line: 7, baseType: !8, size: 64, offset: 64)
!24 = !DILocalVariable(name: "st", arg: 1, scope: !16, file: !3, line: 10, type: !19)
!25 = !DILocation(line: 10, column: 19, scope: !16)
!26 = !DILocalVariable(name: "temp", scope: !16, file: !3, line: 11, type: !8)
!27 = !DILocation(line: 11, column: 6, scope: !16)
!28 = !DILocation(line: 11, column: 13, scope: !16)
!29 = !DILocation(line: 11, column: 17, scope: !16)
!30 = !DILocation(line: 12, column: 9, scope: !16)
!31 = !DILocation(line: 12, column: 1, scope: !16)
!32 = !DILocation(line: 12, column: 5, scope: !16)
!33 = !DILocation(line: 12, column: 7, scope: !16)
!34 = !DILocation(line: 13, column: 9, scope: !16)
!35 = !DILocation(line: 13, column: 1, scope: !16)
!36 = !DILocation(line: 13, column: 5, scope: !16)
!37 = !DILocation(line: 13, column: 7, scope: !16)
!38 = !DILocation(line: 15, column: 1, scope: !16)
!39 = distinct !DISubprogram(name: "main", scope: !3, file: !3, line: 18, type: !40, scopeLine: 18, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!40 = !DISubroutineType(types: !41)
!41 = !{!9}
!42 = !DILocalVariable(name: "p", scope: !39, file: !3, line: 19, type: !8)
!43 = !DILocation(line: 19, column: 10, scope: !39)
!44 = !DILocalVariable(name: "x", scope: !39, file: !3, line: 20, type: !9)
!45 = !DILocation(line: 20, column: 9, scope: !39)
!46 = !DILocalVariable(name: "y", scope: !39, file: !3, line: 21, type: !9)
!47 = !DILocation(line: 21, column: 9, scope: !39)
!48 = !DILocalVariable(name: "st", scope: !39, file: !3, line: 22, type: !20)
!49 = !DILocation(line: 22, column: 16, scope: !39)
!50 = !DILocation(line: 23, column: 8, scope: !39)
!51 = !DILocation(line: 23, column: 10, scope: !39)
!52 = !DILocation(line: 24, column: 8, scope: !39)
!53 = !DILocation(line: 24, column: 10, scope: !39)
!54 = !DILocation(line: 25, column: 5, scope: !39)
!55 = !DILocation(line: 26, column: 7, scope: !39)
!56 = !DILocation(line: 27, column: 6, scope: !39)
!57 = !DILocation(line: 27, column: 8, scope: !39)
!58 = !DILocation(line: 28, column: 21, scope: !39)
!59 = !DILocation(line: 28, column: 25, scope: !39)
!60 = !DILocation(line: 28, column: 24, scope: !39)
!61 = !DILocation(line: 28, column: 5, scope: !39)
!62 = !DILocation(line: 29, column: 5, scope: !39)
