ENTRY(_start)

SECTIONS
{
	. = 0x00000000;
	.text.init : {
			* (.text.init);
	}
	.text : {
	      * (.text);
	}
	. = SIZE;
	.data : {
	      * (.data);
	}
	.srodata : {
	      * (.srodata);
	}
	.rodata : {
	      * (.rodata);
	}
	.bss : {
	     * (.bss);
	}

	PROVIDE( end = . );
    PROVIDE( _end = . );
    PROVIDE( __end = . );
}
