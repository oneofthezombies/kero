; NOTE: Assertions have been autogenerated by utils/update_llc_test_checks.py UTC_ARGS: --version 2
; RUN: llc -mtriple=amdgcn -mcpu=gfx1100 -amdgpu-enable-delay-alu=0 -global-isel=1 -verify-machineinstrs < %s | FileCheck  -check-prefixes=GFX11 %s
; RUN: llc -mtriple=amdgcn -mcpu=gfx1100 -amdgpu-enable-delay-alu=0 -global-isel=0 -verify-machineinstrs < %s | FileCheck  -check-prefixes=GFX11 %s

declare i32 @llvm.amdgcn.s.wqm.i32(i32)
declare i64 @llvm.amdgcn.s.wqm.i64(i64)

define i32 @test_s_wqm_constant_i32() {
; GFX11-LABEL: test_s_wqm_constant_i32:
; GFX11:       ; %bb.0:
; GFX11-NEXT:    s_waitcnt vmcnt(0) expcnt(0) lgkmcnt(0)
; GFX11-NEXT:    v_mov_b32_e32 v0, 0xff00ff0f
; GFX11-NEXT:    s_setpc_b64 s[30:31]
  %br = call i32 @llvm.amdgcn.s.wqm.i32(i32 u0x85003A02)
  ret i32 %br
}

define i32 @test_s_wqm_constant_zero_i32() {
; GFX11-LABEL: test_s_wqm_constant_zero_i32:
; GFX11:       ; %bb.0:
; GFX11-NEXT:    s_waitcnt vmcnt(0) expcnt(0) lgkmcnt(0)
; GFX11-NEXT:    v_mov_b32_e32 v0, 0
; GFX11-NEXT:    s_setpc_b64 s[30:31]
  %br = call i32 @llvm.amdgcn.s.wqm.i32(i32 0)
  ret i32 %br
}

define i32 @test_s_wqm_constant_neg_one_i32() {
; GFX11-LABEL: test_s_wqm_constant_neg_one_i32:
; GFX11:       ; %bb.0:
; GFX11-NEXT:    s_waitcnt vmcnt(0) expcnt(0) lgkmcnt(0)
; GFX11-NEXT:    v_mov_b32_e32 v0, -1
; GFX11-NEXT:    s_setpc_b64 s[30:31]
  %br = call i32 @llvm.amdgcn.s.wqm.i32(i32 -1)
  ret i32 %br
}

define i32 @test_s_wqm_constant_undef_i32() {
; GFX11-LABEL: test_s_wqm_constant_undef_i32:
; GFX11:       ; %bb.0:
; GFX11-NEXT:    s_waitcnt vmcnt(0) expcnt(0) lgkmcnt(0)
; GFX11-NEXT:    s_wqm_b32 s0, s0
; GFX11-NEXT:    v_mov_b32_e32 v0, s0
; GFX11-NEXT:    s_setpc_b64 s[30:31]
  %br = call i32 @llvm.amdgcn.s.wqm.i32(i32 undef)
  ret i32 %br
}

define i32 @test_s_wqm_constant_poison_i32() {
; GFX11-LABEL: test_s_wqm_constant_poison_i32:
; GFX11:       ; %bb.0:
; GFX11-NEXT:    s_waitcnt vmcnt(0) expcnt(0) lgkmcnt(0)
; GFX11-NEXT:    s_wqm_b32 s0, s0
; GFX11-NEXT:    v_mov_b32_e32 v0, s0
; GFX11-NEXT:    s_setpc_b64 s[30:31]
  %br = call i32 @llvm.amdgcn.s.wqm.i32(i32 poison)
  ret i32 %br
}


define amdgpu_cs void @test_s_wqm_sgpr_i32(i32 inreg %mask, ptr addrspace(1) %out) {
; GFX11-LABEL: test_s_wqm_sgpr_i32:
; GFX11:       ; %bb.0: ; %entry
; GFX11-NEXT:    s_wqm_b32 s0, s0
; GFX11-NEXT:    v_mov_b32_e32 v2, s0
; GFX11-NEXT:    global_store_b32 v[0:1], v2, off
; GFX11-NEXT:    s_nop 0
; GFX11-NEXT:    s_sendmsg sendmsg(MSG_DEALLOC_VGPRS)
; GFX11-NEXT:    s_endpgm
entry:
  %br = call i32 @llvm.amdgcn.s.wqm.i32(i32 %mask)
  store i32 %br, ptr addrspace(1) %out
  ret void
}

define i32 @test_s_wqm_vgpr_i32(i32 %mask) {
; GFX11-LABEL: test_s_wqm_vgpr_i32:
; GFX11:       ; %bb.0: ; %entry
; GFX11-NEXT:    s_waitcnt vmcnt(0) expcnt(0) lgkmcnt(0)
; GFX11-NEXT:    v_readfirstlane_b32 s0, v0
; GFX11-NEXT:    s_wqm_b32 s0, s0
; GFX11-NEXT:    v_mov_b32_e32 v0, s0
; GFX11-NEXT:    s_setpc_b64 s[30:31]
entry:
  %br = call i32 @llvm.amdgcn.s.wqm.i32(i32 %mask)
  ret i32 %br
}

define i64 @test_s_wqm_constant_i64() {
; GFX11-LABEL: test_s_wqm_constant_i64:
; GFX11:       ; %bb.0:
; GFX11-NEXT:    s_waitcnt vmcnt(0) expcnt(0) lgkmcnt(0)
; GFX11-NEXT:    v_mov_b32_e32 v0, 0xff00ffff
; GFX11-NEXT:    v_mov_b32_e32 v1, 0xffff0fff
; GFX11-NEXT:    s_setpc_b64 s[30:31]
  %br = call i64 @llvm.amdgcn.s.wqm.i64(i64 u0x12480FDBAC00753E)
  ret i64 %br
}

define i64 @test_s_wqm_constant_zero_i64() {
; GFX11-LABEL: test_s_wqm_constant_zero_i64:
; GFX11:       ; %bb.0:
; GFX11-NEXT:    s_waitcnt vmcnt(0) expcnt(0) lgkmcnt(0)
; GFX11-NEXT:    v_dual_mov_b32 v0, 0 :: v_dual_mov_b32 v1, 0
; GFX11-NEXT:    s_setpc_b64 s[30:31]
  %br = call i64 @llvm.amdgcn.s.wqm.i64(i64 0)
  ret i64 %br
}

define i64 @test_s_wqm_constant_neg_one_i64() {
; GFX11-LABEL: test_s_wqm_constant_neg_one_i64:
; GFX11:       ; %bb.0:
; GFX11-NEXT:    s_waitcnt vmcnt(0) expcnt(0) lgkmcnt(0)
; GFX11-NEXT:    v_dual_mov_b32 v0, -1 :: v_dual_mov_b32 v1, -1
; GFX11-NEXT:    s_setpc_b64 s[30:31]
  %br = call i64 @llvm.amdgcn.s.wqm.i64(i64 -1)
  ret i64 %br
}

define i64 @test_s_wqm_constant_undef_i64() {
; GFX11-LABEL: test_s_wqm_constant_undef_i64:
; GFX11:       ; %bb.0:
; GFX11-NEXT:    s_waitcnt vmcnt(0) expcnt(0) lgkmcnt(0)
; GFX11-NEXT:    s_wqm_b64 s[0:1], s[0:1]
; GFX11-NEXT:    v_dual_mov_b32 v0, s0 :: v_dual_mov_b32 v1, s1
; GFX11-NEXT:    s_setpc_b64 s[30:31]
  %br = call i64 @llvm.amdgcn.s.wqm.i64(i64 undef)
  ret i64 %br
}

define i64 @test_s_wqm_constant_poison_i64() {
; GFX11-LABEL: test_s_wqm_constant_poison_i64:
; GFX11:       ; %bb.0:
; GFX11-NEXT:    s_waitcnt vmcnt(0) expcnt(0) lgkmcnt(0)
; GFX11-NEXT:    s_wqm_b64 s[0:1], s[0:1]
; GFX11-NEXT:    v_dual_mov_b32 v0, s0 :: v_dual_mov_b32 v1, s1
; GFX11-NEXT:    s_setpc_b64 s[30:31]
  %br = call i64 @llvm.amdgcn.s.wqm.i64(i64 poison)
  ret i64 %br
}

define amdgpu_cs void @test_s_wqm_sgpr_i64(i64 inreg %mask, ptr addrspace(1) %out) {
; GFX11-LABEL: test_s_wqm_sgpr_i64:
; GFX11:       ; %bb.0: ; %entry
; GFX11-NEXT:    s_wqm_b64 s[0:1], s[0:1]
; GFX11-NEXT:    v_dual_mov_b32 v3, s1 :: v_dual_mov_b32 v2, s0
; GFX11-NEXT:    global_store_b64 v[0:1], v[2:3], off
; GFX11-NEXT:    s_nop 0
; GFX11-NEXT:    s_sendmsg sendmsg(MSG_DEALLOC_VGPRS)
; GFX11-NEXT:    s_endpgm
entry:
  %br = call i64 @llvm.amdgcn.s.wqm.i64(i64 %mask)
  store i64 %br, ptr addrspace(1) %out
  ret void
}

define i64 @test_s_wqm_vgpr_i64(i64 %mask) {
; GFX11-LABEL: test_s_wqm_vgpr_i64:
; GFX11:       ; %bb.0: ; %entry
; GFX11-NEXT:    s_waitcnt vmcnt(0) expcnt(0) lgkmcnt(0)
; GFX11-NEXT:    v_readfirstlane_b32 s0, v0
; GFX11-NEXT:    v_readfirstlane_b32 s1, v1
; GFX11-NEXT:    s_wqm_b64 s[0:1], s[0:1]
; GFX11-NEXT:    v_dual_mov_b32 v0, s0 :: v_dual_mov_b32 v1, s1
; GFX11-NEXT:    s_setpc_b64 s[30:31]
entry:
  %br = call i64 @llvm.amdgcn.s.wqm.i64(i64 %mask)
  ret i64 %br
}