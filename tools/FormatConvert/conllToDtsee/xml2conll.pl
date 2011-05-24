#!/usr/bin/perl -w
use strict;

if (scalar @ARGV != 2) {
	print STDERR "usage: xxx.pl xml.txt conll.txt\n";
	exit(0);
}

my $in_file = $ARGV[0];
my $out_file = $ARGV[1];

open IN, "<$in_file" or die "open in file err: $in_file";
# <?xml version="1.0" encoding="gbk" ?>
# <xml4nlp>
    # <note sent="y" word="y" pos="y" ne="y" parser="y" wsd="y" srl="y" />
    # <doc>
        # <para id="0">
            # <sent id="0" cont="我爱北京天安门。">
                # <word id="0" cont="我" wsd="Aa02" wsdexp="我_我们" pos="r" ne="O" parent="1" relate="SBV" />
                # <word id="1" cont="爱" wsd="Gb09" wsdexp="喜欢_爱" pos="v" ne="O" parent="-1" relate="HED">
                    # <arg id="0" type="A0" beg="0" end="0" />
                    # <arg id="1" type="A1" beg="3" end="3" />
                # </word>
                # <word id="2" cont="北京" wsd="Di03" wsdexp="首都_省会" pos="ns" ne="B-Ns" parent="3" relate="ATT" />
                # <word id="3" cont="天安门" wsd="Bn01" wsdexp="建筑_房屋" pos="ns" ne="E-Ns" parent="1" relate="VOB" />
                # <word id="4" cont="。" wsd="-1" wsdexp="" pos="wp" ne="O" parent="-2" relate="PUN" />
            # </sent>
        # </para>
    # </doc>
# </xml4nlp>

open OUT, ">$out_file" or die "open out file err: $out_file";
# 1	我	我	r	r	-	2	SBV	-	-
# 2	爱	爱	v	v	-	0	HED	-	-
# 3	北京	北京	ns	ns	-	4	ATT	-	-
# 4	天安门	天安门	ns	ns	-	2	VOB	-	-
# 5	。	。wp	wp	-	2	PUN	-	-

while (<IN>) {
	chomp($_);
	if($_ =~ /word id="(\d+)" cont="(\S+)" wsd="\S+" wsdexp="\S*" pos="(\S+)" ne="\S+" parent="-(\d+)" relate="(\w+)###(\S+)"/){
		print OUT "$6\n";
		print OUT $1+1 . "\t$2\t$2\t$3\t$3\t_\t0\t$5\t_\t_\n";
	}
	if($_ =~ /word id="(\d+)" cont="(\S+)" wsd="\S+" wsdexp="\S*" pos="(\S+)" ne="\S+" parent="(\d+)" relate="(\w+)###(\S+)"/){
		print OUT "$6\n";
		my $parent = $4+1;
		print OUT $1+1 . "\t$2\t$2\t$3\t$3\t_\t" . $parent . "\t$5\t_\t_\n";
	}
	if($_ =~ /word id="(\d+)" cont="(\S+)" wsd="\S+" wsdexp="\S*" pos="(\S+)" ne="\S+" parent="-(\d+)" relate="(\w+)"/){
		print OUT $1+1 . "\t$2\t$2\t$3\t$3\t_\t0\t$5\t_\t_\n";
	}
	if($_ =~ /word id="(\d+)" cont="(\S+)" wsd="\S+" wsdexp="\S*" pos="(\S+)" ne="\S+" parent="(\d+)" relate="(\w+)"/){
		my $parent = $4+1;
		print OUT $1+1 . "\t$2\t$2\t$3\t$3\t_\t" . $parent . "\t$5\t_\t_\n";
	}
}
print OUT "\n";

close IN;
close OUT;
