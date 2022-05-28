; Function Attrs: noinline nounwind uwtable
define dso_local void @f() #0 !dbg !29 {
bb:
; 1 = MemoryDef(liveOnEntry)
  store i32* @n, i32** @p, align 8, !dbg !32
; MemoryUse(1) MayAlias
  %tmp = load %struct.node*, %struct.node** @gnode, align 8, !dbg !33
  %tmp1 = getelementptr inbounds %struct.node, %struct.node* %tmp, i32 0, i32 1, !dbg !34
; 2 = MemoryDef(1)
  store i32* @b, i32** %tmp1, align 8, !dbg !35
; 3 = MemoryDef(2)
  store i32 22, i32* @n, align 4, !dbg !36
  ret void, !dbg !37
}
; Function Attrs: noinline nounwind uwtable
define dso_local void @g() #0 !dbg !29 {
bb:
; 1 = MemoryDef(liveOnEntry)
  store i32* @b, i32** @p, align 8, !dbg !32
; MemoryUse(1) MayAlias
  %tmp = load %struct.node*, %struct.node** @gnode, align 8, !dbg !33
  %tmp1 = getelementptr inbounds %struct.node, %struct.node* %tmp, i32 0, i32 1, !dbg !34
; 2 = MemoryDef(1)
  store i32* @n, i32** %tmp1, align 8, !dbg !35
; 3 = MemoryDef(2)
  store i32 67, i32* @n, align 4, !dbg !36
  ret void, !dbg !37
}
; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main() #0 !dbg !29 {
bb:
; 1 = MemoryDef(liveOnEntry)
  store i32 10, i32* @b, align 4, !dbg !32
; 2 = MemoryDef(1)
  %tmp2 = call i32 (i8*, ...) @__isoc99_scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str, i64 0, i64 0), i32* @n), !dbg !33
; 3 = MemoryDef(2)
  %tmp3 = call noalias i8* @malloc(i64 24) #4, !dbg !34
  %tmp4 = bitcast i8* %tmp3 to %struct.node*, !dbg !35
; 4 = MemoryDef(3)
  store %struct.node* %tmp4, %struct.node** @gnode, align 8, !dbg !36
; MemoryUse(4) MayAlias
  %tmp5 = load %struct.node*, %struct.node** @gnode, align 8, !dbg !37
  %tmp6 = getelementptr inbounds %struct.node, %struct.node* %tmp5, i32 0, i32 0, !dbg !38
; 5 = MemoryDef(4)
  store i32 22, i32* %tmp6, align 8, !dbg !39
; 6 = MemoryDef(5)
  store i32 22, i32* getelementptr inbounds (%struct.node, %struct.node* @local_node, i32 0, i32 0), align 8, !dbg !40
; 7 = MemoryDef(6)
  store i32* @n, i32** getelementptr inbounds (%struct.node, %struct.node* @local_node, i32 0, i32 1), align 8, !dbg !41
; MemoryUse(7) MayAlias
  %tmp7 = load i32, i32* @n, align 4, !dbg !42
  %tmp8 = srem i32 %tmp7, 2, !dbg !44
  %tmp9 = icmp eq i32 %tmp8, 0, !dbg !45
  br i1 %tmp9, label %bb10, label %bb11, !dbg !46

bb10:                                             ; preds = %bb
; 8 = MemoryDef(7)
  call void @f(), !dbg !47
  br label %bb12, !dbg !49

bb11:                                             ; preds = %bb
; 9 = MemoryDef(7)
  call void @g(), !dbg !50
  br label %bb12

bb12:                                             ; preds = %bb11, %bb10
; 11 = MemoryPhi({bb10,8},{bb11,9})
; MemoryUse(11) MayAlias
  %tmp13 = load i32*, i32** @p, align 8, !dbg !52
; MemoryUse(11) MayAlias
  %tmp14 = load i32, i32* %tmp13, align 4, !dbg !53
; MemoryUse(11) MayAlias
  %tmp15 = load %struct.node*, %struct.node** @gnode, align 8, !dbg !54
  %tmp16 = getelementptr inbounds %struct.node, %struct.node* %tmp15, i32 0, i32 1, !dbg !55
; MemoryUse(11) MayAlias
  %tmp17 = load i32*, i32** %tmp16, align 8, !dbg !55
; MemoryUse(11) MayAlias
  %tmp18 = load i32, i32* %tmp17, align 4, !dbg !56
  %tmp19 = add nsw i32 %tmp14, %tmp18, !dbg !57
; MemoryUse(11) MayAlias
  %tmp20 = load i32*, i32** getelementptr inbounds (%struct.node, %struct.node* @local_node, i32 0, i32 1), align 8, !dbg !58
; MemoryUse(11) MayAlias
  %tmp21 = load i32, i32* %tmp20, align 4, !dbg !59
  %tmp22 = add nsw i32 %tmp19, %tmp21, !dbg !60
  call void @llvm.dbg.value(metadata i32 %tmp22, metadata !61, metadata !DIExpression()), !dbg !62
; 10 = MemoryDef(11)
  %tmp24 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0), i32 %tmp22), !dbg !63
  ret i32 0, !dbg !64
}
