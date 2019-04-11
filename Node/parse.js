/*

minimist模块用于解析命令行参数。

$ node example/parse.js -a beep -b boop
{ _: [], a: 'beep', b: 'boop' }

$ node example/parse.js -x 3 -y 4 -n5 -abc --beep=boop foo bar baz
{ _: [ 'foo', 'bar', 'baz' ],
  x: 3,
  y: 4,
  n: 5,
  a: true,
  b: true,
  c: true,
  beep: 'boop' }
  
# npm install minimist -g
node parse.js -a beep -b boop
node parse.js -x 3 -y 4 -n5 -abc --beep=boop foo bar baz

*/

var argv = require('minimist')(process.argv.slice(2));
console.dir(argv);
