# NOTE: Assertions have been autogenerated by utils/update_mca_test_checks.py
# RUN: llvm-mca -mtriple=x86_64-unknown-unknown -mcpu=btver2 -iterations=3 -timeline -register-file-stats < %s | FileCheck %s

pxor %mm0, %mm0
movq %mm0, %mm1

xorps %xmm0, %xmm0
movaps %xmm0, %xmm1
movups %xmm1, %xmm2
movapd %xmm2, %xmm3
movupd %xmm3, %xmm4
movdqa %xmm4, %xmm5
movdqu %xmm5, %xmm0

# CHECK:      Iterations:        3
# CHECK-NEXT: Instructions:      27
# CHECK-NEXT: Total Cycles:      15
# CHECK-NEXT: Total uOps:        27

# CHECK:      Dispatch Width:    2
# CHECK-NEXT: uOps Per Cycle:    1.80
# CHECK-NEXT: IPC:               1.80
# CHECK-NEXT: Block RThroughput: 4.5

# CHECK:      Instruction Info:
# CHECK-NEXT: [1]: #uOps
# CHECK-NEXT: [2]: Latency
# CHECK-NEXT: [3]: RThroughput
# CHECK-NEXT: [4]: MayLoad
# CHECK-NEXT: [5]: MayStore
# CHECK-NEXT: [6]: HasSideEffects (U)

# CHECK:      [1]    [2]    [3]    [4]    [5]    [6]    Instructions:
# CHECK-NEXT:  1      0     0.50                        pxor	%mm0, %mm0
# CHECK-NEXT:  1      1     0.50                        movq	%mm0, %mm1
# CHECK-NEXT:  1      0     0.50                        xorps	%xmm0, %xmm0
# CHECK-NEXT:  1      1     0.50                        movaps	%xmm0, %xmm1
# CHECK-NEXT:  1      1     0.50                        movups	%xmm1, %xmm2
# CHECK-NEXT:  1      1     0.50                        movapd	%xmm2, %xmm3
# CHECK-NEXT:  1      1     0.50                        movupd	%xmm3, %xmm4
# CHECK-NEXT:  1      1     0.50                        movdqa	%xmm4, %xmm5
# CHECK-NEXT:  1      1     0.50                        movdqu	%xmm5, %xmm0

# CHECK:      Register File statistics:
# CHECK-NEXT: Total number of mappings created:    0
# CHECK-NEXT: Max number of mappings used:         0

# CHECK:      *  Register File #1 -- JFpuPRF:
# CHECK-NEXT:    Number of physical registers:     72
# CHECK-NEXT:    Total number of mappings created: 0
# CHECK-NEXT:    Max number of mappings used:      0
# CHECK-NEXT:    Number of optimizable moves:      21
# CHECK-NEXT:    Number of moves eliminated:       21  (100.0%)
# CHECK-NEXT:    Number of zero moves:             21  (100.0%)
# CHECK-NEXT:    Max moves eliminated per cycle:   2

# CHECK:      *  Register File #2 -- JIntegerPRF:
# CHECK-NEXT:    Number of physical registers:     64
# CHECK-NEXT:    Total number of mappings created: 0
# CHECK-NEXT:    Max number of mappings used:      0

# CHECK:      Resources:
# CHECK-NEXT: [0]   - JALU0
# CHECK-NEXT: [1]   - JALU1
# CHECK-NEXT: [2]   - JDiv
# CHECK-NEXT: [3]   - JFPA
# CHECK-NEXT: [4]   - JFPM
# CHECK-NEXT: [5]   - JFPU0
# CHECK-NEXT: [6]   - JFPU1
# CHECK-NEXT: [7]   - JLAGU
# CHECK-NEXT: [8]   - JMul
# CHECK-NEXT: [9]   - JSAGU
# CHECK-NEXT: [10]  - JSTC
# CHECK-NEXT: [11]  - JVALU0
# CHECK-NEXT: [12]  - JVALU1
# CHECK-NEXT: [13]  - JVIMUL

# CHECK:      Resource pressure per iteration:
# CHECK-NEXT: [0]    [1]    [2]    [3]    [4]    [5]    [6]    [7]    [8]    [9]    [10]   [11]   [12]   [13]
# CHECK-NEXT:  -      -      -      -      -      -      -      -      -      -      -      -      -      -

# CHECK:      Resource pressure by instruction:
# CHECK-NEXT: [0]    [1]    [2]    [3]    [4]    [5]    [6]    [7]    [8]    [9]    [10]   [11]   [12]   [13]   Instructions:
# CHECK-NEXT:  -      -      -      -      -      -      -      -      -      -      -      -      -      -     pxor	%mm0, %mm0
# CHECK-NEXT:  -      -      -      -      -      -      -      -      -      -      -      -      -      -     movq	%mm0, %mm1
# CHECK-NEXT:  -      -      -      -      -      -      -      -      -      -      -      -      -      -     xorps	%xmm0, %xmm0
# CHECK-NEXT:  -      -      -      -      -      -      -      -      -      -      -      -      -      -     movaps	%xmm0, %xmm1
# CHECK-NEXT:  -      -      -      -      -      -      -      -      -      -      -      -      -      -     movups	%xmm1, %xmm2
# CHECK-NEXT:  -      -      -      -      -      -      -      -      -      -      -      -      -      -     movapd	%xmm2, %xmm3
# CHECK-NEXT:  -      -      -      -      -      -      -      -      -      -      -      -      -      -     movupd	%xmm3, %xmm4
# CHECK-NEXT:  -      -      -      -      -      -      -      -      -      -      -      -      -      -     movdqa	%xmm4, %xmm5
# CHECK-NEXT:  -      -      -      -      -      -      -      -      -      -      -      -      -      -     movdqu	%xmm5, %xmm0

# CHECK:      Timeline view:
# CHECK-NEXT:                     01234
# CHECK-NEXT: Index     0123456789

# CHECK:      [0,0]     DR   .    .   .   pxor	%mm0, %mm0
# CHECK-NEXT: [0,1]     DR   .    .   .   movq	%mm0, %mm1
# CHECK-NEXT: [0,2]     .DR  .    .   .   xorps	%xmm0, %xmm0
# CHECK-NEXT: [0,3]     .DR  .    .   .   movaps	%xmm0, %xmm1
# CHECK-NEXT: [0,4]     . DR .    .   .   movups	%xmm1, %xmm2
# CHECK-NEXT: [0,5]     . DR .    .   .   movapd	%xmm2, %xmm3
# CHECK-NEXT: [0,6]     .  DR.    .   .   movupd	%xmm3, %xmm4
# CHECK-NEXT: [0,7]     .  DR.    .   .   movdqa	%xmm4, %xmm5
# CHECK-NEXT: [0,8]     .   DR    .   .   movdqu	%xmm5, %xmm0
# CHECK-NEXT: [1,0]     .   DR    .   .   pxor	%mm0, %mm0
# CHECK-NEXT: [1,1]     .    DR   .   .   movq	%mm0, %mm1
# CHECK-NEXT: [1,2]     .    DR   .   .   xorps	%xmm0, %xmm0
# CHECK-NEXT: [1,3]     .    .DR  .   .   movaps	%xmm0, %xmm1
# CHECK-NEXT: [1,4]     .    .DR  .   .   movups	%xmm1, %xmm2
# CHECK-NEXT: [1,5]     .    . DR .   .   movapd	%xmm2, %xmm3
# CHECK-NEXT: [1,6]     .    . DR .   .   movupd	%xmm3, %xmm4
# CHECK-NEXT: [1,7]     .    .  DR.   .   movdqa	%xmm4, %xmm5
# CHECK-NEXT: [1,8]     .    .  DR.   .   movdqu	%xmm5, %xmm0
# CHECK-NEXT: [2,0]     .    .   DR   .   pxor	%mm0, %mm0
# CHECK-NEXT: [2,1]     .    .   DR   .   movq	%mm0, %mm1
# CHECK-NEXT: [2,2]     .    .    DR  .   xorps	%xmm0, %xmm0
# CHECK-NEXT: [2,3]     .    .    DR  .   movaps	%xmm0, %xmm1
# CHECK-NEXT: [2,4]     .    .    .DR .   movups	%xmm1, %xmm2
# CHECK-NEXT: [2,5]     .    .    .DR .   movapd	%xmm2, %xmm3
# CHECK-NEXT: [2,6]     .    .    . DR.   movupd	%xmm3, %xmm4
# CHECK-NEXT: [2,7]     .    .    . DR.   movdqa	%xmm4, %xmm5
# CHECK-NEXT: [2,8]     .    .    .  DR   movdqu	%xmm5, %xmm0

# CHECK:      Average Wait times (based on the timeline view):
# CHECK-NEXT: [0]: Executions
# CHECK-NEXT: [1]: Average time spent waiting in a scheduler's queue
# CHECK-NEXT: [2]: Average time spent waiting in a scheduler's queue while ready
# CHECK-NEXT: [3]: Average time elapsed from WB until retire stage

# CHECK:            [0]    [1]    [2]    [3]
# CHECK-NEXT: 0.     3     0.0    0.0    0.0       pxor	%mm0, %mm0
# CHECK-NEXT: 1.     3     0.0    0.0    0.0       movq	%mm0, %mm1
# CHECK-NEXT: 2.     3     0.0    0.0    0.0       xorps	%xmm0, %xmm0
# CHECK-NEXT: 3.     3     0.0    0.0    0.0       movaps	%xmm0, %xmm1
# CHECK-NEXT: 4.     3     0.0    0.0    0.0       movups	%xmm1, %xmm2
# CHECK-NEXT: 5.     3     0.0    0.0    0.0       movapd	%xmm2, %xmm3
# CHECK-NEXT: 6.     3     0.0    0.0    0.0       movupd	%xmm3, %xmm4
# CHECK-NEXT: 7.     3     0.0    0.0    0.0       movdqa	%xmm4, %xmm5
# CHECK-NEXT: 8.     3     0.0    0.0    0.0       movdqu	%xmm5, %xmm0
# CHECK-NEXT:        3     0.0    0.0    0.0       <total>