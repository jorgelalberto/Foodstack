const greetModule = require('./build/Release/greet.node');

// see properties on 'exports' object
console.log('exports : ', greetModule);
console.log()

// excecute 'greetHello' func
console.log('greetModule.greetHello() : ', greetModule.greetHello());
console.log();