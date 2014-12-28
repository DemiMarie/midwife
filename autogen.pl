#!/usr/bin/perl -w-
eval 'if test $# -eq 0; then exec /usr/bin/perl -W- "$0"
else exec perl -W- "$0" "$@"; fi'
  if 0;
use strict;
use warnings;
require File::Spec;
require File::Path;
{
	my @path = File::Spec->splitpath($0);
	my $curdir = File::Spec->catpath($path[0],$path[1],'.');
	chdir $curdir;
}
unlink 'package.m4';
unlink 'aclocal.m4';
File::Path::remove_tree('autom4te.cache');
$| = 1;
use autodie;
system 'autoreconf', qw(--install -Wall -Werror);
exec 'autom4te', qw(-Wall -Werror 
--language=autotest
--output=tests/testsuite
tests/testsuite.at)
