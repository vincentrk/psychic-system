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
	.dwattr $C$DW$CU, DW_AT_name("pool_notify_config.c")
	.dwattr $C$DW$CU, DW_AT_producer("TMS320C6x C/C++ Codegen Unix v6.1.17 Copyright (c) 1996-2010 Texas Instruments Incorporated")
	.dwattr $C$DW$CU, DW_AT_TI_version(0x01)
	.dwattr $C$DW$CU, DW_AT_comp_dir("/data/home/in4342-admin/esLab/helperExamples/pool_notify/dsp")
;*****************************************************************************
;* CINIT RECORDS                                                             *
;*****************************************************************************
	.sect	".cinit"
	.align	8
	.field  	$C$IR_1,32
	.field  	_SamplePoolParams+0,32
	.field  	0,16			; _SamplePoolParams._poolId @ 0
	.field  	1,16			; _SamplePoolParams._exactMatchReq @ 16
$C$IR_1:	.set	4

	.sect	".cinit"
	.align	8
	.field  	$C$IR_2,32
	.field  	_pool_notify_Pools+0,32
	.field  	_SMAPOOL_init,32		; _pool_notify_Pools[0]._initFxn @ 0
	.field  	_SMAPOOL_FXNS,32		; _pool_notify_Pools[0]._fxns @ 32
	.field  	_SamplePoolParams,32		; _pool_notify_Pools[0]._params @ 64
	.field  	0,32			; _pool_notify_Pools[0]._object @ 96
$C$IR_2:	.set	16

	.sect	".cinit"
	.align	8
	.field  	$C$IR_3,32
	.field  	_POOL_config+0,32
	.field  	_pool_notify_Pools,32		; _POOL_config._allocators @ 0
	.field  	1,16			; _POOL_config._numAllocators @ 32
$C$IR_3:	.set	6


$C$DW$1	.dwtag  DW_TAG_subprogram, DW_AT_name("SMAPOOL_init")
	.dwattr $C$DW$1, DW_AT_TI_symbol_name("_SMAPOOL_init")
	.dwattr $C$DW$1, DW_AT_declaration
	.dwattr $C$DW$1, DW_AT_external
$C$DW$2	.dwtag  DW_TAG_variable, DW_AT_name("SMAPOOL_FXNS")
	.dwattr $C$DW$2, DW_AT_TI_symbol_name("_SMAPOOL_FXNS")
	.dwattr $C$DW$2, DW_AT_type(*$C$DW$T$50)
	.dwattr $C$DW$2, DW_AT_declaration
	.dwattr $C$DW$2, DW_AT_external
	.global	_SamplePoolParams
_SamplePoolParams:	.usect	".far",4,2
$C$DW$3	.dwtag  DW_TAG_variable, DW_AT_name("SamplePoolParams")
	.dwattr $C$DW$3, DW_AT_TI_symbol_name("_SamplePoolParams")
	.dwattr $C$DW$3, DW_AT_location[DW_OP_addr _SamplePoolParams]
	.dwattr $C$DW$3, DW_AT_type(*$C$DW$T$52)
	.dwattr $C$DW$3, DW_AT_external
	.global	_pool_notify_Pools
_pool_notify_Pools:	.usect	".far",16,8
$C$DW$4	.dwtag  DW_TAG_variable, DW_AT_name("pool_notify_Pools")
	.dwattr $C$DW$4, DW_AT_TI_symbol_name("_pool_notify_Pools")
	.dwattr $C$DW$4, DW_AT_location[DW_OP_addr _pool_notify_Pools]
	.dwattr $C$DW$4, DW_AT_type(*$C$DW$T$54)
	.dwattr $C$DW$4, DW_AT_external
	.global	_POOL_config
_POOL_config:	.usect	".far",8,4
$C$DW$5	.dwtag  DW_TAG_variable, DW_AT_name("POOL_config")
	.dwattr $C$DW$5, DW_AT_TI_symbol_name("_POOL_config")
	.dwattr $C$DW$5, DW_AT_location[DW_OP_addr _POOL_config]
	.dwattr $C$DW$5, DW_AT_type(*$C$DW$T$55)
	.dwattr $C$DW$5, DW_AT_external
;	/data/bbToolChain/usr/local/share/c6000/bin/opt6x /tmp/18222XhEr8F /tmp/18222RvQU4H 
;*****************************************************************************
;* UNDEFINED EXTERNAL REFERENCES                                             *
;*****************************************************************************
	.global	_SMAPOOL_init
	.global	_SMAPOOL_FXNS

;******************************************************************************
;* TYPE INFORMATION                                                           *
;******************************************************************************
$C$DW$T$3	.dwtag  DW_TAG_pointer_type
	.dwattr $C$DW$T$3, DW_AT_address_class(0x20)
$C$DW$T$20	.dwtag  DW_TAG_typedef, DW_AT_name("Ptr")
	.dwattr $C$DW$T$20, DW_AT_type(*$C$DW$T$3)
	.dwattr $C$DW$T$20, DW_AT_language(DW_LANG_C)
$C$DW$T$21	.dwtag  DW_TAG_pointer_type
	.dwattr $C$DW$T$21, DW_AT_type(*$C$DW$T$20)
	.dwattr $C$DW$T$21, DW_AT_address_class(0x20)

$C$DW$T$25	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$25, DW_AT_language(DW_LANG_C)
$C$DW$6	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$6, DW_AT_type(*$C$DW$T$20)
	.dwendtag $C$DW$T$25

$C$DW$T$26	.dwtag  DW_TAG_pointer_type
	.dwattr $C$DW$T$26, DW_AT_type(*$C$DW$T$25)
	.dwattr $C$DW$T$26, DW_AT_address_class(0x20)
$C$DW$T$27	.dwtag  DW_TAG_typedef, DW_AT_name("POOL_Close")
	.dwattr $C$DW$T$27, DW_AT_type(*$C$DW$T$26)
	.dwattr $C$DW$T$27, DW_AT_language(DW_LANG_C)

$C$DW$T$32	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$32, DW_AT_language(DW_LANG_C)
$C$DW$7	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$7, DW_AT_type(*$C$DW$T$20)
$C$DW$8	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$8, DW_AT_type(*$C$DW$T$20)
$C$DW$9	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$9, DW_AT_type(*$C$DW$T$28)
	.dwendtag $C$DW$T$32

$C$DW$T$33	.dwtag  DW_TAG_pointer_type
	.dwattr $C$DW$T$33, DW_AT_type(*$C$DW$T$32)
	.dwattr $C$DW$T$33, DW_AT_address_class(0x20)
$C$DW$T$34	.dwtag  DW_TAG_typedef, DW_AT_name("POOL_Free")
	.dwattr $C$DW$T$34, DW_AT_type(*$C$DW$T$33)
	.dwattr $C$DW$T$34, DW_AT_language(DW_LANG_C)

$C$DW$T$39	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$39, DW_AT_language(DW_LANG_C)
$C$DW$T$40	.dwtag  DW_TAG_pointer_type
	.dwattr $C$DW$T$40, DW_AT_type(*$C$DW$T$39)
	.dwattr $C$DW$T$40, DW_AT_address_class(0x20)
$C$DW$T$41	.dwtag  DW_TAG_typedef, DW_AT_name("POOL_Init")
	.dwattr $C$DW$T$41, DW_AT_type(*$C$DW$T$40)
	.dwattr $C$DW$T$41, DW_AT_language(DW_LANG_C)
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
$C$DW$T$36	.dwtag  DW_TAG_typedef, DW_AT_name("Uint16")
	.dwattr $C$DW$T$36, DW_AT_type(*$C$DW$T$9)
	.dwattr $C$DW$T$36, DW_AT_language(DW_LANG_C)
$C$DW$T$37	.dwtag  DW_TAG_typedef, DW_AT_name("Bool")
	.dwattr $C$DW$T$37, DW_AT_type(*$C$DW$T$9)
	.dwattr $C$DW$T$37, DW_AT_language(DW_LANG_C)
$C$DW$T$10	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$10, DW_AT_encoding(DW_ATE_signed)
	.dwattr $C$DW$T$10, DW_AT_name("int")
	.dwattr $C$DW$T$10, DW_AT_byte_size(0x04)
$C$DW$T$19	.dwtag  DW_TAG_typedef, DW_AT_name("Int")
	.dwattr $C$DW$T$19, DW_AT_type(*$C$DW$T$10)
	.dwattr $C$DW$T$19, DW_AT_language(DW_LANG_C)

$C$DW$T$22	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$22, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$T$22, DW_AT_language(DW_LANG_C)
$C$DW$10	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$10, DW_AT_type(*$C$DW$T$21)
$C$DW$11	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$11, DW_AT_type(*$C$DW$T$20)
	.dwendtag $C$DW$T$22

$C$DW$T$23	.dwtag  DW_TAG_pointer_type
	.dwattr $C$DW$T$23, DW_AT_type(*$C$DW$T$22)
	.dwattr $C$DW$T$23, DW_AT_address_class(0x20)
$C$DW$T$24	.dwtag  DW_TAG_typedef, DW_AT_name("POOL_Open")
	.dwattr $C$DW$T$24, DW_AT_type(*$C$DW$T$23)
	.dwattr $C$DW$T$24, DW_AT_language(DW_LANG_C)

$C$DW$T$29	.dwtag  DW_TAG_subroutine_type
	.dwattr $C$DW$T$29, DW_AT_type(*$C$DW$T$19)
	.dwattr $C$DW$T$29, DW_AT_language(DW_LANG_C)
$C$DW$12	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$12, DW_AT_type(*$C$DW$T$20)
$C$DW$13	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$13, DW_AT_type(*$C$DW$T$21)
$C$DW$14	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$14, DW_AT_type(*$C$DW$T$28)
	.dwendtag $C$DW$T$29

$C$DW$T$30	.dwtag  DW_TAG_pointer_type
	.dwattr $C$DW$T$30, DW_AT_type(*$C$DW$T$29)
	.dwattr $C$DW$T$30, DW_AT_address_class(0x20)
$C$DW$T$31	.dwtag  DW_TAG_typedef, DW_AT_name("POOL_Alloc")
	.dwattr $C$DW$T$31, DW_AT_type(*$C$DW$T$30)
	.dwattr $C$DW$T$31, DW_AT_language(DW_LANG_C)
$C$DW$T$11	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$11, DW_AT_encoding(DW_ATE_unsigned)
	.dwattr $C$DW$T$11, DW_AT_name("unsigned int")
	.dwattr $C$DW$T$11, DW_AT_byte_size(0x04)
$C$DW$T$28	.dwtag  DW_TAG_typedef, DW_AT_name("size_t")
	.dwattr $C$DW$T$28, DW_AT_type(*$C$DW$T$11)
	.dwattr $C$DW$T$28, DW_AT_language(DW_LANG_C)
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

$C$DW$T$35	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$35, DW_AT_name("POOL_Fxns")
	.dwattr $C$DW$T$35, DW_AT_byte_size(0x10)
$C$DW$15	.dwtag  DW_TAG_member
	.dwattr $C$DW$15, DW_AT_type(*$C$DW$T$24)
	.dwattr $C$DW$15, DW_AT_name("open")
	.dwattr $C$DW$15, DW_AT_TI_symbol_name("_open")
	.dwattr $C$DW$15, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$15, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$16	.dwtag  DW_TAG_member
	.dwattr $C$DW$16, DW_AT_type(*$C$DW$T$27)
	.dwattr $C$DW$16, DW_AT_name("close")
	.dwattr $C$DW$16, DW_AT_TI_symbol_name("_close")
	.dwattr $C$DW$16, DW_AT_data_member_location[DW_OP_plus_uconst 0x4]
	.dwattr $C$DW$16, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$17	.dwtag  DW_TAG_member
	.dwattr $C$DW$17, DW_AT_type(*$C$DW$T$31)
	.dwattr $C$DW$17, DW_AT_name("alloc")
	.dwattr $C$DW$17, DW_AT_TI_symbol_name("_alloc")
	.dwattr $C$DW$17, DW_AT_data_member_location[DW_OP_plus_uconst 0x8]
	.dwattr $C$DW$17, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$18	.dwtag  DW_TAG_member
	.dwattr $C$DW$18, DW_AT_type(*$C$DW$T$34)
	.dwattr $C$DW$18, DW_AT_name("free")
	.dwattr $C$DW$18, DW_AT_TI_symbol_name("_free")
	.dwattr $C$DW$18, DW_AT_data_member_location[DW_OP_plus_uconst 0xc]
	.dwattr $C$DW$18, DW_AT_accessibility(DW_ACCESS_public)
	.dwendtag $C$DW$T$35

$C$DW$T$42	.dwtag  DW_TAG_typedef, DW_AT_name("POOL_Fxns")
	.dwattr $C$DW$T$42, DW_AT_type(*$C$DW$T$35)
	.dwattr $C$DW$T$42, DW_AT_language(DW_LANG_C)
$C$DW$T$43	.dwtag  DW_TAG_pointer_type
	.dwattr $C$DW$T$43, DW_AT_type(*$C$DW$T$42)
	.dwattr $C$DW$T$43, DW_AT_address_class(0x20)
$C$DW$T$50	.dwtag  DW_TAG_const_type
	.dwattr $C$DW$T$50, DW_AT_type(*$C$DW$T$42)

$C$DW$T$38	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$38, DW_AT_name("SMAPOOL_Params_tag")
	.dwattr $C$DW$T$38, DW_AT_byte_size(0x04)
$C$DW$19	.dwtag  DW_TAG_member
	.dwattr $C$DW$19, DW_AT_type(*$C$DW$T$36)
	.dwattr $C$DW$19, DW_AT_name("poolId")
	.dwattr $C$DW$19, DW_AT_TI_symbol_name("_poolId")
	.dwattr $C$DW$19, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$19, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$20	.dwtag  DW_TAG_member
	.dwattr $C$DW$20, DW_AT_type(*$C$DW$T$37)
	.dwattr $C$DW$20, DW_AT_name("exactMatchReq")
	.dwattr $C$DW$20, DW_AT_TI_symbol_name("_exactMatchReq")
	.dwattr $C$DW$20, DW_AT_data_member_location[DW_OP_plus_uconst 0x2]
	.dwattr $C$DW$20, DW_AT_accessibility(DW_ACCESS_public)
	.dwendtag $C$DW$T$38

$C$DW$T$52	.dwtag  DW_TAG_typedef, DW_AT_name("SMAPOOL_Params")
	.dwattr $C$DW$T$52, DW_AT_type(*$C$DW$T$38)
	.dwattr $C$DW$T$52, DW_AT_language(DW_LANG_C)

$C$DW$T$44	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$44, DW_AT_name("POOL_Obj")
	.dwattr $C$DW$T$44, DW_AT_byte_size(0x10)
$C$DW$21	.dwtag  DW_TAG_member
	.dwattr $C$DW$21, DW_AT_type(*$C$DW$T$41)
	.dwattr $C$DW$21, DW_AT_name("initFxn")
	.dwattr $C$DW$21, DW_AT_TI_symbol_name("_initFxn")
	.dwattr $C$DW$21, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$21, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$22	.dwtag  DW_TAG_member
	.dwattr $C$DW$22, DW_AT_type(*$C$DW$T$43)
	.dwattr $C$DW$22, DW_AT_name("fxns")
	.dwattr $C$DW$22, DW_AT_TI_symbol_name("_fxns")
	.dwattr $C$DW$22, DW_AT_data_member_location[DW_OP_plus_uconst 0x4]
	.dwattr $C$DW$22, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$23	.dwtag  DW_TAG_member
	.dwattr $C$DW$23, DW_AT_type(*$C$DW$T$20)
	.dwattr $C$DW$23, DW_AT_name("params")
	.dwattr $C$DW$23, DW_AT_TI_symbol_name("_params")
	.dwattr $C$DW$23, DW_AT_data_member_location[DW_OP_plus_uconst 0x8]
	.dwattr $C$DW$23, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$24	.dwtag  DW_TAG_member
	.dwattr $C$DW$24, DW_AT_type(*$C$DW$T$20)
	.dwattr $C$DW$24, DW_AT_name("object")
	.dwattr $C$DW$24, DW_AT_TI_symbol_name("_object")
	.dwattr $C$DW$24, DW_AT_data_member_location[DW_OP_plus_uconst 0xc]
	.dwattr $C$DW$24, DW_AT_accessibility(DW_ACCESS_public)
	.dwendtag $C$DW$T$44

$C$DW$T$45	.dwtag  DW_TAG_typedef, DW_AT_name("POOL_Obj")
	.dwattr $C$DW$T$45, DW_AT_type(*$C$DW$T$44)
	.dwattr $C$DW$T$45, DW_AT_language(DW_LANG_C)
$C$DW$T$46	.dwtag  DW_TAG_pointer_type
	.dwattr $C$DW$T$46, DW_AT_type(*$C$DW$T$45)
	.dwattr $C$DW$T$46, DW_AT_address_class(0x20)

$C$DW$T$54	.dwtag  DW_TAG_array_type
	.dwattr $C$DW$T$54, DW_AT_type(*$C$DW$T$45)
	.dwattr $C$DW$T$54, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$54, DW_AT_byte_size(0x10)
$C$DW$25	.dwtag  DW_TAG_subrange_type
	.dwattr $C$DW$25, DW_AT_upper_bound(0x00)
	.dwendtag $C$DW$T$54


$C$DW$T$47	.dwtag  DW_TAG_structure_type
	.dwattr $C$DW$T$47, DW_AT_name("POOL_Config")
	.dwattr $C$DW$T$47, DW_AT_byte_size(0x08)
$C$DW$26	.dwtag  DW_TAG_member
	.dwattr $C$DW$26, DW_AT_type(*$C$DW$T$46)
	.dwattr $C$DW$26, DW_AT_name("allocators")
	.dwattr $C$DW$26, DW_AT_TI_symbol_name("_allocators")
	.dwattr $C$DW$26, DW_AT_data_member_location[DW_OP_plus_uconst 0x0]
	.dwattr $C$DW$26, DW_AT_accessibility(DW_ACCESS_public)
$C$DW$27	.dwtag  DW_TAG_member
	.dwattr $C$DW$27, DW_AT_type(*$C$DW$T$36)
	.dwattr $C$DW$27, DW_AT_name("numAllocators")
	.dwattr $C$DW$27, DW_AT_TI_symbol_name("_numAllocators")
	.dwattr $C$DW$27, DW_AT_data_member_location[DW_OP_plus_uconst 0x4]
	.dwattr $C$DW$27, DW_AT_accessibility(DW_ACCESS_public)
	.dwendtag $C$DW$T$47

$C$DW$T$55	.dwtag  DW_TAG_typedef, DW_AT_name("POOL_Config")
	.dwattr $C$DW$T$55, DW_AT_type(*$C$DW$T$47)
	.dwattr $C$DW$T$55, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$CU, DW_AT_language(DW_LANG_C)

;***************************************************************
;* DWARF REGISTER MAP                                          *
;***************************************************************

$C$DW$28	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A0")
	.dwattr $C$DW$28, DW_AT_location[DW_OP_reg0]
$C$DW$29	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A1")
	.dwattr $C$DW$29, DW_AT_location[DW_OP_reg1]
$C$DW$30	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A2")
	.dwattr $C$DW$30, DW_AT_location[DW_OP_reg2]
$C$DW$31	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A3")
	.dwattr $C$DW$31, DW_AT_location[DW_OP_reg3]
$C$DW$32	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A4")
	.dwattr $C$DW$32, DW_AT_location[DW_OP_reg4]
$C$DW$33	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A5")
	.dwattr $C$DW$33, DW_AT_location[DW_OP_reg5]
$C$DW$34	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A6")
	.dwattr $C$DW$34, DW_AT_location[DW_OP_reg6]
$C$DW$35	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A7")
	.dwattr $C$DW$35, DW_AT_location[DW_OP_reg7]
$C$DW$36	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A8")
	.dwattr $C$DW$36, DW_AT_location[DW_OP_reg8]
$C$DW$37	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A9")
	.dwattr $C$DW$37, DW_AT_location[DW_OP_reg9]
$C$DW$38	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A10")
	.dwattr $C$DW$38, DW_AT_location[DW_OP_reg10]
$C$DW$39	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A11")
	.dwattr $C$DW$39, DW_AT_location[DW_OP_reg11]
$C$DW$40	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A12")
	.dwattr $C$DW$40, DW_AT_location[DW_OP_reg12]
$C$DW$41	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A13")
	.dwattr $C$DW$41, DW_AT_location[DW_OP_reg13]
$C$DW$42	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A14")
	.dwattr $C$DW$42, DW_AT_location[DW_OP_reg14]
$C$DW$43	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A15")
	.dwattr $C$DW$43, DW_AT_location[DW_OP_reg15]
$C$DW$44	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("B0")
	.dwattr $C$DW$44, DW_AT_location[DW_OP_reg16]
$C$DW$45	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("B1")
	.dwattr $C$DW$45, DW_AT_location[DW_OP_reg17]
$C$DW$46	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("B2")
	.dwattr $C$DW$46, DW_AT_location[DW_OP_reg18]
$C$DW$47	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("B3")
	.dwattr $C$DW$47, DW_AT_location[DW_OP_reg19]
$C$DW$48	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("B4")
	.dwattr $C$DW$48, DW_AT_location[DW_OP_reg20]
$C$DW$49	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("B5")
	.dwattr $C$DW$49, DW_AT_location[DW_OP_reg21]
$C$DW$50	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("B6")
	.dwattr $C$DW$50, DW_AT_location[DW_OP_reg22]
$C$DW$51	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("B7")
	.dwattr $C$DW$51, DW_AT_location[DW_OP_reg23]
$C$DW$52	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("B8")
	.dwattr $C$DW$52, DW_AT_location[DW_OP_reg24]
$C$DW$53	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("B9")
	.dwattr $C$DW$53, DW_AT_location[DW_OP_reg25]
$C$DW$54	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("B10")
	.dwattr $C$DW$54, DW_AT_location[DW_OP_reg26]
$C$DW$55	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("B11")
	.dwattr $C$DW$55, DW_AT_location[DW_OP_reg27]
$C$DW$56	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("B12")
	.dwattr $C$DW$56, DW_AT_location[DW_OP_reg28]
$C$DW$57	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("B13")
	.dwattr $C$DW$57, DW_AT_location[DW_OP_reg29]
$C$DW$58	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("DP")
	.dwattr $C$DW$58, DW_AT_location[DW_OP_reg30]
$C$DW$59	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("SP")
	.dwattr $C$DW$59, DW_AT_location[DW_OP_reg31]
$C$DW$60	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("FP")
	.dwattr $C$DW$60, DW_AT_location[DW_OP_regx 0x20]
$C$DW$61	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("PC")
	.dwattr $C$DW$61, DW_AT_location[DW_OP_regx 0x21]
$C$DW$62	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("IRP")
	.dwattr $C$DW$62, DW_AT_location[DW_OP_regx 0x22]
$C$DW$63	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("IFR")
	.dwattr $C$DW$63, DW_AT_location[DW_OP_regx 0x23]
$C$DW$64	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("NRP")
	.dwattr $C$DW$64, DW_AT_location[DW_OP_regx 0x24]
$C$DW$65	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A16")
	.dwattr $C$DW$65, DW_AT_location[DW_OP_regx 0x25]
$C$DW$66	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A17")
	.dwattr $C$DW$66, DW_AT_location[DW_OP_regx 0x26]
$C$DW$67	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A18")
	.dwattr $C$DW$67, DW_AT_location[DW_OP_regx 0x27]
$C$DW$68	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A19")
	.dwattr $C$DW$68, DW_AT_location[DW_OP_regx 0x28]
$C$DW$69	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A20")
	.dwattr $C$DW$69, DW_AT_location[DW_OP_regx 0x29]
$C$DW$70	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A21")
	.dwattr $C$DW$70, DW_AT_location[DW_OP_regx 0x2a]
$C$DW$71	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A22")
	.dwattr $C$DW$71, DW_AT_location[DW_OP_regx 0x2b]
$C$DW$72	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A23")
	.dwattr $C$DW$72, DW_AT_location[DW_OP_regx 0x2c]
$C$DW$73	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A24")
	.dwattr $C$DW$73, DW_AT_location[DW_OP_regx 0x2d]
$C$DW$74	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A25")
	.dwattr $C$DW$74, DW_AT_location[DW_OP_regx 0x2e]
$C$DW$75	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A26")
	.dwattr $C$DW$75, DW_AT_location[DW_OP_regx 0x2f]
$C$DW$76	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A27")
	.dwattr $C$DW$76, DW_AT_location[DW_OP_regx 0x30]
$C$DW$77	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A28")
	.dwattr $C$DW$77, DW_AT_location[DW_OP_regx 0x31]
$C$DW$78	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A29")
	.dwattr $C$DW$78, DW_AT_location[DW_OP_regx 0x32]
$C$DW$79	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A30")
	.dwattr $C$DW$79, DW_AT_location[DW_OP_regx 0x33]
$C$DW$80	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("A31")
	.dwattr $C$DW$80, DW_AT_location[DW_OP_regx 0x34]
$C$DW$81	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("B16")
	.dwattr $C$DW$81, DW_AT_location[DW_OP_regx 0x35]
$C$DW$82	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("B17")
	.dwattr $C$DW$82, DW_AT_location[DW_OP_regx 0x36]
$C$DW$83	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("B18")
	.dwattr $C$DW$83, DW_AT_location[DW_OP_regx 0x37]
$C$DW$84	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("B19")
	.dwattr $C$DW$84, DW_AT_location[DW_OP_regx 0x38]
$C$DW$85	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("B20")
	.dwattr $C$DW$85, DW_AT_location[DW_OP_regx 0x39]
$C$DW$86	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("B21")
	.dwattr $C$DW$86, DW_AT_location[DW_OP_regx 0x3a]
$C$DW$87	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("B22")
	.dwattr $C$DW$87, DW_AT_location[DW_OP_regx 0x3b]
$C$DW$88	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("B23")
	.dwattr $C$DW$88, DW_AT_location[DW_OP_regx 0x3c]
$C$DW$89	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("B24")
	.dwattr $C$DW$89, DW_AT_location[DW_OP_regx 0x3d]
$C$DW$90	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("B25")
	.dwattr $C$DW$90, DW_AT_location[DW_OP_regx 0x3e]
$C$DW$91	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("B26")
	.dwattr $C$DW$91, DW_AT_location[DW_OP_regx 0x3f]
$C$DW$92	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("B27")
	.dwattr $C$DW$92, DW_AT_location[DW_OP_regx 0x40]
$C$DW$93	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("B28")
	.dwattr $C$DW$93, DW_AT_location[DW_OP_regx 0x41]
$C$DW$94	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("B29")
	.dwattr $C$DW$94, DW_AT_location[DW_OP_regx 0x42]
$C$DW$95	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("B30")
	.dwattr $C$DW$95, DW_AT_location[DW_OP_regx 0x43]
$C$DW$96	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("B31")
	.dwattr $C$DW$96, DW_AT_location[DW_OP_regx 0x44]
$C$DW$97	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("AMR")
	.dwattr $C$DW$97, DW_AT_location[DW_OP_regx 0x45]
$C$DW$98	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("CSR")
	.dwattr $C$DW$98, DW_AT_location[DW_OP_regx 0x46]
$C$DW$99	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("ISR")
	.dwattr $C$DW$99, DW_AT_location[DW_OP_regx 0x47]
$C$DW$100	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("ICR")
	.dwattr $C$DW$100, DW_AT_location[DW_OP_regx 0x48]
$C$DW$101	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("IER")
	.dwattr $C$DW$101, DW_AT_location[DW_OP_regx 0x49]
$C$DW$102	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("ISTP")
	.dwattr $C$DW$102, DW_AT_location[DW_OP_regx 0x4a]
$C$DW$103	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("IN")
	.dwattr $C$DW$103, DW_AT_location[DW_OP_regx 0x4b]
$C$DW$104	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("OUT")
	.dwattr $C$DW$104, DW_AT_location[DW_OP_regx 0x4c]
$C$DW$105	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("ACR")
	.dwattr $C$DW$105, DW_AT_location[DW_OP_regx 0x4d]
$C$DW$106	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("ADR")
	.dwattr $C$DW$106, DW_AT_location[DW_OP_regx 0x4e]
$C$DW$107	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("FADCR")
	.dwattr $C$DW$107, DW_AT_location[DW_OP_regx 0x4f]
$C$DW$108	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("FAUCR")
	.dwattr $C$DW$108, DW_AT_location[DW_OP_regx 0x50]
$C$DW$109	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("FMCR")
	.dwattr $C$DW$109, DW_AT_location[DW_OP_regx 0x51]
$C$DW$110	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("GFPGFR")
	.dwattr $C$DW$110, DW_AT_location[DW_OP_regx 0x52]
$C$DW$111	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("DIER")
	.dwattr $C$DW$111, DW_AT_location[DW_OP_regx 0x53]
$C$DW$112	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("REP")
	.dwattr $C$DW$112, DW_AT_location[DW_OP_regx 0x54]
$C$DW$113	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("TSCL")
	.dwattr $C$DW$113, DW_AT_location[DW_OP_regx 0x55]
$C$DW$114	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("TSCH")
	.dwattr $C$DW$114, DW_AT_location[DW_OP_regx 0x56]
$C$DW$115	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("ARP")
	.dwattr $C$DW$115, DW_AT_location[DW_OP_regx 0x57]
$C$DW$116	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("ILC")
	.dwattr $C$DW$116, DW_AT_location[DW_OP_regx 0x58]
$C$DW$117	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("RILC")
	.dwattr $C$DW$117, DW_AT_location[DW_OP_regx 0x59]
$C$DW$118	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("DNUM")
	.dwattr $C$DW$118, DW_AT_location[DW_OP_regx 0x5a]
$C$DW$119	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("SSR")
	.dwattr $C$DW$119, DW_AT_location[DW_OP_regx 0x5b]
$C$DW$120	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("GPLYA")
	.dwattr $C$DW$120, DW_AT_location[DW_OP_regx 0x5c]
$C$DW$121	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("GPLYB")
	.dwattr $C$DW$121, DW_AT_location[DW_OP_regx 0x5d]
$C$DW$122	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("TSR")
	.dwattr $C$DW$122, DW_AT_location[DW_OP_regx 0x5e]
$C$DW$123	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("ITSR")
	.dwattr $C$DW$123, DW_AT_location[DW_OP_regx 0x5f]
$C$DW$124	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("NTSR")
	.dwattr $C$DW$124, DW_AT_location[DW_OP_regx 0x60]
$C$DW$125	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("EFR")
	.dwattr $C$DW$125, DW_AT_location[DW_OP_regx 0x61]
$C$DW$126	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("ECR")
	.dwattr $C$DW$126, DW_AT_location[DW_OP_regx 0x62]
$C$DW$127	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("IERR")
	.dwattr $C$DW$127, DW_AT_location[DW_OP_regx 0x63]
$C$DW$128	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("DMSG")
	.dwattr $C$DW$128, DW_AT_location[DW_OP_regx 0x64]
$C$DW$129	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("CMSG")
	.dwattr $C$DW$129, DW_AT_location[DW_OP_regx 0x65]
$C$DW$130	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("DT_DMA_ADDR")
	.dwattr $C$DW$130, DW_AT_location[DW_OP_regx 0x66]
$C$DW$131	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("DT_DMA_DATA")
	.dwattr $C$DW$131, DW_AT_location[DW_OP_regx 0x67]
$C$DW$132	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("DT_DMA_CNTL")
	.dwattr $C$DW$132, DW_AT_location[DW_OP_regx 0x68]
$C$DW$133	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("TCU_CNTL")
	.dwattr $C$DW$133, DW_AT_location[DW_OP_regx 0x69]
$C$DW$134	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("RTDX_REC_CNTL")
	.dwattr $C$DW$134, DW_AT_location[DW_OP_regx 0x6a]
$C$DW$135	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("RTDX_XMT_CNTL")
	.dwattr $C$DW$135, DW_AT_location[DW_OP_regx 0x6b]
$C$DW$136	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("RTDX_CFG")
	.dwattr $C$DW$136, DW_AT_location[DW_OP_regx 0x6c]
$C$DW$137	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("RTDX_RDATA")
	.dwattr $C$DW$137, DW_AT_location[DW_OP_regx 0x6d]
$C$DW$138	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("RTDX_WDATA")
	.dwattr $C$DW$138, DW_AT_location[DW_OP_regx 0x6e]
$C$DW$139	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("RTDX_RADDR")
	.dwattr $C$DW$139, DW_AT_location[DW_OP_regx 0x6f]
$C$DW$140	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("RTDX_WADDR")
	.dwattr $C$DW$140, DW_AT_location[DW_OP_regx 0x70]
$C$DW$141	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("MFREG0")
	.dwattr $C$DW$141, DW_AT_location[DW_OP_regx 0x71]
$C$DW$142	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("DBG_STAT")
	.dwattr $C$DW$142, DW_AT_location[DW_OP_regx 0x72]
$C$DW$143	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("BRK_EN")
	.dwattr $C$DW$143, DW_AT_location[DW_OP_regx 0x73]
$C$DW$144	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("HWBP0_CNT")
	.dwattr $C$DW$144, DW_AT_location[DW_OP_regx 0x74]
$C$DW$145	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("HWBP0")
	.dwattr $C$DW$145, DW_AT_location[DW_OP_regx 0x75]
$C$DW$146	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("HWBP1")
	.dwattr $C$DW$146, DW_AT_location[DW_OP_regx 0x76]
$C$DW$147	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("HWBP2")
	.dwattr $C$DW$147, DW_AT_location[DW_OP_regx 0x77]
$C$DW$148	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("HWBP3")
	.dwattr $C$DW$148, DW_AT_location[DW_OP_regx 0x78]
$C$DW$149	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("OVERLAY")
	.dwattr $C$DW$149, DW_AT_location[DW_OP_regx 0x79]
$C$DW$150	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("PC_PROF")
	.dwattr $C$DW$150, DW_AT_location[DW_OP_regx 0x7a]
$C$DW$151	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("ATSR")
	.dwattr $C$DW$151, DW_AT_location[DW_OP_regx 0x7b]
$C$DW$152	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("TRR")
	.dwattr $C$DW$152, DW_AT_location[DW_OP_regx 0x7c]
$C$DW$153	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("TCRR")
	.dwattr $C$DW$153, DW_AT_location[DW_OP_regx 0x7d]
$C$DW$154	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("DESR")
	.dwattr $C$DW$154, DW_AT_location[DW_OP_regx 0x7e]
$C$DW$155	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("DETR")
	.dwattr $C$DW$155, DW_AT_location[DW_OP_regx 0x7f]
$C$DW$156	.dwtag  DW_TAG_TI_assign_register, DW_AT_name("CIE_RETA")
	.dwattr $C$DW$156, DW_AT_location[DW_OP_regx 0xe4]
	.dwendtag $C$DW$CU

