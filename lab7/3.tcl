proc finish {} {
  global ns nf
  $ns flush-trace
  close $nf
  exec nam out.nam &
  exit 0
}

set ns [new Simulator]

$ns color 1 Red
$ns color 2 Blue
$ns color 3 Green
$ns color 4 Yellow
$ns color 5 Pink

set nf [open out.nam w]
$ns namtrace-all $nf

# create nodes
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]
set n5 [$ns node]
set n6 [$ns node]
set n7 [$ns node]
set n8 [$ns node]
set n9 [$ns node]
set n10 [$ns node]
set n11 [$ns node]

# setup server pool
$ns duplex-link $n0 $n2 10Mb 20ms DropTail
$ns duplex-link-op $n0 $n2 orient up

$ns duplex-link $n0 $n3 10Mb 20ms DropTail
$ns duplex-link-op $n0 $n3 orient right-up

$ns duplex-link $n0 $n4 10Mb 20ms DropTail
$ns duplex-link-op $n0 $n4 orient right

$ns duplex-link $n0 $n5 10Mb 20ms DropTail
$ns duplex-link-op $n0 $n5 orient right-down

$ns duplex-link $n0 $n6 10Mb 20ms DropTail
$ns duplex-link-op $n0 $n6 orient down

# setup client pool
$ns duplex-link $n1 $n7 10Mb 20ms DropTail
$ns duplex-link-op $n1 $n7 orient up

$ns duplex-link $n1 $n8 10Mb 20ms DropTail
$ns duplex-link-op $n1 $n8 orient left-up

$ns duplex-link $n1 $n9 10Mb 20ms DropTail
$ns duplex-link-op $n1 $n9 orient left

$ns duplex-link $n1 $n10 10Mb 20ms DropTail
$ns duplex-link-op $n1 $n10 orient left-down

$ns duplex-link $n1 $n11 10Mb 20ms DropTail
$ns duplex-link-op $n1 $n11 orient down

# connect both pools
$ns duplex-link $n1 $n0 1.5Mb 40ms DropTail
$ns duplex-link-op $n1 $n0 orient right

# setup n8 n2 as a ftp tcp link
set tcp1 [new Agent/TCP]
$ns attach-agent $n8 $tcp1
set sink1 [new Agent/TCPSink]
$ns attach-agent $n2 $sink1
$ns connect $tcp1 $sink1
$tcp1 set fid_ 1

set ftp1 [new Application/FTP]
$ftp1 attach-agent $tcp1
$ftp1 set type_ FTP

# setup n8 n3 as a ftp tcp link
set tcp2 [new Agent/TCP]
$ns attach-agent $n8 $tcp2
set sink2 [new Agent/TCPSink]
$ns attach-agent $n3 $sink2
$ns connect $tcp2 $sink2
$tcp2 set fid_ 2

set ftp2 [new Application/FTP]
$ftp2 attach-agent $tcp2
$ftp2 set type_ FTP

# setup n8 n4 as a ftp tcp link
set tcp3 [new Agent/TCP]
$ns attach-agent $n8 $tcp3
set sink3 [new Agent/TCPSink]
$ns attach-agent $n4 $sink3
$ns connect $tcp3 $sink3
$tcp3 set fid_ 3

set ftp3 [new Application/FTP]
$ftp3 attach-agent $tcp3
$ftp3 set type_ FTP

# setup n8 n5 as a ftp tcp link
set tcp4 [new Agent/TCP]
$ns attach-agent $n8 $tcp4
set sink4 [new Agent/TCPSink]
$ns attach-agent $n5 $sink4
$ns connect $tcp4 $sink4
$tcp1 set fid_ 4

set ftp4 [new Application/FTP]
$ftp4 attach-agent $tcp4
$ftp4 set type_ FTP

# setup n8 n6 as a ftp tcp link
set tcp5 [new Agent/TCP]
$ns attach-agent $n8 $tcp5
set sink5 [new Agent/TCPSink]
$ns attach-agent $n6 $sink5
$ns connect $tcp5 $sink5
$tcp5 set fid_ 5

set ftp5 [new Application/FTP]
$ftp5 attach-agent $tcp5
$ftp5 set type_ FTP

# events
$ns at 1.0 "$ftp1 start"
$ns at 1.5 "$ftp2 start"
$ns at 2.0 "$ftp3 start"
$ns at 2.5 "$ftp4 start"
$ns at 3.0 "$ftp5 start"
$ns at 7.5 "$ftp1 stop"
$ns at 8.0 "$ftp2 stop"
$ns at 8.5 "$ftp3 stop"
$ns at 9.0 "$ftp4 stop"
$ns at 9.5 "$ftp5 stop"
$ns at 10.0 "finish"

$ns run

