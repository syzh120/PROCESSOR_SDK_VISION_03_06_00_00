use POSIX;

$fname   = $ARGV[0];
$width   = $ARGV[1];
$height  = $ARGV[2];
$downScaleFactor = $ARGV[3];
$isBayer = 0;

$width = $width / $downScaleFactor;
$width = $width + 1;
$height = $height / $downScaleFactor;
$height = $height + 1;

#print $fname . "\n";

$fname_out = $fname . ".bin";
open(FI, "<$fname") || die ("Cannot open $fname \n");
open(FO, ">$fname_out") || die ("Cannot open $fname_out \n");
binmode(FO);

$x = 0;
$y = 0;
$cnt = 0;
while(<FI>)
{
    $line = $_;
    chomp($line);
    $line =~ s/\t/    /g;
    $line =~ s/^/ /g;
    if($isBayer == 0)
    {
        $line =~ m/\ *([-|\ ]\d*)\ *([-|\ ]\d*)/;
        $dx = $1;
        $dy = $2;
        #print $dx . "\n";
        #print $dy . "\n";
        $cnt = $cnt + 1;

        $val = (($dy & 0xFFFF) | (($dx & 0xFFFF) << 16));
        print FO pack('i<',$val) ;
    }
    else
    {
        $line =~ m/\ *([-|\ ]\d*)\ *([-|\ ]\d*)\ *([-|\ ]\d*)\ *([-|\ ]\d*)/;
        $dx  = $1;
        $dy  = $2;
        $dx2 = $3;
        $dy2 = $4;
        #print $dx . "\n";
        #print $dy . "\n";
        #print $dx2 . "\n";
        #print $dy2 . "\n";
        $cnt = $cnt + 1;
        $cnt = $cnt + 1;

        $val = (($dy & 0xFFFF) | (($dx & 0xFFFF) << 16));
        print FO pack('i<',$val) ;
        $val = (($dy2 & 0xFFFF) | (($dx2 & 0xFFFF) << 16));
        print FO pack('i<',$val) ;
    }

    $x = $x + 1;
    if($x >= $width)
    {
        $y = $y + 1;
        $x = 0;
        $tmp = floor(($width + 15)/16)*16 - $width;
        if($isBayer == 1)
        {
            $tmp = floor(($width + 15)/16)*16 - $width;
        }
        while($tmp > 0)
        {
            if($isBayer == 1)
            {
                print FO pack('i<', 0);
            }
            print FO pack('i<', 0);
            $tmp = $tmp - 1;
        }
    }
}

if($cnt != $width*$height)
{
    print("Incorrect dimensions\n");
}

#print "Output: " . floor(($width + 15)/16)*16 . " x $height";
