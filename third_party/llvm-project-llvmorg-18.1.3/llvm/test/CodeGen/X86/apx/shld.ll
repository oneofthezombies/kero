; NOTE: Assertions have been autogenerated by utils/update_llc_test_checks.py
; RUN: llc < %s -mtriple=x86_64-unknown -mattr=+ndd -verify-machineinstrs | FileCheck %s

define i16 @shld16rrcl(i16 noundef %a, i16 noundef %b, i8 %cl) {
; CHECK-LABEL: shld16rrcl:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    andb $15, %dl, %cl
; CHECK-NEXT:    shldw %cl, %si, %di, %ax
; CHECK-NEXT:    retq
entry:
    %clin = sext i8 %cl to i16
    %shld = call i16 @llvm.fshl.i16(i16 %a, i16 %b, i16 %clin)
    ret i16 %shld
}

define i16 @shld16rrcl_mask(i16 noundef %a, i16 noundef %b, i8 %cl) {
; CHECK-LABEL: shld16rrcl_mask:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    andb $15, %dl, %cl
; CHECK-NEXT:    shldw %cl, %si, %di, %ax
; CHECK-NEXT:    retq
entry:
    %clin = sext i8 %cl to i16
    %shamt = and i16 %clin, 31
    %shld = call i16 @llvm.fshl.i16(i16 %a, i16 %b, i16 %shamt)
    ret i16 %shld
}

define i32 @shld32rrcl(i32 noundef %a, i32 noundef %b, i8 %cl) {
; CHECK-LABEL: shld32rrcl:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    movl %edx, %ecx
; CHECK-NEXT:    # kill: def $cl killed $cl killed $ecx
; CHECK-NEXT:    shldl %cl, %esi, %edi, %eax
; CHECK-NEXT:    retq
entry:
    %clin = sext i8 %cl to i32
    %shld = call i32 @llvm.fshl.i32(i32 %a, i32 %b, i32 %clin)
    ret i32 %shld
}

define i32 @shld32rrcl_mask(i32 noundef %a, i32 noundef %b, i8 %cl) {
; CHECK-LABEL: shld32rrcl_mask:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    movl %edx, %ecx
; CHECK-NEXT:    # kill: def $cl killed $cl killed $ecx
; CHECK-NEXT:    shldl %cl, %esi, %edi, %eax
; CHECK-NEXT:    retq
entry:
    %clin = sext i8 %cl to i32
    %shamt = and i32 %clin, 31
    %shld = call i32 @llvm.fshl.i32(i32 %a, i32 %b, i32 %shamt)
    ret i32 %shld
}

define i64 @shld64rrcl(i64 noundef %a, i64 noundef %b, i8 %cl) {
; CHECK-LABEL: shld64rrcl:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    movl %edx, %ecx
; CHECK-NEXT:    # kill: def $cl killed $cl killed $ecx
; CHECK-NEXT:    shldq %cl, %rsi, %rdi, %rax
; CHECK-NEXT:    retq
entry:
    %clin = sext i8 %cl to i64
    %shld = call i64 @llvm.fshl.i64(i64 %a, i64 %b, i64 %clin)
    ret i64 %shld
}

define i64 @shld64rrcl_mask(i64 noundef %a, i64 noundef %b, i8 %cl) {
; CHECK-LABEL: shld64rrcl_mask:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    movl %edx, %ecx
; CHECK-NEXT:    # kill: def $cl killed $cl killed $ecx
; CHECK-NEXT:    shldq %cl, %rsi, %rdi, %rax
; CHECK-NEXT:    retq
entry:
    %clin = sext i8 %cl to i64
    %shamt = and i64 %clin, 63
    %shld = call i64 @llvm.fshl.i64(i64 %a, i64 %b, i64 %clin)
    ret i64 %shld
}

define i16 @shld16rri8(i16 noundef %a, i16 noundef %b) {
; CHECK-LABEL: shld16rri8:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    shldw $12, %si, %di, %ax
; CHECK-NEXT:    retq
entry:
    %shld = call i16 @llvm.fshl.i16(i16 %a, i16 %b, i16 12)
    ret i16 %shld
}

define i32 @shld32rri8(i32 noundef %a, i32 noundef %b) {
; CHECK-LABEL: shld32rri8:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    shldl $12, %esi, %edi, %eax
; CHECK-NEXT:    retq
entry:
    %shld = call i32 @llvm.fshl.i32(i32 %a, i32 %b, i32 12)
    ret i32 %shld
}

define i64 @shld64rri8(i64 noundef %a, i64 noundef %b) {
; CHECK-LABEL: shld64rri8:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    shldq $12, %rsi, %rdi, %rax
; CHECK-NEXT:    retq
entry:
    %shld = call i64 @llvm.fshl.i64(i64 %a, i64 %b, i64 12)
    ret i64 %shld
}

define i16 @shld16mrcl(ptr %ptr, i16 noundef %b, i8 %cl) {
; CHECK-LABEL: shld16mrcl:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    andb $15, %dl, %cl
; CHECK-NEXT:    shldw %cl, %si, (%rdi), %ax
; CHECK-NEXT:    retq
entry:
    %a = load i16, ptr %ptr
    %clin = sext i8 %cl to i16
    %shld = call i16 @llvm.fshl.i16(i16 %a, i16 %b, i16 %clin)
    ret i16 %shld
}

define i32 @shld32mrcl(ptr %ptr, i32 noundef %b, i8 %cl) {
; CHECK-LABEL: shld32mrcl:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    movl %edx, %ecx
; CHECK-NEXT:    # kill: def $cl killed $cl killed $ecx
; CHECK-NEXT:    shldl %cl, %esi, (%rdi), %eax
; CHECK-NEXT:    retq
entry:
    %a = load i32, ptr %ptr
    %clin = sext i8 %cl to i32
    %shld = call i32 @llvm.fshl.i32(i32 %a, i32 %b, i32 %clin)
    ret i32 %shld
}

define i64 @shld64mrcl(ptr %ptr, i64 noundef %b, i8 %cl) {
; CHECK-LABEL: shld64mrcl:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    movl %edx, %ecx
; CHECK-NEXT:    # kill: def $cl killed $cl killed $ecx
; CHECK-NEXT:    shldq %cl, %rsi, (%rdi), %rax
; CHECK-NEXT:    retq
entry:
    %a = load i64, ptr %ptr
    %clin = sext i8 %cl to i64
    %shld = call i64 @llvm.fshl.i64(i64 %a, i64 %b, i64 %clin)
    ret i64 %shld
}

define i16 @shld16mri8(ptr %ptr, i16 noundef %b) {
; CHECK-LABEL: shld16mri8:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    shldw $12, %si, (%rdi), %ax
; CHECK-NEXT:    retq
entry:
    %a = load i16, ptr %ptr
    %shld = call i16 @llvm.fshl.i16(i16 %a, i16 %b, i16 12)
    ret i16 %shld
}

define i32 @shld32mri8(ptr %ptr, i32 noundef %b) {
; CHECK-LABEL: shld32mri8:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    shldl $12, %esi, (%rdi), %eax
; CHECK-NEXT:    retq
entry:
    %a = load i32, ptr %ptr
    %shld = call i32 @llvm.fshl.i32(i32 %a, i32 %b, i32 12)
    ret i32 %shld
}

define i64 @shld64mri8(ptr %ptr, i64 noundef %b) {
; CHECK-LABEL: shld64mri8:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    shldq $12, %rsi, (%rdi), %rax
; CHECK-NEXT:    retq
entry:
    %a = load i64, ptr %ptr
    %shld = call i64 @llvm.fshl.i64(i64 %a, i64 %b, i64 12)
    ret i64 %shld
}

define void @shld16mrcl_legacy(ptr %ptr, i16 noundef %b, i8 %cl) {
; CHECK-LABEL: shld16mrcl_legacy:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    andb $15, %dl, %cl
; CHECK-NEXT:    shldw %cl, %si, (%rdi)
; CHECK-NEXT:    retq
entry:
    %a = load i16, ptr %ptr
    %clin = sext i8 %cl to i16
    %shld = call i16 @llvm.fshl.i16(i16 %a, i16 %b, i16 %clin)
    store i16 %shld, ptr %ptr
    ret void
}

define void @shld32mrcl_legacy(ptr %ptr, i32 noundef %b, i8 %cl) {
; CHECK-LABEL: shld32mrcl_legacy:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    movl %edx, %ecx
; CHECK-NEXT:    # kill: def $cl killed $cl killed $ecx
; CHECK-NEXT:    shldl %cl, %esi, (%rdi)
; CHECK-NEXT:    retq
entry:
    %a = load i32, ptr %ptr
    %clin = sext i8 %cl to i32
    %shld = call i32 @llvm.fshl.i32(i32 %a, i32 %b, i32 %clin)
    store i32 %shld, ptr %ptr
    ret void
}

define void @shld64mrcl_legacy(ptr %ptr, i64 noundef %b, i8 %cl) {
; CHECK-LABEL: shld64mrcl_legacy:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    movl %edx, %ecx
; CHECK-NEXT:    # kill: def $cl killed $cl killed $ecx
; CHECK-NEXT:    shldq %cl, %rsi, (%rdi)
; CHECK-NEXT:    retq
entry:
    %a = load i64, ptr %ptr
    %clin = sext i8 %cl to i64
    %shld = call i64 @llvm.fshl.i64(i64 %a, i64 %b, i64 %clin)
    store i64 %shld, ptr %ptr
    ret void
}

define void @shld16mri8_legacy(ptr %ptr, i16 noundef %b) {
; CHECK-LABEL: shld16mri8_legacy:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    shldw $12, %si, (%rdi)
; CHECK-NEXT:    retq
entry:
    %a = load i16, ptr %ptr
    %shld = call i16 @llvm.fshl.i16(i16 %a, i16 %b, i16 12)
    store i16 %shld, ptr %ptr
    ret void
}

define void @shld32mri8_legacy(ptr %ptr, i32 noundef %b) {
; CHECK-LABEL: shld32mri8_legacy:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    shldl $12, %esi, (%rdi)
; CHECK-NEXT:    retq
entry:
    %a = load i32, ptr %ptr
    %shld = call i32 @llvm.fshl.i32(i32 %a, i32 %b, i32 12)
    store i32 %shld, ptr %ptr
    ret void
}

define void @shld64mri8_legacy(ptr %ptr, i64 noundef %b) {
; CHECK-LABEL: shld64mri8_legacy:
; CHECK:       # %bb.0: # %entry
; CHECK-NEXT:    shldq $12, %rsi, (%rdi)
; CHECK-NEXT:    retq
entry:
    %a = load i64, ptr %ptr
    %shld = call i64 @llvm.fshl.i64(i64 %a, i64 %b, i64 12)
    store i64 %shld, ptr %ptr
    ret void
}