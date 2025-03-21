;=========================== begin_copyright_notice ============================
;
; Copyright (C) 2022-2025 Intel Corporation
;
; SPDX-License-Identifier: MIT
;
;============================ end_copyright_notice =============================

; RUN: %opt %use_old_pass_manager% -GenXFuncBaling -print-baling-info -disable-output \
; RUN: -march=genx64 -mcpu=XeHPG -mtriple=spir64-unknown-unknown -S < %s | FileCheck %s

; CHECK: GenXBaling dump start
; CHECK: bales in function: test:
; CHECK: %1 = sext <16 x i8> %val to <16 x i32>: sext
; CHECK-NOT: %2 = icmp ult <16 x i32> %1, <i32 -1442606154, i32 -1442606154, i32 -1442606154, i32 -1442606154, i32 -1442606154, i32 -1442606154, i32 -1442606154, i32 -1442606154, i32 -1442606154, i32 -1442606154, i32 -1442606154, i32 -1442606154, i32 -1442606154, i32 -1442606154, i32 -1442606154, i32 -1442606154>: maininst 0
; CHECK: GenXBaling dump end

define <16 x i1> @test(<16 x i8> %val) {
  %1 = sext <16 x i8> %val to <16 x i32>
  %2 = icmp ult <16 x i32> %1, <i32 -1442606154, i32 -1442606154, i32 -1442606154, i32 -1442606154, i32 -1442606154, i32 -1442606154, i32 -1442606154, i32 -1442606154, i32 -1442606154, i32 -1442606154, i32 -1442606154, i32 -1442606154, i32 -1442606154, i32 -1442606154, i32 -1442606154, i32 -1442606154>
  ret <16 x i1> %2
}
