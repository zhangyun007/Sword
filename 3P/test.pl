#!/usr/bin/perl

# ppm install DBD::mysql

use DBI;

# use strict;

my $dbname = "test";
my $location = "localhost";
my $port = "3306"; 

my $database = "DBI:mysql:$dbname:$location:$port";

my $db_user = "root";
my $db_pass = "";
my $dbh = DBI->connect($database,$db_user,$db_pass);

my $sql = "SELECT * FROM y2k";
my $sth = $dbh->prepare($sql);

$sth->execute() or die "Cannot execute: $dbh->errstr"; 

while ( @row = $sth->fetchrow_array ) {
  print "@row\n";
}


#$rows = $dbh->do("INSERT INTO y2k VALUES ('2000-02-28','2000-02-28 00:00:00',20000228000000)") 
#   or die "Couldn't insert record : $DBI::errstr";

#print "$rows row(s) added to y2k\n";

$dbh->disconnect;