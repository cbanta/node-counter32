
var Counter32 = require('./build/Release/counter32').Counter32;

var c = new Counter32(1);

var last_val = 0;
var step = 1000000000;

while( last_val < c.getValue() ){
	for( var i = 0; i < step; i++ ){
		c.plusOne();
	}
	last_val = last_val + step;
	console.log(last_val);
}

console.log(c.getValue());
console.log(last_val);
