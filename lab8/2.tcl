set val(chan) Channel/WirelessChannel
set val(prop) Propagation/TwoRayGround
set val(netif) Phy/WirelessPhy
set val(mac) Mac/802_11
set val(ifq) Queue/DropTail/PriQueue
set val(ifqlen) 50
set val(ll) LL
set val(ant) Antenna/OmniAntenna
set val(nn) 8
set val(rp) AODV
set val(x) 600
set val(y) 600
set val(stop) 150

set ns [new Simulator]
set tracefd [open out2.tr w]
set namtrace [open out2.nam w]

$ns trace-all $tracefd
$ns namtrace-all-wireless $namtrace $val(x) $val(y)

set topo [new Topography]
$topo load_flatgrid $val(x) $val(y)

create-god $val(nn)

$ns node-config \
  -adhocRouting $val(rp) \
  -llType $val(ll) \
  -macType $val(mac) \
  -ifqType $val(ifq) \
  -ifqLen $val(ifqlen) \
  -antType $val(ant) \
  -propType $val(prop) \
  -phyType $val(netif) \
  -channelType $val(chan) \
  -topoInstance $topo \
  -agentTrace ON \
  -routerTrace ON \
  -macTrace OFF \
  -movementTrace ON

for { set i 0 } { $i < $val(nn) } { incr i } {
  set node_($i) [$ns node]
}

$node_(0) set X_ 250
$node_(0) set Y_ 400
$node_(0) set Z_ 0.0

$node_(1) set X_ 150.0
$node_(1) set Y_ 250.0
$node_(1) set Z_ 0.0

$node_(2) set X_ 250.0
$node_(2) set Y_ 250.0
$node_(2) set Z_ 0.0

$node_(3) set X_ 350.0
$node_(3) set Y_ 250.0
$node_(3) set Z_ 0.0

$node_(4) set X_ 100.0
$node_(4) set Y_ 50.0
$node_(4) set Z_ 0.0

$node_(5) set X_ 200.0
$node_(5) set Y_ 50.0
$node_(5) set Z_ 0.0

$node_(6) set X_ 300.0
$node_(6) set Y_ 50.0
$node_(6) set Z_ 0.0

$node_(7) set X_ 400.0
$node_(7) set Y_ 50.0
$node_(7) set Z_ 0.0

# setup tcp 4 1
set tcp4 [new Agent/TCP/Newreno]
set sink1 [new Agent/TCPSink]
$ns attach-agent $node_(4) $tcp4
$ns attach-agent $node_(1) $sink1
$ns connect $tcp4 $sink1
set ftp1 [new Application/FTP]
$ftp1 attach-agent $tcp4
$ns at 10.0 "$ftp1 start"

# setup tcp 1 0
set tcp1 [new Agent/TCP/Newreno]
set sink0 [new Agent/TCPSink]
$ns attach-agent $node_(1) $tcp1
$ns attach-agent $node_(0) $sink0
$ns connect $tcp1 $sink0
set ftp2 [new Application/FTP]
$ftp2 attach-agent $tcp1
$ns at 10.0 "$ftp2 start"

for { set i 0 } { $i < $val(nn) } { incr i } {
  $ns initial_node_pos $node_($i) 30
  $ns at $val(stop) "$node_($i) reset";
}

# end simulation
$ns at $val(stop) "$ns nam-end-wireless $val(stop)"
$ns at $val(stop) "stop"
$ns at 150.01 "$ns halt"

proc stop {} {
  global ns tracefd namtrace
  $ns flush-trace
  close $tracefd
  close $namtrace
  exec nam out2.nam & 
}

$ns run