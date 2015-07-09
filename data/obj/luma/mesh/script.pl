#!/usr/bin/perl

open(FILE,"Creature.obj");
open(FILE1,">Luma.obj");
foreach $riga (<FILE>){
  if($riga =~ /^f/){
	chop $riga;
	chop $riga;
	print FILE1 "$riga\n";
	
  }
  else{
	print FILE1 $riga;
  }
  
}

close(FILE1);
close(FILE);