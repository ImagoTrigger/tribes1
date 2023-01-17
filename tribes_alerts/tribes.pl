use common::sense;
my $cmd = "qstat.exe -of stats.txt -R -ne -nh -default tbm t1m1.pu.net:28000";
my $oldplayers = 0;

while (1) {
	my $base = 0; my $ann = 0; my $rpg = 0; my $other = 0;
	system($cmd);
	open(STATS,"stats.txt");
	my @lines = <STATS>;
	close STATS;
	my $players = 0;
	my $ln = 0;
	foreach my $line (@lines) {
		if ($line =~ /(\d+)\//) {
			my $temp = $1;
			$players += $1;
			if ($lines[$ln+1] =~ /mods=annihilation/i) {
				$ann += $temp;
			} elsif ($lines[$ln+1] =~ /mods=base/i) {
				$base += $temp;
			} elsif ($lines[$ln+1] =~ /mods=rpg/i) {
				$rpg += $temp;
			} else {
				$other += $temp;
			}
		}
		$ln++;
	}
  	if ($oldplayers != $players && $players >= 10) {
                $oldplayers = $players;
		my $tweet = ":satellite: There are **$players** active players! :fire:";
		print "$tweet\n";
		my $cmd = "python tweet.py $players $base $ann $rpg $other";
		my $r = `$cmd`;
                my $cmd2 = "perl discord4.pl \"$tweet\" \"```- $base in LT base\" \"- $ann in Annihilation\" \"- $rpg in RPG\" \"- $other in Other```\" ";
                my $r = `$cmd2`;
	} else {
		print "no change\n";
	}
	sleep 60 * 20;
}