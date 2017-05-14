;******************************************************************************
;* TMS320C6x C/C++ Codegen                                       Unix v6.1.17 *
;* Date/Time created: Wed Apr 12 17:36:29 2017                                *
;******************************************************************************
	.compiler_opts --c64p_l1d_workaround=default --disable:=sploop --endian=little --hll_source=on --mem_model:code=far --mem_model:const=data --mem_model:data=far --predefine_memory_model_macros --quiet --silicon_version=6500 --symdebug:skeletal 

;******************************************************************************
;* GLOBAL FILE PARAMETERS                                                     *
;*                                                                            *
;*   Architecture      : TMS320C64x+                                          *
;*   Optimization      : Enabled at level 3                                   *
;*   Optimizing for    : Speed                                                *
;*                       Based on options: -o3, no -ms                        *
;*   Endian            : Little                                               *
;*   Interrupt Thrshld : Disabled                                             *
;*   Data Access Model : Far                                                  *
;*   Pipelining        : Enabled                                              *
;*   Speculate Loads   : Disabled                                             *
;*   Memory Aliases    : Presume are aliases (pessimistic)                    *
;*   Debug Info        : DWARF Debug for Program Analysis w/Optimization      *
;*                                                                            *
;******************************************************************************

	.asg	A15, FP
	.asg	B14, DP
	.asg	B15, SP
	.global	$bss


$C$DW$CU	.dwtag  DW_TAG_compile_unit
	.dwattr $C$DW$CU, DW_AT_name("task.c")
	.dwattr $C$DW$CU, DW_AT_producer("TMS320C6x C/C++ Codegen Unix v6.1.17 Copyright (c) 1996-2010 Texas Instruments Incorporated")
	.dwattr $C$DW$CU, DW_AT_TI_version(0x01)
	.dwattr $C$DW$CU, DW_AT_comp_dir("/data/home/in4342-admin/esLab/helperExamples/pool_notify/dsp")
;*****************************************************************************
;* CINIT RECORDS                                                             *
;*****************************************************************************
	.sect	".cinit"
	.align	8
	.field  	4,32
	.field  	_count$1+0,32
	.field  	0,32			; _count$1 @ 0


$C$DW$1	.dwtag  DW_TAG_subprogram, DW_AT_name("MEM_free")
	.dwattr $C$DW$1, DW_AT_TI_symbol_name("_MEM_free")
	.dwattr $C$DW$1, DW_AT_type(*$C$DW$T$57)
	.dwattr $C$DW$1, DW_AT_declaration
	.dwattr $C$DW$1, DW_AT_external
$C$DW$2	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$2, DW_AT_type(*$C$DW$T$22)
$C$DW$3	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$3, DW_AT_type(*$C$DW$T$39)
$C$DW$4	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$4, DW_AT_type(*$C$DW$T$40)
	.dwendtag $C$DW$1


$C$DW$5	.dwtag  DW_TAG_subprogram, DW_AT_name("MEM_valloc")
	.dwattr $C$DW$5, DW_AT_TI_symbol_name("_MEM_valloc")
	.dwattr $C$DW$5, DW_AT_type(*$C$DW$T$39)
	.dwattr $C$DW$5, DW_AT_declaration
	.dwattr $C$DW$5, DW_AT_external
$C$DW$6	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$6, DW_AT_type(*$C$DW$T$22)
$C$DW$7	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$7, DW_AT_type(*$C$DW$T$40)
$C$DW$8	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$8, DW_AT_type(*$C$DW$T$40)
$C$DW$9	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$9, DW_AT_type(*$C$DW$T$41)
	.dwendtag $C$DW$5


$C$DW$10	.dwtag  DW_TAG_subprogram, DW_AT_name("SEM_pend")
	.dwattr $C$DW$10, DW_AT_TI_symbol_name("_SEM_pend")
	.dwattr $C$DW$10, DW_AT_type(*$C$DW$T$57)
	.dwattr $C$DW$10, DW_AT_declaration
	.dwattr $C$DW$10, DW_AT_external
$C$DW$11	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$11, DW_AT_type(*$C$DW$T$50)
$C$DW$12	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$12, DW_AT_type(*$C$DW$T$65)
	.dwendtag $C$DW$10


$C$DW$13	.dwtag  DW_TAG_subprogram, DW_AT_name("SEM_post")
	.dwattr $C$DW$13, DW_AT_TI_symbol_name("_SEM_post")
	.dwattr $C$DW$13, DW_AT_declaration
	.dwattr $C$DW$13, DW_AT_external
$C$DW$14	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$14, DW_AT_type(*$C$DW$T$50)
	.dwendtag $C$DW$13


$C$DW$15	.dwtag  DW_TAG_subprogram, DW_AT_name("_SEM_dopost")
	.dwattr $C$DW$15, DW_AT_TI_symbol_name("__SEM_dopost")
	.dwattr $C$DW$15, DW_AT_declaration
	.dwattr $C$DW$15, DW_AT_external
$C$DW$16	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$16, DW_AT_type(*$C$DW$T$50)
	.dwendtag $C$DW$15


$C$DW$17	.dwtag  DW_TAG_subprogram, DW_AT_name("NOTIFY_register")
	.dwattr $C$DW$17, DW_AT_TI_symbol_name("_NOTIFY_register")
	.dwattr $C$DW$17, DW_AT_type(*$C$DW$T$22)
	.dwattr $C$DW$17, DW_AT_declaration
	.dwattr $C$DW$17, DW_AT_external
$C$DW$18	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$18, DW_AT_type(*$C$DW$T$37)
$C$DW$19	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$19, DW_AT_type(*$C$DW$T$37)
$C$DW$20	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$20, DW_AT_type(*$C$DW$T$37)
$C$DW$21	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$21, DW_AT_type(*$C$DW$T$56)
$C$DW$22	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$22, DW_AT_type(*$C$DW$T$39)
	.dwendtag $C$DW$17


$C$DW$23	.dwtag  DW_TAG_subprogram, DW_AT_name("NOTIFY_unregister")
	.dwattr $C$DW$23, DW_AT_TI_symbol_name("_NOTIFY_unregister")
	.dwattr $C$DW$23, DW_AT_type(*$C$DW$T$22)
	.dwattr $C$DW$23, DW_AT_declaration
	.dwattr $C$DW$23, DW_AT_external
$C$DW$24	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$24, DW_AT_type(*$C$DW$T$37)
$C$DW$25	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$25, DW_AT_type(*$C$DW$T$37)
$C$DW$26	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$26, DW_AT_type(*$C$DW$T$37)
$C$DW$27	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$27, DW_AT_type(*$C$DW$T$56)
$C$DW$28	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$28, DW_AT_type(*$C$DW$T$3)
	.dwendtag $C$DW$23


$C$DW$29	.dwtag  DW_TAG_subprogram, DW_AT_name("NOTIFY_notify")
	.dwattr $C$DW$29, DW_AT_TI_symbol_name("_NOTIFY_notify")
	.dwattr $C$DW$29, DW_AT_type(*$C$DW$T$22)
	.dwattr $C$DW$29, DW_AT_declaration
	.dwattr $C$DW$29, DW_AT_external
$C$DW$30	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$30, DW_AT_type(*$C$DW$T$37)
$C$DW$31	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$31, DW_AT_type(*$C$DW$T$37)
$C$DW$32	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$32, DW_AT_type(*$C$DW$T$37)
$C$DW$33	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$33, DW_AT_type(*$C$DW$T$37)
	.dwendtag $C$DW$29


$C$DW$34	.dwtag  DW_TAG_subprogram, DW_AT_name("BCACHE_inv")
	.dwattr $C$DW$34, DW_AT_TI_symbol_name("_BCACHE_inv")
	.dwattr $C$DW$34, DW_AT_declaration
	.dwattr $C$DW$34, DW_AT_external
$C$DW$35	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$35, DW_AT_type(*$C$DW$T$39)
$C$DW$36	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$36, DW_AT_type(*$C$DW$T$40)
$C$DW$37	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$37, DW_AT_type(*$C$DW$T$57)
	.dwendtag $C$DW$34

$C$DW$38	.dwtag  DW_TAG_variable, DW_AT_name("DDR2")
	.dwattr $C$DW$38, DW_AT_TI_symbol_name("_DDR2")
	.dwattr $C$DW$38, DW_AT_type(*$C$DW$T$22)
	.dwattr $C$DW$38, DW_AT_declaration
	.dwattr $C$DW$38, DW_AT_external
$C$DW$39	.dwtag  DW_TAG_variable, DW_AT_name("MPCSXFER_BufferSize")
	.dwattr $C$DW$39, DW_AT_TI_symbol_name("_MPCSXFER_BufferSize")
	.dwattr $C$DW$39, DW_AT_type(*$C$DW$T$34)
	.dwattr $C$DW$39, DW_AT_declaration
	.dwattr $C$DW$39, DW_AT_external
	.global	_buf
_buf:	.usect	".far",4,4
$C$DW$40	.dwtag  DW_TAG_variable, DW_AT_name("buf")
	.dwattr $C$DW$40, DW_AT_TI_symbol_name("_buf")
	.dwattr $C$DW$40, DW_AT_location[DW_OP_addr _buf]
	.dwattr $C$DW$40, DW_AT_type(*$C$DW$T$60)
	.dwattr $C$DW$40, DW_AT_external
	.global	_length
_length:	.usect	".far",4,4
$C$DW$41	.dwtag  DW_TAG_variable, DW_AT_name("length")
	.dwattr $C$DW$41, DW_AT_TI_symbol_name("_length")
	.dwattr $C$DW$41, DW_AT_location[DW_OP_addr _length]
	.dwattr $C$DW$41, DW_AT_type(*$C$DW$T$10)
	.dwattr $C$DW$41, DW_AT_external
_count$1:	.usect	".far",4,4
;	/data/bbToolChain/usr/local/share/c6000/bin/opt6x /tmp/1821639uPTj /tmp/182163u6bnD 
	.sect	".text"
	.clink
	.global	_sum_dsp

$C$DW$42	.dwtag  DW_TAG_subprogram, DW_AT_name("sum_dsp")
	.dwattr $C$DW$42, DW_AT_low_pc(_sum_dsp)
	.dwattr $C$DW$42, DW_AT_high_pc(0x00)
	.dwattr $C$DW$42, DW_AT_TI_symbol_name("_sum_dsp")
	.dwattr $C$DW$42, DW_AT_external
	.dwattr $C$DW$42, DW_AT_type(*$C$DW$T$10)
	.dwattr $C$DW$42, DW_AT_TI_begin_file("task.c")
	.dwattr $C$DW$42, DW_AT_TI_begin_line(0x65)
	.dwattr $C$DW$42, DW_AT_TI_begin_column(0x05)
	.dwattr $C$DW$42, DW_AT_frame_base[DW_OP_breg31 0]
	.dwattr $C$DW$42, DW_AT_TI_skeletal
	.dwpsn	file "task.c",line 102,column 1,is_stmt,address _sum_dsp

;******************************************************************************
;* FUNCTION NAME: sum_dsp                                                     *
;*                                                                            *
;*   Regs Modified     : A0,A3,A4,A5,B0,B1,B4                                 *
;*   Regs Used         : A0,A3,A4,A5,B0,B1,B3,B4                              *
;*   Local Frame Size  : 0 Args + 0 Auto + 0 Save = 0 byte                    *
;******************************************************************************
_sum_dsp:
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14
           MVKL    .S1     _length,A3
           MVKH    .S1     _length,A3
           LDW     .D1T1   *A3,A3            ; |104| 
           ZERO    .L1     A5                ; |103| 
           MVKL    .S2     _buf,B4
           MVKH    .S2     _buf,B4
           NOP             1

           MV      .L2X    A3,B0
||         CMPGT   .L1     A3,0,A0           ; |104| 

           CMPGT   .L2     B0,4,B1
|| [!A0]   B       .S1     $C$L5             ; |104| 
|| [ A0]   LDW     .D2T1   *B4,A4

   [!A0]   ZERO    .L2     B1                ; nullify predicate
   [ B1]   BNOP    .S1     $C$L2,3
           ; BRANCHCC OCCURS {$C$L5}         ; |104| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 2
   [!B1]   LDBU    .D1T1   *A4++,A3          ; |104| 
   [ B1]   SUB     .L2     B0,5,B0
           ; BRANCHCC OCCURS {$C$L2} {0} 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 3
	.dwpsn	file "task.c",line 104,column 0,is_stmt
           NOP             3
;** --------------------------------------------------------------------------*
;**   BEGIN LOOP $C$L1
;** --------------------------------------------------------------------------*
$C$L1:    
$C$DW$L$_sum_dsp$4$B:
	.dwpsn	file "task.c",line 105,column 0,is_stmt
;          EXCLUSIVE CPU CYCLES: 7

           SUB     .L2     B0,1,B0           ; |104| 
||         ADD     .L1     A3,A5,A5          ; |104| 

   [ B0]   B       .S1     $C$L1             ; |104| 
|| [ B0]   LDBU    .D1T1   *A4++,A3          ; |104| 

	.dwpsn	file "task.c",line 107,column 0,is_stmt
   [!B0]   BNOP    .S1     $C$L6,4
           ; BRANCHCC OCCURS {$C$L1}         ; |104| 
$C$DW$L$_sum_dsp$4$E:
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 1
$C$DW$43	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$43, DW_AT_low_pc(0x00)
	.dwattr $C$DW$43, DW_AT_TI_return

           RET     .S2     B3                ; |109| 
||         MV      .L1     A5,A4             ; |108| 

           ; BRANCH OCCURS {$C$L6}  
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*
;*      Loop source line                 : 104
;*      Loop opening brace source line   : 105
;*      Loop closing brace source line   : 107
;*      Known Minimum Trip Count         : 1                    
;*      Known Max Trip Count Factor      : 1
;*      Loop Carried Dependency Bound(^) : 0
;*      Unpartitioned Resource Bound     : 1
;*      Partitioned Resource Bound(*)    : 1
;*      Resource Partition:
;*                                A-side   B-side
;*      .L units                     0        0     
;*      .S units                     0        1*    
;*      .D units                     1*       0     
;*      .M units                     0        0     
;*      .X cross paths               0        0     
;*      .T address paths             1*       0     
;*      Long read paths              0        0     
;*      Long write paths             0        0     
;*      Logical  ops (.LS)           0        0     (.L or .S unit)
;*      Addition ops (.LSD)          1        0     (.L or .S or .D unit)
;*      Bound(.L .S .LS)             0        1*    
;*      Bound(.L .S .D .LS .LSD)     1*       1*    
;*
;*      Searching for software pipeline schedule at ...
;*         ii = 1  Schedule found with 6 iterations in parallel
;*
;*      Register Usage Table:
;*          +-----------------------------------------------------------------+
;*          |AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA|BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB|
;*          |00000000001111111111222222222233|00000000001111111111222222222233|
;*          |01234567890123456789012345678901|01234567890123456789012345678901|
;*          |--------------------------------+--------------------------------|
;*       0: |*  ***                          |*                               |
;*          +-----------------------------------------------------------------+
;*
;*      Done
;*
;*      Redundant loop generated
;*      Epilog not removed
;*      Collapsed epilog stages       : 0
;*
;*      Prolog not entirely removed
;*      Collapsed prolog stages       : 1
;*
;*      Minimum required memory pad   : 0 bytes
;*
;*      For further improvement on this loop, try option -mh5
;*
;*      Minimum safe trip count       : 5
;*
;*
;*      Mem bank conflicts/iter(est.) : { min 0.000, est 0.000, max 0.000 }
;*      Mem bank perf. penalty (est.) : 0.0%
;*
;*
;*      Total cycles (est.)         : 5 + trip_cnt * 1        
;*----------------------------------------------------------------------------*
;*       SETUP CODE
;*
;*                  SUB             B0,1,B0
;*
;*        SINGLE SCHEDULED ITERATION
;*
;*        $C$C25:
;*   0              LDBU    .D1T1   *A4++,A3          ; |104| 
;*     ||   [ B0]   BDEC    .S2     $C$C25,B0         ; |104| 
;*   1              NOP             4
;*   5              ADD     .S1     A3,A5,A5          ; |104| 
;*   6              ; BRANCHCC OCCURS {$C$C25}        ; |104| 
;*----------------------------------------------------------------------------*
$C$L2:    ; PIPED LOOP PROLOG
;          EXCLUSIVE CPU CYCLES: 5
   [ B0]   BDEC    .S2     $C$L3,B0          ; |104| (P) <0,0> 

           LDBU    .D1T1   *A4++,A3          ; |104| (P) <0,0> 
|| [ B0]   BDEC    .S2     $C$L3,B0          ; |104| (P) <1,0> 

           LDBU    .D1T1   *A4++,A3          ; |104| (P) <1,0> 
|| [ B0]   BDEC    .S2     $C$L3,B0          ; |104| (P) <2,0> 

           LDBU    .D1T1   *A4++,A3          ; |104| (P) <2,0> 
|| [ B0]   BDEC    .S2     $C$L3,B0          ; |104| (P) <3,0> 

	.dwpsn	file "task.c",line 104,column 0,is_stmt

           MVK     .L1     0x1,A0            ; init prolog collapse predicate
||         LDBU    .D1T1   *A4++,A3          ; |104| (P) <3,0> 
|| [ B0]   BDEC    .S2     $C$L3,B0          ; |104| (P) <4,0> 

;** --------------------------------------------------------------------------*
$C$L3:    ; PIPED LOOP KERNEL
$C$DW$L$_sum_dsp$7$B:
	.dwpsn	file "task.c",line 105,column 0,is_stmt
;          EXCLUSIVE CPU CYCLES: 1
	.dwpsn	file "task.c",line 107,column 0,is_stmt

   [ A0]   SUB     .L1     A0,1,A0           ; <0,5> 
|| [!A0]   ADD     .S1     A3,A5,A5          ; |104| <0,5> 
|| [ B0]   BDEC    .S2     $C$L3,B0          ; |104| <5,0> 
||         LDBU    .D1T1   *A4++,A3          ; |104| <5,0> 

$C$DW$L$_sum_dsp$7$E:
;** --------------------------------------------------------------------------*
$C$L4:    ; PIPED LOOP EPILOG
;          EXCLUSIVE CPU CYCLES: 4
           ADD     .L1     A3,A5,A4          ; |104| (E) <1,5> 
           ADD     .L1     A3,A4,A4          ; |104| (E) <2,5> 
           ADD     .L1     A3,A4,A4          ; |104| (E) <3,5> 
           ADD     .L1     A3,A4,A4          ; |104| (E) <4,5> 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 1
           ADD     .L1     A3,A4,A5          ; |104| (E) <5,5> 
;** --------------------------------------------------------------------------*
$C$L5:    
;          EXCLUSIVE CPU CYCLES: 1
$C$DW$44	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$44, DW_AT_low_pc(0x00)
	.dwattr $C$DW$44, DW_AT_TI_return

           RET     .S2     B3                ; |109| 
||         MV      .L1     A5,A4             ; |108| 

;** --------------------------------------------------------------------------*
$C$L6:    
;          EXCLUSIVE CPU CYCLES: 5
	.dwpsn	file "task.c",line 109,column 1,is_stmt
           NOP             5
           ; BRANCH OCCURS {B3}              ; |109| 

$C$DW$45	.dwtag  DW_TAG_TI_loop
	.dwattr $C$DW$45, DW_AT_name("/data/home/in4342-admin/esLab/helperExamples/pool_notify/dsp/task.asm:$C$L3:1:1492018589")
	.dwattr $C$DW$45, DW_AT_TI_begin_file("task.c")
	.dwattr $C$DW$45, DW_AT_TI_begin_line(0x68)
	.dwattr $C$DW$45, DW_AT_TI_end_line(0x6b)
$C$DW$46	.dwtag  DW_TAG_TI_loop_range
	.dwattr $C$DW$46, DW_AT_low_pc($C$DW$L$_sum_dsp$7$B)
	.dwattr $C$DW$46, DW_AT_high_pc($C$DW$L$_sum_dsp$7$E)
	.dwendtag $C$DW$45


$C$DW$47	.dwtag  DW_TAG_TI_loop
	.dwattr $C$DW$47, DW_AT_name("/data/home/in4342-admin/esLab/helperExamples/pool_notify/dsp/task.asm:$C$L1:1:1492018589")
	.dwattr $C$DW$47, DW_AT_TI_begin_file("task.c")
	.dwattr $C$DW$47, DW_AT_TI_begin_line(0x68)
	.dwattr $C$DW$47, DW_AT_TI_end_line(0x6b)
$C$DW$48	.dwtag  DW_TAG_TI_loop_range
	.dwattr $C$DW$48, DW_AT_low_pc($C$DW$L$_sum_dsp$4$B)
	.dwattr $C$DW$48, DW_AT_high_pc($C$DW$L$_sum_dsp$4$E)
	.dwendtag $C$DW$47

	.dwattr $C$DW$42, DW_AT_TI_end_file("task.c")
	.dwattr $C$DW$42, DW_AT_TI_end_line(0x6d)
	.dwattr $C$DW$42, DW_AT_TI_end_column(0x01)
	.dwendtag $C$DW$42

	.sect	".text"
	.clink

$C$DW$49	.dwtag  DW_TAG_subprogram, DW_AT_name("Task_notify")
	.dwattr $C$DW$49, DW_AT_low_pc(_Task_notify)
	.dwattr $C$DW$49, DW_AT_high_pc(0x00)
	.dwattr $C$DW$49, DW_AT_TI_symbol_name("_Task_notify")
	.dwattr $C$DW$49, DW_AT_TI_begin_file("task.c")
	.dwattr $C$DW$49, DW_AT_TI_begin_line(0x9b)
	.dwattr $C$DW$49, DW_AT_TI_begin_column(0x0d)
	.dwattr $C$DW$49, DW_AT_frame_base[DW_OP_breg31 8]
	.dwattr $C$DW$49, DW_AT_TI_skeletal
	.dwpsn	file "task.c",line 156,column 1,is_stmt,address _Task_notify
$C$DW$50	.dwtag  DW_TAG_formal_parameter, DW_AT_name("eventNo")
	.dwattr $C$DW$50, DW_AT_TI_symbol_name("_eventNo")
	.dwattr $C$DW$50, DW_AT_type(*$C$DW$T$37)
	.dwattr $C$DW$50, DW_AT_location[DW_OP_reg4]
$C$DW$51	.dwtag  DW_TAG_formal_parameter, DW_AT_name("arg")
	.dwattr $C$DW$51, DW_AT_TI_symbol_name("_arg")
	.dwattr $C$DW$51, DW_AT_type(*$C$DW$T$39)
	.dwattr $C$DW$51, DW_AT_location[DW_OP_reg20]
$C$DW$52	.dwtag  DW_TAG_formal_parameter, DW_AT_name("info")
	.dwattr $C$DW$52, DW_AT_TI_symbol_name("_info")
	.dwattr $C$DW$52, DW_AT_type(*$C$DW$T$39)
	.dwattr $C$DW$52, DW_AT_location[DW_OP_reg6]

;******************************************************************************
;* FUNCTION NAME: Task_notify                                                 *
;*                                                                            *
;*   Regs Modified     : A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,B0,B1,B2,B3,B4,B5,B6,  *
;*                           B7,B8,B9,A16,A17,A18,A19,A20,A21,A22,A23,A24,A25,*
;*                           A26,A27,A28,A29,A30,A31,B16,B17,B18,B19,B20,B21, *
;*                           B22,B23,B24,B25,B26,B27,B28,B29,B30,B31          *
;*   Regs Used         : A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,B0,B1,B2,B3,B4,B5,B6,  *
;*                           B7,B8,B9,SP,A16,A17,A18,A19,A20,A21,A22,A23,A24, *
;*                           A25,A26,A27,A28,A29,A30,A31,B16,B17,B18,B19,B20, *
;*                           B21,B22,B23,B24,B25,B26,B27,B28,B29,B30,B31      *
;*   Local Frame Size  : 0 Args + 0 Auto + 4 Save = 4 byte                    *
;******************************************************************************
_Task_notify:
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 17
           MVKL    .S1     _count$1,A4
           MVKH    .S1     _count$1,A4
           LDW     .D1T1   *A4,A3            ; |162| 
           MVKL    .S2     _length,B5
           MVKH    .S2     _length,B5
           MVKL    .S1     _buf,A5
           MVKH    .S1     _buf,A5
           ADD     .L1     1,A3,A3           ; |162| 
           CMPEQ   .L1     A3,2,A0           ; |166| 

   [ A0]   STW     .D2T1   A6,*B5            ; |167| 
||         MVKL    .S2     _SEM_post,B5      ; |170| 

           MVKH    .S2     _SEM_post,B5      ; |170| 
$C$DW$53	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$53, DW_AT_low_pc(0x00)
	.dwattr $C$DW$53, DW_AT_name("_SEM_post")
	.dwattr $C$DW$53, DW_AT_TI_call
	.dwattr $C$DW$53, DW_AT_TI_return
           CALLRET .S2     B5                ; |170| 
           STW     .D1T1   A3,*A4            ; |162| 
           CMPEQ   .L2X    A3,1,B0           ; |163| 
   [ B0]   STW     .D1T1   A6,*A5            ; |164| 
           ADD     .L1X    4,B4,A4           ; |170| 
	.dwpsn	file "task.c",line 171,column 1,is_stmt
           NOP             1
$C$RL0:    ; CALL-RETURN OCCURS {_SEM_post} {0}  ; |170| 
	.dwattr $C$DW$49, DW_AT_TI_end_file("task.c")
	.dwattr $C$DW$49, DW_AT_TI_end_line(0xab)
	.dwattr $C$DW$49, DW_AT_TI_end_column(0x01)
	.dwendtag $C$DW$49

	.sect	".text"
	.clink
	.global	_Task_execute

$C$DW$54	.dwtag  DW_TAG_subprogram, DW_AT_name("Task_execute")
	.dwattr $C$DW$54, DW_AT_low_pc(_Task_execute)
	.dwattr $C$DW$54, DW_AT_high_pc(0x00)
	.dwattr $C$DW$54, DW_AT_TI_symbol_name("_Task_execute")
	.dwattr $C$DW$54, DW_AT_external
	.dwattr $C$DW$54, DW_AT_type(*$C$DW$T$22)
	.dwattr $C$DW$54, DW_AT_TI_begin_file("task.c")
	.dwattr $C$DW$54, DW_AT_TI_begin_line(0x6f)
	.dwattr $C$DW$54, DW_AT_TI_begin_column(0x05)
	.dwattr $C$DW$54, DW_AT_frame_base[DW_OP_breg31 16]
	.dwattr $C$DW$54, DW_AT_TI_skeletal
	.dwpsn	file "task.c",line 112,column 1,is_stmt,address _Task_execute
$C$DW$55	.dwtag  DW_TAG_formal_parameter, DW_AT_name("info")
	.dwattr $C$DW$55, DW_AT_TI_symbol_name("_info")
	.dwattr $C$DW$55, DW_AT_type(*$C$DW$T$75)
	.dwattr $C$DW$55, DW_AT_location[DW_OP_reg4]

;******************************************************************************
;* FUNCTION NAME: Task_execute                                                *
;*                                                                            *
;*   Regs Modified     : A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,B0,B1,B2,B3,B4,*
;*                           B5,B6,B7,B8,B9,B10,SP,A16,A17,A18,A19,A20,A21,   *
;*                           A22,A23,A24,A25,A26,A27,A28,A29,A30,A31,B16,B17, *
;*                           B18,B19,B20,B21,B22,B23,B24,B25,B26,B27,B28,B29, *
;*                           B30,B31                                          *
;*   Regs Used         : A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,B0,B1,B2,B3,B4,*
;*                           B5,B6,B7,B8,B9,B10,SP,A16,A17,A18,A19,A20,A21,   *
;*                           A22,A23,A24,A25,A26,A27,A28,A29,A30,A31,B16,B17, *
;*                           B18,B19,B20,B21,B22,B23,B24,B25,B26,B27,B28,B29, *
;*                           B30,B31                                          *
;*   Local Frame Size  : 0 Args + 0 Auto + 16 Save = 16 byte                  *
;******************************************************************************
_Task_execute:
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 9
           MVKL    .S1     _SEM_pend,A3      ; |116| 
           MVKH    .S1     _SEM_pend,A3      ; |116| 
           STW     .D2T2   B10,*SP--(8)      ; |112| 
$C$DW$56	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$56, DW_AT_low_pc(0x00)
	.dwattr $C$DW$56, DW_AT_name("_SEM_pend")
	.dwattr $C$DW$56, DW_AT_TI_call
           CALL    .S2X    A3                ; |116| 
           STDW    .D2T1   A11:A10,*SP--     ; |112| 
           MV      .L1X    B3,A11            ; |112| 
           ADDKPC  .S2     $C$RL1,B3,1       ; |116| 

           ADD     .L1     4,A4,A4           ; |116| 
||         MVK     .L2     0xffffffff,B4     ; |116| 

$C$RL1:    ; CALL OCCURS {_SEM_pend} {0}     ; |116| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 10
           MVKL    .S2     _BCACHE_inv,B5    ; |119| 
           MVKL    .S2     _buf,B10
           MVKH    .S2     _BCACHE_inv,B5    ; |119| 

           MVKL    .S1     _length,A10
||         MVKH    .S2     _buf,B10

$C$DW$57	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$57, DW_AT_low_pc(0x00)
	.dwattr $C$DW$57, DW_AT_name("_BCACHE_inv")
	.dwattr $C$DW$57, DW_AT_TI_call

           CALL    .S2     B5                ; |119| 
||         MVKH    .S1     _length,A10

           LDW     .D1T2   *A10,B4           ; |119| 
||         LDW     .D2T1   *B10,A4           ; |119| 

           ADDKPC  .S2     $C$RL2,B3,2       ; |119| 
           MVK     .L1     0x1,A6            ; |119| 
$C$RL2:    ; CALL OCCURS {_BCACHE_inv} {0}   ; |119| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 12
           LDW     .D1T1   *A10,A3           ; |104| 
           ZERO    .L1     A10               ; |103| 
           MV      .L2     B10,B4            ; |104| 
           NOP             2

           MV      .L2X    A3,B0
||         CMPGT   .L1     A3,0,A0           ; |104| 

           CMPGT   .L2     B0,4,B1
|| [!A0]   B       .S1     $C$L11            ; |104| 
|| [ A0]   LDW     .D2T1   *B4,A4

   [!A0]   ZERO    .L2     B1                ; nullify predicate
   [ B1]   BNOP    .S1     $C$L8,3
           ; BRANCHCC OCCURS {$C$L11}        ; |104| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 2
   [!B1]   LDBU    .D1T1   *A4++,A3          ; |104| 
   [ B1]   SUB     .L2     B0,5,B0
           ; BRANCHCC OCCURS {$C$L8} {0} 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 3
	.dwpsn	file "task.c",line 104,column 0,is_stmt
           NOP             3
;** --------------------------------------------------------------------------*
;**   BEGIN LOOP $C$L7
;** --------------------------------------------------------------------------*
$C$L7:    
$C$DW$L$_Task_execute$6$B:
	.dwpsn	file "task.c",line 105,column 0,is_stmt
;          EXCLUSIVE CPU CYCLES: 7

           SUB     .L2     B0,1,B0           ; |104| 
||         ADD     .L1     A3,A10,A10        ; |104| 

   [ B0]   B       .S1     $C$L7             ; |104| 
|| [ B0]   LDBU    .D1T1   *A4++,A3          ; |104| 

	.dwpsn	file "task.c",line 107,column 0,is_stmt
   [!B0]   BNOP    .S1     $C$L12,4
           ; BRANCHCC OCCURS {$C$L7}         ; |104| 
$C$DW$L$_Task_execute$6$E:
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 1
           MVKL    .S1     _NOTIFY_notify,A3 ; |125| 
           ; BRANCH OCCURS {$C$L12}  
;*----------------------------------------------------------------------------*
;*   SOFTWARE PIPELINE INFORMATION
;*
;*      Loop source line                 : 104
;*      Loop opening brace source line   : 105
;*      Loop closing brace source line   : 107
;*      Known Minimum Trip Count         : 1                    
;*      Known Max Trip Count Factor      : 1
;*      Loop Carried Dependency Bound(^) : 0
;*      Unpartitioned Resource Bound     : 1
;*      Partitioned Resource Bound(*)    : 1
;*      Resource Partition:
;*                                A-side   B-side
;*      .L units                     0        0     
;*      .S units                     0        1*    
;*      .D units                     1*       0     
;*      .M units                     0        0     
;*      .X cross paths               0        0     
;*      .T address paths             1*       0     
;*      Long read paths              0        0     
;*      Long write paths             0        0     
;*      Logical  ops (.LS)           0        0     (.L or .S unit)
;*      Addition ops (.LSD)          1        0     (.L or .S or .D unit)
;*      Bound(.L .S .LS)             0        1*    
;*      Bound(.L .S .D .LS .LSD)     1*       1*    
;*
;*      Searching for software pipeline schedule at ...
;*         ii = 1  Schedule found with 6 iterations in parallel
;*
;*      Register Usage Table:
;*          +-----------------------------------------------------------------+
;*          |AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA|BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB|
;*          |00000000001111111111222222222233|00000000001111111111222222222233|
;*          |01234567890123456789012345678901|01234567890123456789012345678901|
;*          |--------------------------------+--------------------------------|
;*       0: |*  ***                          |*                               |
;*          +-----------------------------------------------------------------+
;*
;*      Done
;*
;*      Redundant loop generated
;*      Epilog not removed
;*      Collapsed epilog stages       : 0
;*
;*      Prolog not entirely removed
;*      Collapsed prolog stages       : 1
;*
;*      Minimum required memory pad   : 0 bytes
;*
;*      For further improvement on this loop, try option -mh5
;*
;*      Minimum safe trip count       : 5
;*
;*
;*      Mem bank conflicts/iter(est.) : { min 0.000, est 0.000, max 0.000 }
;*      Mem bank perf. penalty (est.) : 0.0%
;*
;*
;*      Total cycles (est.)         : 5 + trip_cnt * 1        
;*----------------------------------------------------------------------------*
;*       SETUP CODE
;*
;*                  SUB             B0,1,B0
;*
;*        SINGLE SCHEDULED ITERATION
;*
;*        $C$C106:
;*   0              LDBU    .D1T1   *A4++,A3          ; |104| 
;*     ||   [ B0]   BDEC    .S2     $C$C106,B0        ; |104| 
;*   1              NOP             4
;*   5              ADD     .S1     A3,A5,A5          ; |104| 
;*   6              ; BRANCHCC OCCURS {$C$C106}       ; |104| 
;*----------------------------------------------------------------------------*
$C$L8:    ; PIPED LOOP PROLOG
;          EXCLUSIVE CPU CYCLES: 5
   [ B0]   BDEC    .S2     $C$L9,B0          ; |104| (P) <0,0> 

           LDBU    .D1T1   *A4++,A3          ; |104| (P) <0,0> 
|| [ B0]   BDEC    .S2     $C$L9,B0          ; |104| (P) <1,0> 

           LDBU    .D1T1   *A4++,A3          ; |104| (P) <1,0> 
|| [ B0]   BDEC    .S2     $C$L9,B0          ; |104| (P) <2,0> 

           LDBU    .D1T1   *A4++,A3          ; |104| (P) <2,0> 
|| [ B0]   BDEC    .S2     $C$L9,B0          ; |104| (P) <3,0> 

	.dwpsn	file "task.c",line 104,column 0,is_stmt

           MV      .L1     A10,A5
||         MVK     .S1     0x1,A0            ; init prolog collapse predicate
||         LDBU    .D1T1   *A4++,A3          ; |104| (P) <3,0> 
|| [ B0]   BDEC    .S2     $C$L9,B0          ; |104| (P) <4,0> 

;** --------------------------------------------------------------------------*
$C$L9:    ; PIPED LOOP KERNEL
$C$DW$L$_Task_execute$9$B:
	.dwpsn	file "task.c",line 105,column 0,is_stmt
;          EXCLUSIVE CPU CYCLES: 1
	.dwpsn	file "task.c",line 107,column 0,is_stmt

   [ A0]   SUB     .L1     A0,1,A0           ; <0,5> 
|| [!A0]   ADD     .S1     A3,A5,A5          ; |104| <0,5> 
|| [ B0]   BDEC    .S2     $C$L9,B0          ; |104| <5,0> 
||         LDBU    .D1T1   *A4++,A3          ; |104| <5,0> 

$C$DW$L$_Task_execute$9$E:
;** --------------------------------------------------------------------------*
$C$L10:    ; PIPED LOOP EPILOG
;          EXCLUSIVE CPU CYCLES: 4
           ADD     .L1     A3,A5,A4          ; |104| (E) <1,5> 
           ADD     .L1     A3,A4,A4          ; |104| (E) <2,5> 
           ADD     .L1     A3,A4,A4          ; |104| (E) <3,5> 
           ADD     .L1     A3,A4,A4          ; |104| (E) <4,5> 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 1
           ADD     .L1     A3,A4,A10         ; |104| 
;** --------------------------------------------------------------------------*
$C$L11:    
;          EXCLUSIVE CPU CYCLES: 1
           MVKL    .S1     _NOTIFY_notify,A3 ; |125| 
;** --------------------------------------------------------------------------*
$C$L12:    
;          EXCLUSIVE CPU CYCLES: 8
           MVKH    .S1     _NOTIFY_notify,A3 ; |125| 
           MVK     .L1     0x5,A6            ; |125| 
$C$DW$58	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$58, DW_AT_low_pc(0x00)
	.dwattr $C$DW$58, DW_AT_name("_NOTIFY_notify")
	.dwattr $C$DW$58, DW_AT_TI_call
           CALL    .S2X    A3                ; |125| 
           ZERO    .L2     B4                ; |125| 
           ZERO    .L2     B6                ; |125| 
           MVK     .L1     0x1,A4            ; |125| 
           ADDKPC  .S2     $C$RL3,B3,1       ; |125| 
$C$RL3:    ; CALL OCCURS {_NOTIFY_notify} {0}  ; |125| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 8
           MVKL    .S2     _NOTIFY_notify,B5 ; |127| 
           MVKH    .S2     _NOTIFY_notify,B5 ; |127| 
$C$DW$59	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$59, DW_AT_low_pc(0x00)
	.dwattr $C$DW$59, DW_AT_name("_NOTIFY_notify")
	.dwattr $C$DW$59, DW_AT_TI_call
           CALL    .S2     B5                ; |127| 
           ADDKPC  .S2     $C$RL4,B3,3       ; |127| 

           MVK     .L1     0x1,A4            ; |127| 
||         ZERO    .L2     B4                ; |127| 
||         MVK     .S1     0x5,A6            ; |127| 
||         MV      .S2X    A10,B6            ; |127| 

$C$RL4:    ; CALL OCCURS {_NOTIFY_notify} {0}  ; |127| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7
           MV      .L2X    A11,B3            ; |130| 
$C$DW$60	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$60, DW_AT_low_pc(0x00)
	.dwattr $C$DW$60, DW_AT_TI_return

           RET     .S2     B3                ; |130| 
||         LDDW    .D2T1   *++SP,A11:A10     ; |130| 

           LDW     .D2T2   *++SP(8),B10      ; |130| 
           ZERO    .L1     A4                ; |129| 
	.dwpsn	file "task.c",line 130,column 1,is_stmt
           NOP             3
           ; BRANCH OCCURS {B3}              ; |130| 

$C$DW$61	.dwtag  DW_TAG_TI_loop
	.dwattr $C$DW$61, DW_AT_name("/data/home/in4342-admin/esLab/helperExamples/pool_notify/dsp/task.asm:$C$L9:1:1492018589")
	.dwattr $C$DW$61, DW_AT_TI_begin_file("task.c")
	.dwattr $C$DW$61, DW_AT_TI_begin_line(0x68)
	.dwattr $C$DW$61, DW_AT_TI_end_line(0x6b)
$C$DW$62	.dwtag  DW_TAG_TI_loop_range
	.dwattr $C$DW$62, DW_AT_low_pc($C$DW$L$_Task_execute$9$B)
	.dwattr $C$DW$62, DW_AT_high_pc($C$DW$L$_Task_execute$9$E)
	.dwendtag $C$DW$61


$C$DW$63	.dwtag  DW_TAG_TI_loop
	.dwattr $C$DW$63, DW_AT_name("/data/home/in4342-admin/esLab/helperExamples/pool_notify/dsp/task.asm:$C$L7:1:1492018589")
	.dwattr $C$DW$63, DW_AT_TI_begin_file("task.c")
	.dwattr $C$DW$63, DW_AT_TI_begin_line(0x68)
	.dwattr $C$DW$63, DW_AT_TI_end_line(0x6b)
$C$DW$64	.dwtag  DW_TAG_TI_loop_range
	.dwattr $C$DW$64, DW_AT_low_pc($C$DW$L$_Task_execute$6$B)
	.dwattr $C$DW$64, DW_AT_high_pc($C$DW$L$_Task_execute$6$E)
	.dwendtag $C$DW$63

	.dwattr $C$DW$54, DW_AT_TI_end_file("task.c")
	.dwattr $C$DW$54, DW_AT_TI_end_line(0x82)
	.dwattr $C$DW$54, DW_AT_TI_end_column(0x01)
	.dwendtag $C$DW$54

	.sect	".text"
	.clink
	.global	_Task_delete

$C$DW$65	.dwtag  DW_TAG_subprogram, DW_AT_name("Task_delete")
	.dwattr $C$DW$65, DW_AT_low_pc(_Task_delete)
	.dwattr $C$DW$65, DW_AT_high_pc(0x00)
	.dwattr $C$DW$65, DW_AT_TI_symbol_name("_Task_delete")
	.dwattr $C$DW$65, DW_AT_external
	.dwattr $C$DW$65, DW_AT_type(*$C$DW$T$22)
	.dwattr $C$DW$65, DW_AT_TI_begin_file("task.c")
	.dwattr $C$DW$65, DW_AT_TI_begin_line(0x84)
	.dwattr $C$DW$65, DW_AT_TI_begin_column(0x05)
	.dwattr $C$DW$65, DW_AT_frame_base[DW_OP_breg31 16]
	.dwattr $C$DW$65, DW_AT_TI_skeletal
	.dwpsn	file "task.c",line 133,column 1,is_stmt,address _Task_delete
$C$DW$66	.dwtag  DW_TAG_formal_parameter, DW_AT_name("info")
	.dwattr $C$DW$66, DW_AT_TI_symbol_name("_info")
	.dwattr $C$DW$66, DW_AT_type(*$C$DW$T$75)
	.dwattr $C$DW$66, DW_AT_location[DW_OP_reg4]

;******************************************************************************
;* FUNCTION NAME: Task_delete                                                 *
;*                                                                            *
;*   Regs Modified     : A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,B0,B1,B2,B3,B4,*
;*                           B5,B6,B7,B8,B9,B13,SP,A16,A17,A18,A19,A20,A21,   *
;*                           A22,A23,A24,A25,A26,A27,A28,A29,A30,A31,B16,B17, *
;*                           B18,B19,B20,B21,B22,B23,B24,B25,B26,B27,B28,B29, *
;*                           B30,B31                                          *
;*   Regs Used         : A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,B0,B1,B2,B3,B4,*
;*                           B5,B6,B7,B8,B9,B13,SP,A16,A17,A18,A19,A20,A21,   *
;*                           A22,A23,A24,A25,A26,A27,A28,A29,A30,A31,B16,B17, *
;*                           B18,B19,B20,B21,B22,B23,B24,B25,B26,B27,B28,B29, *
;*                           B30,B31                                          *
;*   Local Frame Size  : 0 Args + 0 Auto + 16 Save = 16 byte                  *
;******************************************************************************
_Task_delete:
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 9
           MVKL    .S1     _NOTIFY_unregister,A3 ; |139| 
           MVKH    .S1     _NOTIFY_unregister,A3 ; |139| 
           MVKL    .S2     _Task_notify,B6   ; |139| 
$C$DW$67	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$67, DW_AT_low_pc(0x00)
	.dwattr $C$DW$67, DW_AT_name("_NOTIFY_unregister")
	.dwattr $C$DW$67, DW_AT_TI_call
           CALL    .S2X    A3                ; |139| 
           STW     .D2T2   B13,*SP--(8)      ; |133| 
           MVKH    .S2     _Task_notify,B6   ; |139| 
           MV      .L1     A4,A8             ; |133| 
           ZERO    .L2     B4                ; |139| 

           STDW    .D2T1   A11:A10,*SP--     ; |133| 
||         MV      .L1     A4,A11            ; |133| 
||         MV      .L2     B3,B13            ; |133| 
||         ADDKPC  .S2     $C$RL5,B3,0       ; |139| 
||         MVK     .S1     0x5,A6            ; |139| 
||         MVK     .D1     0x1,A4            ; |139| 

$C$RL5:    ; CALL OCCURS {_NOTIFY_unregister} {0}  ; |139| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 8
           MVKL    .S2     _MEM_free,B5      ; |146| 

           MVKH    .S2     _MEM_free,B5      ; |146| 
||         MVKL    .S1     _DDR2,A3

$C$DW$68	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$68, DW_AT_low_pc(0x00)
	.dwattr $C$DW$68, DW_AT_name("_MEM_free")
	.dwattr $C$DW$68, DW_AT_TI_call

           CALL    .S2     B5                ; |146| 
||         MVKH    .S1     _DDR2,A3

           MV      .L1     A4,A10            ; |139| 
||         LDW     .D1T1   *A3,A4            ; |146| 

           ADDKPC  .S2     $C$RL6,B3,2       ; |146| 

           MV      .L2X    A11,B4            ; |146| 
||         MVK     .S1     0x28,A6           ; |146| 

$C$RL6:    ; CALL OCCURS {_MEM_free} {0}     ; |146| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7
           MV      .L2     B13,B3            ; |152| 
$C$DW$69	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$69, DW_AT_low_pc(0x00)
	.dwattr $C$DW$69, DW_AT_TI_return

           RET     .S2     B3                ; |152| 
||         MV      .L1     A10,A4            ; |151| 
||         LDDW    .D2T1   *++SP,A11:A10     ; |152| 

           LDW     .D2T2   *++SP(8),B13      ; |152| 
	.dwpsn	file "task.c",line 152,column 1,is_stmt
           NOP             4
           ; BRANCH OCCURS {B3}              ; |152| 
	.dwattr $C$DW$65, DW_AT_TI_end_file("task.c")
	.dwattr $C$DW$65, DW_AT_TI_end_line(0x98)
	.dwattr $C$DW$65, DW_AT_TI_end_column(0x01)
	.dwendtag $C$DW$65

	.sect	".text"
	.clink
	.global	_Task_create

$C$DW$70	.dwtag  DW_TAG_subprogram, DW_AT_name("Task_create")
	.dwattr $C$DW$70, DW_AT_low_pc(_Task_create)
	.dwattr $C$DW$70, DW_AT_high_pc(0x00)
	.dwattr $C$DW$70, DW_AT_TI_symbol_name("_Task_create")
	.dwattr $C$DW$70, DW_AT_external
	.dwattr $C$DW$70, DW_AT_type(*$C$DW$T$22)
	.dwattr $C$DW$70, DW_AT_TI_begin_file("task.c")
	.dwattr $C$DW$70, DW_AT_TI_begin_line(0x19)
	.dwattr $C$DW$70, DW_AT_TI_begin_column(0x05)
	.dwattr $C$DW$70, DW_AT_frame_base[DW_OP_breg31 24]
	.dwattr $C$DW$70, DW_AT_TI_skeletal
	.dwpsn	file "task.c",line 26,column 1,is_stmt,address _Task_create
$C$DW$71	.dwtag  DW_TAG_formal_parameter, DW_AT_name("infoPtr")
	.dwattr $C$DW$71, DW_AT_TI_symbol_name("_infoPtr")
	.dwattr $C$DW$71, DW_AT_type(*$C$DW$T$76)
	.dwattr $C$DW$71, DW_AT_location[DW_OP_reg4]

;******************************************************************************
;* FUNCTION NAME: Task_create                                                 *
;*                                                                            *
;*   Regs Modified     : A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,B0,B1,B2,B3,B4,*
;*                           B5,B6,B7,B8,B9,B10,B11,SP,A16,A17,A18,A19,A20,   *
;*                           A21,A22,A23,A24,A25,A26,A27,A28,A29,A30,A31,B16, *
;*                           B17,B18,B19,B20,B21,B22,B23,B24,B25,B26,B27,B28, *
;*                           B29,B30,B31                                      *
;*   Regs Used         : A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,B0,B1,B2,B3,B4,*
;*                           B5,B6,B7,B8,B9,B10,B11,SP,A16,A17,A18,A19,A20,   *
;*                           A21,A22,A23,A24,A25,A26,A27,A28,A29,A30,A31,B16, *
;*                           B17,B18,B19,B20,B21,B22,B23,B24,B25,B26,B27,B28, *
;*                           B29,B30,B31                                      *
;*   Local Frame Size  : 0 Args + 0 Auto + 24 Save = 24 byte                  *
;******************************************************************************
_Task_create:
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 9
           MVKL    .S1     _MEM_valloc,A3    ; |34| 

           MVKH    .S1     _MEM_valloc,A3    ; |34| 
||         STW     .D2T1   A11,*SP--(8)      ; |26| 

           STDW    .D2T2   B11:B10,*SP--     ; |26| 
||         MV      .L2X    A4,B10            ; |26| 
||         MVKL    .S1     _DDR2,A4

$C$DW$72	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$72, DW_AT_low_pc(0x00)
	.dwattr $C$DW$72, DW_AT_name("_MEM_valloc")
	.dwattr $C$DW$72, DW_AT_TI_call

           CALL    .S2X    A3                ; |34| 
||         STW     .D2T1   A10,*SP--(8)      ; |26| 
||         MVKH    .S1     _DDR2,A4

           LDW     .D1T1   *A4,A4            ; |34| 
           MVK     .S2     0x28,B4           ; |34| 
           MV      .L2     B3,B11            ; |26| 
           ADDKPC  .S2     $C$RL7,B3,0       ; |34| 

           ZERO    .L1     A6                ; |34| 
||         ZERO    .L2     B6                ; |34| 

$C$RL7:    ; CALL OCCURS {_MEM_valloc} {0}   ; |34| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 14

           MVKL    .S2     _MPCSXFER_BufferSize,B4
||         MV      .L1     A4,A0             ; |37| 
||         ZERO    .D1     A10               ; |28| 
||         MVKL    .S1     __SEM_dopost,A3
||         STW     .D2T1   A4,*B10           ; |34| 
||         ZERO    .L2     B9                ; |50| 

           MVKH    .S2     _MPCSXFER_BufferSize,B4
|| [ A0]   MV      .L1     A0,A10            ; |43| 
||         MVKH    .S1     __SEM_dopost,A3
||         MVK     .D1     0x1,A4            ; |61| 
||         ZERO    .L2     B8                ; |50| 

           LDHU    .D2T2   *B4,B7            ; |48| 
||         MVK     .L2     0x1,B4            ; |39| 
||         MVKL    .S2     _Task_notify,B6   ; |61| 
||         MVK     .L1     0x5,A6            ; |61| 
||         ADD     .D1     A10,24,A5         ; |87| 
||         MV      .S1     A10,A8            ; |61| 

           MVKH    .S2     _Task_notify,B6   ; |61| 

           MV      .L1X    B4,A11            ; |48| 
||         MVKL    .S2     _NOTIFY_register,B5 ; |61| 
||         ZERO    .L2     B4                ; |50| 

   [ A0]   ZERO    .L1     A11               ; |27| 
||         MVKH    .S2     _NOTIFY_register,B5 ; |61| 

           MV      .L1     A11,A0            ; |61| 

   [ A0]   MVKL    .S1     _NOTIFY_notify,A3 ; |78| 
|| [ A0]   MVK     .L1     0x5,A6            ; |78| 
|| [ A0]   MVK     .D1     0x1,A4            ; |78| 
|| [ A0]   ZERO    .L2     B4                ; |78| 
|| [ A0]   ZERO    .S2     B6                ; |78| 

   [ A0]   B       .S2     $C$L13            ; |48| 
|| [ A0]   MVKH    .S1     _NOTIFY_notify,A3 ; |78| 
|| [!A0]   STW     .D1T2   B9,*+A10(20)      ; |86| 

   [ A0]   BNOP    .S1     $C$L15,3          ; |76| 
$C$DW$73	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$73, DW_AT_low_pc(0x00)
	.dwattr $C$DW$73, DW_AT_name("_NOTIFY_register")
	.dwattr $C$DW$73, DW_AT_TI_call

   [!A0]   CALL    .S2     B5                ; |61| 
|| [!A0]   STW     .D1T2   B7,*+A10(36)      ; |51| 

           ; BRANCHCC OCCURS {$C$L13}        ; |48| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           STW     .D1T2   B8,*A10           ; |50| 
           STW     .D1T1   A3,*+A10(16)      ; |89| 
           STW     .D1T2   B9,*+A10(12)      ; |88| 
           STW     .D1T1   A5,*+A10(24)      ; |87| 

           STW     .D1T1   A5,*+A10(28)      ; |87| 
||         ADDKPC  .S2     $C$RL8,B3,0       ; |61| 

$C$RL8:    ; CALL OCCURS {_NOTIFY_register} {0}  ; |61| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           MV      .L1     A4,A0             ; |61| 
||         MV      .S1     A4,A11            ; |61| 

   [ A0]   BNOP    .S2     $C$L14,4          ; |61| 
|| [!A0]   MVKL    .S1     _NOTIFY_notify,A3 ; |78| 
|| [!A0]   MVK     .L1     0x1,A4            ; |78| 
|| [!A0]   ZERO    .L2     B6                ; |78| 
|| [!A0]   ZERO    .D2     B4                ; |78| 
|| [!A0]   MVK     .D1     0x5,A6            ; |78| 

   [!A0]   MVKH    .S1     _NOTIFY_notify,A3 ; |78| 
           ; BRANCHCC OCCURS {$C$L14}        ; |61| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
   [ A0]   BNOP    .S1     $C$L15,4          ; |76| 
;** --------------------------------------------------------------------------*
$C$L13:    
;          EXCLUSIVE CPU CYCLES: 1
$C$DW$74	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$74, DW_AT_low_pc(0x00)
	.dwattr $C$DW$74, DW_AT_name("_NOTIFY_notify")
	.dwattr $C$DW$74, DW_AT_TI_call
   [!A0]   CALL    .S2X    A3                ; |78| 
           ; BRANCHCC OCCURS {$C$L15}        ; |76| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 5
           ADDKPC  .S2     $C$RL9,B3,4       ; |78| 
$C$RL9:    ; CALL OCCURS {_NOTIFY_notify} {0}  ; |78| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           MVKL    .S1     _SEM_pend,A3      ; |92| 
||         MV      .L1     A4,A0             ; |78| 

   [!A0]   BNOP    .S2     $C$L16,1          ; |78| 
||         MVKH    .S1     _SEM_pend,A3      ; |92| 

$C$DW$75	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$75, DW_AT_low_pc(0x00)
	.dwattr $C$DW$75, DW_AT_name("_SEM_pend")
	.dwattr $C$DW$75, DW_AT_TI_call
   [!A0]   CALL    .S2X    A3                ; |92| 
           MV      .L1     A4,A11            ; |78| 
           NOP             2
           ; BRANCHCC OCCURS {$C$L16}        ; |78| 
;** --------------------------------------------------------------------------*
$C$L14:    
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T1   *++SP(8),A10      ; |96| 
||         MV      .L2     B11,B3            ; |96| 

$C$DW$76	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$76, DW_AT_low_pc(0x04)
	.dwattr $C$DW$76, DW_AT_TI_return

           LDDW    .D2T2   *++SP,B11:B10     ; |96| 
||         RET     .S2     B3                ; |96| 

           LDW     .D2T1   *++SP(8),A11      ; |96| 
           NOP             4
           ; BRANCH OCCURS {B3}              ; |96| 
;** --------------------------------------------------------------------------*
$C$L15:    
;          EXCLUSIVE CPU CYCLES: 7
           MVKL    .S1     _SEM_pend,A3      ; |92| 
           MVKH    .S1     _SEM_pend,A3      ; |92| 
           NOP             1
$C$DW$77	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$77, DW_AT_low_pc(0x00)
	.dwattr $C$DW$77, DW_AT_name("_SEM_pend")
	.dwattr $C$DW$77, DW_AT_TI_call
           CALL    .S2X    A3                ; |92| 
           NOP             3
;** --------------------------------------------------------------------------*
$C$L16:    
;          EXCLUSIVE CPU CYCLES: 2
           ADD     .L1     4,A10,A4          ; |92| 

           ADD     .L1     4,A10,A10         ; |92| 
||         MVK     .L2     0xffffffff,B4     ; |92| 
||         ADDKPC  .S2     $C$RL10,B3,0      ; |92| 

$C$RL10:   ; CALL OCCURS {_SEM_pend} {0}     ; |92| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 8
           MVKL    .S2     _SEM_pend,B5      ; |93| 
           MVKH    .S2     _SEM_pend,B5      ; |93| 
$C$DW$78	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$78, DW_AT_low_pc(0x00)
	.dwattr $C$DW$78, DW_AT_name("_SEM_pend")
	.dwattr $C$DW$78, DW_AT_TI_call
           CALL    .S2     B5                ; |93| 
           ADDKPC  .S2     $C$RL11,B3,3      ; |93| 

           MV      .L1     A10,A4            ; |93| 
||         MVK     .L2     0xffffffff,B4     ; |93| 

$C$RL11:   ; CALL OCCURS {_SEM_pend} {0}     ; |93| 
;** --------------------------------------------------------------------------*
;          EXCLUSIVE CPU CYCLES: 7

           LDW     .D2T1   *++SP(8),A10      ; |96| 
||         MV      .L2     B11,B3            ; |96| 

$C$DW$79	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$79, DW_AT_low_pc(0x04)
	.dwattr $C$DW$79, DW_AT_TI_return

           LDDW    .D2T2   *++SP,B11:B10     ; |96| 
||         RET     .S2     B3                ; |96| 

           MV      .L1     A11,A4            ; |93| 
||         LDW     .D2T1   *++SP(8),A11      ; |96| 

	.dwpsn	file "task.c",line 96,column 1,is_stmt
           NOP             4
           ; BRANCH OCCURS {B3}              ; |96| 
	.dwattr $C$DW$70, DW_AT_TI_end_file("task.c")
	.dwattr $C$DW$70, DW_AT_TI_end_line(0x60)
	.dwattr $C$DW$70, DW_AT_TI_end_column(0x01)
	.dwendtag $C$DW$70

;*****************************************************************************
;* UNDEFINED EXTERNAL REFERENCES                                             *
;*****************************************************************************
	.global	_MEM_free
	.global	_MEM_valloc
	.global	_SEM_pend
	.global	_SEM_post
	.global	__SEM_dopost
	.global	_NOTIFY_register
	.global	_NOTIFY_unregister
	.global	_NOTIFY_notify
	.global	_BCACHE_inv
	.global	_DDR2
	.global	_MPCSXFER_BufferSize

;******************************************************************************
;* TYPE INFORMATION                                                           *
;******************************************************************************
$C$DW$T$3	.dwtag  DW_TAG_pointer_type
	.dwattr $C$DW$T$3, DW_AT_address_class(0x20)
$C$DW$T$39	.dwtag  DW_TAG_typedef, DW_AT_name("Ptr")
	.dwattr $C$DW$T$39, DW_AT_type(*$C$DW$T$3)
	.dwattr $C$DW$T$39, DW_AT_language(DW_LANG_C)

$C$DW$T$25	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$25, DW_AT_language(DW_LANG_C)
$C$DW$80	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$80, DW_AT_type(*$C$DW$T$24)
	.dwendtag $C$DW$T$25

$C$DW$T$26	.dwtag  DW_TAG_pointer_type
	.dwattr $C$DW$T$26, DW_AT_type(*$C$DW$T$25)
	.dwattr $C$DW$T$26, DW_AT_address_class(0x20)
$C$DW$T$27	.dwtag  DW_TAG_typedef, DW_AT_name("KNL_Fxn")
	.dwattr $C$DW$T$27, DW_AT_type(*$C$DW$T$26)
	.dwattr $C$DW$T$27, DW_AT_language(DW_LANG_C)

$C$DW$T$54	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$54, DW_AT_language(DW_LANG_C)
$C$DW$81	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$81, DW_AT_type(*$C$DW$T$37)
$C$DW$82	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$82, DW_AT_type(*$C$DW$T$39)
$C$DW$83	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$83, DW_AT_type(*$C$DW$T$39)
	.dwendtag $C$DW$T$54

$C$DW$T$55	.dwtag  DW_TAG_pointer_type
	.dwattr $C$DW$T$55, DW_AT_type(*$C$DW$T$54)
	.dwattr $C$DW$T$55, DW_AT_address_class(0x20)
$C$DW$T$56	.dwtag  DW_TAG_typedef, DW_AT_name("FnNotifyCbck")
	.dwattr $C$DW$T$56, DW_AT_type(*$C$DW$T$55)
	.dwattr $C$DW$T$56, DW_AT_language(DW_LANG_C)
$C$DW$T$4	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$4, DW_AT_encoding(DW_ATE_boolean)
	.dwattr $C$DW$T$4, DW_AT_name("bool")
	.dwattr $C$DW$T$4, DW_AT_byte_size(0x01)
$C$DW$T$5	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$5, DW_AT_encoding(DW_ATE_signed_char)
	.dwattr $C$DW$T$5, DW_AT_name("signed char")
	.dwattr $C$DW$T$5, DW_AT_byte_size(0x01)
$C$DW$T$6	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$6, DW_AT_encoding(DW_ATE_unsigned_char)
	.dwattr $C$DW$T$6, DW_AT_name("unsigned char")
	.dwattr $C$DW$T$6, DW_AT_byte_size(0x01)
$C$DW$T$60	.dwtag  DW_TAG_pointer_type
	.dwattr $C$DW$T$60, DW_AT_type(*$C$DW$T$6)
	.dwattr $C$DW$T$60, DW_AT_address_class(0x20)
$C$DW$T$7	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$7, DW_AT_encoding(DW_ATE_signed_char)
	.dwattr $C$DW$T$7, DW_AT_name("wchar_t")
	.dwattr $C$DW$T$7, DW_AT_byte_size(0x02)
$C$DW$T$8	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$8, DW_AT_encoding(DW_ATE_signed)
	.dwattr $C$DW$T$8, DW_AT_name("short")
	.dwattr $C$DW$T$8, DW_AT_byte_size(0x02)
$C$DW$T$9	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$9, DW_AT_encoding(DW_ATE_unsigned)
	.dwattr $C$DW$T$9, DW_AT_name("unsigned short")
	.dwattr $C$DW$T$9, DW_AT_byte_size(0x02)
$C$DW$T$34	.dwtag  DW_TAG_typedef, DW_AT_name("Uint16")
	.dwattr $C$DW$T$34, DW_AT_type(*$C$DW$T$9)
	.dwattr $C$DW$T$34, DW_AT_language(DW_LANG_C)
$C$DW$T$35	.dwtag  DW_TAG_pointer_type
	.dwattr $C$DW$T$35, DW_AT_type(*$C$DW$T$34)
	.dwattr $C$DW$T$35, DW_AT_address_class(0x20)
$C$DW$T$57	.dwtag  DW_TAG_typedef, DW_AT_name("Bool")
	.dwattr $C$DW$T$57, DW_AT_type(*$C$DW$T$9)
	.dwattr $C$DW$T$57, DW_AT_language(DW_LANG_C)
$C$DW$T$10	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$10, DW_AT_encoding(DW_ATE_signed)
	.dwattr $C$DW$T$10, DW_AT_name("int")
	.dwattr $C$DW$T$10, DW_AT_byte_size(0x04)
$C$DW$T$22	.dwtag  DW_TAG_typedef, DW_AT_name("Int")
	.dwattr $C$DW$T$22, DW_AT_type(*$C$DW$T$10)
	.dwattr $C$DW$T$22, DW_AT_language(DW_LANG_C)
$C$DW$T$11	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$11, DW_AT_encoding(DW_ATE_unsigned)
	.dwattr $C$DW$T$11, DW_AT_name("unsigned int")
	.dwattr $C$DW$T$11, DW_AT_byte_size(0x04)
$C$DW$T$37	.dwtag  DW_TAG_typedef, DW_AT_name("Uint32")
	.dwattr $C$DW$T$37, DW_AT_type(*$C$DW$T$11)
	.dwattr $C$DW$T$37, DW_AT_language(DW_LANG_C)
$C$DW$T$40	.dwtag  DW_TAG_typedef, DW_AT_name("size_t")
	.dwattr $C$DW$T$40, DW_AT_type(*$C$DW$T$11)
	.dwattr $C$DW$T$40, DW_AT_language(DW_LANG_C)
$C$DW$T$65	.dwtag  DW_TAG_typedef, DW_AT_name("Uns")
	.dwattr $C$DW$T$65, DW_AT_type(*$C$DW$T$11)
	.dwattr $C$DW$T$65, DW_AT_language(DW_LANG_C)
$C$DW$T$12	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$12, DW_AT_encoding(DW_ATE_signed)
	.dwattr $C$DW$T$12, DW_AT_name("long")
	.dwattr $C$DW$T$12, DW_AT_byte_size(0x08)
	.dwattr $C$DW$T$12, DW_AT_bit_size(0x28)
	.dwattr $C$DW$T$12, DW_AT_bit_offset(0x18)
$C$DW$T$13	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$13, DW_AT_encoding(DW_ATE_unsigned)
	.dwattr $C$DW$T$13, DW_AT_name("unsigned long")
	.dwattr $C$DW$T$13, DW_AT_byte_size(0x08)
	.dwattr $C$DW$T$13, DW_AT_bit_size(0x28)
	.dwattr $C$DW$T$13, DW_AT_bit_offset(0x18)
$C$DW$T$14	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$14, DW_AT_encoding(DW_ATE_signed)
	.dwattr $C$DW$T$14, DW_AT_name("long long")
	.dwattr $C$DW$T$14, DW_AT_byte_size(0x08)
$C$DW$T$15	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$15, DW_AT_encoding(DW_ATE_unsigned)
	.dwattr $C$DW$T$15, DW_AT_name("unsigned long long")
	.dwattr $C$DW$T$15, DW_AT_byte_size(0x08)
$C$DW$T$16	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$16, DW_AT_encoding(DW_ATE_float)
	.dwattr $C$DW$T$16, DW_AT_name("float")
	.dwattr $C$DW$T$16, DW_AT_byte_size(0x04)
$C$DW$T$17	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$17, DW_AT_encoding(DW_ATE_float)
	.dwattr $C$DW$T$17, DW_AT_name("double")
	.dwattr $C$DW$T$17, DW_AT_byte_size(0x08)
$C$DW$T$18	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$18, DW_AT_encoding(DW_ATE_float)
	.dwattr $C$DW$T$18, DW_AT_name("long double")
	.dwattr $C$DW$T$18, DW_AT_byte_size(0x08)

$C$DW$T$20	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$20, DW_AT_name("QUE_Elem")
	.dwattr $C$DW$T$20, DW_AT_byte_size(0x08)
$C$DW$84	.dwtag  DW_TAG_member
	.dwattr $C$DW$84, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$84, DW_AT_name("next")
	.dwattr $C$DW$84, DW_AT_TI_symbol_name("_next")
	.dwattr $C$DW$84, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$84, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$85	.dwtag  DW_TAG_member
	.dwattr $C$DW$85, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$85, DW_AT_name("prev")
	.dwattr $C$DW$85, DW_AT_TI_symbol_name("_prev")
	.dwattr $C$DW$85, DW_AT_data_member_location[DW_OP_plus_uconst 0x4]
	.dwattr $C$DW$85, DW_AT_accessibility(DW_ACCESS_public)
	.dwendtag $C$DW$T$20

$C$DW$T$19	.dwtag  DW_TAG_pointer_type
	.dwattr $C$DW$T$19, DW_AT_type(*$C$DW$T$20)
	.dwattr $C$DW$T$19, DW_AT_address_class(0x20)
$C$DW$T$21	.dwtag  DW_TAG_typedef, DW_AT_name("QUE_Obj")
	.dwattr $C$DW$T$21, DW_AT_type(*$C$DW$T$20)
	.dwattr $C$DW$T$21, DW_AT_language(DW_LANG_C)

$C$DW$T$28	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$28, DW_AT_name("KNL_Job")
	.dwattr $C$DW$T$28, DW_AT_byte_size(0x10)
$C$DW$86	.dwtag  DW_TAG_member
	.dwattr $C$DW$86, DW_AT_type(*$C$DW$T$21)
	.dwattr $C$DW$86, DW_AT_name("wListElem")
	.dwattr $C$DW$86, DW_AT_TI_symbol_name("_wListElem")
	.dwattr $C$DW$86, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$86, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$87	.dwtag  DW_TAG_member
	.dwattr $C$DW$87, DW_AT_type(*$C$DW$T$22)
	.dwattr $C$DW$87, DW_AT_name("wCount")
	.dwattr $C$DW$87, DW_AT_TI_symbol_name("_wCount")
	.dwattr $C$DW$87, DW_AT_data_member_location[DW_OP_plus_uconst 0x8]
	.dwattr $C$DW$87, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$88	.dwtag  DW_TAG_member
	.dwattr $C$DW$88, DW_AT_type(*$C$DW$T$27)
	.dwattr $C$DW$88, DW_AT_name("fxn")
	.dwattr $C$DW$88, DW_AT_TI_symbol_name("_fxn")
	.dwattr $C$DW$88, DW_AT_data_member_location[DW_OP_plus_uconst 0xc]
	.dwattr $C$DW$88, DW_AT_accessibility(DW_ACCESS_public)
	.dwendtag $C$DW$T$28

$C$DW$T$23	.dwtag  DW_TAG_pointer_type
	.dwattr $C$DW$T$23, DW_AT_type(*$C$DW$T$28)
	.dwattr $C$DW$T$23, DW_AT_address_class(0x20)
$C$DW$T$24	.dwtag  DW_TAG_typedef, DW_AT_name("KNL_JobHandle")
	.dwattr $C$DW$T$24, DW_AT_type(*$C$DW$T$23)
	.dwattr $C$DW$T$24, DW_AT_language(DW_LANG_C)
$C$DW$T$29	.dwtag  DW_TAG_typedef, DW_AT_name("KNL_Job")
	.dwattr $C$DW$T$29, DW_AT_type(*$C$DW$T$28)
	.dwattr $C$DW$T$29, DW_AT_language(DW_LANG_C)
$C$DW$T$30	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$30, DW_AT_encoding(DW_ATE_signed_char)
	.dwattr $C$DW$T$30, DW_AT_name("signed char")
	.dwattr $C$DW$T$30, DW_AT_byte_size(0x01)
$C$DW$T$31	.dwtag  DW_TAG_pointer_type
	.dwattr $C$DW$T$31, DW_AT_type(*$C$DW$T$30)
	.dwattr $C$DW$T$31, DW_AT_address_class(0x20)
$C$DW$T$32	.dwtag  DW_TAG_typedef, DW_AT_name("String")
	.dwattr $C$DW$T$32, DW_AT_type(*$C$DW$T$31)
	.dwattr $C$DW$T$32, DW_AT_language(DW_LANG_C)
$C$DW$T$41	.dwtag  DW_TAG_typedef, DW_AT_name("Char")
	.dwattr $C$DW$T$41, DW_AT_type(*$C$DW$T$30)
	.dwattr $C$DW$T$41, DW_AT_language(DW_LANG_C)

$C$DW$T$33	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$33, DW_AT_name("SEM_Obj")
	.dwattr $C$DW$T$33, DW_AT_byte_size(0x20)
$C$DW$89	.dwtag  DW_TAG_member
	.dwattr $C$DW$89, DW_AT_type(*$C$DW$T$29)
	.dwattr $C$DW$89, DW_AT_name("job")
	.dwattr $C$DW$89, DW_AT_TI_symbol_name("_job")
	.dwattr $C$DW$89, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$89, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$90	.dwtag  DW_TAG_member
	.dwattr $C$DW$90, DW_AT_type(*$C$DW$T$22)
	.dwattr $C$DW$90, DW_AT_name("count")
	.dwattr $C$DW$90, DW_AT_TI_symbol_name("_count")
	.dwattr $C$DW$90, DW_AT_data_member_location[DW_OP_plus_uconst 0x10]
	.dwattr $C$DW$90, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$91	.dwtag  DW_TAG_member
	.dwattr $C$DW$91, DW_AT_type(*$C$DW$T$21)
	.dwattr $C$DW$91, DW_AT_name("pendQ")
	.dwattr $C$DW$91, DW_AT_TI_symbol_name("_pendQ")
	.dwattr $C$DW$91, DW_AT_data_member_location[DW_OP_plus_uconst 0x14]
	.dwattr $C$DW$91, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$92	.dwtag  DW_TAG_member
	.dwattr $C$DW$92, DW_AT_type(*$C$DW$T$32)
	.dwattr $C$DW$92, DW_AT_name("name")
	.dwattr $C$DW$92, DW_AT_TI_symbol_name("_name")
	.dwattr $C$DW$92, DW_AT_data_member_location[DW_OP_plus_uconst 0x1c]
	.dwattr $C$DW$92, DW_AT_accessibility(DW_ACCESS_public)
	.dwendtag $C$DW$T$33

$C$DW$T$36	.dwtag  DW_TAG_typedef, DW_AT_name("SEM_Obj")
	.dwattr $C$DW$T$36, DW_AT_type(*$C$DW$T$33)
	.dwattr $C$DW$T$36, DW_AT_language(DW_LANG_C)
$C$DW$T$49	.dwtag  DW_TAG_pointer_type
	.dwattr $C$DW$T$49, DW_AT_type(*$C$DW$T$33)
	.dwattr $C$DW$T$49, DW_AT_address_class(0x20)
$C$DW$T$50	.dwtag  DW_TAG_typedef, DW_AT_name("SEM_Handle")
	.dwattr $C$DW$T$50, DW_AT_type(*$C$DW$T$49)
	.dwattr $C$DW$T$50, DW_AT_language(DW_LANG_C)

$C$DW$T$38	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$38, DW_AT_name("Task_TransferInfo_tag")
	.dwattr $C$DW$T$38, DW_AT_byte_size(0x28)
$C$DW$93	.dwtag  DW_TAG_member
	.dwattr $C$DW$93, DW_AT_type(*$C$DW$T$35)
	.dwattr $C$DW$93, DW_AT_name("dataBuf")
	.dwattr $C$DW$93, DW_AT_TI_symbol_name("_dataBuf")
	.dwattr $C$DW$93, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$93, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$94	.dwtag  DW_TAG_member
	.dwattr $C$DW$94, DW_AT_type(*$C$DW$T$36)
	.dwattr $C$DW$94, DW_AT_name("notifySemObj")
	.dwattr $C$DW$94, DW_AT_TI_symbol_name("_notifySemObj")
	.dwattr $C$DW$94, DW_AT_data_member_location[DW_OP_plus_uconst 0x4]
	.dwattr $C$DW$94, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$95	.dwtag  DW_TAG_member
	.dwattr $C$DW$95, DW_AT_type(*$C$DW$T$37)
	.dwattr $C$DW$95, DW_AT_name("bufferSize")
	.dwattr $C$DW$95, DW_AT_TI_symbol_name("_bufferSize")
	.dwattr $C$DW$95, DW_AT_data_member_location[DW_OP_plus_uconst 0x24]
	.dwattr $C$DW$95, DW_AT_accessibility(DW_ACCESS_public)
	.dwendtag $C$DW$T$38

$C$DW$T$74	.dwtag  DW_TAG_typedef, DW_AT_name("Task_TransferInfo")
	.dwattr $C$DW$T$74, DW_AT_type(*$C$DW$T$38)
	.dwattr $C$DW$T$74, DW_AT_language(DW_LANG_C)
$C$DW$T$75	.dwtag  DW_TAG_pointer_type
	.dwattr $C$DW$T$75, DW_AT_type(*$C$DW$T$74)
	.dwattr $C$DW$T$75, DW_AT_address_class(0x20)
$C$DW$T$76	.dwtag  DW_TAG_pointer_type
	.dwattr $C$DW$T$76, DW_AT_type(*$C$DW$T$75)
	.dwattr $C$DW$T$76, DW_AT_address_class(0x20)
	.dwattr $C$DW$CU, DW_AT_language(DW_LANG_C)

;***************************************************************
;* DWARF REGISTER MAP                                          *
;***************************************************************

$C$DW$96	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A0")
	.dwattr $C$DW$96, DW_AT_location[DW_OP_reg0]
$C$DW$97	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A1")
	.dwattr $C$DW$97, DW_AT_location[DW_OP_reg1]
$C$DW$98	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A2")
	.dwattr $C$DW$98, DW_AT_location[DW_OP_reg2]
$C$DW$99	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A3")
	.dwattr $C$DW$99, DW_AT_location[DW_OP_reg3]
$C$DW$100	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A4")
	.dwattr $C$DW$100, DW_AT_location[DW_OP_reg4]
$C$DW$101	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A5")
	.dwattr $C$DW$101, DW_AT_location[DW_OP_reg5]
$C$DW$102	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A6")
	.dwattr $C$DW$102, DW_AT_location[DW_OP_reg6]
$C$DW$103	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A7")
	.dwattr $C$DW$103, DW_AT_location[DW_OP_reg7]
$C$DW$104	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A8")
	.dwattr $C$DW$104, DW_AT_location[DW_OP_reg8]
$C$DW$105	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A9")
	.dwattr $C$DW$105, DW_AT_location[DW_OP_reg9]
$C$DW$106	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A10")
	.dwattr $C$DW$106, DW_AT_location[DW_OP_reg10]
$C$DW$107	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A11")
	.dwattr $C$DW$107, DW_AT_location[DW_OP_reg11]
$C$DW$108	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A12")
	.dwattr $C$DW$108, DW_AT_location[DW_OP_reg12]
$C$DW$109	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A13")
	.dwattr $C$DW$109, DW_AT_location[DW_OP_reg13]
$C$DW$110	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A14")
	.dwattr $C$DW$110, DW_AT_location[DW_OP_reg14]
$C$DW$111	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A15")
	.dwattr $C$DW$111, DW_AT_location[DW_OP_reg15]
$C$DW$112	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("B0")
	.dwattr $C$DW$112, DW_AT_location[DW_OP_reg16]
$C$DW$113	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("B1")
	.dwattr $C$DW$113, DW_AT_location[DW_OP_reg17]
$C$DW$114	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("B2")
	.dwattr $C$DW$114, DW_AT_location[DW_OP_reg18]
$C$DW$115	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("B3")
	.dwattr $C$DW$115, DW_AT_location[DW_OP_reg19]
$C$DW$116	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("B4")
	.dwattr $C$DW$116, DW_AT_location[DW_OP_reg20]
$C$DW$117	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("B5")
	.dwattr $C$DW$117, DW_AT_location[DW_OP_reg21]
$C$DW$118	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("B6")
	.dwattr $C$DW$118, DW_AT_location[DW_OP_reg22]
$C$DW$119	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("B7")
	.dwattr $C$DW$119, DW_AT_location[DW_OP_reg23]
$C$DW$120	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("B8")
	.dwattr $C$DW$120, DW_AT_location[DW_OP_reg24]
$C$DW$121	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("B9")
	.dwattr $C$DW$121, DW_AT_location[DW_OP_reg25]
$C$DW$122	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("B10")
	.dwattr $C$DW$122, DW_AT_location[DW_OP_reg26]
$C$DW$123	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("B11")
	.dwattr $C$DW$123, DW_AT_location[DW_OP_reg27]
$C$DW$124	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("B12")
	.dwattr $C$DW$124, DW_AT_location[DW_OP_reg28]
$C$DW$125	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("B13")
	.dwattr $C$DW$125, DW_AT_location[DW_OP_reg29]
$C$DW$126	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("DP")
	.dwattr $C$DW$126, DW_AT_location[DW_OP_reg30]
$C$DW$127	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("SP")
	.dwattr $C$DW$127, DW_AT_location[DW_OP_reg31]
$C$DW$128	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("FP")
	.dwattr $C$DW$128, DW_AT_location[DW_OP_regx 0x20]
$C$DW$129	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("PC")
	.dwattr $C$DW$129, DW_AT_location[DW_OP_regx 0x21]
$C$DW$130	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("IRP")
	.dwattr $C$DW$130, DW_AT_location[DW_OP_regx 0x22]
$C$DW$131	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("IFR")
	.dwattr $C$DW$131, DW_AT_location[DW_OP_regx 0x23]
$C$DW$132	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("NRP")
	.dwattr $C$DW$132, DW_AT_location[DW_OP_regx 0x24]
$C$DW$133	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A16")
	.dwattr $C$DW$133, DW_AT_location[DW_OP_regx 0x25]
$C$DW$134	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A17")
	.dwattr $C$DW$134, DW_AT_location[DW_OP_regx 0x26]
$C$DW$135	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A18")
	.dwattr $C$DW$135, DW_AT_location[DW_OP_regx 0x27]
$C$DW$136	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A19")
	.dwattr $C$DW$136, DW_AT_location[DW_OP_regx 0x28]
$C$DW$137	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A20")
	.dwattr $C$DW$137, DW_AT_location[DW_OP_regx 0x29]
$C$DW$138	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A21")
	.dwattr $C$DW$138, DW_AT_location[DW_OP_regx 0x2a]
$C$DW$139	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A22")
	.dwattr $C$DW$139, DW_AT_location[DW_OP_regx 0x2b]
$C$DW$140	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A23")
	.dwattr $C$DW$140, DW_AT_location[DW_OP_regx 0x2c]
$C$DW$141	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A24")
	.dwattr $C$DW$141, DW_AT_location[DW_OP_regx 0x2d]
$C$DW$142	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A25")
	.dwattr $C$DW$142, DW_AT_location[DW_OP_regx 0x2e]
$C$DW$143	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A26")
	.dwattr $C$DW$143, DW_AT_location[DW_OP_regx 0x2f]
$C$DW$144	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A27")
	.dwattr $C$DW$144, DW_AT_location[DW_OP_regx 0x30]
$C$DW$145	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A28")
	.dwattr $C$DW$145, DW_AT_location[DW_OP_regx 0x31]
$C$DW$146	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A29")
	.dwattr $C$DW$146, DW_AT_location[DW_OP_regx 0x32]
$C$DW$147	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A30")
	.dwattr $C$DW$147, DW_AT_location[DW_OP_regx 0x33]
$C$DW$148	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A31")
	.dwattr $C$DW$148, DW_AT_location[DW_OP_regx 0x34]
$C$DW$149	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("B16")
	.dwattr $C$DW$149, DW_AT_location[DW_OP_regx 0x35]
$C$DW$150	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("B17")
	.dwattr $C$DW$150, DW_AT_location[DW_OP_regx 0x36]
$C$DW$151	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("B18")
	.dwattr $C$DW$151, DW_AT_location[DW_OP_regx 0x37]
$C$DW$152	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("B19")
	.dwattr $C$DW$152, DW_AT_location[DW_OP_regx 0x38]
$C$DW$153	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("B20")
	.dwattr $C$DW$153, DW_AT_location[DW_OP_regx 0x39]
$C$DW$154	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("B21")
	.dwattr $C$DW$154, DW_AT_location[DW_OP_regx 0x3a]
$C$DW$155	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("B22")
	.dwattr $C$DW$155, DW_AT_location[DW_OP_regx 0x3b]
$C$DW$156	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("B23")
	.dwattr $C$DW$156, DW_AT_location[DW_OP_regx 0x3c]
$C$DW$157	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("B24")
	.dwattr $C$DW$157, DW_AT_location[DW_OP_regx 0x3d]
$C$DW$158	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("B25")
	.dwattr $C$DW$158, DW_AT_location[DW_OP_regx 0x3e]
$C$DW$159	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("B26")
	.dwattr $C$DW$159, DW_AT_location[DW_OP_regx 0x3f]
$C$DW$160	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("B27")
	.dwattr $C$DW$160, DW_AT_location[DW_OP_regx 0x40]
$C$DW$161	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("B28")
	.dwattr $C$DW$161, DW_AT_location[DW_OP_regx 0x41]
$C$DW$162	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("B29")
	.dwattr $C$DW$162, DW_AT_location[DW_OP_regx 0x42]
$C$DW$163	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("B30")
	.dwattr $C$DW$163, DW_AT_location[DW_OP_regx 0x43]
$C$DW$164	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("B31")
	.dwattr $C$DW$164, DW_AT_location[DW_OP_regx 0x44]
$C$DW$165	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("AMR")
	.dwattr $C$DW$165, DW_AT_location[DW_OP_regx 0x45]
$C$DW$166	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("CSR")
	.dwattr $C$DW$166, DW_AT_location[DW_OP_regx 0x46]
$C$DW$167	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("ISR")
	.dwattr $C$DW$167, DW_AT_location[DW_OP_regx 0x47]
$C$DW$168	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("ICR")
	.dwattr $C$DW$168, DW_AT_location[DW_OP_regx 0x48]
$C$DW$169	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("IER")
	.dwattr $C$DW$169, DW_AT_location[DW_OP_regx 0x49]
$C$DW$170	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("ISTP")
	.dwattr $C$DW$170, DW_AT_location[DW_OP_regx 0x4a]
$C$DW$171	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("IN")
	.dwattr $C$DW$171, DW_AT_location[DW_OP_regx 0x4b]
$C$DW$172	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("OUT")
	.dwattr $C$DW$172, DW_AT_location[DW_OP_regx 0x4c]
$C$DW$173	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("ACR")
	.dwattr $C$DW$173, DW_AT_location[DW_OP_regx 0x4d]
$C$DW$174	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("ADR")
	.dwattr $C$DW$174, DW_AT_location[DW_OP_regx 0x4e]
$C$DW$175	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("FADCR")
	.dwattr $C$DW$175, DW_AT_location[DW_OP_regx 0x4f]
$C$DW$176	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("FAUCR")
	.dwattr $C$DW$176, DW_AT_location[DW_OP_regx 0x50]
$C$DW$177	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("FMCR")
	.dwattr $C$DW$177, DW_AT_location[DW_OP_regx 0x51]
$C$DW$178	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("GFPGFR")
	.dwattr $C$DW$178, DW_AT_location[DW_OP_regx 0x52]
$C$DW$179	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("DIER")
	.dwattr $C$DW$179, DW_AT_location[DW_OP_regx 0x53]
$C$DW$180	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("REP")
	.dwattr $C$DW$180, DW_AT_location[DW_OP_regx 0x54]
$C$DW$181	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("TSCL")
	.dwattr $C$DW$181, DW_AT_location[DW_OP_regx 0x55]
$C$DW$182	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("TSCH")
	.dwattr $C$DW$182, DW_AT_location[DW_OP_regx 0x56]
$C$DW$183	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("ARP")
	.dwattr $C$DW$183, DW_AT_location[DW_OP_regx 0x57]
$C$DW$184	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("ILC")
	.dwattr $C$DW$184, DW_AT_location[DW_OP_regx 0x58]
$C$DW$185	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("RILC")
	.dwattr $C$DW$185, DW_AT_location[DW_OP_regx 0x59]
$C$DW$186	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("DNUM")
	.dwattr $C$DW$186, DW_AT_location[DW_OP_regx 0x5a]
$C$DW$187	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("SSR")
	.dwattr $C$DW$187, DW_AT_location[DW_OP_regx 0x5b]
$C$DW$188	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("GPLYA")
	.dwattr $C$DW$188, DW_AT_location[DW_OP_regx 0x5c]
$C$DW$189	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("GPLYB")
	.dwattr $C$DW$189, DW_AT_location[DW_OP_regx 0x5d]
$C$DW$190	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("TSR")
	.dwattr $C$DW$190, DW_AT_location[DW_OP_regx 0x5e]
$C$DW$191	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("ITSR")
	.dwattr $C$DW$191, DW_AT_location[DW_OP_regx 0x5f]
$C$DW$192	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("NTSR")
	.dwattr $C$DW$192, DW_AT_location[DW_OP_regx 0x60]
$C$DW$193	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("EFR")
	.dwattr $C$DW$193, DW_AT_location[DW_OP_regx 0x61]
$C$DW$194	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("ECR")
	.dwattr $C$DW$194, DW_AT_location[DW_OP_regx 0x62]
$C$DW$195	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("IERR")
	.dwattr $C$DW$195, DW_AT_location[DW_OP_regx 0x63]
$C$DW$196	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("DMSG")
	.dwattr $C$DW$196, DW_AT_location[DW_OP_regx 0x64]
$C$DW$197	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("CMSG")
	.dwattr $C$DW$197, DW_AT_location[DW_OP_regx 0x65]
$C$DW$198	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("DT_DMA_ADDR")
	.dwattr $C$DW$198, DW_AT_location[DW_OP_regx 0x66]
$C$DW$199	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("DT_DMA_DATA")
	.dwattr $C$DW$199, DW_AT_location[DW_OP_regx 0x67]
$C$DW$200	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("DT_DMA_CNTL")
	.dwattr $C$DW$200, DW_AT_location[DW_OP_regx 0x68]
$C$DW$201	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("TCU_CNTL")
	.dwattr $C$DW$201, DW_AT_location[DW_OP_regx 0x69]
$C$DW$202	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("RTDX_REC_CNTL")
	.dwattr $C$DW$202, DW_AT_location[DW_OP_regx 0x6a]
$C$DW$203	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("RTDX_XMT_CNTL")
	.dwattr $C$DW$203, DW_AT_location[DW_OP_regx 0x6b]
$C$DW$204	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("RTDX_CFG")
	.dwattr $C$DW$204, DW_AT_location[DW_OP_regx 0x6c]
$C$DW$205	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("RTDX_RDATA")
	.dwattr $C$DW$205, DW_AT_location[DW_OP_regx 0x6d]
$C$DW$206	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("RTDX_WDATA")
	.dwattr $C$DW$206, DW_AT_location[DW_OP_regx 0x6e]
$C$DW$207	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("RTDX_RADDR")
	.dwattr $C$DW$207, DW_AT_location[DW_OP_regx 0x6f]
$C$DW$208	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("RTDX_WADDR")
	.dwattr $C$DW$208, DW_AT_location[DW_OP_regx 0x70]
$C$DW$209	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("MFREG0")
	.dwattr $C$DW$209, DW_AT_location[DW_OP_regx 0x71]
$C$DW$210	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("DBG_STAT")
	.dwattr $C$DW$210, DW_AT_location[DW_OP_regx 0x72]
$C$DW$211	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("BRK_EN")
	.dwattr $C$DW$211, DW_AT_location[DW_OP_regx 0x73]
$C$DW$212	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("HWBP0_CNT")
	.dwattr $C$DW$212, DW_AT_location[DW_OP_regx 0x74]
$C$DW$213	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("HWBP0")
	.dwattr $C$DW$213, DW_AT_location[DW_OP_regx 0x75]
$C$DW$214	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("HWBP1")
	.dwattr $C$DW$214, DW_AT_location[DW_OP_regx 0x76]
$C$DW$215	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("HWBP2")
	.dwattr $C$DW$215, DW_AT_location[DW_OP_regx 0x77]
$C$DW$216	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("HWBP3")
	.dwattr $C$DW$216, DW_AT_location[DW_OP_regx 0x78]
$C$DW$217	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("OVERLAY")
	.dwattr $C$DW$217, DW_AT_location[DW_OP_regx 0x79]
$C$DW$218	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("PC_PROF")
	.dwattr $C$DW$218, DW_AT_location[DW_OP_regx 0x7a]
$C$DW$219	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("ATSR")
	.dwattr $C$DW$219, DW_AT_location[DW_OP_regx 0x7b]
$C$DW$220	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("TRR")
	.dwattr $C$DW$220, DW_AT_location[DW_OP_regx 0x7c]
$C$DW$221	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("TCRR")
	.dwattr $C$DW$221, DW_AT_location[DW_OP_regx 0x7d]
$C$DW$222	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("DESR")
	.dwattr $C$DW$222, DW_AT_location[DW_OP_regx 0x7e]
$C$DW$223	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("DETR")
	.dwattr $C$DW$223, DW_AT_location[DW_OP_regx 0x7f]
$C$DW$224	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("CIE_RETA")
	.dwattr $C$DW$224, DW_AT_location[DW_OP_regx 0xe4]
	.dwendtag $C$DW$CU

