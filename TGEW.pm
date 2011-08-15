package TGEW;

sub base_dir() {
    return $ENV{'HOME'} . "/.tge";
}

sub tempscript_dir() {
    return base_dir() . "/tempscript";
}

sub log_dir() {
    return base_dir() . "/log";
}

sub masterlog_path() {
    return log_dir() . "/message";
}

sub execdb_path() {
    return base_dir() . "/execdb";
}

sub rc_path() {
    return base_dir() . "/.tgerc";
}

sub fsrc_path() {
    return base_dir() . "/.tgefs";
}

sub config_path() {
    return base_dir() . "/.tgerc";
}

sub is_installed() {
    return -e base_dir();
}

use FileHandle;
sub get_parameters() {
    my %retval;
    my $configFileName = config_path();
    my $fh = new FileHandle "< $configFileName";
    return undef unless(defined $fh);
    while(<$fh>) {
	chomp;
	next if(/^\s*$/);
	next if(/^\s*#/);
	m|^(\S+)=(.*)$|;
	my $leftHand  = $1;
	my $rightHand = $2;
	$retval{$leftHand} = $rightHand;
    }
    $fh->close();
    return \%retval;
}

1;
