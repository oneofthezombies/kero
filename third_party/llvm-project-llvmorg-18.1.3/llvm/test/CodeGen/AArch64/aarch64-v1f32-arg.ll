; NOTE: Assertions have been autogenerated by utils/update_llc_test_checks.py
; RUN: llc < %s -mtriple=aarch64 | FileCheck %s

define <1 x float> @f(<16 x i64> %0, <1 x float> %1) {
; CHECK-LABEL: f:
; CHECK:       // %bb.0: // %BB
; CHECK-NEXT:    ldr d0, [sp]
; CHECK-NEXT:    ret
BB:
  ret <1 x float> %1
}