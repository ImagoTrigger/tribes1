use common::sense;
use WebService::Discord::Webhook;

my $url = "https://discord.com/api/webhooks/********";
my $webhook = WebService::Discord::Webhook->new( $url );
$webhook->get();
print "Webhook posting as '" . $webhook->{name} ."' in channel " . $webhook->{channel_id} . "\n";
$webhook->execute( content => qq{$ARGV[0]\n$ARGV[1]\n$ARGV[2]\n$ARGV[3]\n$ARGV[4]} );
