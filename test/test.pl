#!/usr/bin/env perl
use 5.012;
use warnings;

my @tests = qw(
    line
);

my $failed = 0;

for my $test (@tests) {
    my $testh = uc $test;
    print "===== TEST: $testh =====\n";
    system("mosml -P full $test.sml");
    my $diff = `compare -metric AE $test-exp.png $test-out.png null: 2>&1`;

    chomp($diff);
    my $status = $diff eq "0" ? "OK" : "FAIL ($diff)";
    $failed += 1 if $diff eq "0";

    print "===== TEST: $testh - $status =====\n";
}

exit($failed);
