use common::sense;
use WebService::Discord::Webhook;

my $url = "https://discord.com/api/webhooks/*****";
my $webhook = WebService::Discord::Webhook->new( url => $url, wait => 1);
$webhook->get();
print "Webhook posting as '" . $webhook->{name} ."' in channel " . $webhook->{channel_id} . "\n";
open(LAST,'discord4.txt');
my $id = <LAST>;
close LAST;
my $curl = 'curl -X DELETE '.$url .'/messages/'.$id;
`$curl`;
my $return = $webhook->execute( content => qq{$ARGV[0]\n$ARGV[1]\n$ARGV[2]\n$ARGV[3]\n$ARGV[4]} );
open(LAST,'>discord4.txt');
print LAST $return->{id};
close LAST;




