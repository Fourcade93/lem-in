var canvas;
var ctx;
var rooms;
var start;
var end;
var moves;
var ants;
var cur_move = 0;

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
			var one = singl[j].split('-');
			obj[one[0]] = one[1];
		};
		ret.push(obj);
	}
	return ret;
}

$(document).ready(function() {
	canvas = $('#canvas');
	$.get('get_input.php?rooms=get', function (data, status) {
		rooms = roomsFactory(data);
	});
	$.get('get_input.php?start=get', function (data, status) {
		start = data;
	});
	$.get('get_input.php?end=get', function (data, status) {
		end = data;
	});
	$.get('get_input.php?ants=get', function (data, status) {
		ants = parseInt(data);
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
			var color = (key == start) ? 'black' : 'green';
			color = (key == end) ? 'red' : color;
			canvas.drawRect({
				layer: true,
				fillStyle: color,
				strokeStyle: 'red',
				stroleWidth: 2,
				x: rooms[key].x, y: rooms[key].y,
				width: 40, height: 40
			}).drawText({
				fillStyle: '#fff',
				layer: true,
				x: rooms[key].x, y: rooms[key].y,
				fontSize: 16,
				fontFamily: 'Verdana, sans-serif',
				text: key
			});
		}
	});
	$.get('get_input.php?output=get', function (data, status) {
		moves = movesFactory(data);
		for (var i = 1; i <= ants; i++) {
			canvas.drawArc({
				name: "L" + i,
				layer: true,
				x: rooms[start].x, y: rooms[start].y,
				radius: 18,
				fillStyle: 'brown'
			}).drawText({
				fillStyle: '#fff',
				name: "L" + i + "t",
				layer: true,
				x: rooms[start].x, y: rooms[start].y,
				fontSize: 16,
				fontFamily: 'Verdana, sans-serif',
				text: 'L' + i
			});
		}
	});
	$(document).bind("keypress", function (event) {
		if (event.which == 50) {
			if (cur_move < moves.length) {
				for (elem in moves[cur_move]) {
					canvas.animateLayer(elem, {
						x: rooms[moves[cur_move][elem]].x,
						y: rooms[moves[cur_move][elem]].y
					}, 1500);
					canvas.animateLayer(elem + "t", {
						x: rooms[moves[cur_move][elem]].x,
						y: rooms[moves[cur_move][elem]].y
					}, 1500);
				}
				cur_move++;
			}
		}
	});
});