var canvas;
var ctx;
var rooms;

function roomsFactory(rooms) {
	var rooms = rooms.split('\n');
	var len = rooms.length;
	var	ret = {};
	for (var i = 0; i < len; i++) {
		var one = rooms[i].split(' ');
		ret[one[0]] = {x : (parseInt(one[1]) + 1) * 50, y : (parseInt(one[2]) + 1) * 50};
	}
	return ret;
}

$(document).ready(function() {
	canvas = $('#canvas');
	$.get('get_input.php?rooms=get', function(data, status) {
		rooms = roomsFactory(data);
		for (key in rooms) {
			canvas.drawRect({
				fillStyle: 'green',
				strokeStyle: 'red',
				stroleWidth: 2,
				x: rooms[key].x, y: rooms[key].y,
				fromCenter: false,
				width: 30,
				height: 30
			});
		}
	});
});