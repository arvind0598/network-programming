proc stop {} {
  global ns tracefd namtrace
  $ns flush-trace
  close $tracefd
  close $namtrace
  exec nam out.nam
}

set val(chan) Channel/WirelessChannel
set val(prop) Propagation/TwoRayGround
set val(netif) Phy/WirelessPhy
set val(mac) Mac/802_11
set val(ifq) Queue/DropTail/PriQueue
set val(ifqlen) 50
set val(ll) LL
set val(ant) Antenna/OmniAntenna
set val(nn) 10
set val(rp) AODV
set val(x) 600
set val(y) 600
set val(stop) 150

set ns [new Simulator]
set tracefd [open out.tr w]
set namtrace [open out.nam w]

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

$node_(0) set X_ 300
$node_(0) set Y_ 550
$node_(0) set Z_ 0.0

$node_(1) set X_ 400
$node_(1) set Y_ 450
$node_(1) set Z_ 0.0

$node_(2) set X_ 500
$node_(2) set Y_ 350
$node_(2) set Z_ 0.0

$node_(3) set X_ 500
$node_(3) set Y_ 250
$node_(3) set Z_ 0.0

$node_(4) set X_ 400
$node_(4) set Y_ 150
$node_(4) set Z_ 0.0

$node_(5) set X_ 300
$node_(5) set Y_ 50
$node_(5) set Z_ 0.0

$node_(6) set X_ 200
$node_(6) set Y_ 150
$node_(6) set Z_ 0.0

$node_(7) set X_ 100
$node_(7) set Y_ 250
$node_(7) set Z_ 0.0

$node_(8) set X_ 100
$node_(8) set Y_ 350
$node_(8) set Z_ 0.0

$node_(9) set X_ 200
$node_(9) set Y_ 450
$node_(9) set Z_ 0.0

# setup tcp 0 1
set tcp [new Agent/TCP/Newreno]
set sink [new Agent/TCPSink]
$ns attach-agent $node_(0) $tcp
$ns attach-agent $node_(1) $sink
$ns connect $tcp $sink
set ftp [new Application/FTP]
$ftp attach-agent $tcp
$ns at 10.0 "$ftp start"

# setup udp 0 2
set udp [new Agent/UDP]
set null [new Agent/Null]
$ns attach-agent $node_(0) $udp
$ns attach-agent $node_(9) $null
$ns connect $udp $null
set cbr [new Application/Traffic/CBR]
$cbr attach-agent $udp
$ns at 10.0 "$cbr start"


for { set i 0 } { $i < $val(nn) } { incr i } {
  $ns initial_node_pos $node_($i) 30
  $ns at $val(stop) "$node_($i) reset";
}

# end simulation
$ns at $val(stop) "$ns nam-end-wireless $val(stop)"
$ns at $val(stop) "stop"
$ns at 150.01 "$ns halt"

$ns run
