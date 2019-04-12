use File::Basename;
use Cwd;

$n = 3;
$n += 2;
$s = "I am a string";
my $cwd = getcwd;

print "6*7\n";
print "$n\n";
print "$s\n";
print "$cwd\n";

chomp($line = <STDIN>);

if ($line eq "\n") {
    print "It is a blank line\n";
} else {
    print "Line is $line\n";
}

while ($count < 10) {
    $count += 2;
    print "count is now $count\n"
}


my $name = "/usr/local/bin/perl";
my $basename = basename $name;
my $dirname = dirname $name;
print "$basename \n $dirname";