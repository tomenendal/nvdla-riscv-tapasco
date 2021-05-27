OUTPUT_ARCH( "riscv" )
ENTRY(_start)

MEMORY {
    ICCM    : ORIGIN = 0xee000000, LENGTH = 0x80000
    DCCM    : ORIGIN = 0xf0040000, LENGTH = 0x10000
}

SECTIONS
{
	.text.init : {
			* (.text.init);
	} > ICCM
	.text : SUBALIGN(4) {
	      * (.text.*);
	} > ICCM
	.data : SUBALIGN(4) {
	      * (.data.*);
	      * (.sdata.*);
	      * (.sdata2.*);
	} > DCCM
	.srodata : ALIGN(4) SUBALIGN(4) {
	      * (.srodata.*);
	} > DCCM
	.rodata : ALIGN(4) {
	      * (.rodata.*);
	      . = ALIGN(4);
	      LONG(0xDEADBEEF);
	} > DCCM
	.bss : {
	     * (.bss.*);
	} > DCCM
}
