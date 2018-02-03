<!DOCTYPE html>
<html>
<head lang="en">
	<meta charset="utf-8">
	<title>Visual</title>
	<link rel="stylesheet" type="text/css" href="style.css">
	<script
  		src="https://code.jquery.com/jquery-3.3.1.min.js"
  		integrity="sha256-FgpCb/KJQlLNfOu91ta32o/NMZxltwRo8QtmkMRdAu8="
  		crossorigin="anonymous"></script>
	<script src="https://cdnjs.cloudflare.com/ajax/libs/jcanvas/20.1.4/min/jcanvas.min.js"></script>
</head>
<body>
	<canvas id="canvas" width="1600" height="1100">
		
	</canvas>
	<script>
		var canvas;
var ctx;
var rooms;
var start;
var end;
var moves;
var ants;

function roomsFactory(rooms) {
	rooms = rooms.split('\n');
	var len = rooms.length;
	var	ret = {};
	for (var i = 0; i < len; i++) {
		var one = rooms[i].split(' ');
		ret[one[0]] = {x : (parseInt(one[1]) + 1) * 50, y : (parseInt(one[2]) + 1) * 50};
	}
	return ret;
}

function connectFactory(connections) {
	connections = connections.split('\n');
	var len = connections.length;
	var ret = [];
	for (var i = 0; i < len; i++) {
		var one = connections[i].split('-');
		ret.push([one[0], one[1]]);
	};
	return ret;
}

function movesFactory(data) {
	data = data.split('\n');
	var ret = [];
	var len = data.length;
	for (var i = 0; i < len; i++) {
		var obj = {};
		var singl = data[i].split(' ');
		for (var j = 0; j < singl.length; j++) {
			var one = singl[i].split('-');
			obj[one[0]] = one[1];
		};
		ret.push(obj);
	}
	return ret;
}

$(document).ready(function() {
	canvas = $('#canvas');
	$.get('get_input.php?rooms=get', function(data, status) {
		rooms = roomsFactory(data);
	});
	$.get('get_input.php?start=get', function(data, status) {
		start = data;
	});
	$.get('get_input.php?end=get', function(data, status) {
		end = data;
	});
	$.get('get_input.php?ants=get', function(data, status) {
		ants = parseInt(data);
	});
	$.get('get_input.php?output=get', function(data, status) {
		moves = movesFactory(data);
	});
	$.get('get_input.php?connections=get', function(data, status) {
		var connections = connectFactory(data);
		for (var i = 0; i < connections.length; i++) {
			if (connections[i][0]) {
				canvas.drawLine({
					layer: true,
					strokeStyle: 'blue',
					strokeWidth: 4,
					x1: rooms[connections[i][0]].x, y1: rooms[connections[i][0]].y,
					x2: rooms[connections[i][1]].x, y2: rooms[connections[i][1]].y
				});
			}
		}
		for (key in rooms) {
			var color = (key == start) ? 'yellow' : 'green';
			color = (key == end) ? 'red' : color;
			canvas.drawArc({
				layer: true,
				fillStyle: color,
				strokeStyle: 'red',
				stroleWidth: 2,
				x: rooms[key].x, y: rooms[key].y,
				radius: 15
			});
		}
		canvas.drawArc({
			name: 'room',
			layer: true,
			x: rooms[start].x, y: rooms[start].y,
			radius: 15,
			fillStyle: 'brown'
		});
		$(document).bind('keypress', function(event) {
			if (event.which == 50) {
				canvas.animateLayer('room', {
					x: 200, y: 100
				});
			}
		});
	});
});
	</script>
	<!-- <script src="script.js"></script> -->
</body>
</html>