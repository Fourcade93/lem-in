<?php

$arr = explode(PHP_EOL, trim(file_get_contents('input')));
$rooms = "";
$connections = "";
$output = "";
$start = 0;
$end = 0;

foreach ($arr as $val) {
	if ($start)
	{
		$startRoom = substr($val, 0, strpos($val, " "));
		$start = 0;
	}
	if (preg_match('/^##start$/', $val))
		$start = 1;
	if ($end)
	{
		$endRoom = substr($val, 0, strpos($val, " "));
		$end = 0;
	}
	if (preg_match('/^##end$/', $val))
		$end = 1;
	if (preg_match('/[^#]+(.+)? ([0-9]+) ([0-9]+)$/', $val))
		$rooms .= $val.PHP_EOL;
	if (preg_match('/^[^#L]([^-]+)?-([^-]+)$/', $val))
		$connections .= $val.PHP_EOL;
	if (preg_match('/^L/', $val))
		$output .= $val.PHP_EOL;
	if (preg_match('/^[0-9]+$/', $val))
		$ants = $val;
}

if (isset($_GET['rooms'])) {
	echo trim($rooms);
}
if (isset($_GET['connections'])) {
	echo trim($connections);
}
if (isset($_GET['output'])) {
	echo trim($output);
}
if (isset($_GET['start'])) {
	echo $startRoom;
}
if (isset($_GET['end'])) {
	echo $endRoom;
}
if (isset($_GET['ants'])) {
	echo $ants;
}

?>