; NOTE: Assertions have been autogenerated by utils/update_test_checks.py UTC_ARGS: --version 3
; RUN: opt < %s -S -passes=early-cse -earlycse-debug-hash | FileCheck %s
; RUN: opt < %s -S -passes='early-cse<memssa>' | FileCheck %s

%T1 = type { i64, i64, i64 }

declare void @use_vec(<4 x ptr>);

define void @foo(ptr %a, <4 x i64> %b, i64 %i) {
; CHECK-LABEL: define void @foo(
; CHECK-SAME: ptr [[A:%.*]], <4 x i64> [[B:%.*]], i64 [[I:%.*]]) {
; CHECK-NEXT:    [[S1A:%.*]] = getelementptr i8, ptr [[A]], i64 8
; CHECK-NEXT:    [[N1D:%.*]] = getelementptr i8, ptr [[A]], i64 7
; CHECK-NEXT:    [[N1G:%.*]] = getelementptr i32, ptr [[A]], i64 1
; CHECK-NEXT:    [[N1H:%.*]] = getelementptr i8, ptr [[A]], i64 [[I]]
; CHECK-NEXT:    [[V:%.*]] = getelementptr i64, ptr [[A]], <4 x i64> <i64 1, i64 1, i64 1, i64 1>
; CHECK-NEXT:    call void @use_vec(<4 x ptr> [[V]])
; CHECK-NEXT:    [[V2:%.*]] = getelementptr i64, ptr [[A]], <4 x i64> <i64 0, i64 2, i64 1, i64 1>
; CHECK-NEXT:    call void @use_vec(<4 x ptr> [[V2]])
; CHECK-NEXT:    ret void
;
  %s1a = getelementptr i8, ptr %a, i64 8
  %s1av = load i64, ptr %s1a
  %s1b = getelementptr inbounds i8, ptr %a, i64 8
  %s1bv = load i64, ptr %s1b
  %s1c = getelementptr %T1, ptr %a, i64 0, i32 1
  %s1cv = load i64, ptr %s1c
  %n1d = getelementptr i8, ptr %a, i64 7
  %n1dv = load i64, ptr %n1d
  %s1e = getelementptr i64, ptr %a, i64 1
  %s1ev = load i64, ptr %s1e
  %s1f = getelementptr i32, ptr %a, i64 2
  %s1fv = load i64, ptr %s1f
  %n1g = getelementptr i32, ptr %a, i64 1
  %n1gv = load i64, ptr %n1g
  %n1h = getelementptr i8, ptr %a, i64 %i
  %n1hv = load i64, ptr %n1h

  %v = getelementptr i64, ptr %a, <4 x i64> <i64 1, i64 1, i64 1, i64 1>
  call void @use_vec(<4 x ptr> %v)
  %v2 = getelementptr i64, ptr %a, <4 x i64> <i64 0, i64 2, i64 1, i64 1>
  call void @use_vec(<4 x ptr> %v2)
  ret void
}