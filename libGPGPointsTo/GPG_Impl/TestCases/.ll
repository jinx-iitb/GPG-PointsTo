; ModuleID = 'ex1.ll'
source_filename = "ex1.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [3 x i8] c"%d\00", align 1

; Function Attrs: noinline nounwind uwtable
define dso_local void @f(i32* %arg) #0 !dbg !7 {
bb:
  call void @llvm.dbg.value(metadata i32* %arg, metadata !12, metadata !DIExpression()), !dbg !13
  store i32 10, i32* %arg, align 4, !dbg !14
  ret void, !dbg !15
}

; Function Attrs: nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main() #0 !dbg !16 {
bb:
  %tmp1 = alloca i32, align 4
  call void @llvm.dbg.declare(metadata i32* %tmp1, metadata !19, metadata !DIExpression()), !dbg !20
  store i32 5, i32* %tmp1, align 4, !dbg !20
  call void @llvm.dbg.value(metadata i32* %tmp1, metadata !21, metadata !DIExpression()), !dbg !22
  call void @f(i32* %tmp1), !dbg !23
  %tmp5 = load i32, i32* %tmp1, align 4, !dbg !24
  %tmp6 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str, i64 0, i64 0), i32 %tmp5), !dbg !25
  ret i32 1, !dbg !26
}

declare dso_local i32 @printf(i8*, ...) #2

; Function Attrs: nounwind readnone speculatable willreturn
declare void @llvm.dbg.value(metadata, metadata, metadata) #1

attributes #0 = { noinline nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone speculatable willreturn }
attributes #2 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

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
!9 = !{null, !10}
!10 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !11, size: 64)
!11 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!12 = !DILocalVariable(name: "x", arg: 1, scope: !7, file: !1, line: 3, type: !10)
!13 = !DILocation(line: 0, scope: !7)
!14 = !DILocation(line: 4, column: 5, scope: !7)
!15 = !DILocation(line: 5, column: 1, scope: !7)
!16 = distinct !DISubprogram(name: "main", scope: !1, file: !1, line: 6, type: !17, scopeLine: 6, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !2)
!17 = !DISubroutineType(types: !18)
!18 = !{!11}
!19 = !DILocalVariable(name: "a", scope: !16, file: !1, line: 7, type: !11)
!20 = !DILocation(line: 7, column: 9, scope: !16)
!21 = !DILocalVariable(name: "x", scope: !16, file: !1, line: 8, type: !10)
!22 = !DILocation(line: 0, scope: !16)
!23 = !DILocation(line: 9, column: 2, scope: !16)
!24 = !DILocation(line: 10, column: 15, scope: !16)
!25 = !DILocation(line: 10, column: 2, scope: !16)
!26 = !DILocation(line: 11, column: 2, scope: !16)
; ModuleID = 'ex1.ll'
source_filename = "ex1.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [3 x i8] c"%d\00", align 1

; Function Attrs: noinline nounwind uwtable
define dso_local void @f(i32* %arg) #0 !dbg !7 {
bb:
  call void @llvm.dbg.value(metadata i32* %arg, metadata !12, metadata !DIExpression()), !dbg !13
  store i32 10, i32* %arg, align 4, !dbg !14
  ret void, !dbg !15
}

; Function Attrs: nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main() #0 !dbg !16 {
bb:
  %tmp1 = alloca i32, align 4
  call void @llvm.dbg.declare(metadata i32* %tmp1, metadata !19, metadata !DIExpression()), !dbg !20
  store i32 5, i32* %tmp1, align 4, !dbg !20
  call void @llvm.dbg.value(metadata i32* %tmp1, metadata !21, metadata !DIExpression()), !dbg !22
  call void @f(i32* %tmp1), !dbg !23
  %tmp5 = load i32, i32* %tmp1, align 4, !dbg !24
  %tmp6 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str, i64 0, i64 0), i32 %tmp5), !dbg !25
  ret i32 1, !dbg !26
}

declare dso_local i32 @printf(i8*, ...) #2

; Function Attrs: nounwind readnone speculatable willreturn
declare void @llvm.dbg.value(metadata, metadata, metadata) #1

attributes #0 = { noinline nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone speculatable willreturn }
attributes #2 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

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
!9 = !{null, !10}
!10 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !11, size: 64)
!11 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!12 = !DILocalVariable(name: "x", arg: 1, scope: !7, file: !1, line: 3, type: !10)
!13 = !DILocation(line: 0, scope: !7)
!14 = !DILocation(line: 4, column: 5, scope: !7)
!15 = !DILocation(line: 5, column: 1, scope: !7)
!16 = distinct !DISubprogram(name: "main", scope: !1, file: !1, line: 6, type: !17, scopeLine: 6, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !2)
!17 = !DISubroutineType(types: !18)
!18 = !{!11}
!19 = !DILocalVariable(name: "a", scope: !16, file: !1, line: 7, type: !11)
!20 = !DILocation(line: 7, column: 9, scope: !16)
!21 = !DILocalVariable(name: "x", scope: !16, file: !1, line: 8, type: !10)
!22 = !DILocation(line: 0, scope: !16)
!23 = !DILocation(line: 9, column: 2, scope: !16)
!24 = !DILocation(line: 10, column: 15, scope: !16)
!25 = !DILocation(line: 10, column: 2, scope: !16)
!26 = !DILocation(line: 11, column: 2, scope: !16)
; ModuleID = 'ex1.ll'
source_filename = "ex1.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [3 x i8] c"%d\00", align 1

; Function Attrs: noinline nounwind uwtable
define dso_local void @f(i32* %arg) #0 !dbg !7 {
bb:
  call void @llvm.dbg.value(metadata i32* %arg, metadata !12, metadata !DIExpression()), !dbg !13
  store i32 10, i32* %arg, align 4, !dbg !14
  ret void, !dbg !15
}

; Function Attrs: nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main() #0 !dbg !16 {
bb:
  %tmp1 = alloca i32, align 4
  call void @llvm.dbg.declare(metadata i32* %tmp1, metadata !19, metadata !DIExpression()), !dbg !20
  store i32 5, i32* %tmp1, align 4, !dbg !20
  call void @llvm.dbg.value(metadata i32* %tmp1, metadata !21, metadata !DIExpression()), !dbg !22
  call void @f(i32* %tmp1), !dbg !23
  %tmp5 = load i32, i32* %tmp1, align 4, !dbg !24
  %tmp6 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str, i64 0, i64 0), i32 %tmp5), !dbg !25
  ret i32 1, !dbg !26
}

declare dso_local i32 @printf(i8*, ...) #2

; Function Attrs: nounwind readnone speculatable willreturn
declare void @llvm.dbg.value(metadata, metadata, metadata) #1

attributes #0 = { noinline nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone speculatable willreturn }
attributes #2 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

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
!9 = !{null, !10}
!10 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !11, size: 64)
!11 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!12 = !DILocalVariable(name: "x", arg: 1, scope: !7, file: !1, line: 3, type: !10)
!13 = !DILocation(line: 0, scope: !7)
!14 = !DILocation(line: 4, column: 5, scope: !7)
!15 = !DILocation(line: 5, column: 1, scope: !7)
!16 = distinct !DISubprogram(name: "main", scope: !1, file: !1, line: 6, type: !17, scopeLine: 6, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !2)
!17 = !DISubroutineType(types: !18)
!18 = !{!11}
!19 = !DILocalVariable(name: "a", scope: !16, file: !1, line: 7, type: !11)
!20 = !DILocation(line: 7, column: 9, scope: !16)
!21 = !DILocalVariable(name: "x", scope: !16, file: !1, line: 8, type: !10)
!22 = !DILocation(line: 0, scope: !16)
!23 = !DILocation(line: 9, column: 2, scope: !16)
!24 = !DILocation(line: 10, column: 15, scope: !16)
!25 = !DILocation(line: 10, column: 2, scope: !16)
!26 = !DILocation(line: 11, column: 2, scope: !16)
; ModuleID = 'ex1.ll'
source_filename = "ex1.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [3 x i8] c"%d\00", align 1

; Function Attrs: noinline nounwind uwtable
define dso_local void @f(i32* %arg) #0 !dbg !7 {
bb:
  call void @llvm.dbg.value(metadata i32* %arg, metadata !12, metadata !DIExpression()), !dbg !13
  store i32 10, i32* %arg, align 4, !dbg !14
  ret void, !dbg !15
}

; Function Attrs: nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main() #0 !dbg !16 {
bb:
  %tmp1 = alloca i32, align 4
  call void @llvm.dbg.declare(metadata i32* %tmp1, metadata !19, metadata !DIExpression()), !dbg !20
  store i32 5, i32* %tmp1, align 4, !dbg !20
  call void @llvm.dbg.value(metadata i32* %tmp1, metadata !21, metadata !DIExpression()), !dbg !22
  call void @f(i32* %tmp1), !dbg !23
  %tmp5 = load i32, i32* %tmp1, align 4, !dbg !24
  %tmp6 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str, i64 0, i64 0), i32 %tmp5), !dbg !25
  ret i32 1, !dbg !26
}

declare dso_local i32 @printf(i8*, ...) #2

; Function Attrs: nounwind readnone speculatable willreturn
declare void @llvm.dbg.value(metadata, metadata, metadata) #1

attributes #0 = { noinline nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone speculatable willreturn }
attributes #2 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

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
!9 = !{null, !10}
!10 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !11, size: 64)
!11 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!12 = !DILocalVariable(name: "x", arg: 1, scope: !7, file: !1, line: 3, type: !10)
!13 = !DILocation(line: 0, scope: !7)
!14 = !DILocation(line: 4, column: 5, scope: !7)
!15 = !DILocation(line: 5, column: 1, scope: !7)
!16 = distinct !DISubprogram(name: "main", scope: !1, file: !1, line: 6, type: !17, scopeLine: 6, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !2)
!17 = !DISubroutineType(types: !18)
!18 = !{!11}
!19 = !DILocalVariable(name: "a", scope: !16, file: !1, line: 7, type: !11)
!20 = !DILocation(line: 7, column: 9, scope: !16)
!21 = !DILocalVariable(name: "x", scope: !16, file: !1, line: 8, type: !10)
!22 = !DILocation(line: 0, scope: !16)
!23 = !DILocation(line: 9, column: 2, scope: !16)
!24 = !DILocation(line: 10, column: 15, scope: !16)
!25 = !DILocation(line: 10, column: 2, scope: !16)
!26 = !DILocation(line: 11, column: 2, scope: !16)
