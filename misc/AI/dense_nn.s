	.file	"dense_nn.cpp"
	.intel_syntax noprefix
	.text
	.align 2
	.p2align 4
	.globl	_ZN18DenseNeuralNetwork10getOutputsEv
	.type	_ZN18DenseNeuralNetwork10getOutputsEv, @function
_ZN18DenseNeuralNetwork10getOutputsEv:
.LFB4158:
	.cfi_startproc
	mov	rax, QWORD PTR [rdi+16]
	sub	rax, 24
	ret
	.cfi_endproc
.LFE4158:
	.size	_ZN18DenseNeuralNetwork10getOutputsEv, .-_ZN18DenseNeuralNetwork10getOutputsEv
	.align 2
	.p2align 4
	.globl	_ZN18DenseNeuralNetwork5trainEPKSt6vectorIfSaIfEEf
	.type	_ZN18DenseNeuralNetwork5trainEPKSt6vectorIfSaIfEEf, @function
_ZN18DenseNeuralNetwork5trainEPKSt6vectorIfSaIfEEf:
.LFB4161:
	.cfi_startproc
	ret
	.cfi_endproc
.LFE4161:
	.size	_ZN18DenseNeuralNetwork5trainEPKSt6vectorIfSaIfEEf, .-_ZN18DenseNeuralNetwork5trainEPKSt6vectorIfSaIfEEf
	.align 2
	.p2align 4
	.globl	_ZN18DenseNeuralNetwork10saveToFileEPSt14basic_ofstreamIcSt11char_traitsIcEE
	.type	_ZN18DenseNeuralNetwork10saveToFileEPSt14basic_ofstreamIcSt11char_traitsIcEE, @function
_ZN18DenseNeuralNetwork10saveToFileEPSt14basic_ofstreamIcSt11char_traitsIcEE:
.LFB4162:
	.cfi_startproc
	ret
	.cfi_endproc
.LFE4162:
	.size	_ZN18DenseNeuralNetwork10saveToFileEPSt14basic_ofstreamIcSt11char_traitsIcEE, .-_ZN18DenseNeuralNetwork10saveToFileEPSt14basic_ofstreamIcSt11char_traitsIcEE
	.globl	_ZN18DenseNeuralNetwork12readFromFileEPSt14basic_ifstreamIcSt11char_traitsIcEE
	.set	_ZN18DenseNeuralNetwork12readFromFileEPSt14basic_ifstreamIcSt11char_traitsIcEE,_ZN18DenseNeuralNetwork10saveToFileEPSt14basic_ofstreamIcSt11char_traitsIcEE
	.align 2
	.p2align 4
	.globl	_ZN18DenseNeuralNetwork7processEPKSt6vectorIfSaIfEE
	.type	_ZN18DenseNeuralNetwork7processEPKSt6vectorIfSaIfEE, @function
_ZN18DenseNeuralNetwork7processEPKSt6vectorIfSaIfEE:
.LFB4160:
	.cfi_startproc
	lea	r10, [rsp+8]
	.cfi_def_cfa 10, 0
	and	rsp, -32
	mov	r11, rdi
	push	QWORD PTR [r10-8]
	push	rbp
	mov	rbp, rsp
	.cfi_escape 0x10,0x6,0x2,0x76,0
	push	r15
	push	r14
	push	r13
	push	r12
	push	r10
	.cfi_escape 0xf,0x3,0x76,0x58,0x6
	.cfi_escape 0x10,0xf,0x2,0x76,0x78
	.cfi_escape 0x10,0xe,0x2,0x76,0x70
	.cfi_escape 0x10,0xd,0x2,0x76,0x68
	.cfi_escape 0x10,0xc,0x2,0x76,0x60
	push	rbx
	sub	rsp, 192
	.cfi_escape 0x10,0x3,0x2,0x76,0x50
	mov	rdi, QWORD PTR [rsi+8]
	mov	rbx, QWORD PTR [rsi]
	mov	QWORD PTR [rbp-80], rdi
	sub	rdi, rbx
	mov	r15, rdi
	mov	r10, rdi
	mov	rdi, QWORD PTR [r11+8]
	sar	r15, 2
	mov	rax, QWORD PTR [rdi+8]
	mov	r8, QWORD PTR [rdi]
	mov	QWORD PTR [rbp-200], rdi
	mov	rdi, QWORD PTR [r11+80]
	mov	rdx, rax
	sub	rdx, r8
	mov	QWORD PTR [rbp-120], rdi
	sar	rdx, 2
	mov	QWORD PTR [rbp-128], rdx
	cmp	rax, r8
	je	.L6
	mov	rax, QWORD PTR [r11+32]
	test	r10, r10
	mov	r9d, 1
	mov	QWORD PTR [rbp-136], r8
	cmovne	r9, r15
	mov	QWORD PTR [rbp-144], r10
	xor	r14d, r14d
	mov	rax, QWORD PTR [rax]
	mov	QWORD PTR [rbp-208], r11
	mov	r13, r9
	mov	QWORD PTR [rbp-160], r9
	mov	QWORD PTR [rbp-112], rax
	mov	rax, r9
	shr	r13, 3
	and	rax, -8
	sal	r13, 5
	mov	QWORD PTR [rbp-184], rax
	mov	DWORD PTR [rbp-192], eax
	mov	rax, r9
	and	eax, 7
	mov	QWORD PTR [rbp-152], rax
	mov	rax, r15
	mov	r15, r13
	mov	r13, r14
	mov	r12, rax
	.p2align 4,,10
	.p2align 3
.L7:
	mov	rax, QWORD PTR [rbp-80]
	vxorps	xmm0, xmm0, xmm0
	cmp	rbx, rax
	je	.L14
	mov	rax, QWORD PTR [rbp-120]
	cmp	QWORD PTR [rbp-144], 28
	mov	rdi, QWORD PTR [rax]
	jbe	.L35
	lea	rdx, [rdi+r14*4]
	xor	eax, eax
	vxorps	xmm1, xmm1, xmm1
	.p2align 4,,10
	.p2align 3
.L9:
	vmovups	ymm7, YMMWORD PTR [rbx+rax]
	vmulps	ymm0, ymm7, YMMWORD PTR [rdx+rax]
	add	rax, 32
	vaddps	ymm1, ymm1, ymm0
	cmp	rax, r15
	jne	.L9
	vextractf128	xmm3, ymm1, 0x1
	cmp	QWORD PTR [rbp-152], 0
	vaddps	xmm0, xmm3, xmm1
	vaddps	xmm1, xmm1, xmm3
	vmovhlps	xmm2, xmm0, xmm0
	vaddps	xmm2, xmm2, xmm0
	vshufps	xmm0, xmm2, xmm2, 85
	vaddps	xmm0, xmm0, xmm2
	je	.L64
	mov	eax, DWORD PTR [rbp-192]
	mov	rdx, QWORD PTR [rbp-184]
	vzeroupper
.L8:
	mov	r9, QWORD PTR [rbp-160]
	sub	r9, rdx
	lea	r10, [r9-1]
	cmp	r10, 2
	jbe	.L11
	lea	r10, [r14+rdx]
	vmovups	xmm6, XMMWORD PTR [rdi+r10*4]
	vmulps	xmm0, xmm6, XMMWORD PTR [rbx+rdx*4]
	mov	r10, r9
	and	r10, -4
	add	rdx, r10
	add	eax, r10d
	and	r9d, 3
	vaddps	xmm0, xmm0, xmm1
	vmovhlps	xmm1, xmm0, xmm0
	vaddps	xmm1, xmm1, xmm0
	vshufps	xmm0, xmm1, xmm1, 85
	vaddps	xmm0, xmm0, xmm1
	je	.L14
.L11:
	lea	r9, [r14+rdx]
	vmovss	xmm1, DWORD PTR [rdi+r9*4]
	vmulss	xmm1, xmm1, DWORD PTR [rbx+rdx*4]
	lea	edx, [rax+1]
	movsx	rdx, edx
	vaddss	xmm0, xmm0, xmm1
	cmp	rdx, r12
	jnb	.L14
	lea	r9, [rdx+r14]
	add	eax, 2
	lea	r10, [0+rdx*4]
	vmovss	xmm1, DWORD PTR [rdi+r9*4]
	vmulss	xmm1, xmm1, DWORD PTR [rbx+rdx*4]
	cdqe
	vaddss	xmm0, xmm0, xmm1
	cmp	rax, r12
	jnb	.L14
	add	rax, r14
	vmovss	xmm1, DWORD PTR [rdi+rax*4]
	vmulss	xmm1, xmm1, DWORD PTR [rbx+4+r10]
	vaddss	xmm0, xmm0, xmm1
.L14:
	mov	rax, QWORD PTR [rbp-112]
	add	r14, r12
	vaddss	xmm0, xmm0, DWORD PTR [rax+r13*4]
	vxorps	xmm0, xmm0, XMMWORD PTR .LC1[rip]
	vcvtss2sd	xmm0, xmm0, xmm0
	call	exp
	mov	rax, QWORD PTR [rbp-136]
	vaddsd	xmm0, xmm0, QWORD PTR .LC2[rip]
	vmovsd	xmm4, QWORD PTR .LC2[rip]
	vdivsd	xmm0, xmm4, xmm0
	vcvtsd2ss	xmm0, xmm0, xmm0
	vmovss	DWORD PTR [rax+r13*4], xmm0
	mov	rax, QWORD PTR [rbp-128]
	add	r13, 1
	cmp	r13, rax
	jb	.L7
	mov	r11, QWORD PTR [rbp-208]
.L6:
	mov	rdi, QWORD PTR [rbp-120]
	mov	rax, QWORD PTR [r11+88]
	movabs	rcx, -6148914691236517205
	mov	QWORD PTR [rbp-160], 0
	mov	r13d, 24
	sub	rax, rdi
	mov	rdx, rax
	sar	rdx, 3
	imul	rdx, rcx
	lea	rdi, [rdx-1]
	mov	QWORD PTR [rbp-208], rdi
	cmp	rax, 24
	je	.L65
	mov	QWORD PTR [rbp-216], r11
	.p2align 4,,10
	.p2align 3
.L15:
	mov	rsi, QWORD PTR [rbp-200]
	add	QWORD PTR [rbp-160], 1
	mov	rcx, QWORD PTR [rsi+8+r13]
	mov	r15, QWORD PTR [rsi-16+r13]
	mov	r12, QWORD PTR [rsi+r13]
	mov	rax, QWORD PTR [rsi-24+r13]
	mov	rdx, rcx
	mov	rbx, r15
	sub	rdx, r12
	sub	rbx, rax
	mov	r14, rdx
	mov	QWORD PTR [rbp-112], rbx
	sar	rbx, 2
	sar	r14, 2
	test	rdx, rdx
	je	.L16
	mov	rdi, QWORD PTR [rbp-216]
	cmp	r15, rax
	mov	r9d, 1
	mov	QWORD PTR [rbp-184], rcx
	cmovne	r9, rbx
	mov	QWORD PTR [rbp-192], rdx
	xor	r8d, r8d
	mov	rsi, QWORD PTR [rdi+32]
	mov	QWORD PTR [rbp-136], r9
	mov	rdi, r9
	mov	rsi, QWORD PTR [rsi+r13]
	shr	rdi, 3
	sal	rdi, 5
	mov	QWORD PTR [rbp-80], rsi
	mov	rsi, r9
	and	r9d, 7
	mov	QWORD PTR [rbp-128], r9
	and	rsi, -8
	mov	QWORD PTR [rbp-152], rsi
	mov	DWORD PTR [rbp-144], esi
	xor	esi, esi
	.p2align 4,,10
	.p2align 3
.L17:
	vxorps	xmm0, xmm0, xmm0
	cmp	r15, rax
	je	.L25
	mov	rcx, QWORD PTR [rbp-120]
	cmp	QWORD PTR [rbp-112], 28
	mov	r9, QWORD PTR [rcx+r13]
	jbe	.L37
	lea	rcx, [r9+rsi*4]
	xor	edx, edx
	vxorps	xmm1, xmm1, xmm1
	.p2align 4,,10
	.p2align 3
.L19:
	vmovups	ymm5, YMMWORD PTR [rcx+rdx]
	vmulps	ymm0, ymm5, YMMWORD PTR [rax+rdx]
	add	rdx, 32
	vaddps	ymm1, ymm1, ymm0
	cmp	rdi, rdx
	jne	.L19
	vextractf128	xmm4, ymm1, 0x1
	cmp	QWORD PTR [rbp-128], 0
	vaddps	xmm0, xmm4, xmm1
	vaddps	xmm1, xmm1, xmm4
	vmovhlps	xmm3, xmm0, xmm0
	vaddps	xmm3, xmm3, xmm0
	vshufps	xmm0, xmm3, xmm3, 85
	vaddps	xmm0, xmm0, xmm3
	je	.L25
	mov	ecx, DWORD PTR [rbp-144]
	mov	rdx, QWORD PTR [rbp-152]
.L18:
	mov	r10, QWORD PTR [rbp-136]
	sub	r10, rdx
	lea	r11, [r10-1]
	cmp	r11, 2
	jbe	.L21
	lea	r11, [rdx+rsi]
	vmovups	xmm6, XMMWORD PTR [r9+r11*4]
	vmulps	xmm0, xmm6, XMMWORD PTR [rax+rdx*4]
	mov	r11, r10
	and	r11, -4
	add	rdx, r11
	add	ecx, r11d
	and	r10d, 3
	vaddps	xmm0, xmm0, xmm1
	vmovhlps	xmm1, xmm0, xmm0
	vaddps	xmm1, xmm1, xmm0
	vshufps	xmm0, xmm1, xmm1, 85
	vaddps	xmm0, xmm0, xmm1
	je	.L25
.L21:
	lea	r10, [rdx+rsi]
	vmovss	xmm1, DWORD PTR [r9+r10*4]
	vmulss	xmm1, xmm1, DWORD PTR [rax+rdx*4]
	lea	edx, [rcx+1]
	movsx	rdx, edx
	vaddss	xmm0, xmm0, xmm1
	cmp	rdx, rbx
	jnb	.L25
	lea	r10, [rdx+rsi]
	add	ecx, 2
	lea	r11, [0+rdx*4]
	vmovss	xmm1, DWORD PTR [r9+r10*4]
	vmulss	xmm1, xmm1, DWORD PTR [rax+rdx*4]
	movsx	rcx, ecx
	vaddss	xmm0, xmm0, xmm1
	cmp	rcx, rbx
	jnb	.L25
	add	rcx, rsi
	vmovss	xmm1, DWORD PTR [r9+rcx*4]
	vmulss	xmm1, xmm1, DWORD PTR [rax+4+r11]
	vaddss	xmm0, xmm0, xmm1
.L25:
	mov	rcx, QWORD PTR [rbp-80]
	add	rsi, rbx
	vaddss	xmm0, xmm0, DWORD PTR [rcx+r8*4]
	vmovss	DWORD PTR [r12+r8*4], xmm0
	add	r8, 1
	cmp	r8, r14
	jb	.L17
	mov	rcx, QWORD PTR [rbp-184]
	mov	rdx, QWORD PTR [rbp-192]
	cmp	rcx, r12
	je	.L27
	test	rdx, rdx
	mov	eax, 1
	cmovne	rax, r14
	cmp	rdx, 28
	jbe	.L39
	mov	rbx, rax
	mov	QWORD PTR [rbp-128], r12
	mov	r15, rax
	shr	rbx, 3
	sal	rbx, 5
	add	rbx, r12
	.p2align 4,,10
	.p2align 3
.L31:
	vmovups	ymm4, YMMWORD PTR [r12]
	vxorps	ymm1, ymm4, YMMWORD PTR .LC3[rip]
	add	r12, 32
	vmovaps	YMMWORD PTR [rbp-112], ymm1
	vcvtps2pd	ymm0, xmm1
	call	_ZGVdN4v_exp
	vmovaps	ymm1, YMMWORD PTR [rbp-112]
	vmovapd	YMMWORD PTR [rbp-80], ymm0
	vextractf128	xmm0, ymm1, 0x1
	vcvtps2pd	ymm0, xmm0
	call	_ZGVdN4v_exp
	vmovapd	ymm2, YMMWORD PTR .LC5[rip]
	vmovapd	ymm1, ymm0
	vaddpd	ymm0, ymm2, YMMWORD PTR [rbp-80]
	vaddpd	ymm1, ymm1, ymm2
	vdivpd	ymm0, ymm2, ymm0
	vdivpd	ymm1, ymm2, ymm1
	vcvtpd2ps	xmm0, ymm0
	vcvtpd2ps	xmm1, ymm1
	vinsertf128	ymm0, ymm0, xmm1, 0x1
	vmovups	YMMWORD PTR [r12-32], ymm0
	cmp	r12, rbx
	jne	.L31
	mov	rdx, r15
	mov	rax, r15
	mov	r12, QWORD PTR [rbp-128]
	and	rdx, -8
	mov	ebx, edx
	test	al, 7
	je	.L27
.L30:
	sub	rax, rdx
	mov	r15, rax
	lea	rax, [rax-1]
	cmp	rax, 2
	jbe	.L26
	lea	rax, [r12+rdx*4]
	mov	QWORD PTR [rbp-112], rdx
	vmovups	xmm6, XMMWORD PTR [rax]
	vxorps	xmm1, xmm6, XMMWORD PTR .LC6[rip]
	mov	QWORD PTR [rbp-80], rax
	vmovhps	QWORD PTR [rbp-176], xmm1
	vcvtps2pd	xmm0, xmm1
	vcvtps2pd	xmm1, QWORD PTR [rbp-176]
	vinsertf128	ymm0, ymm0, xmm1, 0x1
	call	_ZGVdN4v_exp
	mov	rax, QWORD PTR [rbp-80]
	mov	rdx, QWORD PTR [rbp-112]
	vmovddup	xmm6, QWORD PTR .LC2[rip]
	vmovapd	xmm1, XMMWORD PTR .LC7[rip]
	vaddpd	xmm1, xmm1, xmm0
	vextractf128	xmm0, ymm0, 0x1
	vaddpd	xmm0, xmm0, XMMWORD PTR .LC7[rip]
	vdivpd	xmm1, xmm6, xmm1
	vdivpd	xmm0, xmm6, xmm0
	vinsertf128	ymm0, ymm1, xmm0, 0x1
	vcvtpd2ps	xmm0, ymm0
	vmovups	XMMWORD PTR [rax], xmm0
	mov	rax, r15
	and	rax, -4
	add	rdx, rax
	add	ebx, eax
	and	r15d, 3
	je	.L27
.L26:
	lea	r15, [r12+rdx*4]
	vmovss	xmm0, DWORD PTR [r15]
	vxorps	xmm0, xmm0, XMMWORD PTR .LC1[rip]
	vcvtss2sd	xmm0, xmm0, xmm0
	vzeroupper
	call	exp
	vaddsd	xmm0, xmm0, QWORD PTR .LC2[rip]
	vmovsd	xmm7, QWORD PTR .LC2[rip]
	vdivsd	xmm0, xmm7, xmm0
	vcvtsd2ss	xmm0, xmm0, xmm0
	vmovss	DWORD PTR [r15], xmm0
	lea	r15d, [rbx+1]
	movsx	r15, r15d
	cmp	r15, r14
	jnb	.L27
	sal	r15, 2
	lea	rax, [r12+r15]
	vmovss	xmm0, DWORD PTR [rax]
	vxorps	xmm0, xmm0, XMMWORD PTR .LC1[rip]
	mov	QWORD PTR [rbp-80], rax
	vcvtss2sd	xmm0, xmm0, xmm0
	call	exp
	mov	rax, QWORD PTR [rbp-80]
	vaddsd	xmm0, xmm0, QWORD PTR .LC2[rip]
	vmovsd	xmm7, QWORD PTR .LC2[rip]
	vdivsd	xmm0, xmm7, xmm0
	vcvtsd2ss	xmm0, xmm0, xmm0
	vmovss	DWORD PTR [rax], xmm0
	lea	eax, [rbx+2]
	cdqe
	cmp	rax, r14
	jnb	.L27
	lea	rbx, [r12+4+r15]
	vmovss	xmm0, DWORD PTR [rbx]
	vxorps	xmm0, xmm0, XMMWORD PTR .LC1[rip]
	vcvtss2sd	xmm0, xmm0, xmm0
	call	exp
	vaddsd	xmm0, xmm0, QWORD PTR .LC2[rip]
	vmovsd	xmm7, QWORD PTR .LC2[rip]
	vdivsd	xmm0, xmm7, xmm0
	vcvtsd2ss	xmm0, xmm0, xmm0
	vmovss	DWORD PTR [rbx], xmm0
.L27:
	mov	rsi, QWORD PTR [rbp-208]
	add	r13, 24
	cmp	QWORD PTR [rbp-160], rsi
	jb	.L15
	vzeroupper
.L65:
	add	rsp, 192
	pop	rbx
	pop	r10
	.cfi_remember_state
	.cfi_def_cfa 10, 0
	pop	r12
	pop	r13
	pop	r14
	pop	r15
	pop	rbp
	lea	rsp, [r10-8]
	.cfi_def_cfa 7, 8
	ret
.L37:
	.cfi_restore_state
	vxorps	xmm1, xmm1, xmm1
	xor	ecx, ecx
	vxorps	xmm0, xmm0, xmm0
	xor	edx, edx
	jmp	.L18
.L64:
	vzeroupper
	jmp	.L14
.L35:
	vxorps	xmm1, xmm1, xmm1
	xor	eax, eax
	vxorps	xmm0, xmm0, xmm0
	xor	edx, edx
	jmp	.L8
.L16:
	xor	ebx, ebx
	xor	edx, edx
	cmp	rcx, r12
	jne	.L26
	jmp	.L27
.L39:
	xor	ebx, ebx
	xor	edx, edx
	jmp	.L30
	.cfi_endproc
.LFE4160:
	.size	_ZN18DenseNeuralNetwork7processEPKSt6vectorIfSaIfEE, .-_ZN18DenseNeuralNetwork7processEPKSt6vectorIfSaIfEE
	.section	.text._ZNSt6vectorIS_IfSaIfEESaIS1_EED2Ev,"axG",@progbits,_ZNSt6vectorIS_IfSaIfEESaIS1_EED5Ev,comdat
	.align 2
	.p2align 4
	.weak	_ZNSt6vectorIS_IfSaIfEESaIS1_EED2Ev
	.type	_ZNSt6vectorIS_IfSaIfEESaIS1_EED2Ev, @function
_ZNSt6vectorIS_IfSaIfEESaIS1_EED2Ev:
.LFB4522:
	.cfi_startproc
	push	r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	mov	r12, rdi
	push	rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	push	rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	mov	rbp, QWORD PTR [rdi+8]
	mov	rbx, QWORD PTR [rdi]
	cmp	rbp, rbx
	je	.L68
	.p2align 4,,10
	.p2align 3
.L72:
	mov	rdi, QWORD PTR [rbx]
	test	rdi, rdi
	je	.L69
	mov	rsi, QWORD PTR [rbx+16]
	add	rbx, 24
	sub	rsi, rdi
	call	_ZdlPvm
	cmp	rbp, rbx
	jne	.L72
.L71:
	mov	rbx, QWORD PTR [r12]
.L68:
	test	rbx, rbx
	je	.L74
	mov	rsi, QWORD PTR [r12+16]
	mov	rdi, rbx
	sub	rsi, rbx
	pop	rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	pop	rbp
	.cfi_def_cfa_offset 16
	pop	r12
	.cfi_def_cfa_offset 8
	jmp	_ZdlPvm
	.p2align 4,,10
	.p2align 3
.L69:
	.cfi_restore_state
	add	rbx, 24
	cmp	rbp, rbx
	jne	.L72
	jmp	.L71
	.p2align 4,,10
	.p2align 3
.L74:
	pop	rbx
	.cfi_def_cfa_offset 24
	pop	rbp
	.cfi_def_cfa_offset 16
	pop	r12
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE4522:
	.size	_ZNSt6vectorIS_IfSaIfEESaIS1_EED2Ev, .-_ZNSt6vectorIS_IfSaIfEESaIS1_EED2Ev
	.weak	_ZNSt6vectorIS_IfSaIfEESaIS1_EED1Ev
	.set	_ZNSt6vectorIS_IfSaIfEESaIS1_EED1Ev,_ZNSt6vectorIS_IfSaIfEESaIS1_EED2Ev
	.section	.rodata._ZNSt6vectorIfSaIfEE17_M_default_appendEm.str1.1,"aMS",@progbits,1
.LC8:
	.string	"vector::_M_default_append"
	.section	.text._ZNSt6vectorIfSaIfEE17_M_default_appendEm,"axG",@progbits,_ZNSt6vectorIfSaIfEE17_M_default_appendEm,comdat
	.align 2
	.p2align 4
	.weak	_ZNSt6vectorIfSaIfEE17_M_default_appendEm
	.type	_ZNSt6vectorIfSaIfEE17_M_default_appendEm, @function
_ZNSt6vectorIfSaIfEE17_M_default_appendEm:
.LFB4736:
	.cfi_startproc
	test	rsi, rsi
	je	.L102
	movabs	rax, 2305843009213693951
	push	r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	push	r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	push	r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	push	r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	push	rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	mov	rbp, rdi
	push	rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	mov	rbx, rsi
	sub	rsp, 24
	.cfi_def_cfa_offset 80
	mov	rdx, QWORD PTR [rdi+8]
	mov	r12, rdx
	sub	r12, QWORD PTR [rdi]
	mov	rcx, r12
	sar	rcx, 2
	sub	rax, rcx
	mov	rsi, rax
	mov	rax, QWORD PTR [rdi+16]
	sub	rax, rdx
	sar	rax, 2
	cmp	rax, rbx
	jnb	.L105
	cmp	rsi, rbx
	jb	.L106
	lea	r14, [rbx+rcx]
	cmp	rcx, rbx
	jb	.L107
	movabs	r13, 9223372036854775804
	lea	rax, [rcx+rcx]
	cmp	rax, rcx
	jnb	.L108
.L82:
	mov	rdi, r13
	call	_Znwm
	mov	r8, QWORD PTR [rbp+0]
	mov	rcx, QWORD PTR [rbp+8]
	add	r12, rax
	mov	r15, rax
	add	r13, rax
	mov	DWORD PTR [r12], 0x00000000
	sub	rcx, r8
	sub	rbx, 1
	je	.L86
	lea	rdi, [r12+4]
	lea	rdx, [0+rbx*4]
	xor	esi, esi
	mov	QWORD PTR [rsp+8], rcx
	mov	QWORD PTR [rsp], r8
	call	memset
	mov	r8, QWORD PTR [rsp]
	mov	rcx, QWORD PTR [rsp+8]
.L86:
	test	rcx, rcx
	jg	.L109
	test	r8, r8
	jne	.L110
.L88:
	lea	rax, [r15+r14*4]
	mov	QWORD PTR [rbp+0], r15
	mov	QWORD PTR [rbp+8], rax
	mov	QWORD PTR [rbp+16], r13
	add	rsp, 24
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	pop	rbx
	.cfi_def_cfa_offset 48
	pop	rbp
	.cfi_def_cfa_offset 40
	pop	r12
	.cfi_def_cfa_offset 32
	pop	r13
	.cfi_def_cfa_offset 24
	pop	r14
	.cfi_def_cfa_offset 16
	pop	r15
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L105:
	.cfi_restore_state
	mov	DWORD PTR [rdx], 0x00000000
	lea	rcx, [rdx+4]
	sub	rbx, 1
	je	.L79
	lea	rax, [rcx+rbx*4]
	mov	rdi, rcx
	xor	esi, esi
	sub	rax, rdx
	lea	rbx, [rax-4]
	mov	rdx, rbx
	call	memset
	mov	rcx, rax
	add	rcx, rbx
.L79:
	mov	QWORD PTR [rbp+8], rcx
	add	rsp, 24
	.cfi_def_cfa_offset 56
	pop	rbx
	.cfi_def_cfa_offset 48
	pop	rbp
	.cfi_def_cfa_offset 40
	pop	r12
	.cfi_def_cfa_offset 32
	pop	r13
	.cfi_def_cfa_offset 24
	pop	r14
	.cfi_def_cfa_offset 16
	pop	r15
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L102:
	.cfi_restore 3
	.cfi_restore 6
	.cfi_restore 12
	.cfi_restore 13
	.cfi_restore 14
	.cfi_restore 15
	ret
	.p2align 4,,10
	.p2align 3
.L107:
	.cfi_def_cfa_offset 80
	.cfi_offset 3, -56
	.cfi_offset 6, -48
	.cfi_offset 12, -40
	.cfi_offset 13, -32
	.cfi_offset 14, -24
	.cfi_offset 15, -16
	movabs	r13, 2305843009213693951
	cmp	r14, r13
	cmovbe	r13, r14
	sal	r13, 2
	jmp	.L82
	.p2align 4,,10
	.p2align 3
.L109:
	mov	rsi, r8
	mov	rdx, rcx
	mov	rdi, r15
	mov	QWORD PTR [rsp], r8
	call	memmove
	mov	rsi, QWORD PTR [rbp+16]
	mov	r8, QWORD PTR [rsp]
	sub	rsi, r8
.L87:
	mov	rdi, r8
	call	_ZdlPvm
	jmp	.L88
	.p2align 4,,10
	.p2align 3
.L110:
	mov	rsi, QWORD PTR [rbp+16]
	sub	rsi, r8
	jmp	.L87
.L106:
	mov	edi, OFFSET FLAT:.LC8
	call	_ZSt20__throw_length_errorPKc
.L108:
	movabs	rdx, 2305843009213693951
	cmp	rax, rdx
	cmova	rax, rdx
	lea	r13, [0+rax*4]
	jmp	.L82
	.cfi_endproc
.LFE4736:
	.size	_ZNSt6vectorIfSaIfEE17_M_default_appendEm, .-_ZNSt6vectorIfSaIfEE17_M_default_appendEm
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC9:
	.string	"cannot create std::vector larger than max_size()"
	.section	.text.unlikely,"ax",@progbits
	.align 2
.LCOLDB10:
	.text
.LHOTB10:
	.align 2
	.p2align 4
	.globl	_ZN18DenseNeuralNetworkC2ESt6vectorIiSaIiEE
	.type	_ZN18DenseNeuralNetworkC2ESt6vectorIiSaIiEE, @function
_ZN18DenseNeuralNetworkC2ESt6vectorIiSaIiEE:
.LFB4156:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA4156
	movabs	rdx, 384307168202282325
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	push	r15
	push	r14
	push	r13
	push	r12
	.cfi_offset 15, -24
	.cfi_offset 14, -32
	.cfi_offset 13, -40
	.cfi_offset 12, -48
	mov	r12, rdi
	push	rbx
	sub	rsp, 24
	.cfi_offset 3, -56
	mov	rax, QWORD PTR [rsi+8]
	mov	QWORD PTR [rdi], OFFSET FLAT:_ZTV18DenseNeuralNetwork+16
	mov	QWORD PTR [rdi+8], 0
	mov	rbx, rax
	sub	rbx, QWORD PTR [rsi]
	mov	QWORD PTR [rdi+16], 0
	sar	rbx, 2
	mov	QWORD PTR [rdi+24], 0
	lea	r13, [rbx-1]
	mov	QWORD PTR [rdi+32], 0
	mov	QWORD PTR [rdi+40], 0
	mov	QWORD PTR [rdi+48], 0
	mov	QWORD PTR [rdi+56], 0
	mov	QWORD PTR [rdi+64], 0
	mov	QWORD PTR [rdi+72], 0
	mov	QWORD PTR [rdi+80], 0
	mov	QWORD PTR [rdi+88], 0
	mov	QWORD PTR [rdi+96], 0
	mov	QWORD PTR [rdi+104], 0
	mov	QWORD PTR [rdi+112], 0
	mov	QWORD PTR [rdi+120], 0
	cmp	rdx, r13
	jb	.L216
	mov	r14, rsi
	test	r13, r13
	je	.L113
	lea	r15, [r13+0+r13*2]
	sal	r15, 3
	mov	rdi, r15
.LEHB0:
	call	_Znwm
	mov	rdx, rax
	lea	rsi, [rax+r15]
	lea	rax, [rbx-2]
	cmp	rax, 2
	jbe	.L159
	mov	rcx, r13
	mov	rax, rdx
	vpxor	xmm0, xmm0, xmm0
	shr	rcx, 2
	lea	rcx, [rcx+rcx*2]
	sal	rcx, 5
	add	rcx, rdx
	.p2align 4,,10
	.p2align 3
.L115:
	vmovdqu	YMMWORD PTR [rax], ymm0
	add	rax, 96
	vmovdqu	YMMWORD PTR [rax-64], ymm0
	vmovdqu	YMMWORD PTR [rax-32], ymm0
	cmp	rax, rcx
	jne	.L115
	mov	rcx, r13
	mov	rdi, r13
	and	rcx, -4
	lea	rax, [rcx+rcx*2]
	sub	rdi, rcx
	and	r13d, 3
	lea	rax, [rdx+rax*8]
	je	.L217
	vzeroupper
.L114:
	vpxor	xmm0, xmm0, xmm0
	mov	QWORD PTR [rax+16], 0
	vmovdqu	XMMWORD PTR [rax], xmm0
	cmp	rdi, 1
	je	.L116
	mov	QWORD PTR [rax+40], 0
	vmovdqu	XMMWORD PTR [rax+24], xmm0
	cmp	rdi, 2
	je	.L116
	mov	QWORD PTR [rax+64], 0
	vmovdqu	XMMWORD PTR [rax+48], xmm0
.L116:
	mov	rax, QWORD PTR [r12+24]
	mov	r13, QWORD PTR [r12+8]
	lea	rcx, [rbx+rbx*2]
	mov	QWORD PTR [r12+8], rdx
	mov	r15, QWORD PTR [r12+16]
	lea	rdx, [rdx-24+rcx*8]
	mov	QWORD PTR [r12+24], rsi
	mov	QWORD PTR [rsp+8], rax
	mov	QWORD PTR [r12+16], rdx
	cmp	r13, r15
	je	.L117
	mov	rbx, r13
	.p2align 4,,10
	.p2align 3
.L121:
	mov	rdi, QWORD PTR [rbx]
	test	rdi, rdi
	je	.L118
	mov	rsi, QWORD PTR [rbx+16]
	add	rbx, 24
	sub	rsi, rdi
	call	_ZdlPvm
	cmp	r15, rbx
	jne	.L121
.L120:
	mov	r15, r13
.L117:
	test	r15, r15
	je	.L215
	mov	rsi, QWORD PTR [rsp+8]
	mov	rdi, r15
	sub	rsi, r13
	call	_ZdlPvm
.L215:
	mov	rax, QWORD PTR [r14+8]
.L113:
	sub	rax, QWORD PTR [r14]
	mov	rbx, rax
	movabs	rax, 384307168202282325
	sar	rbx, 2
	lea	r13, [rbx-1]
	cmp	rax, r13
	jb	.L218
	test	r13, r13
	je	.L160
	lea	r15, [r13+0+r13*2]
	sal	r15, 3
	mov	rdi, r15
	call	_Znwm
	mov	rdx, rax
	lea	rsi, [rax+r15]
	lea	rax, [rbx-2]
	cmp	rax, 2
	jbe	.L161
	mov	rcx, r13
	mov	rax, rdx
	vpxor	xmm0, xmm0, xmm0
	shr	rcx, 2
	lea	rcx, [rcx+rcx*2]
	sal	rcx, 5
	add	rcx, rdx
	.p2align 4,,10
	.p2align 3
.L125:
	vmovdqu	YMMWORD PTR [rax], ymm0
	add	rax, 96
	vmovdqu	YMMWORD PTR [rax-64], ymm0
	vmovdqu	YMMWORD PTR [rax-32], ymm0
	cmp	rax, rcx
	jne	.L125
	mov	rcx, r13
	mov	rdi, r13
	and	rcx, -4
	lea	rax, [rcx+rcx*2]
	sub	rdi, rcx
	and	r13d, 3
	lea	rax, [rdx+rax*8]
	je	.L219
	vzeroupper
.L124:
	vpxor	xmm0, xmm0, xmm0
	mov	QWORD PTR [rax+16], 0
	vmovdqu	XMMWORD PTR [rax], xmm0
	cmp	rdi, 1
	je	.L127
	mov	QWORD PTR [rax+40], 0
	vmovdqu	XMMWORD PTR [rax+24], xmm0
	cmp	rdi, 2
	je	.L127
	mov	QWORD PTR [rax+64], 0
	vmovdqu	XMMWORD PTR [rax+48], xmm0
.L127:
	lea	rax, [rbx+rbx*2]
	lea	rcx, [rdx-24+rax*8]
.L123:
	mov	r13, QWORD PTR [r12+80]
	mov	rax, QWORD PTR [r12+96]
	mov	QWORD PTR [r12+80], rdx
	mov	r15, QWORD PTR [r12+88]
	mov	QWORD PTR [r12+96], rsi
	mov	QWORD PTR [rsp+8], rax
	mov	rbx, r13
	mov	QWORD PTR [r12+88], rcx
	cmp	r13, r15
	je	.L133
	.p2align 4,,10
	.p2align 3
.L128:
	mov	rdi, QWORD PTR [rbx]
	test	rdi, rdi
	je	.L131
	mov	rsi, QWORD PTR [rbx+16]
	add	rbx, 24
	sub	rsi, rdi
	call	_ZdlPvm
	cmp	r15, rbx
	jne	.L128
.L133:
	test	r13, r13
	je	.L130
	mov	rsi, QWORD PTR [rsp+8]
	mov	rdi, r13
	sub	rsi, r13
	call	_ZdlPvm
.L130:
	movabs	rax, 384307168202282325
	mov	rbx, QWORD PTR [r14+8]
	sub	rbx, QWORD PTR [r14]
	sar	rbx, 2
	lea	r13, [rbx-1]
	cmp	rax, r13
	jb	.L220
	test	r13, r13
	je	.L163
	lea	r15, [r13+0+r13*2]
	sal	r15, 3
	mov	rdi, r15
	call	_Znwm
	mov	rdx, rax
	lea	rsi, [rax+r15]
	lea	rax, [rbx-2]
	cmp	rax, 2
	jbe	.L164
	mov	rcx, r13
	mov	rax, rdx
	vpxor	xmm0, xmm0, xmm0
	shr	rcx, 2
	lea	rcx, [rcx+rcx*2]
	sal	rcx, 5
	add	rcx, rdx
	.p2align 4,,10
	.p2align 3
.L137:
	vmovdqu	YMMWORD PTR [rax], ymm0
	add	rax, 96
	vmovdqu	YMMWORD PTR [rax-64], ymm0
	vmovdqu	YMMWORD PTR [rax-32], ymm0
	cmp	rax, rcx
	jne	.L137
	mov	rcx, r13
	mov	rdi, r13
	and	rcx, -4
	lea	rax, [rcx+rcx*2]
	sub	rdi, rcx
	and	r13d, 3
	lea	rax, [rdx+rax*8]
	je	.L221
	vzeroupper
.L136:
	vpxor	xmm0, xmm0, xmm0
	mov	QWORD PTR [rax+16], 0
	vmovdqu	XMMWORD PTR [rax], xmm0
	cmp	rdi, 1
	je	.L139
	mov	QWORD PTR [rax+40], 0
	vmovdqu	XMMWORD PTR [rax+24], xmm0
	cmp	rdi, 2
	je	.L139
	mov	QWORD PTR [rax+64], 0
	vmovdqu	XMMWORD PTR [rax+48], xmm0
.L139:
	lea	rax, [rbx+rbx*2]
	lea	rcx, [rdx-24+rax*8]
.L135:
	mov	r13, QWORD PTR [r12+32]
	mov	rax, QWORD PTR [r12+48]
	mov	QWORD PTR [r12+32], rdx
	mov	r15, QWORD PTR [r12+40]
	mov	QWORD PTR [r12+48], rsi
	mov	QWORD PTR [rsp+8], rax
	mov	rbx, r13
	mov	QWORD PTR [r12+40], rcx
	cmp	r13, r15
	je	.L145
	.p2align 4,,10
	.p2align 3
.L140:
	mov	rdi, QWORD PTR [rbx]
	test	rdi, rdi
	je	.L143
	mov	rsi, QWORD PTR [rbx+16]
	add	rbx, 24
	sub	rsi, rdi
	call	_ZdlPvm
	cmp	r15, rbx
	jne	.L140
.L145:
	test	r13, r13
	je	.L142
	mov	rsi, QWORD PTR [rsp+8]
	mov	rdi, r13
	sub	rsi, r13
	call	_ZdlPvm
.L142:
	mov	rdx, QWORD PTR [r14]
	mov	rax, QWORD PTR [r14+8]
	xor	r13d, r13d
	sub	rax, rdx
	cmp	rax, 4
	jne	.L146
	jmp	.L213
	.p2align 4,,10
	.p2align 3
.L147:
	cmp	rsi, rax
	jnb	.L148
	lea	rax, [r8+rsi*4]
	cmp	rcx, rax
	je	.L148
	mov	QWORD PTR [rdi+8], rax
.L148:
	mov	rdi, QWORD PTR [r12+8]
	movsx	rax, DWORD PTR [rdx+4+r15]
	add	rdi, rbx
	mov	rsi, QWORD PTR [rdi+8]
	mov	r8, QWORD PTR [rdi]
	mov	rcx, rsi
	sub	rcx, r8
	sar	rcx, 2
	cmp	rcx, rax
	jb	.L222
	cmp	rax, rcx
	jnb	.L150
	lea	rcx, [r8+rax*4]
	cmp	rsi, rcx
	je	.L150
	mov	QWORD PTR [rdi+8], rcx
.L150:
	add	rbx, QWORD PTR [r12+32]
	mov	rsi, QWORD PTR [rbx+8]
	mov	rdi, QWORD PTR [rbx]
	mov	rcx, rsi
	sub	rcx, rdi
	sar	rcx, 2
	cmp	rcx, rax
	jb	.L223
	cmp	rax, rcx
	jnb	.L154
	lea	rax, [rdi+rax*4]
	cmp	rsi, rax
	je	.L154
	mov	QWORD PTR [rbx+8], rax
.L154:
	mov	rax, QWORD PTR [r14+8]
	sub	rax, rdx
	sar	rax, 2
	sub	rax, 1
	cmp	r13, rax
	jnb	.L213
.L146:
	lea	rbx, [r13+0+r13*2]
	mov	rdi, QWORD PTR [r12+80]
	lea	r15, [0+r13*4]
	add	r13, 1
	sal	rbx, 3
	mov	esi, DWORD PTR [rdx+r15]
	imul	esi, DWORD PTR [rdx+4+r15]
	add	rdi, rbx
	mov	rcx, QWORD PTR [rdi+8]
	mov	r8, QWORD PTR [rdi]
	movsx	rsi, esi
	mov	rax, rcx
	sub	rax, r8
	sar	rax, 2
	cmp	rax, rsi
	jnb	.L147
	sub	rsi, rax
	call	_ZNSt6vectorIfSaIfEE17_M_default_appendEm
	mov	rdx, QWORD PTR [r14]
	jmp	.L148
	.p2align 4,,10
	.p2align 3
.L118:
	add	rbx, 24
	cmp	r15, rbx
	jne	.L121
	jmp	.L120
	.p2align 4,,10
	.p2align 3
.L131:
	add	rbx, 24
	cmp	r15, rbx
	jne	.L128
	jmp	.L133
	.p2align 4,,10
	.p2align 3
.L143:
	add	rbx, 24
	cmp	r15, rbx
	jne	.L140
	jmp	.L145
	.p2align 4,,10
	.p2align 3
.L223:
	sub	rax, rcx
	mov	rdi, rbx
	mov	rsi, rax
	call	_ZNSt6vectorIfSaIfEE17_M_default_appendEm
	mov	rdx, QWORD PTR [r14]
	jmp	.L154
	.p2align 4,,10
	.p2align 3
.L222:
	sub	rax, rcx
	mov	rsi, rax
	call	_ZNSt6vectorIfSaIfEE17_M_default_appendEm
	mov	rdx, QWORD PTR [r14]
	movsx	rax, DWORD PTR [rdx+4+r15]
	jmp	.L150
	.p2align 4,,10
	.p2align 3
.L213:
	add	rsp, 24
	pop	rbx
	pop	r12
	pop	r13
	pop	r14
	pop	r15
	pop	rbp
	.cfi_remember_state
	.cfi_def_cfa 7, 8
	ret
	.p2align 4,,10
	.p2align 3
.L160:
	.cfi_restore_state
	xor	esi, esi
	xor	edx, edx
	xor	ecx, ecx
	jmp	.L123
	.p2align 4,,10
	.p2align 3
.L163:
	xor	esi, esi
	xor	edx, edx
	xor	ecx, ecx
	jmp	.L135
	.p2align 4,,10
	.p2align 3
.L217:
	vzeroupper
	jmp	.L116
	.p2align 4,,10
	.p2align 3
.L219:
	vzeroupper
	jmp	.L127
	.p2align 4,,10
	.p2align 3
.L221:
	vzeroupper
	jmp	.L139
.L159:
	mov	rdi, r13
	mov	rax, rdx
	jmp	.L114
.L161:
	mov	rdi, r13
	mov	rax, rdx
	jmp	.L124
.L164:
	mov	rdi, r13
	mov	rax, rdx
	jmp	.L136
.L216:
	mov	edi, OFFSET FLAT:.LC9
	call	_ZSt20__throw_length_errorPKc
.L220:
	mov	edi, OFFSET FLAT:.LC9
	call	_ZSt20__throw_length_errorPKc
.L218:
	mov	edi, OFFSET FLAT:.LC9
	call	_ZSt20__throw_length_errorPKc
.LEHE0:
.L167:
	mov	rbx, rax
	jmp	.L158
	.globl	__gxx_personality_v0
	.section	.gcc_except_table,"a",@progbits
.LLSDA4156:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE4156-.LLSDACSB4156
.LLSDACSB4156:
	.uleb128 .LEHB0-.LFB4156
	.uleb128 .LEHE0-.LEHB0
	.uleb128 .L167-.LFB4156
	.uleb128 0
.LLSDACSE4156:
	.text
	.cfi_endproc
	.section	.text.unlikely
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDAC4156
	.type	_ZN18DenseNeuralNetworkC2ESt6vectorIiSaIiEE.cold, @function
_ZN18DenseNeuralNetworkC2ESt6vectorIiSaIiEE.cold:
.LFSB4156:
.L158:
	.cfi_def_cfa 6, 16
	.cfi_offset 3, -56
	.cfi_offset 6, -16
	.cfi_offset 12, -48
	.cfi_offset 13, -40
	.cfi_offset 14, -32
	.cfi_offset 15, -24
	lea	rdi, [r12+104]
	vzeroupper
	call	_ZNSt6vectorIS_IfSaIfEESaIS1_EED1Ev
	lea	rdi, [r12+80]
	call	_ZNSt6vectorIS_IfSaIfEESaIS1_EED1Ev
	lea	rdi, [r12+56]
	call	_ZNSt6vectorIS_IfSaIfEESaIS1_EED1Ev
	lea	rdi, [r12+32]
	call	_ZNSt6vectorIS_IfSaIfEESaIS1_EED1Ev
	lea	rdi, [r12+8]
	call	_ZNSt6vectorIS_IfSaIfEESaIS1_EED1Ev
	mov	rdi, rbx
.LEHB1:
	call	_Unwind_Resume
.LEHE1:
	.cfi_endproc
.LFE4156:
	.section	.gcc_except_table
.LLSDAC4156:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSEC4156-.LLSDACSBC4156
.LLSDACSBC4156:
	.uleb128 .LEHB1-.LCOLDB10
	.uleb128 .LEHE1-.LEHB1
	.uleb128 0
	.uleb128 0
.LLSDACSEC4156:
	.section	.text.unlikely
	.text
	.size	_ZN18DenseNeuralNetworkC2ESt6vectorIiSaIiEE, .-_ZN18DenseNeuralNetworkC2ESt6vectorIiSaIiEE
	.section	.text.unlikely
	.size	_ZN18DenseNeuralNetworkC2ESt6vectorIiSaIiEE.cold, .-_ZN18DenseNeuralNetworkC2ESt6vectorIiSaIiEE.cold
.LCOLDE10:
	.text
.LHOTE10:
	.globl	_ZN18DenseNeuralNetworkC1ESt6vectorIiSaIiEE
	.set	_ZN18DenseNeuralNetworkC1ESt6vectorIiSaIiEE,_ZN18DenseNeuralNetworkC2ESt6vectorIiSaIiEE
	.section	.text._ZNSt23mersenne_twister_engineImLm32ELm624ELm397ELm31ELm2567483615ELm11ELm4294967295ELm7ELm2636928640ELm15ELm4022730752ELm18ELm1812433253EE11_M_gen_randEv,"axG",@progbits,_ZNSt23mersenne_twister_engineImLm32ELm624ELm397ELm31ELm2567483615ELm11ELm4294967295ELm7ELm2636928640ELm15ELm4022730752ELm18ELm1812433253EE11_M_gen_randEv,comdat
	.align 2
	.p2align 4
	.weak	_ZNSt23mersenne_twister_engineImLm32ELm624ELm397ELm31ELm2567483615ELm11ELm4294967295ELm7ELm2636928640ELm15ELm4022730752ELm18ELm1812433253EE11_M_gen_randEv
	.type	_ZNSt23mersenne_twister_engineImLm32ELm624ELm397ELm31ELm2567483615ELm11ELm4294967295ELm7ELm2636928640ELm15ELm4022730752ELm18ELm1812433253EE11_M_gen_randEv, @function
_ZNSt23mersenne_twister_engineImLm32ELm624ELm397ELm31ELm2567483615ELm11ELm4294967295ELm7ELm2636928640ELm15ELm4022730752ELm18ELm1812433253EE11_M_gen_randEv:
.LFB5062:
	.cfi_startproc
	mov	rax, rdi
	mov	rdx, rdi
	vpxor	xmm6, xmm6, xmm6
	mov	esi, 2567483615
	lea	rcx, [rdi+1792]
	mov	rdi, -2147483648
	vmovq	xmm5, rsi
	vmovq	xmm0, rdi
	mov	edi, 2147483647
	vpbroadcastq	ymm5, xmm5
	vmovq	xmm1, rdi
	mov	edi, 1
	vpbroadcastq	ymm9, xmm0
	vmovq	xmm3, rdi
	vpbroadcastq	ymm8, xmm1
	vpbroadcastq	ymm7, xmm3
	.p2align 4,,10
	.p2align 3
.L225:
	vpand	ymm4, ymm8, YMMWORD PTR [rdx+8]
	vpand	ymm2, ymm9, YMMWORD PTR [rdx]
	add	rdx, 32
	vpor	ymm2, ymm2, ymm4
	vpsrlq	ymm4, ymm2, 1
	vpand	ymm2, ymm2, ymm7
	vpxor	ymm4, ymm4, YMMWORD PTR [rdx+3144]
	vpcmpeqq	ymm2, ymm2, ymm6
	vpxor	ymm10, ymm4, ymm5
	vpblendvb	ymm2, ymm10, ymm4, ymm2
	vmovdqu	YMMWORD PTR [rdx-32], ymm2
	cmp	rcx, rdx
	jne	.L225
	mov	rcx, QWORD PTR [rax+1808]
	vpunpcklqdq	xmm0, xmm0, xmm0
	vpunpcklqdq	xmm1, xmm1, xmm1
	vpxor	xmm6, xmm6, xmm6
	vpand	xmm1, xmm1, XMMWORD PTR [rax+1800]
	vpand	xmm0, xmm0, XMMWORD PTR [rax+1792]
	vmovq	xmm7, rsi
	mov	rdx, QWORD PTR [rax+1816]
	and	rcx, -2147483648
	vpor	xmm0, xmm0, xmm1
	vpunpcklqdq	xmm1, xmm3, xmm3
	vpxor	xmm3, xmm3, xmm3
	and	edx, 2147483647
	vpsrlq	xmm2, xmm0, 1
	vpand	xmm0, xmm0, xmm1
	or	rcx, rdx
	vpxor	xmm2, xmm2, XMMWORD PTR [rax+4968]
	vpunpcklqdq	xmm1, xmm7, xmm7
	mov	rdx, rcx
	vpcmpeqq	xmm0, xmm0, xmm3
	shr	rdx
	xor	rdx, QWORD PTR [rax+4984]
	vpxor	xmm1, xmm2, xmm1
	xor	rsi, rdx
	and	ecx, 1
	mov	ecx, 2567483615
	vpblendvb	xmm0, xmm1, xmm2, xmm0
	cmovne	rdx, rsi
	vmovq	xmm5, rcx
	vpbroadcastq	ymm2, QWORD PTR .LC19[rip]
	vmovdqu	XMMWORD PTR [rax+1792], xmm0
	lea	rsi, [rax+4984]
	vpbroadcastq	ymm5, xmm5
	vpbroadcastq	ymm1, QWORD PTR .LC20[rip]
	vpbroadcastq	ymm0, QWORD PTR .LC21[rip]
	mov	QWORD PTR [rax+1808], rdx
	lea	rdx, [rax+1816]
.L227:
	vpand	ymm4, ymm1, YMMWORD PTR [rdx+8]
	vpand	ymm3, ymm2, YMMWORD PTR [rdx]
	add	rdx, 32
	vpor	ymm3, ymm3, ymm4
	vpsrlq	ymm4, ymm3, 1
	vpand	ymm3, ymm3, ymm0
	vpxor	ymm4, ymm4, YMMWORD PTR [rdx-1848]
	vpcmpeqq	ymm3, ymm3, ymm6
	vpxor	ymm7, ymm4, ymm5
	vpblendvb	ymm3, ymm7, ymm4, ymm3
	vmovdqu	YMMWORD PTR [rdx-32], ymm3
	cmp	rsi, rdx
	jne	.L227
	mov	rsi, QWORD PTR [rax+4984]
	mov	rdx, QWORD PTR [rax]
	mov	QWORD PTR [rax+4992], 0
	and	edx, 2147483647
	and	rsi, -2147483648
	or	rsi, rdx
	mov	rdx, rsi
	shr	rdx
	xor	rdx, QWORD PTR [rax+3168]
	xor	rcx, rdx
	and	esi, 1
	cmovne	rdx, rcx
	mov	QWORD PTR [rax+4984], rdx
	vzeroupper
	ret
	.cfi_endproc
.LFE5062:
	.size	_ZNSt23mersenne_twister_engineImLm32ELm624ELm397ELm31ELm2567483615ELm11ELm4294967295ELm7ELm2636928640ELm15ELm4022730752ELm18ELm1812433253EE11_M_gen_randEv, .-_ZNSt23mersenne_twister_engineImLm32ELm624ELm397ELm31ELm2567483615ELm11ELm4294967295ELm7ELm2636928640ELm15ELm4022730752ELm18ELm1812433253EE11_M_gen_randEv
	.text
	.align 2
	.p2align 4
	.globl	_ZN18DenseNeuralNetwork20initializeParametersEff
	.type	_ZN18DenseNeuralNetwork20initializeParametersEff, @function
_ZN18DenseNeuralNetwork20initializeParametersEff:
.LFB4159:
	.cfi_startproc
	push	r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	mov	ecx, 5489
	mov	edx, 1
	push	r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	push	r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	push	r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	push	rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	push	rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	sub	rsp, 5096
	.cfi_def_cfa_offset 5152
	mov	QWORD PTR [rsp+64], rdi
	mov	QWORD PTR [rsp+80], 5489
	.p2align 4,,10
	.p2align 3
.L235:
	mov	rax, rcx
	shr	rax, 30
	xor	rax, rcx
	imul	rax, rax, 1812433253
	lea	ecx, [rax+rdx]
	mov	QWORD PTR [rsp+80+rdx*8], rcx
	add	rdx, 1
	cmp	rdx, 624
	jne	.L235
	mov	rdi, QWORD PTR [rsp+64]
	vcvtss2sd	xmm6, xmm1, xmm1
	vcvtss2sd	xmm5, xmm0, xmm0
	movabs	rdx, -6148914691236517205
	mov	QWORD PTR [rsp+5072], 624
	vxorps	xmm2, xmm2, xmm2
	mov	rax, QWORD PTR [rdi+88]
	mov	rbp, QWORD PTR [rdi+80]
	vmovsd	QWORD PTR [rsp+72], xmm6
	vmovsd	QWORD PTR [rsp+32], xmm5
	mov	r13, rax
	sub	r13, rbp
	sar	r13, 3
	imul	r13, rdx
	cmp	rax, rbp
	je	.L236
	vsubsd	xmm7, xmm6, xmm5
	vmulsd	xmm0, xmm7, QWORD PTR .LC22[rip]
	xor	r12d, r12d
	vmovsd	QWORD PTR [rsp+40], xmm7
	vaddsd	xmm5, xmm0, xmm5
	vmovsd	QWORD PTR [rsp+56], xmm5
	.p2align 4,,10
	.p2align 3
.L237:
	mov	rax, QWORD PTR [rbp+8]
	mov	r14, QWORD PTR [rbp+0]
	mov	rbx, rax
	sub	rbx, r14
	sar	rbx, 2
	cmp	r14, rax
	je	.L238
	vmovsd	xmm4, QWORD PTR .LC23[rip]
	vmovsd	xmm5, QWORD PTR .LC24[rip]
	xor	r15d, r15d
	vmovsd	xmm6, QWORD PTR .LC25[rip]
	mov	rcx, QWORD PTR [rsp+5072]
	vmovsd	QWORD PTR [rsp+8], xmm4
	vmovsd	QWORD PTR [rsp+16], xmm5
	vmovsd	QWORD PTR [rsp+24], xmm6
	jmp	.L247
	.p2align 4,,10
	.p2align 3
.L239:
	mov	rax, QWORD PTR [rsp+80+rcx*8]
	lea	rsi, [rcx+1]
	mov	QWORD PTR [rsp+5072], rsi
	mov	rcx, rax
	shr	rcx, 11
	mov	ecx, ecx
	xor	rax, rcx
	mov	rcx, rax
	sal	rcx, 7
	and	ecx, 2636928640
	xor	rax, rcx
	mov	rcx, rax
	sal	rcx, 15
	and	ecx, 4022730752
	xor	rax, rcx
	mov	rcx, rax
	shr	rcx, 18
	xor	rax, rcx
	vcvtsi2sd	xmm1, xmm2, rax
	jns	.L241
	mov	rcx, rax
	and	eax, 1
	shr	rcx
	or	rcx, rax
	vcvtsi2sd	xmm1, xmm2, rcx
	vaddsd	xmm1, xmm1, xmm1
.L241:
	cmp	rsi, 623
	ja	.L263
.L242:
	mov	rax, QWORD PTR [rsp+80+rsi*8]
	lea	rcx, [rsi+1]
	mov	QWORD PTR [rsp+5072], rcx
	mov	rsi, rax
	shr	rsi, 11
	mov	esi, esi
	xor	rax, rsi
	mov	rsi, rax
	sal	rsi, 7
	and	esi, 2636928640
	xor	rax, rsi
	mov	rsi, rax
	sal	rsi, 15
	and	esi, 4022730752
	xor	rax, rsi
	mov	rsi, rax
	shr	rsi, 18
	xor	rax, rsi
	vcvtsi2sd	xmm0, xmm2, rax
	jns	.L244
	mov	rsi, rax
	and	eax, 1
	shr	rsi
	or	rsi, rax
	vcvtsi2sd	xmm0, xmm2, rsi
	vaddsd	xmm0, xmm0, xmm0
.L244:
	vmulsd	xmm0, xmm0, QWORD PTR [rsp+8]
	vaddsd	xmm0, xmm0, xmm1
	vcomisd	xmm0, QWORD PTR [rsp+24]
	vmulsd	xmm1, xmm0, QWORD PTR [rsp+16]
	jnb	.L245
	vmulsd	xmm1, xmm1, QWORD PTR [rsp+40]
	vaddsd	xmm1, xmm1, QWORD PTR [rsp+32]
	vcvtsd2ss	xmm1, xmm1, xmm1
	vmovss	DWORD PTR [r14+r15*4], xmm1
	add	r15, 1
	cmp	r15, rbx
	jnb	.L238
.L247:
	cmp	rcx, 623
	jbe	.L239
	lea	rdi, [rsp+80]
	call	_ZNSt23mersenne_twister_engineImLm32ELm624ELm397ELm31ELm2567483615ELm11ELm4294967295ELm7ELm2636928640ELm15ELm4022730752ELm18ELm1812433253EE11_M_gen_randEv
	mov	rcx, QWORD PTR [rsp+5072]
	vxorps	xmm2, xmm2, xmm2
	jmp	.L239
	.p2align 4,,10
	.p2align 3
.L263:
	lea	rdi, [rsp+80]
	vmovsd	QWORD PTR [rsp+48], xmm1
	call	_ZNSt23mersenne_twister_engineImLm32ELm624ELm397ELm31ELm2567483615ELm11ELm4294967295ELm7ELm2636928640ELm15ELm4022730752ELm18ELm1812433253EE11_M_gen_randEv
	vmovsd	xmm1, QWORD PTR [rsp+48]
	vxorps	xmm2, xmm2, xmm2
	mov	rsi, QWORD PTR [rsp+5072]
	jmp	.L242
	.p2align 4,,10
	.p2align 3
.L245:
	vcvtsd2ss	xmm0, xmm0, QWORD PTR [rsp+56]
	vmovss	DWORD PTR [r14+r15*4], xmm0
	add	r15, 1
	cmp	r15, rbx
	jb	.L247
	.p2align 4,,10
	.p2align 3
.L238:
	add	r12, 1
	add	rbp, 24
	cmp	r12, r13
	jb	.L237
.L236:
	movabs	rdx, -6148914691236517205
	mov	rdi, QWORD PTR [rsp+64]
	mov	rax, QWORD PTR [rdi+40]
	mov	rbp, QWORD PTR [rdi+32]
	mov	r13, rax
	sub	r13, rbp
	sar	r13, 3
	imul	r13, rdx
	cmp	rbp, rax
	je	.L261
	vmovsd	xmm6, QWORD PTR [rsp+32]
	vmovsd	xmm7, QWORD PTR [rsp+72]
	xor	r12d, r12d
	vsubsd	xmm7, xmm7, xmm6
	vmulsd	xmm0, xmm7, QWORD PTR .LC22[rip]
	vmovsd	QWORD PTR [rsp+40], xmm7
	vaddsd	xmm5, xmm0, xmm6
	vmovsd	QWORD PTR [rsp+56], xmm5
	.p2align 4,,10
	.p2align 3
.L249:
	mov	rax, QWORD PTR [rbp+8]
	mov	r14, QWORD PTR [rbp+0]
	mov	rbx, rax
	sub	rbx, r14
	sar	rbx, 2
	cmp	rax, r14
	je	.L250
	vmovsd	xmm7, QWORD PTR .LC23[rip]
	vmovsd	xmm3, QWORD PTR .LC24[rip]
	xor	r15d, r15d
	vmovsd	xmm4, QWORD PTR .LC25[rip]
	mov	rsi, QWORD PTR [rsp+5072]
	vmovsd	QWORD PTR [rsp+8], xmm7
	vmovsd	QWORD PTR [rsp+16], xmm3
	vmovsd	QWORD PTR [rsp+24], xmm4
	jmp	.L259
	.p2align 4,,10
	.p2align 3
.L251:
	lea	rcx, [rsi+1]
	mov	rsi, QWORD PTR [rsp+80+rsi*8]
	mov	QWORD PTR [rsp+5072], rcx
	mov	rax, rsi
	shr	rax, 11
	mov	eax, eax
	xor	rax, rsi
	mov	rsi, rax
	sal	rsi, 7
	and	esi, 2636928640
	xor	rax, rsi
	mov	rsi, rax
	sal	rsi, 15
	and	esi, 4022730752
	xor	rax, rsi
	mov	rsi, rax
	shr	rsi, 18
	xor	rax, rsi
	vcvtsi2sd	xmm1, xmm2, rax
	jns	.L253
	mov	rsi, rax
	and	eax, 1
	shr	rsi
	or	rsi, rax
	vcvtsi2sd	xmm1, xmm2, rsi
	vaddsd	xmm1, xmm1, xmm1
.L253:
	cmp	rcx, 623
	ja	.L264
.L254:
	mov	rax, QWORD PTR [rsp+80+rcx*8]
	lea	rsi, [rcx+1]
	mov	QWORD PTR [rsp+5072], rsi
	mov	rcx, rax
	shr	rcx, 11
	mov	ecx, ecx
	xor	rax, rcx
	mov	rcx, rax
	sal	rcx, 7
	and	ecx, 2636928640
	xor	rax, rcx
	mov	rcx, rax
	sal	rcx, 15
	and	ecx, 4022730752
	xor	rax, rcx
	mov	rcx, rax
	shr	rcx, 18
	xor	rax, rcx
	vcvtsi2sd	xmm0, xmm2, rax
	jns	.L256
	mov	rcx, rax
	and	eax, 1
	shr	rcx
	or	rcx, rax
	vcvtsi2sd	xmm0, xmm2, rcx
	vaddsd	xmm0, xmm0, xmm0
.L256:
	vmulsd	xmm0, xmm0, QWORD PTR [rsp+8]
	vaddsd	xmm0, xmm0, xmm1
	vcomisd	xmm0, QWORD PTR [rsp+24]
	vmulsd	xmm1, xmm0, QWORD PTR [rsp+16]
	jnb	.L257
	vmulsd	xmm1, xmm1, QWORD PTR [rsp+40]
	vaddsd	xmm1, xmm1, QWORD PTR [rsp+32]
	vcvtsd2ss	xmm1, xmm1, xmm1
	vmovss	DWORD PTR [r14+r15*4], xmm1
	add	r15, 1
	cmp	r15, rbx
	jnb	.L250
.L259:
	cmp	rsi, 623
	jbe	.L251
	lea	rdi, [rsp+80]
	call	_ZNSt23mersenne_twister_engineImLm32ELm624ELm397ELm31ELm2567483615ELm11ELm4294967295ELm7ELm2636928640ELm15ELm4022730752ELm18ELm1812433253EE11_M_gen_randEv
	mov	rsi, QWORD PTR [rsp+5072]
	vxorps	xmm2, xmm2, xmm2
	jmp	.L251
	.p2align 4,,10
	.p2align 3
.L264:
	lea	rdi, [rsp+80]
	vmovsd	QWORD PTR [rsp+48], xmm1
	call	_ZNSt23mersenne_twister_engineImLm32ELm624ELm397ELm31ELm2567483615ELm11ELm4294967295ELm7ELm2636928640ELm15ELm4022730752ELm18ELm1812433253EE11_M_gen_randEv
	vmovsd	xmm1, QWORD PTR [rsp+48]
	vxorps	xmm2, xmm2, xmm2
	mov	rcx, QWORD PTR [rsp+5072]
	jmp	.L254
	.p2align 4,,10
	.p2align 3
.L257:
	vcvtsd2ss	xmm0, xmm0, QWORD PTR [rsp+56]
	vmovss	DWORD PTR [r14+r15*4], xmm0
	add	r15, 1
	cmp	r15, rbx
	jb	.L259
	.p2align 4,,10
	.p2align 3
.L250:
	add	r12, 1
	add	rbp, 24
	cmp	r12, r13
	jb	.L249
.L261:
	add	rsp, 5096
	.cfi_def_cfa_offset 56
	pop	rbx
	.cfi_def_cfa_offset 48
	pop	rbp
	.cfi_def_cfa_offset 40
	pop	r12
	.cfi_def_cfa_offset 32
	pop	r13
	.cfi_def_cfa_offset 24
	pop	r14
	.cfi_def_cfa_offset 16
	pop	r15
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE4159:
	.size	_ZN18DenseNeuralNetwork20initializeParametersEff, .-_ZN18DenseNeuralNetwork20initializeParametersEff
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.type	_GLOBAL__sub_I__ZN18DenseNeuralNetworkC2ESt6vectorIiSaIiEE, @function
_GLOBAL__sub_I__ZN18DenseNeuralNetworkC2ESt6vectorIiSaIiEE:
.LFB5092:
	.cfi_startproc
	sub	rsp, 8
	.cfi_def_cfa_offset 16
	mov	edi, OFFSET FLAT:_ZStL8__ioinit
	call	_ZNSt8ios_base4InitC1Ev
	mov	edx, OFFSET FLAT:__dso_handle
	mov	esi, OFFSET FLAT:_ZStL8__ioinit
	mov	edi, OFFSET FLAT:_ZNSt8ios_base4InitD1Ev
	add	rsp, 8
	.cfi_def_cfa_offset 8
	jmp	__cxa_atexit
	.cfi_endproc
.LFE5092:
	.size	_GLOBAL__sub_I__ZN18DenseNeuralNetworkC2ESt6vectorIiSaIiEE, .-_GLOBAL__sub_I__ZN18DenseNeuralNetworkC2ESt6vectorIiSaIiEE
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I__ZN18DenseNeuralNetworkC2ESt6vectorIiSaIiEE
	.weak	_ZTS8NNModule
	.section	.rodata._ZTS8NNModule,"aG",@progbits,_ZTS8NNModule,comdat
	.align 8
	.type	_ZTS8NNModule, @object
	.size	_ZTS8NNModule, 10
_ZTS8NNModule:
	.string	"8NNModule"
	.weak	_ZTI8NNModule
	.section	.rodata._ZTI8NNModule,"aG",@progbits,_ZTI8NNModule,comdat
	.align 8
	.type	_ZTI8NNModule, @object
	.size	_ZTI8NNModule, 16
_ZTI8NNModule:
	.quad	_ZTVN10__cxxabiv117__class_type_infoE+16
	.quad	_ZTS8NNModule
	.weak	_ZTS18DenseNeuralNetwork
	.section	.rodata._ZTS18DenseNeuralNetwork,"aG",@progbits,_ZTS18DenseNeuralNetwork,comdat
	.align 16
	.type	_ZTS18DenseNeuralNetwork, @object
	.size	_ZTS18DenseNeuralNetwork, 21
_ZTS18DenseNeuralNetwork:
	.string	"18DenseNeuralNetwork"
	.weak	_ZTI18DenseNeuralNetwork
	.section	.rodata._ZTI18DenseNeuralNetwork,"aG",@progbits,_ZTI18DenseNeuralNetwork,comdat
	.align 8
	.type	_ZTI18DenseNeuralNetwork, @object
	.size	_ZTI18DenseNeuralNetwork, 24
_ZTI18DenseNeuralNetwork:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	_ZTS18DenseNeuralNetwork
	.quad	_ZTI8NNModule
	.weak	_ZTV18DenseNeuralNetwork
	.section	.rodata._ZTV18DenseNeuralNetwork,"aG",@progbits,_ZTV18DenseNeuralNetwork,comdat
	.align 8
	.type	_ZTV18DenseNeuralNetwork, @object
	.size	_ZTV18DenseNeuralNetwork, 64
_ZTV18DenseNeuralNetwork:
	.quad	0
	.quad	_ZTI18DenseNeuralNetwork
	.quad	_ZN18DenseNeuralNetwork10getOutputsEv
	.quad	_ZN18DenseNeuralNetwork20initializeParametersEff
	.quad	_ZN18DenseNeuralNetwork7processEPKSt6vectorIfSaIfEE
	.quad	_ZN18DenseNeuralNetwork5trainEPKSt6vectorIfSaIfEEf
	.quad	_ZN18DenseNeuralNetwork10saveToFileEPSt14basic_ofstreamIcSt11char_traitsIcEE
	.quad	_ZN18DenseNeuralNetwork12readFromFileEPSt14basic_ifstreamIcSt11char_traitsIcEE
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.section	.rodata.cst16,"aM",@progbits,16
	.align 16
.LC1:
	.long	-2147483648
	.long	0
	.long	0
	.long	0
	.set	.LC2,.LC5
	.section	.rodata.cst32,"aM",@progbits,32
	.align 32
.LC3:
	.long	-2147483648
	.long	-2147483648
	.long	-2147483648
	.long	-2147483648
	.long	-2147483648
	.long	-2147483648
	.long	-2147483648
	.long	-2147483648
	.align 32
.LC5:
	.long	0
	.long	1072693248
	.long	0
	.long	1072693248
	.long	0
	.long	1072693248
	.long	0
	.long	1072693248
	.set	.LC6,.LC3
	.set	.LC7,.LC5
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC19:
	.quad	-2147483648
	.align 8
.LC20:
	.quad	2147483647
	.align 8
.LC21:
	.quad	1
	.align 8
.LC22:
	.long	-1
	.long	1072693247
	.align 8
.LC23:
	.long	0
	.long	1106247680
	.align 8
.LC24:
	.long	0
	.long	1005584384
	.align 8
.LC25:
	.long	0
	.long	1139802112
	.hidden	__dso_handle
	.ident	"GCC: (GNU) 12.2.1 20220819 (Red Hat 12.2.1-2)"
	.section	.note.GNU-stack,"",@progbits
