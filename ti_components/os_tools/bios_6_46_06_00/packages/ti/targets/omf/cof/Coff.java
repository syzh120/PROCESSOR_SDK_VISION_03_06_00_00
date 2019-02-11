package ti.targets.omf.cof;

import java.io.RandomAccessFile;
import java.io.IOException;
import java.util.HashMap;

/*
 *  ======== Coff ========
 */
public class Coff implements xdc.rta.IOFReader
{
    static final int NAMELEN = 8;
    static final int FILEHDRSIZE = 22;  /* "real" sizeof(COF_FileHdr) */
    static final int SECTHDRSIZE = 48;  /* "real" sizeof(COF_SectHdr) */
    static final int SYMBOLSIZE = 18;   /* "real" sizeof(COF_SectHdr) */

    static final int C28MAGIC = 0x9D;	/* Magic number for TI C28 COF  */
    static final int C30MAGIC = 0x93;	/* Magic number for TI C30 COF  */
    static final int C40MAGIC = 0x93;	/* Magic number for TI C40 COF  */
    static final int C50MAGIC = 0x92;	/* Magic number for TI C50 COF  */
    static final int C54MAGIC = 0x98; 	/* Magic number for TI C54 COF  */
    static final int C55MAGIC = 0x9c; 	/* Magic number for LEAD3 (C55) COF */
    static final int C56MAGIC = 0xA1; 	/* Magic number for Ryujin (C56) COF */
    static final int C62MAGIC = 0x99;	/* Magic number for TI C62x COF */
    static final int C80MAGIC = 0x95;	/* Magic number for TI C80 COF  */
    static final int ARMMAGIC = 0x97;	/* Magic number for TI ARM COF */
    static final int C430MAGIC = 0xA0;	/* Magic number for TI MSP430 COF */

    static final int VER0MAGIC = 0xc0;	/* TI version 0 COFF format */
    static final int VER1MAGIC = 0xc1;	/* TI version 1 COFF format */
    static final int VER2MAGIC = 0xc2;	/* TI version 2 COFF format */

    /*
     *  File Header flags
     */
    static final int F_VERS0 = 0x0;
    static final int F_VERS1 = 0x10;
    static final int F_VERS2 = 0x20;
    static final int F_VERS3 = 0x40;
    static final int F_VERS4 = 0x80;
    static final int F_VERSION = (F_VERS1 | F_VERS2 | F_VERS3 | F_VERS4);

    static final int F_LITTLE = 0x0100;
    static final int F_BIG = 0x0200;
    static final int F_AR32WR = 0x0040;
    static final int F_STRP30 = 0x1000;

    /*
     *  Section Header flags
     */
    static final int S_REG = 0x0000;    /* "regular" : allocated, relocated,
                                           loaded */
    static final int S_DSECT = 0x0001;	/* "dummy": not allocated, relocated,
                                           not loaded*/
    static final int S_NOLOAD = 0x0002;	/* "noload"  : allocated, relocated, */
                                        /* not loaded 			    */
    static final int S_GROUP = 0x0004;	/* "grouped" : formed of input
                                           sections */
    static final int S_PAD = 0x0008;	/* "padding" : not allocated, not
                                            relocated, loaded */
    static final int S_COPY = 0x0010;   /* "copy" : used for C init tables - 
                                                    not allocated, relocated,
                                                    loaded;  reloc & lineno
                                                    entries processed normally
                                         */
    static final int S_TEXT = 0x0020;   /* section contains text only */
    static final int S_DATA = 0x0040;   /* section contains data only */   
    static final int S_BSS = 0x0080;    /* section contains bss only */
    static final int S_CLINK = 0x4000;

    /*
     *  ======== Target ========
     *  Field mausize:
     *      Number of bytes in minimum addressable unit. 
     *  Field charsize:
     *      Number of bytes in a character. For the C6x, charsize = 1, since
     *      4 characters are packed into a word. For C55x, charsize = 2,
     *      since data memory is only word addressable, although mausize = 1
     *      (program memory is byte addressable).
     */
    static public class Target {
        public int      wordsize;   /* Size of a word */
        public int      mausize;    /* Size of minimum addressable unit */
        public int      charsize;   /* For C55, mausize= 1, but charsize = 2 */
        public int      ptrsize;    /* pointer size; C55L == 4, C55 == 2 */
        public boolean  bigendian;  /* big or little endian? */
        public short    magic;      /* target identifier */
        
        public Target(short magic, short flags) {

            this.magic = magic;
            
            bigendian = (flags & F_BIG) == 0 ? false : true;
            
            switch (magic) {
                case C30MAGIC: {    /* same as C40MAGIC */
                    wordsize = 4;
                    mausize = 4;
                    charsize = 4;
                    ptrsize = 4;
                    break;
                }
                case C50MAGIC: {
                    wordsize = 2;
                    mausize = 2;
                    charsize = 2;
                    ptrsize = 2;
                    break;
                }
                case C54MAGIC: {
                    wordsize = 2;
                    mausize = 2;
                    charsize = 2;
                    ptrsize = 2;
                    break;
                }
                case C62MAGIC: {
                    wordsize = 4;
                    mausize = 1;
                    charsize = 1;
                    ptrsize = 4;
                    break;
                }
                case C80MAGIC: {
                    wordsize = 4;
                    mausize = 1;
                    charsize = 1;
                    ptrsize = 4;
                    break;
                }
                case C55MAGIC: {
                    /*  Warning!!! HACK!!! This test was determined by reverse
                     *  engineering the COFF file header and may be wrong.
                     */
                    if ((flags & 0xf0) == 0xe0) {
                        /* C55L */
                        wordsize = 2;
                        mausize = 1;
                        charsize = 2;
                        ptrsize = 4;
                    }
                    else {
                        /* C55 */
                        wordsize = 2;
                        mausize = 1;
                        charsize = 2;
                        ptrsize = 2;
                    }
                    break;
                }
                case C56MAGIC: {
                    /* byte mode if f_vers1 bit set */
                    if ((flags & F_VERS1) != 0) {
                        /* C56 byte-mode */
                        wordsize = 2;
                        mausize = 1;
                        charsize = 1;
                        ptrsize = 4;
                    }
                    else {
                        /* C56 word-mode */
                        wordsize = 2;
                        mausize = 2;
                        charsize = 2;
                        ptrsize = 4;
                    }
                    break;
                }
                case ARMMAGIC: {
                    wordsize = 4;
                    mausize = 1;
                    charsize = 1;
                    ptrsize = 4;
                    break;
                }
                case C28MAGIC: {
                    wordsize = 2;
                    mausize = 2;
                    charsize = 2;
                    ptrsize = 2;
                    break;
                }
                case C430MAGIC: {
                    wordsize = 2;
                    mausize = 1;
                    charsize = 1;
                    ptrsize = 2;
                    break;
                }

                default: {
                    wordsize = 0;
                    mausize = 0;
                    charsize = 0;
                    ptrsize = 0;
                    break;
                }
            }
        }
    }
    
    /*
     *  ======== FileHeader ========
     */
    static public class FileHeader {
        public short   version;     /* version number */
        public short   nSects;      /* number of sections */
        public int     date;        /* time & date stamp */
        public int     symTabPtr;   /* file pointer to symtab */
        public int     nSyms;       /* number of symtab entries */
        public short   optHdrSize;  /* sizeof(optional hdr) */
        public short   flags;       /* flags */
        public short   magic;       /* magic number */
        public boolean swapped;
        public String  error;

        public void read(RandomAccessFile file)
            throws java.io.IOException
        {
            /* read the file data */
            file.seek(0);
            version = file.readShort();
            nSects = file.readShort();
            date = file.readInt();
            symTabPtr = file.readInt();
            nSyms = file.readInt();
            optHdrSize = file.readShort();
            flags = file.readShort();
            magic = file.readShort();

            /* check to see if file is swapped */
            swapped = false;
            if (version != VER0MAGIC
                && version != VER1MAGIC
                && version != VER2MAGIC) {
                swapped = true;
            }

            if (swapped) {
                version = Coff.swap(version);
                nSects = Coff.swap(nSects);
                date = Coff.swap(date);
                symTabPtr = Coff.swap(symTabPtr);
                nSyms = Coff.swap(nSyms);
                optHdrSize = Coff.swap(optHdrSize);
                flags = Coff.swap(flags);
                magic = Coff.swap(magic);
            }

            if (version != VER0MAGIC
                && version != VER1MAGIC
                && version != VER2MAGIC) {
                error = "Unrecognized file type";
                swapped = false;
            }
        }
        public String toString()
        {
            return ("version = 0x" + Integer.toHexString(version & 0xffff)
                + ", nSects = 0x" + Integer.toHexString(nSects & 0xffff)
                + ", magic = 0x" + Integer.toHexString(magic & 0xffff));
        }
    }
    
    /*
     *  ======== OptHeader ========
     */
    static public class OptHeader {
        public int  magic;      /* magic number                         */
        public int  vers;       /* version stamp                        */
        public int  textSize;    /* text size in bytes, padded to FW     */
        public int  dataSize;    /* initialized data "  "                */
        public int  bssSize;     /* uninitialized data "   "             */
        public int  entryPoint;  /* entry pt.                            */
        public int  textAddr;    /* base of text used for this file      */
        public int  dataAddr;    /* base of data used for this file      */

        public void read(RandomAccessFile file, boolean swapped)
            throws java.io.IOException
        {
            magic = file.readInt();
            vers = file.readInt();
            textSize = file.readInt();
            dataSize = file.readInt();
            bssSize = file.readInt();
            entryPoint = file.readInt();
            textAddr = file.readInt();
            dataAddr = file.readInt();
            if (swapped) {
                magic = Coff.swap(magic);
                vers = Coff.swap(vers);
                textSize = Coff.swap(textSize);
                dataSize = Coff.swap(dataSize);
                bssSize = Coff.swap(bssSize);
                entryPoint = Coff.swap(entryPoint);
                textAddr = Coff.swap(textAddr);
                dataAddr = Coff.swap(dataAddr);
            }
        }
    }

    /*
     *  ======== NameDesc ========
     */
    static public class NameDesc {
        int             immedFlag;
        int             ptr;
        public String   name;

        public void read(RandomAccessFile file, boolean swapped)
            throws java.io.IOException
        {
            name = "<long name>";

            /* save current location in file */
            long offset = file.getFilePointer();

            immedFlag = file.readInt();
            if (immedFlag == 0) {
                ptr = file.readInt();
                if (swapped) {
                    ptr = Coff.swap(ptr);
                }
            }
            else {
                /* re-read the name descripter as a byte array */
                byte [] nameBuf = new byte[NAMELEN];
                file.seek(offset);
                file.read(nameBuf);
                int i;
                for (i = 0; i < NAMELEN; i++) {
                    if (nameBuf[i] == 0) {
                        break;
                    }
                }
                name = new String(nameBuf, 0, i);
            }
        }
    }

    /*
     *  ======== SectHeader ========
     */
    static public class SectHeader {
        public NameDesc nameDesc =
                    new NameDesc();     /* name or offset into string table */
        public int      physAddr;       /* physical address */
        public int      virtAddr;       /* virtual address */
        public int      size;           /* section size */
        public int      dataPtr;        /* file ptr to raw data for section */
        public int      relocPtr;       /* file ptr to relocation */
        public int      linePtr;        /* file ptr to line numbers */

        public int      nRelocs;        /* number of relocation entries */
        public int      nLines;         /* number of line number entries */
        public int      flags;          /* section flags */
	
        public short    dummy;
        public short    pageNum;

        public void read(RandomAccessFile file, boolean swapped)
            throws java.io.IOException
        {
            nameDesc.read(file, swapped);
            physAddr = file.readInt();
            virtAddr = file.readInt();
            size = file.readInt();
            dataPtr = file.readInt();
            relocPtr = file.readInt();
            linePtr = file.readInt();
            nRelocs = file.readInt();
            nLines = file.readInt();
            flags = file.readInt();
            dummy = file.readShort();
            pageNum = file.readShort();
            if (swapped) {
                physAddr = Coff.swap(physAddr);
                virtAddr = Coff.swap(virtAddr);
                size = Coff.swap(size);
                dataPtr = Coff.swap(dataPtr);
                relocPtr = Coff.swap(relocPtr);
                linePtr = Coff.swap(linePtr);
                nRelocs = Coff.swap(nRelocs);
                nLines = Coff.swap(nLines);
                flags = Coff.swap(flags);
                pageNum = Coff.swap(pageNum);
            }
        }

        public String getName()
        {
            return (nameDesc.name);
        }

        public String toString()
        {
            return getName()
                + ": base = 0x" + Integer.toHexString(physAddr)
                + ", size = 0x" + Integer.toHexString(size)
                + " (" + size + ")";
        }
    }

    /* HashMap for caching the strings found by 'findString(addr)' */
    private HashMap<Long, String> addrToStr;
    
    /*
     *  ======== getFileHeader ========
     */
    public FileHeader getFileHeader()
    {
        return (fileHeader);
    }

    /*
     *  ======== getSectionHeader ========
     */
    public SectHeader getSectionHeader(int index)
    {
        if (index >= sectHeaders.length) {
            return (null);
        }
        return (sectHeaders[index]);
    }
    
    private static long unsToLong(int value)
    {
        long res = value;
        return (((res << 32) >>> 32));
    }

    /*
     *  ======== findString ========
     *  Return the target string located at the specified address
     *
     *  addr is an address as seen by the target; i.e., the value that
     *  would be displayed if the target were to call printf("0x%x", str).
     *
     *  This method only looks in TEXT, DATA or BSS sections and will
     *  return the string located in the first section whose address
     *  range contains the string address; if two sections overlap the
     *  first section in the file will always win.
     *  
     *  This method maintains a cache of the strings found to enable
     *  faster lookup if the string is requested repeatedly. 
     */
    public String findString(long addr)
    {
        String result;
        
        /* 
         * First, check the cache to see if the string has already been 
         * found. 
         */
        if ((result = addrToStr.get(addr)) != null) {
            return (result);
        }
        
        if (target.magic == C55MAGIC) {
            addr = addr * 2;    /* C55 data addrs are 1/2 prog mem addrs */
        }

        try {
            for (int i = 0; i < fileHeader.nSects; i++) {
                SectHeader header = sectHeaders[i];

                if ((header.flags & (S_TEXT | S_DATA | S_BSS)) == 0) {
                    /* skip non-target sections (debug, ...) */
                    continue;
                }

                long start = unsToLong(header.physAddr);
                long end = start + unsToLong(header.size);
                if (addr >= start && addr < end) {
                    long offset = unsToLong(header.dataPtr)
                        + target.mausize * (addr - start);
                    
                    result = readString(offset, target.charsize); 
                    
                    /* Add the string to the cache. */
                    addrToStr.put(addr, result);
                    
                    return (result);
                }
            }
        }
        catch (java.io.IOException e) {
            ;
        }
        
        return (null);
    }

    /*
     *  ======== findString ========
     *  Return the target string located at the specified address and section
     *
     *  addr is an address as seen by the target; i.e., the value that
     *  would be displayed if the target were to call printf("0x%x", str).
     *  
     *  This API does not currently implement caching of the located strings.
     */
    public String findString(long addr, String sectionName)
    {
        if (target.magic == C55MAGIC) {
            addr = addr * 2;    /* C55 data addrs are 1/2 prog mem addrs */
        }

        SectHeader header = findSectionHeader(sectionName);
        if (header != null) {
            long start = unsToLong(header.physAddr);
            long end = start + unsToLong(header.size);
            if (addr >= start && addr < end) {
                try {
                    long offset = unsToLong(header.dataPtr)
                        + target.mausize * (addr - start);
                    return (readString(offset, target.charsize));
                }
                catch (java.io.IOException e) {
                    ;
                }
            }
        }

        return (null);
    }

    /*
     *  ======== findSectionHeader ========
     */
    public SectHeader findSectionHeader(String name)
    {
        for (int i = 0; i < fileHeader.nSects; i++) {
            if (sectHeaders[i].getName().equals(name)) {
                return (sectHeaders[i]);
            }
        }

        return (null);
    }

    /*
     *  ======== toString ========
     */
    public String toString()
    {
        String result = "";

        result = fileHeader.toString();
    
        for (int i = 0; i < fileHeader.nSects; i++) {
            result = result.concat("\n" + sectHeaders[i].toString());
        }

        return (result);
    }

    /*
     *  ======== close ========
     */
    public void close()
        throws java.io.IOException
    {
        if (file != null) {
            file.close();
            isClosed = true;
        }
    }

    /*
     *  ======== reopen ========
     */
    public void reopen()
        throws java.io.IOException
    {
        if (isClosed) {
            file = new RandomAccessFile(curFileName, "r");
            isClosed = false;
        }
    }
    
    /*
     *  ======== parse ========
     */
    public String parse(String fileName)
        throws java.io.IOException
    {
        String result = "";
        
        if (file != null) {
            file.close();
            isClosed = true;
        }
        if (fileName == null) {
            return ("");
        }

        addrToStr = new HashMap<Long, String>();
        
        file = new RandomAccessFile(fileName, "r");
        curFileName = fileName;
        isClosed = false;
        
        /* read the file header, file if not a COFF file */
        fileHeader.read(file);
        if (fileHeader.error != null) {
            file.close();
            return (fileHeader.error);
        }

        /* determine the target, fail if not recognized */
        target = new Target(fileHeader.magic, fileHeader.flags);
        if (target.wordsize == 0) {
            file.close();
            return ("Error: unrecognized COFF type (magic = "
                + fileHeader.magic + ")");
        }

        fileHeaderSize = FILEHDRSIZE + fileHeader.optHdrSize;
        stringTabOffset = fileHeader.symTabPtr + fileHeader.nSyms * SYMBOLSIZE;

        /* seek to section header table */
        file.seek(fileHeaderSize);

        /* read each section header */
        sectHeaders = new SectHeader [fileHeader.nSects];
        for (int i = 0; i < fileHeader.nSects; i++) {
            sectHeaders[i] = new SectHeader();
            sectHeaders[i].read(file, fileHeader.swapped);
        }

        /* fixup section names */
        for (int i = 0; i < fileHeader.nSects; i++) {
            if (sectHeaders[i].nameDesc.immedFlag == 0) {
                long offset = stringTabOffset + sectHeaders[i].nameDesc.ptr;
                sectHeaders[i].nameDesc.name = readString(offset, 1);
            }
        }

        return (result);
    }

    /*
     *  ======== decimate ========
     */
    private int decimate(byte [] stringBuf, int df)
    {
        int len = stringBuf.length / df;
        int pos = target.bigendian ? (df - 1) : 0;

//        for (int i = 0; i < len; i++) System.out.print(stringBuf[i] + ":");
//        System.out.println("");

        for (int i = (target.bigendian ? 0 : 1); i < len; i++) {
            stringBuf[i] = stringBuf[df * i + pos];
        }

//        for (int i = 0; i < len; i++) System.out.print(stringBuf[i] + ":");
//        System.out.println("");
        
        return (len);
    }
    
    /*
     *  ======== readString ========
     */
    private String readString(long offset, int df)
        throws java.io.IOException
    {
        boolean done = false;
        String result = "";

        if (isClosed) {
            file = new RandomAccessFile(curFileName, "r");
        }
        file.seek(offset);

//        System.out.println("string at offset 0x" + Long.toHexString(offset));
        
        while (!done) {
            byte [] stringBuf = new byte[80];
            int n = file.read(stringBuf);
            if (n <= 0) {
                break;
            }

            if (df > 1) {
                n = decimate(stringBuf, df);
            }
            
            for (int i = 0; i < n; i++) {
                if (stringBuf[i] == 0) {
                    n = i;
                    done = true;
                    break;
                }
            }
            result = result.concat(new String(stringBuf, 0, n));
        }

        if (isClosed) {
            file.close();
        }

        return (result);
    }

    /*
     *  ======== swap ========
     */
    static short swap(short value)
    {
        int b1 = value & 0xff;
        int b2 = (value >> 8) & 0xff;
        
        return ((short)(b1 << 8 | b2));
    }

    static int swap(int value)
    {
        int b1 = (value >>  0) & 0xff;
        int b2 = (value >>  8) & 0xff;
        int b3 = (value >> 16) & 0xff;
        int b4 = (value >> 24) & 0xff;
        
        return (b1 << 24 | b2 << 16 | b3 << 8 | b4);
    }

    private RandomAccessFile file;
    private String curFileName = null;
    private boolean isClosed = true;
    private FileHeader fileHeader = new FileHeader();
    private SectHeader [] sectHeaders;
    private int fileHeaderSize = 0;
    private long stringTabOffset = 0;
    private Target target;
    
    /*
     *  ======== main ========
     */
    public static void main(String args[])
    {
        Coff coff = new Coff();

        try {
            for (int i = 0; i < args.length - 1; i += 2) {
                /* read COFF file */
                System.out.println(args[i] + " ...");
                String error = coff.parse(args[i]);
                if (error != "") {
                    System.out.println("Error: can't parse " + args[i]
                        + ": " + error);
                    continue;
                }

                /* display coff file */
                System.out.println(coff.toString());

                /* lookup a string from an address */
                long addr = Long.decode(args[i + 1]);
                String value = coff.findString(addr);
                if (value == null) {
                    System.out.println("Error: can't find string at "
                        + args[i + 1]);
                }
                else {
                    System.out.println(value);
                }

                /* look for string in the .const section */
                value = coff.findString(addr, ".const");
                if (value == null) {
                    System.out.println("Error: can't find string at "
                        + args[i + 1] + " within the .const section");
                }
                else {
                    System.out.println(value);
                }
            }

            /* close any open file associated with coff */
            coff.close();
        }
        catch (java.io.IOException e) {
            System.err.println("" + e);
        }
    }
}
