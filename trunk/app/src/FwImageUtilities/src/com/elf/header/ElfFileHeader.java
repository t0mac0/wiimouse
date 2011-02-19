package com.elf.header;

import java.util.Arrays;

import com.util.ConversionUtil;


public class ElfFileHeader {

	/****************************************************
	 * 
	 * Constants
	 * 
	 ****************************************************/
	public static final int EI_NIDNET = 16;
	public static int	EI_MAG0		=0;	/* e_ident[] indexes */
	public static int	EI_MAG1		=1;
	public static int	EI_MAG2		=2;
	public static int	EI_MAG3		=3;
	public static int	EI_CLASS	=4;	/* File class */
	public static int	EI_DATA		=5;	/* Data encoding */
	public static int	EI_VERSION	=6;	/* File version */
	public static int	EI_OSABI	=7;	/* Operating system/ABI identification */
	public static int	EI_ABIVERSION	=8;	/* ABI version */
	public static int	EI_PAD		=9;	/* Start of padding bytes */

	public static int	ELFMAG0		=0x7f;		/* EI_MAG */
	public static int	ELFMAG1		='E';
	public static int	ELFMAG2		='L';
	public static int	ELFMAG3		='F';
	public static String ELFMAG		="\177ELF";
	public static int	SELFMAG		=4;

	public static int	ELFCLASSNONE=0;		/* EI_CLASS */
	public static int	ELFCLASS32	=1;
	public static int	ELFCLASS64	=2;
	public static int	ELFCLASSNUM	=3;

	public static int	ELFDATANONE	=0;		/* EI_DATA */
	public static int	ELFDATA2LSB	=1;
	public static int	ELFDATA2MSB	=2;
	public static int	ELFDATANUM	=3;

	public static int	ET_NONE		=0;		/* e_type */
	public static int	ET_REL		=1;
	public static int	ET_EXEC		=2;
	public static int	ET_DYN		=3;
	public static int	ET_CORE		=4;
	public static int	ET_NUM		=5;
	public static int	ET_LOOS		=0xfe00;		/* OS specific range */
	public static int	ET_LOSUNW	=0xfeff;
	public static int	ET_SUNWPSEUDO	=0xfeff;
	public static int	ET_HISUNW	=0xfeff;
	public static int	ET_HIOS		=0xfeff;
	public static int	ET_LOPROC	=0xff00;	/* processor specific range */
	public static int	ET_HIPROC	=0xffff;


	public static int	EM_NONE		=0;		/* e_machine */
	public static int	EM_M32		=1;		/* AT&T WE 32100 */
	public static int	EM_SPARC	=2;		/* Sun SPARC */
	public static int	EM_386		=3;		/* Intel 80386 */
	public static int	EM_68K		=4;		/* Motorola 68000 */
	public static int	EM_88K		=5;		/* Motorola 88000 */
	public static int	EM_486		=6;		/* Intel 80486 */
	public static int	EM_860		=7;		/* Intel i860 */
	public static int	EM_MIPS		=8;		/* MIPS RS3000 Big-Endian */
	public static int	EM_S370		=9;		/* IBM System/370 Processor */
	public static int	EM_MIPS_RS3_LE	=10;		/* MIPS RS3000 Little-Endian */
	public static int	EM_RS6000	=11;		/* RS6000 */
	public static int	EM_UNKNOWN12	=12;
	public static int	EM_UNKNOWN13	=13;
	public static int	EM_UNKNOWN14	=14;
	public static int	EM_PA_RISC	=15;		/* PA-RISC */
	public static int	EM_PARISC	=EM_PA_RISC;	/* Alias: GNU compatibility */
	public static int	EM_nCUBE	=16;		/* nCUBE */
	public static int	EM_VPP500	=17;		/* Fujitsu VPP500 */
	public static int	EM_SPARC32PLUS	=18;		/* Sun SPARC 32+ */
	public static int	EM_960		=19;		/* Intel 80960 */
	public static int	EM_PPC		=20;		/* PowerPC */
	public static int	EM_PPC64	=21;		/* 64-bit PowerPC */
	public static int	EM_S390		=22;		/* IBM System/390 Processor */
	public static int	EM_UNKNOWN22	=EM_S390;		/* Alias: Older published name */
	public static int	EM_UNKNOWN23	=23;
	public static int	EM_UNKNOWN24	=24;
	public static int	EM_UNKNOWN25	=25;
	public static int	EM_UNKNOWN26	=26;
	public static int	EM_UNKNOWN27	=27;
	public static int	EM_UNKNOWN28	=28;
	public static int	EM_UNKNOWN29	=29;
	public static int	EM_UNKNOWN30	=30;
	public static int	EM_UNKNOWN31	=31;
	public static int	EM_UNKNOWN32	=32;
	public static int	EM_UNKNOWN33	=33;
	public static int	EM_UNKNOWN34	=34;
	public static int	EM_UNKNOWN35	=35;
	public static int	EM_V800		=36;/* NEX V800 */
	public static int	EM_FR20		=37;		/* Fujitsu FR20 */
	public static int	EM_RH32		=38;		/* TRW RH-32 */
	public static int	EM_RCE		=39;		/* Motorola RCE */
	public static int	EM_ARM		=40;		/* Advanced RISC Marchines ARM */
	public static int	EM_ALPHA	=41;		/* Digital Alpha */
	public static int	EM_SH		=42;		/* Hitachi SH */
	public static int	EM_SPARCV9	=43;		/* Sun SPARC V9 (64-bit) */
	public static int	EM_TRICORE	=44;		/* Siemens Tricore embedded processor */
	public static int	EM_ARC		=45;		/* Argonaut RISC Core, */
	/*	Argonaut Technologies Inc. */
	public static int	EM_H8_300	=46;		/* Hitachi H8/300 */
	public static int	EM_H8_300H	=47;		/* Hitachi H8/300H */
	public static int	EM_H8S		=48;		/* Hitachi H8S */
	public static int	EM_H8_500	=49;		/* Hitachi H8/500 */
	public static int	EM_IA_64	=50;		/* Intel IA64 */
	public static int	EM_MIPS_X	=51;		/* Stanford MIPS-X */
	public static int	EM_COLDFIRE	=52;		/* Motorola ColdFire */
	public static int	EM_68HC12	=53;		/* Motorola M68HC12 */
	public static int	EM_MMA		=54;		/* Fujitsu MMA Mulimedia Accelerator */
	public static int	EM_PCP		=55;		/* Siemens PCP */
	public static int	EM_NCPU		=56;		/* Sony nCPU embedded RISC processor */
	public static int	EM_NDR1		=57;		/* Denso NDR1 microprocessor */
	public static int	EM_STARCORE	=58;		/* Motorola Star*Core processor */
	public static int	EM_ME16		=59;		/* Toyota ME16 processor */
	public static int	EM_ST100	=60;		/* STMicroelectronics ST100 processor */
	public static int	EM_TINYJ	=61;		/* Advanced Logic Corp. TinyJ */
	/*	embedded processor family */
	public static int	EM_AMD64	=62;		/* AMDs x86-64 architecture */
	public static int	EM_X86_64	=EM_AMD64;	/* (compatibility) */

	public static int	EM_PDSP		=63;		/* Sony DSP Processor */
	public static int	EM_UNKNOWN64	=64;
	public static int	EM_UNKNOWN65	=65;
	public static int	EM_FX66		=66;		/* Siemens FX66 microcontroller */
	public static int	EM_ST9PLUS	=67;		/* STMicroelectronics ST9+8/16 bit */
	/*	microcontroller */
	public static int	EM_ST7		=68;		/* STMicroelectronics ST7 8-bit */
	/*	microcontroller */
	public static int	EM_68HC16	=69;		/* Motorola MC68HC16 Microcontroller */
	public static int	EM_68HC11	=70;		/* Motorola MC68HC11 Microcontroller */
	public static int	EM_68HC08	=71;		/* Motorola MC68HC08 Microcontroller */
	public static int	EM_68HC05	=72;		/* Motorola MC68HC05 Microcontroller */
	public static int	EM_SVX		=73;		/* Silicon Graphics SVx */
	public static int	EM_ST19		=74;		/* STMicroelectronics ST19 8-bit */
	/*	microcontroller */
	public static int	EM_VAX		=75;		/* Digital VAX */
	public static int	EM_CRIS		=76;		/* Axis Communications 32-bit */
	/*	embedded processor */
	public static int	EM_JAVELIN	=77;		/* Infineon Technologies 32-bit */
	/*	embedded processor */
	public static int	EM_FIREPATH	=78;		/* Element 14 64-bit DSP Processor */
	public static int	EM_ZSP		=79;		/* LSI Logic 16-bit DSP Processor */
	public static int	EM_MMIX		=80;		/* Donald Knuth's educational */
	/*	64-bit processor */
	public static int	EM_HUANY	=81;		/* Harvard University */
	/*	machine-independent */
	/*	object files */
	public static int	EM_PRISM	=82;		/* SiTera Prism */
	public static int	EM_AVR		=83;		/* Atmel AVR 8-bit microcontroller */
	public static int	EM_FR30		=84;		/* Fujitsu FR30 */
	public static int	EM_D10V		=85;		/* Mitsubishi D10V */
	public static int	EM_D30V		=86;		/* Mitsubishi D30V */
	public static int	EM_V850		=87;		/* NEC v850 */
	public static int	EM_M32R		=88;		/* Mitsubishi M32R */
	public static int	EM_MN10300	=89;		/* Matsushita MN10300 */
	public static int	EM_MN10200	=90;		/* Matsushita MN10200 */
	public static int	EM_PJ		=91;		/* picoJava */
	public static int	EM_OPENRISC	=92;		/* OpenRISC 32-bit embedded processor */
	public static int	EM_ARC_A5	=93;		/* ARC Cores Tangent-A5 */
	public static int	EM_XTENSA	=94;		/* Tensilica Xtensa architecture */
	public static int	EM_NUM		=95;

	public static int	EV_NONE		=0;	/* e_version, EI_VERSION */
	public static int	EV_CURRENT	=1;
	public static int	EV_NUM		=2;


	public static int	ELFOSABI_NONE		=0;	/* No extensions or unspecified */
	public static int	ELFOSABI_SYSV		=ELFOSABI_NONE;
	public static int	ELFOSABI_HPUX		=1;	/* Hewlett-Packard HP-UX */
	public static int	ELFOSABI_NETBSD		=2;	/* NetBSD */
	public static int	ELFOSABI_LINUX		=3;	/* Linux */
	public static int	ELFOSABI_UNKNOWN4	=4;
	public static int	ELFOSABI_UNKNOWN5	=5;
	public static int	ELFOSABI_SOLARIS	=6;	/* Sun Solaris */
	public static int	ELFOSABI_AIX		=7;	/* AIX */
	public static int	ELFOSABI_IRIX		=8;	/* IRIX */
	public static int	ELFOSABI_FREEBSD	=9;	/* FreeBSD */
	public static int	ELFOSABI_TRU64		=10;	/* Compaq TRU64 UNIX */
	public static int	ELFOSABI_MODESTO	=11;	/* Novell Modesto */
	public static int	ELFOSABI_OPENBSD	=12;	/* Open BSD */
	public static int	ELFOSABI_OPENVMS	=13;	/* Open VMS */
	public static int	ELFOSABI_NSK		=14;	/* Hewlett-Packard Non-Stop Kernel */
	public static int	ELFOSABI_AROS		=15;	/* Amiga Research OS */
	public static int	ELFOSABI_ARM		=97;	/* ARM */
	public static int	ELFOSABI_STANDALONE	=255;	/* standalone (embedded) application */


	/***************************************************************
	 * 
	 * Data Members
	 * 
	 ***************************************************************/
	private byte	e_ident[];	/* ident bytes */
	private int	e_type;			/* file type */
	private int	e_machine;		/* target machine */
	private int		e_version;		/* file version */
	private int		e_entry;		/* start address */
	private int		e_phoff;		/* phdr file offset */
	private int		e_shoff;		/* shdr file offset */
	private int		e_flags;		/* file flags */
	private int	e_ehsize;		/* sizeof ehdr */
	private int	e_phentsize;		/* sizeof phdr */
	private int	e_phnum;		/* number phdrs */
	private int	e_shentsize;		/* sizeof shdr */
	private int	e_shnum;		/* number shdrs */
	private int	e_shstrndx;		/* shdr string index */

	public ElfFileHeader(byte buffer[]) {
		e_ident = Arrays.copyOf(buffer, EI_NIDNET);
		e_type = ConversionUtil.byteArrayToShortBE(buffer, 16);
		e_machine = ConversionUtil.byteArrayToShortBE(buffer, 18);
		e_version = ConversionUtil.byteArrayToIntBE(buffer, 20);
		e_entry = ConversionUtil.byteArrayToIntBE(buffer, 24);
		e_phoff = ConversionUtil.byteArrayToIntBE(buffer, 28);
		e_shoff = ConversionUtil.byteArrayToIntBE(buffer, 32);
		e_flags = ConversionUtil.byteArrayToIntBE(buffer, 36);
		e_ehsize = ConversionUtil.byteArrayToShortBE(buffer, 40);
		e_phentsize =  ConversionUtil.byteArrayToShortBE(buffer, 42);
		e_phnum = ConversionUtil.byteArrayToShortBE(buffer, 44);
		e_shentsize = ConversionUtil.byteArrayToShortBE(buffer, 46);
		e_shnum = ConversionUtil.byteArrayToShortBE(buffer, 48);
		e_shstrndx = ConversionUtil.byteArrayToShortBE(buffer, 50);
	}

	public byte[] getE_ident() {
		return e_ident;
	}

	public int getE_type() {
		return e_type;
	}

	public int getE_machine() {
		return e_machine;
	}

	public int getE_version() {
		return e_version;
	}

	public int getE_entry() {
		return e_entry;
	}

	public int getE_phoff() {
		return e_phoff;
	}

	public int getE_shoff() {
		return e_shoff;
	}

	public int getE_flags() {
		return e_flags;
	}

	public int getE_ehsize() {
		return e_ehsize;
	}

	public int getE_phentsize() {
		return e_phentsize;
	}

	public int getE_phnum() {
		return e_phnum;
	}

	public int getE_shentsize() {
		return e_shentsize;
	}

	public int getE_shnum() {
		return e_shnum;
	}

	public int getE_shstrndx() {
		return e_shstrndx;
	}

}
