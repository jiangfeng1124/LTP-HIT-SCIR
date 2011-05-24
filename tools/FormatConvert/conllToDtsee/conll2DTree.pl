#!/usr/bin/perl -w
use strict;



if (scalar @ARGV != 2) {
	print STDERR "format: xxx.pl in_file_5ln out_file_DTSee\n";
	exit(0);
}

my $in_file = $ARGV[0];
my $out_file = $ARGV[1];

open IN, "<$in_file" or die "open in file err: $in_file";
open OUT, ">$out_file" or die "open out file err: $out_file";

#迈向/v 充满/v 希望/n 的/u 新/a 世纪/n ——/wp 一九九八年/nt 新年/nt 讲话/n
#[1]迈向/v [2]充满/v [3]希望/n [4]的/u [5]新/a [6]世纪/n [7]——/wp [8]一九九八年/nt [9]新年/nt [10]讲话/n ... [17]<EOS>/<EOS> 
#[1]迈向_[6]世纪(VOB)		[2]充满_[3]希望(VOB)		[6]世纪_[4]的(ATT)		[17]<EOS>_[1]迈向(HED)

my $line_ctr = 0;
my $sent_ctr = 0;
my $word_num = 0;
my @line1 = ();
my @line2 = ();
my @line3 = ();	
my @allword = ();
my @alltag = ();
my @allparent = ();
my @allrel = ();
while (my $line = <IN>) 
{
	print "$sent_ctr\n" if (++$sent_ctr % 1000) == 0;	
	
	$line =~ s/\s+$//;
	if($line_ctr == 0){
		@line1 = ();
		@line2 = ();
		@line3 = ();	
		@allword = ();
		@alltag = ();
		@allparent = ();
		@allrel = ();
	}
	$line_ctr++;
	if ($line eq "" ){
		$word_num = scalar @allword;
		my $EOS_id = $word_num +1;
		for my $i (0..$word_num-1) {
			#$allrel[$i] = "" if !defined($allrel[$i]);
			push(@line1, "$allword[$i]/$alltag[$i]");
			my $id = $i + 1;
			push(@line2, "[$id]$allword[$i]/$alltag[$i]");
			if ($allparent[$i] == 0) {
				push(@line3, "[$EOS_id]<EOS>_[$id]$allword[$i](HED)");
			} else { 
				my $father_id = $allparent[$i] - 1;
				push(@line3, "[$allparent[$i]]$allword[$father_id]_[$id]$allword[$i]($allrel[$i])");
			}
		}
		
		push(@line2,"[$EOS_id]<EOS>/<EOS>");
		print OUT join(" ", @line1), " \n";
		print OUT join(" ", @line2), " \n";
		print OUT join("\t\t", @line3), "\t\t\n";
		$line_ctr = 0;
		@line1 = ();
		@line2 = ();
		@line3 = ();	
		@allword = ();
		@alltag = ();
		@allparent = ();
		@allrel = ();
	}
	else{
		#print $line."\n";
		my @word = split(/\t/, $line);
		push(@allword, $word[1]);
		push(@alltag, $word[3]);
		push(@allparent, $word[6]);
		push(@allrel, $word[7]);
	}	
}

print STDERR "sent_ctr: $sent_ctr\n";
print STDERR "line_ctr: $line_ctr\n";
close IN;
close OUT;