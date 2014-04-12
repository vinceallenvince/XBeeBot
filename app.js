var EventEmitter = require('events').EventEmitter,
    serialport = require("serialport"),
    keypress = require('keypress');

/*connect = require('connect'),
    io = require('socket.io').listen(1337),*/

keypress(process.stdin);

var emitter = new EventEmitter();

var SerialPort = serialport.SerialPort; // localize object constructor

//var mySerialPort = '/dev/tty.usbmodem1411'; // Arduino connected via usb
var mySerialPort = '/dev/tty.usbserial-A702LCUI'; // XBee

var sp = new SerialPort(mySerialPort, {
  baudrate: 57600,
  parser: serialport.parsers.readline('\n')
});

sp.on('open', function () {
console.log('!!!');
  process.stdin.resume();
  process.stdin.setEncoding('utf8');
  process.stdin.setRawMode(true);

  process.stdin.on('keypress', function (ch, key) {

    if ( !key ) return;

    if ( key.name == 'q' ) {
      console.log('Quitting');
      process.exit();
    } else if ( key.name == 'up' ) {
      sp.write('1');
    } else if ( key.name == 'right' ) {
      sp.write('2');
    } else if ( key.name == 'down' ) {
      sp.write('3');
    } else if ( key.name == 'left' ) {
      sp.write('4');
    } else if ( key.name == 'space' ) {
      sp.write('5');
    } else if ( key.name == 'a' ) {
      sp.write('6');
    } else if ( key.name == 's' ) {
      sp.write('7');
    } else if ( key.name == 'd' ) {
      sp.write('8');
    } else if ( key.name == 'f' ) {
      sp.write('9');
    }

  });

  // when we receive data, publish it via the emitter
  sp.on('data', function(data) {
    emitter.emit('data', data);
  });

});



// host a single page
/*connect(connect.static(__dirname + '/public')).listen(8000);

// start web sockets
io.sockets.on('connection', function(socket) {

  socket.emit('connected');

  // when we receive data, send it to the web sockets client
  emitter.on('data', function(data) {
    socket.emit('data', data);
  });

});*/
