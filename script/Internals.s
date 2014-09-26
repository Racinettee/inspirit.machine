	.file	"Internals.cpp"
	.text
	.globl	_ZN8inspirit6Engine10PushScreenEPNS_11IGameScreenE
	.align	16, 0x90
	.type	_ZN8inspirit6Engine10PushScreenEPNS_11IGameScreenE,@function
_ZN8inspirit6Engine10PushScreenEPNS_11IGameScreenE: # @_ZN8inspirit6Engine10PushScreenEPNS_11IGameScreenE
	.cfi_startproc
# BB#0:
	pushq	%rbp
.Ltmp2:
	.cfi_def_cfa_offset 16
.Ltmp3:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp4:
	.cfi_def_cfa_register %rbp
	movq	%rdi, -8(%rbp)
	popq	%rbp
	ret
.Ltmp5:
	.size	_ZN8inspirit6Engine10PushScreenEPNS_11IGameScreenE, .Ltmp5-_ZN8inspirit6Engine10PushScreenEPNS_11IGameScreenE
	.cfi_endproc

	.globl	_ZN8inspirit6Engine9PopScreenEv
	.align	16, 0x90
	.type	_ZN8inspirit6Engine9PopScreenEv,@function
_ZN8inspirit6Engine9PopScreenEv:        # @_ZN8inspirit6Engine9PopScreenEv
	.cfi_startproc
# BB#0:
	pushq	%rbp
.Ltmp8:
	.cfi_def_cfa_offset 16
.Ltmp9:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp10:
	.cfi_def_cfa_register %rbp
	movq	%rdi, -8(%rbp)          # 8-byte Spill
	ud2
.Ltmp11:
	.size	_ZN8inspirit6Engine9PopScreenEv, .Ltmp11-_ZN8inspirit6Engine9PopScreenEv
	.cfi_endproc

	.globl	_ZN8inspirit6Engine13CurrentScreenEv
	.align	16, 0x90
	.type	_ZN8inspirit6Engine13CurrentScreenEv,@function
_ZN8inspirit6Engine13CurrentScreenEv:   # @_ZN8inspirit6Engine13CurrentScreenEv
	.cfi_startproc
# BB#0:
	pushq	%rbp
.Ltmp14:
	.cfi_def_cfa_offset 16
.Ltmp15:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp16:
	.cfi_def_cfa_register %rbp
	ud2
.Ltmp17:
	.size	_ZN8inspirit6Engine13CurrentScreenEv, .Ltmp17-_ZN8inspirit6Engine13CurrentScreenEv
	.cfi_endproc

	.globl	_ZN8inspirit6Engine9TopScreenEv
	.align	16, 0x90
	.type	_ZN8inspirit6Engine9TopScreenEv,@function
_ZN8inspirit6Engine9TopScreenEv:        # @_ZN8inspirit6Engine9TopScreenEv
	.cfi_startproc
# BB#0:
	pushq	%rbp
.Ltmp20:
	.cfi_def_cfa_offset 16
.Ltmp21:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp22:
	.cfi_def_cfa_register %rbp
	ud2
.Ltmp23:
	.size	_ZN8inspirit6Engine9TopScreenEv, .Ltmp23-_ZN8inspirit6Engine9TopScreenEv
	.cfi_endproc

	.globl	_ZN8inspirit6Engine6DeltaTEv
	.align	16, 0x90
	.type	_ZN8inspirit6Engine6DeltaTEv,@function
_ZN8inspirit6Engine6DeltaTEv:           # @_ZN8inspirit6Engine6DeltaTEv
	.cfi_startproc
# BB#0:
	pushq	%rbp
.Ltmp26:
	.cfi_def_cfa_offset 16
.Ltmp27:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp28:
	.cfi_def_cfa_register %rbp
	ud2
.Ltmp29:
	.size	_ZN8inspirit6Engine6DeltaTEv, .Ltmp29-_ZN8inspirit6Engine6DeltaTEv
	.cfi_endproc


	.ident	"Ubuntu clang version 3.4-1ubuntu3 (tags/RELEASE_34/final) (based on LLVM 3.4)"
	.section	".note.GNU-stack","",@progbits
