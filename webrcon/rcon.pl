use common::sense;
use CGI;
use Net::Telnet::Wrapper;

my $c = CGI->new;
my $vars = $c->Vars;
my $w = Net::Telnet::Wrapper->new('Prompt' => '/\% /', 'device_class' => 'Unix::General', -host => 'localhost');
sleep 1;
$w->print("logic");
sleep 1;
my $data = $c->param('POSTDATA');
$w->cmd($vars->{'command'});
print $c->redirect('/tribes/#OK:'.$vars->{'command'});
exit;