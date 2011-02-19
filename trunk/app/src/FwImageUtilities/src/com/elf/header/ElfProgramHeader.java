package com.elf.header;

import com.util.ConversionUtil;

public class ElfProgramHeader {

	/****************************************************
	 * 
	 * Constants
	 * 
	 ****************************************************/
	public static final int	PT_NULL		=0;		/* p_type */
	public static final int	PT_LOAD		=1;
	public static final int	PT_DYNAMIC	=2;
	public static final int	PT_INTERP	=3;
	public static final int	PT_NOTE		=4;
	public static final int	PT_SHLIB	=5;
	public static final int	PT_PHDR		=6;
	public static final int	PT_TLS		=7;
	public static final int	PT_NUM		=8;

	public static final int	PT_LOOS		=0x60000000;	/* OS specific range */

	/*
	 * Note: The amd64 psABI defines that the UNWIND program header
	 *	 should reside in the OS specific range of the program
	 *	 headers.
	 */
	public static final int	PT_SUNW_UNWIND	=0x6464e550;	/* amd64 UNWIND program header */
	public static final int	PT_GNU_EH_FRAME	=PT_SUNW_UNWIND;


	public static final int	PT_LOSUNW	=0x6ffffffa;
	public static final int	PT_SUNWBSS	=0x6ffffffa;	/* Sun Specific segment */
	public static final int	PT_SUNWSTACK	=0x6ffffffb;	/* describes the stack segment */
	public static final int	PT_SUNWDTRACE	=0x6ffffffc;	/* private */
	public static final int	PT_SUNWCAP	=0x6ffffffd;	/* hard/soft capabilities segment */
	public static final int	PT_HISUNW	=0x6fffffff;
	public static final int	PT_HIOS		=0x6fffffff;

	public static final int	PT_LOPROC	=0x70000000;	/* processor specific range */
	public static final int	PT_HIPROC	=0x7fffffff;

	public static final int	PF_R		=0x4;		/* p_flags */
	public static final int	PF_W		=0x2;
	public static final int	PF_X		=0x1;

	public static final int	PF_MASKOS	=0x0ff00000;	/* OS specific values */
	public static final int	PF_MASKPROC	=0xf0000000;	/* processor specific values */

	public static final int	PF_SUNW_FAILURE	=0x00100000;	/* mapping absent due to failure */

	public static final int	PN_XNUM		=0xffff;		/* extended program header index */	
	
	/***************************************************************
	 * 
	 * Data Members
	 * 
	 ***************************************************************/
	private int	p_type;		/* entry type */
	private int	p_offset;	/* file offset */
	private int	p_vaddr;	/* virtual address */
	private int	p_paddr;	/* physical address */
	private int	p_filesz;	/* file size */
	private int	p_memsz;	/* memory size */
	private int	p_flags;	/* entry flags */
	private int	p_align;	/* memory/file alignment */
	
	public ElfProgramHeader(byte[] buffer, int ProgramHeaderOffset) {
		p_type = ConversionUtil.byteArrayToIntBE(buffer, ProgramHeaderOffset);
		p_offset = ConversionUtil.byteArrayToIntBE(buffer, ProgramHeaderOffset+4);
		p_vaddr = ConversionUtil.byteArrayToIntBE(buffer, ProgramHeaderOffset+8);
		p_paddr = ConversionUtil.byteArrayToIntBE(buffer, ProgramHeaderOffset+12);
		p_filesz = ConversionUtil.byteArrayToIntBE(buffer, ProgramHeaderOffset+16);
		p_memsz = ConversionUtil.byteArrayToIntBE(buffer, ProgramHeaderOffset+20);
		p_flags = ConversionUtil.byteArrayToIntBE(buffer, ProgramHeaderOffset+24);
		p_align = ConversionUtil.byteArrayToIntBE(buffer, ProgramHeaderOffset+28);
	}

	public int getP_type() {
		return p_type;
	}

	public int getP_offset() {
		return p_offset;
	}

	public int getP_vaddr() {
		return p_vaddr;
	}

	public int getP_paddr() {
		return p_paddr;
	}

	public int getP_filesz() {
		return p_filesz;
	}

	public int getP_memsz() {
		return p_memsz;
	}

	public int getP_flags() {
		return p_flags;
	}

	public int getP_align() {
		return p_align;
	}
	
	

}
