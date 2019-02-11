#!/usr/bin/perl

# Syntax
# ccperl cpytools.pl srcbase dstbase [enable_write]
#
# Copy tree specified from srcbase to dstbase.  If the enable_write parameter 
# is provided, then files are copied to and deleted from dstbase, to maintain
# an exact mirror of srcbase.  If the enable_write parameter is not provided,
# an exit status of 0 is returned if all of the files in srcbase are present
# in dstbase with same sizes and dates; If any of the files are missing or do
# not match, then a nonzero exit value is returned. 
#

# For DOS, change this to "command /c copy"

$copy="cmd /c copy";
$write_enabled = 0;
$error = 1;
$files_to_copy = 0;
$files_to_delete = 0;

$error = 0 if ($#ARGV == 1);
if ($#ARGV == 2) {
   if ($ARGV[2] eq "enable_write") {
      $write_enabled = 1;
	  $error = 0;
   }
}

errexit ("Syntax: ccperl $0 srcbase dstbase [enable_write]\n") if ($error);

# Now verify that srcbase exists
$srcbase = $ARGV[0];
errexit ("Source base directory invalid ($srcbase)\n") if ( !-d $srcbase);

# Set dstbase, error will "fall out" while trying to copy files
$dstbase = $ARGV[1];

# Get a list of files in $dstbase
@subdirs = ("$dstbase");

while (@subdirs) {
   $dir = pop (@subdirs);
   opendir (DIR, $dir) || next; 
   @files = readdir(DIR);
   closedir DIR;

   foreach $file (@files) {
      next if (($file eq ".") || ($file eq ".."));
	  if (-f "$dir/$file") {
         # Add files to checklist hash
		 $dstfiles{normalize("$dir/$file")} = 1;
      } elsif (-d "$dir/$file") {
         # Add directories to @subdirs
		 push @subdirs, "$dir/$file";
      }
   }
}

# Get a list of files in $srcbase
@subdirs = ("");
@cpylist = ();

while (@subdirs) {
   $reldir = pop (@subdirs);
   opendir DIR, "$srcbase$reldir" || errexit ("Can\'t read $srcbase$reldir\n"); 
   @files = readdir(DIR);
   closedir DIR;

   foreach $file (@files) {
      next if (($file eq ".") || ($file eq ".."));
	  if (-f "$srcbase$reldir/$file") {
	     # Process the file.
         $dstpath = normalize("$dstbase$reldir/$file");
		 
         # Mark file as present
         $dstfiles{"$dstpath"} = 0;

         push @cpylist, "$reldir/$file";
      } elsif (-d "$srcbase$reldir/$file") {
         # Add directories to @subdirs
		 push @subdirs, "$reldir/$file";
      }
   }
}

# Find any files that were in srcbase, but were not in dstfiles, and delete them
foreach $file (keys %dstfiles) {
   if ($dstfiles{"$file"}) {
      if ($write_enabled) {
         print "rm -f $file\n";
         chmod 0777, $file;
         unlink $file;
	  } else {
	     $files_to_delete ++;
	  }
   }
}

# Now copy source files to dest files; this is done after deletions so that
# files with incorrect case on case preserving but case insensitive filesystems
# are recopied with correct case.
for ($i=0; $i<=$#cpylist; $i++) {
   $srcpath = normalize("$srcbase$cpylist[$i]");
   $dstpath = normalize("$dstbase$cpylist[$i]");
   
   if ((-e $srcpath) && (-e $dstpath)) {
      @stats = stat($srcpath);              
      $srcmtime = $stats[9];
      $srcsize  = $stats[7];
      @stats = stat($dstpath);              
      $dstmtime = $stats[9];
      $dstsize  = $stats[7];
      next if (($srcmtime == $dstmtime) && ($srcsize == $dstsize));
   }
   
   if ($write_enabled) {
      makepath ($dstpath);
			
      if ((-e $dstpath) && (! -w $dstpath)) {
         print "rm -f $dstpath\n";
         chmod 0777, $dstpath;
         unlink $dstpath;
      }
      $cmd = dosnormalize("\"$srcpath\" \"$dstpath\"");
      print  "copy $cmd\n";
      $ret = system "$copy $cmd >nul";
      errexit ("Command ($cmd) failed\nCheck for cmd vs command\n") if ($ret != 0);
   } else {
      $files_to_copy ++;
   }
}

# Check and return error status
if (! $write_enabled) {
   if ($files_to_delete || $files_to_copy) {
      print "********************** UNSYNCHRONIZED TOOLS ***************************\n";
      print "In order to synchronize $dstbase,\n";
      print "need to delete $files_to_delete files, and copy $files_to_copy files.\n";
	  print "Rerun command with 'enable_write' parameter to perform synchronization\n";
	  print "********************** UNSYNCHRONIZED TOOLS ***************************\n";
	  exit (1);
   }
}
exit (0);

# Convert \ to /, and then // to /
sub normalize {
   my ($str) = @_;

   $str =~ s|\\|/|g;
   
   $str =~ s|/+|/|g;

   return "$str";
}

# Convert / to \, and then \\ to \
sub dosnormalize {
   my ($str) = @_;

   $str =~ s|/|\\|g;
   
   $str =~ s|\\+|\\|g;

   return "$str";
}

sub makepath {
   my ($path) = @_;

   @components = split /\//, $path;
   # Dispose of file name part
   pop(@components);  
   
   $first = 1;
   $path = "";
   foreach $component (@components) {
      $path = $path . "$component";

      if ($first) {
         # Skip through the drive letter
		 $first = 0;
		 if ($component =~ /^[A-Za-z]:$/) {
            $path = $path . "/";
			next;
         }
      }
	  if (! -e $path) {
  	     print "mkdir $path\n";
         mkdir "$path",0777;
      }
      errexit ("Destination must be directory: ($path)") if (! -d $path);

	  $path = $path . "/";
   }
}

sub errexit {
  my ($msg) = @_;
  
  print $msg;
  exit(5);
}
