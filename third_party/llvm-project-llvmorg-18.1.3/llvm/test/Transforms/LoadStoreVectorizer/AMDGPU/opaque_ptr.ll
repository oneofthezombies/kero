; NOTE: Assertions have been autogenerated by utils/update_test_checks.py
; RUN: opt -mtriple=amdgcn-amd-amdhsa -passes=load-store-vectorizer -S -o - %s | FileCheck %s

; Vectorize and emit valid code (Issue #54896).

%S = type { i64, i64 }
@S = external global %S

define i64 @order() {
; CHECK-LABEL: @order(
; CHECK-NEXT:    [[IDX0:%.*]] = getelementptr inbounds [[S:%.*]], ptr @S, i32 0, i32 0
; CHECK-NEXT:    [[TMP1:%.*]] = load <2 x i64>, ptr [[IDX0]], align 8
; CHECK-NEXT:    [[L01:%.*]] = extractelement <2 x i64> [[TMP1]], i32 0
; CHECK-NEXT:    [[L12:%.*]] = extractelement <2 x i64> [[TMP1]], i32 1
; CHECK-NEXT:    [[ADD:%.*]] = add i64 [[L01]], [[L12]]
; CHECK-NEXT:    ret i64 [[ADD]]
;
  %idx1 = getelementptr inbounds %S, ptr @S, i32 0, i32 1
  %l1 = load i64, i64* %idx1, align 8
  %idx0 = getelementptr inbounds %S, ptr @S, i32 0, i32 0
  %l0 = load i64, i64* %idx0, align 8
  %add = add i64 %l0, %l1
  ret i64 %add
}