<?php

$input = "";
$i = 0;
while ($line = fgets(STDIN)) {
	$input .= $line;
	$i++;
}

if ($i > 1) {
	file_put_contents('visual/input', $input);
	shell_exec('sh visual/vis.sh');
}

?>