#!/usr/bin/perl -w
use strict;

# 2008-04-11 modified by Nash


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
while (my $word_line = <IN>) 
{
	print "$sent_ctr\n" if (++$sent_ctr % 1000) == 0;	
	
	my $tag_line = <IN>;
	my $dep_line = <IN>;
	my $rel_line = <IN>;
	my $blank_line = <IN>;

	$word_line =~ s/\s+$//;
	$tag_line =~ s/\s+$//;
	$dep_line =~ s/\s+$//;
	$rel_line =~ s/\s+$//;
	$line_ctr += 5;
	
	last if ($word_line eq ""  or $tag_line eq "" or $dep_line eq "" or $rel_line eq "");
	
#	my @word = split(/\s+/, $word_line);
#	my @tag = split(/\s+/, $tag_line);
#	my @dep = split(/\s+/, $dep_line);
#	my @rel = split(/\s+/, $rel_line);

	my @word = split(/\t/, $word_line);
	my @tag = split(/\t/, $tag_line);
	my @dep = split(/\t/, $dep_line);
	my @rel = split(/\t/, $rel_line);
	
	if (scalar @word != scalar @tag or scalar @dep != scalar @rel or scalar @word != scalar @dep) {
		print STDERR "format err at line: $line_ctr: at sent: $sent_ctr: tokens num not equal.\n";
		printf STDERR "word: %d\npos: %d\nhead: %d\ndeprel: %d\n", scalar @word, scalar @tag, scalar @dep, scalar @rel;
		exit(0);
	}
	my @line1 = ();
	my @line2 = ();
	my @line3 = ();
	my $word_num = scalar @word;
	my $EOS_id = $word_num + 1;
	for my $i (0..$word_num-1) {
		$rel[$i] = "" if !defined($rel[$i]);
		push(@line1, "$word[$i]/$tag[$i]");
		my $id = $i + 1;
		push(@line2, "[$id]$word[$i]/$tag[$i]");

		if ($dep[$i] == 0) {
			push(@line3, "[$id]$word[$i]_[$EOS_id]<EOS>($rel[$i])");
		} else { 
			my $father_id = $dep[$i] - 1;
			push(@line3, "[$id]$word[$i]_[$dep[$i]]$word[$father_id]($rel[$i])");
		}
	}
	push(@line2, "[$EOS_id]<EOS>/<EOS>");
	
	print OUT join(" ", @line1), " \n";
	print OUT join(" ", @line2), " \n";
	print OUT join("\t\t", @line3), "\t\t\n";	
}

print STDERR "sent_ctr: $sent_ctr\n";
print STDERR "line_ctr: $line_ctr\n";
close IN;
close OUT;