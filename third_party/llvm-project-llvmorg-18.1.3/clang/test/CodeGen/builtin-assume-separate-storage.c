// NOTE: Assertions have been autogenerated by utils/update_cc_test_checks.py
// RUN: %clang_cc1 -triple x86_64-unknown-unknown -emit-llvm -o - %s | FileCheck %s
void *nonconst(void);

// CHECK-LABEL: @test1(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[A_ADDR:%.*]] = alloca ptr, align 8
// CHECK-NEXT:    [[B_ADDR:%.*]] = alloca ptr, align 8
// CHECK-NEXT:    store ptr [[A:%.*]], ptr [[A_ADDR]], align 8
// CHECK-NEXT:    store ptr [[B:%.*]], ptr [[B_ADDR]], align 8
// CHECK-NEXT:    [[TMP0:%.*]] = load ptr, ptr [[A_ADDR]], align 8
// CHECK-NEXT:    [[TMP1:%.*]] = load ptr, ptr [[B_ADDR]], align 8
// CHECK-NEXT:    call void @llvm.assume(i1 true) [ "separate_storage"(ptr [[TMP0]], ptr [[TMP1]]) ]
// CHECK-NEXT:    ret void
//
void test1(int *a, int *b) {

  __builtin_assume_separate_storage(a, b);
}

// Separate storage assumptions evaluate their arguments unconditionally, like
// assume_aligned but *unlike* assume. Check that we actually do so.
// CHECK-LABEL: @test2(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[A_ADDR:%.*]] = alloca ptr, align 8
// CHECK-NEXT:    [[B_ADDR:%.*]] = alloca ptr, align 8
// CHECK-NEXT:    store ptr [[A:%.*]], ptr [[A_ADDR]], align 8
// CHECK-NEXT:    store ptr [[B:%.*]], ptr [[B_ADDR]], align 8
// CHECK-NEXT:    [[TMP0:%.*]] = load ptr, ptr [[A_ADDR]], align 8
// CHECK-NEXT:    [[CALL:%.*]] = call ptr @nonconst()
// CHECK-NEXT:    call void @llvm.assume(i1 true) [ "separate_storage"(ptr [[TMP0]], ptr [[CALL]]) ]
// CHECK-NEXT:    ret void
//
void test2(int *a, int *b) {
  __builtin_assume_separate_storage(a, nonconst());
}