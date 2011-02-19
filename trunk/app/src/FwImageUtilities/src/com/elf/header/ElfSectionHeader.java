package com.elf.header;

import com.util.ConversionUtil;


public class ElfSectionHeader {

	/****************************************************
	 * 
	 * Constants
	 * 
	 ****************************************************/
	public static final int	SHT_NULL		=0;		/* sh_type */
	public static final int	SHT_PROGBITS	=1;
	public static final int	SHT_SYMTAB		=2;
	public static final int	SHT_STRTAB		=3;
	public static final int	SHT_RELA		=4;
	public static final int	SHT_HASH		=5;
	public static final int	SHT_DYNAMIC		=6;
	public static final int	SHT_NOTE		=7;
	public static final int	SHT_NOBITS		=8;
	public static final int	SHT_REL			=9;
	public static final int	SHT_SHLIB		=10;
	public static final int	SHT_DYNSYM		=11;
	public static final int	SHT_UNKNOWN12		=12;
	public static final int	SHT_UNKNOWN13		=13;
	public static final int	SHT_INIT_ARRAY		=14;
	public static final int	SHT_FINI_ARRAY		=15;
	public static final int	SHT_PREINIT_ARRAY	=16;
	public static final int	SHT_GROUP		=17;
	public static final int	SHT_SYMTAB_SHNDX	=18;
	public static final int	SHT_NUM			=19;

	/* Solaris ABI specific values */
	public static final int	SHT_LOOS		=0x60000000;	/* OS specific range */
	public static final int	SHT_LOSUNW		=0x6ffffff1;
	public static final int	SHT_SUNW_symsort	=0x6ffffff1;
	public static final int	SHT_SUNW_tlssort	=0x6ffffff2;
	public static final int	SHT_SUNW_LDYNSYM	=0x6ffffff3;
	public static final int	SHT_SUNW_dof		=0x6ffffff4;
	public static final int	SHT_SUNW_cap		=0x6ffffff5;
	public static final int	SHT_SUNW_SIGNATURE	=0x6ffffff6;
	public static final int	SHT_SUNW_ANNOTATE	=0x6ffffff7;
	public static final int	SHT_SUNW_DEBUGSTR	=0x6ffffff8;
	public static final int	SHT_SUNW_DEBUG		=0x6ffffff9;;
	public static final int	SHT_SUNW_move		=0x6ffffffa;
	public static final int	SHT_SUNW_COMDAT		=0x6ffffffb;
	public static final int	SHT_SUNW_syminfo	=0x6ffffffc;
	public static final int	SHT_SUNW_verdef		=0x6ffffffd;
	public static final int	SHT_SUNW_verneed	=0x6ffffffe;
	public static final int	SHT_SUNW_versym		=0x6fffffff;
	public static final int	SHT_HISUNW		=0x6fffffff;
	public static final int	SHT_HIOS		=0x6fffffff;

	/* GNU/Linux ABI specific values */
	public static final int	SHT_GNU_verdef		=0x6ffffffd;
	public static final int	SHT_GNU_verneed		=0x6ffffffe;
	public static final int	SHT_GNU_versym		=0x6fffffff;

	public static final int	SHT_LOPROC	=0x70000000;	/* processor specific range */
	public static final int	SHT_HIPROC	=0x7fffffff;

	public static final int	SHT_LOUSER	=0x80000000;
	public static final int	SHT_HIUSER	=0xffffffff;

	public static final int	SHF_WRITE		=0x01;		/* sh_flags */
	public static final int	SHF_ALLOC		=0x02;
	public static final int	SHF_EXECINSTR		=0x04;
	public static final int	SHF_MERGE		=0x10;
	public static final int	SHF_STRINGS		=0x20;
	public static final int	SHF_INFO_LINK		=0x40;
	public static final int	SHF_LINK_ORDER		=0x80;
	public static final int	SHF_OS_NONCONFORMING	=0x100;
	public static final int	SHF_GROUP		=0x200;
	public static final int	SHF_TLS			=0x400;

	public static final int	SHF_MASKOS	=0x0ff00000;	/* OS specific values */


	public static final int	SHF_MASKPROC	=0xf0000000;	/* processor specific values */

	public static final int	SHN_UNDEF	=0;		/* special section numbers */
	public static final int	SHN_LORESERVE	=0xff00;
	public static final int	SHN_LOPROC	=0xff00;		/* processor specific range */
	public static final int	SHN_HIPROC	=0xff1f;
	public static final int	SHN_LOOS	=0xff20;	/* OS specific range */
	public static final int	SHN_LOSUNW	=0xff3f;
	public static final int	SHN_SUNW_IGNORE	=0xff3f;
	public static final int	SHN_HISUNW	=0xff3f;
	public static final int	SHN_HIOS	=0xff3f;
	public static final int	SHN_ABS		=0xfff1;
	public static final int	SHN_COMMON	=0xfff2;
	public static final int	SHN_XINDEX	=0xffff;		/* extended sect index */
	public static final int	SHN_HIRESERVE	=0xffff;
	
	
	/***************************************************************
	 * 
	 * Data Members
	 * 
	 ***************************************************************/
	private int	sh_name;	/* section name */
	private int	sh_type;	/* SHT_... */
	private int	sh_flags;	/* SHF_... */
	private int	sh_addr;	/* virtual address */
	private int	sh_offset;	/* file offset */
	private int	sh_size;	/* section size */
	private int	sh_link;	/* misc info */
	private int	sh_info;	/* misc info */
	private int	sh_addralign;	/* memory alignment */
	private int	sh_entsize;	/* entry size if table */
	
	
	public ElfSectionHeader(byte[] buffer, int SectionHeaderOffset) {
		sh_name = ConversionUtil.byteArrayToIntBE(buffer, SectionHeaderOffset+0);
		sh_type = ConversionUtil.byteArrayToIntBE(buffer, SectionHeaderOffset+4);
		sh_flags = ConversionUtil.byteArrayToIntBE(buffer, SectionHeaderOffset+8);
		sh_addr = ConversionUtil.byteArrayToIntBE(buffer, SectionHeaderOffset+12);
		sh_offset = ConversionUtil.byteArrayToIntBE(buffer, SectionHeaderOffset+16);
		sh_size = ConversionUtil.byteArrayToIntBE(buffer, SectionHeaderOffset+20);
		sh_link = ConversionUtil.byteArrayToIntBE(buffer, SectionHeaderOffset+24);
		sh_info = ConversionUtil.byteArrayToIntBE(buffer, SectionHeaderOffset+28);
		sh_addralign = ConversionUtil.byteArrayToIntBE(buffer, SectionHeaderOffset+32);
		sh_entsize = ConversionUtil.byteArrayToIntBE(buffer, SectionHeaderOffset+36);
	}


	public int getSh_name() {
		return sh_name;
	}


	public int getSh_type() {
		return sh_type;
	}


	public int getSh_flags() {
		return sh_flags;
	}


	public int getSh_addr() {
		return sh_addr;
	}


	public int getSh_offset() {
		return sh_offset;
	}


	public int getSh_size() {
		return sh_size;
	}


	public int getSh_link() {
		return sh_link;
	}


	public int getSh_info() {
		return sh_info;
	}


	public int getSh_addralign() {
		return sh_addralign;
	}


	public int getSh_entsize() {
		return sh_entsize;
	}

	
}
